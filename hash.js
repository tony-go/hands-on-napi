const crypto = require("crypto");

const hashes = [];

function doCryptoWork(data, rounds) {
  for (let i = 0; i < rounds; i++) {
    const hash = crypto.createHash("sha256").update(data).digest("hex");
    hashes.push(hash);
  }
  return hashes.length;
}

module.exports = {
  doCryptoWork,
};
