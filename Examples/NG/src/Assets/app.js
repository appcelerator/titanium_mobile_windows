var win = Ti.UI.createWindow({ backgroundColor: 'green' }),
    label = Ti.UI.createLabel({
        width: Ti.UI.FILL,
        height: '50%',
        textAlign: Ti.UI.TEXT_ALIGNMENT_CENTER,
        backgroundColor: 'white'
    });
win.add(label);
win.addEventListener('open', function () {
    /*
    var System_Object = require('System.Object');
    var object = new System_Object();
    alert(object.GetHashCode());
    var System_Math = require('System.Math');
    alert(System_Math.Abs(-1.23));
    */
    var MemoryManager = require('Windows.System.MemoryManager');
    var appMemoryUsageLimit = MemoryManager.AppMemoryUsageLimit / 1024 / 1024;
    var appMemoryUsage      = MemoryManager.AppMemoryUsage / 1024 / 1024;

    label.text = 'MemoryManager.AppMemoryUsageLimit = ' + parseInt(appMemoryUsageLimit)
        + " MB\nMemoryManager.AppMemoryUsage = " + parseInt(appMemoryUsage) + " MB";
});
win.open();
