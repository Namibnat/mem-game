
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "mem.h"

int checker(int *wrd, int **wordbin, int reps);
int winner(int right, int reps);
void printhelp(int reps);
void printwords(int word[MLW]);

int main(int argc, char *argv[])
{

  srand(time(NULL));
  FILE *fp;
  int i, ii, li, ri, c, letter, reps, state;
  int right, r, sec;
  int lcounter, wcounter, gcounter;
  int wordholder_max;
  int *wps[FM], *wordbin[MREPS], wrd[MLW];
  int buffer[BUF];
  int word[MLW], wordholder[MREPS][MLW];

  state = OUT;
  /* clear the console to start the game */
  system("clear");

  if(argc > 1 && argv[1][0] == 'h'){
    printhelp(DEFREPS);
    return(EXIT_SUCCESS);
  }
  if(argc > 1 && isdigit(argv[1][0])){
    reps = argv[1][0] - '0';
    if(isdigit(argv[1][1])){
      reps = (reps * 10) + (argv[1][0] - '0');
    }
    if(isdigit(argv[1][2])){
      printhelp(DEFREPS);
      return(EXIT_SUCCESS);
    }
  }
  else{
    reps = DEFREPS;
    printf("\nYou'll guess %d words\n", reps);
  }
  ri = reps;
  /* sec - how long user gets to study the word */
  sec = reps * 5;
  /* Get the words from the file */
  fp = fopen(FW, "r");
  lcounter = wcounter = 0;
  while((c = getc(fp)) != EOF){
    buffer[lcounter] = c;
    if(c == '\n'){
      state = OUT;
    }
    else if(state == OUT){
      wps[wcounter++] = &buffer[lcounter];
      state = IN;
    }
    lcounter++;
  }
  fclose(fp);
  /* get pointers to the words I'll be guessing */
  ii = 0;
  int holder[reps];
  int good, hcounter;
  hcounter = 0;
  while(ri > 0){
      r = rand() % wcounter + 1;
      for(i = 0, good = 1; i < hcounter; i++){
	if(r == holder[i]){
	  good = 0;
	}
      }
      if(good){
	holder[hcounter++] = r;
        wordbin[ii++] = wps[r];
        ri--;
      }
  }
  /* print them to the console */
  printf("\n");
  for(i = 0, li = 0; i < ii; i++){
    while((letter = *(wordbin[i] + li)) != '\n'){
      wordholder[i][li] = letter;
      word[li] = letter;
      li++;
    }
    word[li] = wordholder[i][li] = '\0';
    printwords(word);
    printf("\n");
    li = 0;
  }
  wordholder_max = i;
  /* After giving time to study them, clear screen */
  sleep(sec);
  system("clear");
  /* get the guesses */

  /* todo *********************************
   * use wordholder to test that          *
   * a word isn't guessed twice           *
   ***************************************/

  printf("\nGuess the %d words\npress enter after each word\n\n", reps);
  int guess[reps * 20];
  for(i = ii = 0, c = '0'; i < reps; i++){
    for(gcounter = 0; (c = getchar()) != '\n'; gcounter++){
      guess[ii++] = c;
    }
    guess[ii++] = '\n';
  }
  guess[ii] = -1;
  /* go through guess, chopping off each word for checking */
  for(right = i = ii = 0; guess[i] != -1; i++){
    if(guess[i] != '\n'){
      wrd[ii++] = guess[i];
    }
    if(guess[i] == '\n'){
      wrd[ii] = '\n';
      right += checker(wrd, wordbin, reps);
      ii = 0;
    }
  }
  /* End the game, if they get anything wrong, print the words again
     so they can compare */
  if(winner(right, reps)){
    printf("The correct words were:");
    printf("\n\033[1;31;40m");
    for(i = 0; i <= wordholder_max; i++){
      for(ii = 0; wordholder[i][ii] != '\0'; ii++){
	word[ii] = wordholder[i][ii];
      }
      word[ii] = '\0';
      printwords(word);
      printf("\n");
    }
    printf("\033[0;37;40m");
  }
  return 0;
}

int checker(int *wrd, int **wordbin, int reps)
{
  int i, ii;
  for(i = 0; i < reps; i++){
    for(ii = 0; wordbin[i][ii] != '\n' && wrd[ii] != '\n' && wordbin[i][ii] == wrd[ii]; ii++){
      if(wordbin[i][ii+1] == '\n' && wrd[ii+1] == '\n'){
	return 1;
      }
    }
  }
  return(EXIT_SUCCESS);
}

int winner(int right, int reps)
{
 if(right == reps){
    printf("\n\t\033[1;31;40mHURRAY!!!  \033[0;37;40mYou got them all right\n\n");
    return 0;
  }
  else if(right == 0){
    printf("\n\tYou got none, try a little harder next time\n\n");
  }
  else{
    printf("\n\tYou got %d right\n\n", right);
  }
 return 1;
}

void printhelp(int reps)
{
  printf("\n\t\033[1;31;40mPlay a memory game to help your grey matter\n\n");
  printf(" \033[0;37;40mYou can simply run the program to get %d words to guess,\n", reps);
  printf(" or you can enter a value between 1 and 100 to play that many guesses.\n");
  printf(" You'll have a few seconds to study the words, trying to remember each one.\n");
  printf(" Then the console will clear and you must try to type each of the words.\n\n");
  printf(" After typing in each word, hit enter.\n");
  printf("\n \033[1;31;40mEnjoy the game!!!\033[0;37;40m\n\n");
}

void printwords(int word[MLW])
{
  int i;
  for (i = 0; word[i] != '\0'; i++){
    printf("%c", word[i]);
  }
}
