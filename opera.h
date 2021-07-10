struct opera *aggiungiOpera(struct opera *testa);

struct opera *modificaOpera(struct opera *testa, struct opera *opera);

struct opera *eliminaOpera(struct opera *testa, struct opera *opera);

void scriviOpere(struct opera *testa);

void stampaOpere(struct opera *testa);

struct opera *ricercaOpera(struct opera *testa, int id);

typedef struct opera Opera;

#include "opera.c"
