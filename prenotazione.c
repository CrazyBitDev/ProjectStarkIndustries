struct prenotazione{
   char dataMostra[10];
   char oraInizio[5];
   char oraFine[5];
   char nome[20];
   char cognome[20];
   char email[60];
   struct prenotazione *nextPrenotazione;
}prenotazione;
