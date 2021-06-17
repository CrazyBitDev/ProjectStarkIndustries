struct utente *registrazioneUtente(struct utente *testa);

struct utente *accesso(struct utente *testa, char *email);

int letturaUltimoID(void);

int contaRighe(void);

void stampaUtente(struct utente *testa);

struct utente *modificaUtente(struct utente *utenteLogin);

struct utente *ordinamento(struct utente *testa);

struct utente *eliminaUtente(struct utente *utenteLogin);

typedef struct utente Utente;

#include "utente.c"
