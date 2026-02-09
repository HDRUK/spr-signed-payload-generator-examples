using System;
using System.Security.Cryptography;
using System.Text;
using System.Text.Json;

class Program
{
    static void Main()
    {
        var payload = new
        {
            user = "Alice",
            action = "transfer",
            amount = 100
        };

        // Convert payload to minified JSON string
        string payloadJson = JsonSerializer.Serialize(
            payload,
            new JsonSerializerOptions { WriteIndented = false }
        );

        // Secret key
        string secretKey = "UHaelt3kZcGLsnQRCPwmFUnyRchj9rV9pk1JKhxH";
        byte[] secretKeyBytes = Encoding.UTF8.GetBytes(secretKey);

        // Generate HMAC-SHA256 signature
        using HMACSHA256 hmac = new HMACSHA256(secretKeyBytes);
        byte[] signatureBytes = hmac.ComputeHash(
            Encoding.UTF8.GetBytes(payloadJson)
        );

        // Encode to Base64 string
        string signatureBase64 = Convert.ToBase64String(signatureBytes);

        Console.WriteLine("Signature: " + signatureBase64);
    }
}
