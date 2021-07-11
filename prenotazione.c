Prenotazione *letturaPrenotazioni(FILE *fp) {
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
                    tempPrenotazione->idUtente = atoi(tok);
                }
                if (colonna == 2) {
                    tempPrenotazione->idMostra = atoi(tok);
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