struct mostre *aggiungiMostra(struct mostre *testa, struct utente *utenteLogin);

struct mostre *modificaMostra(struct mostre *testa, struct utente *utenteLogin);

struct mostre *eliminaMostra(struct mostre *testa, struct utente *utenteLogin);

void scriviMostre(struct mostre *testa);

void stampaMostre(struct mostre *testa);

//struct mostre *ordinamento(struct mostre *testa);

typedef struct mostre Mostre;

#include "mostra.c"
