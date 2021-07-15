#define COLOR_GREEN   10
#define COLOR_CYAN    11
#define COLOR_RED     12
#define COLOR_MAGENTA 13
#define COLOR_RESET   15

#ifdef _WIN32

    #include <windows.h>

#else //UNIX

    #include <unistd.h>

    #define ANSI_COLOR_GREEN   "\x1b[92m"
    #define ANSI_COLOR_CYAN    "\x1b[96m"
    #define ANSI_COLOR_RED     "\x1b[91m"
    #define ANSI_COLOR_MAGENTA "\x1b[95m"
    #define ANSI_COLOR_RESET   "\x1b[0m"

#endif

/**
 * Function: printColor
 * ----------------------------
 *   Stampa in console del testo con un determinato colore
 *
 *   @param text testo da visualizzare in console
 *   @param color codice del colore da utilizzare. È possibile usare le constanti COLOR_*
 */
void printColor(char text[], int color) {
    #ifdef _WIN32
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, color);
    #else
        switch (color) {
            case COLOR_GREEN:
                printf(ANSI_COLOR_GREEN);
                break;
            case COLOR_CYAN:
                printf(ANSI_COLOR_CYAN);
                break;
            case COLOR_RED:
                printf(ANSI_COLOR_RED);
                break;
            case COLOR_MAGENTA:
                printf(ANSI_COLOR_MAGENTA);
                break;
            case COLOR_RESET:
                printf(ANSI_COLOR_RESET);
                break;
            default:
                break;
        }
    #endif

    printf("%s", text);

    #ifdef _WIN32
        SetConsoleTextAttribute(hConsole, 15);
    #else
        printf(ANSI_COLOR_RESET);
    #endif
}

/**
 * Function: consoleColor
 * ----------------------------
 *   Cambia il colore alla console
 *
 *   @param color codice del colore da utilizzare. È possibile usare le constanti COLOR_*
 */
void consoleColor(int color) {
    #ifdef _WIN32
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, color);
    #else
        switch (color) {
            case COLOR_GREEN:
                printf(ANSI_COLOR_GREEN);
                break;
            case COLOR_CYAN:
                printf(ANSI_COLOR_CYAN);
                break;
            case COLOR_RED:
                printf(ANSI_COLOR_RED);
                break;
            case COLOR_MAGENTA:
                printf(ANSI_COLOR_MAGENTA);
                break;
            case COLOR_RESET:
                printf(ANSI_COLOR_RESET);
                break;
            default:
                break;
        }
    #endif
}

/**
 * Function: consoleColor
 * ----------------------------
 *   Permette all'utente di inserire del testo in console senza che venga visualizzato.
 *   Utile ed utilizzato nell'inserimento di password.
 *
 *   @param prompt testo da visualizzare prima dell'input
 *   @param password puntatore all'array di char utilizzato per memorizzare l'input
 *   @param checkLunghezza abilita il checkLunghezza, utile nell'input al momento della registrazione. Input lunghi meno di 6 caratteri richiederanno il reinserimento fino a condizione non superata
 */
void readPassword(char prompt[], char *password, bool checkLunghezza) {
    do {
        #ifdef _WIN32
            char input[32] = "";
            HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
            DWORD mode = 0;
            GetConsoleMode(hStdin, &mode);
            SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));
            printf("%s", prompt);
            scanf("%s", input);
            printf("\n");
            SetConsoleMode(hStdin, mode);
            strcpy(password, input);
        #else
            char *input = getpass(prompt);
            strcpy(password, input);
        #endif
    } while (checkLunghezza && strlen(password) < 6 && strlen(password) != 0);
}

/**
 * Function: clearConsole
 * ----------------------------
 *   Pulisce la console completamente o solo parzialmente (solo la zona visualizzata)
 */
void clearConsole() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

/**
 * Function: verificaData
 * ----------------------------
 *   Controlla che la data sia corretta
 *
 *   @param giorno giorno (numerico) della data da verificare
 *   @param mese mese (numerico) della data da verificare
 *   @param anno anno (numerico) della data da verificare
 * 
 *   @return dataCorretta, booleano, true se i campi rispettano i criteri e la data è reale, altrimenti false
 */
bool verificaData(int giorno, int mese, int anno) {
    bool dataCorretta = false; //flag per verificare la correttezza della data di nascita

    //controllo se l'anno inserito è bisestile o meno
    bool annoBis = annoBisestile(anno);

    //controllo la correttezza di tutta la data inserita
    if ((giorno > 28 && mese == 2 && !annoBis) || (giorno > 29 && mese == 2 && annoBis)) {
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

    return dataCorretta;
}

/**
 * Function: annoBisestile
 * ----------------------------
 *   Controlla che l'anno passato come argomento sia bisestile o meno
 *
 *   @param anno anno (numerico)
 * 
 *   @return annoBis, booleano, true se l'anno passato come argomento è bisestile, altrimenti false
 */
bool annoBisestile(int anno) {
    bool annoBis = false;
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
    return annoBis;
}

/**
 * Function: letturaUltimoID
 * ----------------------------
 *   Verifica qual'è l'ultimo ID inserito
 *
 *   @param file puntatore ad un array di char contenente il nome del file da controllare
 * 
 *   @return ultimo id presente nel file
 */
int letturaUltimoID(char *file) {
    FILE *fp = NULL;

    fp = fopen(file, "r"); //apertura file

    int totRighe = 0;
    int ultimoID = 0;
    char buf[BUFFER_SIZE];
    char *res;

    totRighe = contaRighe(file);

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

/**
 * Function: contaRighe
 * ----------------------------
 *   Conta le righe in un determinato file
 *
 *   @param file puntatore ad un array di char contenente il nome del file da controllare
 * 
 *   @return numero di righe del file
 */
int contaRighe(char *file) {
    FILE *fp = NULL;
    fp = fopen(file, "r"); //apertura file

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

/**
 * Function: titolo
 * ----------------------------
 *   Stampa a video il titolo del software
 */
void titolo() {
    printf("\n");
    consoleColor(COLOR_CYAN);
    printf("   _____ __             __      ____          __           __       _          \n");
    printf("  / ___// /_____ ______/ /__   /  _/___  ____/ /_  _______/ /______(_)__  _____\n");
    printf("  \\__ \\/ __/ __ `/ ___/ //_/   / // __ \\/ __  / / / / ___/ __/ ___/ / _ \\/ ___/\n");
    printf(" ___/ / /_/ /_/ / /  / ,<    _/ // / / / /_/ / /_/ (__  ) /_/ /  / /  __(__  ) \n");
    printf("/____/\\__/\\__,_/_/  /_/|_|  /___/_/ /_/\\__,_/\\__,_/____/\\__/_/  /_/\\___/____/  \n");
    consoleColor(COLOR_RESET);
    printf("\n");
}

/**
 * Function: differenzaDate
 * ----------------------------
 *   Effettua un controllo tra le due date passate come argomento per verificare se coincidono o quale delle due è successiva all'altra
 *
 *   @param giorno1 intero, giorno della prima data
 *   @param mese1 intero, mese della prima data
 *   @param anno1 intero, anno della prima data
 *   @param giorno2 intero, giorno della seconda data
 *   @param mese2 intero, mese della seconda data
 *   @param anno2 intero, anno della seconda data
 * 
 *   @return 0 se le date sono uguali, 1 se la seconda data è successivo alla prima, -1 se la prima data è successivo alla seconda
 */
int differenzaDate(int giorno1, int mese1, int anno1, int giorno2, int mese2, int anno2) {

    int differenza = 0;

    if (anno1 < anno2 || (anno1 == anno2 && mese1 < mese2) || (anno1 == anno2 && mese1 == mese2 && giorno1 < giorno2)) {
        differenza = 1;
    } else if (anno1 != anno2 || mese1 != mese2 || giorno1 != giorno2) {
        differenza = -1;
    }

    return differenza;
}



/**
 * Function: differenzaDateChar
 * ----------------------------
 *   Effettua un controllo tra le due date passate come argomento per verificare se coincidono o quale delle due è successiva all'altra.
 *   Effettua una conversione degli array di char e successivamente richiama differenzaDate()
 *
 *   @param data1 puntatore ad un array di char contenente la prima data, formato gg/mm/aaaa
 *   @param data2 puntatore ad un array di char contenente la seconda data, formato gg/mm/aaaa
 * 
 *   @return 0 se le date sono uguali, 1 se la seconda data è successivo alla prima, -1 se la prima data è successivo alla seconda
 */
int differenzaDateChar(char *data1, char *data2) {
    char dataTemp1[11], dataTemp2[11];

    strcpy(dataTemp1, data1);
    strcpy(dataTemp2, data2);

    int data1Convertita[3], data2Convertita[3];

    char *tok1 = strtok(dataTemp1, "/");
    char *tok2 = strtok(dataTemp2, "/");
    for (int i = 0; i < 3; i++) {
        data1Convertita[i] = atoi(tok1);
        data2Convertita[i] = atoi(tok2);
        tok1 = strtok(NULL, "/");
        tok2 = strtok(NULL, "/");
    }

    return differenzaDate(data1Convertita[0], data1Convertita[1], data1Convertita[2], data2Convertita[0],
                          data2Convertita[1], data2Convertita[2]);
}

/**
 * Function: differenzaDateOggi
 * ----------------------------
 *   Effettua un controllo tra la data passata come argomento e la data del giorno corrente per verificare se coincidono o quale delle due è successiva all'altra
 *   Dopo aver ricavato il giorno corrente, richiama differenzaDate()
 *
 *   @param giorno intero, giorno della data
 *   @param mese intero, mese della data
 *   @param anno intero, anno della data
 * 
 *   @return 0 se le date sono uguali, 1 se la seconda data è successivo al giorno corrente, -1 se è precedente al giorno corrente
 */
int differenzaDateOggi(int giorno, int mese, int anno) {
    struct tm *ts;
    char annoCorrente[5], meseCorrente[3], giornoCorrente[3];

    time_t now = time(NULL);

    ts = localtime(&now);
    strftime(annoCorrente, sizeof(annoCorrente), "%Y", ts);
    strftime(meseCorrente, sizeof(meseCorrente), "%m", ts);
    strftime(giornoCorrente, sizeof(giornoCorrente), "%d", ts);

    return differenzaDate(atoi(giornoCorrente), atoi(meseCorrente), atoi(annoCorrente), giorno, mese, anno);
}

/**
 * Function: differenzaDateOggiChar
 * ----------------------------
 *   Effettua un controllo tra la data passata come argomento e la data del giorno corrente per verificare se coincidono o quale delle due è successiva all'altra
 *   Effettua una conversione degli array e successivamente richiama differenzaDateOggi()
 *
 *   @param dataTarget puntatore all'array di char contenente la data da controllare, formato gg/mm/aaaa
 * 
 *   @return 0 se le date sono uguali, 1 se la seconda data è successivo al giorno corrente, -1 se è precedente al giorno corrente
 */
int differenzaDateOggiChar(char *dataTarget) {

    char data[11];

    strcpy(data, dataTarget);

    int dataConvertita[3];

    char *tok = strtok(data, "/");

    for (int i = 0; i < 3; i++) {
        dataConvertita[i] = atoi(tok);
        tok = strtok(NULL, "/");
    }

    return differenzaDateOggi(dataConvertita[0], dataConvertita[1], dataConvertita[2]);
}

/**
 * Function: dataInIntervallo
 * ----------------------------
 *   Effettua un controllo tra la date passate come argomento, verifica che la prima data (valori passati singolarmente) è inclusa in un intervallo dato dalla seconda e terza data (puntatore all'array di char)
 *   Effettua una conversione degli array e successivamente richiama verificaData() e differenzaDate()
 *
 *   @param giorno intero, giorno della prima data
 *   @param mese intero, mese della prima data
 *   @param anno intero, anno della prima data
 *   @param giorno1 puntatore all'array di char contenente la seconda data (estremo sinistro dell'intervallo), formato gg/mm/aaaa
 *   @param giorno2 puntatore all'array di char contenente la terza data (estremo destro dell'intervallo), formato gg/mm/aaaa
 * 
 *   @return true se da prima data è inclusa nell'intervallo generato dalla seconda e terza data, altrimenti false
 */
bool dataInIntervallo(int giorno, int mese, int anno, char *giorno1, char *giorno2) {
    bool inIntervallo = false;
    int giorno1conv[3], giorno2conv[3];
    char giorno1temp[11], giorno2temp[11];

    strcpy(giorno1temp, giorno1);
    strcpy(giorno2temp, giorno2);

    char *tok = strtok(giorno1temp, "/");

    for (int i = 0; i < 3; i++) {
        giorno1conv[i] = atoi(tok);
        tok = strtok(NULL, "/");
    }

    tok = strtok(giorno2temp, "/");

    for (int i = 0; i < 3; i++) {
        giorno2conv[i] = atoi(tok);
        tok = strtok(NULL, "/");
    }
    if (verificaData(giorno, mese, anno) && verificaData(giorno1conv[0], giorno1conv[1], giorno1conv[2]) &&
        verificaData(giorno2conv[0], giorno2conv[1], giorno2conv[2])) {
        if (differenzaDate(giorno, mese, anno, giorno1conv[0], giorno1conv[1], giorno1conv[2]) <= 0 &&
            differenzaDate(giorno, mese, anno, giorno2conv[0], giorno2conv[1], giorno2conv[2]) >= 0) {
            inIntervallo = true;
        }
    }
    printf("data in intervallo: %d\n", inIntervallo);
    return inIntervallo;
}

/**
 * Function: notificaAnnulla
 * ----------------------------
 *   Stampa a video un avviso per l'utente
 * 
 *   @param tastoNum true se l'utente deve premere il tasto 0, altrimenti tasto INVIO
 */
void notificaAnnulla(bool tastoNum) {
    consoleColor(COLOR_RED);
    printf("\t\t\t|-----------------------------|\n");
    printf("\t\t\t|         Attenzione!         |\n");
    printf("\t\t\t|   Se hai sbagliato e vuoi   |\n");
    printf("\t\t\t|       tornare al menu'      |\n");
    if (tastoNum) {
        printf("\t\t\t|      premere il tasto 0     |\n");
    } else {
        printf("\t\t\t|   premere il tasto INVIO    |\n");
    }
    printf("\t\t\t|-----------------------------|\n");
    consoleColor(COLOR_RESET);
}

/**
 * Function: pausa
 * ----------------------------
 *   Stampa una stringa e attende che l'utente prema INVIO per continuare con l'esecuzione del software
 */
void pausa() {
    printf("Premi INVIO per continuare\n");
    getchar();
}

/**
 * Function: toUppercase
 * ----------------------------
 *   Data una stringa, tutti i caratteri diventano maiuscoli
 *
 *   @param stringa puntatore all'array di char contenete la stringa che diventerà tutta maiuscola
 */
void toUppercase(char *stringa) {
    char *s = stringa;
    while (*s) {
        *s = toupper((unsigned char) *s);
        s++;
    }
}