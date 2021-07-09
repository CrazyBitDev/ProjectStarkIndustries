#define BUFFER_SIZE 1024

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
#include "mostra.h"
/*#include "opera.h"*/

int main() {

    titolo();

    int scelta, scelta2 = 0, colonna = 0;
    char email[60], buf[BUFFER_SIZE];

    Utente *testaUtente = NULL;
    Utente *utenteLogin = NULL; //utente che avrà eseguito il login
    Utente *tempUtente = NULL; //temporanea
    Utente *precUtente = NULL;

    //Lettura utenti dal file
    FILE *fpU;
    fpU = fopen("utenti.csv", "r");

    if (fpU == NULL) {
        printColor("\t\t\t|-----------------------------|\n", COLOR_RED);
        printColor("\t\t\t|File \"utenti\" non trovato!   |\n", COLOR_RED);
        printColor("\t\t\t|\t...                   |\n", COLOR_RED);
        printColor("\t\t\t|File in creazione            |\n", COLOR_RED);
        printColor("\t\t\t|-----------------------------|\n", COLOR_RED);
    } else {
        while (!feof(fpU)) {
            fgets(buf, BUFFER_SIZE, fpU);
            tempUtente = (struct utente *) malloc(sizeof(struct utente));
            tempUtente->nextUtente = NULL;

            if (precUtente != NULL) {
                precUtente->nextUtente = tempUtente;
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
                    strcpy(tempUtente->nick, tok);
                    tempUtente->nick[strlen(tempUtente->nick)] = 0;
                }
                if (colonna == 4) {
                    strcpy(tempUtente->email, tok);
                    tempUtente->email[strlen(tempUtente->email)] = 0;
                }
                if (colonna == 5) {
                    strcpy(tempUtente->password, tok);
                    tempUtente->password[strlen(tempUtente->password)] = 0;
                }
                if (colonna == 6) {
                    strcpy(tempUtente->dataNascita, tok);
                    tempUtente->dataNascita[strlen(tempUtente->dataNascita)] = 0;
                }
                if (colonna == 7) {
                    tempUtente->permessi = atoi(tok);
                }
                tok = strtok(NULL, ",");
                colonna++;
            }
            colonna = 0;
            precUtente = tempUtente;

        }
    }

    //Lettura mostre dal file
    int nMostra, colonna1 = 0;
    char buf2[BUFFER_SIZE];

    Mostre *testaMostre = NULL;
    Mostre *mostraScelta = NULL;
    Mostre *tempMostre = NULL; //temporanea
    Mostre *tempMostre1 = NULL;

    FILE *fpM;
    fpM = fopen("mostre.csv", "r");

    if (fpU == NULL) {
        printColor("\t\t\t|-----------------------------|\n", COLOR_RED);
        printColor("\t\t\t|File \"mostre\" non trovato!   |\n", COLOR_RED);
        printColor("\t\t\t|\t...                   |\n", COLOR_RED);
        printColor("\t\t\t|File in creazione            |\n", COLOR_RED);
        printColor("\t\t\t|-----------------------------|\n", COLOR_RED);
    } else {
        while (!feof(fpM)) {
            fgets(buf2, BUFFER_SIZE, fpM);
            tempMostre = (struct mostre *) malloc(sizeof(struct mostre));
            tempMostre->nextMostra = NULL;

            if (tempMostre1 != NULL) {
                tempMostre1->nextMostra = tempMostre;
            } else {
                testaMostre = tempMostre;
            }

            char *tok2;
            tok2 = strtok(buf2, ",");

            while (tok2) {
                if (colonna1 == 0) {
                    tempMostre->id = atoi(tok2);
                }
                if (colonna1 == 1) {
                    strcpy(tempMostre->responsabile, tok2);
                    tempMostre->responsabile[strlen(tempMostre->responsabile)] = 0;
                }
                if (colonna1 == 2) {
                    strcpy(tempMostre->luogo, tok2);
                    tempMostre->luogo[strlen(tempMostre->luogo)] = 0;
                }
                if (colonna1 == 3) {
                    strcpy(tempMostre->citta, tok2);
                    tempMostre->citta[strlen(tempMostre->citta)] = 0;
                }
                if (colonna1 == 4) {
                    strcpy(tempMostre->indirizzo, tok2);
                    tempMostre->indirizzo[strlen(tempMostre->indirizzo)] = 0;
                }
                if (colonna1 == 5) {
                    strcpy(tempMostre->dataInizio, tok2);
                    tempMostre->dataInizio[strlen(tempMostre->dataInizio)] = 0;
                }
                if (colonna1 == 6) {
                    strcpy(tempMostre->dataFine, tok2);
                    tempMostre->dataFine[strlen(tempMostre->dataFine)] = 0;
                }
                if (colonna1 == 7) {
                    tempMostre->nOpere = atoi(tok2);
                }
                tok2 = strtok(NULL, ",");
                colonna1++;
            }
            colonna1 = 0;
            tempMostre1 = tempMostre;
        }
    }

    do {
        printf("---HOME---\n");
        printf("1: Registrazione\n");
        printf("2: Login\n");
        printf("0: Chiudi applicazione\n");
        printf("----------\n");
        printf("-> ");
        scanf("%d", &scelta);
        printf("\n");
        
        //ripulisco la schermata
        clearConsole();
        titolo();

        switch (scelta) {
            case 1:
                printColor("Benvenuto! \nCrea il tuo account\n", COLOR_CYAN);
                testaUtente = registrazioneUtente(testaUtente);
                clearConsole();
                titolo();
                break;

            case 2:
                while ('\n' != getchar());

                printf("Email o nickname: ");
                fgets(email, 60, stdin);
                email[strlen(email) - 1] = 0;

                utenteLogin = accesso(testaUtente, email);
                char *valore = (char *) utenteLogin;

                if (valore != NULL) {
                    clearConsole();
                    titolo();
                    
                    printColor("Benvenuto nella sezione privata del tuo account\n", COLOR_CYAN);
                    //Operazioni che può effettuare l'utente una volta che ha eseguito il login
                    do {
                        printf("\n---MENU'---\n");
                        printf("1: Visualizza informazioni personali\n");
                        printf("2: Modifica dati personali\n");
                        printf("3: Elimina account\n");

                        if(utenteLogin->permessi == 2) {
                            //operazioni che può effettuare il dirigente
                            printf("4: Aggiungi dati mostra\n");
                            printf("5: Modifica dati mostra\n");
                            printf("6: Cancella dati mostra\n");
                        } else {
                            //operazioni che può effettuare l'utente
                            printf("4: Visualizza mostre\n");
                            //printf("5: Prenotati ad una mostra\n");
                        }

                        printf("9: Logout\n");
                        printf("0: Chiudi Applicazione\n");
                        printf("----------\n");
                        printf("-> ");
                        scanf("%d", &scelta2);
                        printf("\n");


                        switch (scelta2) {
                            case 1:
                                clearConsole();
                                titolo();
                                
                                stampaUtente(utenteLogin);
                                break;

                            case 2:
                                clearConsole();
                                titolo();
                                
                                while ('\n' != getchar());
                                stampaUtente(utenteLogin);
                                testaUtente = modificaUtente(utenteLogin, testaUtente);
                                break;

                            case 3:
                                clearConsole();
                                titolo();
                                
                                testaUtente = eliminaUtente(utenteLogin, testaUtente);
                                break;

                            case 4:
                                clearConsole();
                                titolo();
                                
                                while ('\n' != getchar());

                                if(utenteLogin->permessi == 2) {
                                    aggiungiMostra(testaMostre);
                                } else {
                                    stampaMostre(testaMostre);
                                }
                                break;

                            case 5:
                                clearConsole();
                                titolo();
                                
                                if(utenteLogin->permessi == 2) {
                                    printColor("Elenco delle Mostre disponibili\n", COLOR_CYAN);
                                    stampaMostre(testaMostre);
                                    printf("\n");
                                    printf("Inserire il numero della mostra da modificare: ");
                                    scanf("%d", &nMostra);
                                    
                                    clearConsole();
                                    titolo();
                                    
                                    mostraScelta = ricercaMostra(testaMostre, nMostra);
                                    
                                    char *valore2 = (char *) mostraScelta;
                                    if(valore2 != NULL) {
                                        modificaMostra(testaMostre, mostraScelta);
                                    }
                                    while ('\n' != getchar());
                                }
                                break;
                            case 6:
                                clearConsole();
                                titolo();
                                
                                if(utenteLogin->permessi == 2) {
                                    printColor("Elenco delle Mostre\n", COLOR_CYAN);
                                    stampaMostre(testaMostre);
                                    printf("\n");
                                    printf("Inserire il numero della mostra da eliminare: ");
                                    scanf("%d", &nMostra);
                                    
                                    clearConsole();
                                    titolo();
                                    
                                    mostraScelta = ricercaMostra(testaMostre, nMostra);
                                    
                                    char *valore2 = (char *) mostraScelta;
                                    if(valore2 != NULL) {
                                        eliminaMostra(testaMostre, mostraScelta);
                                    }
                                    while ('\n' != getchar());
                                }
                                break;
                            default:
                                break;
                        }
                        titolo();
                        if(scelta2 == 0) {
                            scelta = 0;
                        }
                        
                    } while (scelta2 != 9 && scelta2 != 3 && scelta2 != 0);
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
