//Gestione Mostre
#define BUFFER_SIZE 1024

//Definizione struct mostre
struct mostre
{
    int id;
    char citta[20];
    char indirizzo[30];
    char dataInizio[10];
    char dataFine[10];
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

        printf("Inserisci Data Inizio (non ti dimenticare di separarli con /): \n");
        fgets(nuovoNodo->dataInizio, 60, stdin);
        nuovoNodo->dataInizio[strlen(nuovoNodo->dataInizio) - 1] = 0;

        //verifico che sia stata inserita la /
        char *ptr;
        char *a = "/";
        ptr = strstr(nuovoNodo->dataInizio, a);

        while (ptr == NULL)
        {
            printColor("Attenzione! La data inserita non e' corretta\n", COLOR_RED);

            printf("Inserisci Data Inizio (non ti dimenticare di separarli con /): \n");
            fgets(nuovoNodo->dataInizio, 60, stdin);
            nuovoNodo->dataInizio[strlen(nuovoNodo->dataInizio) - 1] = 0;
            ptr = strstr(nuovoNodo->dataInizio, a);
        }
        printf("\n");

        printf("Inserisci Data Fine (non ti dimenticare di separarli con /): \n");
        fgets(nuovoNodo->dataFine, 60, stdin);
        nuovoNodo->dataFine[strlen(nuovoNodo->dataFine) - 1] = 0;

        //verifico che sia stata inserita la /
        char *ptr2;
        char *a2 = "/";
        ptr = strstr(nuovoNodo->dataInizio, a2);

        while (ptr2 == NULL)
        {

            printColor("Attenzione! La data inserita non e' corretta\n", COLOR_RED);

            printf("Inserisci Data Fine (non ti dimenticare di separarli con /): \n");
            fgets(nuovoNodo->dataFine, 60, stdin);
            nuovoNodo->dataFine[strlen(nuovoNodo->dataFine) - 1] = 0;
            ptr2 = strstr(nuovoNodo->dataFine, a2);
        }
        printf("\n");

        printf("Inserisci Il Numero delle Opere: ");
        fgets(nuovoNodo->nOpere, stdin);
        nuovoNodo->nOpere[strlen(nuovoNodo->nOpere) - 1] = 0;
        printf("\n");
        fprintf(fp, "%s,%s,%s,%s,%d\n", nuovoNodo->citta, nuovoNodo->indirizzo, nuovoNodo->dataInizio,
                nuovoNodo->dataFine, nuovoNodo->nOpere);

        nuovoNodo->nextMostra = testa;

        testa = nuovoNodo;

        fclose(fp);

        return nuovoNodo;
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
                printf("Inserisci la data d'inizio(non ti dimenticare di separarli con /): ");
                fgets(nuovoNodo->dataInizio, 20, stdin);
                nuovoNodo->dataInizio[strlen(nuovoNodo->dataInizio) - 1] = 0;
                nuovoNodo->dataInizio[0] = toupper(nuovoNodo->dataInizio[0]);

                //verifico che sia stata inserita la /
                char *ptr;
                char *a = "/";
                ptr = strstr(nuovoNodo->dataInizio, a);

                while (ptr == NULL)
                {
                    printColor("Attenzione! L'email inserita non e' corretta\n", COLOR_RED);

                    printf("Inserisci Data Inizio (non ti dimenticare di separarli con /): \n");
                    fgets(nuovoNodo->dataInizio, 20, stdin);
                    nuovoNodo->dataInizio[strlen(nuovoNodo->dataInizio) - 1] = 0;
                    ptr = strstr(nuovoNodo->dataInizio, a);
                }
                printf("\n");
                break;

            case 4:
                printf("Inserisci la data di fine(non ti dimenticare di separarli con /): ");
                fgets(nuovoNodo->dataFine, 20, stdin);
                nuovoNodo->dataFine[strlen(nuovoNodo->dataFine) - 1] = 0;
                nuovoNodo->dataFine[0] = toupper(nuovoNodo->dataFine[0]);

                //verifico che sia stata inserita la /
                char *ptr2;
                char *a = "/";
                ptr = strstr(nuovoNodo->dataFine, a);

                while (ptr2 == NULL)
                {

                    printColor("Attenzione! L'email inserita non e' corretta\n", COLOR_RED);

                    printf("Inserisci Data Fine (non ti dimenticare di separarli con /): \n");
                    fgets(nuovoNodo->dataFine, 20, stdin);
                    nuovoNodo->dataFine[strlen(nuovoNodo->dataFine) - 1] = 0;
                    ptr2 = strstr(nuovoNodo->dataFine, a);
                }
                printf("\n");
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

void scriviMostre(struct mostre *testa) {
    struct mostre *temp;

    FILE *fp;
    fp = fopen("mostreTemp.csv", "w"); //apertura file

    ordinamento(testa);

    for (temp = testa; temp != NULL; temp = temp->nextMostra) {
        long size = ftell(fp);

        if (size == 0) { //file vuoto.
            fprintf(fp, "%d,%s,%s,%s,%s,%s", temp->id, temp->citta, temp->indirizzo, temp->dataInizio, temp->dataFine, temp->nOpere);
        } else { //file pieno
            fprintf(fp, "\n%d,%s,%s,%s,%s,%s", temp->id, temp->citta, temp->indirizzo, temp->dataInizio, temp->dataFine, temp->nOpere);
        }
    }

    remove("mostre.csv");
    rename("mostreTemp.csv", "mostre.csv");
    fclose(fp);
}

struct mostre *ordinamento(struct mostre *testa){
    Mostre *p, *ultimo;
    int flag, tempId, tempPermessi;
    char tempCitta[20], tempIndirizzo[20], tempDataInizio[20], tempDataFine[60], tempnOpere[20];

    ultimo = NULL;

    flag = 1;
    while (flag == 1) {
        p = testa;
        flag = 0;
        while (p->nextMostra != ultimo) {
            if (p->id > (p->nextMostra)->id) {

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
