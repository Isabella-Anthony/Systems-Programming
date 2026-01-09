#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define FALSE 0
#define TRUE 1
#define MAX_LEN 1000
#define error(m,c) do{printf("Fatal Error: %s\n", m);exit(c);}while(0)
extern int m;
void encrypt(char* plaintext, int* key);
void decrypt(char* ciphertext, int* key);