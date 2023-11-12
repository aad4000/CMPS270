#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "checking.c"

int main(){

    char player1 [20];
    char player2 [20];
    // assuming the names do not exceed 20 characters

    printf("Player 1, enter your name: ");
    scanf("%s", player1);
    printf("Player 2, enter your name: ");
    scanf("%s", player2);

    struct Spell * spellMap[26]; //array of 26 linked lists of spells, each entry starting with a certain letter
    int tally[26]; //keeps track of how many spells we have starting with each letter which are playable (not used yet)
    for(int i = 0; i < 26; i++){
        spellMap[i] = NULL;
        tally[i] = 0;
    }

    readSpells(spellMap, tally, "spells.txt");
    // reads from file all spells, and places them in the array accoridng to first letter
    // also prints the spells as desired.

    srand(time(NULL));
    int coin = rand()%2; // 0 for player 1, and 1 for player 2

    int c = 0; //counter for how many turns have been played
    char * prev = (char *) malloc(30 * sizeof(char)); //assuming 30 is largest

    while(1){
        int turn = ((c + coin) % 2); //calculates whose turn it is: 0 for player 1, 1 for player 2.

        if(!canPlay(tally, prev) && c!=0){
            //Player loses because he has no more possible moves.
            char * winner, *loser;
            if(turn == 0){
                winner = player2;
                loser = player1;
            }
            else{
                winner = player1;
                loser = player2;
            }
            printf("\n%s lost because there are no more possible moves.\n%s is the winner!", loser, winner);
            break;
        }

        if(turn == 0)
            printf("\n%s's turn. Enter a spell: ", player1);
        else 
            printf("\n%s's turn. Enter a spell: ", player2);
        
        char word [30]; //again, assuming longest word is of 30 characters
        scanf("%s", word);

        int t = isLegal(spellMap, tally, prev, word, c);
        if(t < 0){
            //Player loses for one of 3 reasons according to return value
            char * winner, *loser;
            if(turn == 0){
                winner = player2;
                loser = player1;
            }
            else{
                winner = player1;
                loser = player2;
            }

            if(t == -1)
                printf("\n%s lost because the first letter does not match the last letter of the previous spell.\n%s is the winner!", loser, winner);
            else if(t == -2)
                printf("\n%s lost because the spell used is not on the list.\n%s is the winner!", loser, winner);
            else 
                printf("\n%s lost because the spelled used was previously used.\n%s is the winner!", loser, winner);

            break;
        }

        strcpy(prev, word); //store copy of word in prev to check conditions next turn
        c++;
    }


    free(prev);
    for (int i = 0; i < 26; i++) {
        struct Spell *current = spellMap[i];
        while (current != NULL) {
            struct Spell *next = current->next;
            free(current->name);
            free(current);
            current = next;
        }
    }

    return 0;
}