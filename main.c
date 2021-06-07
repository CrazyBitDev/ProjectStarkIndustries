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
#include <ctype.h>

#include "utente.h"
#include "prenotazione.h"

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
        
        printf("---HOME---\n");
        printf("1: Registrazione\n");
        printf("2: Login\n");
        printf("0: Esci\n");
        scanf("%d", &scelta);
        printf("\n");
        
        switch (scelta) {
            case 1:
                #ifdef _WIN32
                    HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, 11);
                    printf("Benvenuto! \nCrea il tuo account\n");
                    SetConsoleTextAttribute(hConsole, 15);
                #else
                    printf(ANSI_COLOR_CYAN "Benvenuto! \nCrea il tuo account\n" ANSI_COLOR_RESET "\n");
                #endif
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
                    #ifdef _WIN32
                        HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                        SetConsoleTextAttribute(hConsole, 11);
                        printf("Benvenuto nella sezione privata del tuo account\n");
                        SetConsoleTextAttribute(hConsole, 15);
                    #else
                        printf(ANSI_COLOR_CYAN "Benvenuto nella sezione privata del tuo account\n" ANSI_COLOR_RESET);
                    #endif
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
                                #ifdef _WIN32
                                    HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                                    SetConsoleTextAttribute(hConsole, 11);
                                    printf("Elenco dati personali\n");
                                    SetConsoleTextAttribute(hConsole, 15);
                                #else
                                    printf(ANSI_COLOR_CYAN "Elenco dati personali\n" ANSI_COLOR_RESET);
                                #endif
                                
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
        
        #ifdef _WIN32
            HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 11);
            printf("-----------------------------\n");
            SetConsoleTextAttribute(hConsole, 15);
        #else
            printf(ANSI_COLOR_CYAN "-----------------------------\n" ANSI_COLOR_RESET "\n");
        #endif
        
    } while(scelta != 0);
    
    
    
    printf("\n");
    return 0;
}

void titolo() {
    
    printf("\n");
    
    #ifdef _WIN32
        HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 11);
        printf("███████╗████████╗ █████╗ ██████╗ ██╗  ██╗    ██╗███╗   ██╗██████╗ ██╗   ██╗███████╗████████╗██████╗ ██╗███████╗███████╗\n");
        printf("██╔════╝╚══██╔══╝██╔══██╗██╔══██╗██║ ██╔╝    ██║████╗  ██║██╔══██╗██║   ██║██╔════╝╚══██╔══╝██╔══██╗██║██╔════╝██╔════╝\n");
        printf("███████╗   ██║   ███████║██████╔╝█████╔╝     ██║██╔██╗ ██║██║  ██║██║   ██║███████╗   ██║   ██████╔╝██║█████╗  ███████╗\n");
        printf("╚════██║   ██║   ██╔══██║██╔══██╗██╔═██╗     ██║██║╚██╗██║██║  ██║██║   ██║╚════██║   ██║   ██╔══██╗██║██╔══╝  ╚════██║\n");
        printf("███████║   ██║   ██║  ██║██║  ██║██║  ██╗    ██║██║ ╚████║██████╔╝╚██████╔╝███████║   ██║   ██║  ██║██║███████╗███████║\n");
        printf("╚══════╝   ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝    ╚═╝╚═╝  ╚═══╝╚═════╝  ╚═════╝ ╚══════╝   ╚═╝   ╚═╝  ╚═╝╚═╝╚══════╝╚══════╝\n");
        SetConsoleTextAttribute(hConsole, 15);
    #else
        printf(ANSI_COLOR_CYAN "███████╗████████╗ █████╗ ██████╗ ██╗  ██╗    ██╗███╗   ██╗██████╗ ██╗   ██╗███████╗████████╗██████╗ ██╗███████╗███████╗\n");
        printf(ANSI_COLOR_CYAN"██╔════╝╚══██╔══╝██╔══██╗██╔══██╗██║ ██╔╝    ██║████╗  ██║██╔══██╗██║   ██║██╔════╝╚══██╔══╝██╔══██╗██║██╔════╝██╔════╝\n");
        printf(ANSI_COLOR_CYAN"███████╗   ██║   ███████║██████╔╝█████╔╝     ██║██╔██╗ ██║██║  ██║██║   ██║███████╗   ██║   ██████╔╝██║█████╗  ███████╗\n");
        printf(ANSI_COLOR_CYAN"╚════██║   ██║   ██╔══██║██╔══██╗██╔═██╗     ██║██║╚██╗██║██║  ██║██║   ██║╚════██║   ██║   ██╔══██╗██║██╔══╝  ╚════██║\n");
        printf(ANSI_COLOR_CYAN"███████║   ██║   ██║  ██║██║  ██║██║  ██╗    ██║██║ ╚████║██████╔╝╚██████╔╝███████║   ██║   ██║  ██║██║███████╗███████║\n");
        printf(ANSI_COLOR_CYAN"╚══════╝   ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝    ╚═╝╚═╝  ╚═══╝╚═════╝  ╚═════╝ ╚══════╝   ╚═╝   ╚═╝  ╚═╝╚═╝╚══════╝╚══════╝\n" ANSI_COLOR_RESET);
    #endif
    
    printf("\n");
}
