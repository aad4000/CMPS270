#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "spellmap.h"

void addToMap(struct Spell * spellMap[], struct Spell *node){
    int index = node->first - 'a'; // will return index in the array.

    if(spellMap[index] == NULL) 
        spellMap[index] = node;
    else {
        struct Spell *current = spellMap[index];
        while(current->next != NULL)
            current = current->next;
        current->next = node;
        
    }
}


void readSpells(struct Spell * spellMap[], int tally[], const char * filename){
    FILE *file = fopen(filename, "r");
    
    int numberOfSpells;                                                                                         
    fscanf(file, "%d", &numberOfSpells);
    
    for(int i = 0; i < numberOfSpells; i++){
        struct Spell *current = (struct Spell*)malloc(sizeof(struct Spell));
        
        current->name = (char *) malloc( 30 * sizeof(char)); //assuming largest is 30
        fscanf(file, "%s", current->name);

        printf("%s\t\t\t", current->name);
        if(i % 5 == 4) //new line every 5 words printed
            printf("\n");

        current->first = current->name[0];
        current->last = current->name[strlen(current->name)-1];
        current->next = NULL;
        current->used = 0; //inititally unused

        tally[current->first - 'a']++; //update tally

        addToMap(spellMap, current);

    }

    fclose(file);
};




