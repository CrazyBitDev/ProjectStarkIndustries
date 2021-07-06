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
    nuovoNodo->responsabile[0] = toupper(nuovoNodo->responsabile[0]);
    printf("\n");
    
    printf("Inserisci Città: ");
    fgets(nuovoNodo->citta, 20, stdin);
    nuovoNodo->citta[strlen(nuovoNodo->citta) - 1] = 0;
    nuovoNodo->responsabile[0] = toupper(nuovoNodo->responsabile[0]);
    printf("\n");
    
    printf("Inserisci Indirizzo: ");
    fgets(nuovoNodo->indirizzo, 20, stdin);
    nuovoNodo->indirizzo[strlen(nuovoNodo->indirizzo) - 1] = 0;
    nuovoNodo->indirizzo[0] = toupper(nuovoNodo->indirizzo[0]);
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
    
    
    //verifico se nel file ci sono già delle mmostre registrate o meno
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    
    ultimoID = letturaUltimoID(nomeFile2) + 1;
    
    //ricerca della posizione di inserimento
    while(curr != NULL && ultimoID > curr->id)
    {
        prec = curr;
        curr = curr->nextMostra;
    }
    
    
    if (size == 0)   //file vuoto
    {
        
        nuovoNodo->id = 0;
        
        fprintf(fp, "%d,%s,%s,%s,%s,%s,%d", nuovoNodo->id, nuovoNodo->responsabile, nuovoNodo->citta, nuovoNodo->indirizzo, nuovoNodo->dataInizio, nuovoNodo->dataFine, nuovoNodo->nOpere);
        
    }
    else     //file pieno
    {
        
        nuovoNodo->id = ultimoID;
        
        fprintf(fp, "\n%d,%s,%s,%s,%s,%s,%d", nuovoNodo->id, nuovoNodo->responsabile, nuovoNodo->citta, nuovoNodo->indirizzo, nuovoNodo->dataInizio, nuovoNodo->dataFine, nuovoNodo->nOpere);
        
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

struct mostre *modificaMostra(struct mostre *testa, struct mostre *mostra)
{
    int scelta, colonna = 0;
    char risposta;
    bool flagDate = false;
    
    char dataIn[11];
    bool dataCorrettaIn = true;
    int giornoIn = 0, meseIn = 0, annoIn = 0;
    
    char dataFin[11];
    bool dataCorrettaFin = true;
    int giornoFin = 0, meseFin = 0, annoFin = 0;
    
    struct mostre *temp = NULL;
    
    temp = mostra;
    
    printColor("\nDati relativi alla mostra scelta:\n", COLOR_CYAN);
    printf("Id: %d\n", temp->id);
    printf("Responsabile: %s\n", temp->responsabile);
    printf("Citta': %s\n", temp->citta);
    printf("Indirizzo: %s\n", temp->indirizzo);
    printf("Data inizio mostra: %s\n", temp->dataInizio);
    printf("Data fine mostra: %s\n", temp->dataFine);
    printf("Numero opere esposte: %d\n", temp->nOpere);
    printColor("----------\n\n", COLOR_CYAN);
    
    do
    {
        while ('\n' != getchar());
        
        //elenco campi modificabili
        printf("Scegliere il campo da modificare\n");
        printf("----------\n");
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
                fgets(temp->responsabile, 30, stdin);
                temp->responsabile[strlen(temp->responsabile) - 1] = 0;
                temp->responsabile[0] = toupper(temp->responsabile[0]);
                break;
            case 2:
                printf("Inserisci la città: ");
                fgets(temp->citta, 20, stdin);
                temp->citta[strlen(temp->citta) - 1] = 0;
                temp->citta[0] = toupper(temp->citta[0]);
                break;
                
            case 3:
                printf("Inserisci l'indirizzo: ");
                fgets(temp->indirizzo, 20, stdin);
                temp->indirizzo[strlen(temp->indirizzo) - 1] = 0;
                temp->indirizzo[0] = toupper(temp->indirizzo[0]);
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
                    
                    char *tok;
                    tok = strtok(temp->dataFine, "/");
                    
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
                        tok = strtok(NULL, "/");
                        colonna++;
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
                    
                }
                while(!flagDate);
                strcpy(temp->dataInizio, dataIn);
                
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
                    
                    char *tok;
                    tok = strtok(temp->dataInizio, "/");
                    
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
                        tok = strtok(NULL, "/");
                        colonna++;
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
                }
                while(!flagDate);
                strcpy(temp->dataFine, dataFin);
                
                break;
                
            case 6:
                printf("Inserisci il numero delle opere: ");
                scanf("%d", &temp->nOpere);
                break;
                
            default:
                break;
        }
        
        
        printf("Vuoi modificare un altro campo? (s/n): ");
        scanf("%c", &risposta);
        
        //rendo la risposta in maiuscolo
        risposta = toupper(risposta);
        printColor("fuori", COLOR_MAGENTA);
        if (risposta == 'N')
        {
            scriviMostre(testa);
        }
    }
    while (risposta == 'S');
    
    return testa;
}

void stampaMostre(struct mostre *testa)
{
    struct mostre *temp = NULL;
    
    for (temp = testa; temp != NULL; temp = temp->nextMostra)
    {
        printf("Mostra numero: %d \n", temp->id);
        printf("Responsabile: %s \n", temp->responsabile);
        printf("Luogo: %s - %s\n", temp->citta, temp->indirizzo);
        printf("Durata: dal %s al %s\n",  temp->dataInizio, temp->dataFine);
        printf("----------\n");
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




struct mostre *eliminaMostra(struct mostre *testa, struct mostre *mostra)
{
    char risposta;
    struct mostre *curr, *prec;
    struct mostre *temp;
    
    temp = mostra;
    prec = NULL;
    curr = testa;
    
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
        printf("test: %c\n", risposta);
    }
    while(risposta != 'S' && risposta != 'N');
    
    if (risposta == 'S')
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
    }
    return testa;
}


struct mostre *ricercaMostra(struct mostre *testa, int id) {
    bool flag = false;
    struct mostre *nuovoNodo = NULL;
    struct mostre *temp;
    
    for (temp = testa; temp != NULL; temp = temp->nextMostra) {
        
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
