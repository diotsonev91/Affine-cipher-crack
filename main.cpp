#include <iostream>

int gcd_extended(int a, int b, int& x, int& y) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }

    int x1, y1;
    int gcd = gcd_extended(b % a, a, x1, y1);

    x = y1 - (b / a) * x1;
    y = x1;

    return gcd;
}

int modular_inverse(int a, int m) {
    int x, y;
    int gcd = gcd_extended(a, m, x, y);

    if (gcd != 1) {
        // Modular inverse doesn't exist
        return -1;
    }

    return (x % m + m) % m;
}

std::string affine_encrypt(const std::string& plaintext, int a, int b) {
    std::string encrypted_text = "";

    for (char c : plaintext) {
        if (isalpha(c)) {
            int x = toupper(c) - 'A';
            int y = (a * x + b) % 26;
            encrypted_text += 'A' + y;
        } else {
            encrypted_text += c;
        }
    }

    return encrypted_text;
}

std::string affine_decrypt(const std::string& ciphertext, int a, int b) {
    std::string decrypted_text = "";
    int a_inverse = modular_inverse(a, 26);

    if (a_inverse == -1) {
        std::cout << "The value of 'a' is not valid. It should be coprime with 26." << std::endl;
        return decrypted_text;
    }

    for (char c : ciphertext) {
        if (isalpha(c)) {
            int y = toupper(c) - 'A';
            int x = (a_inverse * (y - b + 26)) % 26;
            decrypted_text += 'A' + x;
        } else {
            decrypted_text += c;
        }
    }

    return decrypted_text;
}

void crack_affine_cipher_with_given_pair(const std::string& ciphertext, char knownLetter, char knownCipher) {
    int x = knownLetter - 'A';
    int y = knownCipher - 'A';
    std::string plaintext;

    for (int a = 1; a <= 25; ++a) {
        int inverse = modular_inverse(a, 26);
        if (inverse != -1) {
            int b = ((y - (a * x)) % 26 + 26) % 26;
            for (char cipher : ciphertext) {
                int cipherValue = cipher - 'A';
                int plaintextValue = ((inverse * (cipherValue - b)) % 26 + 26) % 26;
                char plainChar = 'A' + plaintextValue;
                plaintext += plainChar;
            }
            std::cout << "Possible key found: a = " << a << ", b = " << b << std::endl;
            std::cout << "Plaintext: " << plaintext << std::endl;
            plaintext.clear();
        }
    }

}


void crack_affine_cipher_without_pair(const std::string& ciphertext, char knownLetter = '\0', char knownCipher = '\0') {
    std::string plaintext;

    for (int a = 1; a <= 25; ++a) {
        int inverse = modular_inverse(a, 26);
        if (inverse != -1) {
            for (int b = 0; b < 26; ++b) {
                plaintext = affine_decrypt(ciphertext, a, b);
                if (knownLetter != '\0' && knownCipher != '\0') {
                    if (plaintext[0] == knownLetter && ciphertext[0] == knownCipher) {
                        std::cout << "Possible key found: a = " << a << ", b = " << b << std::endl;
                        std::cout << "Plaintext: " << plaintext << std::endl;
                        return;
                    }
                } else {
                    std::cout << "Possible key found: a = " << a << ", b = " << b << std::endl;
                    std::cout << "Plaintext: " << plaintext << std::endl;
                }
            }
        }
    }

    std::cout << "No key found." << std::endl;
}

bool is_valid_a(int a) {
    // Check if 'a' is coprime with 26
    int m = 26;
    int x, y;
    int gcd = gcd_extended(a, m, x, y);

    return (gcd == 1);
}

int main() {
  std::string plaintext;
    int a, b;

    std::cout << "Enter the plaintext: ";
    std::getline(std::cin, plaintext);

    std::cout << "Enter the value of 'a': ";
    std::cin >> a;

    // Validate 'a'
    while (!is_valid_a(a)) {
        std::cout << "Invalid value of 'a'. 'a' should be coprime with 26." << std::endl;
        std::cout << "Enter a valid value of 'a': ";
        std::cin >> a;
    }

    std::cout << "Enter the value of 'b': ";
    std::cin >> b;

    std::cin.ignore(); // Ignore the newline character

    std::string ciphertext = affine_encrypt(plaintext, a, b);
    std::cout << "Ciphertext: " << ciphertext << std::endl;

    char option;
    std::cout << "Choose an option for cracking the cipher: " << std::endl;
    std::cout << "1. Crack with a given pair of letters" << std::endl;
    std::cout << "2. Crack without a given pair of letters" << std::endl;
    std::cout << "Enter your choice (1 or 2): ";
    std::cin >> option;

    std::cin.ignore(); // Ignore the newline character

    if (option == '1') {
        char plain1, cipher1;
        std::cout << "Enter the known pair of letters (original and ciphered): ";
        std::cin >> plain1 >> cipher1;
        crack_affine_cipher_with_given_pair(ciphertext, plain1, cipher1);
    } else if (option == '2') {
        crack_affine_cipher_without_pair(ciphertext);
    } else {
        std::cout << "Invalid option." << std::endl;
    }

    std::string decrypted_text = affine_decrypt(ciphertext, a, b);
    std::cout << "Decrypted Text: " << decrypted_text << std::endl;

    return 0;
}
