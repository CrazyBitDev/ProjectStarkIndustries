//Gestione Utente
#define BUFFER_SIZE 1024

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
    
    nuovoNodo = (struct utente *) malloc(sizeof(struct utente));

    int ultimoID;
    bool annoBis = false; //flag anno bisestile
    bool dataCorretta = false; //flag per correttezza verifica data di nascita
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
        
        for (temp = testa; temp != NULL; temp = temp->nextUtente) {

            if (strcmp(temp->nick, nuovoNodo->nick) == 0) {
                flag = true;
                break;
            }
        }
        
        if (flag) {
            printColor("---Nickname gia' in uso!---\n", COLOR_RED);
            printColor("---Si prega di sceglierne un altro---\n", COLOR_RED);
        }
        
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
    int etaMinima;

    printf("Inserisci data di nascita\n");

    printColor("---Per potersi registrare bisogna avere almeno 16 anni---\n", COLOR_RED);
    
    do {
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
        if ((giorno > 28 && mese == 2 && annoBis == false) || (giorno > 29 && mese == 2 && annoBis == true)) {
            dataCorretta = false;
        } else {
            if (giorno > 31 &&
                (mese == 1 || mese == 3 || mese == 5 || mese == 7 || mese == 8 || mese == 10 || mese == 12)) {
                dataCorretta = false;
            } else {
                if (giorno > 30 && (mese == 4 || mese == 6 || mese == 9 || mese == 11)) {
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
    } while (anno > etaMinima || dataCorretta == false);

    snprintf(data, 11, "%d/%d/%d", giorno, mese, anno);
    //data = dataNascita();
    strcpy(nuovoNodo->dataNascita, data);

    //verifico se nel file ci sono già utenti registrati o meno
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);

    if (size == 0) { //file vuoto. quindi il primo utente registrato avrà i permessi di livello 2
        
        nuovoNodo->id = 0;
        nuovoNodo->permessi = 2;
        
        fprintf(fp, "%d,%s,%s,%s,%s,%s,%s,%d", nuovoNodo->id, nuovoNodo->nome, nuovoNodo->cognome, nuovoNodo->nick, nuovoNodo->email, nuovoNodo->password, nuovoNodo->dataNascita, nuovoNodo->permessi);
          
     } else { //file pieno

        ultimoID = letturaUltimoID();
        nuovoNodo->id = ultimoID + 1;
        nuovoNodo->permessi = 1;
        
        fprintf(fp, "\n%d,%s,%s,%s,%s,%s,%s,%d", nuovoNodo->id, nuovoNodo->nome, nuovoNodo->cognome, nuovoNodo->nick, nuovoNodo->email, nuovoNodo->password, nuovoNodo->dataNascita, nuovoNodo->permessi);
        
    }

    nuovoNodo->nextUtente = testa;

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
    int i = 1; //contatore

    while (1) {
        res = fgets(buf, 200, fp);
        if (res == NULL) {
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
        fread((void *) &buffer, sizeof(char), 1, fp);
        if (feof(fp)) {
            break;
        }
        if (buffer == '\n') {
            totRighe++;
        }
    }
    
    fclose(fp);
    return totRighe;
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
    char risposta[3];

    char data[10];
    int giorno, mese, anno;
    int etaMinima;
    bool annoBis = false; //flag anno bisestile
    bool dataCorretta = false; //flag per correttezza verifica data di nascita

    struct utente *temp = NULL;

    temp = utenteLogin;

    do {
        while ('\n' != getchar());

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
                printf("Inserisci la nuova Email (non ti dimenticare la @): \n");
                fgets(temp->email, 60, stdin);
                temp->email[strlen(temp->email) - 1] = 0;

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
                //prossisamente sarà una funzione (?)
                //controlli sulla data di nascita
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
                    if ((giorno > 28 && mese == 2 && annoBis == false) ||
                        (giorno > 29 && mese == 2 && annoBis == true)) {
                        dataCorretta = false;
                    } else {
                        if (giorno > 31 &&
                            (mese == 1 || mese == 3 || mese == 5 || mese == 7 || mese == 8 || mese == 10 ||
                             mese == 12)) {
                            dataCorretta = false;
                        } else {
                            if (giorno > 30 && (mese == 4 || mese == 6 || mese == 9 || mese == 11)) {
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
                } while (anno > etaMinima || dataCorretta == false);

                snprintf(data, 10, "%d/%d/%d", giorno, mese, anno);
                //data = dataNascita();
                strcpy(temp->dataNascita, data);
                
                while ('\n' != getchar());
                break;

            default:
                break;
        }
        
        printf("Vuoi modificare un altro campo? (si/no): ");
        fgets(risposta, 3, stdin);

        //rendo la risposta tutta maiuscola per evitare errori
        for (int i = 0; i < strlen(risposta); i++) {
            risposta[i] = toupper(risposta[i]);
        }

        if (strcmp(risposta, "NO") == 0) {
            scriviUtenti(testa);
        }

    } while (strcmp(risposta, "SI") == 0);

    return testa;
}

struct utente *eliminaUtente(struct utente *utenteLogin, struct utente *testa) {
    char risposta[3];
    struct utente *curr, *prec;
    struct utente *temp = NULL;

    temp = utenteLogin;
    prec = NULL;
    curr = testa;
    
    do {
        while ('\n' != getchar());
        printColor("ATTENZIONE!\n", COLOR_RED);
        printf("Sei sicuro/a di voler eliminare il tuo account?\n");
        printf("Per poter riaccedere dovrai creare un nuovo account\n");
        printf("Risposta (si/no): ");
        fgets(risposta, 3, stdin);
        printf("\n");
        
        //rendo la risposta tutta maiuscola per evitare errori
        for (int i = 0; i < strlen(risposta); i++) {
            risposta[i] = toupper(risposta[i]);
        }
        
    }while(strcmp(risposta, "SI") != 0 && strcmp(risposta, "NO") != 0);
    
    if (strcmp(risposta, "SI") == 0) {
        
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
    struct utente *temp;

    FILE *fp;
    fp = fopen("utentiTemp.csv", "w"); //apertura file
    
    ordinamento(testa);
    
    for (temp = testa; temp != NULL; temp = temp->nextUtente) {
        long size = ftell(fp);

        if (size == 0) { //file vuoto.
            fprintf(fp, "%d,%s,%s,%s,%s,%s,%s,%d", temp->id, temp->nome, temp->cognome, temp->nick, temp->email, temp->password, temp->dataNascita, temp->permessi);
        } else { //file pieno
            fprintf(fp, "\n%d,%s,%s,%s,%s,%s,%s,%d", temp->id, temp->nome, temp->cognome, temp->nick, temp->email, temp->password, temp->dataNascita, temp->permessi);
        }
    }
    
    remove("utenti.csv");
    rename("utentiTemp.csv", "utenti.csv");
    fclose(fp);
}

//ordinamento lista
struct utente *ordinamento(struct utente *testa) {
    Utente *p, *ultimo;
    int flag, tempId, tempPermessi;
    char tempNome[20], tempCognome[20], tempNick[20], tempEmail[60], tempPassword[20], tempDataNascita[11];
    
    ultimo = NULL;

    flag = 1;
    while (flag == 1) {
        p = testa;
        flag = 0;
        while (p->nextUtente != ultimo) {
            if (p->id > (p->nextUtente)->id) {
                
                tempId = p->id;
                p->id = (p->nextUtente)->id;
                (p->nextUtente)->id = tempId;
                
                strcpy(tempNome, p->nome);
                strcpy(p->nome, (p->nextUtente)->nome);
                strcpy((p->nextUtente)->nome, tempNome);
                
                strcpy(tempCognome, p->cognome);
                strcpy(p->cognome, (p->nextUtente)->cognome);
                strcpy((p->nextUtente)->cognome, tempCognome);
                
                strcpy(tempNick, p->nick);
                strcpy(p->nick, (p->nextUtente)->nick);
                strcpy((p->nextUtente)->nick, tempNick);
                
                strcpy(tempEmail, p->email);
                strcpy(p->email, (p->nextUtente)->email);
                strcpy((p->nextUtente)->email, tempEmail);
                
                strcpy(tempPassword, p->password);
                strcpy(p->password, (p->nextUtente)->password);
                strcpy((p->nextUtente)->password, tempPassword);
                
                strcpy(tempDataNascita, p->dataNascita);
                strcpy(p->dataNascita, (p->nextUtente)->dataNascita);
                strcpy((p->nextUtente)->dataNascita, tempDataNascita);
                
                tempPermessi = p->permessi;
                p->permessi = (p->nextUtente)->permessi;
                (p->nextUtente)->permessi = tempPermessi;
                
                flag = 1;
            }
            p = p->nextUtente;
        }
        ultimo = p;
    }

    return testa;
}
