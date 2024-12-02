#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
/**
 * This function is used to encrypt and decrypt the pass.json file.
 * @param file_name The name of the file to be encrypted/decrypted.
 * @return 0 if the encryption/decryption is successful, -1 if there is an error.
 */

// If it fails to open the file (e.g., due to a file not found), it prints an error message and exits the program.
void can_file_open(FILE *fp) {
    if (fp == NULL) {
        printf("File cannot be opened\n");
        exit(0);
    }
}

// Writes the key to a file
void writeKeyToFile(const char *fileName, int key) {
    FILE *fp = fopen(fileName, "w");
    can_file_open(fp);
    fprintf(fp, "%d", key);
    fclose(fp);
}

// Reads the key from a file
int readKeyFromFile(const char *fileName) {
    FILE *fp = fopen(fileName, "r");
    if (fp == NULL) {
        return -1; // Indicate that the key file doesn't exist
    }

    int key;
    fscanf(fp, "%d", &key);
    fclose(fp);
    return key;
}

// Deletes the key file
void deleteKeyFile(const char *fileName) {
    remove(fileName);
}

// Checks if the key file exists
int keyExists(const char *fileName) {
    FILE *fp = fopen(fileName, "r");
    if (fp == NULL) {
        return 0; // File doesn't exist
    }
    fclose(fp);
    return 1; // File exists
}

// Encrypts the string using the caesar cipher
void caesarEncrypt(char *str, int key, int keynumber) {
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] = (str[i] - 'a' + key) % 26 + 'a';
        } else if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = (str[i] - 'A' + key) % 26 + 'A';
        } else if (str[i] >= '0' && str[i] <= '9') {
            str[i] = (str[i] - '0' + keynumber) % 10 + '0';
        }
        i++;
    }
}

// Decrypts the string using the caesar cipher
void caesarDecrypt(char *str, int key, int numberkey) {
    caesarEncrypt(str, 26 - key, 10 - numberkey);
}

// Generates a random key
int generateKey() {
    srand(time(NULL));
    return rand() % 26;
}

// Generates a random number key
int gerateNumberKey() {
    srand(time(NULL));
    return rand() % 10;
}

// Encrypts the users.json file
int enncrypt_function_with_key() {
    FILE *fp = fopen("decrypted_output.json", "r");
    can_file_open(fp);
    // Getting the file size
    fseek(fp, 0, SEEK_END);
    long fileSize = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    // Reading the content of the file into a string
    char *content = (char *) malloc(fileSize + 1);
    fread(content, 1, fileSize, fp);
    content[fileSize] = '\0';
    fclose(fp);
    int storedWordKey = readKeyFromFile("word_key.txt");
    int storedNumberKey = readKeyFromFile("number_key.txt");
    caesarEncrypt(content, storedWordKey, storedNumberKey);
    FILE *input = fopen("users.json", "w");
    can_file_open(input);
    fprintf(input, "%s", content);
    fclose(input);
    free(content);
}

// Decrypts the users.json file and makes copy of it
int enryptionAndDecryption(const char* file_name) {
    // Check if word key exists
    if (!keyExists("word_key.txt")) {
        // Generate and store word key
        int wordKey = generateKey();
        writeKeyToFile("word_key.txt", wordKey);
    }

    // Check if number key exists
    if (!keyExists("number_key.txt")) {
        // Generate and store number key
        int numberKey = generateKey();
        writeKeyToFile("number_key.txt", numberKey);
    }

    int storedWordKey = readKeyFromFile("word_key.txt");
    int storedNumberKey = readKeyFromFile("number_key.txt");

    FILE *fp = fopen(file_name, "r");
    can_file_open(fp);

    // Getting the file size
    fseek(fp, 0, SEEK_END);
    long fileSize = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    // Reading the content of the file into a string
    char *content = (char *) malloc(fileSize + 1);
    fread(content, 1, fileSize, fp);
    content[fileSize] = '\0';
    fclose(fp);

    // Decrypting
    caesarDecrypt(content, storedWordKey, storedNumberKey);

   //Writing the decrypted content to a new file
    FILE *decryptedFile = fopen("decrypted_output.json", "w");
    can_file_open(decryptedFile);
    fprintf(decryptedFile, "%s", content);
    fclose(decryptedFile);

    // Generating new keys
    int newWordKey = generateKey();
    int newNumberKey = gerateNumberKey();

    // Encrypting with new keys
    caesarEncrypt(content, newWordKey, newNumberKey);

    // Writing the encrypted content back to the original file
    fp = fopen(file_name, "w");
    can_file_open(fp);
    fprintf(fp, "%s", content);
    fclose(fp);

    // Deleting old keys after use
    deleteKeyFile("word_key.txt");
    deleteKeyFile("number_key.txt");

    // Writing the new keys to files
    writeKeyToFile("word_key.txt", newWordKey);
    writeKeyToFile("number_key.txt", newNumberKey);

    // Freeing memory
    free(content);

    return 0;
}
