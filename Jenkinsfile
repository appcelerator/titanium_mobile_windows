#!groovy​

def gitCommit = ''

// wrap in timestamps
timestamps {
	// Generate docs on generic node
	stage('Docs') {
		node('npm && node') {
			try {
				// TODO Checkout just apidoc folder?
				// checkout scm
				// Hack for JENKINS-37658 - see https://support.cloudbees.com/hc/en-us/articles/226122247-How-to-Customize-Checkout-for-Pipeline-Multibranch
				checkout([
					$class: 'GitSCM',
					branches: scm.branches,
					extensions: scm.extensions + [
						[$class: 'CleanCheckout'],
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
					bat 'robocopy apidoc\\\\Titanium dist\\\\windows\\\\doc\\\\Titanium /e'
				}
				archiveArtifacts artifacts: 'dist/**/*'
			} catch (e) {
				// if any exception occurs, mark the build as failed
				currentBuild.result = 'FAILURE'
				throw e
			} finally {
				step([$class: 'WsCleanup', notFailBuild: true])
			}
		}
	}

	stage ('Build') {
		def targetBranch = 'master'
		if (!env.BRANCH_NAME.startsWith('PR-')) {
			targetBranch = env.BRANCH_NAME
		}
		parallel(
			'Windows 8.1': {
				// Windows 8.1 SDK build
				// FIXME Support vs2013 or vs2015 by separating the JSC 8.1/10 builds
				node('msbuild-12 && vs2013 && hyper-v && windows-sdk-8.1 && npm && node && cmake && jsc') {
					try {
						unstash 'sources' // for build
						unstash 'NMocha' // for tests
						bat 'mkdir dist\\windows'
						dir('Tools/Scripts') {
							bat 'npm install .'
							echo 'Installing JSC built for Windows 8.1'
							bat 'node setup.js -s 8.1 --no-color --no-progress-bars'
							bat 'rmdir node_modules /Q /S'
						}

						dir('Tools/Scripts/build') {
							bat 'npm install .'

							// TODO Parallelize the builds for each platform/arch!
							timeout(80) {
								echo 'Building for Windows 8.1'
								bat "node build.js -s 8.1 -m 12.0 -o WindowsStore-x86 --sha ${gitCommit}"
								bat "node build.js -s 8.1 -m 12.0 -o WindowsPhone-x86 --sha ${gitCommit}"
								bat "node build.js -s 8.1 -m 12.0 -o WindowsPhone-ARM --sha ${gitCommit}"
							}
							archiveArtifacts artifacts: '../../../dist/**/*'

							// TODO Parallelize the tests!
							timeout(10) {
								echo 'Running Tests on Windows 8.1 Phone Emulator'
								bat "node test.js -s 8.1 -T wp-emulator -p Windows8_1.Phone -b ${targetBranch}"
								junit '../../../dist/junit_report*.xml'
							}

							timeout(10) {
								echo 'Running Tests on Windows 8.1 Desktop'
								bat "node test.js -s 8.1 -T ws-local -p Windows8_1.Store -b ${targetBranch}"
								junit '../../../dist/junit_report*.xml'
							}
							bat 'rmdir node_modules /Q /S'
						}
					} catch (e) {
						// if any exception occurs, mark the build as failed
						currentBuild.result = 'FAILURE'
						throw e
					} finally {
						step([$class: 'WsCleanup', notFailBuild: true])
					}
				}
			},
			'Windows 10': {
				// Windows 10 SDK build
				node('msbuild-14 && vs2015 && hyper-v && windows-sdk-10 && npm && node && cmake && jsc') {
					try {
						unstash 'sources' // for build
						unstash 'NMocha' // for tests
						bat 'mkdir dist\\windows'

						dir('Tools/Scripts') {
							bat 'npm install .'
							echo 'Installing JSC built for Windows 10'
							bat 'node setup.js -s 10.0 --no-color --no-progress-bars'
							bat 'rmdir node_modules /Q /S'
						}

						dir('Tools/Scripts/build') {
							bat 'npm install .'

							// TODO Parallelize the builds for each arch!
							timeout(60) {
								echo 'Building for Windows 10'
								bat "node build.js -s 10.0 -m 14.0 -o WindowsStore-x86 --sha ${gitCommit}"
								bat "node build.js -s 10.0 -m 14.0 -o WindowsStore-ARM --sha ${gitCommit}"
							}
							archiveArtifacts artifacts: '../../../dist/**/*'

							// TODO Parallelize the tests!
							timeout(10) {
								echo 'Running Tests on Windows 10 Phone Emulator'
								bat "node test.js -s 10.0.10586 -T wp-emulator -p Windows10.Phone -b ${targetBranch}"
								junit '../../../dist/junit_report*.xml'
							}

							timeout(10) {
								echo 'Running Tests on Windows 10 Desktop'
								bat "node test.js -s 10.0 -T ws-local -p Windows10.Store -b ${targetBranch}"
								junit '../../../dist/junit_report*.xml'
							}
							bat 'rmdir node_modules /Q /S'
						}
					} catch (e) {
						// if any exception occurs, mark the build as failed
						currentBuild.result = 'FAILURE'
						throw e
					} finally {
						step([$class: 'WsCleanup', notFailBuild: true])
					}
				}
			}
		)
	}

	// If not a PR, trigger titanium_mobile to build
	if (!env.BRANCH_NAME.startsWith('PR-')) {
		// Trigger build of titaium_mobile in our pipeline multibranch group!
		build job: "appcelerator/titanium_mobile/${env.BRANCH_NAME}", wait: false
	}
}
