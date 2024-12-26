#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>

int main()
{ //A1
// Random number generator
int rd;
srand(time(NULL));
rd = rand() % 5330;
//File handling of the txt file (Getting a random word)
char words[15];
char a;
int wordlen;
FILE* fp;
fp = fopen("/Users/mac/Desktop/CTest/words.txt","r");
fseek(fp,rd,SEEK_SET);
do
{ //B1
 a = getc(fp);
 fseek(fp,1,SEEK_CUR);
} //B2
while(a != '\n');
fseek(fp,-1,SEEK_CUR);
fgets(words,sizeof(words),fp);
wordlen = strlen(words);
//Welcome messages
printf("This is a hang man game ! You have 7 chances to guess the word or else...\n");
printf("You get hanged !\n");
printf("Each turn you will enter a letter, if the letter is in the word, it is gonna be displayed\n");
printf("Otherwise a line is gonna be drawn, causing you to get closer to getting hanged !\n");
printf("You can also type ""I want to guess"" in order to guess the word\n");
printf("Note that guessing the word wrong during this process means an instant lose !\n");
printf("Oh and have fun and try not to get hanged !\n");
//Main word checking loop
int chances = 7;
int c = wordlen;
int count = 0, count1 = 0, count2 = 0;
char lcount[15];
char letters;
while(count != wordlen - 1)
{ //B1*
 lcount[count] = '_';
 count++;
} //B2*
while(count != 15)
{ //B1**
 lcount[count] = '\0';
 count++;
} //B2**1
count = 0;
while(chances > 0)
 { //C1 (Inputting guesses)
printf("Guess a letter: ");
scanf(" %c", &letters);  // Ensures you capture only one character
if (!isalpha(letters)) 
{ 
  printf("Please enter a valid letter.\n");
  continue;  // Skip the rest of the loop if it's an invalid input
}
 // Main loop body
  while(count != wordlen - 1)
   { //D1 (Checking if the guess is correct)
    if(letters == words[count])
     { //E1
      lcount[count] = letters; //Storing said guess in an array containing our right guesses
      count++;
      count2++;
     } //E2
      else
       { //F1
        count1++; //Incrementing the non-matching values
        count++;
       } //F2
   } //D2
    count = 0;   
    if(count1 == wordlen - 1) //Check the amount of chances left and print the corresponding state of the game
     { //G1
      switch(chances) 
       { //H1
        case 7: printf("____\n\n");
        printf("%s\n",lcount);
        count1 = 0;
        chances--;
        break;
        case 6: printf("  |  \n  |  \n  |  \n  |  \n__|__\n\n");
        printf("%s\n",lcount);
        count1 = 0;
        chances--;
        break;
        case 5:  printf("  ____\n"); //5
                 printf("  |  \n  |  \n  |  \n  |  \n__|__\n\n");
        printf("%s\n",lcount);
        count1 = 0;
        chances--;
        break;
        case 4:  printf("  ____\n"); //4
                 printf("  |/  \n  |  \n  |  \n  |  \n__|__\n\n");
        printf("%s\n",lcount);
        count1 = 0;
        chances--;
        break;
        case 3:  printf("  ____\n"); //3
                 printf("  |/ |\n  |  \n  |  \n  |  \n__|__\n\n");
        printf("%s\n",lcount);
        count1 = 0;
        chances--;
        break;
        case 2:  printf("  ____\n"); //2
                 printf("  |/ |\n  |  O\n  |  \n  |  \n__|__\n\n");
        printf("%s\n",lcount);
        count1 = 0;
        chances--;
        break;
        case 1:  printf("  ____\n"); //1
                 printf("  |/ |\n  |  O\n  |  |\n  |  \n__|__\n\n");
        printf("%s\n",lcount);
        count1 = 0;
        chances--;
        break;
       } //H2
     } //G2 
      else
       { //I1
        switch(chances+1) 
         { //H1*
          case 7: printf("____\n\n");
          count1 = 0;
          printf("%s\n",lcount);
          break;
          case 6: printf("  |  \n  |  \n  |  \n  |  \n__|__\n\n");
          count1 = 0;
          printf("%s\n",lcount);
          break;
          case 5:  printf("  ____\n"); //5
                   printf("  |  \n  |  \n  |  \n  |  \n__|__\n\n");
          count1 = 0;
          printf("%s\n",lcount);
          break;
          case 4:  printf("  ____\n"); //4
                   printf("  |/  \n  |  \n  |  \n  |  \n__|__\n\n");
          count1 = 0;
          printf("%s\n",lcount);
          break;
          case 3:  printf("  ____\n"); //3
                   printf("  |/ |\n  |  \n  |  \n  |  \n__|__\n\n");
          count1 = 0;
          printf("%s\n",lcount);
          break;
          case 2:  printf("  ____\n"); //2
                   printf("  |/ |\n  |  O\n  |  \n  |  \n__|__\n\n");
          count1 = 0;
          printf("%s\n",lcount);
          break;
          case 1:  printf("  ____\n"); //1
                   printf("  |/ |\n  |  O\n  |  |\n  |  \n__|__\n\n");
          count1 = 0;
          printf("%s\n",lcount);
          break;
        } //H2*
       } //I2
       if(count2 == wordlen - 1)
       {
        printf("You win !\n");
        printf("The word effectively was : %s",words);
        exit(0);
       }
 } //C2
 printf("  ____\n"); //0
 printf("  |/ |\n  |  O\n  | /|\\\n  |  |\\\n__|__\n\n");
 printf("You lose !\n");
 printf("The word was : %s",words);
 exit(0);
} //A2
