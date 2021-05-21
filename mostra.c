#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>

//Gestione Mostre
#define ID 1
#define BUFFER_SIZE 1024
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"

//Definizione struct mostre
struct mostre {
    int id;
    char citta[20];
    char indirizzo[30];
    char dataInizio[10];
    char dataFine[10];
    int nOpere; // Numero opere
    int permessi; //livello 1 = utente normale; livello 2 = direttore generale, ha accesso a tutto;
    struct mostre *nextMostra; //puntatore al prossimo nodo
}mostre;

struct mostre* aggiungiMostra(struct mostre* testa){
    struct mostre *nuovoNodo=NULL;

    nuovoNodo = (struct mostre*)malloc(sizeof(struct mostre));
    
    FILE *fp;
     fp = fopen("mostre.csv", "a+"); //apertura file

    printf("Inserisci Città: ");
    fgets(nuovoNodo -> citta, 20, stdin);
    nuovoNodo -> citta[strlen(nuovoNodo -> citta)-1] = 0;
    printf("\n");
    
    printf("Inserisci Indirizzo: ");
    fgets(nuovoNodo -> indirizzo, 20, stdin);
    nuovoNodo -> indirizzo[strlen(nuovoNodo -> indirizzo)-1] = 0;
    printf("\n");
    
    printf("Inserisci Data Inizio (non ti dimenticare di separarli con /): \n");
    fgets(nuovoNodo -> dataInizio, 60, stdin);
    nuovoNodo -> dataInizio[strlen(nuovoNodo -> dataInizio)-1] = 0;

    //verifico che sia stata inserita la /
    char *ptr;
    char *a = "/";
    ptr = strstr(nuovoNodo -> dataInizio, a);
        
    while(ptr == NULL) {
        #ifdef _WIN32
            HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 12);
            printf("Attenzione! L'email inserita non e' corretta\n");
            SetConsoleTextAttribute(hConsole, 15);
        #else
            printf(ANSI_COLOR_RED "Attenzione! L'email inserita non e' corretta\n" ANSI_COLOR_RESET "\n");
        #endif
           
        
        printf("Inserisci Data Inizio (non ti dimenticare di separarli con /): \n");
        fgets(nuovoNodo -> dataInizio, 60, stdin);
        nuovoNodo -> dataInizio[strlen(nuovoNodo -> dataInizio)-1] = 0;
        ptr = strstr(nuovoNodo -> dataInizio, a);
    }
    printf("\n");

    printf("Inserisci Data Fine (non ti dimenticare di separarli con /): \n");
    fgets(nuovoNodo -> dataFine, 60, stdin);
    nuovoNodo -> dataFine[strlen(nuovoNodo -> dataFine)-1] = 0;

    //verifico che sia stata inserita la /
    char *ptr2;
    char *a = "/";
    ptr = strstr(nuovoNodo -> dataInizio, a);
        
    while(ptr == NULL) {
        #ifdef _WIN32
            HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 12);
            printf("Attenzione! L'email inserita non e' corretta\n");
            SetConsoleTextAttribute(hConsole, 15);
        #else
            printf(ANSI_COLOR_RED "Attenzione! L'email inserita non e' corretta\n" ANSI_COLOR_RESET "\n");
        #endif
           
        
        printf("Inserisci Data Fine (non ti dimenticare di separarli con /): \n");
        fgets(nuovoNodo -> dataFine, 60, stdin);
        nuovoNodo -> dataFine[strlen(nuovoNodo -> dataFine)-1] = 0;
        ptr2 = strstr(nuovoNodo -> dataFine, a);
    }
    printf("\n");

    printf("Inserisci Il Numero delle Opere: ");
    fgets(nuovoNodo -> nOpere,stdin);
    nuovoNodo -> nOpere[strlen(nuovoNodo -> nOpere)-1] = 0;
    printf("\n");
}

