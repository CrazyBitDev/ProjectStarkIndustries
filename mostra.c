//Gestione Mostre
#define BUFFER_SIZE 1024
#define nomeFile2 "mostre.csv"

//Definizione struct mostre
struct mostre
{
    int id;
    char responsabile[30];
    char citta[20];
    char indirizzo[30];
    char dataInizio[11];
    char dataFine[11];
    int nOpere; // Numero opere
    struct mostre *nextMostra; //puntatore al prossimo nodo
} mostre;

struct mostre *aggiungiMostra(struct mostre *testa)
{

    struct mostre *curr, *prec;
    prec = NULL;
    curr = testa;

    bool flagDate = false;
    char dataIn[11];
    bool dataCorrettaIn = true;
    int giornoIn, meseIn, annoIn;
    int ultimoID = 0;

    char dataFin[11];
    bool dataCorrettaFin = true;
    int giornoFin, meseFin, annoFin;

    struct mostre *nuovoNodo = NULL;


    nuovoNodo = (struct mostre *) malloc(sizeof(struct mostre));

    FILE *fp;
    fp = fopen("mostre.csv", "a+"); //apertura file

    printf("Inserisci il responsabile: ");
    fgets(nuovoNodo->responsabile, 30, stdin);
    nuovoNodo->responsabile[strlen(nuovoNodo->responsabile) - 1] = 0;
    printf("\n");

    printf("Inserisci Città: ");
    fgets(nuovoNodo->citta, 20, stdin);
    nuovoNodo->citta[strlen(nuovoNodo->citta) - 1] = 0;
    printf("\n");

    printf("Inserisci Indirizzo: ");
    fgets(nuovoNodo->indirizzo, 20, stdin);
    nuovoNodo->indirizzo[strlen(nuovoNodo->indirizzo) - 1] = 0;
    printf("\n");

    do
    {
        printf("Inserisci data d'inizio mostra\n");

        do
        {
            if(!dataCorrettaIn)
            {
                printColor("\nAttenzione!\n", COLOR_RED);
                printf("La data inserita non è corretta.\nSi prega di inserirla nuovamente\n\n");
            }

            do
            {
                printf("Giorno: ");
                scanf("%d", &giornoIn);
            }
            while (giornoIn < 0 || giornoIn > 31);

            do
            {
                printf("Mese: ");
                scanf("%d", &meseIn);
            }
            while (meseIn < 1 || meseIn > 12);

            printf("Anno: ");
            scanf("%d", &annoIn);

            dataCorrettaIn = verificaData(giornoIn, meseIn, annoIn);

        }
        while (!dataCorrettaIn);

        while ('\n' != getchar());

        snprintf(dataIn, 11, "%d/%d/%d", giornoIn, meseIn, annoIn);

        printf("\n");

        printf("Inserisci data di fine mostra\n");

        do
        {
            if(!dataCorrettaFin)
            {
                printColor("\nAttenzione!\n", COLOR_RED);
                printf("La data inserita non è corretta.\nSi prega di inserirla nuovamente\n\n");
            }

            do
            {
                printf("Giorno: ");
                scanf("%d", &giornoFin);
            }
            while (giornoFin< 0 || giornoFin > 31);

            do
            {
                printf("Mese: ");
                scanf("%d", &meseFin);
            }
            while (meseFin < 1 || meseFin > 12);

            printf("Anno: ");
            scanf("%d", &annoFin);

            dataCorrettaFin = verificaData(giornoFin, meseFin, annoFin);

        }
        while (!dataCorrettaFin);

        while ('\n' != getchar());

        snprintf(dataFin, 11, "%d/%d/%d", giornoFin, meseFin, annoFin);


        printf("\n");
        if((giornoIn == giornoFin) && (meseIn == meseFin) && (annoIn == annoFin))
        {
            //La mostra dura solo un giorno di conseguenza le date coincidono
            flagDate = true;
        }
        else if(annoIn < annoFin || (annoIn == annoFin && meseIn < meseFin) || (annoIn == annoFin && meseIn == meseFin && giornoIn < giornoFin))
        {
            //La data d'inizio precede quella di fine
            flagDate = true;
        }
        else
        {
            //La data di fine precede quella d'inizio
            flagDate = false;
            printColor("Attenzione!\n", COLOR_RED);
            printf("La data di fine mostra deve susseguire la data d'inizio.\n");
            printf("Si prega di inserire nuovamente le date.\n\n");

        }
    }
    while(!flagDate);
    strcpy(nuovoNodo->dataInizio, dataIn);
    strcpy(nuovoNodo->dataFine, dataFin);

    printf("Inserisci Il Numero delle Opere: ");
    scanf("%d",&nuovoNodo->nOpere);
    printf("\n");


    //verifico se nel file ci sono già utenti registrati o meno

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);

    ultimoID = letturaUltimoID(nomeFile) + 1;

    //ricerca della posizione di inserimento
    while(curr != NULL && ultimoID > curr->id)
    {
        prec = curr;
        curr = curr->nextMostra;
    }


    if (size == 0)   //file vuoto
    {

        nuovoNodo->id = 0;

        fprintf(fp, "%d,%s,%s,%s,%s,%d", nuovoNodo->id,nuovoNodo->citta, nuovoNodo->indirizzo, nuovoNodo->dataInizio, nuovoNodo->dataFine, nuovoNodo->nOpere);

    }
    else     //file pieno
    {

        ultimoID = letturaUltimoID(nomeFile);
        nuovoNodo->id = ultimoID + 1;

        fprintf(fp, "\n%d,%s,%s,%s,%s,%d", nuovoNodo->id,nuovoNodo->citta, nuovoNodo->indirizzo, nuovoNodo->dataInizio, nuovoNodo->dataFine, nuovoNodo->nOpere);

    }

    fclose(fp);

    //aggiornamento dei collegamenti
    if(prec == NULL)
    {
        nuovoNodo->nextMostra = testa;
        testa = nuovoNodo;
        return testa;
    }
    else
    {
        prec->nextMostra = nuovoNodo;
        nuovoNodo->nextMostra = curr;
        return testa;
    }

}

struct mostre *modificaMostra(struct mostre *testa, int sceltaMostra)
{
    int scelta, colonna = 0;
    char risposta;
    bool flag = false;
    bool flagDate = false;

    char dataIn[11];
    bool dataCorrettaIn = true;
    int giornoIn = 0, meseIn = 0, annoIn = 0;

    char dataFin[11];
    bool dataCorrettaFin = true;
    int giornoFin = 0, meseFin = 0, annoFin = 0;

    struct mostre *temp = NULL;
    struct mostre *tempM = NULL;

    for (temp = testa; temp != NULL; temp = temp->nextMostra)
    {

        if (temp->id == sceltaMostra)
        {

            tempM = temp;
            flag = true;
            break;

        }
    }

    if(!flag)
    {
        printColor("Attenzione!", COLOR_RED);
        printf("La mostra scelta non esiste\n");
    }
    else
    {
        do
        {
            while ('\n' != getchar());

            //elenco campi modificabili
            printf("1: Responsabile\n");
            printf("2: Citta'\n");
            printf("3: Indirizzo\n");
            printf("4: Data Inizio\n");
            printf("5: Data Fine\n");
            printf("6: Numero Opere\n");
            printf("----------\n");
            printf("-> ");
            scanf("%d", &scelta);
            printf("\n");
            while ('\n' != getchar());

            switch (scelta)
            {
            case 1:
                printf("Inserisci il responsabile: ");
                fgets(tempM->responsabile, 30, stdin);
                tempM->responsabile[strlen(tempM->responsabile) - 1] = 0;
                tempM->responsabile[0] = toupper(tempM->responsabile[0]);
                break;
            case 2:
                printf("Inserisci la città: ");
                fgets(tempM->citta, 20, stdin);
                tempM->citta[strlen(tempM->citta) - 1] = 0;
                tempM->citta[0] = toupper(tempM->citta[0]);
                break;

            case 3:
                printf("Inserisci l'indirizzo: ");
                fgets(tempM->indirizzo, 20, stdin);
                tempM->indirizzo[strlen(tempM->indirizzo) - 1] = 0;
                tempM->indirizzo[0] = toupper(tempM->indirizzo[0]);
                break;

            case 4:
                printf("Inserisci data d'inizio mostra\n");
                do
                {
                    do
                    {
                        if(!dataCorrettaIn)
                        {
                            printColor("\nAttenzione!\n", COLOR_RED);
                            printf("La data inserita non è corretta.\nSi prega di inserirla nuovamente\n\n");
                        }

                        do
                        {
                            printf("Giorno: ");
                            scanf("%d", &giornoIn);
                        }
                        while (giornoIn < 0 || giornoIn > 31);

                        do
                        {
                            printf("Mese: ");
                            scanf("%d", &meseIn);
                        }
                        while (meseIn < 1 || meseIn > 12);

                        printf("Anno: ");
                        scanf("%d", &annoIn);

                        dataCorrettaIn = verificaData(giornoIn, meseIn, annoIn);

                    }
                    while (!dataCorrettaIn);

                    snprintf(dataIn, 11, "%d/%d/%d", giornoIn, meseIn, annoIn);

                    //while ('\n' != getchar());

                    char *tok;
                    tok = strtok(tempM->dataFine, "/");

                    while (tok)
                    {
                        if (colonna == 0)
                        {
                            giornoFin = atoi(tok);
                        }
                        if (colonna == 1)
                        {
                            meseFin = atoi(tok);
                        }
                        if (colonna == 2)
                        {
                            annoFin = atoi(tok);
                        }
                    }

                    if((giornoIn == giornoFin) && (meseIn == meseFin) && (annoIn == annoFin))
                    {
                        //La mostra dura solo un giorno di conseguenza le date coincidono
                        flagDate = true;
                    }
                    else if(annoIn < annoFin || (annoIn == annoFin && meseIn < meseFin) || (annoIn == annoFin && meseIn == meseFin && giornoIn < giornoFin))
                    {
                        //La data d'inizio precede quella di fine
                        flagDate = true;
                    }
                    else
                    {
                        //La data di fine precede quella d'inizio
                        flagDate = false;
                        printColor("Attenzione!\n", COLOR_RED);
                        printf("La data di fine mostra deve susseguire la data d'inizio.\n");
                        printf("Si prega di inserire nuovamente le date.\n\n");

                    }

                    printf("\n");
                    if((giornoIn == giornoFin) && (meseIn == meseFin) && (annoIn == annoFin))
                    {
                        //La mostra dura solo un giorno di conseguenza le date coincidono
                        flagDate = true;
                    }
                    else if(annoIn < annoFin || (annoIn == annoFin && meseIn < meseFin) || (annoIn == annoFin && meseIn == meseFin && giornoIn < giornoFin))
                    {
                        //La data d'inizio precede quella di fine
                        flagDate = true;
                    }
                    else
                    {
                        //La data di fine precede quella d'inizio
                        flagDate = false;
                        printColor("Attenzione!\n", COLOR_RED);
                        printf("La data di fine mostra deve susseguire la data d'inizio.\n");
                        printf("Si prega di inserire nuovamente le date.\n\n");

                    }
                }
                while(!flagDate);
                strcpy(tempM->dataInizio, dataIn);

                break;

            case 5:
                printf("Inserisci data di fine mostra\n");
                do
                {
                    do
                    {
                        if(!dataCorrettaFin)
                        {
                            printColor("\nAttenzione!\n", COLOR_RED);
                            printf("La data inserita non è corretta.\nSi prega di inserirla nuovamente\n\n");
                        }

                        do
                        {
                            printf("Giorno: ");
                            scanf("%d", &giornoFin);
                        }
                        while (giornoFin< 0 || giornoFin > 31);

                        do
                        {
                            printf("Mese: ");
                            scanf("%d", &meseFin);
                        }
                        while (meseFin < 1 || meseFin > 12);

                        printf("Anno: ");
                        scanf("%d", &annoFin);

                        dataCorrettaFin = verificaData(giornoFin, meseFin, annoFin);

                    }
                    while (!dataCorrettaFin);

                    snprintf(dataFin, 11, "%d/%d/%d", giornoFin, meseFin, annoFin);

                    //while ('\n' != getchar());

                    char *tok;
                    tok = strtok(tempM->dataInizio, "/");

                    while (tok)
                    {
                        if (colonna == 0)
                        {
                            giornoIn = atoi(tok);
                        }
                        if (colonna == 1)
                        {
                            meseIn = atoi(tok);
                        }
                        if (colonna == 2)
                        {
                            annoIn = atoi(tok);
                        }
                    }

                    if((giornoIn == giornoFin) && (meseIn == meseFin) && (annoIn == annoFin))
                    {
                        //La mostra dura solo un giorno di conseguenza le date coincidono
                        flagDate = true;
                    }
                    else if(annoIn < annoFin || (annoIn == annoFin && meseIn < meseFin) || (annoIn == annoFin && meseIn == meseFin && giornoIn < giornoFin))
                    {
                        //La data d'inizio precede quella di fine
                        flagDate = true;
                    }
                    else
                    {
                        //La data di fine precede quella d'inizio
                        flagDate = false;
                        printColor("Attenzione!\n", COLOR_RED);
                        printf("La data di fine mostra deve susseguire la data d'inizio.\n");
                        printf("Si prega di inserire nuovamente le date.\n\n");

                    }

                    printf("\n");

                    if((giornoIn == giornoFin) && (meseIn == meseFin) && (annoIn == annoFin))
                    {
                        //La mostra dura solo un giorno di conseguenza le date coincidono
                        flagDate = true;
                    }
                    else if(annoIn < annoFin || (annoIn == annoFin && meseIn < meseFin) || (annoIn == annoFin && meseIn == meseFin && giornoIn < giornoFin))
                    {
                        //La data d'inizio precede quella di fine
                        flagDate = true;
                    }
                    else
                    {
                        //La data di fine precede quella d'inizio
                        flagDate = false;
                        printColor("Attenzione!\n", COLOR_RED);
                        printf("La data di fine mostra deve susseguire la data d'inizio.\n");
                        printf("Si prega di inserire nuovamente le date.\n\n");

                    }
                }
                while(!flagDate);
                strcpy(tempM->dataFine, dataFin);

                break;

            case 6:
                printf("Inserisci il numero delle opere: ");
                scanf("%d", &tempM->nOpere);
                break;

            default:
                break;
            }


            printf("Vuoi modificare un altro campo? (s/n): ");
            scanf("%c", &risposta);

            //rendo la risposta in maiuscolo
            risposta = toupper(risposta);

            if (risposta == 'N')
            {
                scriviMostre(testa);
            }
        }
        while (risposta == 'S');
    }


    return testa;
}

void stampaMostre(struct mostre *testa)
{
    struct mostre *temp = NULL;
    temp = testa;

    for (temp = testa; temp != NULL; temp = temp->nextMostra)
    {
        printf("Mostra numero: %d \n", temp->id);
        printf("Responsabile: %s \n", temp->responsabile);
        printf("Luogo: %s - %s\n", temp->citta, temp->indirizzo);
        printf("Durata: dal %s al %s\n",  temp->dataInizio, temp->dataFine);
        printf("------\n");
    }
}

void scriviMostre(struct mostre *testa)
{
    struct mostre *temp =  NULL;

    FILE *fp;
    fp = fopen("mostre.csv", "w"); //apertura file

    for (temp = testa; temp != NULL; temp = temp->nextMostra)
    {
        long size = ftell(fp);

        if (size == 0)   //file vuoto.
        {
            fprintf(fp, "%d,%s,%s,%s,%s,%s,%d", temp->id, temp->responsabile, temp->citta, temp->indirizzo, temp->dataInizio, temp->dataFine, temp->nOpere);
        }
        else     //file pieno
        {
            fprintf(fp, "\n%d,%s,%s,%s,%s,%s,%d", temp->id, temp->responsabile, temp->citta, temp->indirizzo, temp->dataInizio, temp->dataFine, temp->nOpere);
        }
    }
    fclose(fp);
}




struct mostre *eliminaMostra(struct mostre *testa, int sceltaMostra)
{
    char risposta;
    struct mostre *curr, *prec;
    struct mostre *temp = NULL;
    struct mostre *tempM;
    bool flag = false;

    tempM = testa;
    prec = NULL;
    curr = testa;

    for (temp = testa; temp != NULL; temp = temp->nextMostra)
    {

        if (temp->id == sceltaMostra)
        {
            tempM = temp;
            flag = true;
            break;
        }
    }

    if(!flag)
    {
        printColor("Attenzione!", COLOR_RED);
        printf("La mostra scelta non esiste\n");
    }
    else
    {
        do
        {
            while ('\n' != getchar());
            printColor("ATTENZIONE!\n", COLOR_RED);
            printf("Sei sicuro/a di voler eliminare la mostra?\n");
            printf("Risposta (s/n): ");
            scanf("%c",&risposta);
            printf("\n");

            //rendo la risposta tutta maiuscola per evitare errori
            risposta = toupper(risposta);
        }
        while(risposta != 'S' && risposta != 'N');

        if (risposta == 'S')
        {
            while (curr != NULL && temp->id != curr->id)
            {
                prec = curr;
                curr = curr->nextMostra;

                if(tempM->id == curr->id)
                {
                    if(prec == NULL)   //elemento trovato in testa
                    {
                        testa = curr->nextMostra;
                    }
                    else     //elemento al centro della lista
                    {
                        prec->nextMostra = curr->nextMostra;
                    }
                    free(curr);
                }
                scriviMostre(testa);
            }
            return testa;
        }
    }
}
