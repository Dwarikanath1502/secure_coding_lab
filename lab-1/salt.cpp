// Continuing the Q.1, now use the concept of salting the plaintext before applying the
// encryption function over the plaintext. User has to choose some salt value say S such
// that S Є Z26
// .
// 
// The process as follows:
// Plaintext: HELLO
// Salt added to each character: H+C, E+C, L+C, L+C, O+C. ( 7+2, 4+2, 11+2, 11+2, 14+2)
// Modified Plaintext: JGNNQ
// Encrypted text using Affine Cipher: BMVVK.

#include <iostream>
#include <string>
using namespace std;

// Modular inverse function using brute-force
int modInverse(int a, int m) {
    a %= m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1;
}

// Add salt to each character of plaintext
string addSalt(string text, int salt) {
    string result = "";
    for (char c : text) {
        if (isalpha(c)) {
            int x = toupper(c) - 'A';
            char salted_char = ((x + salt) % 26) + 'A';
            result += salted_char;
        } else {
            result += c;
        }
    }
    return result;
}

// Affine encryption function
string encrypt_affine(string text, int a, int b) {
    string result = "";
    for (char c : text) {
        int x = toupper(c) - 'A';
        char encrypted_char = ((a * x + b) % 26) + 'A';
        result += encrypted_char;
    }
    return result;
}

// Affine decryption function (with salt removal)
string decrypt_affine_with_salt(string encrypted_text, int a, int b, int salt) {
    string result = "";
    int a_inv = modInverse(a, 26);
    if (a_inv == -1) {
        cout << "Invalid key! 'a' has no modular inverse modulo 26.\n";
        return "";
    }

    for (char c : encrypted_text) {
        int y = toupper(c) - 'A';
        int x = (a_inv * (y - b + 26)) % 26;
        char original = (x - salt + 26) % 26 + 'A'; // Remove salt
        result += original;
    }

    return result;
}

int main() {
    string plaintext;
    int a, b, salt;

    cout << "Enter plaintext (UPPERCASE): ";
    cin >> plaintext;

    cout << "Enter keys (a and b): ";
    cin >> a >> b;

    cout << "Enter salt value (0-25): ";
    cin >> salt;

    string salted = addSalt(plaintext, salt);
    cout << "Salted plaintext: " << salted << endl;

    string encrypted = encrypt_affine(salted, a, b);
    cout << "Encrypted text: " << encrypted << endl;

    string decrypted = decrypt_affine_with_salt(encrypted, a, b, salt);
    cout << "Decrypted text: " << decrypted << endl;

    return 0;
}
