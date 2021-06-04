struct utente *registrazione(struct utente *testa);
struct utente *accesso(struct utente *testa, char *email);
int letturaUltimoID(void);
int contaRighe(void);
void stampa(struct utente* testa);

typedef struct utente Utente;

#include "utente.c"
