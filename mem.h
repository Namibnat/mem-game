#define FW "./words"                                /* where to get the word file */
#define FM 70000                                    /* max number of pointers to words */
#define MREPS 100                                   /* max words that can be in the list of words to guess */
#define MLW 25                                      /* max length of a word, when I chop them off guess[] for comparison */
#define IN 1                                        /* state - in a word */
#define OUT 0                                       /* state - out of a word */
#define BUF 1000000                                 /* big buffer to read the file into as one long char array */
#define DEFREPS 2                                   /* default number of reps */
