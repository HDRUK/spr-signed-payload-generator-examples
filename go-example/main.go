package main

import (
	"crypto/hmac"
	"crypto/sha256"
	"encoding/base64"
	"encoding/json"
	"fmt"
)

func main() {
	payload := map[string]interface{}{
		"user":   "Alice",
		"action": "transfer",
		"amount": 100,
	}

	payloadJSON, err := json.Marshal(payload)
	if err != nil {
		panic(err)
	}

	safePeopleRegistryIdentifier := []byte("ReplaceMeWithYourSafePeopleRegistryIdentifier")

	h := hmac.New(sha256.New, safePeopleRegistryIdentifier)
	h.Write(payloadJSON)
	signature := h.Sum(nil)

	signatureBase64 := base64.StdEncoding.EncodeToString(signature)

	fmt.Println("Payload JSON:", string(payloadJSON))
	fmt.Println("Signature:", signatureBase64)
}
