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
int canPlay(struct Spell *spellMap[], int tally[], char *prev);
int isLegal(struct Spell *spellMap[], int tally[], char *prev, char *word, int round);

#endif // SPELLMAP_H
