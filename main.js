const largeData = require('./data.js');
const { hash } = require('./hash.js');

const operations = 10_000_000;

console.time('Do crypto work in JS');
for (let i = 0; i < operations; i++) {
  hash(largeData);
}
console.timeEnd('Do crypto work in JS');

