/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2015-2016 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

var should = require('./should'),
	utilities = require('./utilities/utilities');

describe('Titanium.UI.Windows.ListView', function () {
	this.timeout(6e4);

	it('Ti.UI.Windows.ListView', function (finish) {
		should(Ti.UI.Windows.ListView).not.be.undefined;
		finish();
	});

	it('createListView', function (finish) {

		// Validate createListView()
		should(Ti.UI.Windows.createListView).not.be.undefined;
		should(Ti.UI.Windows.createListView).be.a.Function;

		// Create ListView
		var listView = Ti.UI.Windows.createListView();
		should(listView).be.a.Object;

		// Create list section
		var section_0 = Ti.UI.createListSection({ headerTitle: 'Zero'});
		should(section_0).be.a.Object;

		// Set section items
		var section_0_set = [
			{properties: { title: 'Red'}},
			{properties: { title: 'White'}}
		];
		section_0.setItems(section_0_set);
		should(section_0.items.length).be.eql(2);

		// Append item to section
		section_0.appendItems([{properties: { title: 'Purple'}}]);

		// Validate section items length
		should(section_0.items.length).be.eql(3);

		// Create list section
		var section_1 = Ti.UI.createListSection({ headerTitle: 'One'});
		should(section_1).be.a.Object;

		// Set section items
		var section_1_set = [
			{properties: { title: 'Green'}},
			{properties: { title: 'Yellow'}},
			{properties: { title: 'Blue'}}
		];
		section_1.setItems(section_1_set);
		should(section_1.items.length).be.eql(3);

		// Set listView sections
		listView.sections = [section_0];

		// Validate listView section count
		should(listView.sectionCount).be.eql(1);

		// Apend section to listView
		listView.appendSection([section_1]);

		// Validate listView section count
		should(listView.sectionCount).be.eql(2);

		finish();
	});

	it('appendSection', function (finish) {
		var win = Ti.UI.createWindow({backgroundColor: 'green'});
		var listView = Ti.UI.Windows.createListView();

		var fruitSection = Ti.UI.createListSection({ headerTitle: 'Fruits'});
		var fruitDataSet = [
			{properties: { title: 'Apple'}},
			{properties: { title: 'Banana'}},
		];
		fruitSection.setItems(fruitDataSet);

		var vegSection = Ti.UI.createListSection({ headerTitle: 'Vegetables'});
		var vegDataSet = [
			{properties: { title: 'Carrots'}},
			{properties: { title: 'Potatoes'}},
		];
		vegSection.setItems(vegDataSet);

		var fishSection = Ti.UI.createListSection({ headerTitle: 'Fish'});
		var fishDataSet = [
			{properties: { title: 'Cod'}},
			{properties: { title: 'Haddock'}},
		];
		fishSection.setItems(fishDataSet);

		listView.sections = [ fruitSection ];

		win.addEventListener('open', function () {
			should(listView.sectionCount).be.eql(1);
			should(listView.sections[0].items.length).be.eql(2);
			should(listView.sections[0].items[0].properties.title).be.eql('Apple');
			should(listView.sections[0].items[1].properties.title).be.eql('Banana');

			listView.appendSection(vegSection);

			should(listView.sectionCount).be.eql(2);
			should(listView.sections[1].items.length).be.eql(2);
			should(listView.sections[1].items[0].properties.title).be.eql('Carrots');
			should(listView.sections[1].items[1].properties.title).be.eql('Potatoes');

			// appenSection with an array
			listView.appendSection([ fishSection ]);
			should(listView.sectionCount).be.eql(3);
			should(listView.sections[2].items.length).be.eql(2);
			should(listView.sections[2].items[0].properties.title).be.eql('Cod');
			should(listView.sections[2].items[1].properties.title).be.eql('Haddock');

			setTimeout(function () {
				win.close();
				finish();
			}, 1000);
		});

		win.add(listView);
		win.open();
	});

	it('insertSectionAt', function (finish) {
		var win = Ti.UI.createWindow({ backgroundColor: 'green' });
		var listView = Ti.UI.Windows.createListView();

		var fruitSection = Ti.UI.createListSection({ headerTitle: 'Fruits' });
		var fruitDataSet = [
			{ properties: { title: 'Apple' } },
			{ properties: { title: 'Banana' } },
		];
		fruitSection.setItems(fruitDataSet);

		var vegSection = Ti.UI.createListSection({ headerTitle: 'Vegetables' });
		var vegDataSet = [
			{ properties: { title: 'Carrots' } },
			{ properties: { title: 'Potatoes' } },
		];
		vegSection.setItems(vegDataSet);

		var fishSection = Ti.UI.createListSection({ headerTitle: 'Fish' });
		var fishDataSet = [
			{ properties: { title: 'Cod' } },
			{ properties: { title: 'Haddock' } },
		];
		fishSection.setItems(fishDataSet);

		listView.sections = [ fruitSection, fishSection ];

		win.addEventListener('open', function () {
			should(listView.sectionCount).be.eql(2);
			should(listView.sections[0].items.length).be.eql(2);
			should(listView.sections[0].items[0].properties.title).be.eql('Apple');
			should(listView.sections[0].items[1].properties.title).be.eql('Banana');

			listView.insertSectionAt(0, vegSection);

			should(listView.sectionCount).be.eql(3);
			should(listView.sections[0].items.length).be.eql(2);
			should(listView.sections[0].items[0].properties.title).be.eql('Carrots');
			should(listView.sections[0].items[1].properties.title).be.eql('Potatoes');
			should(listView.sections[1].items.length).be.eql(2);
			should(listView.sections[1].items[0].properties.title).be.eql('Apple');
			should(listView.sections[1].items[1].properties.title).be.eql('Banana');

			setTimeout(function () {
				win.close();
				finish();
			}, 1000);
		});

		win.add(listView);
		win.open();
	});

	it('replaceSectionAt', function (finish) {
		var win = Ti.UI.createWindow({backgroundColor: 'green'});
		var listView = Ti.UI.Windows.createListView();

		var fruitSection = Ti.UI.createListSection({ headerTitle: 'Fruits'});
		var fruitDataSet = [
			{properties: { title: 'Apple'}},
			{properties: { title: 'Banana'}},
		];
		fruitSection.setItems(fruitDataSet);

		var vegSection = Ti.UI.createListSection({ headerTitle: 'Vegetables'});
		var vegDataSet = [
			{properties: { title: 'Carrots'}},
			{properties: { title: 'Potatoes'}},
		];
		vegSection.setItems(vegDataSet);

		var fishSection = Ti.UI.createListSection({ headerTitle: 'Fish'});
		var fishDataSet = [
			{properties: { title: 'Cod'}},
			{properties: { title: 'Haddock'}},
		];
		fishSection.setItems(fishDataSet);

		listView.sections = [ fruitSection, vegSection ];

		win.addEventListener('open', function () {
			should(listView.sectionCount).be.eql(2);
			should(listView.sections[0].items.length).be.eql(2);
			should(listView.sections[0].items[0].properties.title).be.eql('Apple');
			should(listView.sections[0].items[1].properties.title).be.eql('Banana');
			should(listView.sections[1].items.length).be.eql(2);
			should(listView.sections[1].items[0].properties.title).be.eql('Carrots');
			should(listView.sections[1].items[1].properties.title).be.eql('Potatoes');

			listView.replaceSectionAt(1, fishSection);

			should(listView.sectionCount).be.eql(2);
			should(listView.sections[0].items.length).be.eql(2);
			should(listView.sections[0].items[0].properties.title).be.eql('Apple');
			should(listView.sections[0].items[1].properties.title).be.eql('Banana');
			should(listView.sections[1].items.length).be.eql(2);
			should(listView.sections[1].items[0].properties.title).be.eql('Cod');
			should(listView.sections[1].items[1].properties.title).be.eql('Haddock');

			setTimeout(function () {
				win.close();
				finish();
			}, 1000);
		});

		win.add(listView);
		win.open();
	});

	it('deleteSectionAt', function (finish) {
		var win = Ti.UI.createWindow({backgroundColor: 'green'});
		var listView = Ti.UI.Windows.createListView();

		var fruitSection = Ti.UI.createListSection({ headerTitle: 'Fruits'});
		var fruitDataSet = [
			{properties: { title: 'Apple'}},
			{properties: { title: 'Banana'}},
		];
		fruitSection.setItems(fruitDataSet);

		var vegSection = Ti.UI.createListSection({ headerTitle: 'Vegetables'});
		var vegDataSet = [
			{properties: { title: 'Carrots'}},
			{properties: { title: 'Potatoes'}},
		];
		vegSection.setItems(vegDataSet);

		var fishSection = Ti.UI.createListSection({ headerTitle: 'Fish'});
		var fishDataSet = [
			{properties: { title: 'Cod'}},
			{properties: { title: 'Haddock'}},
		];
		fishSection.setItems(fishDataSet);

		listView.sections = [ fruitSection, vegSection, fishSection ];

		win.addEventListener('open', function () {
			should(listView.sectionCount).be.eql(3);
			should(listView.sections[0].items.length).be.eql(2);
			should(listView.sections[0].items[0].properties.title).be.eql('Apple');
			should(listView.sections[0].items[1].properties.title).be.eql('Banana');
			should(listView.sections[1].items.length).be.eql(2);
			should(listView.sections[1].items[0].properties.title).be.eql('Carrots');
			should(listView.sections[1].items[1].properties.title).be.eql('Potatoes');
			should(listView.sections[2].items.length).be.eql(2);
			should(listView.sections[2].items[0].properties.title).be.eql('Cod');
			should(listView.sections[2].items[1].properties.title).be.eql('Haddock');

			listView.deleteSectionAt(1);

			should(listView.sectionCount).be.eql(2);
			should(listView.sections[0].items.length).be.eql(2);
			should(listView.sections[0].items[0].properties.title).be.eql('Apple');
			should(listView.sections[0].items[1].properties.title).be.eql('Banana');
			should(listView.sections[1].items.length).be.eql(2);
			should(listView.sections[1].items[0].properties.title).be.eql('Cod');
			should(listView.sections[1].items[1].properties.title).be.eql('Haddock');

			setTimeout(function () {
				win.close();
				finish();
			}, 1000);
		});

		win.add(listView);
		win.open();
	});

	it('fireListSectionEvent', function (finish) {
		var section = Ti.UI.createListSection({
		        items: [
		            { properties: { title: 'B' } },
		            { properties: { title: 'A' } },
		            { properties: { title: 'E' } },
		            { properties: { title: 'G' } }
		        ]
		    }),
		    listView = Ti.UI.Windows.createListView({ sections: [section] }),
		    items_a = [
		        { properties: { title: 'A' } },
		    ],
		    items_b = [
		        { properties: { title: 'C' } },
		        { properties: { title: 'D' } }
		    ],
		    items_c = [
		        { properties: { title: 'E' } },
		        { properties: { title: 'F' } },
		    ],
		    validation = ['A', 'B', 'C', 'D', 'E', 'F'];

		section.updateItemAt(0, { properties: { title: 'A' } });
		section.updateItemAt(1, { properties: { title: 'B' } });
		section.updateItemAt(3, { properties: { title: 'F' } });
		section.insertItemsAt(2, items_b);
		section.deleteItemsAt(0, 1);
		section.deleteItemsAt(3, 2);
		section.appendItems(items_c);
		section.insertItemsAt(0, items_a);

		var items = section.getItems();
		should(items.length).be.eql(6);
		for (var i = 0; i < items.length; i++) {
		    var item = items[i].properties.title;
		    should(item).be.eql(validation[i]);
		}

		finish();
	});

});
