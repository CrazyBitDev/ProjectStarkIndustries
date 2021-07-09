struct utente *registrazioneUtente(struct utente *testa);

struct utente *accesso(struct utente *testa, char *text);

void stampaUtente(struct utente *testa);

void scriviUtenti(struct utente *testa);

struct utente *modificaUtente(struct utente *utenteLogin, struct utente *testa);

struct utente *ordinamento(struct utente *testa);

struct utente *eliminaUtente(struct utente *utenteLogin, struct utente *testa);

typedef struct utente Utente;

#include "utente.c"
