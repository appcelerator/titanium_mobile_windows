var win = Ti.UI.createWindow({ backgroundColor: 'green' });

win.addEventListener('open', function () {
    Ti.Locale.setLanguage('en');
    Ti.API.info('current language is: ' + Ti.Locale.getCurrentLanguage());
    Ti.API.info('before change ' + L('this is my key'));
    Ti.Locale.setLanguage('es');
    Ti.API.info('new language is: ' + Ti.Locale.getCurrentLanguage());
    Ti.API.info('after change ' + L('this is my key'));
});

win.open();
