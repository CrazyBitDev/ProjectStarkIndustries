struct utente {
    int id;
    char nome[20];
    char cognome[20];
    char nick[20];
    char email[60];
    char password[33];
    char dataNascita[11]; // gg/mm/aaaa
    int permessi; //livello 1 = utente normale; livello 2 = direttore generale, ha accesso a tutto;
    Utente *nextUtente; //puntatore al prossimo nodo
};

/**
 * Function: letturaUtenti
 * ----------------------------
 *   Permette di leggere i dati dal file "utenti.csv" e salvarli all'interno della struct Utente
 *
 *   @param fp puntatore alla variabile di tipo FILE, precedentemente configurata, che punta al file utenti.csv
 *
 *   @return puntatore alla variabile di tipo Utenti, una lista contenente tutte gli utenti
 */
Utente *letturaUtenti(FILE *fp) {

    int colonna = 0;
    char buf[BUFFER_SIZE];

    Utente *testaUtente = NULL;
    Utente *tempUtente = NULL; //temporanea
    Utente *precUtente = NULL;

    if (fp == NULL) {
        printColor("\t\t\t|-----------------------------|\n", COLOR_RED);
        printColor("\t\t\t|  File \"utenti\" non trovato! |\n", COLOR_RED);
        printColor("\t\t\t|             ...             |\n", COLOR_RED);
        printColor("\t\t\t|      File in creazione      |\n", COLOR_RED);
        printColor("\t\t\t|-----------------------------|\n", COLOR_RED);
    } else {
        while (!feof(fp)) {
            fgets(buf, BUFFER_SIZE, fp);
            tempUtente = (Utente *) malloc(sizeof(Utente));
            tempUtente->nextUtente = NULL;

            if (precUtente != NULL) {
                precUtente->nextUtente = tempUtente;
            } else {
                testaUtente = tempUtente;
            }

            char *tok;
            tok = strtok(buf, ",");

            while (tok) {
                if (colonna == 0) {
                    tempUtente->id = atoi(tok);
                }
                if (colonna == 1) {
                    strcpy(tempUtente->nome, tok);
                    tempUtente->nome[strlen(tempUtente->nome)] = 0;
                }
                if (colonna == 2) {
                    strcpy(tempUtente->cognome, tok);
                    tempUtente->cognome[strlen(tempUtente->cognome)] = 0;
                }
                if (colonna == 3) {
                    strcpy(tempUtente->nick, tok);
                    tempUtente->nick[strlen(tempUtente->nick)] = 0;
                }
                if (colonna == 4) {
                    strcpy(tempUtente->email, tok);
                    tempUtente->email[strlen(tempUtente->email)] = 0;
                }
                if (colonna == 5) {
                    strcpy(tempUtente->dataNascita, tok);
                    tempUtente->dataNascita[strlen(tempUtente->dataNascita)] = 0;
                }
                if (colonna == 6) {
                    strcpy(tempUtente->password, tok);
                    tempUtente->password[strlen(tempUtente->password)] = 0;
                }
                if (colonna == 7) {
                    tempUtente->permessi = atoi(tok);
                }
                tok = strtok(NULL, ",");
                colonna++;
            }
            colonna = 0;
            precUtente = tempUtente;

        }
    }

    return testaUtente;
}

/**
 * Function: registrazioneUtente
 * ----------------------------
 *   Permette la registrazione di un nuovo utente, con salvatggio dei dati sul file "utenti.csv" e nella struct Utente
 *
 *   @param testa puntatore alla variabile di tipo Utenti, una lista contenente tutte gli utenti
 */
void registrazioneUtente(Utente *testa) {
    Utente *nuovoNodo = NULL;
    Utente *temp;
    Utente *curr, *prec;
    prec = NULL;
    curr = testa;

    nuovoNodo = (Utente *) malloc(sizeof(Utente));

    int ultimoID = 0, i;
    int etaMinima;
    bool dataCorretta = true; //flag per verificare la correttezza della data di nascita
    bool flag = false; //flag per controllare univocità del campo email e nickname
    bool testInput = false; //flag per controllare i vari input
    bool continuaInserimento = true;

    FILE *fp;
    fp = fopen("utenti.csv", "a+"); //apertura file

    while ('\n' != getchar());

    notificaAnnulla(false);

    do {
        testInput = false;
        printf("Inserisci Nome: ");
        fgets(nuovoNodo->nome, 20, stdin);
        nuovoNodo->nome[strlen(nuovoNodo->nome) - 1] = 0;
        nuovoNodo->nome[0] = toupper(nuovoNodo->nome[0]);

        if (strlen(nuovoNodo->nome) == 0) {
            continuaInserimento = false;
            clearConsole();
            titolo();
            break;
        }

        for (i = 0; i < strlen(nuovoNodo->nome); i++) {
            if (isalpha(nuovoNodo->nome[i]) == 0 && nuovoNodo->nome[i] != ' ') {
                testInput = true; //carattere non alfabetico
            }
        }

        if (testInput) {
            clearConsole();
            titolo();
            printf("\n----------");
            printColor("\nAttenzione!\n", COLOR_RED);
            printf("Nome non valido.\n");
            printf("----------\n\n");
        }

    } while (testInput);
    if (continuaInserimento) {

        clearConsole();
        titolo();

        do {
            testInput = false;
            printf("Inserisci Cognome: ");
            fgets(nuovoNodo->cognome, 20, stdin);
            nuovoNodo->cognome[strlen(nuovoNodo->cognome) - 1] = 0;
            nuovoNodo->cognome[0] = toupper(nuovoNodo->cognome[0]);

            for (i = 0; i < strlen(nuovoNodo->cognome); i++) {
                if (isalpha(nuovoNodo->cognome[i]) == 0 && nuovoNodo->cognome[i] != ' ') {
                    testInput = true; //carattere non alfabetico
                }
            }

            if (testInput || strlen(nuovoNodo->cognome) == 0) {
                clearConsole();
                titolo();
                printf("\n----------");
                printColor("\nAttenzione!\n", COLOR_RED);
                printf("Cognome non valido.\n");
                printf("----------\n\n");
            }

        } while (testInput || strlen(nuovoNodo->cognome) == 0);

        printf("-----------------------------\n");

        do {
            testInput = false;
            flag = false;
            printf("Scegli con cura il tuo nickname perche' non e' modificabile.\n");
            printf("Inserisci Nickname: ");
            fgets(nuovoNodo->nick, 20, stdin);
            nuovoNodo->nick[strlen(nuovoNodo->nick) - 1] = 0;

            if (strlen(nuovoNodo->nick) == 0) {
                testInput = true;
                clearConsole();
                titolo();
                printf("\n----------");
                printColor("\nAttenzione!\n", COLOR_RED);
                printf("Nickname non valido\n");
                printf("----------\n\n");
            } else {

                //verifica univocita' nickname
                for (temp = testa; temp != NULL; temp = temp->nextUtente) {
                    if (strcmp(temp->nick, nuovoNodo->nick) == 0) {
                        flag = true;
                        break;
                    }
                }

                if (flag) {
                    clearConsole();
                    titolo();
                    printf("\n----------");
                    printColor("\nAttenzione!\n", COLOR_RED);
                    printColor("Nickname gia' in uso!\n", COLOR_RED);
                    printf("Si prega di sceglierne un altro\n");
                    printf("----------\n\n");
                }
            }


        } while (flag || testInput);

        printf("-----------------------------\n");

        do {
            flag = false;
            printf("Inserisci Email (non ti dimenticare la @): \n");
            fgets(nuovoNodo->email, 60, stdin);
            nuovoNodo->email[strlen(nuovoNodo->email) - 1] = 0;

            //verifica univocita' email
            for (temp = testa; temp != NULL; temp = temp->nextUtente) {

                if (strcmp(temp->email, nuovoNodo->email) == 0) {
                    flag = true;
                    break;
                }
            }

            if (flag) {
                clearConsole();
                titolo();
                printf("\n----------\n");
                printColor("Attenzione!\n", COLOR_RED);
                printColor("Email gia' in uso!\n", COLOR_RED);
                printf("Si prega di sceglierne un'altra\n");
                printf("----------\n\n");
            }


        } while (flag);

        //verifico che sia stata inserita la @
        char *ptr;
        char *a = "@";
        ptr = strstr(nuovoNodo->email, a);

        while (ptr == NULL) {
            clearConsole();
            printColor("Attenzione! L'email inserita non e' corretta\n", COLOR_RED);

            printf("Inserisci Email (non ti dimenticare la @): \n");
            fgets(nuovoNodo->email, 60, stdin);
            nuovoNodo->email[strlen(nuovoNodo->email) - 1] = 0;
            ptr = strstr(nuovoNodo->email, a);
        }

        printf("-----------------------------\n");
        char psw[32], psw2[32];

        //controllo su correttezza password
        do {

            readPassword("Password (minimo 6 caratteri): ", psw, true);

            readPassword("Conferma password: ", psw2, true);

            if (strcmp(psw, psw2) != 0) {
                clearConsole();
                titolo();
                printColor("\nAttenzione!\n", COLOR_RED);
                printf("Le password non coincidono fra loro\n");
                printf("Effettuare nuovamente l'inserimento\n\n");
            }

        } while (strcmp(psw, psw2) != 0);

        strcpy(nuovoNodo->password, psw);

        printf("-----------------------------\n");


        //controlli sulla data di nascita
        char data[11];
        int giorno, mese, anno;
        bool controllo = true;

        printf("Inserisci data di nascita\n");

        printColor("Attenzione!\n", COLOR_RED);
        printf("Per potersi registrare bisogna avere almeno 16 anni\n\n");

        do {
            if (!dataCorretta) {
                clearConsole();
                titolo();
                printColor("\nAttenzione!\n", COLOR_RED);
                printf("La data inserita non e' corretta.\nSi prega di inserirla nuovamente\n\n");
            }

            do {
                if (!controllo) {
                    clearConsole();
                    titolo();
                    printf("\n----------");
                    printColor("\nAttenzione!\n", COLOR_RED);
                    printf("Giorno non valido.\n");
                    printf("----------\n\n");
                }

                do {
                    printf("Giorno: ");
                    scanf("%d", &giorno);
                } while (giorno < 1 || giorno > 31);


            } while (giorno < 1 || giorno > 31 || testInput);

            do {
                while ('\n' != getchar());
                printf("Mese: ");
                scanf("%d", &mese);
            } while (mese < 1 || mese > 12);

            do {
                // while ('\n' != getchar());
                printf("Anno (dal 1900 in poi): ");
                scanf("%d", &anno);
            } while (anno < 1900);

            dataCorretta = verificaData(giorno, mese, anno);

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
            if (anno > etaMinima || dataCorretta == false) {
                dataCorretta = false;
            } else {
                dataCorretta = true;
            }

        } while (!dataCorretta);

        while ('\n' != getchar());

        snprintf(data, 11, "%d/%d/%d", giorno, mese, anno);
        strcpy(nuovoNodo->dataNascita, data);

        //verifico se nel file ci sono già utenti registrati o meno
        fseek(fp, 0, SEEK_END);
        long size = ftell(fp);

        ultimoID = letturaUltimoID("utenti.csv") + 1;

        //ricerca della posizione di inserimento
        while (curr != NULL && ultimoID > curr->id) {
            prec = curr;
            curr = curr->nextUtente;
        }

        if (size == 0) { //file vuoto. quindi il primo utente registrato avrà i permessi di livello 2

            nuovoNodo->id = 0;
            nuovoNodo->permessi = 2;
            fprintf(fp, "%d,%s,%s,%s,%s,%s,%s,%d", nuovoNodo->id, nuovoNodo->nome, nuovoNodo->cognome, nuovoNodo->nick,
                    nuovoNodo->email, nuovoNodo->dataNascita, nuovoNodo->password, nuovoNodo->permessi);

        } else { //file pieno

            nuovoNodo->id = ultimoID;
            nuovoNodo->permessi = 1;
            fprintf(fp, "\n%d,%s,%s,%s,%s,%s,%s,%d", nuovoNodo->id, nuovoNodo->nome, nuovoNodo->cognome,
                    nuovoNodo->nick, nuovoNodo->email, nuovoNodo->dataNascita, nuovoNodo->password,
                    nuovoNodo->permessi);
        }

        fclose(fp);

        //aggiornamento dei collegamenti
        if (prec == NULL) {
            nuovoNodo->nextUtente = testa;
            testa = nuovoNodo;
        } else {
            prec->nextUtente = nuovoNodo;
            nuovoNodo->nextUtente = curr;
        }

        clearConsole();
        titolo();
        printColor("Registrazione avvenuta con successo.\n", COLOR_GREEN);
        printf("Benvenuto/a %s.\n", nuovoNodo->nome);
        pausa();

    }
}

/**
 * Function: accesso
 * ----------------------------
 *   Permette di effettuare l'accesso al proprio profilo personale, precedentemente registrato
 *
 *   @param testa puntatore alla variabile di tipo Utenti, una lista contenente tutte gli utenti
 *   @param text testo inserito dall'utente per fare l'accesso (email o nickname)
 *
 *   @return  se esiste utente con email o nickname uguale al valore del secondo argomento
 *            (char *text) e la password inserita corrisponde la funzione lo ritornerà,
 *            altrimenti il valore sarà uguale a NULL
 */
Utente *accesso(Utente *testa, char *text) {
    bool utenteTrovato = false;
    Utente *utente = NULL;
    Utente *temp = NULL;

    char pass[33] = "";
    readPassword("Password: ", pass, false);

    for (temp = testa; temp != NULL; temp = temp->nextUtente) {
        if ((strcmp(temp->email, text) == 0 || strcmp(temp->nick, text) == 0) && strcmp(temp->password, pass) == 0) {
            utente = temp;
            utenteTrovato = true;
            break;
        }
    }

    if (!utenteTrovato) {
        printColor("\nEmail/Nickname e/o Password errati!\n\n", COLOR_RED);
        pausa();
        clearConsole();
        titolo();
    }

    if (utenteTrovato)
        return utente;
    else
        return NULL;
}

/**
 * Function: ricercaUtente
 * ----------------------------
 *   Ricerca l'utente con un determinato id
 *
 *   @param testa puntatore alla variabile di tipo Utenti, una lista contenente tutte gli utenti
 *   @param id id dell'utente da ricercare
 *
 *   @return Utente con id corrispondende al parametro id, altrimenti NULL
 */
Utente *ricercaUtente(Utente *testa, int id) {
    bool flag = false;
    Utente *nuovoNodo = NULL;

    for (Utente *temp = testa; temp != NULL; temp = temp->nextUtente) {
        if (temp->id == id) {
            nuovoNodo = temp;
            flag = true;
            break;
        }
    }

    if (!flag) {
        printf("\n----------\n");
        printColor("Attenzione!\n", COLOR_RED);
        printf("Utente non trovato!\n");
        printf("----------\n\n");
    }

    return nuovoNodo;
}

/**
 * Function: ricercaUtente
 * ----------------------------
 *   Permette di stampare i dati personali di un determinato utente
 *
 *   @param utente utente da stampare nel dettaglio
 */
void stampaUtente(Utente *utente) {

    printColor("Elenco dati personali\n", COLOR_CYAN);
    printf("Id: %d\n", utente->id);
    printf("Nome: %s\n", utente->nome);
    printf("Cognome: %s\n", utente->cognome);
    printf("Nickname: %s\n", utente->nick);
    printf("Email: %s\n", utente->email);
    printf("Data di nascita: %s\n", utente->dataNascita);

    if (utente->permessi == 1) {
        printf("Permessi: utente base\n");
    } else {
        printf("Permessi: direttore\n");
    }

    printColor("-----------------------------\n", COLOR_CYAN);

}

/**
 * Function: modificaUtente
 * ----------------------------
 *   Permette di modificare i dati personali dell'utente una volta effettuato l'accesso al proprio profilo
 *
 *   @param utente utente da modificare
 *   @param testa puntatore alla variabile di tipo Utenti, una lista contenente tutte gli utenti
 */
//TODO: invertire
void modificaUtente(Utente *utente, Utente *testa) {
    int scelta, i;
    char risposta = '\0';

    char nome[20];
    char cognome[20];
    char email[60];
    char data[11];
    int giorno, mese = 0, anno = 0;
    bool dataCorretta = true; //flag per verificare la correttezza della data di nascita
    bool flag = false;
    bool continuaModifica = true;
    bool testInput = false;

    Utente *temp = NULL;
    Utente *temp2 = NULL;

    temp = utente;

    do {

        //elenco campi modificabili
        printf("Scegliere il campo da modificare\n");
        printf("----------\n");
        printf("1: Nome\n");
        printf("2: Cognome\n");
        printf("3: Email\n");
        printf("4: Password\n");
        printf("5: Data di nascita\n");
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
                clearConsole();
                titolo();

                do {
                    notificaAnnulla(false);
                    testInput = false;
                    printf("Inserisci il nuovo nome: ");
                    fgets(nome, 20, stdin);
                    nome[strlen(nome) - 1] = 0;
                    nome[0] = toupper(nome[0]);

                    if (strlen(nome) == 0 && testInput == false) {
                        continuaModifica = false;
                        break;
                    }

                    for (i = 0; i < strlen(nome); i++) {
                        if (isalpha(nome[i]) == 0 && nome[i] != ' ') {
                            testInput = true; //carattere non alfabetico
                        }
                    }

                    if (testInput) {
                        clearConsole();
                        titolo();
                        printf("\n----------");
                        printColor("\nAttenzione!\n", COLOR_RED);
                        printf("Nome non valido.\n");
                        printf("----------\n\n");
                    } else {
                        strcpy(temp->nome, nome);
                    }

                } while (testInput);

                break;

            case 2:
                clearConsole();
                titolo();
                do {
                    notificaAnnulla(false);
                    testInput = false;
                    printf("Inserisci il nuovo cognome: ");
                    fgets(cognome, 20, stdin);
                    cognome[strlen(cognome) - 1] = 0;
                    cognome[0] = toupper(cognome[0]);

                    if (strlen(cognome) == 0 && testInput == false) {
                        continuaModifica = false;
                        break;
                    }


                    for (i = 0; i < strlen(cognome); i++) {
                        if (isalpha(cognome[i]) == 0 && cognome[i] != ' ') {
                            testInput = true; //carattere non alfabetico
                        }
                    }

                    if (testInput) {
                        clearConsole();
                        titolo();
                        printf("\n----------");
                        printColor("\nAttenzione!\n", COLOR_RED);
                        printf("Cognome non valido.\n");
                        printf("----------\n\n");
                    } else {
                        strcpy(temp->cognome, cognome);
                    }
                } while (testInput);

                break;

            case 3:
                clearConsole();
                titolo();
                notificaAnnulla(false);

                do {
                    notificaAnnulla(false);
                    testInput = false;
                    flag = false;
                    printf("Inserisci Email (non ti dimenticare la @): \n");
                    fgets(email, 60, stdin);
                    email[strlen(email) - 1] = 0;

                    if (strlen(email) == 0 && testInput == false) {
                        continuaModifica = false;
                        break;
                    }

                    //verifico univocita'
                    for (temp2 = testa; temp2 != NULL; temp2 = temp2->nextUtente) {
                        if (strcmp(temp2->email, email) == 0) {
                            flag = true;
                            break;
                        }
                    }

                    if (flag) {
                        clearConsole();
                        printf("\n----------\n");
                        printColor("Attenzione!\n", COLOR_RED);
                        printColor("Email gia' in uso!\n", COLOR_RED);
                        printf("Si prega di sceglierne un'altra\n");
                        printf("----------\n\n");
                    } else {
                        strcpy(temp->email, email);
                    }

                } while (flag);

                //verifico che sia stata inserita la @
                char *ptr;
                char *a = "@";
                ptr = strstr(temp->email, a);

                while (ptr == NULL) {
                    clearConsole();
                    printColor("Attenzione! L'email inserita non e' corretta", COLOR_RED);

                    printf("Inserisci Email (non ti dimenticare la @): \n");
                    fgets(temp->email, 60, stdin);
                    temp->email[strlen(temp->email) - 1] = 0;
                    ptr = strstr(temp->email, a);
                }
                break;

            case 4:;
                clearConsole();
                titolo();

                char psw[32], psw2[32];

                do {
                    notificaAnnulla(false);
                    printf("\n");

                    readPassword("Inserisci la nuova password (minimo 6 caratteri): ", psw, false);

                    if (strlen(psw) == 0) {
                        continuaModifica = false;
                        break;
                    }

                    readPassword("Conferma password: ", psw2, true);

                    if (strcmp(psw, psw2) != 0) {
                        clearConsole();
                        printColor("\nAttenzione!\n", COLOR_RED);
                        printf("Le password non coincidono fra loro\n");
                        printf("Effettuare nuovamente l'inserimento\n\n");
                    } else {
                        strcpy(temp->password, psw);
                    }

                } while (strcmp(psw, psw2) != 0);

                break;

            case 5:
                clearConsole();
                titolo();

                notificaAnnulla(true);

                printf("Inserisci data di nascita\n");

                printColor("Attenzione!\n", COLOR_RED);
                printf("Per potersi registrare bisogna avere almeno 16 anni\n\n");

                do {
                    if (!dataCorretta) {
                        clearConsole();
                        printColor("\nAttenzione!\n", COLOR_RED);
                        printf("La data inserita non e' corretta.\nSi prega di inserirla nuovamente\n\n");
                    }

                    do {
                        printf("Giorno: ");
                        scanf("%d", &giorno);

                        if (giorno == 0) {
                            continuaModifica = false;
                            break;
                        }

                    } while (giorno < 1 || giorno > 31);

                    if (continuaModifica) {
                        do {
                            printf("Mese: ");
                            scanf("%d", &mese);
                        } while (mese < 1 || mese > 12);

                        do {
                            printf("Anno (dal 1900 in poi): ");
                            scanf("%d", &anno);
                        } while (anno < 1900);

                        dataCorretta = verificaData(giorno, mese, anno);
                    }

                } while (!dataCorretta);

                if (continuaModifica) {
                    snprintf(data, 11, "%d/%d/%d", giorno, mese, anno);
                    strcpy(temp->dataNascita, data);
                }

                while ('\n' != getchar());
                break;

            default:
                break;
        }

        if (scelta != 0 && continuaModifica) {
            do {
                printf("----------\n");
                printf("Vuoi modificare un altro campo? (s/n): ");
                risposta = getchar();
                while ('\n' != getchar());

                //rendo la risposta in maiuscolo per evitare errori
                risposta = toupper(risposta);

                if (risposta == 'N') {
                    scriviUtenti(testa);
                }

            } while (risposta != 'S' && risposta != 'N');
        }

        clearConsole();
        titolo();
    } while (risposta == 'S' && scelta != 0);
}

/**
 * Function: eliminaUtente
 * ----------------------------
 *   Permette di eliminare un utente
 *
 *   @param utente utente da stampare nel dettaglio
 *   @param testa puntatore alla variabile di tipo Utenti, una lista contenente tutte gli utenti
 */
//TODO: invertire
void eliminaUtente(Utente *utente, Utente *testa) {
    char risposta;
    Utente *curr, *prec;
    Utente *temp = NULL;

    temp = utente;
    prec = NULL;
    curr = testa;

    do {
        while ('\n' != getchar());
        printColor("ATTENZIONE!\n", COLOR_RED);
        printf("Sei sicuro/a di voler eliminare il tuo account?\n");
        printf("Per poter riaccedere dovrai creare un nuovo account\n");
        printf("Risposta (s/n): ");
        scanf("%c", &risposta);
        printf("\n");

        //rendo la risposta in maiuscolo per evitare errori
        risposta = toupper(risposta);

    } while (risposta != 'S' && risposta != 'N');

    clearConsole();
    titolo();

    if (risposta == 'S') {

        while (curr != NULL && temp->id != curr->id) {
            prec = curr;
            curr = curr->nextUtente;
        }

        if (temp->id == curr->id) {
            if (prec == NULL) { //elemento trovato in testa
                testa = curr->nextUtente;
            } else { //elemento al centro della lista
                prec->nextUtente = curr->nextUtente;
            }
            free(curr);
        }

        scriviUtenti(testa);
        printColor("Eliminazione completata con successo!\n", COLOR_GREEN);
        while ('\n' != getchar());
        pausa();
        clearConsole();
        titolo();
    } else {
        printColor("-----------------------------\n", COLOR_CYAN);
        printf("%s siamo contenti che tu abbia deciso di rimanere con noi!\n", temp->nome);
        printf("Se vuoi puoi riaccedere al tuo profilo facendo il login.\n");
        while ('\n' != getchar());
        pausa();
        clearConsole();
        titolo();
    }
}

/**
 * Function: scriviUtenti
 * ----------------------------
 *   Permette di salvare tutte le modifiche effettuate sul file "utenti.csv"
 *
 *   @param testa puntatore alla variabile di tipo Utenti, una lista contenente tutte gli utenti
 */
void scriviUtenti(Utente *testa) {
    Utente *temp = NULL;

    FILE *fp;
    fp = fopen("utenti.csv", "w"); //apertura file

    for (temp = testa; temp != NULL; temp = temp->nextUtente) {
        long size = ftell(fp);

        if (size == 0) { //file vuoto.
            fprintf(fp, "%d,%s,%s,%s,%s,%s,%s,%d", temp->id, temp->nome, temp->cognome, temp->nick, temp->email,
                    temp->dataNascita, temp->password, temp->permessi);
        } else { //file pieno
            fprintf(fp, "\n%d,%s,%s,%s,%s,%s,%s,%d", temp->id, temp->nome, temp->cognome, temp->nick, temp->email,
                    temp->dataNascita, temp->password, temp->permessi);
        }
    }

    fclose(fp);
}

/**
 * Function: eliminaUtente
 * ----------------------------
 *   Permette di modificare il permesso di un utente scelto
 *
 *   @param testa puntatore alla variabile di tipo Utenti, una lista contenente tutte gli utenti
 */
void modificaPermessi(Utente *testa) {
    char idScelto, sceltaPerm;
    char risposta = '\0';
    bool modifica = true;
    bool trovato = false;

    do {
        do {
            printColor("Elenco utenti.\n", COLOR_CYAN);
            for (Utente *temp = testa; temp != NULL; temp = temp->nextUtente) {
                printf("Id: %d\n", temp->id);
                printf("Nominativo: %s %s\n", temp->nome, temp->cognome);
                if (temp->permessi == 1) {
                    printf("Permessi: Utente base\n");
                } else {
                    printf("Permessi: Direttore\n");
                }
                printf("----------\n");

            }

            notificaAnnulla(false);
            printf("Scegli l'id dell'utente al quale vuoi cambiare i permessi: \n");
            printf("-> ");
            scanf(" %c", &idScelto);
            idScelto = (int) idScelto - 48;

            clearConsole();
            titolo();

            printf("Che livello di permessi vuoi assegnargli? \n");
            printf("1: Utente base\n");
            printf("2: Direttore\n");
            printf("0: Torna indietro\n");
            printf("-> ");
            scanf(" %c", &sceltaPerm);
            while ('\n' != getchar());
            sceltaPerm = (int) sceltaPerm - 48;

            switch (sceltaPerm) {
                case 0:
                    modifica = false;
                    trovato = true;
                    break;

                case 1:
                    for (Utente *temp = testa; temp != NULL; temp = temp->nextUtente) {
                        if (temp->id == idScelto) {
                            trovato = true;
                            temp->permessi = 1;
                        }
                    }
                    break;

                case 2:
                    for (Utente *temp = testa; temp != NULL; temp = temp->nextUtente) {
                        if (temp->id == idScelto) {
                            trovato = true;
                            temp->permessi = 2;
                        }
                    }
                    break;

                default:
                    break;
            }

            if (!trovato) {
                clearConsole();
                titolo();
                printf("\n----------\n");
                printColor("Attenzione!\n", COLOR_RED);
                printf("Nessun utente trovato con questo id.\n");
                printf("Scegliere un nuovo utente.\n");
                printf("----------\n\n");
                pausa();
            }
            clearConsole();
            titolo();
        } while (!trovato && modifica);

        if (modifica) {
            do {
                printf("----------\n");
                printf("Vuoi modificare altri permessi? (s/n): ");
                risposta = getchar();

                //rendo la risposta in maiuscolo per evitare errori
                risposta = toupper(risposta);

                if (risposta == 'N') {
                    scriviUtenti(testa);
                }
            } while (risposta != 'S' && risposta != 'N');
        }
    } while (risposta == 'S' && modifica);
}
