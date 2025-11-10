// Hajdú Patrik Zsolt – RP329D – utolsó frissítés dátuma: 2024.11.19
#ifndef SEGED_H
#define SEGED_H

#include <stdbool.h>

// Törli a konzolt, működik Windows-on és Linux-on is.
void Konzol_Torles();

// ASCII karakterekkel kiírja meg a „Szótár” feliratot.
void Szotar_Felirat();

// Egymás után végrehajtja rendre a Konzol_Torles()-t és a Szotar_Felirat()-t.
void Torol_Szotar_Felirat();

// Kiírja a kapott szöveget és vár egy billentyűleütésre, ami kiüríti a bemeneti buffert és a konzolt.
void Tovabb_Gombra(const char *Szoveg_Ki_Ir);

// Kiírja a főmenü pontjait.
void Menu_Opciok();

// Kiírja a szótár menü pontjait.
void Szotar_Opciok();

// Kiír egy kérdést, majd beolvassa a választ és ellenőrzi nincs-e benne szám. Ha van benne szám hiba üzenetet ír ki.
void Szoveg_Beolvas(bool Kerdes_Kell_E, const char *Kerdes, char *Be_Szoveg, int Spec_Esett, const char *Spec_Out, bool Hiba_Kell_E, const char* Hiba);

// Bekér egy számot egy adott intervallumban. Annak helyességét ellenőrzi. Ha benne van az intervallumban a választott szám, akkor visszaadja. Ha pedig nincs az intervallumban választott szám, akkor hiba üzenetet ír ki.
int Szam_Beker_Intervallumban(Lista *Fo_Lista, int Also_Hatar, int Felso_Hatar, int Tipus, bool Kell_E_Hiba_Uzenet, const char *Hiba_Uzenet);

// Megnézi, hogy a megadott nevű szótár már szerepel-e a tárolt adatok között.
bool Van_E(Lista *Fo_Lista, char *File_Neve);

// Megnézi, hogy a megadott nevű fájl megtalálható-e a számítógépen.
bool File_Megtalalhato_E(const char *File_Neve);

// Egy megadott string-ről ellenőrzi, hogy tartalmazza-e a ".txt” kiterjesztést. Ez alapján vissza add egy Igaz vagy Hamis érétket.
char *Txt_Vizsgalo(char *Input_Nev);

#endif