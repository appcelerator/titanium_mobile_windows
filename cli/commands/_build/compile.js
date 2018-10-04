var appc = require('node-appc'),
	fs = require('fs'),
	os = require('os'),
	path = require('path'),
	spawn = require('child_process').spawn,
	ti = require('node-titanium-sdk'),
	windowslib = require('windowslib'),
	__ = appc.i18n(__dirname).__;

/*
 Public API.
 */
exports.mixin = mixin;

/*
 Implementation.
 */
function mixin(WindowsBuilder) {
	WindowsBuilder.prototype.compileApp = compileApp;
}

/**
 * Compiles the generated Visual Studio project.
 *
 * @param {Function} next - A function to call after the Visual Studio project.
 */
function compileApp(next) {
	var _t = this,
		cmakeProjectName = this.sanitizeProjectName(this.cli.tiapp.name),
		slnFile = path.resolve(this.cmakeTargetDir, cmakeProjectName + '.sln'),
		vcxproj = path.resolve(this.cmakeTargetDir, cmakeProjectName + '.vcxproj'),
		ZERO_CHECK = path.resolve(this.cmakeTargetDir, 'ZERO_CHECK.vcxproj'),
		ALL_BUILD  = path.resolve(this.cmakeTargetDir, 'ALL_BUILD.vcxproj'),
		nativeVcxProj = path.resolve(this.cmakeTargetDir, 'Native', 'TitaniumWindows_Native.vcxproj'),
		nativeALL_BUILD = path.resolve(this.cmakeTargetDir, 'Native', 'ALL_BUILD.vcxproj');

	this.logger.info(__('Targeting Windows SDK: %s', this.targetPlatformSdkVersion.cyan || this.wpsdk.cyan));
	this.logger.info(__('Running MSBuild on solution: %s', slnFile.cyan));

	var appxBundleParam = this.useAppxBundle ? 'Always' : 'Never';

	// Modify the vcxproj to inject some properties, so we always bundle
	var modified = fs.readFileSync(vcxproj, 'utf8');
	fs.unlinkSync(vcxproj);
	// Only modify the one property group we care about!
	modified = modified.replace(/<\/PropertyGroup>\s*<ItemDefinitionGroup/m,
		'<AppxBundle>' + appxBundleParam + '</AppxBundle>' +
		'<AppxBundlePlatforms>' + this.arch + '</AppxBundlePlatforms>' +
		(
			!/^ws-local|dist-winstore$/.test(this.target) && this.wpsdk != '10.0' ? '' :
			'<PackageCertificateThumbprint>' + this.certificateThumbprint + '</PackageCertificateThumbprint>' +
			'<PackageCertificateKeyFile>' + this.certificatePath + '</PackageCertificateKeyFile>'
		) + '$&');

	// Fix quoted hint paths for native module winmd paths
	modified = modified.replace(/<HintPath>"([^"]+?)"<\/HintPath>/, '<HintPath>$1<\/HintPath>');
	modified = modified.replace(/<CustomBuild[\s\S]+<\/CustomBuild>/m, '');
	fs.writeFileSync(vcxproj, modified);

	modified = fs.readFileSync(ZERO_CHECK, 'utf8');
	modified = modified.replace(/<CustomBuild[\s\S]+<\/CustomBuild>/m, '');
	fs.writeFileSync(ZERO_CHECK, modified);

	modified = fs.readFileSync(ALL_BUILD, 'utf8');
	modified = modified.replace(/<CustomBuild[\s\S]+<\/CustomBuild>/m, '');
	fs.writeFileSync(ALL_BUILD, modified);

	modified = fs.readFileSync(nativeALL_BUILD, 'utf8');
	modified = modified.replace(/<CustomBuild[\s\S]+<\/CustomBuild>/m, '');
	fs.writeFileSync(nativeALL_BUILD, modified);

	// Modify the Native vcxproj to fix quoted hint paths for module winmd paths
	modified = fs.readFileSync(nativeVcxProj, 'utf8');
	fs.unlinkSync(nativeVcxProj);
	modified = modified.replace(/<HintPath>"([^"]+?)"<\/HintPath>/, '<HintPath>$1<\/HintPath>');
	modified = modified.replace(/<CustomBuild[\s\S]+<\/CustomBuild>/m, '');
	fs.writeFileSync(nativeVcxProj, modified);

	// Use spawn directly so we can pipe output as we go
	// FIXME Edit windowslib to allow realtime output
	var vsInfo = this.windowsInfo.selectedVisualStudio,
		p;

	if (!vsInfo) {
		_t.logger.error(__('Unable to find a supported Visual Studio installation'));
		_t.logger.log();
		process.exit(1);
	}

	// Use spawn directly so we can pipe output as we go
	p = spawn((process.env.comspec || 'cmd.exe'), ['/S', '/C', '"', vsInfo.vsDevCmd.replace(/[ \(\)\&]/g, '^$&') +
		' &&' + ' MSBuild' + ' /p:Platform=' + _t.cmakeArch + ' /p:Configuration=' + _t.buildConfiguration + ' ' + slnFile, '"'
	], {windowsVerbatimArguments: true});
	
	p.stdout.on('data', function (data) {
		var line = data.toString().trim();
		// msbuild produces "Invalid qualifier" warning for all files that has minus sign (-) in the middle of the file name!
		// It makes no harm and we just can ignore it.
		if (line.indexOf('GENERATEPROJECTPRIFILE : warning PRI249: 0xdef00520 - Invalid qualifier') >= 0) {
			return;
		}
		if (line.indexOf('error ') >= 0) {
			_t.logger.error(line);
		}
		else if (line.indexOf('warning ') >= 0) {
			_t.logger.warn(line);
		}
		else if (line.indexOf(':\\') === -1) {
			_t.logger.debug(line);
		}
		else {
			_t.logger.trace(line);
		}
	});
	p.stderr.on('data', function (data) {
		_t.logger.warn(data.toString().trim());
	});
	p.on('close', function (code) {

		if (code != 0) {
			process.exit(1); // Exit with code from msbuild?
		}

		next();
	});
}
