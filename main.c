#define BUFFER_SIZE 1024

//librerie generali
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>

//NOME DIVERSO? O LASCIARE IN MAIN.C? DOBBIAMO CREARE UN DATA.H? @dany-el92
#include "data.c"

#include "functions.h"
#include "utente.h"
#include "prenotazione.h"
#include "mostra.h"
#include "opera.h"

int main() {

    titolo();

    int scelta, scelta2 = 0;
    char email[60];
    int nMostra, nOpera;

    Utente *testaUtente  = NULL;
    Mostra *testaMostra  = NULL;
    Opera  *testaOpera   = NULL;

    Utente *utenteLogin  = NULL; //utente che avrà eseguito il login
    Mostra *mostraScelta = NULL;
    Opera  *operaScelta  = NULL;

    //Lettura utenti dal file
    FILE *fpU;
    fpU = fopen("utenti.csv", "r");

    //Lettura utenti dal file
    FILE *fpM;
    fpM = fopen("mostre.csv", "r");
    
    //Lettura utenti dal file
    FILE *fpO;
    fpO = fopen("opere.csv", "r");

    testaUtente = letturaUtenti(fpU);
    testaMostra = letturaMostre(fpM);
    testaOpera  = letturaOpere(fpO);

    do {
        printf("---HOME---\n");
        printf("1: Login\n");
        printf("2: Registrazione\n");
        printf("0: Chiudi applicazione\n");
        printf("----------\n");
        printf("-> ");
        scanf("%d", &scelta);
        //printf("\n"); TODO: RIMUOVERE?

        //ripulisco la schermata
        clearConsole();
        titolo();

        switch (scelta) {
            case 1:
                while ('\n' != getchar());

                fseek(fpU, 0, SEEK_END);
                long sizeU = ftell(fpU);

                if(sizeU == 0) { //file vuoto - nessun utente registrato
                    
                    printColor("Attenzione!\n", COLOR_RED);
                    printf("Non ci sono utenti registrati.\n");
                
                } else { //file pieno - utenti registrati presenti
                
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

                            if (utenteLogin->permessi == 2) {
                                //operazioni che può effettuare il dirigente
                                printf("4: Aggiungi dati mostra\n");
                                printf("5: Modifica dati mostra\n");
                                printf("6: Cancella dati mostra\n");
                                printf("7: Aggiungi dati opera\n");
                                printf("8: Modifica dati opera\n");
                                printf("9: Cancella dati opera\n");
                            } else {
                                //operazioni che può effettuare l'utente
                                printf("4: Visualizza mostre\n");
                                //printf("5: Prenotati ad una mostra\n");
                            }

                            //printf("9: Logout\n");
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
                                    modificaUtente(utenteLogin, testaUtente);
                                    break;

                                case 3:
                                    clearConsole();
                                    titolo();
                                    eliminaUtente(utenteLogin, testaUtente);
                                    break;

                                case 4:
                                    clearConsole();
                                    titolo();

                                    while ('\n' != getchar());

                                    if (utenteLogin->permessi == 2) {
                                        aggiungiMostra(testaMostra);
                                    } else {
                                        stampaMostre(testaMostra);
                                    }
                                    break;

                                case 5:;
                                    clearConsole();
                                    titolo();

                                    if (utenteLogin->permessi == 2) {
                                        
                                        fseek(fpM, 0, SEEK_END);
                                        long sizeM = ftell(fpM);
                                        
                                        if(sizeM == 0) { //non ci sono mostre registrate
                                            printColor("Attenzione!\n", COLOR_RED);
                                            printf("Non ci sono mostre registrate.\n");
                                        } else {
                                            printColor("Elenco delle Mostre disponibili\n", COLOR_CYAN);
                                            stampaMostre(testaMostra);
                                            printf("\n");
                                            printf("Inserire il numero della mostra da modificare: ");
                                            scanf("%d", &nMostra);

                                            clearConsole();
                                            titolo();

                                            mostraScelta = ricercaMostra(testaMostra, nMostra);

                                            char *valore2 = (char *) mostraScelta;
                                            if (valore2 != NULL) {
                                                modificaMostra(testaMostra, mostraScelta);
                                            }
                                            while ('\n' != getchar());
                                        }
                                        
                                    }
                                    break;
                                case 6:
                                    clearConsole();
                                    titolo();

                                    if (utenteLogin->permessi == 2) {
                                        fseek(fpM, 0, SEEK_END);
                                        long sizeM = ftell(fpM);
                                        
                                        if(sizeM == 0) { //non ci sono mostre registrate
                                            
                                            printColor("Attenzione!\n", COLOR_RED);
                                            printf("Non ci sono mostre registrate.\n");
                                            
                                        } else {
                                            
                                            printColor("Elenco delle Mostre\n", COLOR_CYAN);
                                            stampaMostre(testaMostra);
                                            printf("\n");
                                            printf("Inserire il numero della mostra da eliminare: ");
                                            scanf("%d", &nMostra);

                                            clearConsole();
                                            titolo();

                                            mostraScelta = ricercaMostra(testaMostra, nMostra);

                                            char *valore2 = (char *) mostraScelta;
                                            if (valore2 != NULL) {
                                                eliminaMostra(testaMostra, mostraScelta);
                                            }
                                            while ('\n' != getchar());
                                        }
                                        
                                    }
                                    break;
                                case 7:
                                    clearConsole();
                                    titolo();

                                    if (utenteLogin->permessi == 2) {
                                        aggiungiOpera(testaOpera);
                                    }
                                    break;
                                case 8:
                                    clearConsole();
                                    titolo();

                                    if (utenteLogin->permessi == 2) {
                                        
                                        fseek(fpO, 0, SEEK_END);
                                        long sizeO = ftell(fpO);
                                        
                                        if(sizeO == 0) { //non ci sono mostre registrate
                                            printColor("Attenzione!\n", COLOR_RED);
                                            printf("Non ci sono opere registrate.\n");
                                        } else {
                                            printColor("Elenco delle Opere disponibili\n", COLOR_CYAN);
                                            stampaOpere(testaOpera);
                                            printf("\n");
                                            printf("Inserire il numero dell'opera da modificare: ");
                                            scanf("%d", &nOpera);

                                            clearConsole();
                                            titolo();

                                            operaScelta = ricercaOpera(testaOpera, nOpera);

                                            char *valore2 = (char *) operaScelta;
                                            if (valore2 != NULL) {
                                                modificaOpera(testaOpera, operaScelta);
                                            }
                                            while ('\n' != getchar());
                                        }
                                        
                                    }
                                    break;
                                case 9:
                                    clearConsole();
                                    titolo();

                                    if (utenteLogin->permessi == 2) {
                                        fseek(fpO, 0, SEEK_END);
                                        long sizeO = ftell(fpO);
                                        
                                        if(sizeO == 0) { //non ci sono mostre registrate
                                            
                                            printColor("Attenzione!\n", COLOR_RED);
                                            printf("Non ci sono opere registrate.\n");
                                            
                                        } else {
                                            
                                            printColor("Elenco delle Opere\n", COLOR_CYAN);
                                            stampaOpere(testaOpera);
                                            printf("\n");
                                            printf("Inserire il numero della mostra da eliminare: ");
                                            scanf("%d", &nOpera);

                                            clearConsole();
                                            titolo();

                                            operaScelta = ricercaOpera(testaOpera, nOpera);

                                            char *valore2 = (char *) operaScelta;
                                            if (valore2 != NULL) {
                                                eliminaOpera(testaOpera, operaScelta);
                                            }
                                            while ('\n' != getchar());
                                        }
                                        
                                    }
                                    break;
                                default:
                                    clearConsole();
                                    titolo();
                                    break;
                            }
                            if (scelta2 == 0) {
                                scelta = 0;
                            }

                        } while (/*scelta2 != 9 && */scelta2 != 3 && scelta2 != 0);
                    }
                }
                break;

            case 2:
                printColor("Benvenuto! \nCrea il tuo account\n", COLOR_CYAN);
                registrazioneUtente(testaUtente);
                clearConsole();
                titolo();
                break;

            default:
                break;
        }
        printColor("-----------------------------\n", COLOR_CYAN);

    } while (scelta != 0);

    printf("\n");
    return 0;
}
