/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2016 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */
var should = require('./should'),
	utilities = require('./utilities/utilities');

describe('Titanium.Network.Socket.TCP', function () {

    it('connect', function (finish) {
	    var socket = Ti.Network.Socket.createTCP({
	        host: 'www.appcelerator.com', port: 80,
	        connected: function (e) {
	            finish();
	        }
	    });
	    should(socket.connect).not.be.null;
	    should(socket.connect).be.a.Function;
	    socket.connect();
    });

    it('accept', function (finish) {
        var socket = Ti.Network.Socket.createTCP();
        should(socket.accept).not.be.null;
        should(socket.accept).be.a.Function;
        finish();
    });

    it('listen', function (finish) {
        var socket = Ti.Network.Socket.createTCP();
        should(socket.listen).not.be.null;
        should(socket.listen).be.a.Function;
        finish();
    });

    it('close', function (finish) {
        var socket = Ti.Network.Socket.createTCP();
        should(socket.close).not.be.null;
        should(socket.close).be.a.Function;
        finish();
    });

    it('send data', function (finish) {
	    var socket = Ti.Network.Socket.createTCP({
	        host: 'www.appcelerator.com', port: 80,
	        connected: function (e) {
	            should(socket.write).not.be.null;
	            should(socket.write).be.a.Function;
	            socket.write(Ti.createBuffer({value: 'GET / HTTP/1.1\r\nHost: www.appcelerator.com\r\nConnection: close\r\n\r\n'}));
	            finish();
	        }
	    });
	    should(socket.connect).not.be.null;
	    should(socket.connect).be.a.Function;
	    socket.connect();
	});

    it('receive data', function (finish) {
	    var socket = Ti.Network.Socket.createTCP({
	        host: 'pastebin.com', port: 80,
	        connected: function (e) {

	            // receive callback
	            should(socket.read).not.be.null;
	            should(socket.read).be.a.Function;
	            Ti.Stream.pump(e.socket, function (e) {
	                if (e.buffer.toString().indexOf('SUCCESS!') > 0) {
	                    finish();
	                }
	            }, 1024, true);

                // send GET request
	            should(socket.write).not.be.null;
	            should(socket.write).be.a.Function;
	            socket.write(Ti.createBuffer({ value: 'GET /raw/eF5dK0xU HTTP/1.1\r\nHost: pastebin.com\r\nConnection: close\r\n\r\n' }));
	        }
	    });
	    should(socket.connect).not.be.null;
	    should(socket.connect).be.a.Function;
	    socket.connect();
	});
});
