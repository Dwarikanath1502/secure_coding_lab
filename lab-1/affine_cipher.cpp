
// Q.1 Write a program in your convenient programming language to implement the Affine
// Cipher for both encryption and decryption as follows:
// 1. encrypt_affine(plain_text, a, b):
// Encrypt a given plaintext string using the formula: E(x)=(a⋅x+b)mod 26
// Where:
// E(x): Encrypted character
// a: Multiplicative key (must be coprime with 26)
// b: Additive key
// x: Index of the character in the alphabet
// (A=0, B=1, C=2, D=3, E=4, F=5, G=6, H=7, I=8, J=9, K=10, L=11, M=12,
// N=13, O=14, P=15, Q=16, R=17, S=18, T=19, U=20, V=21, W=22, X=23, Y=24,
// Z=25)
// 2. decrypt_affine(cipher_text, a, b):
// Decrypt a given ciphertext string using the formula: D(x)=a−1⋅(x−b)mod 26
// Where:
// D(x): Decrypted character
// a−1: Modular inverse of a modulo 26 (calculated using the Extended Euclidean
// Algorithm).
// Input:
// Enter plaintext: HELLO
// Enter keys (a, b): 5 8
// Output:
// Encrypted text: RCLLA
// Decrypted text: HELLO


#include <iostream>
#include <string>
using namespace std;

// Function to find modular inverse of 'a' under modulo m using Extended Euclidean Algorithm
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++)
        if ((a * x) % m == 1)
            return x;
    return -1; // if inverse doesn't exist
}

// Function to encrypt text using Affine Cipher
string encrypt_affine(string plain_text, int a, int b) {
    string result = "";
    for (char c : plain_text) {
        if (isalpha(c)) {
            char upper = toupper(c);
            int x = upper - 'A';
            char encrypted_char = ((a * x + b) % 26) + 'A';
            result += encrypted_char;
        } else {
            result += c; // keep non-alphabet characters unchanged
        }
    }
    return result;
}

// Function to decrypt text using Affine Cipher
string decrypt_affine(string cipher_text, int a, int b) {
    string result = "";
    int a_inv = modInverse(a, 26);
    if (a_inv == -1) {
        cout << "Multiplicative inverse for 'a' does not exist. Choose 'a' such that it's coprime with 26.\n";
        return "";
    }

    for (char c : cipher_text) {
        if (isalpha(c)) {
            char upper = toupper(c);
            int y = upper - 'A';
            int decrypted_val = (a_inv * (y - b + 26)) % 26; // +26 to avoid negative values
            char decrypted_char = decrypted_val + 'A';
            result += decrypted_char;
        } else {
            result += c; // keep non-alphabet characters unchanged
        }
    }
    return result;
}

int main() {
    string plaintext;
    int a, b;

    cout << "Enter plaintext: ";
    cin >> plaintext;

    cout << "Enter keys (a and b): ";
    cin >> a >> b;

    string encrypted = encrypt_affine(plaintext, a, b);
    cout << "Encrypted text: " << encrypted << endl;

    string decrypted = decrypt_affine(encrypted, a, b);
    cout << "Decrypted text: " << decrypted << endl;

    return 0;
}
