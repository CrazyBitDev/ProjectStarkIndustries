//SO - Windows
#ifdef _WIN32
    #include <windows.h>
    //PROMEMORIA: SetConsoleTextAttribute(hConsole, 12); colore rosso
#endif

//SO - MacOS
#ifdef __APPLE__
    #define ANSI_COLOR_RED     "\x1b[31m"
    #define ANSI_COLOR_RESET   "\x1b[0m"
#endif

//librerie generali
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "utente.h"
#include "prenotazione.h"

int main() {
    /*
    struct utente *testa = NULL;
    struct utente *nuovoNodo;
    
    nuovoNodo = (struct utente*)malloc(sizeof(struct utente));
    
    testa = registrazione(testa);
    */
    
    printf("\n");
    return 0;
}
