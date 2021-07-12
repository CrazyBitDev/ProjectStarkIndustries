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

//stampa a video
void stampaPrenotazioni(Prenotazione *testa) {
    for (Prenotazione *temp = testa; temp != NULL; temp = temp->nextPrenotazione) {
        stampaPrenotazione(temp);
        printf("----------\n");
    }
}

void stampaPrenotazione(Prenotazione *prenotazione) {
    printf("id: %d\n", prenotazione->id);
    printf("Id utente: %d\n", prenotazione->utente->id);
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