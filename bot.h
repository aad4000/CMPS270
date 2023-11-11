#ifndef BOT_H
#define BOT_H

#include "spellmap.h" // Assuming spellmap.h contains the definition of struct Spell

int playBot(struct Spell *spellMap[], int tally[], char *prev, int difficulty, char *word);

#endif // BOT_H
