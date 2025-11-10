// Hajdú Patrik Zsolt – RP329D – utolsó frissítés dátuma: 2024.11.19
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "struktura.h"
#include "lista_muveletek.h"
#include "debugmalloc.h"

// Törli a konzolt, működik Windows-on és Linux-on is.
void Konzol_Torles() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// ASCII karakterekkel kiírja meg a „Szótár” feliratot.
void Szotar_Felirat() {
    printf("\n\n\t ____      __  _    __    \n");
    printf("\t/ ___|____/_/ | |_ /_/\\_ _ __\n");
    printf("\t\\___ \\_  / _ \\| __/ _ | '__|\n");
    printf("\t ___) / /(_) | ||(_| | |   \n");
    printf("\t|____/___\\___/ \\__\\__,_|_|   \n\n\n");
}

// Egymás után végrehajtja rendre a Konzol_Torles()-t és a Szotar_Felirat()-t.
void Torol_Szotar_Felirat() {
    Konzol_Torles();
    Szotar_Felirat();
}

// Kiírja a kapott szöveget és vár egy billentyűleütésre, ami kiüríti a bemeneti buffert és a konzolt.
void Tovabb_Gombra(const char *Szoveg_Ki_Ir) {
    printf("\n%s", Szoveg_Ki_Ir);
    int c;
    while((c = getchar()) != '\n' && c != EOF) {
        // Ezzel ürítjük ki a bemeneti buffert a sor végéig
    }
    Konzol_Torles();
}

// Kiírja a főmenü pontjait.
void Menu_Opciok() {
    printf("\t[0] - Elerheto szotarak\n");
    printf("\t[1] - Uj szotar letrehozasa\n");
    printf("\t[2] - Meglevo szotar torlese\n");
    printf("\t[3] - Szotar fajlbol olvasasa\n");
    printf("\t[4] - Keresett szo megfeleloinek kiirasa\n");
    printf("\t[5] - Kilepes\n\n");
    printf("\tValassz egy menu pontot [0-5]: ");
}

// Kiírja a szótár menü pontjait.
void Szotar_Opciok() {
    printf("\t[0] - Szoparok ki listazasa\n");
    printf("\t[1] - Szoparok fajlba irasa\n");
    printf("\t[2] - Uj szopar felvetele\n");
    printf("\t[3] - Valasztott szopar javitasa\n");
    printf("\t[4] - Valasztott szopar torlese\n");
    printf("\t[5] - QUIZ\n");
    printf("\t[6] - Kilepes\n\n");
    printf("\tValassz egy menu pontot [0-6]: ");
}

// Kiír egy kérdést, majd beolvassa a választ és ellenőrzi nincs-e benne szám. Ha van benne szám hiba üzenetet ír ki.
void Szoveg_Beolvas(const bool Kerdes_Kell_E, const char *Kerdes, char *Be_Szoveg, const int Spec_Esett, const char *Spec_Out, const bool Hiba_Kell_E, const char* Hiba) {
    bool Van_E_Szam = false;
    do {
        Van_E_Szam = false;
        if (Kerdes_Kell_E) {
            printf("\n\t%s", Kerdes);
        } else {
            if(Spec_Esett == 0) {
                printf("\n\t%s-nek mi a megfeleloje? ", Spec_Out);
            }
        }
        scanf("%s", Be_Szoveg);

        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
            // Ezzel ürítjük ki a bemeneti buffert a sor végéig
        }

        for (int i = 0; Be_Szoveg[i] != '\0'; i++) {
            if (isdigit(Be_Szoveg[i])) {
                Van_E_Szam = true;
                break;
            }
        }

        if (Van_E_Szam && Hiba_Kell_E) {
            Konzol_Torles();
            printf("\t>>> HIBA: %s <<<\n", Hiba);
            Szotar_Felirat();
        }
    } while (Van_E_Szam);
}

// Bekér egy számot egy adott intervallumban. Annak helyességét ellenőrzi. Ha benne van az intervallumban a választott szám, akkor visszaadja. Ha pedig nincs az intervallumban választott szám, akkor hiba üzenetet ír ki.
int Szam_Beker_Intervallumban(Lista *Fo_Lista, const int Also_Hatar, const int Felso_Hatar, const int Tipus, const bool Kell_E_Hiba_Uzenet, const char *Hiba_Uzenet) {
    int Valasztott_Int = -1;
    do {
        // 4 Típus lehetséges:
        switch (Tipus) {
            // Típus 0 => Egy szótár kiválasztása
            case 0: {
                L_Kiir(Fo_Lista);
                printf("\tValassza ki a szotart melynek tartalmaval tovabb dolgozna: ");
            } break;
                // Típus 1 => Szótár törlése
            case 1: {
                L_Kiir(Fo_Lista);
                printf("\tValassza ki a szotart melyet torolni kivan: ");
            } break;
                // Típus 2 => Egy szótárral való művelet kiválasztása
            case 2: {
                Szotar_Opciok();
            } break;
                // Típus 3 => Hányadik szótár be
            case 3: {
                printf("\n\tAdja meg a szerkesztendo szopar szamat: ");
            } break;
            default: {
            } break;
        }
        char Valasztott_Tomb[101];

        fgets(Valasztott_Tomb, sizeof(Valasztott_Tomb), stdin);
        Valasztott_Tomb[strlen(Valasztott_Tomb) - 1] = '\0';
        size_t Valasztott_Hossza = strlen(Valasztott_Tomb);

        if (Valasztott_Hossza == 1 && isdigit(Valasztott_Tomb[0])) {
            Valasztott_Int = Valasztott_Tomb[0] - '0';
            if (Valasztott_Int < Also_Hatar || Valasztott_Int > Felso_Hatar) {
                Valasztott_Int = -1;
            }
        } else {
            Valasztott_Int = -1;
        }

        if(Valasztott_Int == -1 && Kell_E_Hiba_Uzenet == true) {
            Konzol_Torles();
            printf("\t>>> HIBA: %s <<<\n", Hiba_Uzenet);
            Szotar_Felirat();
        }
    } while (Valasztott_Int == -1);

    return Valasztott_Int;
}

// Megnézi, hogy a megadott nevű szótár már szerepel-e a tárolt adatok között.
bool Van_E(Lista *Fo_Lista, char *File_Neve) {
    Lista *Akt = Fo_Lista;
    while (Akt != NULL) {
        // Dinamikusan allokálunk memóriát a Temp_File_Neve számára
        size_t nyelv1_len = strlen(Akt->szotar.nyelv1);
        size_t nyelv2_len = strlen(Akt->szotar.nyelv2);
        size_t Temp_File_Neve_len = nyelv1_len + 1 + nyelv2_len + 4 + 1; // nyelv1 + "_" + nyelv2 + ".txt" + '\0'
        char *Temp_File_Neve = (char *)malloc(Temp_File_Neve_len);

        strcpy(Temp_File_Neve, Akt->szotar.nyelv1);
        strcat(Temp_File_Neve, "_");
        strcat(Temp_File_Neve, Akt->szotar.nyelv2);
        strcat(Temp_File_Neve, ".txt");

        if (strcmp(Temp_File_Neve, File_Neve) == 0) {
            free(Temp_File_Neve); // Felszabadítjuk a memóriát mielőtt visszatérünk
            return true;
        }

        free(Temp_File_Neve); // Felszabadítjuk a memóriát minden iteráció végén
        Akt = Akt->kov;
    }
    return false;
}

// Megnézi, hogy a megadott nevű fájl megtalálható-e a számítógépen.
bool File_Megtalalhato_E(const char *File_Neve) {
    FILE *fp = fopen(File_Neve, "r");
    if (fp != NULL) {
        fclose(fp);
        return true;
    }
    return false;
}

// Egy megadott string-ről ellenőrzi, hogy tartalmazza-e a ".txt” kiterjesztést. Ez alapján vissza add egy Igaz vagy Hamis érétket.
char* Txt_Vizsgalo(char *Input_Nev) {
    char *Van_E_Txt = strstr(Input_Nev, ".txt");
    char *File_Neve;

    if (Van_E_Txt) {
        Van_E_Txt[4] = '\0';  // Levágja a ".txt" utáni karaktereket
        File_Neve = (char *) malloc(strlen(Input_Nev) + 1);

        if (File_Neve == NULL) {
            return NULL;
        }
        strcpy(File_Neve, Input_Nev);
    } else {
        File_Neve = (char *) malloc(strlen(Input_Nev) + 5);  // ".txt"-hez + 4 karakter + 1 a lezáró null

        if (File_Neve == NULL) {
            return NULL;
        }
        strcpy(File_Neve, Input_Nev);
        strcat(File_Neve, ".txt");
    }

    return File_Neve;
}