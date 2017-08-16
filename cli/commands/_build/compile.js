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
		nativeVcxProj = path.resolve(this.cmakeTargetDir, 'Native', 'TitaniumWindows_Native.vcxproj');

	this.logger.info(__('Targeting Windows SDK: %s', this.targetPlatformSdkVersion.cyan || this.wpsdk.cyan));
	this.logger.info(__('Running MSBuild on solution: %s', slnFile.cyan));

	// Modify the vcxproj to inject some properties, so we always bundle
	var modified = fs.readFileSync(vcxproj, 'utf8');
	fs.existsSync(vcxproj) && fs.renameSync(vcxproj, vcxproj + '.bak');
	// Only modify the one property group we care about!
	modified = modified.replace(/<\/PropertyGroup>\s*<ItemDefinitionGroup/m,
		'<AppxBundle>Always</AppxBundle>' +
		'<AppxBundlePlatforms>' + this.arch + '</AppxBundlePlatforms>' +
		(
			!/^ws-local|dist-winstore$/.test(this.target) && this.wpsdk != '10.0' ? '' :
			'<PackageCertificateThumbprint>' + this.certificateThumbprint + '</PackageCertificateThumbprint>' +
			'<PackageCertificateKeyFile>' + this.certificatePath + '</PackageCertificateKeyFile>'
		) + '$&');

	// Fix quoted hint paths for native module winmd paths
	modified = modified.replace(/<HintPath>"([^"]+?)"<\/HintPath>/, '<HintPath>$1<\/HintPath>');
	fs.writeFileSync(vcxproj, modified);

	// Modify the Native vcxproj to fix quoted hint paths for module winmd paths
	modified = fs.readFileSync(nativeVcxProj, 'utf8');
	fs.existsSync(nativeVcxProj) && fs.renameSync(nativeVcxProj, nativeVcxProj + '.bak');
	modified = modified.replace(/<HintPath>"([^"]+?)"<\/HintPath>/, '<HintPath>$1<\/HintPath>');
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
