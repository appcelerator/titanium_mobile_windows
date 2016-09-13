var sub2 = require('./sub2'),
    sub3 = require('./sub3');

module.exports = {
    name: 'sub1.js',
    filename: __filename,
    sub: sub2.name,
    sub3: sub3.name
};
