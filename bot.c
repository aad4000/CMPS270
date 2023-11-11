#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "checking.c"

struct Option{
    char * word;
    char character; //last character
    int tally; //tally of last character
    int taken; //whether it has been used or not in the array
};

char* playEasy(struct Spell * spellMap[], int tally[], char * prev){
    tally[prev[strlen(prev) - 1]]--; //because we know the word to be played will start with this character

    struct Option options[26]; //we will have at most 26 words to choose from, each ending with a different character
    for(int i = 0; i < 26; i++)
        options[i].taken = 0;

    int index = prev[strlen(prev) - 1] - 'a';
    struct Spell *current = spellMap[index];
    while(current != NULL){
        if(current->used == 0){ //skip if word is not an option (cannot be played because was already played before)
            char lastCharacter = current->last;
            int index2 = lastCharacter - 'a';
            if(tally[index2] == 0)
                return current->name;
            else{
                if(options[index2].taken == 0){
                    options[index2].taken = 1;
                    options[index2].word = current->name;
                    options[index2].character = current->last;
                    options[index2].tally = tally[index2];
                }
            }
        }
        current = current->next;
    }

    struct Option optionsSorted[26]; //sort according to tally
    int usedEntries = 26; //how many entries of sorted array are actually used
    for(int i = 0; i < 26; i++){
        int max = -1;
        int maxIndex = -1;
        for(int j = 0; j < 26; j++){
            if(options[j].taken == 1){
                if(options[j].tally > max){
                    max = options[j].tally;
                    maxIndex = j;
                }
            }
        }
        if(max > -1){
            optionsSorted[i] = options[maxIndex];
            options[maxIndex].taken = 0; //so that we don't check it again
        }
        else{ // we have the complete sorted array
            usedEntries = i; //we dont need to check the remaining elements later
            break;
        }
    }

    for(int i = 0; i < usedEntries; i++){
        int index2 = optionsSorted[i].character - 'a';
        struct Spell *current = spellMap[index2];
        int canLose = 0; //1 means i CAN lose on the next turn immediately, 0 means my move is safe
        while(current != NULL){
            if(current->used == 0){ 
                if(tally[current->last-'a'] == 0) //opponent has a winning move
                    canLose = 1;
                    break;
            }
            current = current->next;
        }
        if(canLose == 0)
            return options[i].word;
    }
}