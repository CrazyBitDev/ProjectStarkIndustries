Opera *aggiungiOpera(Opera *testa) {

    Opera *curr, *prec;
    prec = NULL;
    curr = testa;

    int ultimoID = 0;

    Opera *nuovoNodo = NULL;


    nuovoNodo = (Opera *) malloc(sizeof(Opera));

    FILE *fp;
    fp = fopen("opere.csv", "a+"); //apertura file


    //verifico se nel file ci sono già delle opere registrate o meno
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);

    ultimoID = letturaUltimoID("opere.csv") + 1;

    //ricerca della posizione di inserimento
    while (curr != NULL && ultimoID > curr->id) {
        prec = curr;
        curr = curr->nextOpera;
    }

    if (size == 0)   //file vuoto
    {

        nuovoNodo->id = 0;

        /*fprintf(fp, "%d,%s,%s,%s,%s,%s,%s,%d", nuovoNodo->id, nuovoNodo->responsabile, nuovoNodo->luogo,
                nuovoNodo->citta, nuovoNodo->indirizzo, nuovoNodo->dataInizio, nuovoNodo->dataFine, nuovoNodo->nOpere);*/

    } else     //file pieno
    {

        nuovoNodo->id = ultimoID;

        /*fprintf(fp, "\n%d,%s,%s,%s,%s,%s,%s,%d", nuovoNodo->id, nuovoNodo->responsabile, nuovoNodo->luogo,
                nuovoNodo->citta, nuovoNodo->indirizzo, nuovoNodo->dataInizio, nuovoNodo->dataFine, nuovoNodo->nOpere);*/

    }

    fclose(fp);

    //aggiornamento dei collegamenti
    if (prec == NULL) {
        nuovoNodo->nextOpera = testa;
        testa = nuovoNodo;
        return testa;
    } else {
        prec->nextOpera = nuovoNodo;
        nuovoNodo->nextOpera = curr;
        return testa;
    }

}

Opera *modificaOpera(Opera *testa, Opera *opera) {
    
    int scelta, colonna = 0;
    char risposta;

    Opera *temp = NULL;

    temp = opera;

    printColor("\nDati relativi alla opera scelta:\n", COLOR_CYAN);
    
    printColor("----------\n\n", COLOR_CYAN);

    do {
        while ('\n' != getchar());

        //elenco campi modificabili
        printf("Scegliere il campo da modificare\n");
        printf("----------\n");
        printf("0: Annulla\n");
        printf("----------\n");
        printf("-> ");
        scanf("%d", &scelta);
        printf("\n");
        while ('\n' != getchar());

        switch (scelta) {
            case 0:
                break;

            default:
                break;
        }


        while ('\n' != getchar());
        printf("Vuoi modificare un altro campo? (s/n): ");
        risposta = toupper(getchar());

        if (risposta == 'N') {
            scriviOpere(testa);
        }
    } while (risposta == 'S');

    return testa;
}

//stampa a video
void stampaOpere(Opera *testa) {
    Opera *temp = NULL;

    for (temp = testa; temp != NULL; temp = temp->nextOpera) {
        printf("----------\n");
    }
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
            /*fprintf(fp, "%d,%s,%s,%s,%s,%s,%s,%d", temp->id, temp->responsabile, temp->luogo, temp->citta,
                    temp->indirizzo, temp->dataInizio, temp->dataFine, temp->nOpere);*/
        } else     //file pieno
        {
            /*fprintf(fp, "\n%d,%s,%s,%s,%s,%s,%s,%d", temp->id, temp->responsabile, temp->luogo, temp->citta,
                    temp->indirizzo, temp->dataInizio, temp->dataFine, temp->nOpere);*/
        }
    }
    fclose(fp);
}


Opera *eliminaOpera(Opera *testa, Opera *opera) {
    char risposta;
    Opera *curr, *prec;
    Opera *temp;

    temp = opera;
    prec = NULL;
    curr = testa;

    do {
        while ('\n' != getchar());
        printColor("ATTENZIONE!\n", COLOR_RED);
        printf("Sei sicuro/a di voler eliminare l'opera?\n");
        printf("Risposta (s/n): ");
        scanf("%c", &risposta);
        printf("\n");

        //rendo la risposta tutta maiuscola per evitare errori
        risposta = toupper(risposta);
    } while (risposta != 'S' && risposta != 'N');

    if (risposta == 'S') {
        while (curr != NULL && temp->id != curr->id) {
            prec = curr;
            curr = curr->nextOpera;

            if (temp->id == curr->id) {
                if (prec == NULL)   //elemento trovato in testa
                {
                    testa = curr->nextOpera;
                } else     //elemento al centro della lista
                {
                    prec->nextOpera = curr->nextOpera;
                }
                free(curr);
            }
            scriviOpere(testa);
        }
    }
    return testa;
}


Opera *ricercaOpera(Opera *testa, int id) {
    bool flag = false;
    Opera *nuovoNodo = NULL;
    Opera *temp;

    for (temp = testa; temp != NULL; temp = temp->nextOpera) {

        if (temp->id == id) {

            nuovoNodo = temp;
            flag = true;
            break;

        }
    }

    if (!flag) {
        printColor("---Mostra non trovata!---\n", COLOR_RED);
    }

    if (flag)
        return nuovoNodo;
    else
        return NULL;
}
