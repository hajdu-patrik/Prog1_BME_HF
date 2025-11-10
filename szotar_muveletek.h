// Hajdú Patrik Zsolt – RP329D – utolsó frissítés dátuma: 2024.11.19
#ifndef SZOTAR_MUVELETEK_H_INCLUDED
#define SZOTAR_MUVELETEK_H_INCLUDED

#include <stdbool.h>

// Felsorolja a megadott szótár összes szópárját ezt a "Fileba_Listaz" paraméter függésében vagy egy fájlba vagy a konzolra irja.
void Ki_Listazo(Lista *Fo_Lista, int Melyik_Szotar, bool Fileba_Listaz, const char *File_Neve);

// Hozzá add egy új szó párt a választott szótárhoz feltéve, hogy a szótár nem érte el a maximális kapacitását. (ez 1000 szópár)
void Uj_Szo_Add(Lista *Fo_Lista, int Melyik_Szotar, const char *Szo_Nyelv1, const char *Szo_Nyelv2);

// Egy választott szót/szópárt lehet vele módosítani a szótárban.
void Szopar_Javito(Lista *Fo_Lista, int Melyik_Szotar, int Hanyadik_Szopar);

// Megadott szótár egy adott szópárját törli.
void Szopar_Torlo(Lista *Fo_Lista, int Melyik_Szotar, char Melyiket_Torol);

#endif