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

void printColor(char text[], int color) {
    #ifdef _WIN32
        HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
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

void consoleColor(int color) {
    #ifdef _WIN32
        HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
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

/*
void readPassword() {
    char password[20] = "";
    readPassword("TEST: ", password);
    printf("%s", password);
}
*/
void readPassword(char prompt[], char *password) {
    #ifdef _WIN32
        HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
        DWORD mode = 0;
        GetConsoleMode(hStdin, &mode);
        SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));
        printf("%s", prompt);
        scanf("%s",password);
        printf("\n");
        SetConsoleMode(hStdin, mode);
    #else
        char *tempPassword="";
        tempPassword = getpass(prompt);
        strcpy(password, tempPassword);
    #endif
}

bool verificaData(int giorno, int mese, int anno) {
    int etaMinima;
    
    bool annoBis = false; //flag anno bisestile
    bool dataCorretta = false; //flag per verificare la correttezza della data di nascita
    
    
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
    if(anno > etaMinima || dataCorretta == false) {
        dataCorretta = false;
    } else {
        dataCorretta = true;
    }
    
    return dataCorretta;
}
