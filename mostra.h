//Definizione struct mostraOpera
typedef struct mostraOpera MostraOpera;

//Definizione struct mostre
typedef struct mostra Mostra;

Mostra *letturaMostre(FILE *fp, FILE *fpMO, Opera *testaOpera);

void aggiungiMostra(Mostra *testa);

void aggiungiOperaAMostra(Mostra *testa, Mostra *mostra, Opera *opera);

void modificaMostra(Mostra *testa, Mostra *mostra);

void eliminaMostra(Mostra *testa, Mostra *mostra);

void eliminaOperaAMostra(Mostra *testa, Mostra *mostra, int idOpera);

void scriviMostre(Mostra *testa);

void stampaMostre(Mostra *testa);

void stampaMostra(Mostra *mostra, bool stampaOpere);

Mostra *ricercaMostra(Mostra *testa, int id);

Mostra *browserMostra(FILE *fp, Mostra *testa, bool selezione);

#include "mostra.c"