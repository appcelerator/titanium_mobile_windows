/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2011-2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */
var should = require('./should');

describe("webview", function () {
    // Make sure to set plentiful timeout
    // so that test won't fail due to the timeout from server
    this.timeout(30000);

    it("Ti.UI.createWebView", function (finish) {
        should(Ti.UI.createWebView).be.a.Function;
        should(Ti.UI.createWebView()).be.an.Object;
        finish();
    });

    it("Ti.UI.WebView.event_beforeload", function (finish) {
        var webview = Ti.UI.createWebView();
        webview.addEventListener('beforeload', function () {
            should(webview.url).be.eql('http://www.appcelerator.com/');
            finish();
        });
        webview.url = 'http://www.appcelerator.com/';
    });

    it("Ti.UI.WebView.event_load", function (finish) {
        var webview = Ti.UI.createWebView();
        webview.addEventListener('load', function () {
            should(webview.url).be.eql('http://www.appcelerator.com/');
            finish();
        });
        webview.url = 'http://www.appcelerator.com/';
    });

    // make sure removeListrener won't remove rest of listeners
    it("Ti.UI.WebView.removeEvent_beforeload", function (finish) {
        var webview = Ti.UI.createWebView();
        var funcToBeRemoved = function () { throw new Error('This should never happen'); };
        webview.addEventListener('beforeload', funcToBeRemoved);
        webview.addEventListener('beforeload', function () {
            should(webview.url).be.eql('http://www.appcelerator.com/');
            finish();
        });
        webview.removeEventListener('beforeload', funcToBeRemoved);
        webview.url = 'http://www.appcelerator.com/';
    });

    // make sure removeListrener won't remove rest of listeners
    it("Ti.UI.WebView.removeEvent_load", function (finish) {
        var webview = Ti.UI.createWebView();
        var funcToBeRemoved = function () { throw new Error('This should never happen'); };
        webview.addEventListener('load', funcToBeRemoved);
        webview.addEventListener('load', function () {
            should(webview.url).be.eql('http://www.appcelerator.com/');
            finish();
        });
        webview.removeEventListener('load', funcToBeRemoved);
        webview.url = 'http://www.appcelerator.com/';
    });

    // make sure removeListrener won't remove rest of listeners
    it("Ti.UI.WebView.removeEvent_error", function (finish) {
        var webview = Ti.UI.createWebView();
        var funcToBeRemoved = function () { throw new Error('This should never happen'); };
        webview.addEventListener('error', funcToBeRemoved);
        webview.addEventListener('error', function () {
            finish();
        });
        webview.removeEventListener('error', funcToBeRemoved);
        webview.url = 'http://xxx/';
    });

    it("Ti.UI.WebView.loading", function (finish) {
        var webview = Ti.UI.createWebView();
        should(webview.loading).be.false;
        webview.addEventListener('beforeload', function () {
            should(webview.loading).be.true;
        });
        webview.addEventListener('load', function () {
            should(webview.loading).be.false;
            finish();
        });
        webview.url = 'http://www.appcelerator.com/';
    });

    it("Ti.UI.WebView.opacity", function (finish) {
        var webview = Ti.UI.createWebView();
        should(webview.opacity).be.a.Number;
        webview.opacity = 0.5;
        should(webview.opacity).be.eql(0.5);
        finish();
    });

    it("Ti.UI.WebView.goBack", function (finish) {
        var webview = Ti.UI.createWebView();
        should(webview.goBack).be.a.Function;
        webview.goBack();
        finish();
    });

    it("Ti.UI.WebView.canGoBack", function (finish) {
        var webview = Ti.UI.createWebView();
        should(webview.canGoBack).be.a.Function;
        should(webview.canGoBack()).be.a.Boolean;
        finish();
    });

    it("Ti.UI.WebView.goForward", function (finish) {
        var webview = Ti.UI.createWebView();
        should(webview.goForward).be.a.Function;
        webview.goForward();
        finish();
    });

    it("Ti.UI.WebView.canGoForward", function (finish) {
        var webview = Ti.UI.createWebView();
        should(webview.canGoForward).be.a.Function;
        should(webview.canGoForward()).be.a.Boolean;
        finish();
    });

    it("Ti.UI.WebView.stopLoading", function (finish) {
        var webview = Ti.UI.createWebView();
        should(webview.stopLoading).be.a.Function;
        webview.addEventListener('beforeload', function (e) {
            webview.stopLoading();
            finish();
        });
        webview.html = '<html><body></body></html>';
    });

    it("Ti.UI.WebView.reload", function (finish) {
        var webview = Ti.UI.createWebView();
        should(webview.reload).be.a.Function;
        webview.addEventListener('load', function (e) {
            webview.reload();
            finish();
        });
        webview.html = '<html><body></body></html>';
    });

    it("Ti.UI.WebView.setData", function (finish) {
        var webview = Ti.UI.createWebView();
        should(webview.setData).be.a.Function;
        finish();
    });

    it.skip("Ti.UI.WebView.getData", function (finish) {
        var webview = Ti.UI.createWebView();
        should(webview.getData).be.a.Function;
        should(webview.getData()).be.an.Object;
        finish();
    });

    it("Ti.UI.WebView.html", function (finish) {
        var webview = Ti.UI.createWebView();
        webview.addEventListener('load', function () {
            if (Ti.Platform.osname == 'windowsstore' || Ti.Platform.osname == 'windowsphone') {
                should(webview.getHtml).be.a.Function;
                webview.getHtml(function (data) {
                    should(data).be.a.String;
                    should(data.indexOf('Hello, World')).not.be.eql(-1)
                    finish();
                });
            } else {
                should(webview.html).be.a.String;
                should(webview.html.indexOf('Hello, World')).not.be.eql(-1)
                finish();
            }
        });
        webview.html = '<html><body>Hello, World</body></html>';
    });

    it("Ti.UI.WebView.evalJS", function (finish) {
        var webview = Ti.UI.createWebView();
        webview.addEventListener('load', function () {
            if (Ti.Platform.osname == 'windowsstore' || Ti.Platform.osname == 'windowsphone') {
                should(webview.evalJS).be.a.Function;
                webview.evalJS("document.body.innerHTML", function (data) {
                    should(data).be.a.String;
                    should(data.indexOf('Hello, World')).not.be.eql(-1)
                    finish();
                });
            } else {
                should(webview.evalJS).be.a.Function;
                should(webview.evalJS('document.body.innerHTML').indexOf('Hello, World')).not.be.eql(-1)
                finish();
            }
        });
        webview.html = '<html><body>Hello, World</body></html>';
    });

    it("Ti.UI.WebView.getCacheMode", function (finish) {
        var webview = Ti.UI.createWebView();
        if (Ti.Platform.osname == 'android') {
            should(webview.getCacheMode).be.a.Function;
            should(webview.getCacheMode()).be.a.Number;
        } else {
            should(webview.getCacheMode).be.undefined;;
        }
        finish();
    });

    it("Ti.UI.WebView.setCacheMode", function (finish) {
        var webview = Ti.UI.createWebView();
        if (Ti.Platform.osname == 'android') {
            should(webview.setCacheMode).be.a.Function;
            webview.setCacheMode(Ti.UI.Android.WEBVIEW_LOAD_DEFAULT);
            should(webview.getCacheMode()).be.eql(Ti.UI.Android.WEBVIEW_LOAD_DEFAULT);
        } else {
            should(webview.setCacheMode).be.undefined;;
        }
        finish();
    });

    it("Ti.UI.WebView.getDisableBounce", function (finish) {
        var webview = Ti.UI.createWebView();
        if (Ti.Platform.osname == 'iphone' || Ti.Platform.osname == 'ipad') {
            should(webview.getDisableBounce).be.a.Function;
            should(webview.getDisableBounce()).be.a.Boolean;
        } else {
            should(webview.getDisableBounce).be.undefined;;
        }
        finish();
    });

    it("Ti.UI.WebView.setDisableBounce", function (finish) {
        var webview = Ti.UI.createWebView();
        if (Ti.Platform.osname == 'iphone' || Ti.Platform.osname == 'ipad') {
            should(webview.setDisableBounce).be.a.Function;
        } else {
            should(webview.getCacheMode).be.undefined;;
        }
        finish();
    });

    it("Ti.UI.WebView.getEnableZoomControls", function (finish) {
        var webview = Ti.UI.createWebView();
        if (Ti.Platform.osname == 'android') {
            should(webview.getEnableZoomControls).be.a.Function;
            should(webview.getEnableZoomControls()).be.a.Boolean;
        } else {
            should(webview.getEnableZoomControls).be.undefined;;
        }
        finish();
    });

    it("Ti.UI.WebView.setEnableZoomControls", function (finish) {
        var webview = Ti.UI.createWebView();
        if (Ti.Platform.osname == 'android') {
            should(webview.setEnableZoomControls).be.a.Function;
        } else {
            should(webview.setEnableZoomControls).be.undefined;;
        }
        finish();
    });

    it("Ti.UI.WebView.getHandlePlatformUrl", function (finish) {
        var webview = Ti.UI.createWebView();
        if (Ti.Platform.osname == 'iphone' || Ti.Platform.osname == 'ipad') {
            should(webview.getHandlePlatformUrl).be.a.Function;
            should(webview.getHandlePlatformUrl()).be.a.Boolean;
        } else {
            should(webview.getHandlePlatformUrl).be.undefined;;
        }
        finish();
    });

    it("Ti.UI.WebView.setHandlePlatformUrl", function (finish) {
        var webview = Ti.UI.createWebView();
        if (Ti.Platform.osname == 'iphone' || Ti.Platform.osname == 'ipad') {
            should(webview.setHandlePlatformUrl).be.a.Function;
        } else {
            should(webview.setHandlePlatformUrl).be.undefined;;
        }
        finish();
    });

    it("Ti.UI.WebView.getHideLoadIndicator", function (finish) {
        var webview = Ti.UI.createWebView();
        if (Ti.Platform.osname == 'iphone' || Ti.Platform.osname == 'ipad') {
            should(webview.getHideLoadIndicator).be.a.Function;
            should(webview.getHideLoadIndicator()).be.a.Boolean;
        } else {
            should(webview.getHideLoadIndicator).be.undefined;;
        }
        finish();
    });

    it("Ti.UI.WebView.setHideLoadIndicator", function (finish) {
        var webview = Ti.UI.createWebView();
        if (Ti.Platform.osname == 'iphone' || Ti.Platform.osname == 'ipad') {
            should(webview.setHideLoadIndicator).be.a.Function;
        } else {
            should(webview.setHideLoadIndicator).be.undefined;;
        }
        finish();
    });

    it("Ti.UI.WebView.getIgnoreSslError", function (finish) {
        var webview = Ti.UI.createWebView();
        if (Ti.Platform.osname == 'android') {
            should(webview.getIgnoreSslError).be.a.Function;
            should(webview.getIgnoreSslError()).be.a.Boolean;
        } else {
            should(webview.getIgnoreSslError).be.undefined;;
        }
        finish();
    });

    it("Ti.UI.WebView.setIgnoreSslError", function (finish) {
        var webview = Ti.UI.createWebView();
        if (Ti.Platform.osname == 'android') {
            should(webview.setIgnoreSslError).be.a.Function;
        } else {
            should(webview.setIgnoreSslError).be.undefined;;
        }
        finish();
    });

    it("Ti.UI.WebView.getLightTouchEnabled", function (finish) {
        var webview = Ti.UI.createWebView();
        if (Ti.Platform.osname == 'android') {
            should(webview.getLightTouchEnabled).be.a.Function;
            should(webview.getLightTouchEnabled()).be.a.Boolean;
        } else {
            should(webview.getLightTouchEnabled).be.undefined;;
        }
        finish();
    });

    it("Ti.UI.WebView.setLightTouchEnabled", function (finish) {
        var webview = Ti.UI.createWebView();
        if (Ti.Platform.osname == 'android') {
            should(webview.setLightTouchEnabled).be.a.Function;
        } else {
            should(webview.setLightTouchEnabled).be.undefined;;
        }
        finish();
    });

    it("Ti.UI.WebView.getOnCreateWindow", function (finish) {
        var webview = Ti.UI.createWebView();
        if (Ti.Platform.osname == 'android') {
            should(webview.getOnCreateWindow).be.a.Function;
            should(webview.getOnCreateWindow()).be.an.Object;
        } else {
            should(webview.getOnCreateWindow).be.undefined;;
        }
        finish();
    });

    it("Ti.UI.WebView.setOnCreateWindow", function (finish) {
        var webview = Ti.UI.createWebView();
        if (Ti.Platform.osname == 'android') {
            should(webview.setOnCreateWindow).be.a.Function;
        } else {
            should(webview.setOnCreateWindow).be.undefined;;
        }
        finish();
    });

    it("Ti.UI.WebView.getOverScrollMode", function (finish) {
        var webview = Ti.UI.createWebView();
        if (Ti.Platform.osname == 'android') {
            should(webview.getOverScrollMode).be.a.Function;
            should(webview.getOverScrollMode()).be.a.Number;
        } else {
            should(webview.getOverScrollMode).be.undefined;;
        }
        finish();
    });

    it("Ti.UI.WebView.setOverScrollMode", function (finish) {
        var webview = Ti.UI.createWebView();
        if (Ti.Platform.osname == 'android') {
            should(webview.setOverScrollMode).be.a.Function;
        } else {
            should(webview.setOverScrollMode).be.undefined;;
        }
        finish();
    });

    it("Ti.UI.WebView.getPluginState", function (finish) {
        var webview = Ti.UI.createWebView();
        if (Ti.Platform.osname == 'android') {
            should(webview.getPluginState).be.a.Function;
            should(webview.getPluginState()).be.a.Number;
        } else {
            should(webview.getPluginState).be.undefined;;
        }
        finish();
    });

    it("Ti.UI.WebView.setPluginState", function (finish) {
        var webview = Ti.UI.createWebView();
        if (Ti.Platform.osname == 'android') {
            should(webview.setPluginState).be.a.Function;
        } else {
            should(webview.setPluginState).be.undefined;;
        }
        finish();
    });

    it("Ti.UI.WebView.getScalesPageToFit", function (finish) {
        var webview = Ti.UI.createWebView();
        if (Ti.Platform.osname == 'windowsstore' || Ti.Platform.osname == 'windowsphone') {
            should(webview.getScalesPageToFit).be.undefined;;
        } else {
            should(webview.getScalesPageToFit).be.a.Function;
            should(webview.getScalesPageToFit()).be.a.Boolean;
        }
        finish();
    });

    it("Ti.UI.WebView.setScalesPageToFit", function (finish) {
        var webview = Ti.UI.createWebView();
        if (Ti.Platform.osname == 'windowsstore' || Ti.Platform.osname == 'windowsphone') {
            should(webview.setScalesPageToFit).be.undefined;;
        } else {
            should(webview.setScalesPageToFit).be.a.Function;
        }
        finish();
    });

    it("Ti.UI.WebView.getScrollsToTop", function (finish) {
        var webview = Ti.UI.createWebView();
        if (Ti.Platform.osname == 'iphone' || Ti.Platform.osname == 'ipad') {
            should(webview.getScrollsToTop).be.a.Function;
            should(webview.getScrollsToTop()).be.a.Boolean;
        } else {
            should(webview.getScrollsToTop).be.undefined;;
        }
        finish();
    });

    it("Ti.UI.WebView.setScrollsToTop", function (finish) {
        var webview = Ti.UI.createWebView();
        if (Ti.Platform.osname == 'iphone' || Ti.Platform.osname == 'ipad') {
            should(webview.setScrollsToTop).be.a.Function;
        } else {
            should(webview.setScrollsToTop).be.undefined;;
        }
        finish();
    });

    it("Ti.UI.WebView.getUserAgent", function (finish) {
        var webview = Ti.UI.createWebView();
        if (Ti.Platform.osname == 'android') {
            should(webview.getUserAgent).be.a.Function;
            should(webview.getUserAgent()).be.a.String;
        } else {
            should(webview.getUserAgent).be.undefined;;
        }
        finish();
    });

    it("Ti.UI.WebView.setUserAgent", function (finish) {
        var webview = Ti.UI.createWebView();
        if (Ti.Platform.osname == 'android') {
            should(webview.setUserAgent).be.a.Function;
        } else {
            should(webview.setUserAgent).be.undefined;;
        }
        finish();
    });

    it("Ti.UI.WebView.getWillHandleTouches", function (finish) {
        var webview = Ti.UI.createWebView();
        if (Ti.Platform.osname == 'iphone' || Ti.Platform.osname == 'ipad') {
            should(webview.getWillHandleTouches).be.a.Function;
            should(webview.getWillHandleTouches()).be.a.Boolean;
        } else {
            should(webview.getWillHandleTouches).be.undefined;;
        }
        finish();
    });

    it("Ti.UI.WebView.setWillHandleTouches", function (finish) {
        var webview = Ti.UI.createWebView();
        if (Ti.Platform.osname == 'iphone' || Ti.Platform.osname == 'ipad') {
            should(webview.setWillHandleTouches).be.a.Function;
        } else {
            should(webview.setWillHandleTouches).be.undefined;;
        }
        finish();
    });

    it("Ti.UI.WebView.pause", function (finish) {
        var webview = Ti.UI.createWebView();
        if (Ti.Platform.osname == 'android') {
            should(webview.pause).be.a.Function;
            webview.pause();
        } else {
            should(webview.pause).be.undefined;;
        }
        finish();
    });

    it("Ti.UI.WebView.resume", function (finish) {
        var webview = Ti.UI.createWebView();
        if (Ti.Platform.osname == 'android') {
            should(webview.resume).be.a.Function;
            webview.resume();
        } else {
            should(webview.resume).be.undefined;;
        }
        finish();
    });

    it("Ti.UI.WebView.repaint", function (finish) {
        var webview = Ti.UI.createWebView();
        if (Ti.Platform.osname == 'iphone' || Ti.Platform.osname == 'ipad') {
            should(webview.repaint).be.a.Function;
            webview.repaint();
        } else {
            should(webview.repaint).be.undefined;;
        }
        finish();
    });

    it("Ti.UI.WebView.setBasicAuthentication", function (finish) {
        var webview = Ti.UI.createWebView();
        should(webview.setBasicAuthentication).be.a.Function;
        finish();
    });

    it("Ti.UI.WebView.LocalScript_log", function (finish) {
        var webview = Ti.UI.createWebView();
        webview.addEventListener('load', function () {
            if (Ti.Platform.osname == 'windowsstore' || Ti.Platform.osname == 'windowsphone') {
                should(webview.evalJS).be.a.Function;
                webview.evalJS("try{Ti.API.info('Test');}catch(E){'[ERROR]';}", function (data) {
                    should(data).be.a.String;
                    should(data.indexOf('[ERROR]')).be.eql(-1)
                    finish();
                });
            } else {
                should(webview.evalJS).be.a.Function;
                should(webview.evalJS("try{Ti.API.info('Test');}catch(E){'[ERROR]';}").indexOf('[ERROR]')).be.eql(-1)
                finish();
            }
        });
        webview.html = '<html><body>Hello, World</body></html>';
    });

});
