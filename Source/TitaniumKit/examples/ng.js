/**
 * TitaniumKit
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

button.addEventListener('click', function(e) {
  Ti.API.warn('Goals without a timeline are just a dream.');
});

var view = Ti.UI.createView({
  bottom: 50,
  right: 50,
  width: 300,
  height: Ti.UI.SIZE
});

view.add(button);

var window = Ti.UI.createWindow();
window.add(view);

window.open();

Ti.API.info(Ti.Platform.osname);
Ti.API.info('ng.js running...');
