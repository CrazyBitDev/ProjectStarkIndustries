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
    scanf("%s", password);
    printf("\n");
    SetConsoleMode(hStdin, mode);
#else
    char *tempPassword="";
    tempPassword = getpass(prompt);
    strcpy(password, tempPassword);
#endif
}

void clearConsole() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

bool verificaData(int giorno, int mese, int anno) {
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

    return dataCorretta;
}

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

bool differenzaDate(int giorno1, int mese1, int anno1, int giorno2, int mese2, int anno2) {
    bool dateCorrette = false;

    if((giorno1 == giorno2) && (mese1 == mese2) && (anno1 == anno2))
    {
        //La mostra dura solo un giorno di conseguenza le date coincidono
        dateCorrette = true;
    }
    else if(anno1 < anno2 || (anno1 == anno2 && mese1 < mese2) || (anno1 == anno2 && mese1 == mese2 && giorno1 < giorno2))
    {
        //La data d'inizio precede quella di fine
        dateCorrette = true;
    }

    return dateCorrette;
}

void notificaAnnulla() {
    consoleColor(COLOR_RED);
    printf("\t\t\t|-----------------------------|\n");
    printf("\t\t\t|         Attenzione!         |\n");
    printf("\t\t\t|   Se hai sbagliato e vuoi   |\n");
    printf("\t\t\t|       tornare al menu'      |\n");
    printf("\t\t\t|   premere il tasto invio    |\n");
    printf("\t\t\t|-----------------------------|\n");
    consoleColor(COLOR_RESET);
}

void pausa() {
    printf("Premi INVIO per continuare\n");  
    getchar();
}
