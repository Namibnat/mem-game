# Play a memory game to sharpen the pip

The game is part of a series of programs I'm
writing to serve the duel purpose of sharpening
my mind and helping me to learn the C programming
language.

To play, run the program from a linux console.
The optional argument is a number between
1 and 100, for the number of words to guess.

The word list was taken from /usr/share/dict/american-english
and just cleaned up a bit.  A better wordlist could
improve the game a lot, especially if you wanted to
use if for kids.

In play:
The console will display the words, selected
at random.  You have a total of five seconds times
the number of words to study the words.

The console will clear and you can then enter your guesses.
After each guess, hit enter until you've guessed the
right number of words.

The computer will let you know how many you got right.

Edit it:
If you want to move the 'words' file
or alternatively use your own, just edit
the first line of the mem.h file to give
the path to your words file

Build it:
$ make

Run it:
$ ./mem

