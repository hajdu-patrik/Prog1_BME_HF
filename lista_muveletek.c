// Hajdú Patrik Zsolt – RP329D – utolsó frissítés dátuma: 2024.11.19
#include <stdio.h>
#include <string.h>

#include "struktura.h"
#include "debugmalloc.h"

// A lista végére beszúr egy új elemet.
void L_Beszur(Lista **Fo_Lista, const char* nyelv1, const char* nyelv2) {
    Lista *Uj_Elem = (Lista*) malloc(sizeof(Lista));
    Uj_Elem->szotar.nyelv1 = (char *) malloc(strlen(nyelv1) + 1);
    Uj_Elem->szotar.nyelv2 = (char *) malloc(strlen(nyelv2) + 1);
    strcpy(Uj_Elem->szotar.nyelv1, nyelv1);
    strcpy(Uj_Elem->szotar.nyelv2, nyelv2);
    Uj_Elem->szotar.szoparok_szama = 0;
    Uj_Elem->kov = NULL;

    if(*Fo_Lista == NULL) {
        *Fo_Lista = Uj_Elem;
    } else {
        Lista *i = *Fo_Lista;
        while(i->kov != NULL) {
            i = i->kov;
        }
        i->kov = Uj_Elem;
    }
}

// Felszabadítja a teljes láncolt listát.
void L_Felszabadit(Lista *Fo_Lista) {
    while(Fo_Lista != NULL) {
        Lista *kov = Fo_Lista->kov;
        free(Fo_Lista->szotar.nyelv1);
        free(Fo_Lista->szotar.nyelv2);
        free(Fo_Lista);
        Fo_Lista = kov;
    }
}

// Visszaadja a láncolt lista hosszát.
int Lista_Hossza(Lista *Fo_Lista) {
    int Hossz = -1;
    Lista *i = Fo_Lista;
    while(i != NULL) {
        Hossz++;
        i = i->kov;
    }
    return Hossz;
}

// Kiírja a listában található szótárakat, mindegyiket egy sorszámmal ellátva.
void L_Kiir(Lista *Fo_Lista) {
    int Szotar_DB_Szam = -1;
    for(Lista *i = Fo_Lista; i != NULL; i = i->kov) {
        printf("\t%d. %s - %s \n",(Szotar_DB_Szam + 1), i->szotar.nyelv1, i->szotar.nyelv2);
        Szotar_DB_Szam++;
    }
    printf("\n");
}

// Törli a listában található, megadott pozíciójú szótárat.
void Szotar_Listabol_Torlo(Lista **Fo_Lista, int Melyik_Szotar) {
    Lista *Lemarado = NULL;
    Lista *Mozgo = *Fo_Lista;
    int i = 0;

    while (i != Melyik_Szotar && Mozgo != NULL) {
        Lemarado = Mozgo;
        Mozgo = Mozgo->kov;
        i++;
    }

    if (Mozgo == NULL) {
        // Nincs teendő, mert nem találtunk ilyen sorszámú elemet
    } else if (Lemarado == NULL) {
        // Az első elemet kell törölni
        Lista *Uj_Fo_Lista = Mozgo->kov;
        free(Mozgo->szotar.nyelv1);
        free(Mozgo->szotar.nyelv2);
        free(Mozgo);
        *Fo_Lista = Uj_Fo_Lista;
    } else {
        // Egy középső vagy utolsó elemet kell törölni
        Lemarado->kov = Mozgo->kov;
        free(Mozgo->szotar.nyelv1);
        free(Mozgo->szotar.nyelv2);
        free(Mozgo);
    }
}

// Addig lépked előre a láncolt listában, míg el nem éri a megadott pozíciójú szótárt.
Lista *Lista_Lepteto(Lista *Fo_Lista, int Valasztott_Szotar) {
    Lista *Akt = Fo_Lista;
    for (int i = 0; i < Valasztott_Szotar && Akt != NULL; i++) {
        Akt = Akt->kov;
    }
    return Akt;
}