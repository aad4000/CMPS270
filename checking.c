#include <stdio.h>
#include <stdlib.h>
#include "spellmap.h"


int canPlay(int tally[], char * previousWord) {                                                
    int index = previousWord[strlen(previousWord)-1] - 'a';

    if (tally[index] > 0) //there are still available words starting with the desired letter.
        return 1;

    return 0;
}


int isLegal(struct Spell * spellMap[], int tally[], char * previousWord, char * currentWord, int round) {                       
    if(round != 0)
        if (previousWord != NULL && currentWord[0] != previousWord[strlen(previousWord) - 1]) { //check if letters match
            return -1;  
        }

    int index = currentWord[0] - 'a';

    struct Spell *current = spellMap[index];
    while (current != NULL) {
        if (strcmp(current->name, currentWord) == 0) { //look for the word
            if(current->used == 0){ //if it is found, check that is it not used, and update tally and used.
                current->used = 1;
                tally[index]--;
                return 1;
            }
            else
                return -3;
        }
        current = current->next;
    }

    //word was not found
    return -2;
}


