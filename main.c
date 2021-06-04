#define DIM 50
//SO - Windows
#ifdef _WIN32
    #include <windows.h>
    //PROMEMORIA: SetConsoleTextAttribute(hConsole, 12); colore rosso
#else //macOS - Linux
    #define ANSI_COLOR_RED     "\x1b[91m"
    #define ANSI_COLOR_GREEN   "\x1b[92m"
    #define ANSI_COLOR_RESET   "\x1b[0m"
    #define ANSI_COLOR_CYAN    "\x1b[96m"
#endif

//librerie generali
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>

#include "utente.h"
#include "prenotazione.h"


int main() {
    int scelta, colonna = 0;
    char email[60], buf[DIM];
    
    Utente *testaUtente = NULL;
    Utente *testaUtente1 = NULL;
    Utente* tempUtente = NULL; //temporanea
    Utente *tempUtente1 = NULL;
    
    //Lettura utenti dal file - renderla una funzione (?)
    FILE *fpU;
    fpU = fopen("/Users/dan/Documents/OneDrive - Università degli Studi di Bari/I anno/Secondo Semestre/Laboratorio/Caso di studio/home/utenti.csv", "r");
    
    if(fpU == NULL) {
        #ifdef _WIN32
            HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 12);
            printf("File \"utenti\" non trovato!\n");
            SetConsoleTextAttribute(hConsole, 15);
        #else
            printf(ANSI_COLOR_RED "File \"utenti\" non trovato!\n" ANSI_COLOR_RESET "\n");
        #endif
    } else {
        while (!feof(fpU)) {
            fgets(buf, BUFFER_SIZE, fpU);
            tempUtente = (struct utente*)malloc(sizeof(struct utente));
            
            if(tempUtente1 != NULL) {
                tempUtente1 -> nextUtente = tempUtente;
            } else {
                testaUtente = tempUtente;
            }
            
            char *tok;
            tok = strtok(buf, ",");
            
            while(tok) {
                if(colonna == 0){
                    tempUtente -> id = atoi(tok);
                }
                if(colonna == 1){
                    strcpy(tempUtente -> nome, tok);
                    tempUtente -> nome[strlen(tempUtente -> nome)] = 0;
                }
                if(colonna == 2){
                    strcpy(tempUtente -> cognome, tok);
                    tempUtente -> cognome[strlen(tempUtente -> cognome)] = 0;
                }
                if(colonna == 3){
                    strcpy(tempUtente -> email, tok);
                    tempUtente -> email[strlen(tempUtente -> email)] = 0;
                }
                if(colonna == 4){
                    strcpy(tempUtente -> password, tok);
                    tempUtente -> password[strlen(tempUtente -> password)] = 0;
                }
                if(colonna == 5){
                    strcpy(tempUtente -> dataNascita, tok);
                    tempUtente -> dataNascita[strlen(tempUtente -> dataNascita)] = 0;
                }
                if(colonna == 6){
                    tempUtente -> permessi = atoi(tok);
                }
                tok = strtok(NULL, ",");
                colonna++;
            }
            colonna = 0;
            tempUtente1 = tempUtente;
            
        }
    }
    
    
    do {
        
        printf("---MENU' TEMPORANEO---\n");
        printf("1: Registrazione\n");
        printf("2: Login\n");
        printf("0: Esci\n");
        scanf("%d", &scelta);
        
        switch (scelta) {
            case 1:
                testaUtente = registrazione(testaUtente);
                break;
                
            case 2:
                while('\n'!=getchar());
                
                printf("Email: ");
                fgets(email, 60, stdin);
                email[strlen(email)-1]=0;
                
                testaUtente1 = accesso(testaUtente, email);
                char *valore = (char *)testaUtente1;
                
                if(valore != NULL) {
                    printf("---Informazioni utente prova---\n");
                    stampa(testaUtente1);
                    printf("-------------------------------\n");
                }
                
                break;
                
            default:
                break;
        }
        
        
    } while(scelta != 0);
    
    
    
    
    printf("\n");
    return 0;
}
