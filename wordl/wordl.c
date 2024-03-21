//Wordle for terminal!
//Returns 1 for error
//need to clean up code and fix alignment. But it works thats what matters (1:45am, Feb 14, 2024)

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const char * const GREEN = "\x1b[32m";
const char * const YELLOW = "\x1b[33m";
const char * const WHITE = "\x1b[0m";
const char * current = WHITE;

void setColour(const char *colour) {
  if (current == colour) return;
  printf("%s", colour);
  current = colour;
}

void failed(char const **word){
  setColour(WHITE);
  char fail[] = "Failed to guess the word: ";
  printf("%s%s\n", fail, word[1]);
}
int compareArray(char const *word, char const *guess_word){
  unsigned int green = 0;
  
  int *g = malloc (strlen(word) * sizeof(int));
  char *wordLetters = malloc( (strlen(word) * sizeof(char) ));
  int *occur = malloc (strlen(word) * sizeof(int));
  int *occurGuess = malloc (strlen(word) * sizeof(int));
  char *guessLetters = malloc( (strlen(word) * sizeof(char) ));
  
  //set all to 0
  for(unsigned int i = 0; i < strlen(word); ++i){
      g[i] =0;
      occur[i]=0;
      occurGuess[i]=0;
      wordLetters[i] = word[i];
      guessLetters[i] = guess_word[i];
  }

  for(unsigned int i = 0; i < strlen(word); ++i){
    for(unsigned int j = (0); j < strlen(word); ++j){
        if(wordLetters[i] == wordLetters[j]){
            ++occur[i];
        }
        if(guessLetters[i] == guessLetters[j]){
            ++occurGuess[i];
        }
    }
  }
  
  
  
    for(unsigned int i = 0; i < strlen(word); ++i){
        for(unsigned int j = (1+i); j < strlen(word); ++j){
            if(wordLetters[i] == wordLetters[j]){
                wordLetters[j] = 0;
                occur[j] = 0;
            }
        //added
            if(guessLetters[i] == guessLetters[j]){
                guessLetters[j] = 0;
                occurGuess[j] = 0;
            }
        }
    }
  
//hours wasted 18
// ~~ 300 lines of code later

//GREEN
    for(unsigned int i = 0; i < strlen(word); ++i){
        if(word[i] == guess_word[i]){
            g[i] = 1;
            ++green;
            for(unsigned int j = 0; j <strlen(word); ++j){
                if(guess_word[i] == wordLetters[j]){
                    occur[j] = occur[j] - 1;
                }
            }
        }
    }

//YELLOW
for(unsigned int i = 0; i <strlen(word); ++i){
    for(unsigned int j = 0; j <strlen(word); ++j){       
        if(guess_word[i] == wordLetters[j] && g[i] != 1 && occur[j] > 0){
            for(unsigned int k = 0; k <strlen(word); ++k){
                if(guess_word[i] == wordLetters[k]){
                    if(occur[k] > 0){
                        occur[k] = occur[k] - 1;
                    }
                }
            }
            g[i] = 2;
        }
    }
}

  for(unsigned int i = 0; i <strlen(word); ++i){
    if(g[i] == 1){
      setColour(GREEN);
    }
    else if(g[i] == 2){
      setColour(YELLOW);
    }
    else if(g[i] == 0){
      setColour(WHITE);
    }
    printf("%c", guess_word[i]);
    //setColour(WHITE);
  } printf("\n");
  
  free(g);
  free(wordLetters);
  free(occur);
  free(occurGuess);
  free(guessLetters);
  return green;
}


int main(int argc, char const *argv[]){
//  printf("%d", argc);
  if (argc != 2){
    printf("Invalid number of command line arguments\n");
    return 1;
  }
  else if(strlen(argv[1]) > 12){
    printf("Code longer than 12 characters, invalid input\n");
    return 1;
  }
  else{
    char *str = malloc( (strlen(argv[1]) + 1) * sizeof(char));
    unsigned int i = 0; //to keep outside of for loop
    for(; i < 6; ++i){
      setColour(WHITE);
      printf("Enter guess: ");
      scanf("%s", str);
      //if(strlen(guess) > 12 || strlen(guess) < strlen(argv[1])){
      if(strlen(str) != strlen(argv[1]) ){
        printf("Invalid guess, guess length must match word length\n");
        free(str);
        return 1;
      }

      //Will need to print letters individially
      unsigned int greenLetters = compareArray(argv[1], str);
      if (greenLetters == strlen(argv[1])){
        setColour(WHITE);
        printf("Finished in %d guesses\n", (i+1));
        free(str);
        return 0;
      }

    }
    failed(argv);
    free(str);
  }
  return 0;
}