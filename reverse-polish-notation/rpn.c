#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int intOperations(char const *input){
  int *positionsO = malloc ((strlen(input) + 1) * sizeof(int));
  int *positionsN = malloc ((strlen(input) + 1) * sizeof(int));
  int *positionsNeg = malloc ((strlen(input) + 1) * sizeof(int));
  int *theInts = malloc (strlen(input) * sizeof(int));
  char flag = 'f';
  char errorFlag = 'f';
  int start = 0, operation = 0;
  
  for(unsigned int j = 0; j < strlen(input);++j){
    //add negative numbers
    if(input[j] == 'p' || input[j] == 's' || input[j] == '*' || input [j] == '/'){
      positionsO[j] = j;
    }
    else if (input[j] == '-'){
      positionsNeg[j] = j;
    }
    
    else if (input[j] != '#'){
      positionsN[j] = j;
    }
  }

  for(unsigned int i = 0; i < strlen(input); ++i){
    if(positionsN[i] != '\0' && flag == 'f'){
      flag = 't';
      theInts[i] = (int)(input[i]);
      theInts[i] = theInts[i] - '0';
    }
    if(positionsN[i] != '\0' && positionsN[i] != '\0' && flag == 't'){
      for(unsigned int k = i+1; k < strlen(input); ++k){
        if(positionsN[k] == '\0'){
          break;
        }
        else{
          theInts[k] = (int)(input[k]);
          theInts[k] = theInts[k] - '0';
          theInts[i] = (theInts[i] *10) + theInts[k];
          theInts[k] = '\0';
          positionsN[k] = '\0';
        }
      }
    }
    if(positionsN[i] == '\0'){
      flag = 'f';
    }
  }
  //negatives
  for (unsigned int i = 0; i < strlen(input); i++){
    if(positionsNeg[i] != '\0'){
      theInts[i+1] = theInts[i+1] * -1;
    }
  }
  
  for(unsigned int i = 0; i < strlen(input); ++i){ //operends
    char flagship = 'f';
    unsigned int countN = 0;
    for(unsigned int k = 0; k < strlen(input); ++k){
        if(positionsN[k] != '\0'){
          ++countN;
        }
      }
    for (unsigned int j = i; 0 < j; --j){ //ints
      if(positionsO[i] == '\0'){
        continue;
      }
      else{

        if(j == 1 && countN < 2){
          printf("Invalid input - operator without enough operands \n");
          errorFlag = 't';
        }
        else{
          if (positionsN[j] != '\0' && flagship == 'f'){
            start = theInts[j];
            theInts[j] = '\0';
            positionsN[j] = '\0';
            flagship = 't';
          }
          else if(positionsN[j] != '\0' && flagship == 't'){
            operation = theInts[j];
            theInts[j] = '\0';
            switch (input[i]){
		    case 'p':
              //addition
              positionsO[i] = '\0';
              theInts[j] = start + operation;
              operation = 0;
              flagship = 'f';

              break;
            case 's':
              //subtracion
              positionsO[i] = '\0';
              theInts[j] =  operation - start;
              operation = 0;
              flagship = 'f';

              break;
            case '*':
              //multi
              positionsO[i] = '\0';
              theInts[j] = start * operation;
              operation = 0;
              flagship = 'f';
              break;
            case '/':
              // int division
              positionsO[i] = '\0';
              theInts[j] = operation / start;
              operation = 0;
              flagship = 'f';
              break;
            }
              break;
          }
        }
      }
    }
  }
  if(errorFlag == 't'){
    free(theInts);
    free(positionsO);
    free(positionsNeg);
    free(positionsN);
    return 1;
  }

  for(unsigned int i = 0; i < strlen(input); ++i){
    if(theInts[i] != '\0'){
      printf("%d\n",theInts[i]);
    }
  }
  free(theInts);
  free(positionsO);
  free(positionsN);
  free(positionsNeg);
  return 0;
}
int errorSeeking(char const *input){
  char errorFlag = 'f';
  for(unsigned int j = 0; j < strlen(input);++j){
    if(input[j] == 'p' || input[j] == 's' || input[j] == '*' || input [j] == '/' || input[j] == '-'){
      continue;
    }
    else if ((input[j] == '0' || input[j] == '1' || input[j] == '2' || input[j] == '3' || input[j] == '4'
    || input[j] == '5' || input[j] == '6' || input[j] == '7' || input[j] == '8' || input[j] == '9')){
      continue;
    }
    else if (input[j] == '#'){
      continue;
    }

    else{
      printf("Invalid input invalid operator %c\n",input[j]);
      errorFlag = 't';
    }
  }
  if(errorFlag == 'f'){
  return 0;
  }
  else{
    return 1;
  }
}



int main(int argc, char const *argv[]){
  char *lineInput = malloc(sizeof(char) * 64 );
  char *allInput = malloc(sizeof(char) * 64);
  char s[] = "#"; //using underscore for better visabilty.
  int errorCode = 0;
  
  strcat(allInput,s);
  scanf("%s",lineInput);
  //scanf("%[^\n]",allInput);
  
  while (1){
  
    strcat(allInput,lineInput);
    strcat(allInput,s);
    
    
    if(scanf("%s",lineInput) == EOF){
      break;
    }
  }

  errorCode = errorSeeking(allInput);
  //printf("%d", errorCode);
  if(errorCode == 0){
    intOperations(allInput);
  }  

  free(allInput);
  free(lineInput);
  return 0;
}
