//Gestione Utente
#define ID 1
#define BUFFER_SIZE 1024

//Definizione della struct Utente
struct utente {
    int id;
    char nome[20];
    char cognome[20];
    char email[60];
    char password[20];
    char dataNascita[10]; // gg/mm/aaaa
    int permessi; //livello 1 = utente normale; livello 2 = direttore generale, ha accesso a tutto;
    struct utente *nextUtente; //puntatore al prossimo nodo
}utente;

struct utente* registrazione(struct utente* testa){
    struct utente *nuovoNodo = NULL;

    nuovoNodo = (struct utente*)malloc(sizeof(struct utente));
    
    int ultimoID;
    bool annoBis = false; //flag anno bisestile
    bool dataCorretta = false; //flag per correttezza verifica data di nascita

    
    FILE *fp;
    fp = fopen("utenti.csv", "a+"); //apertura file
    
    while('\n'!=getchar());
    
    printf("Inserisci Nome: ");
    fgets(nuovoNodo -> nome, 20, stdin);
    nuovoNodo -> nome[strlen(nuovoNodo -> nome)-1] = 0;
    //printf("\n");
    
    printf("Inserisci Cognome: ");
    fgets(nuovoNodo -> cognome, 20, stdin);
    nuovoNodo -> cognome[strlen(nuovoNodo -> cognome)-1] = 0;
    printf("---------------------------------\n");
    
    printf("Inserisci Email (non ti dimenticare la @): \n");
    fgets(nuovoNodo -> email, 60, stdin);
    nuovoNodo -> email[strlen(nuovoNodo -> email)-1] = 0;
        
    //verifico che sia stata inserita la @
    char *ptr;
    char *a = "@";
    ptr = strstr(nuovoNodo -> email, a);
        
    while(ptr == NULL) {
		printColor("Attenzione! L'email inserita non e' corretta\n", COLOR_RED);
        
        printf("Inserisci Email (non ti dimenticare la @): \n");
        fgets(nuovoNodo -> email, 60, stdin);
        nuovoNodo -> email[strlen(nuovoNodo -> email)-1] = 0;
        ptr = strstr(nuovoNodo -> email, a);
    }
    printf("---------------------------------\n");
    char psw[20];
    readPassword("Password: ", psw);
    strcpy(nuovoNodo -> password, psw);
    
    printf("---------------------------------\n");
    //controlli sulla data di nascita
    char data[10];
    int giorno, mese, anno;
    int etaMinima;
    
    printf("Inserisci data di nascita\n");

	
	printColor("---Per potersi registrare bisogna avere almeno 16 anni---\n", COLOR_RED);
    
    do {
        do {
            printf("Giorno: ");
            scanf("%d", &giorno);
           // printf("\n");
        } while (giorno < 0 || giorno > 31);
        
        do {
            printf("Mese: ");
            scanf("%d", &mese);
           // printf("\n");
        } while (mese < 1 || mese > 12);
    
        printf("Anno (dal 1900 in poi): ");
        scanf("%d", &anno);
        // printf("\n");
        printf("---------------------------------\n");
        
        //controllo se l'anno inserito è bisestile o meno
        if (anno % 4 == 0) {
            if (anno % 100 == 0) {
                if (anno % 400 == 0) {
                    annoBis = true;
                } else {
                    annoBis = false;
                }
            } else {
                annoBis = true;
            }
        } else {
            annoBis = false;
        }
    
        //controllo la correttezza di tutta la data inserita
        if((giorno > 28 && mese == 2 && annoBis == false) || (giorno > 29 && mese == 2 && annoBis == true)) {
            dataCorretta = false;
        } else {
            if (giorno > 31 && (mese == 1 || mese == 3 || mese == 5 || mese == 7 || mese == 8 || mese == 10 || mese == 12)) {
                dataCorretta = false;
            } else {
                if (giorno > 30 && (mese == 4 || mese == 6 || mese == 9 || mese == 11 )) {
                    dataCorretta = false;
                } else {
                    dataCorretta = true;
                }
            }
        }
        
        //controllo la data odierna, per verificare se l'utente ha l'eta minima richiesta per potersi iscrivere
        time_t now;
        struct tm *ts;
        char annoCorrente[5];

        now = time(NULL);

        ts = localtime(&now);
        strftime(annoCorrente, sizeof(annoCorrente), "%Y", ts);
        
        // per potersi registrare al sistema bisogna avere almeno 16 anni
        etaMinima = atoi(annoCorrente) - 16;
        
    //se l'età è minore a quella richiesta, oppure, se la data di nascita inserita è errata verrà richiesto l'inserimento
    } while(anno > etaMinima || dataCorretta == false);
            
    snprintf(data, 10, "%d/%d/%d", giorno, mese, anno);
    
    strcpy(nuovoNodo -> dataNascita, data);
    
    //verifico se nel file ci sono già utenti registrati o meno
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    
    if(size == 0) { //file vuoto. quindi il primo utente registrato avrà i permessi di livello 2
        
        nuovoNodo -> id = ID;
        nuovoNodo -> permessi = 2;
    } else { //file pieno
        
        ultimoID = letturaUltimoID();
        nuovoNodo -> id = ultimoID + 1;
        nuovoNodo -> permessi = 1;
    }
    
    fprintf(fp, "%d,%s,%s,%s,%s,%s,%d\n", nuovoNodo -> id, nuovoNodo -> nome, nuovoNodo -> cognome, nuovoNodo -> email, nuovoNodo -> password, nuovoNodo -> dataNascita, nuovoNodo -> permessi);
    
    nuovoNodo -> nextUtente = testa;
    
    testa = nuovoNodo;
    
    fclose(fp);
    
    return nuovoNodo;
}

int letturaUltimoID() {
    FILE *fp;
    fp = fopen("utenti.csv", "r"); //apertura file
    
    int totRighe = 0;
    int ultimoID = 0;
    char buf[BUFFER_SIZE];
    char *res;
    
    totRighe = contaRighe();
    int i=1; //contatore
    
    while(1) {
        res=fgets(buf, 200, fp);
        if(res == NULL) {
            break;
        }
        
        if (i == totRighe) {
            char *tok;
            tok = strtok(buf, ",");
            ultimoID = atoi(tok);
        } else {
            i++;
        }
    }
     
    fclose(fp);
    return ultimoID;
}


int contaRighe() {
    
    FILE *fp;
    fp = fopen("utenti.csv", "r"); //apertura file
    
    int totRighe = 0;
    char buffer;
    
    while (true) {
        fread((void *)&buffer,sizeof(char),1,fp);
        if (feof(fp)) {
            break;
        }
        if (buffer == '\n') {
            totRighe++;
        }
    }
    
    return totRighe;
}

struct utente *accesso(struct utente *testa, char *email){
    bool flag= false;
    struct utente *nuovoNodo = NULL;
    struct utente *temp;

    char pass[20] = "";
    readPassword("Password: ", pass);
    
    for(temp = testa; temp != NULL; temp = temp -> nextUtente){
        
        if(strcmp(temp->email, email) == 0 && strcmp(temp -> password, pass) == 0){

			printColor("---Email e/o Password errati!---\n", COLOR_GREEN);
            nuovoNodo = temp;
            flag = true;
            break;
            
        }
     }
    
    if(!flag){
		printColor("---Email e/o Password errati!---\n", COLOR_RED);
    }
    
    if(flag)
        return nuovoNodo;
    else
        return NULL;
}

void stampa(struct utente* testa) {

	struct utente* temp=NULL;
	temp = testa;

    consoleColor(COLOR_CYAN);
    printf("%d,%s,%s,%s,%s,%s,%d\n", temp -> id, temp -> nome, temp -> cognome, temp -> email, temp -> password, temp -> dataNascita, temp -> permessi );
    consoleColor(COLOR_RESET);

}
