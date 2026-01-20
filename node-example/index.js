const crypto = require("crypto");

const payload = {
    "user":   "Alice",
    "action": "transfer",
    "amount": 100,
};

const payloadJson = JSON.stringify(payload);

const safePeopleRegistryIdentifier = Buffer.from(
    "ReplaceMeWithYourSafePeopleRegistryIdentifier"
);

const signature = crypto
    .createHmac("sha256", safePeopleRegistryIdentifier)
    .update(payloadJson, "utf-8")
    .digest("base64");

console.log("Signature:", signature);
