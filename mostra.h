Mostra *letturaMostre(FILE *fp);

void aggiungiMostra(Mostra *testa);

void modificaMostra(Mostra *testa, Mostra *mostra);

void eliminaMostra(Mostra *testa, Mostra *mostra);

void scriviMostre(Mostra *testa);

void stampaMostre(Mostra *testa);

void stampaMostra(Mostra *mostra);

Mostra *ricercaMostra(Mostra *testa, int id);

Mostra *browserMostra(FILE *fp, Mostra *testa, bool selezione);

#include "mostra.c"
