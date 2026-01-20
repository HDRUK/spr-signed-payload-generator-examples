import hmac
import hashlib
import base64
import json

payload = {
    "user": "Alice",
    "action": "transfer",
    "amount": 100
}

payload_json = json.dumps(payload, separators=(",", ":"))

safe_people_registry_identifier = b"ReplaceMeWithYourSafePeopleRegistryIdentifier"

signature = hmac.new(
    safe_people_registry_identifier,
    payload_json.encode("utf-8"),
    hashlib.sha256
).digest()

signature_base64 = base64.b64encode(signature).decode("utf-8")

print("Signature:", signature_base64)
