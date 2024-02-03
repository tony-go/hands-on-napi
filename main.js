const largeData = require('./data.js');
const { hash } = require('./hash.js');
const nativeaddon = require('./build/Release/hashaddon');

const operations = 10_000_000;
const jsHashes = [];
const nativeHashes = [];

console.time('Do crypto work in JS');
for (let i = 0; i < operations; i++) {
  jsHashes.push(hash(largeData));
}
console.timeEnd('Do crypto work in JS');

console.time('Do crypto work in native addon');
for (let i = 0; i < operations; i++) {
  const buffer = Buffer.alloc(32);
  nativeaddon.hash(largeData, buffer);
  nativeHashes.push(buffer.toString('hex'));
}
console.timeEnd('Do crypto work in native addon');

console.log(jsHashes[0], nativeHashes[0]);

