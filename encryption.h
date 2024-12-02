
#ifndef VS_ENCRYPTION_H
#define VS_ENCRYPTION_H

int enryptionAndDecryption(const char *file_name);
int deleteKeyFile(const char *fileName);
int enncrypt_function_with_key();
void ceasarEncrypt(char *str, int key, int keynumber);
void ceasarDecrypt(char *str, int key, int keynumber);
int readKeyFromFile(const char *fileName);

#endif //VS_ENCRYPTION_H