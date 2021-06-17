#define COLOR_GREEN 10
#define COLOR_CYAN  11
#define COLOR_RED   12
#define COLOR_RESET 15

#ifdef _WIN32

    #include <windows.h>

#else //UNIX

    #include <unistd.h>

    #define ANSI_COLOR_GREEN   "\x1b[92m"
    #define ANSI_COLOR_CYAN    "\x1b[96m"
    #define ANSI_COLOR_RED     "\x1b[91m"
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
