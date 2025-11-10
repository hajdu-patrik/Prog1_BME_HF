// Hajdú Patrik Zsolt – RP329D – utolsó frissítés dátuma: 2024.11.19
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "struktura.h"
#include "seged.h"
#include "lista_muveletek.h"
#include "szotar_muveletek.h"
#include "debugmalloc.h"

int main() {
    // Fő lista => amiben a program tárolja a szótárakat
    Lista *Fo_Lista = NULL;

    // Kezdő értékek inicializálása
    L_Beszur(&Fo_Lista, "angol", "magyar");
    L_Beszur(&Fo_Lista, "francia", "magyar");
    L_Beszur(&Fo_Lista, "nemet", "magyar");

    Uj_Szo_Add(Fo_Lista, 0, "apple", "alma");
    Uj_Szo_Add(Fo_Lista, 0, "pear", "korte");
    Uj_Szo_Add(Fo_Lista, 0, "dog", "kutya");

    Uj_Szo_Add(Fo_Lista, 1, "poire", "korte");
    Uj_Szo_Add(Fo_Lista, 1, "ours", "medve");
    Uj_Szo_Add(Fo_Lista, 1, "pomme", "alma");

    Uj_Szo_Add(Fo_Lista, 2, "apfel", "alma");
    Uj_Szo_Add(Fo_Lista, 2, "hund", "kutya");
    Uj_Szo_Add(Fo_Lista, 2, "tragen", "medve");


    char Menupont_Bemenet[50+1];
    int Valasztott_Menupont = -1;
    do {
        // Menüpont választása
        Torol_Szotar_Felirat();
        Menu_Opciok();

        fgets(Menupont_Bemenet, sizeof(Menupont_Bemenet), stdin);
        Menupont_Bemenet[strlen(Menupont_Bemenet) - 1] = '\0';

        size_t Menu_Hossza = strlen(Menupont_Bemenet);

        if(Menu_Hossza == 1 && isdigit(Menupont_Bemenet[0])) {
            Valasztott_Menupont = Menupont_Bemenet[0] - '0';
            if(Valasztott_Menupont < 0 || Valasztott_Menupont > 5) {
                Valasztott_Menupont = -1;
            }
        } else {
            Valasztott_Menupont = -1;
        }

        // A választott menüpont kivitelezése
        switch(Valasztott_Menupont) {
            case 0: {
                Torol_Szotar_Felirat();

                // Szotárak ki listázása
                int Hany_Szotar = Lista_Hossza(Fo_Lista);

                if(Hany_Szotar < 0) {
                    Torol_Szotar_Felirat();
                    Tovabb_Gombra("\tHIBA: Nincs szotar a programban, igy nem lehet veluk dolgozni!");
                } else {
                    int Valasztott_Szotar = Szam_Beker_Intervallumban(Fo_Lista, 0, Hany_Szotar, 0, true, "Nem letezo szotarat valasztott!");

                    Torol_Szotar_Felirat();
                    // A Szótár menüpont választása
                    int Valasztott_Menupont_Szotar = Szam_Beker_Intervallumban(NULL, 0, 6, 2, true, "Ervenytelen szotar menupontot adott meg!");

                    // A választott szótár menüpont kivitelezése
                    switch(Valasztott_Menupont_Szotar) {
                        case 0: {
                            Torol_Szotar_Felirat();
                            Ki_Listazo(Fo_Lista, Valasztott_Szotar, false, "");
                        } break;

                        case 1: {
                            Torol_Szotar_Felirat();

                            char Ki_Ir_File_Neve_Input[50+1];
                            char *Ki_Ir_File_Neve = NULL;

                            Lista *Akt_Elem = Lista_Lepteto(Fo_Lista, Valasztott_Szotar);

                            if(Akt_Elem->szotar.szoparok_szama != 0) {
                                Szoveg_Beolvas(true, "Add meg a fajl nevet: ", Ki_Ir_File_Neve_Input, -1, "", true, "Nem tartalmazhat egy fajl neve szamot!");
                                Ki_Ir_File_Neve = Txt_Vizsgalo(Ki_Ir_File_Neve_Input);
                            }

                            if (Ki_Ir_File_Neve != NULL) {
                                Ki_Listazo(Fo_Lista, Valasztott_Szotar, true, Ki_Ir_File_Neve_Input);
                            } else {
                                Ki_Listazo(Fo_Lista, Valasztott_Szotar, true, Ki_Ir_File_Neve);
                            }
                            free(Ki_Ir_File_Neve);
                        } break;

                        case 2: {
                            Torol_Szotar_Felirat();
                            char Uj_Szo_Nyelv1[50+1];
                            Szoveg_Beolvas(true, "Add meg a valasztott szotar 1. uj szavat: ", Uj_Szo_Nyelv1, -1, "", true, "Nem tartalmazhat egy szo szamot!");

                            Torol_Szotar_Felirat();
                            char Uj_Szo_Nyelv2[50+1];
                            Szoveg_Beolvas(true, "Add meg a valasztott szotar 2. uj szavat: ", Uj_Szo_Nyelv2, -1, "", true, "Nem tartalmazhat egy szo szamot!");

                            Torol_Szotar_Felirat();
                            Uj_Szo_Add(Fo_Lista, Valasztott_Szotar, Uj_Szo_Nyelv1, Uj_Szo_Nyelv2);
                            Tovabb_Gombra("\tSIKER: A szopar hozza lett adva a valasztott szotarhoz!");
                        } break;

                        case 3: {
                            Torol_Szotar_Felirat();

                            Lista *Akt_Szopar_Javit = Lista_Lepteto(Fo_Lista, Valasztott_Szotar);

                            if(Akt_Szopar_Javit->szotar.szoparok_szama != 0) {
                                int Hanyadik_Szopar_Szerkeszt = Szam_Beker_Intervallumban(NULL, 0, (Akt_Szopar_Javit->szotar.szoparok_szama - 1), 3, true, "Ervenytelen szopar szamot adott meg!");

                                Szopar_Javito(Fo_Lista, Valasztott_Szotar, Hanyadik_Szopar_Szerkeszt);

                            } else {
                                Tovabb_Gombra("\tHIBA: Nincs a szotarban szopar, igy nincs mit javitani!");
                            }
                        } break;

                        case 4: {
                            Torol_Szotar_Felirat();

                            Lista *Akt_Szopar_Torol = Lista_Lepteto(Fo_Lista, Valasztott_Szotar);
                            if(Akt_Szopar_Torol->szotar.szoparok_szama != 0) {
                                int Hanyadik_Szopart_Torol = Szam_Beker_Intervallumban(NULL, 0, (Akt_Szopar_Torol->szotar.szoparok_szama - 1), 3, true, "Ervenytelen szopar szamot adott meg!");

                                Szopar_Torlo(Fo_Lista, Valasztott_Szotar, Hanyadik_Szopart_Torol);
                                Torol_Szotar_Felirat();
                                Tovabb_Gombra("\tSIKER: A szopar torolve lett!");
                            } else {
                                Tovabb_Gombra("\tHIBA: Nincs a szotarban szopar, igy nincs mit torolni!");
                            }
                        } break;

                        case 5: {
                            Torol_Szotar_Felirat();

                            Lista *Akt_Szopar_Quiz = Lista_Lepteto(Fo_Lista, Valasztott_Szotar);
                            int Szopar_Szam = Akt_Szopar_Quiz->szotar.szoparok_szama;
                            if (Szopar_Szam != 0) {
                                bool Van_E_Mar_Ilyen = false;
                                char Akt_Nyelv[51];
                                do {
                                    Konzol_Torles();
                                    if(Van_E_Mar_Ilyen)
                                        printf("\t>>> HIBA: Nem a valasztott szotarban szereplo nyelvek egyiket adtad meg! <<<\n");

                                    Szotar_Felirat();
                                    Szoveg_Beolvas(true, "Add meg melyik nyelvet szeretned gyakorolni: ", Akt_Nyelv, -1, "", true, "Nem tartalmazhat egy NYELV szamot!");
                                    Van_E_Mar_Ilyen = true;
                                } while((strcmp(Akt_Nyelv, Akt_Szopar_Quiz->szotar.nyelv1) != 0) && (strcmp(Akt_Nyelv, Akt_Szopar_Quiz->szotar.nyelv2) != 0));

                                int Melyik_Nyelv = -1;
                                if((strcmp(Akt_Nyelv, Akt_Szopar_Quiz->szotar.nyelv1) == 0))
                                    Melyik_Nyelv = 0;
                                else
                                    Melyik_Nyelv = 1;

                                // A helyesen megadott szavak nyomon követésére szolgál
                                int Sikerek_Szama = 0;
                                bool Megoldva[Szopar_Szam];
                                for(int i = 0; i < Szopar_Szam; i++)
                                    Megoldva[i] = false;

                                srand(time(NULL));
                                Torol_Szotar_Felirat();
                                while (Sikerek_Szama < Szopar_Szam) {
                                    int Random_Szo = rand() % (Szopar_Szam + 1);
                                    if (Megoldva[Random_Szo]) {
                                        // Ha a szópárt már kitalálták, ugorjunk a következőre
                                        continue;
                                    }

                                    char Akt_Valassz[50+1];
                                    // Ha nyelv1-et adót meg a felhasználó gyakorlásra akkor nyelv2-es szavak nyelv1-es megfelelőit kell kérdezni tőle
                                    int Masik_Nyelv = (Melyik_Nyelv == 0) ? 1 : 0;

                                    Szoveg_Beolvas(false, "", Akt_Valassz, 0, Akt_Szopar_Quiz->szotar.szoparok_tomb[Melyik_Nyelv][Random_Szo], true, "Nem tartalmazhat egy szo szamot!");

                                    if (strcmp(Akt_Szopar_Quiz->szotar.szoparok_tomb[Masik_Nyelv][Random_Szo], Akt_Valassz) == 0) {
                                        Sikerek_Szama++;
                                        Megoldva[Random_Szo] = true;

                                        Konzol_Torles();
                                        printf("\tSIKER: Helyes valasz!");
                                        printf("\t%d/%d!", Sikerek_Szama, Szopar_Szam);
                                        Szotar_Felirat();
                                    } else {
                                        Konzol_Torles();
                                        printf("\t>>> HIBA: Helytelen valasz! <<<");
                                        printf("\t%d/%d!", Sikerek_Szama, Szopar_Szam);
                                        Szotar_Felirat();
                                    }
                                }

                                Tovabb_Gombra("\tSIKER: Kitalaltad az osszes szopart!\n");
                            } else {
                                Tovabb_Gombra("\tHIBA: Nincs a szotarban szopar, igy nem lehet QUIZ-elni!");
                            }
                        } break;

                        case 6: {
                            Konzol_Torles();
                        } break;

                        default: {
                        } break;
                    }
                }
            } break;

            case 1: {
                // Egy új szótár nyelvének felvétele
                bool Van_E_Mar_Ilyen = false;

                char Uj_Szotar_Nyelv1[50+1];
                char Uj_Szotar_Nyelv2[50+1];

                do {
                    Konzol_Torles();
                    if(Van_E_Mar_Ilyen)
                        printf("\t>>> HIBA: Letezik mar ilyen szotar! <<<\n");

                    Szotar_Felirat();
                    Szoveg_Beolvas(true, "Add meg az uj szotar 1. nyelvet: ", Uj_Szotar_Nyelv1, -1, "", true, "Nem tartalmazhat egy nyelv szamot!");

                    Torol_Szotar_Felirat();
                    Szoveg_Beolvas(true, "Add meg az uj 2. nyelvet: ", Uj_Szotar_Nyelv2, -1, "", true, "Nem tartalmazhat egy nyelv szamot!");

                    char Be_Olvasott_Nyelv[101];
                    strcpy(Be_Olvasott_Nyelv, Uj_Szotar_Nyelv1);
                    strcat(Be_Olvasott_Nyelv, Uj_Szotar_Nyelv2);

                    Van_E_Mar_Ilyen = false;

                    for(Lista *iter = Fo_Lista; iter != NULL; iter = iter->kov) {
                        char Be_Olvasott_Nyelv_Temp[101];
                        strcpy(Be_Olvasott_Nyelv_Temp, iter->szotar.nyelv1);
                        strcat(Be_Olvasott_Nyelv_Temp, iter->szotar.nyelv2);

                        if(strcmp(Be_Olvasott_Nyelv_Temp, Be_Olvasott_Nyelv) == 0) {
                            Van_E_Mar_Ilyen = true;
                            break;
                        }
                    }
                } while(Van_E_Mar_Ilyen == true);

                L_Beszur(&Fo_Lista, Uj_Szotar_Nyelv1, Uj_Szotar_Nyelv2);
                Torol_Szotar_Felirat();
                Tovabb_Gombra("\tSIKER: A nyelvek hozza lettek adva az uj szotarhoz!");

                // Az új szótár nyelvei szerinti első szópár felvétele
                Torol_Szotar_Felirat();
                char Uj_Szo_Nyelv1[50+1];
                Szoveg_Beolvas(true, "Add meg az uj szotar 1. szavat: ", Uj_Szo_Nyelv1, -1, "", true, "Nem tartalmazhat egy szo szamot!");

                Torol_Szotar_Felirat();
                char Uj_Szo_Nyelv2[50+1];
                Szoveg_Beolvas(true, "Add meg az uj szotar 2. szavat: ", Uj_Szo_Nyelv2, -1, "", true,"Nem tartalmazhat egy szo szamot!");

                Uj_Szo_Add(Fo_Lista, Lista_Hossza(Fo_Lista), Uj_Szo_Nyelv1, Uj_Szo_Nyelv2);
                Torol_Szotar_Felirat();
                Tovabb_Gombra("\tSIKER: A szopar hozza lett adva az uj szotarhoz!");
            } break;

            case 2: {
                Torol_Szotar_Felirat();

                int Hany_Szotar = Lista_Hossza(Fo_Lista);
                if(Hany_Szotar < 0) {
                    Tovabb_Gombra("\tHIBA: Nincs szotar a programban, igy nincs mit torolni!");
                } else {
                    int Valasztott_Szotar = Szam_Beker_Intervallumban(Fo_Lista, 0, Hany_Szotar, 1, true, "Nem letezo szotarat valasztott!");

                    Szotar_Listabol_Torlo(&Fo_Lista, Valasztott_Szotar);
                    Torol_Szotar_Felirat();
                    Tovabb_Gombra("\tSIKER: A valasztott szotar torolve lett!");
                }
            } break;

            case 3: {
                Torol_Szotar_Felirat();
                char Be_Olvas_File_Neve_Input[50+1];
                char *Be_Olvas_File_Neve = NULL;
                bool Van_E_Mar_Ilyen = false;
                bool Letezik_E_File = false;

                do {
                    do {
                        Szoveg_Beolvas(true, "Add meg a beolvasando fajl nevet: ", Be_Olvas_File_Neve_Input, -1, "", true, "Nem tartalmazhat egy fajl neve szamot!");
                        Be_Olvas_File_Neve = Txt_Vizsgalo(Be_Olvas_File_Neve_Input);

                        Van_E_Mar_Ilyen = Van_E(Fo_Lista, Be_Olvas_File_Neve);
                        if (Van_E_Mar_Ilyen) {
                            Konzol_Torles();
                            printf("\t>>> HIBA: Letezik mar ilyen szotar! <<<\n");
                            Szotar_Felirat();
                            free(Be_Olvas_File_Neve);
                            Be_Olvas_File_Neve = NULL;
                        }
                    } while(Van_E_Mar_Ilyen);

                    Letezik_E_File = File_Megtalalhato_E(Be_Olvas_File_Neve);
                    if (!Letezik_E_File) {
                        Konzol_Torles();
                        printf("\t>>> HIBA: A fajl nem letezik, adja meg helyesen! <<<\n");
                        Szotar_Felirat();
                        free(Be_Olvas_File_Neve);
                    }
                } while(!Letezik_E_File);

                FILE *Be_File = fopen(Be_Olvas_File_Neve, "r");
                if (Be_File == NULL) {
                    perror("\t>>> HIBA: A fajl megnyitása közben! <<<");
                    free(Be_Olvas_File_Neve);
                    return 1;
                }

                // Egy sorban lévő szótár beolvasásánál maximum 10 darab szópár szereplhet, ha minden szó 50 karakter hosszú. Ebből következik a 2 * 10 * (50+1) = 1020
                // De ez technikailag elképzelhetetlen igy átlagosan 20-25 szópár.
                char File_Sor[1020+1];

                while (fgets(File_Sor, sizeof(File_Sor), Be_File)) {
                    char *Darab;
                    char Temp_Nyelv1[50+1], Temp_Nyelv2[50+1];

                    Darab = strtok(File_Sor, ";");
                    if (Darab != NULL) {
                        strcpy(Temp_Nyelv1, Darab);
                    }

                    Darab = strtok(NULL, ";");
                    if (Darab != NULL) {
                        strcpy(Temp_Nyelv2, Darab);
                    }

                    L_Beszur(&Fo_Lista, Temp_Nyelv1, Temp_Nyelv2);

                    // Mivel az újonnan beolvasandó szótár nyilván a legutolsó lesz láncolt listába oda kell navigálni.
                    Lista *Akt_Szotar = Fo_Lista;
                    while (Akt_Szotar->kov != NULL) {
                        Akt_Szotar = Akt_Szotar->kov;
                    }

                    int i = 0;
                    while ((Darab = strtok(NULL, ";")) != NULL) {
                        char Temp_Szopar[101];
                        strcpy(Temp_Szopar, Darab);

                        char *Vesszo_Vago = strstr(Temp_Szopar, ",");
                        if (Vesszo_Vago != NULL) {
                            *Vesszo_Vago = '\0';
                            Vesszo_Vago++;
                            strcpy(Akt_Szotar->szotar.szoparok_tomb[0][i], Temp_Szopar);
                            strcpy(Akt_Szotar->szotar.szoparok_tomb[1][i], Vesszo_Vago);
                        } else {
                            strcpy(Akt_Szotar->szotar.szoparok_tomb[0][i], Temp_Szopar);
                            strcpy(Akt_Szotar->szotar.szoparok_tomb[1][i], "");
                        }

                        Akt_Szotar->szotar.szoparok_szama++;
                        i++;
                    }
                }
                fclose(Be_File);

                if (Be_Olvas_File_Neve != NULL) {
                    free(Be_Olvas_File_Neve);
                }
                Torol_Szotar_Felirat();
                Tovabb_Gombra("\tSIKER: A fajl sikeresen beolvasva a szotarak koze!");
            } break;

                /*
                case 4: {

                    Konzol_Torles();
                    char Keresett_Szo[50+1];
                    Szoveg_Beolvas(true, "Add meg a szot, amelynek az osszes nyelven elerheto megfelelojet szeretned megtekinteni, ha szerepel valamelyik szotarban:", Keresett_Szo, -1, "", true, "Nem tartalmazhat egy szo szamot!");

                    bool van_e_barmelyikben = false;
                    int j = 0;
                    for(Lista *iter = Fo_Lista; iter != NULL; iter = iter->kov) {
                        for(int i = 0; i < iter->szotar.szoparok_szama; i++) {
                            if(strcmp(Keresett_Szo, iter->szotar.szoparok_tomb[0][j]) == 0) {
                                if(!van_e_barmelyikben)
                                    printf("A %s-nek az alabbi megfeleloi, az allabi nyelveken:\n");
                                van_e_barmelyikben = true;

                                printf("%s - %s", iter->szotar.nyelv1, iter->szotar.szoparok_tomb[0][j]);
                                j++;
                            }
                            if(strcmp(Keresett_Szo, iter->szotar.szoparok_tomb[1][j]) == 0) {
                                if(!van_e_barmelyikben)
                                    printf("A %s-nek az alabbi megfeleloi, az allabi nyelveken:\n");
                                van_e_barmelyikben = true;

                                printf("%s - %s", iter->szotar.nyelv2, iter->szotar.szoparok_tomb[1][j]);
                                j++;
                            }
                        }
                    }

                } break;
                */
            case 4: {
                Torol_Szotar_Felirat();

                char Keresett_Szo[50 + 1];
                Szoveg_Beolvas(true, "Add meg a szot, amelynek az osszes nyelven elerheto megfelelojet szeretned megtekinteni, ha szerepel valamelyik szotarban: ", Keresett_Szo, -1, "", true, "Nem tartalmazhat egy szo szamot!"
                );

                bool van_e_barmelyikben = false;
                int j = 0;
                for (Lista *iter = Fo_Lista; iter != NULL; iter = iter->kov) {
                    for (int i = 0; i < iter->szotar.szoparok_szama; i++) {
                        // Ellenőrizd az első nyelvet (nyelv1 -> nyelv2 megfelelés)
                        if (strcmp(Keresett_Szo, iter->szotar.szoparok_tomb[0][i]) == 0) {
                            if (!van_e_barmelyikben) {
                                printf("\n\tA(z) '%s'-nak/nek az alabbi megfeleloi, az alabbi nyelveken:\n", Keresett_Szo);
                                van_e_barmelyikben = true;
                            }
                            printf("\t%s - %s\n", iter->szotar.szoparok_tomb[1][i], iter->szotar.nyelv2);
                        }
                        // Ellenőrizd a második nyelvet (nyelv2 -> nyelv1 megfelelés)
                        if (strcmp(Keresett_Szo, iter->szotar.szoparok_tomb[1][i]) == 0) {
                            if (!van_e_barmelyikben) {
                                printf("\n\tA(z) '%s'-nak/nek az alabbi megfeleloi, az alabbi nyelveken:\n", Keresett_Szo);
                                van_e_barmelyikben = true;
                            }
                            printf("\t%s - %s\n", iter->szotar.szoparok_tomb[0][i], iter->szotar.nyelv1);
                        }
                    }
                }

                if (!van_e_barmelyikben) {
                    Tovabb_Gombra("\t>>> HIBA: A keresett szo nem talalhato meg egyik szotarban sem!<<<");
                } else {
                    Tovabb_Gombra("\tSIKER: A keresett szo megfeleloi ki lettek irva!");
                }
            } break;

            case 5: {
                Konzol_Torles();
                printf("\n\t       _                    _   _   __  _    __                \n");
                printf("\t__   _(_)___ _______  _ __ | |_| | /_/_| |_ /_/_ ___ _ __ __ _ \n");
                printf("\t\\ \\ / / / __|_  / _ \\| '_ \\| __| |/ _` | __/ _` / __| '__/ _` |\n");
                printf("\t \\   /| \\__ \\/ /(_) | | | | |_| |(_| | ||(_| \\__ \\ | |(_| |\n");
                printf("\t  \\_/ |_|___/___\\___/|_| |_|\\__|_|\\__,_|\\__\\__,_|___/_|  \\__,_|\n\n\n");
            } break;

            default: {
                Konzol_Torles();
                printf("\t>>> HIBA: Ervenytelen menupontot adott meg! <<<");
            } break;
        }
    } while(Valasztott_Menupont != 5);

    L_Felszabadit(Fo_Lista);

    return 0;
}