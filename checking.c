#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "spellmap.c"

// returns 1 if player has at least one spell he can play (check tally)
// returns 0 if the player is out of option (loses)
// takes the string of the previous spell played
// NOT checked on first turn of first player (when last is NULL, return 1)
int canPlay(struct Spell * spellMap[], int tally[], char * last){
    
}

// returns 1 if     1) the first character of played matches last
//                  2) played is within the available spells
//                  3) the spell was not used before (used=0)
// OTHERWISE the player loses
//      return -1 if        condition (1) was not satisfied
//      return -2 if        condition (2) was not satisfied
//      return -3 if        condition (3) was not satisfied
// if spell is legal, set used to 1 (true), and update tally
int isLegal(struct Spell * spellMap[], int tally[], char * last, char * played){

}


