#ifndef SPELLMAP_H
#define SPELLMAP_H

// Structure definition for Spell
struct Spell {
    char *name;
    char first; // first letter of spell
    char last;  // last letter of spell
    int used;   // 0 if false, 1 if true
    struct Spell *next;
};

// Function prototypes
void addToMap(struct Spell *spellMap[], struct Spell *node);
void readSpells(struct Spell *spellMap[], int tally[], const char *filename);
int canPlay(int tally[], char *previousWord);
int isLegal(struct Spell *spellMap[], int tally[], char *previousWord, char *currentWord, int round);

#endif // SPELLMAP_H
