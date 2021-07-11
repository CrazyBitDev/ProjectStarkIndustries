Utente *letturaUtenti(FILE *fp);

void registrazioneUtente(Utente *testa);

Utente *accesso(Utente *testa, char *text);

Utente *ricercaUtente(Utente *testa, int id);

void stampaUtente(Utente *testa);

void scriviUtenti(Utente *testa);

void modificaUtente(Utente *utenteLogin, Utente *testa);

void eliminaUtente(Utente *utenteLogin, Utente *testa);

#include "utente.c"
