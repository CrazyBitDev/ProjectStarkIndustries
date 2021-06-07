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
#include <ctype.h>


#include "functions.h"
#include "utente.h"
#include "prenotazione.h"
/*#include "opera.h"*/

void titolo(void);

int main() {
    
    titolo();
  
    int scelta, scelta2, colonna = 0;
    char email[60], buf[DIM];
    
    Utente *testaUtente = NULL;
    Utente *utenteLogin = NULL; //utente che avrà eseguito il login
    Utente* tempUtente = NULL; //temporanea
    Utente *tempUtente1 = NULL;
    
    //Lettura utenti dal file
    FILE *fpU;
    fpU = fopen("/Users/dan/Documents/OneDrive - Università degli Studi di Bari/I anno/Secondo Semestre/Laboratorio/Caso di studio/home/utenti.csv", "r");
    
    if(fpU == NULL) {
        printColor("File \"utenti\" non trovato!\n", COLOR_RED);
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
        
        printf("---HOME---\n");
        printf("1: Registrazione\n");
        printf("2: Login\n");
        printf("0: Esci\n");
        scanf("%d", &scelta);
        printf("\n");

        switch (scelta) {
            case 1:
                printColor("Benvenuto! \nCrea il tuo account\n", COLOR_CYAN);
                testaUtente = registrazioneUtente(testaUtente);
                break;
                
            case 2:
                while('\n'!=getchar());
                
                printf("Email: ");
                fgets(email, 60, stdin);
                email[strlen(email)-1]=0;
                
                utenteLogin = accesso(testaUtente, email);
                char *valore = (char *)utenteLogin;
                
                if(valore != NULL) {
                    printColor("Benvenuto nella sezione privata del tuo account\n", COLOR_CYAN);
                    //Operazioni che può effettuare l'utente una volta che ha eseguito il login
                    do {
                        printf("---MENU'---\n");
                        printf("1: Visualizza informazioni personali\n");
                        printf("2: Modifica dati personali\n");
                        printf("0: Esci\n");
                        scanf("%d", &scelta2);
                        printf("\n");

                        switch (scelta2) {
                            case 1:
                                printColor("Elenco dati personali\n", COLOR_CYAN);
                                stampaUtente(utenteLogin);
                                break;

                            case 2:
                                testaUtente = modificaUtente(utenteLogin);
                                break;

                            default:
                                break;
                        }

                    } while (scelta2 != 0);
                }
                break;
                
            default:
                break;
        }

        printColor("-----------------------------\n", COLOR_CYAN);

    } while(scelta != 0);
    
    
    
    printf("\n");
    return 0;
}

void titolo() {
    
    printf("\n");
    /*
     * @dani-el92 utilizza questo sito per generare il testo, purtroppo deve essere ASCII per evitare problemi
     * Nel caso c'è un \ nel testo, utilizza \\
    */
    consoleColor(COLOR_CYAN);
    /*printf("███████╗████████╗ █████╗ ██████╗ ██╗  ██╗    ██╗███╗   ██╗██████╗ ██╗   ██╗███████╗████████╗██████╗ ██╗███████╗███████╗\n");
    printf("██╔════╝╚══██╔══╝██╔══██╗██╔══██╗██║ ██╔╝    ██║████╗  ██║██╔══██╗██║   ██║██╔════╝╚══██╔══╝██╔══██╗██║██╔════╝██╔════╝\n");
    printf("███████╗   ██║   ███████║██████╔╝█████╔╝     ██║██╔██╗ ██║██║  ██║██║   ██║███████╗   ██║   ██████╔╝██║█████╗  ███████╗\n");
    printf("╚════██║   ██║   ██╔══██║██╔══██╗██╔═██╗     ██║██║╚██╗██║██║  ██║██║   ██║╚════██║   ██║   ██╔══██╗██║██╔══╝  ╚════██║\n");
    printf("███████║   ██║   ██║  ██║██║  ██║██║  ██╗    ██║██║ ╚████║██████╔╝╚██████╔╝███████║   ██║   ██║  ██║██║███████╗███████║\n");
    printf("╚══════╝   ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝    ╚═╝╚═╝  ╚═══╝╚═════╝  ╚═════╝ ╚══════╝   ╚═╝   ╚═╝  ╚═╝╚═╝╚══════╝╚══════╝\n");*/
    printf("   _____ _             _      _____           _           _        _           \n");
    printf("  / ____| |           | |    |_   _|         | |         | |      (_)          \n");
    printf(" | (___ | |_ __ _ _ __| | __   | |  _ __   __| |_   _ ___| |_ _ __ _  ___  ___ \n");
    printf("  \\___ \\| __/ _` | '__| |/ /   | | | '_ \\ / _` | | | / __| __| '__| |/ _ \\/ __|\n");
    printf("  ____) | || (_| | |  |   <   _| |_| | | | (_| | |_| \\__ \\ |_| |  | |  __/\\__ \\\n");
    printf(" |_____/ \\__\\__,_|_|  |_|\\_\\ |_____|_| |_|\\__,_|\\__,_|___/\\__|_|  |_|\\___||___/\n");
    consoleColor(COLOR_RESET);
    
    printf("\n");
}