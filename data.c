//Definizione della struct Utente
typedef struct utente Utente;
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

//Definizione struct opera
typedef struct opera Opera;
struct opera {
    int id;
    char nome[30];
    char autore[30];
    char tipo[30];
    char genere[30];
    char periodo[20];
    int anno;
    Opera *nextOpera; //puntatore al prossimo nodo
};

//Definizione struct opera
typedef struct mostraOpera MostraOpera;
struct mostraOpera {
    Opera *opera;
    MostraOpera *nextOpera; //puntatore al prossimo nodo
};

//Definizione struct mostre
typedef struct mostra Mostra;
struct mostra {
    int id;
    char responsabile[30];
    char luogo[25];
    char citta[20];
    char indirizzo[30];
    char dataInizio[11];
    char dataFine[11];
    MostraOpera *opere;
    Mostra *nextMostra; //puntatore al prossimo nodo
};

//Definizione struct prenotazioni - da modificare
typedef struct prenotazione Prenotazione;
struct prenotazione {
    int id;
    Utente *utente;
    Mostra *mostra;
    char data[11];
    char ora[6];
    Prenotazione *nextPrenotazione;
};
