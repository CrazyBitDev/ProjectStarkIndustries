//Gestione Mostre
#define ID 1
#define BUFFER_SIZE 1024
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"

//Definizione struct mostre
struct mostre {
    int id;
    char citta[20];
    char indirizzo[30];
    char dataInizio[10];
    char dataFine[10];
    int nOpere; // Numero opere
    struct mostre *nextMostra; //puntatore al prossimo nodo
}mostre;

struct mostre* aggiungiMostra(struct mostre* testa){
    
}

