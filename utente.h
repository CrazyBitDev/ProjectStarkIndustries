void *registrazioneUtente(Utente *testa);

Utente *accesso(Utente *testa, char *text);

void stampaUtente(Utente *testa);

void scriviUtenti(Utente *testa);

void *modificaUtente(Utente *utenteLogin, Utente *testa);

//TODO: Inutile, si puo' togliere?
//Utente *ordinamento(Utente *testa);

void *eliminaUtente(Utente *utenteLogin, Utente *testa);

#include "utente.c"
