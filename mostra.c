//Gestione Mostre
#define BUFFER_SIZE 1024
#define nomeFile "mostre.csv"

//Definizione struct mostre
struct mostre
{
    int id;
    char citta[20];
    char indirizzo[30];
    char dataInizio[11];
    char dataFine[11];
    int nOpere; // Numero opere
    struct mostre *nextMostra; //puntatore al prossimo nodo
} mostre;

struct mostre *aggiungiMostra(struct mostre *testa, struct utente *utenteLogin)
{
    struct utente *temp = NULL;
    temp = utenteLogin;
    if (temp->permessi == 2)
    {
        struct mostre *nuovoNodo = NULL;
        nuovoNodo = (struct mostre *) malloc(sizeof(struct mostre));

        FILE *fp;
        fp = fopen("mostre.csv", "a+"); //apertura file

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
            char dataIn[11];
            bool dataCorrettaIn = true;
            int giornoIn, meseIn, annoIn;

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

            snprintf(dataIn, 11, "%d/%d/%d", giornoIn, meseIN, annoIn);


            printf("\n");

            char dataFin[11];
            bool dataCorrettaFin = true;
            int giornoFin, meseFin, annoFin;

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
            bool flagDate = false;
            if((giornoIn == giornoFin) && (meseIn == meseFin) && (annoIn == annoFin))
            {
                //La mostra dura solo un giorno di conseguenza le date coincidono
                flagDate = true;
            }
            else if(annoIn < annoFin || (annoIn == annoFin && meseIn < meseFin) || (annoIn == annoFin && meseIn = meseFin && giornoIn < giornoFin))
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
                printf("Si prega di inserire nuovamente le date.\n");

            }
        }
        while(!flagDate);
        strcpy(nuovoNodo->dataInizio, dataIn);
        strcpy(nuovoNodo->dataFine, dataFin);

        printf("Inserisci Il Numero delle Opere: ");
        fgets(nuovoNodo->nOpere, stdin);
        nuovoNodo->nOpere[strlen(nuovoNodo->nOpere) - 1] = 0;
        printf("\n");


        //verifico se nel file ci sono già utenti registrati o meno
        int ultimoID;
        fseek(fp, 0, SEEK_END);
        long size = ftell(fp);

        if (size == 0)   //file vuoto.
        {

            nuovoNodo->id = 0;

            fprintf(fp, "%d,%s,%s,%s,%s,%d", nuovoNodo->id,nuovoNodo->citta, nuovoNodo->indirizzo, nuovoNodo->dataInizio, nuovoNodo->dataFine, nuovoNodo->nOpere);

        }
        else     //file pieno
        {

            ultimoID = letturaUltimoID(nomeFile);
            nuovoNodo->id = ultimoID + 1;

            fprintf(fp, "%d,%s,%s,%s,%s,%d", nuovoNodo->id,nuovoNodo->citta, nuovoNodo->indirizzo, nuovoNodo->dataInizio, nuovoNodo->dataFine, nuovoNodo->nOpere);

        }

        nuovoNodo->nextMostra = testa;

        testa = nuovoNodo;

        fclose(fp);

        return nuovoNodo;
    } else {
        printColor("Attenzione!\n", COLOR_RED);
        printf("%s non hai i permessi per poter accedere a questa funzione.\n", temp->nome);
    }

}

struct mostre *modificaMostra(struct mostre *testa, struct utente *utenteLogin)
{
    struct utente *temp = NULL;
    temp = utenteLogin;
    if (temp->permessi == 2)
    {
        int scelta;
        char risposta[3], psw[20];

        FILE *fp;
        fp = fopen("mostre.csv", "a+"); //apertura file

        struct mostre *nuovoNodo = NULL;
        nuovoNodo = (struct mostre *) malloc(sizeof(struct mostre));

        do
        {
            while ('\n' != getchar());

            //elenco campi modificabili
            printf("1: Città");
            printf("2: Indirizzo");
            printf("3: Data Inizio");
            printf("4: Data Fine");
            printf("5: Numero Opere");
            scanf("%d", &scelta);
            printf("\n");
            while ('\n' != getchar());

            switch (scelta)
            {
            case 1:
                printf("Inserisci la città: ");
                fgets(nuovoNodo->citta, 20, stdin);
                nuovoNodo->citta[strlen(nuovoNodo->citta) - 1] = 0;
                nuovoNodo->citta[0] = toupper(nuovoNodo->citta[0]);
                break;

            case 2:
                printf("Inserisci l'indirizzo: ");
                fgets(nuovoNodo->indirizzo, 20, stdin);
                nuovoNodo->indirizzo[strlen(nuovoNodo->indirizzo) - 1] = 0;
                nuovoNodo->indirizzo[0] = toupper(nuovoNodo->indirizzo[0]);
                break;

            case 3:
                char dataIn[11];
                bool dataCorrettaIn = true;
                int giornoIn, meseIn, annoIn;

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

                snprintf(dataIn, 11, "%d/%d/%d", giornoIn, meseIN, annoIn);
                break;

            case 4:
                char dataFin[11];
                bool dataCorrettaFin = true;
                int giornoFin, meseFin, annoFin;

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
                break;

            case 5:
                printf("Inserisci il numero delle opere: ");
                fgets(nuovoNodo->nOpere, stdin);
                nuovoNodo->nOpere[strlen(nuovoNodo->nOpere) - 1] = 0;
                nuovoNodo->nOpere[0] = toupper(nuovoNodo->nOpere[0]);
                break;

            default:
                break;
            }

            printf("Vuoi modificare un altro campo? (si/no): ");
            fgets(risposta, 3, stdin);

            //rendo la risposta in maiuscolo
            for (int i = 0; i < strlen(risposta); i++)
            {
                risposta[i] = toupper(risposta[i]);
            }

            if (strcmp(risposta, "NO") == 0)
            {
                fprintf(fp, "%d,%s,%s,%s,%s,%d\n", nuovoNodo->id, nuovoNodo->citta, nuovoNodo->indirizzo,
                        nuovoNodo->dataInizio, nuovoNodo->dataFine, nuovoNodo->nOpere);
            }
        }
        while (strcmp(risposta, "SI") == 0);

        return testa;
    }
}

struct mostre *eliminaMostra(struct mostre *testa, struct utente *utenteLogin)
{
    struct utente *temp = NULL;
    temp = utenteLogin;
    if (temp->permessi == 2)
    {
        char risposta[3];
        struct utente *curr, *prec;
        struct utente *temp = NULL;

        temp = utenteLogin;
        prec = NULL;
        curr = testa;

        do
        {
            while ('\n' != getchar());
            printColor("ATTENZIONE!\n", COLOR_RED);
            printf("Sei sicuro/a di voler eliminare la mostra?\n");
            printf("Per poter riaccedere dovrai creare una nuova mostra\n");
            printf("Risposta (si/no): ");
            fgets(risposta, 3, stdin);
            printf("\n");

            //rendo la risposta tutta maiuscola per evitare errori
            for (int i = 0; i < strlen(risposta); i++)
            {
                risposta[i] = toupper(risposta[i]);
            }

        }
        while(strcmp(risposta, "SI") != 0 && strcmp(risposta, "NO") != 0);

        if (strcmp(risposta, "SI") == 0)
        {

            while (curr != NULL && temp->id != curr->id)
            {
                prec = curr;
                curr = curr->nextMostra;

                if(temp->id == curr->id)
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
};

void scriviMostre(struct mostre *testa)
{
    struct mostre *temp;

    FILE *fp;
    fp = fopen("mostreTemp.csv", "w"); //apertura file

    ordinamento(testa);

    for (temp = testa; temp != NULL; temp = temp->nextMostra)
    {
        long size = ftell(fp);

        if (size == 0)   //file vuoto.
        {
            fprintf(fp, "%d,%s,%s,%s,%s,%s", temp->id, temp->citta, temp->indirizzo, temp->dataInizio, temp->dataFine, temp->nOpere);
        }
        else     //file pieno
        {
            fprintf(fp, "\n%d,%s,%s,%s,%s,%s", temp->id, temp->citta, temp->indirizzo, temp->dataInizio, temp->dataFine, temp->nOpere);
        }
    }

    remove("mostre.csv");
    rename("mostreTemp.csv", "mostre.csv");
    fclose(fp);
}

struct mostre *ordinamento(struct mostre *testa)
{
    Mostre *p, *ultimo;
    int flag, tempId, tempPermessi;
    char tempCitta[20], tempIndirizzo[20], tempDataInizio[20], tempDataFine[60], tempnOpere[20];

    ultimo = NULL;

    flag = 1;
    while (flag == 1)
    {
        p = testa;
        flag = 0;
        while (p->nextMostra != ultimo)
        {
            if (p->id > (p->nextMostra)->id)
            {

                tempId = p->id;
                p->id = (p->nextMostra)->id;
                (p->nextMostra)->id = tempId;

                strcpy(tempCitta, p->citta);
                strcpy(p->citta, (p->nextMostra)->citta);
                strcpy((p->nextMostra)->citta, tempCitta);

                strcpy(tempIndirizzo, p->indirizzo);
                strcpy(p->indirizzo, (p->nextMostra)->indirizzo);
                strcpy((p->nextMostra)->indirizzo, tempIndirizzo);

                strcpy(tempDataInizio, p->dataInizio);
                strcpy(p->dataInizio, (p->nextMostra)->dataInizio);
                strcpy((p->nextMostra)->dataInizio, tempDataInizio);

                strcpy(tempDataFine, p->dataFine);
                strcpy(p->dataFine, (p->nextMostra)->dataFine);
                strcpy((p->nextMostra)->dataFine, tempDataFine);

                strcpy(tempnOpere, p->nOpere);
                strcpy(p->nOpere, (p->nextMostra)->nOpere);
                strcpy((p->nextMostra)->nOpere, tempnOpere);

                flag = 1;
            }
            p = p->nextMostra;
        }
        ultimo = p;
    }

    return testa;
};
