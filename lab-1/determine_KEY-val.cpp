// Q.2 You are provided with the following cipher text encrypted using the Affine Cipher.
// Your task is to determine the key pair (a, b) used for the encryption and decrypt the
// provided ciphertext.
// FMXVEDKAPHFERBNDKRXRSREFMORUDSDKDVSHVUFEDK APRKDLYEVLRHHRH
// Table 1: Frequency of letters in above CT.

#include <iostream>
#include <string>
#include <map>
#include <algorithm>
using namespace std;

// Function to find modular inverse of a under mod m
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1;
}

// Affine decryption function
string decrypt_affine(string cipher_text, int a, int b) {
    string result = "";
    int a_inv = modInverse(a, 26);
    if (a_inv == -1) {
        cout << "Invalid key! 'a' has no modular inverse modulo 26.\n";
        return "";
    }

    for (char c : cipher_text) {
        if (isalpha(c)) {
            int y = toupper(c) - 'A';
            int x = (a_inv * (y - b + 26)) % 26;
            result += (x + 'A');
        } else {
            result += c;
        }
    }

    return result;
}

// Frequency count helper
void letterFrequency(string text) {
    map<char, int> freq;
    for (char c : text) {
        if (isalpha(c)) {
            freq[toupper(c)]++;
        }
    }
    for (auto& pair : freq) {
        cout << pair.first << " = " << pair.second << "\n";
    }
}

int main() {
    string ciphertext = "FMXVEDKAPHFERBNDKRXRSREFMORUDSDKDVSHVUFEDKAPRKDLYEVLRHHRH";

    // Print frequencies
    cout << "Letter frequencies in ciphertext:\n";
    letterFrequency(ciphertext);

    // Try common 'a' values (must be coprime with 26): 1, 3, 5, 7, 9, 11, 15, 17, 19, 21, 23, 25
    // Assume most frequent letter corresponds to 'E' (index 4)
    int a = 5, b = 8; // from example, modify based on frequency assumption
    cout << "\nTrying decryption with a = " << a << ", b = " << b << ":\n";
    string decrypted = decrypt_affine(ciphertext, a, b);
    cout << "Decrypted text:\n" << decrypted << endl;

    return 0;
}
