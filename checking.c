#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "spellmap.c"

// returns 1 if player has at least one spell he can play (check tally)
// returns 0 if the player is out of option (loses)
// takes the string of the previous spell played
// NOT checked on first turn of first player 
int canPlay(struct Spell * spellMap[], int tally[], char * last) {


    // Get the index of the last letter in the tally array
    int index = last[strlen(last)-1] - 'a';

    // Check if there are spells starting with the last letter that haven't been used
    if (tally[index] > 0) 
        return 1;

    // The player is out of options (loses)
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
    // Check condition (1): the first character of played matches last
    if(round != 0)
        if (last != NULL && played[0] != last[strlen(last) - 1]) {
            return -1;  // Player loses because condition (1) was not satisfied
        }

    // Get the index of the first letter of played in the tally array
    int index = played[0] - 'a';

    // Check condition (3): the spell was not used before
    struct Spell *current = spellMap[index];
    while (current != NULL) {
        if (strcmp(current->name, played) == 0) {
            if(current->used == 0){
                // The spell is legal, set used to 1 (true), and update tally
                current->used = 1;
                tally[index]--;
                return 1;
            }
            else     // Check condition (2): played is within the available spells (checked later)
                return -3;
        }
        current = current->next;
    }

    // Player loses because condition (2) was not satisfied
    return -2;
}


