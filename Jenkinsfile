#!groovy​

def gitCommit = ''
def testTimeout = 20

def build(sdkVersion, msBuildVersion, architecture, gitCommit) {
	unstash 'sources' // for build
	if (fileExists('dist/windows')) {
		bat 'rmdir dist\\windows /Q /S'
	}
	bat 'mkdir dist\\windows'

	dir('Tools/Scripts') {
		bat 'npm install .'
		echo "Installing JSC built for Windows ${sdkVersion}"
		bat "node setup.js -s ${sdkVersion} --no-color --no-progress-bars"
		bat 'rmdir node_modules /Q /S'
	}

	dir('Tools/Scripts/build') {
		bat 'npm install .'

		timeout(45) {
			echo "Building for ${architecture} ${sdkVersion}"
			def raw = bat(returnStdout: true, script: "echo %JavaScriptCore_${sdkVersion}_HOME%").trim()
			def jscHome = raw.split('\n')[-1]
			echo "Setting JavaScriptCore_HOME to ${jscHome}"
			withEnv(["JavaScriptCore_HOME=${jscHome}"]) {
				bat "node build.js -s ${sdkVersion} -m ${msBuildVersion} -o ${architecture} --sha ${gitCommit}"
			}
		}
	}
	archiveArtifacts artifacts: 'dist/**/*'
}

// wrap in timestamps
timestamps {
	// Generate docs on generic node
	stage('Docs') {
		node('npm && node') {
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
			stash name: 'NMocha', includes: 'Examples/NMocha/**/*'

			if (isUnix()) {
				sh 'mkdir -p dist/windows/doc'
			} else {
				bat 'mkdir dist\\\\windows\\\\doc'
			}
			echo 'Generating docs'
			dir('apidoc') {
				if (isUnix()) {
					sh 'npm install .'
					sh 'node ti_win_yaml.js'
				} else {
					bat 'call npm install .'
					bat 'call node ti_win_yaml.js'
				}
			}
			echo 'copying generated docs to dist folder'
			if (isUnix()) {
				sh 'mv apidoc/Titanium dist/windows/doc/Titanium'
			} else {
				bat '(robocopy apidoc\\\\Titanium dist\\\\windows\\\\doc\\\\Titanium /e) ^& IF %ERRORLEVEL% LEQ 3 cmd /c exit 0'
			}
			archiveArtifacts artifacts: 'dist/**/*'
		} // node
	} // stage('Docs')

	stage ('Build') {
		def targetBranch = env.CHANGE_TARGET // if it's a PR, use target merge branch as branch of SDK to install
		if (!env.BRANCH_NAME.startsWith('PR-')) {
			targetBranch = env.BRANCH_NAME // if it isn't a PR, try to match the current branch
		}
		if (!targetBranch) { // if all else fails, use master as SDK branch to test with
			targetBranch = 'master'
		}

		parallel(
			'Windows 8.1 Store x86': {
				node('msbuild-12 && (vs2013 || vs2015) && hyper-v && windows-sdk-8.1 && npm && node && cmake && jsc') {
					build('8.1', '12.0', 'WindowsStore-x86', gitCommit)

					unstash 'NMocha' // for tests
					dir('Tools/Scripts/build') {
						timeout(testTimeout) {
							echo 'Running Tests on Windows 8.1 Desktop'
							bat "node test.js -s 8.1 -T ws-local -p Windows8_1.Store -b ${targetBranch}"
						}
						// Kill the desktop app, so workspace cleanup works...
						bat 'taskkill /IM Mocha.exe /F'
					}
					junit 'dist/junit_report.xml'
				}
			},
			'Windows 8.1 Phone x86': {
				node('msbuild-12 && (vs2013 || vs2015) && hyper-v && windows-sdk-8.1 && npm && node && cmake && jsc') {
					build('8.1', '12.0', 'WindowsPhone-x86', gitCommit)

					unstash 'NMocha' // for tests
					dir('Tools/Scripts/build') {
						timeout(testTimeout) {
							echo 'Running Tests on Windows 8.1 Phone Emulator'
							bat "node test.js -s 8.1 -T wp-emulator -p Windows8_1.Phone -b ${targetBranch}"
						}
						// Kill the phone emulator, so workspace cleanup works...
						bat 'taskkill /IM xde.exe'
					}
					junit 'dist/junit_report.xml'
				}
			},
			'Windows 8.1 Phone ARM': {
				node('msbuild-12 && (vs2013 || vs2015) && windows-sdk-8.1 && npm && node && cmake && jsc') {
					build('8.1', '12.0', 'WindowsPhone-ARM', gitCommit)
				}
			},
			'Windows 10 x86': {
				node('msbuild-14 && vs2015 && hyper-v && windows-sdk-10 && npm && node && cmake && jsc') {
					build('10.0', '14.0', 'WindowsStore-x86', gitCommit)

					unstash 'NMocha' // for tests
					dir('Tools/Scripts/build') {
						timeout(testTimeout) {
							echo 'Running Tests on Windows 10 Desktop'
							bat "node test.js -s 10.0 -T ws-local -p Windows10.Store -b ${targetBranch}"
						}
						// Kill the desktop app, so workspace cleanup works...
						bat 'taskkill /IM Mocha.exe /F'
					}
					junit 'dist/junit_report.xml'
					// Delete the report from store, so if phone fails we don't pick this one up
					bat 'del /f /q dist\\junit_report.xml'

					dir('Tools/Scripts/build') {
						timeout(testTimeout) {
							echo 'Running Tests on Windows 10 Phone Emulator'
							bat "node test.js -s 10.0.10586 -T wp-emulator -p Windows10.Phone -b ${targetBranch}"
						}
						// Kill the phone emulator, so workspace cleanup works...
						bat 'taskkill /IM xde.exe'
					}
					junit 'dist/junit_report.xml'
				}
			},
			'Windows 10 ARM': {
				node('msbuild-14 && vs2015 && hyper-v && windows-sdk-10 && npm && node && cmake && jsc') {
					build('10.0', '14.0', 'WindowsStore-ARM', gitCommit)
				}
			},
			failFast: true
		)
	}

	// If not a PR, trigger titanium_mobile to build
	if (!env.BRANCH_NAME.startsWith('PR-')) {
		// Trigger build of titanium_mobile in our pipeline multibranch group!
		build job: "../titanium_mobile/${env.BRANCH_NAME}", wait: false
	}
}
