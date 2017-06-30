/**
 * Create a new `Ti.UI.TabGroup`.
 */
var tabGroup = Ti.UI.createTabGroup();

/**
 * Add the two created tabs to the tabGroup object.
 */
tabGroup.addTab(createTab("Tab 1", "I am Window 1"));
tabGroup.addTab(createTab("Tab 2", "I am Window 2"));

/**
 * Open the tabGroup
 */
tabGroup.open();

/**
 * Creates a new Tab and configures it.
 *
 * @param  {String} title The title used in the `Ti.UI.Tab` and it's included `Ti.UI.Window`
 * @param  {String} message The title displayed in the `Ti.UI.Label`
 * @return {String} icon The icon used in the `Ti.UI.Tab`
 */
function createTab(title, message, icon) {
    var win = Ti.UI.createWindow({
        title: title,
        backgroundColor: '#fff'
    });

    var label = Ti.UI.createLabel({
        text: message,
        color: "#333",
        font: {
            fontSize: 20
        }
    });

    win.add(label);

    var tab = Ti.UI.createTab({
        title: title,
        window: win
    });

    return tab;
}
