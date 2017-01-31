/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2011-2016 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */
var should = require('./should'),
	utilities = require('./utilities/utilities');

if (utilities.isWindows()) {
	describe('Titanium.App.Windows.BackgroundService', function () {

		// Skip on Windows 8.1
		(Ti.Platform.version.indexOf('8.1' == 0) ? it.skip : it)('API', function (finish) {
			should(Ti.App.Windows).be.an.Object;
			should(Ti.App.Windows.BackgroundService).be.an.Object;
			should(Ti.App.Windows.BackgroundService.registerTimerTask).be.a.Function;
			should(Ti.App.Windows.BackgroundService.unregisterAllTasks).be.a.Function;
			finish();
		});

		// Skip on Windows 8.1
		(Ti.Platform.version.indexOf('8.1' == 0) ? it.skip : it)('registerTimerTask', function (finish) {
			var task = Ti.App.Windows.BackgroundService.registerTimerTask('TitaniumWindows_Ti.BackgroundServiceTask', 15, true);
			should(task).be.an.Object;
			should(task.unregister).be.a.Function;
			should(task.taskId).be.a.Number;
			task.unregister();
			finish();
		});

		// Skip on Windows 8.1
		(Ti.Platform.version.indexOf('8.1' == 0) ? it.skip : it)('registerPushNotificationTask', function (finish) {
			var task = Ti.App.Windows.BackgroundService.registerPushNotificationTask('TitaniumWindows_Ti.BackgroundServiceTask');
			should(task).be.an.Object;
			should(task.unregister).be.a.Function;
			should(task.taskId).be.a.Number;
			task.unregister();
			finish();
		});

		// Skip on Windows 8.1
		(Ti.Platform.version.indexOf('8.1' == 0) ? it.skip : it)('unregisterTask(task)', function (finish) {
			var task = Ti.App.Windows.BackgroundService.registerTimerTask('TitaniumWindows_Ti.BackgroundServiceTask', 15, true);
			should(task).be.an.Object;
			should(task.unregister).be.a.Function;
			should(task.taskId).be.a.Number;
			Ti.App.Windows.BackgroundService.unregisterTask(task);
			finish();
		});

		// Skip on Windows 8.1
		(Ti.Platform.version.indexOf('8.1' == 0) ? it.skip : it)('unregisterTask(task id)', function (finish) {
			var task = Ti.App.Windows.BackgroundService.registerTimerTask('TitaniumWindows_Ti.BackgroundServiceTask', 15, true);
			should(task).be.an.Object;
			should(task.unregister).be.a.Function;
			should(task.taskId).be.a.Number;
			Ti.App.Windows.BackgroundService.unregisterTask(task.taskId);
			finish();
		});

		// Skip on Windows 8.1
		(Ti.Platform.version.indexOf('8.1' == 0) ? it.skip : it)('unregisterAllTasks', function (finish) {
			var task = Ti.App.Windows.BackgroundService.registerTimerTask('TitaniumWindows_Ti.BackgroundServiceTask', 15, true);
			should(task).be.an.Object;
			should(task.unregister).be.a.Function;
			should(task.taskId).be.a.Number;
			Ti.App.Windows.BackgroundService.unregisterAllTasks();
			finish();
		});

	});
}
