/**
* Appcelerator Titanium Mobile
* Copyright (c) 2009-2014 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License
* Please see the LICENSE included with this distribution for details.
*/

var domParser = require('TitaniumPedro/dom-parser');

exports.parseString = function(_string) {
    var result = new domParser.DOMParser().parseFromString(_string, 'text/xml');
    if (result === undefined) {
        throw new Error("Unable to parse string as XML");
    } else {
        return result;
    }
};
 
exports.serializeToString = function(_xml) {
    return new domParser.XMLSerializer().serializeToString(_xml);
};

exports.apiName = 'Ti.XML';
exports.getApiName = function(){
    return exports.apiName;
};
