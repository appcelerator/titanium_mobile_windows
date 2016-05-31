/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2011-2016 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

var should = require('./should'),
	utilities = require('./utilities/utilities');

describe('Titanium.Buffer', function() {
	it('apiName', function (finish) {
		should(Ti.Buffer.apiName).be.eql('Ti.Buffer');
		finish();
	});

	it('testAPI', function(finish) {
		should(Ti.createBuffer).be.a.Function;
		var buffer = Ti.createBuffer();
		should(buffer).be.an.Object;
		should(buffer.length).eql(0);
		var functions = [ 'append', 'insert', 'copy', 'clone', 'fill', 'clear', 'release', 'toString', 'toBlob' ];
		for (var i = 0; i < functions.length; i++) {
			should(buffer[functions[i]]).be.a.Function;
		}
		finish();
	});

	it('length', function(finish) {
		var buffer = Ti.createBuffer();
		should(buffer.length).eql(0);
		buffer = Ti.createBuffer({
			length: 100
		});
		should(buffer.length).eql(100);
		for (var i = 0; 100 > i; i++) should(buffer[i]).eql(0);
		finish();
	});

	it('append()', function(finish) {
		var buffer1 = Ti.createBuffer({
			length: 20
		});
		var buffer2 = Ti.createBuffer({
			length: 5
		});
		buffer2[0] = 100;
		buffer2[1] = 101;
		var n = buffer1.append(buffer2);
		should(buffer1.length).eql(25);
		should(buffer1[20]).eql(100);
		should(buffer1[21]).eql(101);
		should(n).eql(buffer2.length);
		buffer1 = Ti.createBuffer({
			length: 20
		});
		buffer2 = Ti.createBuffer({
			length: 5
		});
		buffer2[3] = 100;
		buffer2[4] = 101;
		n = buffer1.append(buffer2, 3, 2);
		should(buffer1.length).eql(22);
		should(buffer1[20]).eql(100);
		should(buffer1[21]).eql(101);
		should(n).eql(2);
		should(function() {
			// requires at least 1 arg
			buffer1.append();
		}).throw();
		should(function() {
			// 99 > buffer2.length
			buffer1.append(buffer2, 0, 99);
		}).throw();
		should(function() {
			// 99 position / 100 length > buffer2.length
			buffer1.append(buffer2, 99, 100);
		}).throw();
		finish();
	});

	it('insert()', function(finish) {
		var buffer1 = Ti.createBuffer({
			length: 20
		});
		var buffer2 = Ti.createBuffer({
			length: 5
		});
		buffer2[0] = 103;
		buffer2[1] = 104;
		var n = buffer1.insert(buffer2, 3);
		should(buffer1.length).eql(25);
		should(buffer1[3]).eql(103);
		should(buffer1[4]).eql(104);
		should(n).eql(5);
		buffer2[2] = 105;
		n = buffer1.insert(buffer2, 3, 1, 2);
		should(buffer1.length).eql(27);
		should(buffer1[3]).eql(104);
		should(buffer1[4]).eql(105);
		should(buffer1[5]).eql(103);
		should(buffer1[6]).eql(104);
		should(n).eql(2);
		should(function() {
			// insert requires at least 2 args
			buffer1.insert(buffer2);
		}).throw();
		should(function() {
			// 99 > buffer2.length
			buffer1.insert(buffer2, 0, 0, 99);
		}).throw();
		should(function() {
			// 99 position > buffer1.length
			buffer1.insert(buffer2, 99);
		}).throw();
		should(function() {
			// 99 position / 100 length > buffer2.length
			buffer1.insert(buffer2, 0, 99, 100);
		}).throw();
		finish();
	});

	it('insert() blogExample', function(finish) {
		var buffer = Ti.createBuffer({
			length: 2
		});
		buffer[0] = 1;
		buffer[1] = 3;
		var buffer2 = Ti.createBuffer({
			length: 1
		});
		buffer2[0] = 2;
		buffer.insert(buffer2, 1);
		should(String(buffer[0]) + String(buffer[1]) + String(buffer[2])).eql('123');
		should(buffer.length).eql(3);
		should(buffer[0]).eql(1);
		should(buffer[1]).eql(2);
		should(buffer[2]).eql(3);
		should(buffer2.length).eql(1);
		//unchanged
		should(buffer2[0]).eql(2);
		finish();
	});

	it('copy()', function(finish) {
		var buffer1 = Ti.createBuffer({
			length: 20
		});
		var buffer2 = Ti.createBuffer({
			length: 5
		});
		buffer2[0] = 109;
		buffer2[1] = 110;
		var n = buffer1.copy(buffer2, 0);
		should(buffer1.length).eql(20);
		should(buffer1[0]).eql(109);
		should(buffer1[1]).eql(110);
		should(n).eql(5);
		n = buffer1.copy(buffer2, 15, 0, 2);
		should(buffer1.length).eql(20);
		should(buffer1[15]).eql(109);
		should(buffer1[16]).eql(110);
		should(n).eql(2);
		should(function() {
			// copy requires at least 1 arg
			buffer1.copy();
		}).throw();
		should(function() {
			// 99 > buffer2.length
			buffer1.copy(buffer2, 0, 99);
		}).throw();
		should(function() {
			// 99 position / 100 length > buffer2.length
			buffer1.copy(buffer2, 99, 100);
		}).throw();
		finish();
	});

	it('clone', function(finish) {
		var buffer1 = Ti.createBuffer({ length: 20 });
		buffer1[0] = 100;
		buffer1[6] = 103;
		buffer1[12] = 106;
		buffer1[18] = 109;

		var buffer2 = buffer1.clone();
		should(buffer2.length).eql(20);
		should(buffer2).not.equal(buffer1);
		should(buffer2).eql(buffer1);

		buffer2 = buffer1.clone(6, 13);
		should(buffer2.length).eql(13);
		should(buffer2[0]).eql(103);
		should(buffer2[6]).eql(106);
		should(buffer2[12]).eql(109);

		should(function() {
			// 99 > buffer1.length
			buffer1.clone(0, 99);
		}).throw();

		should(function() {
			// 99 position / 100 length > buffer1.length
			buffer1.clone(99, 100);
		}).throw();

		finish();
	});

	it('fill()', function(finish) {
		var buffer = Ti.createBuffer({
			length: 20
		});
		buffer.fill(100);
		for (var i = 0; 20 > i; i++) should(buffer[i]).eql(100);
		buffer.fill(101, 5, 10);
		should(buffer[0]).eql(100);
		for (var i = 5; 10 > i; i++) should(buffer[i]).eql(101);
		should(function() {
			// fill requires at least 1 arg
			buffer.fill();
		}).throw();
		should(function() {
			// 99 > buffer.length
			buffer.fill(102, 0, 99);
		}).throw();
		should(function() {
			// 99 position / 100 length > buffer1.length
			buffer.fill(100, 99, 100);
		}).throw();
		finish();
	});

	it('clear()', function(finish) {
		var buffer = Ti.createBuffer({
			length: 100
		});
		buffer.fill(99);
		buffer.clear();
		should(buffer.length).eql(100);
		for (var i = 0; 100 > i; i++) should(buffer[i]).eql(0);
		finish();
	});

	it('release()', function(finish) {
		var buffer = Ti.createBuffer({
			length: 100
		});
		buffer.release();
		should(buffer.length).eql(0);
		finish();
	});

	it('toString() and toBlob()', function(finish) {
		this.timeout(2000);
		this.slow(1000);
		// just a simple ascii string
		var buffer = Ti.createBuffer({
			length: 12
		});
		buffer[0] = 97;
		// a
		buffer[1] = 112;
		// p
		buffer[2] = 112;
		// p
		buffer[3] = 99;
		// c
		buffer[4] = 101;
		// e
		buffer[5] = 108;
		// l
		buffer[6] = 101;
		// e
		buffer[7] = 114;
		// r
		buffer[8] = 97;
		// a
		buffer[9] = 116;
		// t
		buffer[10] = 111;
		// o
		buffer[11] = 114;
		// r
		should(buffer.toString()).eql('appcelerator');
		var blob = buffer.toBlob();
		should(blob.length).eql(buffer.length);
		should(blob.text).eql('appcelerator');
		finish();
	});

	it('defaults to UTF-8', function(finish) {
		this.timeout(2000);
		this.slow(1000);
		// default UTF8
		var buffer = Ti.createBuffer({
			value: 'appcelerator'
		});
		should(buffer.length).eql(12);
		should(buffer[0]).eql(97);
		// a
		should(buffer[1]).eql(112);
		// p
		should(buffer[2]).eql(112);
		// p
		should(buffer[3]).eql(99);
		// c
		should(buffer[4]).eql(101);
		// e
		should(buffer[5]).eql(108);
		// l
		should(buffer[6]).eql(101);
		// e
		should(buffer[7]).eql(114);
		// r
		should(buffer[8]).eql(97);
		// a
		should(buffer[9]).eql(116);
		// t
		should(buffer[10]).eql(111);
		// o
		should(buffer[11]).eql(114);
		// r
		finish();
	});

	it('encode with UTF-16', function(finish) {
		this.timeout(2000);
		this.slow(1000);
		// UTF-16
		var buffer = Ti.createBuffer({
			value: 'appcelerator',
			type: Ti.Codec.CHARSET_UTF16
		});
		var length = 24;
		var start = 0;
		// some impls will add a UTF-16 BOM
		// http://en.wikipedia.org/wiki/UTF-16/UCS-2#Byte_order_encoding_schemes
		if (255 == buffer[0] && 254 == buffer[1]) {
			// UTF-16 BE
			length = 26;
			start = 1;
		} else if (254 == buffer[0] && 255 == buffer[1]) {
			// UTF-16 LE
			length = 26;
			start = 2;
		}
		should(buffer.length).eql(length);
		should(buffer.byteOrder).eql(Ti.Codec.getNativeByteOrder());
		should(buffer[start + 1]).eql(97);
		// a
		should(buffer[start + 3]).eql(112);
		// p
		should(buffer[start + 5]).eql(112);
		// p
		should(buffer[start + 7]).eql(99);
		// c
		should(buffer[start + 9]).eql(101);
		// e
		should(buffer[start + 11]).eql(108);
		// l
		should(buffer[start + 13]).eql(101);
		// e
		should(buffer[start + 15]).eql(114);
		// r
		should(buffer[start + 17]).eql(97);
		// a
		should(buffer[start + 19]).eql(116);
		// t
		should(buffer[start + 21]).eql(111);
		// o
		should(buffer[start + 23]).eql(114);
		// r
		finish();
	});

	it('testAutoEncodeBigEndian', function (finish) {
		this.timeout(2000);
		this.slow(1000);
		// 8 Byte long in Big Endian (most significant byte first)
		var buffer = Ti.createBuffer({
			value: 305419896,
			type: Ti.Codec.TYPE_LONG,
			byteOrder: Ti.Codec.BIG_ENDIAN
		});
		should(buffer.byteOrder).eql(Ti.Codec.BIG_ENDIAN);
		should(buffer.length).eql(8);
		for (var i = 0; 4 > i; i++) should(buffer[i]).eql(0);
		should(buffer[4]).eql(18);
		should(buffer[5]).eql(52);
		should(buffer[6]).eql(86);
		should(buffer[7]).eql(120);
		finish();
	});

	it('testAutoEncodeLittleEndian', function (finish) {
		this.timeout(2000);
		this.slow(1000);
		// 4 byte int in Little Endian (least significant byte first)
		var buffer = Ti.createBuffer({
			value: 305419896,
			type: Ti.Codec.TYPE_INT,
			byteOrder: Ti.Codec.LITTLE_ENDIAN
		});
		should(buffer.byteOrder).eql(Ti.Codec.LITTLE_ENDIAN);
		should(buffer[0]).eql(120);
		should(buffer[1]).eql(86);
		should(buffer[2]).eql(52);
		should(buffer[3]).eql(18);
		finish();
	});
});
