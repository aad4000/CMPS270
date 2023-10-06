#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Spell{
    char * name;

    char first;
    char last;

    struct Spell * next;
};

void addToMap(struct Spell * spellMap[], struct Spell *node){
    int index = node->first - 'a'; // will return index in array.
    
    if(spellMap[index] == NULL)
        spellMap[index] = node;
    else {
        struct Spell *current = spellMap[index];
        while(current->next != NULL)
            current = current->next;
        current->next = node;
    }
}

void readSpells(struct Spell * spellMap[], const char * filename, int *n){
    FILE *file = fopen(filename, "r");
    
    
    fscanf(file, "%d", n);

    for(int i = 0; i < *n; i++){
        struct Spell *current = (struct Spell*)malloc(sizeof(struct Spell));
        
        current->name = (char *) malloc( 18 * sizeof(char)); //assuming largest is 18
        fscanf(file, "%s", current->name);

        current->first = current->name[0];
        current->last = current->name[strlen(current->name)-1];

        addToMap(spellMap, current);
    }

    fclose(file);
};




int main(){
    int n;
    struct Spell * spellMap[26];

    readSpells(spellMap, "spells.txt", &n);


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
