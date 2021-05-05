//SO - Windows
#ifdef _WIN32
    #include <windows.h>
    //PROMEMORIA: SetConsoleTextAttribute(hConsole, 10); colore rosso
#endif

//SO - MacOS
#ifdef __APPLE__
    #define ANSI_COLOR_RED     "\x1b[31m"
    #define ANSI_COLOR_RESET   "\x1b[0m"
#endif

//librerie generali
#include <stdio.h>
#include <stdlib.h>
#include "utente.h"
#include "prenotazione.h"

int main() {
    
    
    
    printf("\n");
    return 0;
}
