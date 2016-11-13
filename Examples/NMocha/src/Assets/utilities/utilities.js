var Utility = {};

Utility.isIPhone = function() {
	return Ti.Platform.osname === 'iphone';
};

Utility.isIPad = function() {
	return Ti.Platform.osname === 'ipad';
};

Utility.isIOS = function() {
	return this.isIPhone() || this.isIPad();
};

Utility.isAndroid = function() {
	return ('android' === Ti.Platform.osname);
};

Utility.isWindowsPhone = function() {
	return Ti.Platform.osname === 'windowsphone';
};

Utility.isWindowsDesktop = function() {
	return Ti.Platform.osname === 'windowsstore';
};

Utility.isWindows = function() {
	return this.isWindowsPhone() || this.isWindowsDesktop();
};

Utility.isWindows10 = function() {
	return this.isWindows() && Ti.Platform.version.indexOf('10.0') == 0;
}

Utility.isWindows10Desktop = function() {
	return this.isWindowsDesktop() && this.isWindows10();
};

Utility.isWindows8_1 = function() {
	return this.isWindows() && Ti.Platform.version.indexOf('6.3.9600') == 0;
}

module.exports = Utility;
