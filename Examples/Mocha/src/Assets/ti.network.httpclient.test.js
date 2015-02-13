/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2011-2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */
var should = require('./should');

describe("httpclient", function () {
    it("apiTest", function (finish) {
        should(Ti.Network.createHTTPClient).not.be.null;
        finish();
    });

    // Test for TIMOB-4513
    it.skip("secureValidateProperty", function (finish) {
        var xhr = Ti.Network.createHTTPClient();
        should(xhr).be.an.Object;

        should(xhr.validatesSecureCertificate).be.undefined;
        xhr.validatesSecureCertificate = true;
        should(xhr.validatesSecureCertificate).be.true;
        xhr.validatesSecureCertificate = false;
        should(xhr.validatesSecureCertificate).be.false;

        xhr.setValidatesSecureCertificate(true);
        should(xhr.getValidatesSecureCertificate()).be.true;
        xhr.setValidatesSecureCertificate(false);
        should(xhr.getValidatesSecureCertificate()).be.false;

        finish();
    });

    it("downloadLargeFile", function (finish) {
        this.timeout(6e4);

        var xhr = Ti.Network.createHTTPClient();
        xhr.setTimeout(6e4);

        xhr.onload = function (e) {
          //  should(xhr.responseData.length).be.greaterThan(0);
            finish();
        };
        xhr.onerror = function (e) {
            Ti.API.debug(e);
            finish(new Error('failed to retrieve large image: ' + e));
        };

        xhr.open("GET", "http://www.ambientreality.com/ingot/moon%20background.png");
        xhr.send();
    });

    // https://appcelerator.lighthouseapp.com/projects/32238/tickets/2156-android-invalid-redirect-alert-on-xhr-file-download
    // https://appcelerator.lighthouseapp.com/projects/32238/tickets/1381-android-buffer-large-xhr-downloads
    it("largeFileWithRedirect", function (finish) {
        this.timeout(6e4);

        var xhr = Ti.Network.createHTTPClient();
        xhr.setTimeout(6e4);

        xhr.onload = function (e) {
            //should(xhr.responseData.length).be.greaterThan(0);
            finish();
        };
        xhr.onerror = function (e) {
            Ti.API.debug(e);
            finish(new Error('failed to retrieve redirected large image: ' + e));
        };

        xhr.open("GET", "http://www.ambientreality.com/ingot/moon.php");
        xhr.send();
    });

    // https://appcelerator.lighthouseapp.com/projects/32238-titanium-mobile/tickets/1649-android-httpclientsend-with-no-argument-causes-npe
    it.skip("emptyPOSTSend", function (finish) {
        this.timeout(3e4);
        var xhr = Ti.Network.createHTTPClient();
        xhr.setTimeout(3e4);
        xhr.onload = function (e) {
            finish();
        };
        xhr.onerror = function (e) {
            Ti.API.debug(e);
            finish(new Error('failed to post empty request: ' + e));
        };
        xhr.open("POST", "http://www.ambientreality.com/ingot/post_test.php");
        xhr.send();
    });

    //https://appcelerator.lighthouseapp.com/projects/32238/tickets/2339
    it.skip("responseHeadersBug", function (finish) {
        this.timeout(3e4);
        var xhr = Ti.Network.createHTTPClient();
        xhr.setTimeout(3e4);
        xhr.onload = function (e) {
            var allHeaders = xhr.getAllResponseHeaders();
            should(allHeaders.indexOf("Server:")).be.within(0, 1 / 0);
            var header = xhr.getResponseHeader("Server");
            should(header.length).be.greaterThan(0);
            finish();
        };
        xhr.onerror = function (e) {
            Ti.API.debug(e);
            finish(new Error('failed to retrieve headers: ' + e));
        };
        xhr.open("GET", "http://www.appcelerator.com");
        xhr.send();
    });

    it.skip("requestHeaderMethods", function (finish) {
        this.timeout(3e4);
        var xhr = Ti.Network.createHTTPClient();
        xhr.setTimeout(3e4);
        xhr.onload = function (e) {
            //TODO: set up a server that parrots back the request headers so
            //that we can verfiy what we actually send.
            finish();
        };
        xhr.onerror = function (e) {
            should(e).should.be.type('undefined');
        };
        xhr.open("GET", "http://www.appcelerator.com");
        xhr.setRequestHeader("adhocHeader", "notcleared");
        xhr.setRequestHeader("clearedHeader", "notcleared");
        should(function () {
            xhr.setRequestHeader("clearedHeader", null);
        }).not.throw();
        xhr.send();
    });

    // Confirms that only the selected cookie is deleted
    it.skip("clearCookiePositiveTest", function (finish) {
        this.timeout(3e4);
        var timer = 0;
        var second_cookie_fn = function (e) {
            var second_cookie_string = this.getResponseHeader("Set-Cookie").split.skip(";")[0];
            clearTimeout(timer);
            // New Cookie should be different.
            should(cookie_string).not.be.eql(second_cookie_string);
            finish();
        };
        var xhr = Ti.Network.createHTTPClient();
        var done = false;
        var cookie_string;
        xhr.setTimeout(3e4);
        xhr.onload = function (e) {
            cookie_string = this.getResponseHeader("Set-Cookie").split.skip(";")[0];
            xhr.clearCookies("https://my.appcelerator.com");
            xhr.onload = second_cookie_fn;
            xhr.open("GET", "https://my.appcelerator.com/auth/login");
            xhr.send();
        };
        xhr.onerror = function (e) {
            clearTimeout(timer);
            should(e).should.be.type('undefined');
        };
        xhr.open("GET", "https://my.appcelerator.com/auth/login");
        xhr.send();
    });

    // Confirms that only the selected cookie is deleted
    it.skip("clearCookieUnaffectedCheck", function (finish) {
        this.timeout(3e4);
        var timer = 0;
        var second_cookie_fn = function (e) {
            Ti.API.info("Second Load");
            var second_cookie_string = this.getResponseHeader("Set-Cookie").split.skip(";")[0];
            clearTimeout(timer);
            // Cookie should be the same
            should(cookie_string).eql(second_cookie_string);
            finish();
        };
        var xhr = Ti.Network.createHTTPClient();
        var done = false;
        var cookie_string;
        xhr.setTimeout(3e4);
        xhr.onload = function (e) {
            cookie_string = this.getResponseHeader("Set-Cookie").split.skip(";")[0];
            xhr.clearCookies("http://www.microsoft.com");
            xhr.onload = second_cookie_fn;
            xhr.open("GET", "https://my.appcelerator.com/auth/login");
            xhr.send();
        };
        xhr.onerror = function (e) {
            clearTimeout(timer);
            should(e).should.be.type('undefined');
        };
        xhr.open("GET", "https://my.appcelerator.com/auth/login");
        xhr.send();
    });

    // https://jira.appcelerator.org/browse/TIMOB-2849
    it.skip("setCookieClearCookieWithMultipleHTTPClients", function (finish) {
        this.timeout(3e4);
        var testServer = "http://www.ambientreality.com/ingot/cookie_test.php";
        var xhr = Ti.Network.createHTTPClient();
        xhr.setTimeout(3e4);
        xhr.onload = function (e) {
            should(this.responseText).eql("Set 2 cookies");
            var xhr2 = Ti.Network.createHTTPClient();
            xhr2.setTimeout(3e4);
            xhr2.onload = function (e) {
                Ti.API.info("Clear Cookie");
                should(this.responseText).eql("Set 2 cookies to expire a year ago.");
                finish();
            };
            xhr2.open("GET", testServer + "?count=2&clear=true");
            xhr2.send();
        };
        xhr.open("GET", testServer + "?count=2&clear=false");
        xhr.send();
    });

    // https://jira.appcelerator.org/browse/TIMOB-11751
    // https://jira.appcelerator.org/browse/TIMOB-17403
    it.skip("callbackTestForGETMethod", function (finish) {
        this.timeout(30000);

        var xhr = Ti.Network.createHTTPClient();
        xhr.setTimeout(30000);

        var dataStreamFinished = false;

        xhr.onreadystatechange = function (e) {
            if (this.readyState == this.DONE) {
                if (dataStreamFinished) {
                    finish();
                } else {
                    finish(new Error('onreadystatechange done fired before 100% progress'));
                }
            }
        };

        xhr.ondatastream = function (e) {
            should(e.progress).be.ok;
            if (e.progress >= 1) dataStreamFinished = true;
        };

        xhr.onerror = function (e) {
            should(e).should.be.type('undefined');
        };

        xhr.open("GET", "http://www.appcelerator.com/assets/The_iPad_App_Wave.pdf");
        xhr.send();
    });

    it.skip("callbackTestForPOSTMethod", function (finish) {
        this.timeout(3e4);
        var xhr = Ti.Network.createHTTPClient();
        xhr.setTimeout(3e4);
        var sendStreamFinished = false;
        xhr.onreadystatechange = function (e) {
            if (this.readyState == this.DONE && sendStreamFinished) finish();
        };
        xhr.onsendstream = function (e) {
            should(e.progress).be.ok;
            if (e.progress >= .99) sendStreamFinished = true;
        };
        xhr.onerror = function (e) {
            should(e).should.be.type('undefined');
        };
        var buffer = Ti.createBuffer({
            length: 1024 * 10
        }).toBlob();
        xhr.open("POST", "http://www.ambientreality.com/ingot/post_test.php");
        xhr.send({
            data: buffer,
            username: "fgsandford1000",
            password: "sanford1000",
            message: "check me out"
        });
    });
});
