#include <stdio.h>
#include <stdlib.h>
#include "spellmap.h"


// returns 1 if player has at least one spell he can play
// returns 0 if the player is out of options (loses)
int canPlay(struct Spell * spellMap[], int tally[], char * last) {
    int index = last[strlen(last)-1] - 'a';

    if (tally[index] > 0) //there are still available words starting with the desired letter.
        return 1;

    return 0;
}


// returns 1 if     1) the first character of played matches last
//                  2) played is within the available spells
//                  3) the spell was not used before (used=0)
// OTHERWISE the player loses
//      return -1 if        condition (1) was not satisfied
//      return -2 if        condition (2) was not satisfied
//      return -3 if        condition (3) was not satisfied
// if spell is legal, set used to 1 (true), and update tally
int isLegal(struct Spell * spellMap[], int tally[], char * last, char * played, int round) {
    if(round != 0)
        if (last != NULL && played[0] != last[strlen(last) - 1]) { //check if letters match
            return -1;  
        }

    int index = played[0] - 'a';

    struct Spell *current = spellMap[index];
    while (current != NULL) {
        if (strcmp(current->name, played) == 0) { //look for the word
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


