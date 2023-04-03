#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "io.h"

    //   která čte jedno slovo ze souboru f do zadaného pole znaků
    //   a vrátí délku slova (z delších slov načte prvních max-1 znaků,
    //   a zbytek přeskočí). Funkce vrací EOF, pokud je konec souboru.
    //   Umístěte ji do zvláštního modulu "io.c" (nepatří do knihovny).
    //   Poznámka: Slovo je souvislá posloupnost znaků oddělená isspace znaky.

    // Omezení: řešení v C bude tisknout jinak uspořádaný výstup
    //   a je povoleno použít implementační limit na maximální
    //   délku slova (např. 255 znaků), delší slova se ZKRÁTÍ a program
    //   při prvním delším slovu vytiskne varování na stderr (max 1 varování).

int read_word(char *s, int max, FILE *f) {

    int c;

    // Read all white space chars before some word
    while ((c = getc(f)) != EOF && isspace(c)) ;

    // Check if file is at the end
    if (c == EOF) {
        return EOF;
    }

    // First character is already read, so we store him
    s[0] = c;

    int length = 1;
    // Read chars until EOF or white space char
    while ((c = getc(f)) != EOF && !isspace(c)) {
        s[length++] = c;
        
        if (length == max - 1) {
            s[length] = '\0';

            // Skip rest of the word
            while ((c = getc(f)) != EOF && !isspace(c)) ;
            return strlen(s);
        }
    }

    s[length] = '\0';

    return strlen(s);

}