// Hajdú Patrik Zsolt – RP329D – utolsó frissítés dátuma: 2024.11.19
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "struktura.h"
#include "seged.h"
#include "lista_muveletek.h"
#include "debugmalloc.h"

// Felsorolja a megadott szótár összes szópárját ezt a "Fileba_Listaz" paraméter függésében vagy egy fájlba vagy a konzolra irja.
void Ki_Listazo(Lista *Fo_Lista, int Melyik_Szotar, bool Fileba_Listaz, const char *File_Neve) {
    Lista *i = NULL;
    i = Lista_Lepteto(Fo_Lista, Melyik_Szotar);

    if(i == NULL) {
        return;
    }

    if(Fileba_Listaz) {
        if(i->szotar.szoparok_szama != 0) {
            FILE *Ki_File = fopen(File_Neve, "w");

            if(!Ki_File) {
                return;
            }

            fprintf(Ki_File, "%s;%s", i->szotar.nyelv1, i->szotar.nyelv2);
            for(int j = 0; j < i->szotar.szoparok_szama; j++) {
                fprintf(Ki_File, ";%s,%s", i->szotar.szoparok_tomb[0][j], i->szotar.szoparok_tomb[1][j]);
            }
            fclose(Ki_File);
            Torol_Szotar_Felirat();
            Tovabb_Gombra("\tSIKER: A fajl ki irodott!");
        } else {
            Tovabb_Gombra("\tHIBA: A szotar nem tartalmaz szoparokat, igy nem irhato fajlba!");
        }

    } else {
        if(i->szotar.szoparok_szama != 0) {
            printf("\tSzoparok szama: %d\n", i->szotar.szoparok_szama);
            for(int j = 0; j < i->szotar.szoparok_szama; j++) {
                printf("\tAz %d. szopar: %s - %s\n", j, i->szotar.szoparok_tomb[0][j], i->szotar.szoparok_tomb[1][j]);
            }
            Tovabb_Gombra("\tNyomj le egy billentyut a folytatashoz!");
        } else {
            Tovabb_Gombra("\tHIBA: A szotar nem tartalmaz szoparokat, igy nem irhato a konzolra!");
        }

    }
}

// Hozzá add egy új szó párt a választott szótárhoz feltéve, hogy a szótár nem érte el a maximális kapacitását. (ez 1000 szópár)
void Uj_Szo_Add(Lista *Fo_Lista, int Melyik_Szotar, char *Szo_Nyelv1, char *Szo_Nyelv2) {
    if (Fo_Lista == NULL) {
        return;
    }

    Lista *i = Fo_Lista;
    int Jelenlegi_Szotar = 0;

    while (i != NULL && Jelenlegi_Szotar < Melyik_Szotar) {
        i = i->kov;
        Jelenlegi_Szotar++;
    }

    if (i == NULL) {
        return;
    }

    int db = i->szotar.szoparok_szama;
    if (db >= 1000) {
        return;
    }

    strcpy(i->szotar.szoparok_tomb[0][db], Szo_Nyelv1);
    strcpy(i->szotar.szoparok_tomb[1][db], Szo_Nyelv2);

    i->szotar.szoparok_szama++;
}

// Egy választott szót/szópárt lehet vele módosítani a szótárban.
void Szopar_Javito(Lista *Fo_Lista, int Melyik_Szotar, int Hanyadik_Szopar) {
    char Szo1[50+1];
    char Szo2[50+1];
    char Melyiket_Javit[50+1];
    int Hanyadik_Proba = 0;
    Lista *Akt = Lista_Lepteto(Fo_Lista, Melyik_Szotar);
    /* 3 opció lehetséges:
        - Melyiket_Javit [0] == 'F' vagy 'f' => Első szót javítja
        - Melyiket_Javit [0] == 'S' vagy 's' => Második szót javítja
        - Melyiket_Javit [0] == 'B' vagy 'b' => Mindkettő szót javítja
    A Melyiket_Javit nem [0] elemeit nem nézi a program!
    Ha a [0] elem a keresett, akkor végrehajtódik a neki megfelelő szó javítása. */
    do {
        Konzol_Torles();
        if(Hanyadik_Proba != 0 && Melyiket_Javit[0] != 'F' && Melyiket_Javit[0] != 'f' && Melyiket_Javit[0] != 'S' && Melyiket_Javit[0] != 's' && Melyiket_Javit[0] != 'B' && Melyiket_Javit[0] != 'b')
            printf("\t>>> HIBA: Ervenytelen opciot adott meg! <<<\n");

        Szotar_Felirat();
        printf("\tElso nyelvu szo szerkesztese (F),\n\tMasodik nyelvu szo szerkesztese (S)\n\tVagy mindketott szo szerkesztese (B): ");

        // fgets használata, ellenőrzés, hogy ne legyen üres a bemenet
        if (fgets(Melyiket_Javit, sizeof(Melyiket_Javit), stdin) != NULL) {
            size_t Hossz = strlen(Melyiket_Javit);

            // Töröljük a '\n' karaktert, ha van
            if (Hossz > 0 && Melyiket_Javit[Hossz - 1] == '\n') {
                Melyiket_Javit[Hossz - 1] = '\0';
            }

            if(Hossz > 1 && isalpha(Melyiket_Javit[0])) {
                switch(Melyiket_Javit[0]) {
                    case 'f':
                    case 'F':
                        Torol_Szotar_Felirat();
                        Szoveg_Beolvas(true, "Add meg a valaztott szo-t mire javitanad: ", Szo1, -1, "", true, "Nem tartalmazhat egy szo szamot!");

                        strcpy(Akt->szotar.szoparok_tomb[0][Hanyadik_Szopar], Szo1);

                        Torol_Szotar_Felirat();
                        Tovabb_Gombra("\tSIKER: A szo frissitve lett!");
                        break;

                    case 's':
                    case 'S':
                        Torol_Szotar_Felirat();
                        Szoveg_Beolvas(true, "Add meg a valaztott szo-t mire javitanad: ", Szo2, -1, "", true, "Nem tartalmazhat egy szo szamot!");

                        strcpy(Akt->szotar.szoparok_tomb[1][Hanyadik_Szopar], Szo2);

                        Torol_Szotar_Felirat();
                        Tovabb_Gombra("\tSIKER: A szo frissitve lett!");
                        break;

                    case 'b':
                    case 'B':
                        Torol_Szotar_Felirat();
                        Szoveg_Beolvas(true, "Add meg a valaztott szo-t mire javitanad (1. nyelven): ", Szo1, -1, "", true, "Nem tartalmazhat egy szo szamot!");

                        Torol_Szotar_Felirat();
                        Szoveg_Beolvas(true, "Add meg a valaztott szo-t mire javitanad (2. nyelven): ", Szo2, -1, "", true, "Nem tartalmazhat egy szo szamot!");

                        strcpy(Akt->szotar.szoparok_tomb[0][Hanyadik_Szopar], Szo1);
                        strcpy(Akt->szotar.szoparok_tomb[1][Hanyadik_Szopar], Szo2);

                        Torol_Szotar_Felirat();
                        Tovabb_Gombra("\tSIKER: A szopar frissitve lett!");
                        break;

                    default:
                        break;
                }
            }
            Hanyadik_Proba++;
        }
    } while(Melyiket_Javit[0] != 'F' && Melyiket_Javit[0] != 'f' && Melyiket_Javit[0] != 'S' && Melyiket_Javit[0] != 's' && Melyiket_Javit[0] != 'B' && Melyiket_Javit[0] != 'b');
}

// Megadott szótár egy adott szópárját törli.
void Szopar_Torlo(Lista *Fo_Lista, int Melyik_Szotar, int Melyiket_Torol) {
    Lista *Akt = Lista_Lepteto(Fo_Lista, Melyik_Szotar);

    if (Akt->szotar.szoparok_szama > 0 && Melyiket_Torol < Akt->szotar.szoparok_szama) {
        for (int i = Melyiket_Torol; i < Akt->szotar.szoparok_szama - 1; i++) {
            strcpy(Akt->szotar.szoparok_tomb[0][i], Akt->szotar.szoparok_tomb[0][i + 1]);
            strcpy(Akt->szotar.szoparok_tomb[1][i], Akt->szotar.szoparok_tomb[1][i + 1]);
        }
        strcpy(Akt->szotar.szoparok_tomb[0][Akt->szotar.szoparok_szama - 1], "");
        strcpy(Akt->szotar.szoparok_tomb[1][Akt->szotar.szoparok_szama - 1], "");

        Akt->szotar.szoparok_szama--;
    }
}