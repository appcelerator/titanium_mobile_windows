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
 '{"date":"2015-05-28T08:55:16.811Z","results":[{"state":"passed","duration":16,"suite":"Titanium.Native","title":"helloworld"}]}\n'
 + '\n!TEST_RESULTS_STOP!');
