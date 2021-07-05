//Gestione Utente
#define BUFFER_SIZE 1024
#define nomeFile "utenti.csv"

//Definizione della struct Utente
struct utente {
    int id;
    char nome[20];
    char cognome[20];
    char nick[20];
    char email[60];
    char password[20];
    char dataNascita[11]; // gg/mm/aaaa
    int permessi; //livello 1 = utente normale; livello 2 = direttore generale, ha accesso a tutto;
    struct utente *nextUtente; //puntatore al prossimo nodo
} utente;

struct utente *registrazioneUtente(struct utente *testa) {
    struct utente *nuovoNodo = NULL;
    struct utente *temp;
    struct utente *curr, *prec;
    prec = NULL;
    curr = testa;
    
    nuovoNodo = (struct utente *) malloc(sizeof(struct utente));

    int ultimoID = 0;
    bool dataCorretta = true; //flag per verificare la correttezza della data di nascita
    bool flag = false; //flag per controllare univocità del campo email e nickname

    FILE *fp;
    fp = fopen("utenti.csv", "a+"); //apertura file

    while ('\n' != getchar());

    printf("Inserisci Nome: ");
    fgets(nuovoNodo->nome, 20, stdin);
    nuovoNodo->nome[strlen(nuovoNodo->nome) - 1] = 0;
    nuovoNodo->nome[0] = toupper(nuovoNodo->nome[0]);

    printf("Inserisci Cognome: ");
    fgets(nuovoNodo->cognome, 20, stdin);
    nuovoNodo->cognome[strlen(nuovoNodo->cognome) - 1] = 0;
    nuovoNodo->cognome[0] = toupper(nuovoNodo->cognome[0]);
    printf("-----------------------------\n");
    
    do {
        flag = false;
        printf("Inserisci Nickname: ");
        fgets(nuovoNodo->nick, 20, stdin);
        nuovoNodo->nick[strlen(nuovoNodo->nick) - 1] = 0;
        /*
        for (temp = testa; temp != NULL; temp = temp->nextUtente) {

            if (strcmp(temp->nick, nuovoNodo->nick) == 0) {
                flag = true;
                break;
            }
        }
        
        if (flag) {
            printColor("---Nickname gia' in uso!---\n", COLOR_RED);
            printColor("---Si prega di sceglierne un altro---\n", COLOR_RED);
        } */
        
    } while(flag);
    
    printf("-----------------------------\n");
    
    do {
        flag = false;
        printf("Inserisci Email (non ti dimenticare la @): \n");
        fgets(nuovoNodo->email, 60, stdin);
        nuovoNodo->email[strlen(nuovoNodo->email) - 1] = 0;
        
        for (temp = testa; temp != NULL; temp = temp->nextUtente) {

            if (strcmp(temp->email, nuovoNodo->email) == 0) {
                flag = true;
                break;
            }
        }
        
        if (flag) {
            printColor("---Email gia' in uso!---\n", COLOR_RED);
            printColor("---Si prega di sceglierne un'altra---\n", COLOR_RED);
        }
        
    } while (flag);

    //verifico che sia stata inserita la @
    char *ptr;
    char *a = "@";
    ptr = strstr(nuovoNodo->email, a);

    while (ptr == NULL) {
        printColor("Attenzione! L'email inserita non e' corretta\n", COLOR_RED);

        printf("Inserisci Email (non ti dimenticare la @): \n");
        fgets(nuovoNodo->email, 60, stdin);
        nuovoNodo->email[strlen(nuovoNodo->email) - 1] = 0;
        ptr = strstr(nuovoNodo->email, a);
    }
    
    printf("-----------------------------\n");
    char psw[20];
    readPassword("Password: ", psw);
    strcpy(nuovoNodo->password, psw);

    printf("-----------------------------\n");
    
    //controlli sulla data di nascita
    char data[11];
    int giorno, mese, anno;

    printf("Inserisci data di nascita\n");

    printColor("---Per potersi registrare bisogna avere almeno 16 anni---\n\n", COLOR_RED);
    
    do {
        if(!dataCorretta) {
            printColor("\nAttenzione!\n", COLOR_RED);
            printf("La data inserita non è corretta.\nSi prega di inserirla nuovamente\n\n");
        }
        
        do {
            printf("Giorno: ");
            scanf("%d", &giorno);
        } while (giorno < 0 || giorno > 31);

        do {
            printf("Mese: ");
            scanf("%d", &mese);
        } while (mese < 1 || mese > 12);

        printf("Anno (dal 1900 in poi): ");
        scanf("%d", &anno);
        
        dataCorretta = verificaData(giorno, mese, anno);
        
    } while (!dataCorretta);
    
    while ('\n' != getchar());

    snprintf(data, 11, "%d/%d/%d", giorno, mese, anno);
    strcpy(nuovoNodo->dataNascita, data);

    //verifico se nel file ci sono già utenti registrati o meno
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    
    ultimoID = letturaUltimoID(nomeFile) + 1;
    
    //ricerca della posizione di inserimento
    while(curr != NULL && ultimoID > curr->id) {
        prec = curr;
        curr = curr->nextUtente;
    }

    if (size == 0) { //file vuoto. quindi il primo utente registrato avrà i permessi di livello 2
        
        nuovoNodo->id = 0;
        nuovoNodo->permessi = 2;
        
        fprintf(fp, "%d,%s,%s,%s,%s,%s,%s,%d", nuovoNodo->id, nuovoNodo->nome, nuovoNodo->cognome, nuovoNodo->nick, nuovoNodo->email, nuovoNodo->password, nuovoNodo->dataNascita, nuovoNodo->permessi);
          
    } else { //file pieno
        
        nuovoNodo->id = ultimoID;
        nuovoNodo->permessi = 1;
        
        fprintf(fp, "\n%d,%s,%s,%s,%s,%s,%s,%d", nuovoNodo->id, nuovoNodo->nome, nuovoNodo->cognome, nuovoNodo->nick, nuovoNodo->email, nuovoNodo->password, nuovoNodo->dataNascita, nuovoNodo->permessi);
        
    }
    
    fclose(fp);
    
    //aggiornamento dei collegamenti
    if(prec == NULL) {
        nuovoNodo->nextUtente = testa;
        testa = nuovoNodo;
        return testa;
    } else {
        prec->nextUtente = nuovoNodo;
        nuovoNodo->nextUtente = curr;
        return testa;
    }
    
}



struct utente *accesso(struct utente *testa, char *email) {
    bool flag = false;
    struct utente *nuovoNodo = NULL;
    struct utente *temp;

    char pass[20] = "";
    readPassword("Password: ", pass);

    for (temp = testa; temp != NULL; temp = temp->nextUtente) {

        if (strcmp(temp->email, email) == 0 && strcmp(temp->password, pass) == 0) {

            printColor("---Login effettuato---\n", COLOR_GREEN);
            nuovoNodo = temp;
            flag = true;
            break;

        }
    }

    if (!flag) {
        printColor("---Email e/o Password errati!---\n", COLOR_RED);
    }

    if (flag)
        return nuovoNodo;
    else
        return NULL;
}

void stampaUtente(struct utente *utenteLogin) {
    struct utente *temp = NULL;
    temp = utenteLogin;

    printf("Id: %d\n", temp->id);
    printf("Nome: %s\n", temp->nome);
    printf("Cognome: %s\n", temp->cognome);
    printf("Nickname: %s\n", temp->nick);
    printf("Email: %s\n", temp->email);
    printf("Data di nascita: %s\n", temp->dataNascita);

    if (temp->permessi == 1) {
        printf("Permessi: utente\n");
    } else {
        printf("Permessi: direttore\n");
    }

    printColor("-----------------------------\n", COLOR_CYAN);

}

struct utente *modificaUtente(struct utente *utenteLogin, struct utente *testa) {
    int scelta;
    char risposta;

    char data[11];
    int giorno, mese, anno;
    bool dataCorretta = true; //flag per verificare la correttezza della data di nascita
    bool flag = false;
    
    struct utente *temp = NULL;

    temp = utenteLogin;

    do {
        
        //elenco campi modificabili
        printf("----------\n");
        printf("1: Nome\n");
        printf("2: Cognome\n");
        printf("3: Email\n");
        printf("4: Password\n");
        printf("5: Data di nascita\n");
        printf("-> ");
        scanf("%d", &scelta);
        printf("\n");
        while ('\n' != getchar());

        switch (scelta) {
            case 1:
                printf("Inserisci il nuovo nome: ");
                fgets(temp->nome, 20, stdin);
                temp->nome[strlen(temp->nome) - 1] = 0;
                temp->nome[0] = toupper(temp->nome[0]);
                break;

            case 2:
                printf("Inserisci il nuovo cognome: ");
                fgets(temp->cognome, 20, stdin);
                temp->cognome[strlen(temp->cognome) - 1] = 0;
                temp->cognome[0] = toupper(temp->cognome[0]);
                break;

            case 3:
                
                do {
                    flag = false;
                    printf("Inserisci Email (non ti dimenticare la @): \n");
                    fgets(temp->email, 60, stdin);
                    temp->email[strlen(temp->email) - 1] = 0;
                    
                    for (temp = testa; temp != NULL; temp = temp->nextUtente) {

                        if (strcmp(temp->email, temp->email) == 0) {
                            flag = true;
                            break;
                        }
                    }
                    
                    if (flag) {
                        printColor("---Email gia' in uso!---\n", COLOR_RED);
                        printColor("---Si prega di sceglierne un'altra---\n", COLOR_RED);
                    }
                    
                } while (flag);
                
                //verifico che sia stata inserita la @
                char *ptr;
                char *a = "@";
                ptr = strstr(temp->email, a);

                while (ptr == NULL) {

                    printColor("Attenzione! L'email inserita non e' corretta", COLOR_RED);

                    printf("Inserisci Email (non ti dimenticare la @): \n");
                    fgets(temp->email, 60, stdin);
                    temp->email[strlen(temp->email) - 1] = 0;
                    ptr = strstr(temp->email, a);
                }
                break;

            case 4:;
                char newPassword[20] = "";
                readPassword("Inserisci la nuova password: ", newPassword);
                strcpy(temp->password, newPassword);
                break;


            case 5:
                printf("Inserisci data di nascita\n");

                printColor("---Per potersi registrare bisogna avere almeno 16 anni---\n\n", COLOR_RED);
                
                do {
                    if(!dataCorretta) {
                        printColor("\nAttenzione!\n", COLOR_RED);
                        printf("La data inserita non è corretta.\nSi prega di inserirla nuovamente\n\n");
                    }
                    
                    do {
                        printf("Giorno: ");
                        scanf("%d", &giorno);
                    } while (giorno < 0 || giorno > 31);

                    do {
                        printf("Mese: ");
                        scanf("%d", &mese);
                    } while (mese < 1 || mese > 12);

                    printf("Anno (dal 1900 in poi): ");
                    scanf("%d", &anno);
                    
                    dataCorretta = verificaData(giorno, mese, anno);
                    
                } while (!dataCorretta);

                snprintf(data, 11, "%d/%d/%d", giorno, mese, anno);
                strcpy(temp->dataNascita, data);
                
                while ('\n' != getchar());
                break;

            default:
                break;
        }
        
        do {
            
            printf("Vuoi modificare un altro campo? (s/n): ");
            scanf("%c", &risposta);
            while ('\n' != getchar());
            
            //rendo la risposta in maiuscolo per evitare errori
            risposta = toupper(risposta);
            
            if (risposta == 'N') {
                scriviUtenti(testa);
            }
            
        } while(risposta != 'S' && risposta != 'N');
        
    } while (risposta == 'S');

    return testa;
}

struct utente *eliminaUtente(struct utente *utenteLogin, struct utente *testa) {
    char risposta;
    struct utente *curr, *prec;
    struct utente *temp = NULL;

    temp = utenteLogin;
    prec = NULL;
    curr = testa;
    
    do {
        //while ('\n' != getchar());
        printColor("ATTENZIONE!\n", COLOR_RED);
        printf("Sei sicuro/a di voler eliminare il tuo account?\n");
        printf("Per poter riaccedere dovrai creare un nuovo account\n");
        printf("Risposta (s/n): ");
        scanf("%c", &risposta);
        printf("\n");
        while ('\n' != getchar());
        
        //rendo la risposta in maiuscolo per evitare errori
        risposta = toupper(risposta);
        
    }while(risposta != 'S' && risposta != 'N');
    
    if (risposta == 'S') {
        
        while (curr != NULL && temp->id != curr->id) {
            prec = curr;
            curr = curr->nextUtente;
        }
        
        if(temp->id == curr->id) {
            if(prec == NULL) { //elemento trovato in testa
                testa = curr->nextUtente;
            } else { //elemento al centro della lista
                prec->nextUtente = curr->nextUtente;
            }
            free(curr);
        }
        
        scriviUtenti(testa);
    } else {
        printColor("-----------------------------\n", COLOR_CYAN);
        printf("%s siamo contenti che tu abbia deciso di rimanere con noi!\n", temp->nome);
    }
    
    return testa;
}

void scriviUtenti(struct utente *testa) {
    struct utente *temp =  NULL;

    FILE *fp;
    fp = fopen("utenti.csv", "w"); //apertura file
    
    for (temp = testa; temp != NULL; temp = temp->nextUtente) {
        long size = ftell(fp);
        
        if (size == 0) { //file vuoto.
            fprintf(fp, "%d,%s,%s,%s,%s,%s,%s,%d", temp->id, temp->nome, temp->cognome, temp->nick, temp->email, temp->password, temp->dataNascita, temp->permessi);
        } else { //file pieno
            fprintf(fp, "\n%d,%s,%s,%s,%s,%s,%s,%d", temp->id, temp->nome, temp->cognome, temp->nick, temp->email, temp->password, temp->dataNascita, temp->permessi);
        }
    }
    
    fclose(fp);
}
