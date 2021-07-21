struct mostraOpera {
    Opera *opera; //puntatore all'opera
    MostraOpera *nextOpera; //puntatore al prossimo nodo
};

struct mostra {
    int id;
    char responsabile[30];
    char luogo[25];
    char citta[20];
    char indirizzo[30];
    char dataInizio[11];
    char dataFine[11];
    MostraOpera *opere;
    Mostra *nextMostra; //puntatore al prossimo nodo
};

/**
 * Function: letturaMostre
 * ----------------------------
 *   Legge i dati dal file "mostre.csv" e il file "mostreopere.csv" salvando il tutto all'interno della struct Mostra e alla struct MostreOpere, contenuta all'interno di Mostra
 *
 *   @param fp puntatore alla variabile di tipo FILE, precedentemente configurata, che punta al file mostre.csv
 *   @param fpMO puntatore alla variabile di tipo FILE, precedentemente configurata, che punta al file mostreopere.csv
 *   @param testaOpera puntatore alla variabile di tipo Opera, una lista contenente tutte le opere precedentemente caricate
 *
 *   @return puntatore alla variabile di tipo Mostra, una lista contenente tutte le mostre e le opere associate
 */
Mostra *letturaMostre(FILE *fp, FILE *fpMO, Opera *testaOpera) {

    int colonna1 = 0;
    char buf[BUFFER_SIZE];

    Mostra *testaMostra = NULL;
    Mostra *tempMostra = NULL;
    Mostra *tempMostra1 = NULL;

    MostraOpera *tempMostraOpera = NULL;
    Opera *tempOpera = NULL;
    bool operaNonInserita = false;

    if (fp == NULL) {
        printColor("\t\t\t|-----------------------------|\n", COLOR_RED);
        printColor("\t\t\t|  File \"mostre\" non trovato! |\n", COLOR_RED);
        printColor("\t\t\t|             ...             |\n", COLOR_RED);
        printColor("\t\t\t|      File in creazione      |\n", COLOR_RED);
        printColor("\t\t\t|-----------------------------|\n", COLOR_RED);
    } else {
        while (!feof(fp)) {
            fgets(buf, BUFFER_SIZE, fp);
            tempMostra = (Mostra *) malloc(sizeof(Mostra));
            tempMostra->nextMostra = NULL;
            tempMostra->opere = NULL;

            if (tempMostra1 != NULL) {
                tempMostra1->nextMostra = tempMostra;
            } else {
                testaMostra = tempMostra;
            }

            char *tok2;
            tok2 = strtok(buf, ",");

            while (tok2) {
                if (colonna1 == 0) {
                    tempMostra->id = atoi(tok2);
                }
                if (colonna1 == 1) {
                    strcpy(tempMostra->responsabile, tok2);
                    tempMostra->responsabile[strlen(tempMostra->responsabile)] = 0;
                }
                if (colonna1 == 2) {
                    strcpy(tempMostra->luogo, tok2);
                    tempMostra->luogo[strlen(tempMostra->luogo)] = 0;
                }
                if (colonna1 == 3) {
                    strcpy(tempMostra->citta, tok2);
                    tempMostra->citta[strlen(tempMostra->citta)] = 0;
                }
                if (colonna1 == 4) {
                    strcpy(tempMostra->indirizzo, tok2);
                    tempMostra->indirizzo[strlen(tempMostra->indirizzo)] = 0;
                }
                if (colonna1 == 5) {
                    strcpy(tempMostra->dataInizio, tok2);
                    tempMostra->dataInizio[strlen(tempMostra->dataInizio)] = 0;
                }
                if (colonna1 == 6) {
                    if (strstr(tok2, "\n") != NULL) {
                        tok2[strlen(tok2) - 1] = 0;
                    }
                    strcpy(tempMostra->dataFine, tok2);
                    tempMostra->dataFine[strlen(tempMostra->dataFine)] = 0;
                }
                tok2 = strtok(NULL, ",");
                colonna1++;
            }
            colonna1 = 0;
            tempMostra1 = tempMostra;
        }
    }

    if (fpMO == NULL) {
        printColor("\t\t\t|-------------------------------|\n", COLOR_RED);
        printColor("\t\t\t|File \"mostreopere\" non trovato!|\n", COLOR_RED);
        printColor("\t\t\t|              ...              |\n", COLOR_RED);
        printColor("\t\t\t|       File in creazione       |\n", COLOR_RED);
        printColor("\t\t\t|-------------------------------|\n", COLOR_RED);
    } else {
        while (!feof(fpMO)) {
            fgets(buf, BUFFER_SIZE, fpMO);

            char *tok = strtok(buf, ",");

            while (tok) {
                if (colonna1 == 0) {
                    Mostra *tempMostra = ricercaMostra(testaMostra, atoi(tok));
                    if (tempMostra->opere == NULL) {
                        tempMostra->opere = (MostraOpera *) malloc(sizeof(MostraOpera));
                        tempMostra->opere->nextOpera = NULL;
                        tempMostra->opere->opera = NULL;
                    }
                    tempMostraOpera = tempMostra->opere;
                }
                if (colonna1 == 1) {
                    if (strstr(tok, "\n") != NULL) {
                        tok[strlen(tok) - 1] = 0;
                    }
                    tempOpera = ricercaOpera(testaOpera, atoi(tok));
                    operaNonInserita = true;
                    do {
                        if (tempMostraOpera->opera == NULL) {
                            tempMostraOpera->opera = tempOpera;
                            operaNonInserita = false;
                        } else {
                            if (tempMostraOpera->nextOpera == NULL) {
                                tempMostraOpera->nextOpera = (MostraOpera *) malloc(sizeof(MostraOpera));
                                tempMostraOpera->nextOpera->nextOpera = NULL;
                                tempMostraOpera->nextOpera->opera = NULL;
                            }
                            tempMostraOpera = tempMostraOpera->nextOpera;
                        }
                    } while (operaNonInserita);
                }
                tok = strtok(NULL, ",");
                colonna1++;
            }
            colonna1 = 0;
        }
    }

    return testaMostra;
}

/**
 * Function: aggiungiMostra
 * ----------------------------
 *   Permette la registrazione di una nuova mostra
 *   Effettuata l'inserimento, verrà effettuato una scrittura del file "mostra.csv"
 *
 *   @param testa puntatore alla variabile di tipo Mostra, una lista contenente tutte le mostre
 */
void aggiungiMostra(Mostra *testa) {

    Mostra *curr, *prec;
    prec = NULL;
    curr = testa;

    bool continuaInserimento = true;
    bool testInput = false; //flag per controllare i vari input
    bool flagDate = false;
    char dataIn[11];
    bool dataCorrettaIn = true;
    int giornoIn, meseIn, annoIn;
    int ultimoID = 0, i;

    char dataFin[11];
    bool dataCorrettaFin = true;
    int giornoFin, meseFin, annoFin;

    Mostra *nuovoNodo = NULL;


    nuovoNodo = (Mostra *) malloc(sizeof(Mostra));

    FILE *fp;
    fp = fopen("mostre.csv", "a+"); //apertura file

    notificaAnnulla(false);

    do {
        testInput = false;
        printf("Inserisci il responsabile: ");
        fgets(nuovoNodo->responsabile, 30, stdin);
        nuovoNodo->responsabile[strlen(nuovoNodo->responsabile) - 1] = 0;
        nuovoNodo->responsabile[0] = toupper(nuovoNodo->responsabile[0]);

        if (strlen(nuovoNodo->responsabile) == 0) {
            continuaInserimento = false;
            clearConsole();
            titolo();
            break;
        }

        //verifico che siano stati inseriti solo caratteri alfabetici
        for (i = 0; i < strlen(nuovoNodo->responsabile); i++) {
            if (isalpha(nuovoNodo->responsabile[i]) == 0 && nuovoNodo->responsabile[i] != ' ') {
                testInput = true; //carattere non alfabetico
            }
        }

        if (testInput) {
            clearConsole();
            titolo();
            printf("\n----------");
            printColor("\nAttenzione!\n", COLOR_RED);
            printf("Responsabile non valido.\n");
            printf("----------\n\n");
        }
    } while (testInput);

    if (continuaInserimento) {

        clearConsole();
        titolo();

        do {
            testInput = false;
            printf("Inserisci il luogo: ");
            fgets(nuovoNodo->luogo, 25, stdin);
            nuovoNodo->luogo[strlen(nuovoNodo->luogo) - 1] = 0;
            nuovoNodo->luogo[0] = toupper(nuovoNodo->luogo[0]);

            for (i = 0; i < strlen(nuovoNodo->luogo); i++) {
                if (isalpha(nuovoNodo->luogo[i]) == 0 && nuovoNodo->luogo[i] != ' ') {
                    testInput = true; //carattere non alfabetico
                }
            }

            if (testInput || strlen(nuovoNodo->luogo) == 0) {
                clearConsole();
                titolo();
                printf("\n----------");
                printColor("\nAttenzione!\n", COLOR_RED);
                printf("Luogo non valido.\n");
                printf("----------\n\n");
            }
        } while (testInput || strlen(nuovoNodo->luogo) == 0);

        printf("-----------------------------\n");

        do {
            testInput = false;
            printf("Inserisci Citta': ");
            fgets(nuovoNodo->citta, 20, stdin);
            nuovoNodo->citta[strlen(nuovoNodo->citta) - 1] = 0;
            nuovoNodo->citta[0] = toupper(nuovoNodo->citta[0]);

            for (i = 0; i < strlen(nuovoNodo->citta); i++) {
                if (isalpha(nuovoNodo->citta[i]) == 0 && nuovoNodo->citta[i] != ' ') {
                    testInput = true; //carattere non alfabetico
                }
            }

            if (testInput || strlen(nuovoNodo->citta) == 0) {
                clearConsole();
                titolo();
                printf("\n----------");
                printColor("\nAttenzione!\n", COLOR_RED);
                printf("Citta' non valida.\n");
                printf("----------\n\n");
            }
        } while (testInput || strlen(nuovoNodo->luogo) == 0);

        printf("-----------------------------\n");

        do {
            testInput = false;
            printf("Inserisci Indirizzo: ");
            fgets(nuovoNodo->indirizzo, 30, stdin);
            nuovoNodo->indirizzo[strlen(nuovoNodo->indirizzo) - 1] = 0;
            nuovoNodo->indirizzo[0] = toupper(nuovoNodo->indirizzo[0]);

            if (strlen(nuovoNodo->indirizzo) == 0) {
                testInput = true;
                clearConsole();
                titolo();
                printf("\n----------");
                printColor("\nAttenzione!\n", COLOR_RED);
                printf("Indirizzo non valido.\n");
                printf("----------\n\n");
            }
        } while (testInput);

        printf("-----------------------------\n");

        bool dataCorr = true;

        do {
            do {
                if (!dataCorr) {
                    clearConsole();
                    titolo();
                    printf("\n----------");
                    printColor("\nAttenzione!\n", COLOR_RED);
                    printf("La data inserita deve essere succesiva a quella corrente.\n");
                    printf("Si prega di inserirla nuovamente.\n");
                    printf("----------\n\n");
                }

                printf("Inserisci la data d'");
                printColor("inizio ", COLOR_CYAN);
                printf("mostra\n");

                do {
                    if (!dataCorrettaIn) {
                        clearConsole();
                        titolo();
                        printf("\n----------");
                        printColor("\nAttenzione!\n", COLOR_RED);
                        printf("La data inserita non e' corretta.\nSi prega di inserirla nuovamente.\n");
                        printf("----------\n\n");
                    }

                    do {
                        printf("Giorno: ");
                        scanf("%d", &giornoIn);
                    } while (giornoIn < 1 || giornoIn > 31);

                    do {
                        printf("Mese: ");
                        scanf("%d", &meseIn);
                    } while (meseIn < 1 || meseIn > 12);

                    printf("Anno: ");
                    scanf("%d", &annoIn);

                    dataCorrettaIn = verificaData(giornoIn, meseIn, annoIn);

                } while (!dataCorrettaIn);

                dataCorr = (differenzaDateOggi(giornoIn, meseIn, annoIn) >= 0);
            } while (!dataCorr);

            while ('\n' != getchar());

            snprintf(dataIn, 11, "%d/%d/%d", giornoIn, meseIn, annoIn);

            printf("-----------------------------\n");

            printf("Inserisci la data di ");
            printColor("fine ", COLOR_CYAN);
            printf("mostra\n");

            do {
                if (!dataCorrettaFin) {
                    clearConsole();
                    titolo();
                    printf("\n----------");
                    printColor("\nAttenzione!\n", COLOR_RED);
                    printf("La data inserita non e' corretta.\nSi prega di inserirla nuovamente.\n");
                    printf("----------\n\n");
                }

                do {
                    printf("Giorno: ");
                    scanf("%d", &giornoFin);
                } while (giornoFin < 1 || giornoFin > 31);

                do {
                    printf("Mese: ");
                    scanf("%d", &meseFin);
                } while (meseFin < 1 || meseFin > 12);

                printf("Anno: ");
                scanf("%d", &annoFin);

                dataCorrettaFin = verificaData(giornoFin, meseFin, annoFin);

            } while (!dataCorrettaFin);

            while ('\n' != getchar());

            snprintf(dataFin, 11, "%d/%d/%d", giornoFin, meseFin, annoFin);

            printf("\n");
            if (differenzaDate(giornoIn, meseIn, annoIn, giornoFin, meseFin, annoFin) >= 0) {
                flagDate = true;
            } else {
                clearConsole();
                titolo();
                printf("\n----------\n");
                printColor("Attenzione!\n", COLOR_RED);
                printf("La data di fine mostra deve susseguire la data d'inizio.\n");
                printf("Si prega di inserire nuovamente le date.\n");
                printf("----------\n\n");
            }
        } while (!flagDate);
        strcpy(nuovoNodo->dataInizio, dataIn);
        strcpy(nuovoNodo->dataFine, dataFin);

        //verifico se nel file ci sono già delle mmostre registrate o meno
        fseek(fp, 0, SEEK_END);
        long size = ftell(fp);

        ultimoID = letturaUltimoID("mostre.csv") + 1;

        //ricerca della posizione di inserimento
        while (curr != NULL && ultimoID > curr->id) {
            prec = curr;
            curr = curr->nextMostra;
        }

        if (size == 0) { //file vuoto
            nuovoNodo->id = 0;
            fprintf(fp, "%d,%s,%s,%s,%s,%s,%s", nuovoNodo->id, nuovoNodo->responsabile, nuovoNodo->luogo,
                    nuovoNodo->citta, nuovoNodo->indirizzo, nuovoNodo->dataInizio, nuovoNodo->dataFine);

        } else { //file pieno
            nuovoNodo->id = ultimoID;
            fprintf(fp, "\n%d,%s,%s,%s,%s,%s,%s", nuovoNodo->id, nuovoNodo->responsabile, nuovoNodo->luogo,
                    nuovoNodo->citta, nuovoNodo->indirizzo, nuovoNodo->dataInizio, nuovoNodo->dataFine);
        }

        fclose(fp);

        //aggiornamento dei collegamenti
        if (prec == NULL) {
            nuovoNodo->nextMostra = testa;
            testa = nuovoNodo;
        } else {
            prec->nextMostra = nuovoNodo;
            nuovoNodo->nextMostra = curr;
        }

        clearConsole();
        titolo();
        printColor("Mostra registrata con successo.\n", COLOR_GREEN);
        pausa();
    }
}

/**
 * Function: aggiungiOperaAMostra
 * ----------------------------
 *   Permette di aggiungere una opera ad una determinata mostra, controllando che nel periodo della mostra l'opera non è già occupata
 *
 *   @param testa puntatore alla variabile di tipo Mostra, una lista contenente tutte le mostre
 *   @param mostra mostra scelta per essere modificata
 *   @param opera opera scelta per essere aggiunta
 */
void aggiungiOperaAMostra(Mostra *testa, Mostra *mostra, Opera *opera) {
    bool operaLibera = true;
    for (Mostra *tempMostra = testa; tempMostra != NULL; tempMostra = tempMostra->nextMostra) {
        if (differenzaDateChar(mostra->dataInizio, tempMostra->dataFine) >= 0 && differenzaDateChar(mostra->dataFine, tempMostra->dataInizio) <= 0)
            for (MostraOpera *tempMostraOpera = tempMostra->opere; tempMostraOpera != NULL; tempMostraOpera = tempMostraOpera->nextOpera) {
                if (opera->id == tempMostraOpera->opera->id) {
                    operaLibera = false;
                }
            }
        
    }
    if (operaLibera) {
        bool operaNonInserita = true;
        if (mostra->opere == NULL) {
            mostra->opere = (MostraOpera *) malloc(sizeof(MostraOpera));
            mostra->opere->nextOpera = NULL;
            mostra->opere->opera = NULL;
        }
        MostraOpera *tempMostraOpera = mostra->opere;
        do {
            if (tempMostraOpera->opera == NULL) {
                tempMostraOpera->opera = opera;
                operaNonInserita = false;
            } else {
                if (tempMostraOpera->nextOpera == NULL) {
                    tempMostraOpera->nextOpera = (MostraOpera *) malloc(sizeof(MostraOpera));
                    tempMostraOpera->nextOpera->nextOpera = NULL;
                    tempMostraOpera->nextOpera->opera = NULL;
                }
                tempMostraOpera = tempMostraOpera->nextOpera;
            }
        } while (operaNonInserita);

        //verifico se nel file ci sono già delle mmostre registrate o meno
        FILE *fp;
        fp = fopen("mostreopere.csv", "a+"); //apertura file
        fseek(fp, 0, SEEK_END);
        long size = ftell(fp);

        if (size == 0) { //file vuoto
            fprintf(fp, "%d,%d", mostra->id, opera->id);
        } else { //file pieno
            fprintf(fp, "\n%d,%d", mostra->id, opera->id);
        }

        fclose(fp);
    }
}

/**
 * Function: modificaMostra
 * ----------------------------
 *   Permette di modificare i dati relativi ad una mostra scelta
 *
 *   @param testa puntatore alla variabile di tipo Mostra, una lista contenente tutte le mostre
 *   @param mostra mostra scelta per essere modificata
 */
void modificaMostra(Mostra *testa, Mostra *mostra) {
    int scelta, colonna = 0, i;
    char risposta = '\0';
    bool flagDate = false;
    bool continuaModifica = true;
    bool testInput = false;

    Mostra *temp = NULL;
    temp = mostra;

    char responsabile[30];
    char luogo[25];
    char citta[20];
    char indirizzo[30];

    char dataIn[11];
    bool dataCorrettaIn = true;
    int giornoIn = 0, meseIn = 0, annoIn = 0;

    char dataFin[11];
    bool dataCorrettaFin = true;
    int giornoFin = 0, meseFin = 0, annoFin = 0;

    printColor("\nDati relativi alla mostra scelta:\n", COLOR_CYAN);
    printf("Id: %d\n", temp->id);
    printf("Responsabile: %s\n", temp->responsabile);
    printf("Luogo di esposizione: %s\n", temp->luogo);
    printf("Citta': %s\n", temp->citta);
    printf("Indirizzo: %s\n", temp->indirizzo);
    printf("Data inizio mostra: %s\n", temp->dataInizio);
    printf("Data fine mostra: %s\n", temp->dataFine);
    printColor("----------\n\n", COLOR_CYAN);

    do {
        //elenco campi modificabili
        printf("Scegliere il campo da modificare\n");
        printf("----------\n");
        printf("1: Responsabile\n");
        printf("2: Luogo\n");
        printf("3: Citta'\n");
        printf("4: Indirizzo\n");
        printf("5: Data Inizio\n");
        printf("6: Data Fine\n");
        printf("0: Annulla\n");
        printf("----------\n");
        printf("-> ");
        scanf("%d", &scelta);
        printf("\n");
        while ('\n' != getchar());

        switch (scelta) {
            case 0:
                break;

            case 1:
                clearConsole();
                titolo();

                do {
                    notificaAnnulla(false);
                    testInput = false;
                    printf("Inserisci il responsabile: ");
                    fgets(responsabile, 30, stdin);
                    responsabile[strlen(responsabile) - 1] = 0;
                    responsabile[0] = toupper(responsabile[0]);

                    if (strlen(responsabile) == 0) {
                        continuaModifica = false;
                        break;
                    }

                    for (i = 0; i < strlen(responsabile); i++) {
                        if (isalpha(responsabile[i]) == 0 && responsabile[i] != ' ') {
                            testInput = true; //carattere non alfabetico
                        }
                    }

                    if (testInput) {
                        clearConsole();
                        titolo();
                        printf("\n----------");
                        printColor("\nAttenzione!\n", COLOR_RED);
                        printf("Responsabile non valido.\n");
                        printf("----------\n\n");
                    } else {
                        strcpy(temp->responsabile, responsabile);
                    }
                } while (testInput);
                break;

            case 2:
                clearConsole();
                titolo();

                do {
                    notificaAnnulla(false);
                    testInput = false;
                    printf("Inserisci il luogo: ");
                    fgets(luogo, 25, stdin);
                    luogo[strlen(luogo) - 1] = 0;
                    luogo[0] = toupper(luogo[0]);

                    if (strlen(luogo) == 0) {
                        continuaModifica = false;
                        break;
                    }

                    for (i = 0; i < strlen(luogo); i++) {
                        if (isalpha(luogo[i]) == 0 && luogo[i] != ' ') {
                            testInput = true; //carattere non alfabetico
                        }
                    }

                    if (testInput) {
                        clearConsole();
                        titolo();
                        printf("\n----------");
                        printColor("\nAttenzione!\n", COLOR_RED);
                        printf("Luogo non valido.\n");
                        printf("----------\n\n");
                    } else {
                        strcpy(temp->luogo, luogo);
                    }

                } while (testInput);
                break;

            case 3:
                clearConsole();
                titolo();
                do {
                    notificaAnnulla(false);
                    testInput = false;
                    printf("Inserisci la citta': ");
                    fgets(citta, 20, stdin);
                    citta[strlen(citta) - 1] = 0;
                    citta[0] = toupper(citta[0]);

                    if (strlen(citta) == 0) {
                        continuaModifica = false;
                        break;
                    }
                    for (i = 0; i < strlen(citta); i++) {
                        if (isalpha(citta[i]) == 0 && citta[i] != ' ') {
                            testInput = true; //carattere non alfabetico
                        }
                    }

                    if (testInput) {
                        clearConsole();
                        titolo();
                        printf("\n----------");
                        printColor("\nAttenzione!\n", COLOR_RED);
                        printf("Citta' non valida.\n");
                        printf("----------\n\n");
                    } else {
                        strcpy(temp->citta, citta);
                    }
                } while (testInput);
                break;


            case 4:
                clearConsole();
                titolo();
                notificaAnnulla(false);

                printf("Inserisci l'indirizzo: ");
                fgets(indirizzo, 30, stdin);
                indirizzo[strlen(indirizzo) - 1] = 0;
                indirizzo[0] = toupper(indirizzo[0]);

                if (strlen(indirizzo) == 0) {
                    continuaModifica = false;
                    break;
                } else {
                    strcpy(temp->indirizzo, indirizzo);
                }
                break;

            case 5:;
                bool dataCorr = true;
                flagDate = false;

                clearConsole();
                titolo();
                notificaAnnulla(true);

                do {
                    do {
                        if (!dataCorr) {
                            clearConsole();
                            titolo();
                            printf("\n----------");
                            printColor("\nAttenzione!\n", COLOR_RED);
                            printf("La data inserita deve essere succesiva a quella corrente.\n");
                            printf("Si prega di inserirla nuovamente.\n");
                            printf("----------\n\n");
                        }

                        printf("Inserisci la data d'");
                        printColor("inizio ", COLOR_CYAN);
                        printf("mostra\n");

                        do {
                            if (!dataCorrettaIn) {
                                clearConsole();
                                titolo();
                                printf("\n----------");
                                printColor("\nAttenzione!\n", COLOR_RED);
                                printf("La data inserita non e' corretta.\nSi prega di inserirla nuovamente.\n");
                                printf("----------\n\n");
                            }

                            do {
                                printf("Giorno: ");
                                scanf("%d", &giornoIn);

                                if (giornoIn == 0) {
                                    continuaModifica = false;
                                    flagDate = true;
                                    break;
                                }

                            } while (giornoIn < 1 || giornoIn > 31);

                            if (continuaModifica) {

                                do {
                                    printf("Mese: ");
                                    scanf("%d", &meseIn);
                                } while (meseIn < 1 || meseIn > 12);

                                printf("Anno: ");
                                scanf("%d", &annoIn);

                                dataCorrettaIn = verificaData(giornoIn, meseIn, annoIn);
                            }

                        } while (!dataCorrettaIn);

                        if (giornoIn == 0) {
                            continuaModifica = false;
                            flagDate = true;
                            break;
                        }

                        dataCorr = ( differenzaDateOggi(giornoIn, meseIn, annoIn) >= 0 );
                    } while (!dataCorr);

                    if (continuaModifica) {
                        snprintf(dataIn, 11, "%d/%d/%d", giornoIn, meseIn, annoIn);

                        char *tok;
                        tok = strtok(temp->dataFine, "/");

                        while (tok) {
                            if (colonna == 0) {
                                giornoFin = atoi(tok);
                            }
                            if (colonna == 1) {
                                meseFin = atoi(tok);
                            }
                            if (colonna == 2) {
                                annoFin = atoi(tok);
                            }
                            tok = strtok(NULL, "/");
                            colonna++;
                        }

                        if (differenzaDate(giornoIn, meseIn, annoIn, giornoFin, meseFin, annoFin)) {
                            flagDate = true;
                        } else {
                            clearConsole();
                            titolo();
                            printf("\n----------\n");
                            printColor("Attenzione!\n", COLOR_RED);
                            printf("La data di fine mostra deve susseguire la data d'inizio.\n");
                            printf("Si prega di inserire nuovamente le date.\n");
                            printf("----------\n\n");
                        }
                    }

                    if (differenzaDate(giornoIn, meseIn, annoIn, giornoFin, meseFin, annoFin) >= 0) {
                        flagDate = true;
                    } else {
                        printf("\n----------\n");
                        printColor("Attenzione!\n", COLOR_RED);
                        printf("La data di fine mostra deve susseguire la data d'inizio.\n");
                        printf("Si prega di inserire nuovamente le date.\n");
                        printf("----------\n\n");
                    }

                } while (!flagDate);
                strcpy(temp->dataInizio, dataIn);
                break;

            case 6:
                flagDate = false;
                do {
                    printf("Inserisci la data di");
                    printColor("fine ", COLOR_CYAN);
                    printf("mostra\n");
                    do {
                        if (!dataCorrettaFin) {
                            clearConsole();
                            titolo();
                            printf("\n----------");
                            printColor("\nAttenzione!\n", COLOR_RED);
                            printf("La data inserita non e' corretta.\nSi prega di inserirla nuovamente.\n");
                            printf("----------\n\n");
                        }

                        do {
                            printf("Giorno: ");
                            scanf("%d", &giornoIn);

                            if (giornoIn == 0) {
                                continuaModifica = false;
                                flagDate = true;
                                break;
                            }

                        } while (giornoIn < 1 || giornoIn > 31);

                        if (continuaModifica) {
                            do {
                                printf("Mese: ");
                                scanf("%d", &meseFin);
                            } while (meseFin < 1 || meseFin > 12);

                            printf("Anno: ");
                            scanf("%d", &annoFin);

                            dataCorrettaFin = verificaData(giornoFin, meseFin, annoFin);
                        }

                    } while (!dataCorrettaFin);

                    if (continuaModifica) {

                        snprintf(dataFin, 11, "%d/%d/%d", giornoFin, meseFin, annoFin);

                        char *tok;
                        tok = strtok(temp->dataInizio, "/");

                        while (tok) {
                            if (colonna == 0) {
                                giornoIn = atoi(tok);
                            }
                            if (colonna == 1) {
                                meseIn = atoi(tok);
                            }
                            if (colonna == 2) {
                                annoIn = atoi(tok);
                            }
                            tok = strtok(NULL, "/");
                            colonna++;
                        }

                        if (differenzaDate(giornoIn, meseIn, annoIn, giornoFin, meseFin, annoFin) >= 0) {
                            flagDate = true;
                        } else {
                            clearConsole();
                            titolo();
                            printf("\n----------\n");
                            printColor("Attenzione!\n", COLOR_RED);
                            printf("La data di fine mostra deve susseguire la data d'inizio.\n");
                            printf("Si prega di inserire nuovamente le date.\n");
                            printf("----------\n\n");
                        }
                    }

                } while (!flagDate);
                strcpy(temp->dataFine, dataFin);
                break;

            default:
                break;
        }

        if (scelta != 0 && continuaModifica) {
            do {
                printf("----------\n");
                printf("Vuoi modificare un altro campo? (s/n): ");
                risposta = getchar();
                while ('\n' != getchar());

                //rendo la risposta in maiuscolo per evitare errori
                risposta = toupper(risposta);

                if (risposta == 'N') {
                    printf("prima \n");
                    scriviMostre(testa);
                }

            } while (risposta != 'S' && risposta != 'N');
        }

        clearConsole();
        titolo();
    } while (risposta == 'S' && scelta != 0);
}

/**
 * Function: stampaMostre
 * ----------------------------
 *   Permette di stampare a video l'elenco delle mostre
 *   Richiama stampaMostra()
 *
 *   @param testa puntatore alla variabile di tipo Mostra, una lista contenente tutte le mostre
 */
void stampaMostre(Mostra *testa) {
    for (Mostra *mostra = testa; mostra != NULL; mostra = mostra->nextMostra) {
        if (differenzaDateOggiChar(mostra->dataFine) == 1) {
            stampaMostra(mostra, false);
            printf("----------\n");
        }
    }
}

/**
 * Function: stampaMostra
 * ----------------------------
 *   Permette di stampare a video una mostra
 *
 *   @param mostra puntatore alla mostra da stampare a schermo
 *   @param stampaOpere mostra opere assegnate alla mostra se true
 */
void stampaMostra(Mostra *mostra, bool stampaOpere) {
    FILE *fpMO;
    fpMO = fopen("mostreopere.csv", "w"); //apertura file
    
    printf("Mostra numero: %d \n", mostra->id);
    printf("Responsabile: %s \n", mostra->responsabile);
    printf("Luogo di esposizione: %s \n", mostra->luogo);
    printf("Luogo: %s - %s\n", mostra->citta, mostra->indirizzo);
    printf("Durata: dal %s al %s\n", mostra->dataInizio, mostra->dataFine);
    
    //long sizeMO = ftell(fpMO);
    //if(sizeMO != 0) {
        if (stampaOpere) {
            if (mostra->opere != NULL) {
                printf("Opere nella mostra:\n");
                for (MostraOpera *temp = mostra->opere; temp != NULL; temp = temp->nextOpera) {
                    printf("\tID %d - %s di %s\n", temp->opera->id, temp->opera->nome, temp->opera->autore);
                }
            }
        }
    //}
}

/**
 * Function: scriviMostre
 * ----------------------------
 *   Permette di salvare tutte le modifiche effettuate sul file "mostre.csv" e "mostreopere.csv"
 *
 *   @param testa puntatore alla variabile di tipo Mostra, una lista contenente tutte le mostre e le opere associate
 */
void scriviMostre(Mostra *testa) {
    FILE *fp, *fpMO;
    fp = fopen("mostre.csv", "w"); //apertura file
    fpMO = fopen("mostreopere.csv", "w"); //apertura file

    for (Mostra *temp = testa; temp != NULL; temp = temp->nextMostra) {
        long size = ftell(fp);

        if (size == 0) {
            //file vuoto.
            fprintf(fp, "%d,%s,%s,%s,%s,%s,%s", temp->id, temp->responsabile, temp->luogo, temp->citta,
                    temp->indirizzo, temp->dataInizio, temp->dataFine);
        } else {
            //file pieno
            fprintf(fp, "\n%d,%s,%s,%s,%s,%s,%s", temp->id, temp->responsabile, temp->luogo, temp->citta,
                    temp->indirizzo, temp->dataInizio, temp->dataFine);
        }

        for (MostraOpera *tempMO = temp->opere; tempMO != NULL; tempMO = tempMO->nextOpera) {
            long sizeMO = ftell(fpMO);

            if (sizeMO == 0) {
                //file vuoto.
                fprintf(fpMO, "%d,%d", temp->id, tempMO->opera->id);
            } else {
                //file pieno
                fprintf(fpMO, "\n%d,%d", temp->id, tempMO->opera->id);
            }
        }
    }
    fclose(fp);
    fclose(fpMO);
}

/**
 * Function: eliminaMostra
 * ----------------------------
 *   Permette di eliminare una mostra.
 *   Richiamerà scriviMostre() una volta completata l'eliminazione per aggiornare i file
 *
 *   @param testa puntatore alla variabile di tipo Mostra, una lista contenente tutte le mostre e le opere associate
 *   @param mostra mostra da eliminare
 */
void eliminaMostra(Mostra *testa, Mostra *mostra) {
    char risposta;
    Mostra *curr, *prec;
    Mostra *temp = NULL;

    temp = mostra;
    prec = NULL;
    curr = testa;

    do {
        printColor("ATTENZIONE!\n", COLOR_RED);
        printf("Sei sicuro/a di voler eliminare la mostra?\n");
        printf("Risposta (s/n): ");
        scanf("%c", &risposta);
        printf("\n");

        //rendo la risposta tutta maiuscola per evitare errori
        risposta = toupper(risposta);

    } while (risposta != 'S' && risposta != 'N');

    clearConsole();
    titolo();

    if (risposta == 'S') {
        while (curr != NULL && temp->id != curr->id) {
            prec = curr;
            curr = curr->nextMostra;
        }

        if (temp->id == curr->id) {
            if (prec == NULL) { //elemento trovato in testa
                testa = curr->nextMostra;
            } else { //elemento al centro della lista
                prec->nextMostra = curr->nextMostra;
            }
            free(curr);
        }

        scriviMostre(testa);
        printColor("Eliminazione completata con successo!\n", COLOR_GREEN);
    }
}

/**
 * Function: eliminaOperaAMostra
 * ----------------------------
 *   Permette di modificare una mostra rimuovendone un opera associata
 *
 *   @param testa puntatore alla variabile di tipo Mostra, una lista contenente tutte le mostre e le opere associate
 *   @param mostra mostra da modificare
 *   @param idOpera id dell'opera da rimuovere dalla mostra
 */
void eliminaOperaAMostra(Mostra *testa, Mostra *mostra, int idOpera) {
    char risposta;
    do {
        printColor("ATTENZIONE!\n", COLOR_RED);
        printf("Sei sicuro/a di voler eliminare l'opera dalla mostra?\n");
        printf("Risposta (s/n): ");
        scanf("%c", &risposta);
        printf("\n");

        //rendo la risposta tutta maiuscola per evitare errori
        risposta = toupper(risposta);

    } while (risposta != 'S' && risposta != 'N');

    clearConsole();
    titolo();

    if (risposta == 'S') {

        MostraOpera *curr = mostra->opere, *prec = NULL;

        while (curr != NULL && curr->opera->id != idOpera) {
            prec = curr;
            curr = curr->nextOpera;
        }

        if (curr != NULL) {
            if (idOpera == curr->opera->id) {
                if (prec == NULL) { //elemento trovato in testa
                    mostra->opere = curr->nextOpera;
                } else { //elemento al centro della lista
                    prec->nextOpera = curr->nextOpera;
                }
                free(curr);
            }

            scriviMostre(testa);
            printColor("Eliminazione completata con successo!\n", COLOR_GREEN);
        }
    }
}

/**
 * Function: operaUsataInMostre
 * ----------------------------
 *   Verifica che un opera non sia esposta in una mostra del giorno corrente o futura
 *
 *   @param testa puntatore alla variabile di tipo Mostra, una lista contenente tutte le mostre e le opere associate
 *   @param idOpera id dell'opera da controllare
 *
 *   @return true se l'opera viene usata in una mostra del giorno corrente o futura
 */
bool operaUsataInMostre(Mostra *testa, int idOpera) {
    bool operaUsata = false;
    for (Mostra *mostra = testa; mostra != NULL; mostra = mostra->nextMostra) {
        if (differenzaDateOggiChar(mostra->dataFine) == -1) {
            if (mostra->opere != NULL) {
                for (MostraOpera *temp = mostra->opere; temp != NULL; temp = temp->nextOpera) {
                    if (temp->opera->id == idOpera) {
                        operaUsata = true;
                    }
                }
            }
        }
    }
    return operaUsata;
}

/**
 * Function: ricercaMostra
 * ----------------------------
 *   Effettua una ricerca cercando una mostra con un determinato id
 *
 *   @param testa puntatore alla variabile di tipo Mostra, una lista contenente tutte le mostre
 *   @param id id della mostra da ricercare
 *
 *   @return puntatore della mostra ricercata, o NULL se nessuna mostra trovata
 */
Mostra *ricercaMostra(Mostra *testa, int id) {
    bool flag = false;
    Mostra *nuovoNodo = NULL;

    for (Mostra *temp = testa; temp != NULL; temp = temp->nextMostra) {
        if (temp->id == id) {
            nuovoNodo = temp;
            flag = true;
            break;
        }
    }

    if (!flag) {
        clearConsole();
        titolo();
        printf("\n----------\n");
        printColor("Attenzione!\n", COLOR_RED);
        printf("Mostra non trovata.\n");
        printf("----------\n\n");
    }

    return nuovoNodo;
}

/**
 * Function: mostreBrowser
 * ----------------------------
 *   Permette una vista approfondita delle mostre con ricerca e possibilità di selezionare la mostra.
 *
 *   @param fp puntatore alla variabile di tipo FILE, precedentemente configurata, che punta al file mostre.csv
 *   @param testa puntatore alla variabile di tipo Mostra, una lista contenente tutte le mostre e le opere associate
 *   @param selezione se true permette di selezionare l'opera con return avvalorato
 *
 *   @return se selezione == true la mostra selezionata, altrimenti NULL
 */
Mostra *browserMostra(FILE *fp, Mostra *testa, bool selezione) {
    Mostra *mostraSelezionata = NULL;

    bool ricercaInCorso = true;
    int scelta, mostreTrovate;
    char input[30], tempName[30];

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);

    if (size == 0) { //non ci sono opere registrate
        printColor("Attenzione!\n", COLOR_RED);
        printf("Non ci sono mostre registrate.\n");
        while ('\n' != getchar());
        pausa();
        clearConsole();
        titolo();
    } else {

        clearConsole();
        titolo();

        do {
            printf("Selezionare tipo di ricerca:\n");
            printf("1: Ricerca Mostra per responsabile\n");
            printf("2: Ricerca Mostra per luogo\n");
            printf("3: Ricerca Mostra per citta\n");
            printf("9: Stampa tutte le mostre disponibili\n");
            printf("0: Annulla la ricerca\n");
            printf("-> ");
            scanf("%d", &scelta);

            switch (scelta) {

                case 1:
                    mostreTrovate = 0;
                    clearConsole();
                    titolo();
                    while ('\n' != getchar());
                    printf("Inserire nome completo o parziale del responsabile: ");
                    fgets(input, 30, stdin);
                    input[strlen(input) - 1] = 0;
                    printf("---------------------\n");
                    toUppercase(input);

                    if (strlen(input) != 0) {
                        for (Mostra *temp = testa; temp != NULL; temp = temp->nextMostra) {
                            strcpy(tempName, temp->responsabile);
                            toUppercase(tempName);
                            if (strstr(tempName, input) != NULL && differenzaDateOggiChar(temp->dataFine) >= 0) {
                                mostreTrovate++;
                                stampaMostra(temp, true);
                                printf("---------------------\n");
                            }
                        }
                        if (mostreTrovate > 0) {
                            if (selezione) {
                                printf("Digitare l'ID della mostra da selezionare: ");
                                fgets(input, 30, stdin);
                                input[strlen(input) - 1] = 0;
                                if (strlen(input) != 0) {
                                    scelta = atoi(input);
                                    mostraSelezionata = ricercaMostra(testa, scelta);
                                    ricercaInCorso = false;
                                }
                            } else {
                                pausa();
                                clearConsole();
                                titolo();
                            }
                        } else {
                            clearConsole();
                            titolo();
                            printColor("Nessuna mostra corrisponde alla ricerca, riprovare\n\n", COLOR_RED);
                        }
                    }
                    break;

                case 2:
                    mostreTrovate = 0;
                    clearConsole();
                    titolo();
                    while ('\n' != getchar());
                    printf("Inserire nome completo o parziale del luogo: ");
                    fgets(input, 30, stdin);
                    input[strlen(input) - 1] = 0;
                    printf("---------------------\n");
                    toUppercase(input);

                    if (strlen(input) != 0) {
                        for (Mostra *temp = testa; temp != NULL; temp = temp->nextMostra) {
                            strcpy(tempName, temp->luogo);
                            toUppercase(tempName);
                            if (strstr(tempName, input) != NULL && differenzaDateOggiChar(temp->dataFine) >= 0) {
                                mostreTrovate++;
                                stampaMostra(temp, true);
                                printf("---------------------\n");
                            }
                        }
                        if (mostreTrovate > 0) {
                            if (selezione) {
                                printf("Digitare l'ID della mostra da selezionare: ");
                                fgets(input, 30, stdin);
                                input[strlen(input) - 1] = 0;
                                if (strlen(input) != 0) {
                                    scelta = atoi(input);
                                    mostraSelezionata = ricercaMostra(testa, scelta);
                                    ricercaInCorso = false;
                                }
                            } else {
                                pausa();
                                clearConsole();
                                titolo();
                            }
                        } else {
                            clearConsole();
                            titolo();
                            printColor("Nessuna mostra corrisponde alla ricerca, riprovare\n\n", COLOR_RED);
                        }
                    }
                    break;

                case 3:
                    mostreTrovate = 0;
                    clearConsole();
                    titolo();
                    while ('\n' != getchar());
                    printf("Inserire nome completo o parziale della citta': ");
                    fgets(input, 30, stdin);
                    input[strlen(input) - 1] = 0;
                    printf("---------------------\n");
                    toUppercase(input);

                    if (strlen(input) != 0) {
                        for (Mostra *temp = testa; temp != NULL; temp = temp->nextMostra) {
                            strcpy(tempName, temp->citta);
                            toUppercase(tempName);
                            if (strstr(tempName, input) != NULL && differenzaDateOggiChar(temp->dataFine) >= 0) {
                                mostreTrovate++;
                                stampaMostra(temp, true);
                                printf("---------------------\n");
                            }
                        }
                        if (mostreTrovate > 0) {
                            if (selezione) {
                                printf("Digitare l'ID della mostra da selezionare: ");
                                fgets(input, 30, stdin);
                                input[strlen(input) - 1] = 0;
                                if (strlen(input) != 0) {
                                    scelta = atoi(input);
                                    mostraSelezionata = ricercaMostra(testa, scelta);
                                    ricercaInCorso = false;
                                }
                            } else {
                                pausa();
                                clearConsole();
                                titolo();
                            }
                        } else {
                            clearConsole();
                            titolo();
                            printColor("Nessuna mostra corrisponde alla ricerca, riprovare\n\n", COLOR_RED);
                        }
                    }
                    break;

                case 9:
                    clearConsole();
                    titolo();
                    stampaMostre(testa);
                    while ('\n' != getchar());
                    if (selezione) {
                        printf("Digitare l'ID della mostra da selezionare: ");
                        fgets(input, 30, stdin);
                        input[strlen(input) - 1] = 0;
                        if (strlen(input) != 0) {
                            scelta = atoi(input);
                            mostraSelezionata = ricercaMostra(testa, scelta);
                            ricercaInCorso = false;
                        }
                    } else {
                        pausa();
                        clearConsole();
                        titolo();
                    }

                case 0:
                    ricercaInCorso = false;
                    break;
                default:
                    break;
            }

        } while (ricercaInCorso);
        clearConsole();
        titolo();
    }

    return mostraSelezionata;
}
