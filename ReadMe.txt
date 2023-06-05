    
    Affine cipher cracker 
    The program starts by prompting the user to enter the plaintext, the value of 'a' (the multiplicative key), and the value of 'b' (the additive key).

    The entered 'a' value is validated using the is_valid_a function, which checks if 'a' is coprime with 26 (the size of the alphabet). If the entered 'a' is not valid, the user is prompted to enter a valid value until a valid 'a' is provided.

    The user is then prompted to choose an option for cracking the cipher:
        Option 1: Crack the cipher with a given pair of letters (original and ciphered).
        Option 2: Crack the cipher without a given pair of letters.

    Based on the user's choice, the corresponding function (crack_affine_cipher_with_given_pair or crack_affine_cipher_without_pair) is called to crack the cipher.

    If the user chooses option 1, they are prompted to enter the known pair of letters (original and ciphered). The function crack_affine_cipher_with_given_pair is then called, which calculates the possible keys and prints the decrypted plaintext for each key.

    If the user chooses option 2, the function crack_affine_cipher_without_pair is called. This function iterates through all possible 'a' values (1 to 25) and calculates the corresponding 'b' value for each 'a'. It then uses each pair of 'a' and 'b' values to decrypt the ciphertext and prints the decrypted plaintext.

    Finally, the original ciphertext is decrypted using the provided 'a' and 'b' values using the affine_decrypt function. The decrypted plaintext is displayed to the user.

This program combines techniques such as affine encryption and decryption, modular inverse calculation, cracking the affine cipher with and without a given pair of letters, and input validation for the 'a' value.