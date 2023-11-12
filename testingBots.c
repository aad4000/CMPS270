/*
This is for testing the bots of different difficulties against the random bot
to validate that they perform better than random.
The results of our tests are at the end of the report.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bot.c"
#include "checking.c"
#include "spellmap.c"
#include <time.h>

int main(){

    int DIFFICULTY = 3; //0 is random, 1 is easy, 2 is medium, 3 is hard, ...

    int RandomWins = 0;
    int LostByNoMoreMoves = 0;
    int LostByIllegalMoveWordUnavailable = 0;
    int LostByIllegalMoveWordAlreadyUsed = 0;
    int LostByIllegalMoveWordsDoNotMatch = 0;
    int BotWins = 0;
    int WonByNoMoreMoves = 0;
    int WonByIllegalMoveWordUnavailable = 0;
    int WonByIllegalMoveWordAlreadyUsed = 0;
    int WonByIllegalMoveWordsDoNotMatch = 0;
    int TotalGames = 100;
    srand(time(NULL));
    int coin = rand()%2; // 0 for player 1, and 1 for player 2 (bot);

    for(int g = 0; g < TotalGames; g++){
        struct Spell * spellMap[26]; //array of 26 linked lists of spells, each entry starting with a certain letter
        int tally[26]; //keeps track of how many spells we have starting with each letter which are playable (not used yet)
        for(int i = 0; i < 26; i++){
            spellMap[i] = NULL;
            tally[i] = 0;
        }
        readSpells(spellMap, tally, "spells.txt");
        // reads from file all spells, and places them in the array accoridng to first letter
        // also prints the spells as desired.

        coin = (coin + 1) %2;

        int c = 0; //counter for how many turns have been played
        char * prev = (char *) malloc(30 * sizeof(char)); //assuming 30 is largest 

        while(1){

            int turn = ((c + coin) % 2); //calculates whose turn it is: 0 for player 1, 1 for player 2.

            if(!canPlay(tally, prev) && c!=0){
                //Player loses because he has no more possible moves.
                char * winner, *loser;
                if(turn == 0){
                    BotWins++;
                    WonByNoMoreMoves++;
                }
                else{
                    RandomWins++;
                    LostByNoMoreMoves++;
                }
                break;
            }
            char word [30]; //again, assuming longest word is of 30 characters
            if(turn == 0){
                if(c > 0){
                    playBot(spellMap, tally, prev, 0, word);
                }
                else{
                    for(char i = 'a'; i <= 'z'; i++){
                        if(tally[i-'a'] != 0){
                            char str[] = {i, '\0'};
                            if(playBot(spellMap, tally, str, 0, word) != -1){ //choose a word which does not make you lose 
                                break;
                            }
                        }
                    }
                }            
            }
            else {
                if(c > 0){
                    playBot(spellMap, tally, prev, DIFFICULTY, word);
                }
                else{
                    for(char i = 'a'; i <= 'z'; i++){
                        if(tally[i-'a'] != 0){
                            char str[] = {i, '\0'};
                            if(playBot(spellMap, tally, str, DIFFICULTY, word) != -1){ //choose a word which does not make you lose 
                                break;
                            }
                        }
                    }
                }            
            }

            int t = isLegal(spellMap, tally, prev, word, c);
            if(t < 0){
                //Player loses for one of 3 reasons according to return value
                char * winner, *loser;
                if(turn == 0){
                    BotWins++;
                    if(t == -1)
                        WonByIllegalMoveWordsDoNotMatch++;
                    else if(t == -2)
                        WonByIllegalMoveWordUnavailable++;
                    else 
                        WonByIllegalMoveWordAlreadyUsed++;
                    
                }
                else{
                    RandomWins++;
                    if(t == -1)
                        LostByIllegalMoveWordsDoNotMatch++;
                    else if(t == -2)
                        LostByIllegalMoveWordUnavailable++;
                    else
                        LostByIllegalMoveWordAlreadyUsed++;
                }
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

    }
    printf("\nTotal Number Of Games: %d\nWon By Random Bot: %d\nWon By Difficulty %d Bot: %d\n\nWon By No More Moves: %d\nWon By No Such Word: %d\nWon By Does Not Match: %d\nWon By Already Used: %d\n\nLost By No More Moves: %d\nLost By No Such Word: %d\nLost By Does Not Match: %d\nLost By Already Used: %d\n\n%d", TotalGames, RandomWins, DIFFICULTY, BotWins, WonByNoMoreMoves, WonByIllegalMoveWordUnavailable, WonByIllegalMoveWordsDoNotMatch, WonByIllegalMoveWordAlreadyUsed, LostByNoMoreMoves, LostByIllegalMoveWordUnavailable, LostByIllegalMoveWordsDoNotMatch, LostByIllegalMoveWordAlreadyUsed, 0);


    return 0;
}