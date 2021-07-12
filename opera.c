Opera *letturaOpere(FILE *fp) {
    int colonna = 0;
    char buf[BUFFER_SIZE];

    Opera *testaOpera = NULL;
    Opera *tempOpera = NULL; //temporanea
    Opera *precOpera = NULL;

    if (fp == NULL) {
        printColor("\t\t\t|-----------------------------|\n", COLOR_RED);
        printColor("\t\t\t|  File \"opere\" non trovato!  |\n", COLOR_RED);
        printColor("\t\t\t|             ...             |\n", COLOR_RED);
        printColor("\t\t\t|      File in creazione      |\n", COLOR_RED);
        printColor("\t\t\t|-----------------------------|\n", COLOR_RED);
    } else {
        while (!feof(fp)) {
            fgets(buf, BUFFER_SIZE, fp);
            tempOpera = (Opera *) malloc(sizeof(Opera));
            tempOpera->nextOpera = NULL;

            if (precOpera != NULL) {
                precOpera->nextOpera = tempOpera;
            } else {
                testaOpera = tempOpera;
            }

            char *tok;
            tok = strtok(buf, ",");

            while (tok) {
                if (colonna == 0) {
                    tempOpera->id = atoi(tok);
                }
                if (colonna == 1) {
                    strcpy(tempOpera->nome, tok);
                    tempOpera->nome[strlen(tempOpera->nome)] = 0;
                }
                if (colonna == 2) {
                    strcpy(tempOpera->autore, tok);
                    tempOpera->autore[strlen(tempOpera->autore)] = 0;
                }
                if (colonna == 3) {
                    strcpy(tempOpera->tipo, tok);
                    tempOpera->tipo[strlen(tempOpera->tipo)] = 0;
                }
                if (colonna == 4) {
                    strcpy(tempOpera->genere, tok);
                    tempOpera->genere[strlen(tempOpera->genere)] = 0;
                }
                if (colonna == 5) {
                    strcpy(tempOpera->periodo, tok);
                    tempOpera->periodo[strlen(tempOpera->periodo)] = 0;
                }
                if (colonna == 6) {
                    tempOpera->anno = atoi(tok);
                }
                tok = strtok(NULL, ",");
                colonna++;
            }
            colonna = 0;
            precOpera = tempOpera;
        }
    }
    return testaOpera;
}

void aggiungiOpera(Opera *testa) {

    Opera *curr, *prec;
    prec = NULL;
    curr = testa;

    int ultimoID = 0, i;
    int anno;
    bool testInput = false; //flag per controllare i vari input
    bool continuaInserimento = true;

    Opera *nuovoNodo = NULL;


    nuovoNodo = (Opera *) malloc(sizeof(Opera));

    FILE *fp;
    fp = fopen("opere.csv", "a+"); //apertura file

    while ('\n' != getchar());

    notificaAnnulla();

    do {
        testInput = false;
        printf("Inserisci Nome Opera: ");
        fgets(nuovoNodo->nome, 30, stdin);
        nuovoNodo->nome[strlen(nuovoNodo->nome) - 1] = 0;
        nuovoNodo->nome[0] = toupper(nuovoNodo->nome[0]);

        if (strlen(nuovoNodo->nome) == 0) {
            continuaInserimento = false;
            clearConsole();
            titolo();
            break;
        }

        for (i = 0; i < strlen(nuovoNodo->nome); i++) {
            if (isalpha(nuovoNodo->nome[i]) == 0) {
                testInput = true; //carattere non alfabetico
            }
        }

        if (testInput) {
            clearConsole();
            titolo();
            printf("\n----------");
            printColor("\nAttenzione!\n", COLOR_RED);
            printf("Nome non valido.\n");
            printf("----------\n\n");
        }
    } while (testInput);

    if (continuaInserimento) {

        do {
            testInput = false;
            printf("Inserisci Autore: ");
            fgets(nuovoNodo->autore, 30, stdin);
            nuovoNodo->autore[strlen(nuovoNodo->autore) - 1] = 0;
            nuovoNodo->autore[0] = toupper(nuovoNodo->autore[0]);

            for (i = 0; i < strlen(nuovoNodo->autore); i++) {
                if (isalpha(nuovoNodo->autore[i]) == 0) {
                    testInput = true; //carattere non alfabetico
                }
            }

            if (testInput) {
                clearConsole();
                titolo();
                printf("\n----------");
                printColor("\nAttenzione!\n", COLOR_RED);
                printf("Autore non valido.\n");
                printf("----------\n\n");
            }
        } while (testInput || strlen(nuovoNodo->autore) == 0);

        do {
            testInput = false;
            printf("Inserisci Tipologia dell'Opera (es. dipinto): ");
            fgets(nuovoNodo->tipo, 20, stdin);
            nuovoNodo->tipo[strlen(nuovoNodo->tipo) - 1] = 0;
            nuovoNodo->tipo[0] = toupper(nuovoNodo->tipo[0]);

            for (i = 0; i < strlen(nuovoNodo->tipo); i++) {
                if (isalpha(nuovoNodo->tipo[i]) == 0) {
                    testInput = true; //carattere non alfabetico
                }
            }

            if (testInput) {
                clearConsole();
                titolo();
                printf("\n----------");
                printColor("\nAttenzione!\n", COLOR_RED);
                printf("Tipologia opera non valida.\n");
                printf("----------\n\n");
            }
        } while (testInput || strlen(nuovoNodo->tipo) == 0);

        do {
            testInput = false;
            printf("Inserisci Genere (es. ritratto): ");
            fgets(nuovoNodo->genere, 20, stdin);
            nuovoNodo->genere[strlen(nuovoNodo->genere) - 1] = 0;
            nuovoNodo->genere[0] = toupper(nuovoNodo->genere[0]);

            for (i = 0; i < strlen(nuovoNodo->genere); i++) {
                if (isalpha(nuovoNodo->genere[i]) == 0) {
                    testInput = true; //carattere non alfabetico
                }
            }

            if (testInput) {
                clearConsole();
                titolo();
                printf("\n----------");
                printColor("\nAttenzione!\n", COLOR_RED);
                printf("Tipologia opera non valida.\n");
                printf("----------\n\n");
            }
        } while (testInput);

        do {
            testInput = false;
            printf("Inserisci Periodo storico (es. Barocco): ");
            fgets(nuovoNodo->periodo, 20, stdin);
            nuovoNodo->periodo[strlen(nuovoNodo->periodo) - 1] = 0;
            nuovoNodo->periodo[0] = toupper(nuovoNodo->periodo[0]);

            for (i = 0; i < strlen(nuovoNodo->periodo); i++) {
                if (isalpha(nuovoNodo->periodo[i]) == 0) {
                    testInput = true; //carattere non alfabetico
                }
            }

            if (testInput) {
                clearConsole();
                titolo();
                printf("\n----------");
                printColor("\nAttenzione!\n", COLOR_RED);
                printf("Periodo storico non valida.\n");
                printf("----------\n\n");
            }
        } while (testInput || strlen(nuovoNodo->periodo) == 0);

        do {
            do {
                printf("Inserisci l'anno: ");
                scanf("%d", &nuovoNodo->anno);
            } while (nuovoNodo->anno < 1);
            
            printf("\n");
                

            //controllo data corrente
            time_t now;
            struct tm *ts;
            char annoCorrente[5];

            now = time(NULL);

            ts = localtime(&now);
            strftime(annoCorrente, sizeof(annoCorrente), "%Y", ts);
            anno = atoi(annoCorrente);
        } while (nuovoNodo->anno > anno);

        //verifico se nel file ci sono già delle opere registrate o meno
        fseek(fp, 0, SEEK_END);
        long size = ftell(fp);

        ultimoID = letturaUltimoID("opere.csv") + 1;

        //ricerca della posizione di inserimento
        while (curr != NULL && ultimoID > curr->id) {
            prec = curr;
            curr = curr->nextOpera;
        }

        if (size == 0) { //file vuoto
            nuovoNodo->id = 0;
            fprintf(fp, "%d,%s,%s,%s,%s,%s,%d", nuovoNodo->id, nuovoNodo->nome, nuovoNodo->autore,
                    nuovoNodo->tipo, nuovoNodo->genere, nuovoNodo->periodo, nuovoNodo->anno);

        } else { //file pieno
            nuovoNodo->id = ultimoID;
            fprintf(fp, "\n%d,%s,%s,%s,%s,%s,%d", nuovoNodo->id, nuovoNodo->nome, nuovoNodo->autore,
                    nuovoNodo->tipo, nuovoNodo->genere, nuovoNodo->periodo, nuovoNodo->anno);
        }

        fclose(fp);

        //aggiornamento dei collegamenti
        if (prec == NULL) {
            nuovoNodo->nextOpera = testa;
            testa = nuovoNodo;
        } else {
            prec->nextOpera = nuovoNodo;
            nuovoNodo->nextOpera = curr;
        }
    }
    clearConsole();
    titolo();
}

void modificaOpera(Opera *testa, Opera *opera) {

    bool continuaModifica = true;
    int scelta;
    char risposta = '\0';
    
    char nome[30];
    char autore[30];
    char tipo[20];
    char genere[20];
    char periodo[20];
    int anno;
    
    Opera *temp = NULL;
    temp = opera;

    printColor("\nDati relativi alla opera scelta:\n", COLOR_CYAN);
    printf("id: %d\n", opera->id);
    printf("Nome Opera: %s\n", opera->nome);
    printf("Di %s\n", opera->autore);
    printf("Genere: %s\n", opera->genere);
    printf("Tipologia: %s\n", opera->tipo);
    printf("Periodo: %s\n", opera->periodo);
    printf("Anno: %d\n", opera->anno);
    printColor("----------\n\n", COLOR_CYAN);
    do {

        //elenco campi modificabili
        printf("Scegliere il campo da modificare\n");
        printf("----------\n");
        printf("1: Nome\n");
        printf("2: Autore\n");
        printf("3: Tipo\n");
        printf("4: Genere\n");
        printf("5: Periodo\n");
        printf("6: Anno\n");
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
                notificaAnnulla();
                
                printf("Inserisci il Nome dell'Opera: ");
                fgets(nome, 30, stdin);
                nome[strlen(nome) - 1] = 0;
                nome[0] = toupper(nome[0]);
                
                if(strlen(nome) == 0) {
                    continuaModifica = false;
                    break;
                } else {
                    strcpy(opera->nome, nome);
                }
                break;

            case 2:
                clearConsole();
                titolo();
                notificaAnnulla();
                
                printf("Inserisci l'Autore: ");
                fgets(autore, 30, stdin);
                autore[strlen(autore) - 1] = 0;
                autore[0] = toupper(autore[0]);
                
                if(strlen(autore) == 0) {
                    continuaModifica = false;
                    break;
                } else {
                    strcpy(opera->autore, autore);
                }
                break;

            case 3:
                clearConsole();
                titolo();
                notificaAnnulla();
                
                printf("Inserisci la Tipologia dell'Opera: ");
                fgets(tipo, 20, stdin);
                tipo[strlen(tipo) - 1] = 0;
                tipo[0] = toupper(tipo[0]);
                
                if(strlen(tipo) == 0) {
                    continuaModifica = false;
                    break;
                } else {
                    strcpy(opera->tipo, tipo);
                }
                break;
                
            case 4:
                clearConsole();
                titolo();
                notificaAnnulla();
                
                printf("Inserisci il Genere: ");
                fgets(genere, 20, stdin);
                genere[strlen(genere) - 1] = 0;
                genere[0] = toupper(genere[0]);
                
                if(strlen(genere) == 0) {
                    continuaModifica = false;
                    break;
                } else {
                    strcpy(genere, genere);
                }
                break;
                
            case 5:
                clearConsole();
                titolo();
                notificaAnnulla();
                
                printf("Inserisci il Periodo: ");
                fgets(periodo, 20, stdin);
                periodo[strlen(periodo) - 1] = 0;
                periodo[0] = toupper(periodo[0]);
                
                if(strlen(periodo) == 0) {
                    continuaModifica = false;
                    break;
                } else {
                    strcpy(opera->periodo, periodo);
                }
                break;

            case 6:
                clearConsole();
                titolo();
                
                consoleColor(COLOR_RED);
                printf("\t\t\t|-----------------------------|\n");
                printf("\t\t\t|         Attenzione!         |\n");
                printf("\t\t\t|   Se hai sbagliato e vuoi   |\n");
                printf("\t\t\t|       tornare al menu'      |\n");
                printf("\t\t\t|      premere il tasto 0     |\n");
                printf("\t\t\t|-----------------------------|\n");
                consoleColor(COLOR_RESET);
                
                do {
                    printf("Inserisci l'Anno: ");
                    scanf("%d", &anno);
                    
                    if(anno == 0) {
                        continuaModifica = false;
                        break;
                    }
                } while(anno < 0);
                
                if(continuaModifica) {
                    opera->anno = anno;
                }
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
                    scriviOpere(testa);
                }

            } while (risposta != 'S' && risposta != 'N');
        } else {
            scriviOpere(testa);
        }
        
        clearConsole();
        titolo();
    } while (risposta == 'S' && scelta != 0);
}

//stampa a video
void stampaOpere(Opera *testa) {
    for (Opera *temp = testa; temp != NULL; temp = temp->nextOpera) {
        stampaOpera(temp);
        printf("----------\n");
    }
}

void stampaOpera(Opera *opera) {
    printf("Id: %d\n", opera->id);
    printf("Nome Opera: %s\n", opera->nome);
    printf("Di %s\n", opera->autore);
    printf("Genere: %s\n", opera->genere);
    printf("Tipologia: %s\n", opera->tipo);
    printf("Periodo: %s\n", opera->periodo);
    printf("Anno: %d\n", opera->anno);
}

//scrittura su file
void scriviOpere(Opera *testa) {
    Opera *temp = NULL;
    FILE *fp;
    fp = fopen("opere.csv", "w"); //apertura file

    for (temp = testa; temp != NULL; temp = temp->nextOpera) {
        long size = ftell(fp);

        if (size == 0)   //file vuoto.
        {
            fprintf(fp, "%d,%s,%s,%s,%s,%s,%d", temp->id, temp->nome, temp->autore, temp->tipo,
                    temp->genere, temp->periodo, temp->anno);
        } else     //file pieno
        {
            fprintf(fp, "\n%d,%s,%s,%s,%s,%s,%d", temp->id, temp->nome, temp->autore, temp->tipo,
                    temp->genere, temp->periodo, temp->anno);
        }
    }
    fclose(fp);
}

void eliminaOpera(Opera *testa, Opera *opera) {
    char risposta;
    Opera *curr, *prec;
    Opera *temp;

    temp = opera;
    prec = NULL;
    curr = testa;

    do {
        //while ('\n' != getchar());
        printColor("ATTENZIONE!\n", COLOR_RED);
        printf("Sei sicuro/a di voler eliminare l'opera?\n");
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
            curr = curr->nextOpera;
        }

        if (temp->id == curr->id) {
            if (prec == NULL) {
                //elemento trovato in testa
                testa = curr->nextOpera;
            } else {
                //elemento al centro della lista
                prec->nextOpera = curr->nextOpera;
            }
            free(curr);
        }
        scriviOpere(testa);
        printColor("Eliminazione completata con successo!\n", COLOR_GREEN);
        
    }
}

Opera *ricercaOpera(Opera *testa, int id) {
    bool flag = false;
    Opera *nuovoNodo = NULL;

    for (Opera *temp = testa; temp != NULL; temp = temp->nextOpera) {

        if (temp->id == id) {

            nuovoNodo = temp;
            flag = true;
            break;

        }
    }

    if (!flag) {
        printf("\n----------\n");
        printColor("Attenzione!", COLOR_RED);
        printf("Opera non trovata.\n");
        printf("----------\n\n");
    }

    return nuovoNodo;
}

/*
 * Function: opereBrowser
 * ----------------------------
 *   Permette una vista approfondita delle opere, con ricerca,
 *      possibilità di modificare l'opera, possibilità di selezionare
 *      l'opera.
 *
 *   FILE fp: TODO: finire
 *   Opera testa: TODO: finire
 *   bool selezione: se true permette di selezionare l'opera con return avvalorato
 *
 *   returns: se selezione == true l'opera selezionata, altrimenti NULL
 */

Opera *browserOpere(FILE *fp, Opera *testa, bool selezione) {
    Opera *operaSelezionata = NULL;

    bool ricercaInCorso = true;
    int scelta, opereTrovate;
    char input[30], tempName[30];

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);

    if (size == 0) { //non ci sono opere registrate
        printf("\n----------\n");
        printColor("Attenzione!", COLOR_RED);
        printf("Non ci sono opera registrate.\n");
        printf("----------\n\n");
    } else {

        clearConsole();
        titolo();

        do {
            printf("Selezionare tipo di ricerca:\n");
            printf("1: Ricerca Opera per nome\n");
            printf("2: Ricerca Opera per autore\n");
            printf("3: Ricerca Opera per tipo\n");
            printf("4: Ricerca Opera per genere\n");
            printf("5: Ricerca Opera per periodo\n");
            printf("6: Ricerca Opera per anno\n");
            printf("0: Annulla la ricerca\n");
            printf("-> ");
            scanf("%d", &scelta);
            printf("\n");

            switch (scelta) {
                case 1:
                    opereTrovate = 0;
                    clearConsole();
                    titolo();
                    while ('\n' != getchar());
                    printf("Inserire nome completo o parziale dell'opera: ");
                    fgets(input, 30, stdin);
                    input[strlen(input) - 1] = 0;
                    toUppercase(input);

                    if (strlen(input) != 0) {
                        for (Opera *temp = testa; temp != NULL; temp = temp->nextOpera) {
                            strcpy(tempName, temp->nome);
                            toUppercase(tempName);
                            
                            if (strstr(tempName, input) != NULL) {
                                opereTrovate++;
                                stampaOpera(temp);
                                printf("---------------------\n");
                            }
                        }
                        if (opereTrovate > 0) {
                            if (selezione) {
                                printf("Digitare l'ID dell'opera da selezionare: ");
                                fgets(input, 30, stdin);
                                input[strlen(input) - 1] = 0;
                                if (strlen(input) != 0) {
                                    scelta = atoi(input);
                                    operaSelezionata = ricercaOpera(testa, scelta);
                                    ricercaInCorso = false;
                                }
                            } else {
                                pausa();
                                titolo();
                            }
                        } else {
                            clearConsole();
                            titolo();
                            printColor("Nessuna opera corrisponde alla ricerca, riprovare\n\n", COLOR_RED);
                        }
                    }
                    break;
                case 2:
                    opereTrovate = 0;
                    clearConsole();
                    titolo();
                    while ('\n' != getchar());
                    printf("Inserire nome completo o parziale dell'autore: ");
                    fgets(input, 30, stdin);
                    input[strlen(input) - 1] = 0;
                    toUppercase(input);

                    if (strlen(input) != 0) {
                        for (Opera *temp = testa; temp != NULL; temp = temp->nextOpera) {
                            strcpy(tempName, temp->autore);
                            toUppercase(tempName);
                            if (strstr(tempName, input) != NULL) {
                                opereTrovate++;
                                stampaOpera(temp);
                                printf("---------------------\n");
                            }
                        }
                        if (opereTrovate > 0) {
                            if (selezione) {
                                printf("Digitare l'ID dell'opera da selezionare: ");
                                fgets(input, 30, stdin);
                                input[strlen(input) - 1] = 0;
                                if (strlen(input) != 0) {
                                    scelta = atoi(input);
                                    operaSelezionata = ricercaOpera(testa, scelta);
                                    ricercaInCorso = false;
                                }
                            } else {
                                pausa();
                                titolo();
                            }
                        } else {
                            clearConsole();
                            titolo();
                            printColor("Nessuna opera corrisponde alla ricerca, riprovare\n\n", COLOR_RED);
                        }
                    }
                    break;
                case 3:
                    opereTrovate = 0;
                    clearConsole();
                    titolo();
                    while ('\n' != getchar());
                    printf("Inserire la tipologia dell'opera: ");
                    fgets(input, 30, stdin);
                    input[strlen(input) - 1] = 0;
                    toUppercase(input);

                    if (strlen(input) != 0) {
                        for (Opera *temp = testa; temp != NULL; temp = temp->nextOpera) {
                            strcpy(tempName, temp->tipo);
                            toUppercase(tempName);
                            if (strstr(tempName, input) != NULL) {
                                opereTrovate++;
                                stampaOpera(temp);
                                printf("---------------------\n");
                            }
                        }
                        if (opereTrovate > 0) {
                            if (selezione) {
                                printf("Digitare l'ID dell'opera da selezionare: ");
                                fgets(input, 30, stdin);
                                input[strlen(input) - 1] = 0;
                                if (strlen(input) != 0) {
                                    scelta = atoi(input);
                                    operaSelezionata = ricercaOpera(testa, scelta);
                                    ricercaInCorso = false;
                                }
                            } else {
                                pausa();
                                titolo();
                            }
                        } else {
                            clearConsole();
                            titolo();
                            printColor("Nessuna opera corrisponde alla ricerca, riprovare\n\n", COLOR_RED);
                        }
                    }
                    break;
                case 4:
                    opereTrovate = 0;
                    clearConsole();
                    titolo();
                    while ('\n' != getchar());
                    printf("Inserire il genere dell'opera: ");
                    fgets(input, 30, stdin);
                    input[strlen(input) - 1] = 0;
                    toUppercase(input);

                    if (strlen(input) != 0) {
                        for (Opera *temp = testa; temp != NULL; temp = temp->nextOpera) {
                            strcpy(tempName, temp->genere);
                            toUppercase(tempName);
                            if (strstr(tempName, input) != NULL) {
                                opereTrovate++;
                                stampaOpera(temp);
                                printf("---------------------\n");
                            }
                        }
                        if (opereTrovate > 0) {
                            if (selezione) {
                                printf("Digitare l'ID dell'opera da selezionare: ");
                                fgets(input, 30, stdin);
                                input[strlen(input) - 1] = 0;
                                if (strlen(input) != 0) {
                                    scelta = atoi(input);
                                    operaSelezionata = ricercaOpera(testa, scelta);
                                    ricercaInCorso = false;
                                }
                            } else {
                                pausa();
                                titolo();
                            }
                        } else {
                            clearConsole();
                            titolo();
                            printColor("Nessuna opera corrisponde alla ricerca, riprovare\n\n", COLOR_RED);
                        }
                    }
                    break;
                case 5:
                    opereTrovate = 0;
                    clearConsole();
                    titolo();
                    while ('\n' != getchar());
                    printf("Inserire il perido dell'opera: ");
                    fgets(input, 30, stdin);
                    input[strlen(input) - 1] = 0;
                    toUppercase(input);

                    if (strlen(input) != 0) {
                        for (Opera *temp = testa; temp != NULL; temp = temp->nextOpera) {
                            strcpy(tempName, temp->periodo);
                            toUppercase(tempName);
                            if (strstr(tempName, input) != NULL) {
                                opereTrovate++;
                                stampaOpera(temp);
                                printf("---------------------\n");
                            }
                        }
                        if (opereTrovate > 0) {
                            if (selezione) {
                                printf("Digitare l'ID dell'opera da selezionare: ");
                                fgets(input, 30, stdin);
                                input[strlen(input) - 1] = 0;
                                if (strlen(input) != 0) {
                                    scelta = atoi(input);
                                    operaSelezionata = ricercaOpera(testa, scelta);
                                    ricercaInCorso = false;
                                }
                            } else {
                                pausa();
                                titolo();
                            }
                        } else {
                            clearConsole();
                            titolo();
                            printColor("Nessuna opera corrisponde alla ricerca, riprovare\n\n", COLOR_RED);
                        }
                    }
                    break;
                case 6:
                    do {
                        printf("Selezionare tipo di ricerca:\n");
                        printf("1: Ricerca per anno\n");
                        printf("2: Ricerca per decennio\n");
                        printf("3: Ricerca per secolo\n");
                        printf("0: Annulla la ricerca\n");
                        printf("-> ");
                        scanf("%d", &scelta);
                    } while (scelta != 0);
                case 0:
                    ricercaInCorso = false;
                    break;
                default:
                    break;
            }
        } while (ricercaInCorso);
        clearConsole();
    }

    return operaSelezionata;
}
