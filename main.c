#define DIM 50

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
/*#include "mostra.h"*/
/*#include "opera.h"*/

void titolo(void);

int main() {

    titolo();

    int scelta, scelta2, colonna = 0;
    char email[60], buf[DIM];

    Utente *testaUtente = NULL;
    Utente *utenteLogin = NULL; //utente che avrà eseguito il login
    Utente *tempUtente = NULL; //temporanea
    Utente *tempUtente1 = NULL;

    //Lettura utenti dal file
    FILE *fpU;
    fpU = fopen("utenti.csv", "r");

    if (fpU == NULL) {
        printColor("File \"utenti\" non trovato!\n", COLOR_RED);
    } else {
        while (!feof(fpU)) {
            fgets(buf, BUFFER_SIZE, fpU);
            tempUtente = (struct utente *) malloc(sizeof(struct utente));

            if (tempUtente1 != NULL) {
                tempUtente1->nextUtente = tempUtente;
            } else {
                testaUtente = tempUtente;
            }

            char *tok;
            tok = strtok(buf, ",");

            while (tok) {
                if (colonna == 0) {
                    tempUtente->id = atoi(tok);
                }
                if (colonna == 1) {
                    strcpy(tempUtente->nome, tok);
                    tempUtente->nome[strlen(tempUtente->nome)] = 0;
                }
                if (colonna == 2) {
                    strcpy(tempUtente->cognome, tok);
                    tempUtente->cognome[strlen(tempUtente->cognome)] = 0;
                }
                if (colonna == 3) {
                    strcpy(tempUtente->email, tok);
                    tempUtente->email[strlen(tempUtente->email)] = 0;
                }
                if (colonna == 4) {
                    strcpy(tempUtente->password, tok);
                    tempUtente->password[strlen(tempUtente->password)] = 0;
                }
                if (colonna == 5) {
                    strcpy(tempUtente->dataNascita, tok);
                    tempUtente->dataNascita[strlen(tempUtente->dataNascita)] = 0;
                }
                if (colonna == 6) {
                    tempUtente->permessi = atoi(tok);
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
        printf("0: Chiudi applicazione\n");
        printf("---HOME---\n");
        printf("-> ");
        scanf("%d", &scelta);
        printf("\n");

        switch (scelta) {
            case 1:
                printColor("Benvenuto! \nCrea il tuo account\n", COLOR_CYAN);
                testaUtente = registrazioneUtente(testaUtente);
                break;

            case 2:
                while ('\n' != getchar());

                printf("Email: ");
                fgets(email, 60, stdin);
                email[strlen(email) - 1] = 0;

                utenteLogin = accesso(testaUtente, email);
                char *valore = (char *) utenteLogin;

                if (valore != NULL) {
                    printColor("Benvenuto nella sezione privata del tuo account\n", COLOR_CYAN);
                    //Operazioni che può effettuare l'utente una volta che ha eseguito il login
                    do {
                        printf("---MENU'---\n");
                        printf("1: Visualizza informazioni personali\n");
                        printf("2: Modifica dati personali\n");
                        /*printf("3: Aggiungi dati mostra\n");
                        printf("4: Modifica dati mostra\n");
                        printf("5: Cancella dati mostra\n");*/
                        printf("0: Logout\n");
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
                                /*case 3:
                                    aggiungiMostra(testaUtente,utenteLogin);
                                    break;*/
                        }

                    } while (scelta2 != 0);
                }
                break;

            default:
                break;
        }

        printColor("-----------------------------\n", COLOR_CYAN);

    } while (scelta != 0);

    printf("\n");
    return 0;
}

void titolo() {

    printf("\n");
    consoleColor(COLOR_CYAN);
    printf("   _____ __             __      ____          __           __       _          \n");
    printf("  / ___// /_____ ______/ /__   /  _/___  ____/ /_  _______/ /______(_)__  _____\n");
    printf("  \\__ \\/ __/ __ `/ ___/ //_/   / // __ \\/ __  / / / / ___/ __/ ___/ / _ \\/ ___/\n");
    printf(" ___/ / /_/ /_/ / /  / ,<    _/ // / / / /_/ / /_/ (__  ) /_/ /  / /  __(__  ) \n");
    printf("/____/\\__/\\__,_/_/  /_/|_|  /___/_/ /_/\\__,_/\\__,_/____/\\__/_/  /_/\\___/____/  \n");
    consoleColor(COLOR_RESET);

    printf("\n");
}
