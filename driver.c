#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "checking.c"
#include <time.h>

int main(){

    char player1 [100];
    char player2 [100];
    // assuming the names do not exceed 100 characters

    printf("Player 1, enter your name: ");
    scanf("%s", player1);
    printf("Player 2, enter your name: ");
    scanf("%s", player2);

    int n;
    struct Spell * spellMap[26];
    int tally[26]; //keeps track of how many spells we have starting with each letter which are playable (not used yet)
    for(int i = 0; i < 26; i++){
        spellMap[i] = NULL;
        tally[i] = 0;
    }

    readSpells(spellMap, tally, "spells.txt", &n);


    srand(time(NULL));
    int coin = rand()%2; // 0 for player 1, and 1 for player 2

    int c = 0;
    char * prev = (char *) malloc(18 * sizeof(char));

    while(1){
        int turn = ((c + coin) % 2);

        if(!canPlay(spellMap, tally, prev) && c!=0){
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
        
        char word [18]; //again, assuming longest word is of 18 characters
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

        strcpy(prev, word);
        c++;
    }



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