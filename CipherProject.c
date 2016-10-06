#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char * removeDuplicates(char word[]) {
	int i, j;
	char *temp = word;

	for (i = 0; i < strlen(temp); i++) {
		for (j = strlen(temp)-1; j > i; j--) {
			if (word[i] == word[j]) {
				word[j] = word[j+1];
			}
		}
	}
	for (i = 0; i < strlen(temp); i++) {
		word[i] = toupper(word[i]);
	}
	return word;
}

int targetFound(char charArray[], int num, char target) {
	int i;

	for (i = 0; i < num; i++) {
		if (charArray[i] == target) {
			return 1;
		}
	}
	return 0;
}

void initializeEncryptArray(char key[], char encrypt[]) {
	int x, i = 25, j;

	for (x = 0; x < 26; x++) {
		encrypt[i] = 0;
	}
		
	while (i >= strlen(key)) {
		for (j = 'A'; j <= 'Z'; j++) {
			if (!targetFound(key, strlen(key), j)) {
				encrypt[i] = j;
				i--;
			}
		}
	}
	
	for (i = 0; i < strlen(key); i++) {
		encrypt[i] = key[i];
	}
	
//	printf("Encryption array: %s\n", encrypt);
}

void initializeDecryptArray(char encrypt[], char decrypt[]) {
	int i;

	for (i = 0; i < strlen(decrypt); i++) {
                decrypt[i] = 0;
        }

	for (i = 0; i < 26; i++) {
		decrypt[encrypt[i] - 65] = i + 65;
	}

//	printf("Decryption array: %s\n");
}

void processInput(FILE *inf, FILE *outf, char substitute[]) {
	char temp;
	int i, j;

	while (fscanf(inf, "%c", &temp) != EOF) {
		if (isalpha(temp)) {
			if (isupper(temp)) {
				for (i = 0; i < 26; i++) {
					if (temp == i + 'A') {
						temp = substitute[i];
						fprintf(outf, "%c", temp);
						i = 26;
					}
				}
			}
			if (islower(temp)) {
				for (i = 0; i < 26; i++) {
					if (temp == i + 'a') {
						temp = substitute[i] + 32;
						fprintf(outf, "%c", temp);
						i = 26;
					}
				}
			}
		}
		
		else {
			fprintf(outf, "%c", temp);
		}
	}
}

int main(int argc, char *argv[]) {
	char encrypt[26], key[26], decrypt[26];
	int choice;

	char *pkey;
	FILE *inf, *outf;

//	printf("Enter the key for encrytion: \n");
//	scanf("%s", &key);
	strcpy(key, argv[1]);
	
	pkey = removeDuplicates(key);
//	printf("Your key for encryption is: %s\n", removeDuplicates(key));

	initializeEncryptArray(pkey, encrypt);
	initializeDecryptArray(encrypt, decrypt);

//	Ask for encryption/decryption option.
//	printf("Enter 1 for encryption, enter 2 for decryption: \n");
//	scanf("%d", &choice);
	choice = atoi(argv[2]);
	
	if (choice == 1) {
		inf = fopen(argv[3], "r");
		outf = fopen(argv[4], "w");
		processInput(inf, outf, encrypt);
	}

	else if (choice == 2) {
		inf = fopen(argv[3], "r");
		outf = fopen(argv[4], "w");
		processInput(inf, outf, decrypt);	
	}

	fclose(inf);
	fclose(outf);

/*	if (targetFound(key, 10, target)){
		printf("Target found.\n");
	}
	else {
		printf("Target not found.\n");
	}
*/
	return 0;
}
