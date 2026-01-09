#include <railcipher.h>
void decrypt(char* ciphertext, int* key){
    //define 2d array
    //l,m,n
    int l= strlen(ciphertext);
    if(l%m){
        error("lenghth of ciphetext is not divisible by length key",7);
    }
    int n =l/m; 
    char grid[n][m];
    //break into n bit pieces and put every n bit into one column
    for(int j = 0; j < m;j++)
		for(int i = 0; i < n;i++)
			grid[i][j] = ciphertext[n * (key[j]-1) + i];
	printf("Result: ");
	for(int i = 0; i < n;i++)
		for(int j = 0; j < m;j++)
			putchar(grid[i][j]);
	printf("\n");
}
