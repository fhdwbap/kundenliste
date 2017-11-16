/*
  kundenliste.c
	Dynamische Datenstrukturen: Beispiel einer einfachen linearen Liste

  http://www.github.com/fhdwbap/kundenliste 
	bap 11.04.2001, 23.01.2008, 16.11.2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PROGTITLE   "Lineare Liste Demo"
#define PROGVERSION "0.0.3"
#define PROGDATE    "2001-2017"
#define PROGAUTHOR  "FHDW Software Demonstration Group"

/*
    Als Nutzdatentyp wird hier exemplarisch ein
    einfacher Strukturtyp Kundendaten verwendet.
    Dies ist jedoch fuer die Algorithmik einer
    linearen Liste nicht wesentlich.

    Per typedef wird dieser Strukturtyp kurz
    mit "KD" bezeichnet.
 */
typedef struct Kundendaten // minimalistisch zur Demo
{
    char nachname[50];
    /* weitere Attribute sind hier weggelassen */
} KD;


/*
    Der Datentyp fuer die lineare Liste wird
    per typedef kurz mit "LL" bezeichnet.
 */
typedef struct Knoten
{
    KD              data;
	struct Knoten * next;
} Knoten; /* end struct Knoten */

/*
    Der Kopf einer Linearen Liste ist ein
    Pointer auf einen Knoten wie oben
    definiert. Wir geben diesem Datentypen
    den eigenen Namen "LL".
 */
typedef Knoten* LL;


/*
    Prototypen der hier realisierten Funktionen.
 */
void KDEingabe(KD *);
void KDAusgabe(KD);

void LLAusgabe(LL);
void LLAnhaengen(LL*, KD);
void LLFreigeben(LL*);

char * StringEingeben(char *, int);
void Hilfe(void);


/*
    Hauptprogramm (main)
 */
int main(void)
{
    LL kopf = NULL;       /* Kopf der linearen Liste */
    char auswahl;

    KD einKunde;

    /* Begruessung des Anwenders */
    printf("%s v %s (c) %s %s\n"
           "\"H\" fuer Hilfe, \"E\" fuer Programmende.\n",PROGTITLE,PROGVERSION,PROGDATE,PROGAUTHOR);

    /* Menu-Schleife */
    do
    {
        printf("\nIhre Auswahl, H fuer Hilfe:  ");
        fflush(stdin);
        auswahl = getchar();
        getchar(); // stoerendes Newline absaugen...

        switch(auswahl)
        {
            case 'a':
            case 'A':
                    printf("Bitte Kundendaten eingeben: \n");
                    KDEingabe(&einKunde);
                    LLAnhaengen(&kopf,einKunde);
                    break;

            case 'e':
            case 'E':
                    break;

            case 'h':
            case 'H':
            case '?':
                    Hilfe();
                    break;

            case 'l':
            case 'L':
                    LLAusgabe(kopf);
                    break;

            default:
                    printf("Ungueltige Auswahl: \"%c\"!\n",auswahl);
                    break;

        } /* end switch */

    } while (auswahl != 'e' && auswahl != 'E');


    /* Freigabe der Liste */
    LLFreigeben(&kopf);

} /* end main */



/*
    Implementierung der Funktionen
 */

/* Die Funktionen zum Kundendatentyp */

/*
    Eingeben eines Kundendatensatzes
 */
void KDEingabe(KD * pKunde)
{
    printf("Kundeneingabe\n");
    printf("  Nachname: ");
    StringEingeben(pKunde->nachname,50);
}


void KDAusgabe(KD kunde)
{
    printf("%s\n",kunde.nachname);
}



/* Die Funktionen zur Linearen Liste */
void LLAusgabe(LL kopf)
{
    if (kopf == NULL)
    {
        printf("Die Liste ist leer.\n");
        return;
    }

    while (kopf)
    {
        KDAusgabe(kopf->data);
        kopf = kopf->next;
    }

}


void LLAnhaengen(LL * pKopf, KD kunde)
{
    Knoten* neuerKnoten = NULL;
    LL tmp = NULL;

    /* Knoten bereitstellen fuer den Kunden */
    neuerKnoten = (Knoten*) malloc ( 1 * sizeof(Knoten) );
    if (neuerKnoten == NULL)
    {
        printf("Fataler Programmfehler: \n"
            "Speicher konnte nicht allokiert werden.\n");
        exit(EXIT_FAILURE); /* Programmausstieg */
    }
    printf("** Allokiert Adresse %08x ** \n",(unsigned int)neuerKnoten);
    neuerKnoten->data = kunde;
    neuerKnoten->next = NULL;

    if (*pKopf == NULL)
    {
        /* neues erstes Element */
        printf("** Fuege erstes Element ein! **\n");
        *pKopf = neuerKnoten;
        return;
    }

    /* Liste hat bereits mindestens ein Element */
    tmp = *pKopf;
    while (tmp->next)  /* ausfuehrlich: tmp->next != NULL */
    {
        tmp = tmp->next;
    }
    /* Jetzt ist tmp der Zeiger auf den letzten Knoten */
    tmp->next = neuerKnoten;
    return;
}


void LLFreigeben(LL * pKopf)
{
    LL tmp = *pKopf, tmp2;

    /* Freigabe der gesamten Liste */
    if (tmp == NULL)
    {
        printf("** Liste war leer -> freigegeben! **\n");
        return; /* Liste war leer */
    }

    while(tmp)
    {
        tmp2 = tmp->next;
        printf("** Freigabe Adresse %08x ** \n",(unsigned int)tmp);
        free(tmp);
        tmp = tmp2;
    }
    *pKopf = NULL;

}



/* Hilfsfunktionen */
char * StringEingeben(char * s, int laenge)
{
    int sl;
    fflush(stdin);
    fgets(s,laenge,stdin);

    sl=strlen(s);
    if (s[sl-1]=='\n')  /* ggf. schliessendes Newline entfernen */
    {
        s[sl-1] = '\0';
    }

    return s;
}


void Hilfe(void)
{
    printf(
        "\n"
        "Sie befinden sich im Hilfesystem der Kundenlistenverwaltung\n"
        "von %s.\n"
        "Zur Auswahl stehen: \n"
        "A ....... Anlegen eines (weiteren) Kunden \n"
        "E ....... Programm beenden\n"
        "L ....... Ausgabe (Listen) der gesamten Kundenliste\n"
        "H ....... Diese Hilfe aufrufen \n"
        "\n"
        , PROGAUTHOR
    );
}


/* end of file kundenliste.c */
