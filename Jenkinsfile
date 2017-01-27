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
				stash name: 'sources', includes: '**', excludes: 'apidoc/**,test/**'

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
						unstash 'sources'
						bat "Tools\\\\Scripts\\\\win81.bat ${gitCommit} ${targetBranch}"
						archiveArtifacts artifacts: 'dist/**/*'
						junit 'dist/junit_report*.xml'
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
						unstash 'sources'
						bat "Tools\\\\Scripts\\\\win10.bat ${gitCommit} ${targetBranch}"
						archiveArtifacts artifacts: 'dist/**/*'
						junit 'dist/junit_report*.xml'
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
