//Gestione Utente
#define ID 1
#define BUFFER_SIZE 1024
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"

//Definizione della struct Utente
struct utente {
    int id;
    char nome[20];
    char cognome[20];
    char email[60];
    char dataNascita[10]; // gg/mm/aaaa
    char telefono[10];
    int permessi; //livello 1 = utente normale; livello 2 = direttore generale, ha accesso a tutto;
    struct utente *nextUtente; //puntatore al prossimo nodo
}utente;

struct utente* registrazione(struct utente* testa){
    struct utente *nuovoNodo = NULL;

    nuovoNodo = (struct utente*)malloc(sizeof(struct utente));
    
    int ultimoID;
    
    ultimoID = letturaUltimoID();
    FILE *fp;
    fp = fopen("utenti.csv", "a+"); //apertura file
    
    printf("Inserisci Nome: ");
    fgets(nuovoNodo->nome, 20, stdin);
    nuovoNodo->nome[strlen(nuovoNodo->nome)-1] = 0;
    printf("\n");
    
    printf("Inserisci Cognome: ");
    fgets(nuovoNodo->cognome, 20, stdin);
    nuovoNodo->cognome[strlen(nuovoNodo->cognome)-1] = 0;
    printf("\n");
    
    printf("Inserisci Email (non ti dimenticare la @): \n");
    fgets(nuovoNodo->email, 60, stdin);
    nuovoNodo->email[strlen(nuovoNodo->email)-1] = 0;
        
    //verifico che sia stata inserita la @
    char *ptr;
    char *a = "@";
    ptr = strstr(nuovoNodo->email, a);
        
    while(ptr == NULL) {
        #ifdef _WIN32
            HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 12);
            printf("Attenzione! L'email inserita non e' corretta\n");
            SetConsoleTextAttribute(hConsole, 15);
        #endif
            
        #ifdef __APPLE__
            printf(ANSI_COLOR_RED "Attenzione! L'email inserita non e' corretta\n" ANSI_COLOR_RESET "\n");
        #endif
        
        printf("Inserisci Email (non ti dimenticare la @): \n");
        fgets(nuovoNodo->email, 60, stdin);
        nuovoNodo->email[strlen(nuovoNodo->email)-1] = 0;
        ptr = strstr(nuovoNodo->email, a);
    }
    printf("\n");
    
    //controlli sulla data di nascita
    char data[10];
    int giorno, mese, anno;
    int etaMinima;
    
    printf("Inserisci data di nascita\n");
    do {
        do {
            printf("Giorno: ");
            scanf("%d", &giorno);
            printf("\n");
        } while((giorno < 0) || (giorno > 31));
        
        printf("Mese: ");
        scanf("%d", &mese);
        printf("\n");
    } while ((mese == 2 && giorno > 28) || (mese == 4||mese == 6||mese == 9) || (mese == 11 && giorno == 31));
    
    do {
        printf("Anno: ");
        scanf("%d", &anno);
        printf("\n");
        
        //controllo la data odierna
        time_t now;
        struct tm *ts;
        char annoCorrente[5];

        now = time(NULL);

        ts = localtime(&now);
        strftime(annoCorrente, sizeof(annoCorrente), "%Y", ts);
        
        // per potersi registrare al sistema bisogna avere almeno 16 anni
        etaMinima = atoi(annoCorrente) - 16;
        
    } while((anno < 1900) || (anno > etaMinima));
            
    snprintf(data, 10, "%d/%d/%d", giorno, mese, anno);
    printf("Prova data %s\n", data);
    
    strcpy(nuovoNodo->dataNascita, data);
    
    printf("Inserisci Password: ");

    
    
    
    //verifico se nel file ci sono già utenti registrati o meno
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    
    if(size == 0) { //file vuoto. quindi il primo utente registrato avrà i permessi di livello 2
        
        printf("File vuoto\n");
        nuovoNodo->id = ID;
        nuovoNodo->permessi = 2;
        
    } else { //file pieno
        
        printf("file pieno\n");
        ultimoID = letturaUltimoID();
        nuovoNodo->id = ultimoID + 1;
        
        nuovoNodo->permessi = 1;
     }
    
    fprintf(fp, "%d,%s,%s,%s,%s,%d\n", nuovoNodo->id, nuovoNodo->nome, nuovoNodo->cognome, nuovoNodo->email, nuovoNodo->dataNascita, nuovoNodo->permessi);
    
    nuovoNodo->nextUtente = testa;
    
    fclose(fp);
    
    return nuovoNodo;
}

int letturaUltimoID() {
    FILE *fp;
    fp = fopen("utenti.csv", "r"); //apertura file
    int totRighe = 0;
    
    //verifico se il file è pieno o vuoto
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
        
    int ultimoID = 0;
    char buf[BUFFER_SIZE];
    
    fseek(fp, 0, SEEK_SET); //riposiziono il puntatore all'inizio del file
        
    if(size != 0) { //file pieno - verifico quindi quale sia l'ultimo ID
            
        totRighe = contaRighe() -1;
        
        int i=0; //contatore
        
        while(!feof(fp)) {
            fgets(buf, sizeof(buf), fp);
            buf[strlen(buf)-1] = 0;
            
            if (i == totRighe) {
                char *tok;
                tok = strtok(buf, ",");
                
                ultimoID = atoi(tok);
            } else {
                i++;
            }
            
        }
    }
    fclose(fp);
        
    return ultimoID;
}

int contaRighe() {
    int totRighe = 0;
    char str[BUFFER_SIZE];
    
    FILE *fp;
    fp = fopen("utenti.csv", "r"); //apertura file
    
    while (!feof(fp)) {
        fgets(str, sizeof(BUFFER_SIZE), fp);
        str[strlen(str)-1] = 0;
        totRighe++;
    }
        
    return totRighe;
}
