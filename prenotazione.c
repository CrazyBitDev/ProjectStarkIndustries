Prenotazione *letturaPrenotazioni(FILE *fp, Utente *testaUtente, Mostra *testaMostra) {
    int colonna = 0;
    char buf[BUFFER_SIZE];

    Prenotazione *testaPrenotazione = NULL;
    Prenotazione *tempPrenotazione  = NULL; //temporanea
    Prenotazione *precPrenotazione  = NULL;

    if (fp == NULL) {
        printColor("\t\t\t|--------------------------------|\n", COLOR_RED);
        printColor("\t\t\t|File \"prenotazioni\" non trovato!|\n", COLOR_RED);
        printColor("\t\t\t|\t\t...              |\n", COLOR_RED);
        printColor("\t\t\t|       File in creazione        |\n", COLOR_RED);
        printColor("\t\t\t|--------------------------------|\n", COLOR_RED);
    } else {
        while (!feof(fp)) {
            fgets(buf, BUFFER_SIZE, fp);
            tempPrenotazione = (Prenotazione *) malloc(sizeof(Prenotazione));
            tempPrenotazione->nextPrenotazione = NULL;

            if (precPrenotazione != NULL) {
                precPrenotazione->nextPrenotazione = tempPrenotazione;
            } else {
                testaPrenotazione = tempPrenotazione;
            }

            char *tok;
            tok = strtok(buf, ",");

            while (tok) {
                if (colonna == 0) {
                    tempPrenotazione->id = atoi(tok);
                }
                if (colonna == 1) {
                    tempPrenotazione->utente = ricercaUtente(testaUtente,atoi(tok));
                }
                if (colonna == 2) {
                    tempPrenotazione->mostra = ricercaMostra(testaMostra,atoi(tok));
                }
                if (colonna == 3) {
                    strcpy(tempPrenotazione->data, tok);
                    tempPrenotazione->data[strlen(tempPrenotazione->data)] = 0;
                }
                if (colonna == 4) {
                    strcpy(tempPrenotazione->ora, tok);
                    tempPrenotazione->ora[strlen(tempPrenotazione->ora)] = 0;
                }
                tok = strtok(NULL, ",");
                colonna++;
            }
            colonna = 0;
            precPrenotazione = tempPrenotazione;
        }
    }
    return testaPrenotazione;
}

void registrazionePrenotazione(Prenotazione *testa, Utente *utente, Mostra *mostra) {
    
    Prenotazione *curr, *prec;
    prec = NULL;
    curr = testa;

    int ultimoID = 0, i;
    bool testInput = false; //flag per controllare i vari input
    bool continuaInserimento = true;

    bool dataCorretta = true, continuaModifica = true;
    int giorno, mese, anno, ora, minuti;

    Prenotazione *nuovoNodo = NULL;


    nuovoNodo = (Prenotazione *) malloc(sizeof(Prenotazione));

    FILE *fp;
    fp = fopen("prenotazioni.csv", "a+"); //apertura file

    while ('\n' != getchar());

    consoleColor(COLOR_RED);
    printf("\t\t\t|-----------------------------|\n");
    printf("\t\t\t|         Attenzione!         |\n");
    printf("\t\t\t|   Se hai sbagliato e vuoi   |\n");
    printf("\t\t\t|       tornare al menu'      |\n");
    printf("\t\t\t|      premere il tasto 0     |\n");
    printf("\t\t\t|-----------------------------|\n");
    consoleColor(COLOR_RESET);

    printf("Inserisci data di prenotazione\n");
    
    do {
        if (!dataCorretta) {
            clearConsole();
            printColor("\nAttenzione!\n", COLOR_RED);
            printf("La data inserita non e' corretta.\nSi prega di inserirla nuovamente\n\n");
        }
        
        do {
            printf("Giorno: ");
            scanf("%d", &giorno);
            
            if(giorno == 0) {
                continuaModifica = false;
                break;
            }
            
        } while (giorno < 1 || giorno > 31);
        
        if(continuaModifica) {
            do {
                printf("Mese: ");
                scanf("%d", &mese);
            } while (mese < 1 || mese > 12);
            
            printf("Anno: ");
            scanf("%d", &anno);
            
            dataCorretta = dataInIntervallo(giorno, mese, anno, mostra->dataInizio, mostra->dataFine);
        }
        
    } while (!dataCorretta);

    snprintf(nuovoNodo->data, 11, "%d/%d/%d", giorno, mese, anno);
    
    if(continuaModifica) {
        do {
            printf("Ora: ");
            scanf("%d", &ora);
        } while (ora < 0 || ora > 24);
        
        do {
            printf("Minuti: ");
            scanf("%d", &minuti);
        } while (minuti < 0 || minuti >= 60);

        snprintf(nuovoNodo->ora, 11, "%d:%d", ora, minuti);

        nuovoNodo->utente = utente;
        nuovoNodo->mostra = mostra;

                //verifico se nel file ci sono già delle mmostre registrate o meno
        fseek(fp, 0, SEEK_END);
        long size = ftell(fp);
        
        ultimoID = letturaUltimoID("prenotazioni.csv") + 1;
        
        //ricerca della posizione di inserimento
        while (curr != NULL && ultimoID > curr->id) {
            prec = curr;
            curr = curr->nextPrenotazione;
        }
        
        if (size == 0) { //file vuoto
            nuovoNodo->id = 0;
            fprintf(fp, "%d,%d,%d,%s,%s", nuovoNodo->id, nuovoNodo->utente->id, nuovoNodo->mostra->id,
                    nuovoNodo->data, nuovoNodo->ora);
            
        } else { //file pieno
            nuovoNodo->id = ultimoID;
            fprintf(fp, "\n%d,%d,%d,%s,%s", nuovoNodo->id, nuovoNodo->utente->id, nuovoNodo->mostra->id,
                    nuovoNodo->data, nuovoNodo->ora);
        }
        
        fclose(fp);

    }

    
    clearConsole();
    titolo();
}

void modificaPrenotazione(Prenotazione *testa, Prenotazione *prenotazione) {
    int scelta, colonna = 0;
    char risposta = '\0';
    bool flagDate = false;
    bool continuaModifica = true;
    
    Prenotazione *temp = NULL;
    temp = prenotazione;
    
    char responsabile[30];
    char luogo[25];
    char citta[20];
    char indirizzo[30];
    
    bool dataCorrettaIn = true;
    int giorno = 0, mese = 0, anno = 0;

    int giornoFin = 0, meseFin = 0, annoFin = 0;
    bool dataCorrettaFin = true;
    
    
    stampaPrenotazione(prenotazione);
    
    do {
        while ('\n' != getchar());
        
        //elenco campi modificabili
        printf("Scegliere il campo da modificare\n");
        printf("----------\n");
        printf("1: Data\n");
        printf("2: Ora\n");
        printf("0: Annulla\n");
        printf("----------\n");
        printf("-> ");
        scanf("%d", &scelta);
        printf("\n");
        while ('\n' != getchar());
        
        switch (scelta) {
            case 0:
                break;

            case 1:;
                bool dataCorr = true;
                flagDate = false;
                char dataIn[11];
                
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
                    do {
                        if(!dataCorr) {
                            clearConsole();
                            titolo();
                            printf("\n----------");
                            printColor("\nAttenzione!\n", COLOR_RED);
                            printf("Si prega di inserirla nuovamente.\n");
                            printf("----------\n\n");
                        }
                        
                        printf("Inserisci la nuova data:\n");
                        
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
                                scanf("%d", &giorno);
                                
                                if(giorno == 0) {
                                    continuaModifica = false;
                                    flagDate = true;
                                    break;
                                }
                                
                            } while (giorno < 1 || giorno > 31);
                            
                            if(continuaModifica) {
                                
                                do {
                                    printf("Mese: ");
                                    scanf("%d", &mese);
                                } while (mese < 1 || mese > 12);
                                
                                printf("Anno: ");
                                scanf("%d", &anno);
                                
                                dataCorrettaIn = verificaData(giorno, mese, anno);
                            }
                        
                        } while (!dataCorrettaIn);
                        
                        if(giorno == 0) {
                            continuaModifica = false;
                            flagDate = true;
                            break;
                        }
                        
                        dataCorr = verificaDataCorrente(giorno, mese, anno);
                    } while (!dataCorr);
                        
                    if(continuaModifica) {
                        
                        char *tok;
                        tok = strtok(temp->mostra->dataFine, "/");
                        
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
                        
                        if (differenzaDate(giorno, mese, anno, giornoFin, meseFin, annoFin) >= 1) {
                            flagDate = true;
                        } else {
                            clearConsole();
                            titolo();
                            printf("\n----------");
                            printColor("Attenzione!\n", COLOR_RED);
                            printf("La data di fine mostra deve susseguire la data d'inizio.\n");
                            printf("Si prega di inserire nuovamente le date.\n");
                            printf("----------\n\n");
                        }
                    }
                
                } while (!flagDate);
                snprintf(dataIn, 11, "%d/%d/%d", giorno, mese, anno);
                strcpy(temp->data, dataIn);
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
                    scriviPrenotazioni(testa);
                }

            } while (risposta != 'S' && risposta != 'N');
        } else {
            scriviPrenotazioni(testa);
        }
        
        clearConsole();
        titolo();
    } while (risposta == 'S' && scelta != 0);
}

//stampa a video
void stampaPrenotazioni(Prenotazione *testa) {
    for (Prenotazione *temp = testa; temp != NULL; temp = temp->nextPrenotazione) {
        stampaPrenotazione(temp);
        printf("----------\n");
    }
}

void stampaPrenotazioniUtente(Prenotazione *testa, Utente *utente) {
    for (Prenotazione *temp = testa; temp != NULL; temp = temp->nextPrenotazione) {
        if (temp->utente->id == utente->id) {
            stampaPrenotazione(temp);
            printf("----------\n");
        }
    }
}

void stampaPrenotazione(Prenotazione *prenotazione) {
    printf("id: %d\n", prenotazione->id);
    printf("Utente: %s %s\n", prenotazione->utente->nome, prenotazione->utente->cognome);
    printf("Id mostra: %d\n", prenotazione->mostra->id);
    printf("Data: %s\n", prenotazione->data);
    printf("Ora: %s\n", prenotazione->ora);
}

//scrittura su file
void scriviPrenotazioni(Prenotazione *testa) {
    FILE *fp;
    fp = fopen("prenotazione.csv", "w"); //apertura file

    for (Prenotazione *temp = testa; temp != NULL; temp = temp->nextPrenotazione) {
        long size = ftell(fp);

        if (size == 0)   //file vuoto.
        {
            fprintf(fp, "%d,%d,%d,%s,%s", temp->id, temp->utente->id, temp->mostra->id, temp->data, temp->ora);
        } else     //file pieno
        {
            fprintf(fp, "\n%d,%d,%d,%s,%s", temp->id, temp->utente->id, temp->mostra->id, temp->data, temp->ora);
        }
    }
    fclose(fp);
}


Prenotazione *ricercaPrenotazione(Prenotazione *testa, int id) {
    bool flag = false;
    Prenotazione *nuovoNodo = NULL;

    for (Prenotazione *temp = testa; temp != NULL; temp = temp->nextPrenotazione) {

        if (temp->id == id) {

            nuovoNodo = temp;
            flag = true;
            break;

        }
    }

    if (!flag) {
        printColor("---Mostra non trovata!---\n", COLOR_RED);
    }

    return nuovoNodo;
}

bool prenotazioneModificabile(Prenotazione *prenotazione) {

    int data[3];
    char dataPrenotazione[11];
    
    strcpy(dataPrenotazione, prenotazione->data);

    char *tok = strtok(dataPrenotazione, "/");

    for (int i = 0; i < 3; i++ ) {
        data[i] = atoi(tok);
        tok = strtok(NULL, "/");
    }

    data[0] = data[0] - 2;
    if (data[0]<1) {
        int giorniDaSottrarre = data[0];
        data[1]--;
        if (data[1]<1) {
            data[2]--;
            data[1]=12;
        }
        if (data[1] == 2) {
            data[0] = ( annoBisestile(data[3]) ? 29 : 28 ) + giorniDaSottrarre;
        } else {
            switch(data[1]) {
                case 4:
                case 6:
                case 9:
                case 11:
                    data[0] = 30 + giorniDaSottrarre;
                    break;

                default:
                    data[0] = 31 + giorniDaSottrarre;
                    break;    
            }
        }
    }

    return (differenzaDateOggi(data[0], data[1], data[2]) == 1);
}

void eliminaPrenotazione(Prenotazione *testa, Prenotazione *prenotazione) {

}