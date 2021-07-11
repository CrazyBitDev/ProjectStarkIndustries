Opera *letturaOpere(FILE *fp);

void aggiungiOpera(Opera *testa);

void modificaOpera(Opera *testa, Opera *opera);

void eliminaOpera(Opera *testa, Opera *opera);

void scriviOpere(Opera *testa);

void stampaOpere(Opera *testa);

void stampaOpera(Opera *opera);

Opera *ricercaOpera(Opera *testa, int id);

Opera *browserOpere(FILE *fp, Opera *testa, bool selezione);

#include "opera.c"
