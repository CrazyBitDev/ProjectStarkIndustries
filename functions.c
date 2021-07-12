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
    char password[32] = "";
    readPassword("TEST: ", password, true);
    printf("%s", password);
}
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
            strcpy(password, /*md5(input)*/ input);
        #else
            char *input = getpass(prompt);
            strcpy(password, /*md5(input)*/ input);
        #endif
    } while (checkLunghezza && strlen(password) < 6 && strlen(password) != 0);
}

void clearConsole() {
    #ifdef _WIN32
        //system("cls");
    #else
       // system("clear");
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

//TODO: cambiare nome?
// 0 = giorni uguali, 1 = giorno 2 > giorno 1, -1 = giorno 1 > giorno 2
int differenzaDate(int giorno1, int mese1, int anno1, int giorno2, int mese2, int anno2) {

    int differenza = 0;

    if(anno1 < anno2 || (anno1 == anno2 && mese1 < mese2) || (anno1 == anno2 && mese1 == mese2 && giorno1 < giorno2)) {
        differenza = 1;
    } else if (anno1 != anno2 || mese1 != mese2 || giorno1 != giorno2) {
        differenza = -1;
    }

    return differenza;
}

int differenzaDateOggi(char *dataTarget) {

    char data[11];

    strcpy(data, dataTarget);

    struct tm *ts;
    char annoCorrente[5], meseCorrente[3], giornoCorrente[3];
    
    int dataConvertita[3];
    
    time_t now = time(NULL);
    
    ts = localtime(&now);
    strftime(annoCorrente,   sizeof(annoCorrente),   "%Y", ts);
    strftime(meseCorrente,   sizeof(meseCorrente),   "%m", ts);
    strftime(giornoCorrente, sizeof(giornoCorrente), "%d", ts);

    char *tok = strtok(data, "/");

    for (int i = 0; i < 3; i++ ) {
        dataConvertita[i] = atoi(tok);
        tok = strtok(NULL, "/");
    }

    return differenzaDate(atoi(giornoCorrente), atoi(meseCorrente), atoi(annoCorrente), dataConvertita[0], dataConvertita[1], dataConvertita[2]);
}

bool verificaDataCorrente(int giorno, int mese, int anno) {
    bool dataCorrente;
    
    time_t now;
    struct tm *ts;
    
    char giornoCorrente[3];
    char meseCorrente[3];
    char annoCorrente[5];
    int giornoCorr, meseCorr, annoCorr;
    
    //salvo data odierna
    now = time(NULL);
    ts = localtime(&now);
    
    strftime(annoCorrente, sizeof(annoCorrente), "%Y", ts);
    strftime(meseCorrente, sizeof(meseCorrente), "%m", ts);
    strftime(giornoCorrente, sizeof(giornoCorrente), "%d", ts);
    
    giornoCorr = atoi(giornoCorrente);
    meseCorr = atoi(meseCorrente);
    annoCorr = atoi(annoCorrente);
    
    if((giorno == giornoCorr) && (mese == meseCorr) && (anno == annoCorr)) {
        //le date coincidono
        dataCorrente = true;
    } else {
        if(anno < annoCorr || (anno == annoCorr && mese < meseCorr) || (anno == annoCorr && mese == meseCorr && giorno < giornoCorr)) {
            //La data di inizio mostra precede la data odierna
            dataCorrente = false;
        } else {
            //la data di inizio mostra e' successiva alla data odierna
            dataCorrente = true;
        }
    }
    
    return dataCorrente;
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

void toUppercase(char *stringa) {
    // Convert to upper case
    char *s = stringa;
    while (*s) {
        *s = toupper((unsigned char) *s);
        s++;
    }
}

/*
uint32_t leftrotate(uint32_t x, uint32_t c) {
    return (((x) << (c)) | ((x) >> (32 - (c))));
}
 
char *md5(char *initial_msg) {

    size_t initial_len = strlen(initial_msg);

    uint32_t h0, h1, h2, h3;
    
    uint8_t *p0, *p1, *p2, *p3;
    char *md5result = (char*)malloc(32 * sizeof(char));
 
    uint8_t *msg = NULL;
 
    uint32_t r[] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
                    5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,
                    4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
                    6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};

    uint32_t k[] = {
        0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
        0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
        0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
        0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
        0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
        0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
        0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
        0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
        0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
        0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
        0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
        0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
        0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
        0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
        0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
        0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};
 
    h0 = 0x67452301;
    h1 = 0xefcdab89;
    h2 = 0x98badcfe;
    h3 = 0x10325476;
 
    int new_len = ((((initial_len + 8) / 64) + 1) * 64) - 8;
 
    msg = calloc(new_len + 64, 1);
    
    memcpy(msg, initial_msg, initial_len);
    msg[initial_len] = 128;
 
    uint32_t bits_len = 8*initial_len;
    memcpy(msg + new_len, &bits_len, 4);
 
    for(int offset=0; offset<new_len; offset += (512/8)) {
 
        uint32_t *w = (uint32_t *) (msg + offset);
 
        uint32_t a = h0;
        uint32_t b = h1;
        uint32_t c = h2;
        uint32_t d = h3;
 
        uint32_t i;
        for(i = 0; i<64; i++) {
 
            uint32_t f, g;
 
             if (i < 16) {
                f = (b & c) | ((~b) & d);
                g = i;
            } else if (i < 32) {
                f = (d & b) | ((~d) & c);
                g = (5*i + 1) % 16;
            } else if (i < 48) {
                f = b ^ c ^ d;
                g = (3*i + 5) % 16;
            } else {
                f = c ^ (b | (~d));
                g = (7*i) % 16;
            }

            uint32_t temp = d;
            d = c;
            c = b;
            b = b + leftrotate((a + f + k[i] + w[g]), r[i]);
            a = temp;

        }
 
        h0 += a;
        h1 += b;
        h2 += c;
        h3 += d;
 
    }
     
    p0=(uint8_t *)&h0;
    p1=(uint8_t *)&h1;
    p2=(uint8_t *)&h2;
    p3=(uint8_t *)&h3;
    sprintf(md5result, "%2.2x%2.2x%2.2x%2.2x%2.2x%2.2x%2.2x%2.2x%2.2x%2.2x%2.2x%2.2x%2.2x%2.2x%2.2x%2.2x",
            p0[0], p0[1], p0[2], p0[3],
            p1[0], p1[1], p1[2], p1[3],
            p2[0], p2[1], p2[2], p2[3],
            p3[0], p3[1], p3[2], p3[3]);
    return md5result;
 
}*/
