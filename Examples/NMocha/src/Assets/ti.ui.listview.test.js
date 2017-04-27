/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2015-2016 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

var should = require('./should'),
	utilities = require('./utilities/utilities');
	didFocus = false;

describe('Titanium.UI.ListView', function () {
	this.timeout(6e4);

	beforeEach(function() {
		didFocus = false;
	});

	it('Ti.UI.ListView', function (finish) {
		should(Ti.UI.ListView).not.be.undefined;
		finish();
	});

	it('apiName', function (finish) {
		should(Ti.UI.ListView.apiName).be.eql('Ti.UI.ListView');
		finish();
	});

	it('createListView', function (finish) {

		// Validate createListView()
		should(Ti.UI.createListView).not.be.undefined;
		should(Ti.UI.createListView).be.a.Function;

		// Create ListView
		var listView = Ti.UI.createListView();
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

	//
	// Making sure setting header & footer doesn't throw exception
	//
	it('section header & footer', function (finish) {
		var win = Ti.UI.createWindow({ backgroundColor: 'green' }),
			listView = Ti.UI.createListView(),
			ukHeaderView = Ti.UI.createView({ backgroundColor: 'black', height: 42 }),
			ukFooterView = Ti.UI.createView({ backgroundColor: 'black', height: 42 }),
			ukSection = Ti.UI.createListSection({ headerView: ukHeaderView, footerView: ukFooterView }),
			usSection = Ti.UI.createListSection({ headerTitle: 'English US Header', footerTitle: 'English US Footer' });

		ukHeaderView.add(Ti.UI.createLabel({ text: 'English UK Header', color: 'white' }));
		ukFooterView.add(Ti.UI.createLabel({ text: 'English UK Footer', color: 'white' }));
		ukSection.setItems([
			{ properties: { title: 'Lift', color: 'black' } },
			{ properties: { title: 'Lorry', color: 'black' } },
			{ properties: { title: 'Motorway', color: 'black' } }
		]);
		listView.appendSection(ukSection);

		usSection.setItems([
			{ properties: { title: 'Elevator', color: 'black' } },
			{ properties: { title: 'Truck', color: 'black' } },
			{ properties: { title: 'Freeway', color: 'black' } }
		]);
		listView.appendSection(usSection);

		win.addEventListener('open', function () {
			should(listView.sectionCount).be.eql(2);
			should(listView.sections[0].items.length).be.eql(3);
			should(listView.sections[0].items[0].properties.title).be.eql('Lift');
			should(listView.sections[0].items[1].properties.title).be.eql('Lorry');
			should(listView.sections[0].items[2].properties.title).be.eql('Motorway');
			should(listView.sections[1].items.length).be.eql(3);
			should(listView.sections[1].items[0].properties.title).be.eql('Elevator');
			should(listView.sections[1].items[1].properties.title).be.eql('Truck');
			should(listView.sections[1].items[2].properties.title).be.eql('Freeway');

			setTimeout(function () {
				win.close();
				finish();
			}, 1000);
		});

		win.add(listView);
		win.open();
	});

	//
	// Making sure setting header & footer doesn't mess up section items
	//
	it('headerView', function (finish) {
		var win = Ti.UI.createWindow({backgroundColor: 'green'});
		var listView = Ti.UI.createListView();
		var sections = [];

		var fruitSection = Ti.UI.createListSection({ headerTitle: 'Fruits'});
		var fruitDataSet = [
			{properties: { title: 'Apple'}},
			{properties: { title: 'Banana'}},
		];
		fruitSection.setItems(fruitDataSet);
		fruitSection.headerView = Ti.UI.createView({backgroundColor: 'black', height: 42});
		fruitSection.footerView = Ti.UI.createView({backgroundColor: 'black', height: 42});

		sections.push(fruitSection);

		var vegSection = Ti.UI.createListSection({ headerTitle: 'Vegetables'});
		var vegDataSet = [
			{properties: { title: 'Carrots'}},
			{properties: { title: 'Potatoes'}},
		];
		vegSection.setItems(vegDataSet);
		vegSection.headerView = Ti.UI.createView({backgroundColor: 'black', height: 42});
		vegSection.footerView = Ti.UI.createView({backgroundColor: 'black', height: 42});
		sections.push(vegSection);

		listView.sections = sections;

		win.addEventListener('open', function () {
			should(listView.sectionCount).be.eql(2);
			should(listView.sections[0].items.length).be.eql(2);
			should(listView.sections[0].items[0].properties.title).be.eql('Apple');
			should(listView.sections[0].items[1].properties.title).be.eql('Banana');
			should(listView.sections[1].items.length).be.eql(2);
			should(listView.sections[1].items[0].properties.title).be.eql('Carrots');
			should(listView.sections[1].items[1].properties.title).be.eql('Potatoes');

			setTimeout(function () {
				win.close();
				finish();
			}, 1000);
		});

		win.add(listView);
		win.open();
	});

	//
	// Making sure custom template doesn't throw exception
	//
	it('Custom template', function (finish) {
		var win = Ti.UI.createWindow({ backgroundColor: 'green' });
		var myTemplate = {
			childTemplates: [
				{
					type: 'Ti.UI.ImageView',
					bindId: 'pic',
					properties: {
						width: '50', height: '50', left: 0
					}
				},
				{
					type: 'Ti.UI.Label',
					bindId: 'info',
					properties: {
						color: 'black',
						font: { fontSize: '20', fontWeight: 'bold' },
						left: '60', top: 0,
					}
				},
				{
					type: 'Ti.UI.Label',
					bindId: 'es_info',
					properties: {
						color: 'gray',
						font: { fontSize: '14' },
						left: '60', top: '25',
					}
				}
			]
		};

		var listView = Ti.UI.createListView({
			templates: { 'template': myTemplate },
			defaultItemTemplate: 'template'
		});
		var sections = [];

		var fruitSection = Ti.UI.createListSection({ headerTitle: 'Fruits / Frutas' });
		var fruitDataSet = [
			{ info: { text: 'Apple' }, es_info: { text: 'Manzana' }, pic: { image: 'Logo.png' } },
			{ info: { text: 'Banana' }, es_info: { text: 'Banana' }, pic: { image: 'Logo.png' } }
		];
		fruitSection.setItems(fruitDataSet);
		sections.push(fruitSection);

		var vegSection = Ti.UI.createListSection({ headerTitle: 'Vegetables / Verduras' });
		var vegDataSet = [
			{ info: { text: 'Carrot' }, es_info: { text: 'Zanahoria' }, pic: { image: 'Logo.png' } },
			{ info: { text: 'Potato' }, es_info: { text: 'Patata' }, pic: { image: 'Logo.png' } }
		];
		vegSection.setItems(vegDataSet);
		sections.push(vegSection);

		var grainSection = Ti.UI.createListSection({ headerTitle: 'Grains / Granos' });
		var grainDataSet = [
			{ info: { text: 'Corn' }, es_info: { text: 'Maiz' }, pic: { image: 'Logo.png' } },
			{ info: { text: 'Rice' }, es_info: { text: 'Arroz' }, pic: { image: 'Logo.png' } }
		];
		grainSection.setItems(grainDataSet);
		sections.push(grainSection);

		listView.setSections(sections);

		win.addEventListener('open', function () {
			should(listView.sectionCount).be.eql(3);
			should(listView.sections[0].items.length).be.eql(2);
			should(listView.sections[0].items[0].info.text).be.eql('Apple');
			should(listView.sections[0].items[1].info.text).be.eql('Banana');
			should(listView.sections[1].items.length).be.eql(2);
			should(listView.sections[1].items[0].info.text).be.eql('Carrot');
			should(listView.sections[1].items[1].info.text).be.eql('Potato');
			should(listView.sections[2].items.length).be.eql(2);
			should(listView.sections[2].items[0].info.text).be.eql('Corn');
			should(listView.sections[2].items[1].info.text).be.eql('Rice');

			setTimeout(function () {
				win.close();
				finish();
			}, 1000);
		});

		win.add(listView);
		win.open();
	});

	it('appendSection', function (finish) {
		var win = Ti.UI.createWindow({backgroundColor: 'green'});
		var listView = Ti.UI.createListView();

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
		var listView = Ti.UI.createListView();

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
		var listView = Ti.UI.createListView();

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
		var listView = Ti.UI.createListView();

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
		    listView = Ti.UI.createListView({ sections: [section] }),
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
		for (var i in items) {
		    var item = items[i].properties.title;
		    should(item).be.eql(validation[i]);
		}

		finish();
	});

	it('fireListSectionEvent (header and footer)', function (finish) {
		var section = Ti.UI.createListSection({
				headerTitle: 'HEADER',
        		footerTitle: 'FOOTER',
		        items: [
		            { properties: { title: 'B' } },
		            { properties: { title: 'A' } },
		            { properties: { title: 'E' } },
		            { properties: { title: 'G' } }
		        ]
		    }),
		    listView = Ti.UI.createListView({ sections: [section] }),
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
		for (var i in items) {
		    var item = items[i].properties.title;
		    should(item).be.eql(validation[i]);
		}

		finish();
	});

	// Making sure sections data is saved even when it's filtered (TIMOB-24019)
	it('TIMOB-24019', function (finish) {
	    var win = Ti.UI.createWindow({ backgroundColor: 'green' });
	    var listView = Ti.UI.createListView({ width: Ti.UI.FILL, height: Ti.UI.FILL, caseInsensitiveSearch: true });

	    var fruitSection = Ti.UI.createListSection({ headerTitle: 'Fruits' });
	    var fruitDataSet = [
			{ properties: { title: 'Apple', searchableText: 'Apple' } },
			{ properties: { title: 'Banana', searchableText: 'Banana' } },
	    ];
	    fruitSection.setItems(fruitDataSet);

	    var vegSection = Ti.UI.createListSection({ headerTitle: 'Vegetables' });
	    var vegDataSet = [
			{ properties: { title: 'Carrots', searchableText: 'Carrots' } },
			{ properties: { title: 'Potatoes', searchableText: 'Potatoes' } },
	    ];
	    vegSection.setItems(vegDataSet);

	    listView.sections = [fruitSection, vegSection];

	    win.addEventListener('open', function () {
	        should(listView.sectionCount).be.eql(2);
	        should(listView.sections[0].items.length).be.eql(2);
	        should(listView.sections[0].items[0].properties.title).be.eql('Apple');
	        should(listView.sections[0].items[1].properties.title).be.eql('Banana');
	        should(listView.sections[1].items.length).be.eql(2);
	        should(listView.sections[1].items[0].properties.title).be.eql('Carrots');
	        should(listView.sections[1].items[1].properties.title).be.eql('Potatoes');

	        // This should show 'Apple' and 'Potatoes'
	        listView.searchText = 'p';

	        setTimeout(function () {
	            // Make sure ListView reserves original data
	            should(listView.sectionCount).be.eql(2);
	            should(listView.sections[0].items.length).be.eql(2);
	            should(listView.sections[0].items[0].properties.title).be.eql('Apple');
	            should(listView.sections[0].items[1].properties.title).be.eql('Banana');
	            should(listView.sections[1].items.length).be.eql(2);
	            should(listView.sections[1].items[0].properties.title).be.eql('Carrots');
	            should(listView.sections[1].items[1].properties.title).be.eql('Potatoes');

	            win.close();
	            finish();
	        }, 2000);
	    });

	    win.add(listView);
	    win.open();
	});


});
