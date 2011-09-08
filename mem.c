/* ************************************************************************
*                                                                         *
*   Play a memory game to sharpen the pip                                 *
*                                                                         *
*   Copyright (C) 2011 by Vernon Swanepoel                                *
*   vernon@sandcurves.com                                                 *
*                                                                         *
*   This program is free software; you can redistribute it and/or modify  *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation; either version 2 of the License, or     *
*   (at your option) any later version.                                   *
*                                                                         *
*   This program is distributed in the hope that it will be useful,       *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
*   GNU General Public License for more details.                          *
*                                                                         *
*   You should have received a copy of the GNU General Public License     *
*   along with this program; if not, write to the                         *
*   Free Software Foundation, Inc.,                                       *
*   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
*                                                                         *
***************************************************************************/

#include <stdio.h>
#include <ctype.h>                                  /* for isdigit and isalnum */
#include <stdlib.h>                                 /* for rand() */
#include <time.h>
#include <unistd.h>                                 /* for sleep() */
#include "mem.h"
int checker(int *wrd, int **wordbin, int reps);     /* check word by word how many are right */
void winner(int right, int reps);                   /* print results */
void printhelp(int reps);
int main(int argc, char *argv[])
{
  srand(time(NULL));
  FILE *fp;                                         /* file pointer to file with the words */
  int i, ii, li, ri, c, letter, reps, state;        /* i & ii - general iterator
                                                       ri - iterator for getting the right num of words
                                                       li - letter iterator
                                                       c - for character collecting while reading the file
                                                       letter - to rep letter
                                                       reps - repetitions, i.e. how many words does the user wants to play with
                                                       state - in or out of a word
					            */
  int right, r, sec;                                /* right - for guessing, when it is right
                                                       r - for rand()
                                                       sec - seconds to sleep
                                                    */
  int lcounter, wcounter, gcounter;                 /* lcounter - counting characters (l for letters)
                                                       wcounter - word counter
                                                       gcounter - counter while guessing
						    */
  int *wps[FM], *wordbin[MREPS], wrd[MLW];          /* wps - pointer to each word 
                                                       wordbin - the holder for the words we're playing with
                                                       wrd - while checking each guess, holds the word we're checking
                                                       guess - an array defined further down for holding the guesses.
                                                               defined later because we want the number of reps
						    */
  int buffer[BUF];                                  /* The buffer for the word file */
  state = OUT;
  /* clear the console to start the game */
  system("clear");
  /* get args, set reps */
  if(argc > 1 && argv[1][0] == 'h'){
    printhelp(DEFREPS);
    return(EXIT_SUCCESS) ;
  }
  if(argc > 1 && isdigit(argv[1][0])){
    reps = argv[1][0] - '0';
    if(isdigit(argv[1][1])){
      reps = (reps * 10) + (argv[1][0] - '0');
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
      printf("%c", letter);
      li++;
    }
    printf("\n");
    li = 0;
  }
  /* After giving time to study them, clear screen */
  sleep(sec);
  system("clear");
  /* get the guesses */
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
  winner(right, reps);
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
void winner(int right, int reps)
{
 if(right == reps){
    printf("\n\t\033[1;31;40mHURRAY!!!  \033[0;37;40mYou got them all right\n\n");
  }
  else if(right == 0){
    printf("\n\tYou got none, try a little harder next time\n\n");
  }
  else{
    printf("\n\tYou got %d right\n\n", right);
  }
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
