const { doCryptoWork } = require('./hash.js');
const largeData = require('./data.js');
const { doNativeCryptoWork } = require('./build/Release/hashaddon.node');

const operations = 10_000_000;

console.time('Do crypto work in JS');
const jsCount = doCryptoWork(largeData, operations);
console.timeEnd('Do crypto work in JS');
console.log(jsCount + ' hashes generated in js');

console.time('Do crypto work in C++');
const nativeCount = doNativeCryptoWork(largeData, operations);
console.timeEnd('Do crypto work in C++');
console.log(nativeCount + ' hashes generated in C++');

