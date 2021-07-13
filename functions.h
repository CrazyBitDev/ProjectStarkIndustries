void printColor(char text[], int color);

void consoleColor(int color);

void readPassword(char prompt[], char *password, bool checkLunghezza);

void clearConsole(void);

bool verificaData(int giorno, int mese, int anno);

bool annoBisestile(int anno);

int letturaUltimoID(char *file);

int contaRighe(char *file);

void titolo(void);

int differenzaDate(int giorno1, int mese1, int anno1, int giorno2, int mese2, int anno2);

int differenzaDateOggi(int giorno, int mese, int anno);

int differenzaDateOggiChar(char *dataTarget);

bool verificaDataCorrente(int giorno, int mese, int anno);

bool dataInIntervallo(int giorno, int mese, int anno, char *giorno1, char *giorno2);

void notificaAnnulla(void);

void pausa(void);

void toUppercase(char *stringa);
/*
uint32_t leftrotate(uint32_t x, uint32_t c);

char *md5(char *initial_msg);
*/

#include "functions.c"
