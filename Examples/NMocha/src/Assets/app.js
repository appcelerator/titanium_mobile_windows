var Window = require('Windows.UI.Xaml.Window'),
    TextBlock = require('Windows.UI.Xaml.Controls.TextBlock'),
    window = Window.Current,
    text = new TextBlock();

text.Text = "Hello, world!";
//text.TextAlignment = TextAlignment.Center;
//text.VerticalAlignment = VerticalAlignment.Center;
//text.HorizontalAlignment = HorizontalAlignment.Center;
text.FontSize = 60;

window.Content = text;
window.Activate();

Ti.API.info('!TEST_RESULTS_START!\n' +
        (JSON.stringify({
            date: new Date,
            results: [{"state":"passed","duration":15,"suite":"Titanium.Filesystem.File","title":"not_exists"}]
        })) +
    '\n!TEST_RESULTS_STOP!');

