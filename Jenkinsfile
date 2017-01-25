#!groovy​

// Generate docs on generic node
stage('Docs') {
	node('npm && node') {
		// TODO Checkout just apidoc folder?
		// checkout scm
		echo Arrays.toString(scm.userRemoteConfigs.toArray())
		// Hack for JENKINS-37658 - see https://support.cloudbees.com/hc/en-us/articles/226122247-How-to-Customize-Checkout-for-Pipeline-Multibranch
		checkout([
			$class: 'GitSCM',
			branches: scm.branches,
			extensions: scm.extensions + [
				[$class: 'CleanCheckout'],
				[$class: 'SubmoduleOption', disableSubmodules: false, parentCredentials: false, recursiveSubmodules: true, reference: '', trackingSubmodules: false],
				[$class: 'CloneOption', depth: 30, honorRefspec: true, noTags: true, reference: '', shallow: true]
			],
			userRemoteConfigs: scm.userRemoteConfigs
		])
		// Stash our source code/scripts so we don't need to checkout again?
		stash name: 'sources', includes: '.', excludes: 'apidoc/,test/'

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
	}
}

stage ('Build') {
	parallel(
		'Windows 8.1': {
			// Windows 8.1 SDK build
			node('msbuild-12 && vs2013 && hyper-v && windows-sdk-8.1 && cmake && npm && node && jsc') {
				unstash 'sources'
				bat 'Tools\\\\Scripts\\\\win81.bat'
				archiveArtifacts artifacts: 'dist/**/*'
				junit 'dist/junit_report*.xml'
			}
		},
		'Windows 10': {
			// Windows 10 SDK build
			node('msbuild-14 && vs2015 && hyper-v && windows-sdk-10 && npm && node && cmake && jsc') {
				unstash 'sources'
				bat 'Tools\\\\Scripts\\\\win10.bat'
				archiveArtifacts artifacts: 'dist/**/*'
				junit 'dist/junit_report*.xml'
			}
		}
	)
}
