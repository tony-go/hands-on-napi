const crypto = require("crypto");

function hash(data, rounds) {
  return crypto.createHash("sha256").update(data).digest("hex");
}

module.exports = {
  hash
};
