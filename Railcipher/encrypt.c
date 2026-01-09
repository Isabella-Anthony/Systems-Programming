#include <railcipher.h>
#include <string.h>
#include <ctype.h>


char* remove_non_alpha(char *string){
    int length = strlen(string);
    int j=0;

    for(int i=0;i<length;i++){

        if(isalpha(string[i])){
            string[j]= string[i];
            j++;
        }   
   }
   string[j] = '\0';

   return string;
}
char* to_lower(char *string){
     int length = strlen(string);
      for(int i=0;i<length;i++){
          string[i] = tolower(string[i]);
      }
}



void encrypt(char* plaintext, int* key){
    //define 2d array
    //l,m,n    

    char* text = remove_non_alpha(plaintext);
    to_lower(text);
       

    int l = strlen(text); //amount of letters
    int n = l / m +1;
    int gridsize= m*n;
    char cipher[gridsize];
    char grid[n][m];
    char string[] = "xyzxabcdefghijklmnopqrstuvw";
    int diff= gridsize-l;
    

    if (diff > 0){
        strncat(text, string,diff);
    } 

  for(int i = 0; i < n;i++){
        for(int j = 0; j < m;j++){

            grid[i][j] = text[0];
            text++;
            
        }    
       
   }

	// for(int i = 0; i < n;i++){
	// 	for(int j = 0; j < m;j++){
	// 		putchar(grid[i][j]);
    //     }
	// }
  
    //concetanate the letter of each colomun based on the key
    for(int j = 0; j < m;j++){
		for(int i = 0; i < n;i++){
			cipher[n * (key[j]-1) + i] = grid[i][j];
        }
    }

    printf(cipher);
    printf("\n");

}   
