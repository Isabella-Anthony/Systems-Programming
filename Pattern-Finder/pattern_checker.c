#include <stdio.h>
#include <string.h>
#define MAX_LEN 1000


int is_singleton(char str[]){
  int checker=0;

    for(int i=0; i < strlen(str)-1;i++){

        if(str[i]==str[i+1]){
              checker=1;

        }
      else{
        checker=0;
         return 0;
      }

    }

    return checker;
}

int is_balanced_tripite(char str[]){

  int sub =strlen(str)/3; 
  int checker=0;

  if(strlen(str)%3 != 0){
    checker= 0;
  }
 else{  
   for (int i = 0; i < sub; i++) {

          if (str[i] == str[i+sub] && str[i+sub]== str[i+(sub*2)]) {
            checker=1;
           
             }
          else{
            checker=0;
            return 0;
            
          }
    }
  }
   return checker ;

}

int is_arithmetic(char str[]){
    int checker=0;

   for (int i = 0; i < strlen(str)-1; i++) {       

        if (str[i]<str[i+1]) {
            checker=1;     
        }
       else{
         checker=0;
         return 0;

     }
       }
    return checker ;
}

int is_reversed_arithmetic(char str[]){

  int checker=0;



   for (int i = 0; i < strlen(str)-1; i++) {       

        if (str[i]>str[i+1]) {
            checker=1;     
        }
       else{
         checker=0;
         return 0;

     }
       }
    return checker ;
}

int is_balanced_bipartite(char str[]){

  int sub =strlen(str)/2; 
  int checker=0;

  if(strlen(str)%2 != 0){
    checker= 0;
  }
 else{  
   for (int i = 0; i < sub; i++) {

          if (str[i] == str[i+sub]) {
            checker=1;

             }
          else{
            checker=0;
            return 0;

          }
    }
  }
   return checker ;

}


int is_palindrome(char str[]) {
 int checker = 0; //start as false 

  for (int i = 0; i < strlen(str); i++) {

    if (str[i] == str[strlen(str) - i-1]) {
      checker =1; //only update if conditions are met

    }
    else{
      checker= 0;
      return 0;
    }
  }
  return checker;
}
