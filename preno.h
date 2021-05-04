#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LUN 20
#define MAX 10

//struct prenotazione

struct data{
    int giorno;
    int ora;
    char Nome[LUN];
    char Cognome[LUN];
    char email[LUN];
    int telefono[MAX];
    int giornoMostra;
};
typedef struct data tdata;
