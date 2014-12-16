/**
 * Titanium for Windows
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */
'use strict';

var button = Ti.UI.createButton({
  top: 20,
  bottom: 20,
  width: 200,
  height: Ti.UI.SIZE
});

button.title = 'Neeraj Says...';
//button.title = 'Ingo Says...';
//button.title = 'Chris Barber Says...';

button.addEventListener('click', function(e) {
  Ti.API.warn('Goals without a timeline are just a dream.');
  //Ti.API.info('Your estimation factor is 4X.');
  //Ti.API.info("I am from Santa Clara.");
});

var view = Ti.UI.createView({
  bottom: 50,
  right: 50,
  width: 300,
  height: Ti.UI.SIZE
});

view.add(button);

var window = Ti.UI.createWindow();
window.backgroundColor = "Ivory";
window.add(view);

window.open();

Ti.API.info('app.js running...');

var count = 0;
var timerId = setInterval(function () {
	Ti.API.info('setInterval: timerId = ' + timerId + ', count = ' + count);
	if (++count > 10) {
		clearInterval(timerId);
	}
}, 1000 /* ms */);

Ti.API.info('setInterval: timerId = ' + timerId);
