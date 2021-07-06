struct mostre *aggiungiMostra(struct mostre *testa);

struct mostre *modificaMostra(struct mostre *testa, struct mostre *mostra);

struct mostre *eliminaMostra(struct mostre *testa, struct mostre *mostra);

void scriviMostre(struct mostre *testa);

void stampaMostre(struct mostre *testa);

struct mostre *ricercaMostra(struct mostre *testa, int id);

typedef struct mostre Mostre;

#include "mostra.c"
