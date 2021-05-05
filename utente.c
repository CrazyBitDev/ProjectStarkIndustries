//Gestione Utente

//Definizione della struct Utente
struct utente {
    int id;
    char nome[20];
    char cognome[20];
    char email[60];
    char dataNascita[10]; //gg/mm/aaaa
    char telefono[10];
    int permessi; //livello 1 = utente normale; livello 2 = direttore generale, ha accesso a tutto;
    struct utente *nextUtente; //puntatore al prossimo nodo
}utente;

