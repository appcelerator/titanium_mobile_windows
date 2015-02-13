// this sets the background color of the master UIView (when there are no windows/tab groups on it)
Titanium.UI.setBackgroundColor('#000');

// create tab group
var tabGroup = Titanium.UI.createTabGroup();


//
// create base UI tab and root window
//
var win1 = Titanium.UI.createWindow({
    title: 'Tab 1',
    backgroundColor: 'Blue'
});
var tab1 = Titanium.UI.createTab({
    icon: 'KS_nav_views.png',
    title: 'Tab 1',
    window: win1
});

var textField = Ti.UI.createTextField({
    top: 290,
    width: 200
});
textField.addEventListener('change', function (e) {
    Ti.API.info('The text field changed: ' + e.value);
});
textField.addEventListener('blur', function (e) {
    Ti.API.info('The text field lost focus!');
});
textField.addEventListener('focus', function (e) {
    Ti.API.info('The text field gained focus!');
});
textField.addEventListener('return', function (e) {
    Ti.API.info('The text field return key was hit!');
});
win1.add(textField);

var label = Ti.UI.createLabel({
    'text': 'quotes go here',
    'color': '#ff00ff',
    'top': 500,
    'left': 10
});

var imageView = Ti.UI.createImageView({
    'top': 420,
    'left': 10,
    image: 'http://iconizer.net/files/IconSweets/orig/email.png'
});

imageView.addEventListener('click', function (e) {
    Ti.API.warn('Image, Art, Faith, Mystery.');
});

var button = Ti.UI.createButton({
    title: 'Neeraj Says...'
});

var button2 = Ti.UI.createButton({
    title: 'Ingo Says...'
});

var button3 = Ti.UI.createButton({
    title: 'Chris Barber Says...'
});

button.addEventListener('click', function (e) {
    alert('Goals without a timeline are just a dream.');
    label.text = 'Goals without a timeline are just a dream.';
});

button2.addEventListener('click', function (e) {
    alert('Your estimation factor is 4X.');
    label.text = 'Your estimation factor is 4X.';
});

button3.addEventListener('click', function (e) {
    alert("I am from Santa Clara.");
    label.text = "I am from Santa Clara.";
});

var view = Ti.UI.createView({
    'top': 20,
    'left': 10,
    'width': 145,
    'height': 50,
    backgroundColor: "Red"
});
view.add(button);

var view2 = Ti.UI.createView({
    'top': 120,
    'left': 110,
    'width': 130,
    'height': 50,
    backgroundColor: "Pink"
});
view2.add(button2);

var view3 = Ti.UI.createView({
    'top': 220,
    'left': 210,
    'width': 190,
    'height': 50,
    backgroundColor: 'Green'
});
view3.add(button3);

win1.add(label);
win1.add(imageView);
win1.add(view);
win1.add(view2);
win1.add(view3);


//
// create controls tab and root window
//
var win2 = Titanium.UI.createWindow({
    title: 'Tab 2',
    backgroundColor: '#fff'
});
var tab2 = Titanium.UI.createTab({
    icon: 'KS_nav_ui.png',
    title: 'Tab 2',
    window: win2
});

var label2 = Titanium.UI.createLabel({
    color: '#999',
    text: 'I am Window 2',
    font: { fontSize: 20, fontFamily: 'Helvetica Neue' },
    textAlign: 'center',
    width: 'auto'
});

win2.add(label2);


//
//  add tabs
//
tabGroup.addTab(tab1);
tabGroup.addTab(tab2);

// open tab group
tabGroup.open();

Ti.API.info('app.js running...');

var count = 0;
var timerId = setInterval(function () {
    Ti.API.info('setInterval: timerId = ' + timerId + ', count = ' + count);
    if (++count > 10) {
        clearInterval(timerId);

        Ti.API.info("Playing with database API...");

        var db = Ti.Database.open('mydb1Installed');
        Ti.API.info("Opened DB");
        db.execute('CREATE TABLE IF NOT EXISTS people (name TEXT, phone_number TEXT, city TEXT)');
        Ti.API.info("Created people table");
        db.execute('DELETE FROM people');

        var thisName = 'Arthur';
        var thisPhoneNo = '1-617-000-0000';
        var thisCity = 'Mountain View';
        db.execute('INSERT INTO people (name, phone_number, city) VALUES (?, ?, ?)', thisName, thisPhoneNo, thisCity);
        Ti.API.info("Inserted person into people table");

        var personArray = ['Paul', '020 7000 0000', 'London'];
        db.execute('INSERT INTO people (name, phone_number, city) VALUES (?, ?, ?)', personArray);
        Ti.API.info("Inserted person into people table");

        var rows = db.execute('SELECT rowid,name,phone_number,city FROM people');

        Ti.API.info('Row count: ' + rows.rowCount);
        var fieldCount = rows.fieldCount;
        Ti.API.info('Field count: ' + fieldCount);

        while (rows.isValidRow()) {
            Ti.API.info('Person ---> ROWID: ' + rows.fieldByName('rowid') + ', name:' + rows.field(1) + ', phone_number: ' + rows.fieldByName('phone_number') + ', city: ' + rows.field(3));
            rows.next();
        }
        rows.close();
        db.close();
    }
}, 1000 /* ms */);

Ti.API.info('setInterval: timerId = ' + timerId);
