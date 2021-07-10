void aggiungiOpera(Opera *testa) {

    Opera *curr, *prec;
    prec = NULL;
    curr = testa;

    int ultimoID = 0, i;
    bool testInput = false; //flag per controllare i vari input

    Opera *nuovoNodo = NULL;


    nuovoNodo = (Opera *) malloc(sizeof(Opera));

    FILE *fp;
    fp = fopen("opere.csv", "a+"); //apertura file

    while ('\n' != getchar());

    do {
        printf("Inserisci Nome Opera: ");
        fgets(nuovoNodo->nome, 30, stdin);
        nuovoNodo->nome[strlen(nuovoNodo->nome) - 1] = 0;
        nuovoNodo->nome[0] = toupper(nuovoNodo->nome[0]);
        
        for(i=0; i<strlen(nuovoNodo->nome); i++) {
            if(isalpha(nuovoNodo->nome[i]) == 0) {
                testInput = true; //carattere non alfabetico
            } else {
                testInput = false;
            }
        }
        
        if(testInput) {
            clearConsole();
            titolo();
            printf("\n----------");
            printColor("\nAttenzione!\n", COLOR_RED);
            printf("Nome non valido.\n");
            printf("----------\n\n");
        }
    } while (testInput);
    
    do {
        printf("Inserisci Autore: ");
        fgets(nuovoNodo->autore, 30, stdin);
        nuovoNodo->autore[strlen(nuovoNodo->autore) - 1] = 0;
        nuovoNodo->autore[0] = toupper(nuovoNodo->autore[0]);
        
        for(i=0; i<strlen(nuovoNodo->autore); i++) {
            if(isalpha(nuovoNodo->autore[i]) == 0) {
                testInput = true; //carattere non alfabetico
            } else {
                testInput = false;
            }
        }
        
        if(testInput) {
            clearConsole();
            titolo();
            printf("\n----------");
            printColor("\nAttenzione!\n", COLOR_RED);
            printf("Autore non valido.\n");
            printf("----------\n\n");
        }
    } while (testInput);

    do {
        printf("Inserisci Tipologia dell'Opera (es. dipinto): ");
        fgets(nuovoNodo->tipo, 20, stdin);
        nuovoNodo->tipo[strlen(nuovoNodo->tipo) - 1] = 0;
        nuovoNodo->tipo[0] = toupper(nuovoNodo->tipo[0]);
        
        for(i=0; i<strlen(nuovoNodo->tipo); i++) {
            if(isalpha(nuovoNodo->tipo[i]) == 0) {
                testInput = true; //carattere non alfabetico
            } else {
                testInput = false;
            }
        }
        
        if(testInput) {
            clearConsole();
            titolo();
            printf("\n----------");
            printColor("\nAttenzione!\n", COLOR_RED);
            printf("Tipologia opera non valida.\n");
            printf("----------\n\n");
        }
    } while (testInput);
    
    do {
        printf("Inserisci Genere (es. ritratto): ");
        fgets(nuovoNodo->genere, 20, stdin);
        nuovoNodo->genere[strlen(nuovoNodo->genere) - 1] = 0;
        nuovoNodo->genere[0] = toupper(nuovoNodo->genere[0]);
        
        for(i=0; i<strlen(nuovoNodo->genere); i++) {
            if(isalpha(nuovoNodo->genere[i]) == 0) {
                testInput = true; //carattere non alfabetico
            } else {
                testInput = false;
            }
        }
        
        if(testInput) {
            clearConsole();
            titolo();
            printf("\n----------");
            printColor("\nAttenzione!\n", COLOR_RED);
            printf("Tipologia opera non valida.\n");
            printf("----------\n\n");
        }
    } while (testInput);
    
    do {
        printf("Inserisci Periodo storico (es. Barocco): ");
        fgets(nuovoNodo->periodo, 20, stdin);
        nuovoNodo->periodo[strlen(nuovoNodo->periodo) - 1] = 0;
        nuovoNodo->periodo[0] = toupper(nuovoNodo->periodo[0]);
        
        for(i=0; i<strlen(nuovoNodo->periodo); i++) {
            if(isalpha(nuovoNodo->periodo[i]) == 0) {
                testInput = true; //carattere non alfabetico
            } else {
                testInput = false;
            }
        }
        
        if(testInput) {
            clearConsole();
            titolo();
            printf("\n----------");
            printColor("\nAttenzione!\n", COLOR_RED);
            printf("Periodo storico non valida.\n");
            printf("----------\n\n");
        }
    } while (testInput);

    printf("Inserisci l'anno: ");
    scanf("%d", &nuovoNodo->anno);
    printf("\n");

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

        fprintf(fp, "%d,%s,%s,%s,%s,%s,%d", nuovoNodo->id, nuovoNodo->nome, nuovoNodo->autore,
                nuovoNodo->tipo, nuovoNodo->genere, nuovoNodo->periodo, nuovoNodo->anno);

    } else     //file pieno
    {

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

void modificaOpera(Opera *testa, Opera *opera) {
    
    int scelta, colonna = 0;
    char risposta;

    Opera *temp = NULL;
    temp = opera;

    int anno;

    printColor("\nDati relativi alla opera scelta:\n", COLOR_CYAN);
    
    printColor("----------\n\n", COLOR_CYAN);

    do {
        while ('\n' != getchar());

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
                printf("Inserisci il Nome dell'Opera: ");
                fgets(temp->nome, 30, stdin);
                temp->nome[strlen(temp->nome) - 1] = 0;
                temp->nome[0] = toupper(temp->nome[0]);
                break;
                
            case 2:
                printf("Inserisci l'Autore: ");
                fgets(temp->autore, 30, stdin);
                temp->autore[strlen(temp->autore) - 1] = 0;
                temp->autore[0] = toupper(temp->autore[0]);
                break;

            case 3:
                printf("Inserisci la Tipologia dell'Opera: ");
                fgets(temp->tipo, 20, stdin);
                temp->tipo[strlen(temp->tipo) - 1] = 0;
                temp->tipo[0] = toupper(temp->tipo[0]);
                break;
                
            case 4:
                printf("Inserisci il Genere: ");
                fgets(temp->genere, 20, stdin);
                temp->genere[strlen(temp->genere) - 1] = 0;
                temp->genere[0] = toupper(temp->genere[0]);
                break;
                
            case 5:
                printf("Inserisci il Periodo: ");
                fgets(temp->periodo, 20, stdin);
                temp->periodo[strlen(temp->periodo) - 1] = 0;
                temp->periodo[0] = toupper(temp->periodo[0]);
                break;

            case 6:
                printf("Inserisci l'Anno: ");
                scanf("%d", &anno);
                temp->anno = anno;
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
}

//stampa a video
void stampaOpere(Opera *testa) {
    for (Opera *temp = testa; temp != NULL; temp = temp->nextOpera) {
        printf("Nome Opera: %s\n", temp->nome);
        printf("Di %s\n", temp->autore);
        printf("Genere: %s\t - Periodo: %s", temp->genere, temp->periodo);
        printf("Anno: %d\n", temp->anno);
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
