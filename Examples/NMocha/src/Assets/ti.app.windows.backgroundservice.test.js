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

		it.skip('API', function () {
			should(Ti.App.Windows).be.an.Object;
			should(Ti.App.Windows.BackgroundService).be.an.Object;
			should(Ti.App.Windows.BackgroundService.registerTimerTask).be.a.Function;
			should(Ti.App.Windows.BackgroundService.unregisterAllTasks).be.a.Function;
		});

		it.skip('registerTimerTask', function () {
			var task = Ti.App.Windows.BackgroundService.registerTimerTask('TitaniumWindows_Ti.BackgroundServiceTask', 15, true);
			should(task).be.an.Object;
			should(task.unregister).be.a.Function;
			should(task.taskId).be.a.Number;
			task.unregister();
		});

		it.skip('registerPushNotificationTask', function () {
			var task = Ti.App.Windows.BackgroundService.registerPushNotificationTask('TitaniumWindows_Ti.BackgroundServiceTask');
			should(task).be.an.Object;
			should(task.unregister).be.a.Function;
			should(task.taskId).be.a.Number;
			task.unregister();
		});

		it.skip('unregisterTask(task)', function () {
			var task = Ti.App.Windows.BackgroundService.registerTimerTask('TitaniumWindows_Ti.BackgroundServiceTask', 15, true);
			should(task).be.an.Object;
			should(task.unregister).be.a.Function;
			should(task.taskId).be.a.Number;
			Ti.App.Windows.BackgroundService.unregisterTask(task);
		});

		it.skip('unregisterTask(task id)', function () {
			var task = Ti.App.Windows.BackgroundService.registerTimerTask('TitaniumWindows_Ti.BackgroundServiceTask', 15, true);
			should(task).be.an.Object;
			should(task.unregister).be.a.Function;
			should(task.taskId).be.a.Number;
			Ti.App.Windows.BackgroundService.unregisterTask(task.taskId);
		});

		it.skip('unregisterAllTasks', function () {
			var task = Ti.App.Windows.BackgroundService.registerTimerTask('TitaniumWindows_Ti.BackgroundServiceTask', 15, true);
			should(task).be.an.Object;
			should(task.unregister).be.a.Function;
			should(task.taskId).be.a.Number;
			Ti.App.Windows.BackgroundService.unregisterAllTasks();
		});

	});
}
