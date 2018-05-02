#!groovy
library 'pipeline-library'
// Keep history of up to 30 builds, but only keep artifacts for the last 5
properties([buildDiscarder(logRotator(numToKeepStr: '30', artifactNumToKeepStr: '5'))])

def gitCommit = ''
// Variables we can change
// FIXME Using the nodejs jenkins plugin introduces complications that cause us not to properly connect to the Windows Phone emulator for logs
// Likely need to modify the firewall rules to allow traffic from the new nodejs install like we do for system install!
def nodeVersion = '8.11.1' // NOTE that changing this requires we set up the desired version on jenkins master first!
def npmVersion = '5.8.0'

def build(sdkVersion, msBuildVersion, architecture, gitCommit, nodeVersion, npmVersion) {
	unstash 'sources' // for build
	if (fileExists('dist/windows')) {
		bat 'rmdir dist\\windows /Q /S'
	}
	bat 'mkdir dist\\windows'

	nodejs(nodeJSInstallationName: "node ${nodeVersion}") {
		ensureNPM(npmVersion)
		dir('Tools/Scripts') {
			bat 'npm ci'
			echo "Installing JSC built for Windows ${sdkVersion}"
			bat "node setup.js -s ${sdkVersion} --no-color --no-progress-bars"
			bat 'rmdir node_modules /Q /S'
		}

		dir('Tools/Scripts/build') {
			bat 'npm ci'

			timeout(45) {
				echo "Building for ${architecture} ${sdkVersion}"
				def raw = bat(returnStdout: true, script: "echo %JavaScriptCore_${sdkVersion}_HOME%").trim()
				def jscHome = raw.split('\n')[-1]
				echo "Setting JavaScriptCore_HOME to ${jscHome}"
				withEnv(["JavaScriptCore_HOME=${jscHome}"]) {
					bat "node build.js -s ${sdkVersion} -m ${msBuildVersion} -o ${architecture} --sha ${gitCommit}"
				}
			} // timeout
		} // dir Tool/Scripts/build
	} // nodejs
	archiveArtifacts artifacts: 'dist/**/*'
} // def build

def unitTests(target, branch, testSuiteBranch, nodeVersion, npmVersion) {
	def defaultEmulatorID = '10-0-1'
	unarchive mapping: ['dist/' : '.'] // copy in built SDK from dist/ folder (from Build stage)
	unstash 'sources'
	nodejs(nodeJSInstallationName: "node ${nodeVersion}") {
		ensureNPM(npmVersion)
		def nodeHome = tool(name: "node ${nodeVersion}", type: 'nodejs')
		echo nodeHome
		bat "netsh advfirewall firewall add rule name=\"Node ${nodeVersion}\" program=\"${nodeHome}\\node.exe\" dir=in action=allow protocol=udp description=\"Firewall rule\""
		bat "netsh advfirewall firewall add rule name=\"Node ${nodeVersion}\" program=\"${nodeHome}\\node.exe\" dir=in action=allow protocol=tcp description=\"Firewall rule\""

		dir('Tools/Scripts/build') {
			echo 'Setting up SDK'
			bat 'npm ci'
			bat "node setupSDK.js --branch ${branch}"
		}

		// if our test suite already exists, delete it
		bat 'if exist titanium-mobile-mocha-suite rmdir titanium-mobile-mocha-suite /Q /S'
		// clone the tests suite fresh
		// FIXME Clone once on initial node and use stash/unstash to ensure all OSes use exact same checkout revision
		dir('titanium-mobile-mocha-suite') {
			// TODO Do a shallow clone, using same credentials as from scm object
			git changelog: false, poll: false, credentialsId: 'd05dad3c-d7f9-4c65-9cb6-19fef98fc440', url: 'https://github.com/appcelerator/titanium-mobile-mocha-suite.git', branch: testSuiteBranch
		}
		unstash 'override-tests'
		bat '(robocopy tests titanium-mobile-mocha-suite /e) ^& IF %ERRORLEVEL% LEQ 3 cmd /c exit 0'
		dir('titanium-mobile-mocha-suite') {
			bat 'npm ci'
			echo "Running tests on ${target}"
			dir('scripts') {
				try {
					timeout(30) {
						if ('ws-local'.equals(target)) {
							bat "node test.js -p windows -T ${target} --skip-sdk-install --cleanup"
						} else if ('wp-emulator'.equals(target)) {
							bat "node test.js -p windows -T ${target} -C ${defaultEmulatorID} --skip-sdk-install --cleanup"
						}
					}
				} catch (e) {
					// Archive the crash reports...
					// Crash event report:
					// C:\ProgramData\Microsoft\Windows\WER\ReportArchive\AppCrash_com.appcelerator_8a7a6091d98a3b6827daff1404991c2a9e161a7_8c8df8cd_0a167d3a\Report.wer
					bat 'mkdir crash_reports'
					dir ('crash_reports') {
						// move command doesn't grok wildcards, so we hack it: https://serverfault.com/questions/374997/move-directory-in-dos-batch-file-without-knowing-full-directory-name
						bat "FOR /d %i IN (C:\\ProgramData\\Microsoft\\Windows\\WER\\ReportArchive\\AppCrash_com.appcelerator_*) DO move %i ."
					}
					archiveArtifacts 'crash_reports/**/*'
					bat 'rmdir crash_reports /Q /S'
					throw e
				} finally {
					// kill the emulator/app
					if ('ws-local'.equals(target)) {
						bat 'taskkill /IM mocha.exe /F 2> nul'
					} else if ('wp-emulator'.equals(target)) {
						bat 'taskkill /IM xde.exe /F 2> nul'
					}
				}
				junit 'junit.*.xml'
			} // dir 'scripts'
		} // dir 'titanium-mobile-mocha-suite'
	} // nodejs
} // def unitTests

// wrap in timestamps
timestamps {
	node('git') {
		stage('Checkout') {
			// checkout scm
			// Hack for JENKINS-37658 - see https://support.cloudbees.com/hc/en-us/articles/226122247-How-to-Customize-Checkout-for-Pipeline-Multibranch
			checkout([
				$class: 'GitSCM',
				branches: scm.branches,
				extensions: scm.extensions + [
					[$class: 'CleanBeforeCheckout'],
					[$class: 'SubmoduleOption', disableSubmodules: false, parentCredentials: true, recursiveSubmodules: true, reference: '', trackingSubmodules: false],
					[$class: 'CloneOption', depth: 30, honorRefspec: true, noTags: true, reference: '', shallow: true]
				],
				userRemoteConfigs: scm.userRemoteConfigs
			])
			// FIXME: Workaround for missing env.GIT_COMMIT: http://stackoverflow.com/questions/36304208/jenkins-workflow-checkout-accessing-branch-name-and-git-commit
			gitCommit = sh(returnStdout: true, script: 'git rev-parse HEAD').trim()
			// Stash our source code/scripts so we don't need to checkout again?
			stash name: 'sources', includes: '**', excludes: 'apidoc/**,test/**,Examples/**'
			stash name: 'override-tests', includes: 'tests/'
		} // Checkout stage

		stage('Docs') {
			if (isUnix()) {
				sh 'mkdir -p dist/windows/doc'
			} else {
				bat 'mkdir dist\\\\windows\\\\doc'
			}
			echo 'Generating docs'

			nodejs(nodeJSInstallationName: "node ${nodeVersion}") {
				ensureNPM(npmVersion)
				dir('apidoc') {
					if (isUnix()) {
						sh 'npm ci'
						sh 'node ti_win_yaml.js'
					} else {
						bat 'npm ci'
						bat 'node ti_win_yaml.js'
					}
				}
			}
			echo 'copying generated docs to dist folder'
			if (isUnix()) {
				sh 'mv apidoc/Titanium dist/windows/doc/Titanium'
			} else {
				bat '(robocopy apidoc\\\\Titanium dist\\\\windows\\\\doc\\\\Titanium /e) ^& IF %ERRORLEVEL% LEQ 3 cmd /c exit 0'
			}
			archiveArtifacts artifacts: 'dist/**/*'
		} // stage('Docs')
	} // node

	// Are we on a PR/feature branch, or a "mainline" branch like master/6_2_X/7_0_X?
	def isMainlineBranch = (env.BRANCH_NAME ==~ /master|\d_\d_(X|\d)/)
	def targetBranch = env.CHANGE_TARGET // if it's a PR, use target merge branch as branch of SDK to install
	if (isMainlineBranch) { // if it's a mainline branch, use the same branch for titanium_mobile
		targetBranch = env.BRANCH_NAME
	}
	if (!targetBranch) { // if all else fails, use master as SDK branch to test with
		targetBranch = 'master'
	}
	// Trigger titanium_mobile if we're on a mainline branch
	def triggerDownstream = isMainlineBranch

	stage('Build') {
		parallel(
			'Windows 10 x86': {
				node('msbuild-14 && vs2015 && windows-sdk-10 && cmake && jsc') {
					build('10.0', '14.0', 'WindowsStore-x86', gitCommit, nodeVersion, npmVersion)
				}
			},
			'Windows 10 ARM': {
				node('msbuild-14 && vs2015 && windows-sdk-10 && cmake && jsc') {
					build('10.0', '14.0', 'WindowsStore-ARM', gitCommit, nodeVersion, npmVersion)
				}
			},
			failFast: true
		)
	} // Stage build

	stage('Test') {
		def testSuiteBranch = targetBranch
		parallel(
			'ws-local': {
				node('msbuild-14 && vs2015 && windows-sdk-10 && cmake') {
					unitTests('ws-local', targetBranch, testSuiteBranch, nodeVersion, npmVersion)
				}
			},
			'wp-emulator': {
				node('msbuild-14 && vs2015 && hyper-v && windows-sdk-10 && cmake') {
					unitTests('wp-emulator', targetBranch, testSuiteBranch, nodeVersion, npmVersion)
				}
			}
		)
	} // stage Test

	// If not a PR, trigger titanium_mobile to build
	if (triggerDownstream) {
		// Trigger build of titanium_mobile in our pipeline multibranch group!
		build job: "../titanium_mobile/${env.BRANCH_NAME}", wait: false
	}
}
