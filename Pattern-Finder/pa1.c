#include "pa1.h"
int main(void){
    char line[MAX_LEN];
    while(fgets(line,MAX_LEN,stdin)){
        int len= strlen(line)-1;
        line[len]='\0';

        if(is_singleton(line))
             printf("singleton\n");

        if(is_arithmetic(line))
             printf("arithmetic\n");

        if(is_reversed_arithmetic(line))
             printf("reversed arithmetic\n");

        if(is_balanced_tripite(line))
             printf("balanced tripite\n");

        if(is_balanced_bipartite(line))
             printf("balanced bipartite\n");

        if(is_palindrome(line))
             printf("palindrome\n");
             printf("\n");     
                         
    }

}