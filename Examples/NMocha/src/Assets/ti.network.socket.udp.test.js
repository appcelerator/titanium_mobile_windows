/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2017 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */
var should = require('./should'),
	utilities = require('./utilities/utilities');

describe('Titanium.Network.Socket.UDP', function () {

    it('start', function (finish) {
        this.timeout(6e4);
        var socket = Ti.Network.Socket.createUDP({
            started: function (e) {
                should(e.address).not.be.null;
                should(e.port).not.be.null;
                setTimeout(function () {
                    socket.stop();
                    finish();
                }, 1000);
            },
            error: function (e) {
                should(true).not.be.true;
            }
        });
	    should(socket.start).not.be.null;
	    should(socket.start).be.a.Function;
	    socket.start(43210);
    });

    it('sendString', function (finish) {
        this.timeout(6e4);
        var socket = Ti.Network.Socket.createUDP({
            started: function (e) {
                should(e.address).not.be.null;
                should(e.port).not.be.null;
                setTimeout(function () {
                    socket.sendString(e.port, e.address, "Hello, World!");
                }, 1000);
            },
            data: function(e) {
                should(e.address).not.be.null;
                should(e.port).not.be.null;
                should(e.stringData).not.be.null;
                should(e.bytesData).not.be.null;
                setTimeout(function () {
                    socket.stop();
                    finish();
                }, 1000);
            },
            error: function (e) {
                should(true).not.be.true;
            }
        });
        should(socket.sendString).not.be.null;
        should(socket.sendString).be.a.Function;
        socket.start(43211);
    });

    it('sendBytes', function (finish) {
        this.timeout(6e4);
        var socket = Ti.Network.Socket.createUDP({
            started: function (e) {
                should(e.address).not.be.null;
                should(e.port).not.be.null;
                setTimeout(function () {
                    socket.sendBytes(e.port, e.address, [73, 116, 32, 119, 111, 114, 107, 115, 33]);
                }, 1000);
            },
            data: function (e) {
                should(e.address).not.be.null;
                should(e.port).not.be.null;
                should(e.stringData).not.be.null;
                should(e.bytesData).not.be.null;
                setTimeout(function () {
                    socket.stop();
                    finish();
                }, 1000);
            },
            error: function (e) {
                should(true).not.be.true;
            }
        });
        should(socket.sendBytes).not.be.null;
        should(socket.sendBytes).be.a.Function;
        socket.start(43212);
    });

});
