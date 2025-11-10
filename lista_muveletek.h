// Hajdú Patrik Zsolt – RP329D – utolsó frissítés dátuma: 2024.11.19
#ifndef LISTA_MUVELETEK_H_INCLUDED
#define LISTA_MUVELETEK_H_INCLUDED

// A lista végére beszúr egy új elemet.
void L_Beszur(Lista **Fo_Lista, const char* nyelv1, const char* nyelv2);

// Felszabadítja a teljes láncolt listát.
void L_Felszabadit(Lista *Fo_Lista);

// Visszaadja a láncolt lista hosszát.
int Lista_Hossza(Lista *Fo_Lista);

// Kiírja a listában található szótárakat, mindegyiket egy sorszámmal ellátva.
void L_Kiir(Lista *Fo_Lista);

// Törli a listában található, megadott pozíciójú szótárat.
void Szotar_Listabol_Torlo(Lista **Fo_Lista, int Melyik_Szotar);

// Addig lépked előre a láncolt listában, míg el nem éri a megadott pozíciójú szótárt.
Lista *Lista_Lepteto(Lista *Fo_Lista, int Valasztott_Szotar);

#endif