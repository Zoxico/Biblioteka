#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <conio.h>
#include <time.h>



using namespace std;

//			TO DO:
//		- USUWANIE WYPO¯YCZONEJ KSI¥¯KI WRAZ Z KLIENTEM
//		- IMPLEMENTACJA FUNKCJI SPRAWDZAJ¥CEJ OSTATNI¥ CYFRÊ PESELU
//		- ZAPISYWANIE LISTY KLIENTÓW (I EW. PRACOWNIKÓW) DO PLIKU
//		- AUTOMATYCZNE NALICZANIE OP£AT PO URUCHONIENIU PROGRAMU



int t_wiek = 0;
int t_wzrost = 0;
int t_dni = 0;
int t_mies = 0;
int t_lata = 0;
int t_pensja = 0;
int t_dniZatr = 0, t_miesZatr = 0, t_lataZatr = 0;
int t_dniZwoln = 0, t_miesZwoln = 0, t_lataZwoln = 0;
int t_dniZakUm, t_miesZakUm, t_lataZakUm;
int t_ilosc_wyp(0);
int t_nieZwrocone(0);
int t_oplaty(0);
int t_dniWazn = 0, t_miesWazn = 0, t_lataWazn = 0;
int bladNr = 0;
char t_adres[1000] = "nie ustalono ";
string t_PESEL = "nie ustalono ";
string t_imie = "nie ustalono ";
string t_nazwisko = "nie ustalono ";
string t_oczy = "nie ustalono ";
string t_data_zatr = ("00-00-0000"), t_data_zwoln = ("00-00-0000"), t_data_zakUmowy = ("00-00-0000");
string t_data_wazn = ("00-00-0000");
string tytulKsiazki = " ";
string t_wypozyczenia[10] = { "0","1","2"," "," " ," " ," " ," " ,"9" ," " };
int KlicznikID = 0;
int PlicznikID = 0;
int BlicznikID = 0;
//char tytulKsiazki[1000] = " ";
bool poprawneDane = true, pierwszeUruchomienie = true, trybAdmina = false, czyKarta = false;


//=========================================================================================================================

void pobierzDaneOsoby();
//void poprawnoscPeselu();
string intToStr(int n);

int filtrDoCalkowitych(int dana1)
{
	string daneWStr;
	cin >> daneWStr;
	for (int i = 0; i < daneWStr.length(); i++)
	{
		if (daneWStr[i] < 48 || daneWStr[i] > 57)
		{
			poprawneDane = false;
			bladNr = 8;
			//			cout << "DANE: " << daneWStr;
			return 0;
		}

		if (i + 1 == daneWStr.length())
		{


		}
		dana1 = stoi(daneWStr);
		//		cout << dana1;
		//dana2 = dana1;
		return dana1;
	}
}

//--------------------------------------------------OSOBA------------------------------------------------------------------

class Osoba
{
public:
	string PESEL = "00000000000";
	int wiek, wzrost, dni, mies, lata;
	string imie, nazwisko, oczy;
	char adres[1000];
	Osoba();
	Osoba(string t_PESEL, int t_wiek, int t_wzrost, int t_dni, int t_mies, int t_lata, 
			string t_imie, string t_nazwisko, char t_adres[1000], string t_oczy);

	void wyswietlDane(int idDanej, Osoba &obywatel);
	void pokazAdresowe(Osoba obywatel);

//	void poprawnoscPESELu();

};

void pobierzDaneOsoby()
{
	string w_PESEL = "not set    ", w_imie, w_nazwisko, w_oczy, strLata = "00", strDni = "00", strMies = "00";
	string daneWStr, podmiotu;
	int w_wiek = 0, w_wzrost = 0, w_dni = 0, w_mies = 0, w_lata = 0, testWieku;
	char w_adres[1000];

	//int bladNr = 0;

	time_t czas;
	time(&czas);
	tm czasPodzielony = *localtime(&czas);
	//cout << czasPodzielony.tm_mday << "-" << czasPodzielony.tm_mon + 1 << "-" << czasPodzielony.tm_year + 1900 << endl;

	if (czyKarta)
		podmiotu = "klienta: ";
	else
		podmiotu = "pracownika: ";

	cout << endl;
	cout << "	Podaj PESEL " << podmiotu;

	for (int i = 0; i < 11; i++)
	{
		w_PESEL[i] = _getch();		cout << w_PESEL[i];

		if (w_PESEL[i] == 13)
		{
			cout << endl << endl << "			ZBYT KROTKI PESEL!";
			w_PESEL = t_PESEL;
			_getch();
			poprawneDane = false;
			return;
		}

		if (w_PESEL[i] < 48 || w_PESEL[i] > 57)
		{
			cout << endl << endl << "			PESEL MOZE ZAWIERAC TYLKO CYFRY!";
			w_PESEL = t_PESEL;
			_getch();
			poprawneDane = false;
			return;
		}
		//w_PESEL = w_PESEL + znakPESELu;
	}
	//cin >> w_PESEL;	
	//t_lata = ((int)w_PESEL[0] - 48) * 10 + (int)w_PESEL[1] - 48;
	//if (t_lata > 16)
	cout << endl;
	t_PESEL = w_PESEL;
	_getch();
	
	if (!czyKarta)
	{
		cout << "	Podaj wiek " << podmiotu;	//cin >> w_wiek; t_wiek = w_wiek;
		w_wiek = filtrDoCalkowitych(w_wiek);
		t_wiek = w_wiek;
		if (!poprawneDane)
			bladNr = 8;

		cout << "	Podaj wzrost " << podmiotu;	//cin >> w_wzrost; t_wzrost = w_wzrost;
		w_wzrost = filtrDoCalkowitych(w_wzrost);
		t_wzrost = w_wzrost;
		if (!poprawneDane)
			bladNr = 8;
		cout << endl;

		if (w_wzrost < 50 || !poprawneDane)
		{
			cout << endl << endl << w_wzrost << "			COS NIE TAK ZE WZROSTEM :P";
			w_wzrost = t_wzrost;
			_getch();
			return;
		}
	}
	//else
	//	w_wiek = 2016 - w_lata;


	cout << "	Podaj date urodzenia " << podmiotu << endl << endl; //cin >> w_lata;

	cout << "	Dzien: ";	//	cin >> w_dni;	t_dni = w_dni;
	w_dni = filtrDoCalkowitych(w_dni);
	t_dni = w_dni;
	if (!poprawneDane)
		bladNr = 8;

	cout << "	Miesiac: ";	//cin >> w_mies;	t_mies = w_mies;
	w_mies = filtrDoCalkowitych(w_mies);
	t_mies = w_mies;
	if (!poprawneDane)
		bladNr = 8;

	cout << "	Rok: ";		//cin >> w_lata;	t_lata = w_lata;
	w_lata = filtrDoCalkowitych(w_lata);
	t_lata = w_lata;
	if (!poprawneDane)
		bladNr = 8;

	if (czyKarta)
		w_wiek = 2016 - w_lata;

	cout << endl;
	//cout << w_dni << " " << w_mies << " " << w_lata << endl;


	if (w_lata >= 2000)
	{
		strLata[0] = (w_lata - 2000) / 10 + 48;
		strLata[1] = (w_lata - 2000) % 10 + 48;
	}
	else
	{
		strLata[0] = (w_lata - 1900) / 10 + 48; //  = 
		strLata[1] = (w_lata - 1900) % 10 + 48;
	}

	strDni[0] = (w_dni / 10) + 48;
	strDni[1] = (w_dni % 10) + 48;

	//strMies[0] = (w_mies / 10) + 48;
	//strMies[1] = (w_mies % 10) + 48;

	if (w_lata >= 2000)
	{
		strMies[0] = (w_mies / 10) + 48 + 2;
		strMies[1] = (w_mies % 10) + 48;
	}
	else
	{
		strMies[0] = (w_mies / 10) + 48;
		strMies[1] = (w_mies % 10) + 48;
	}

//	cout << w_lata << " " << w_mies << " " << strMies << endl;

	testWieku = 2016 - w_lata;

	if (strLata[0] != t_PESEL[0] || strLata[1] != t_PESEL[1])
	{
		poprawneDane = false;
		bladNr = 1;
	}
	if (strMies[0] != t_PESEL[2] || strMies[1] != t_PESEL[3])
	{
		poprawneDane = false;
		bladNr = 2;
	}
	if (strDni[0] != t_PESEL[4] || strDni[1] != t_PESEL[5])
	{
		poprawneDane = false;
		bladNr = 3;
	}

	if (testWieku != w_wiek && testWieku != w_wiek + 1)
	{
		poprawneDane = false;
		bladNr = 4;
		//cout << testWieku << " " << w_wiek << " " << t_wiek << endl;
	}

	if ((w_mies == 1 && w_dni > 31)
		|| (w_mies == 2 && w_lata % 4 == 0 && w_dni > 29)
		|| (w_mies == 2 && w_lata % 4 != 0 && w_dni > 28)
		|| (w_mies == 3 && w_dni > 31)
		|| (w_mies == 4 && w_dni > 30)
		|| (w_mies == 5 && w_dni > 31)
		|| (w_mies == 6 && w_dni > 30)
		|| (w_mies == 7 && w_dni > 31)
		|| (w_mies == 8 && w_dni > 31)
		|| (w_mies == 9 && w_dni > 30)
		|| (w_mies == 10 && w_dni > 31)
		|| (w_mies == 11 && w_dni > 30)
		|| (w_mies == 12 && w_dni > 31)
		)
	{
		poprawneDane = false;
		bladNr = 5;
	}

	if (w_mies < 1 || w_mies > 12 || w_dni < 1 || w_lata < 1900 || w_lata > 2016)
	{
		poprawneDane = false;
		bladNr = 6;
	}

	if (w_lata > czasPodzielony.tm_year + 1900)
	{
		poprawneDane = false;
		bladNr = 7;
	}
	else
		if (w_lata == czasPodzielony.tm_year + 1900 && w_mies > czasPodzielony.tm_mon + 1)
		{
			poprawneDane = false;
			bladNr = 7;
		}
		else
			if (w_lata == czasPodzielony.tm_year + 1900 && w_mies == czasPodzielony.tm_mon + 1 && w_dni > czasPodzielony.tm_mday)
			{
				poprawneDane = false;
				bladNr = 7;
			}

	//  TO DO: u³amkiAD W DANYCH

	if (!poprawneDane)
	{
		cout << endl << endl << "			BLAD W DANYCH! (NR BLEDU: " << bladNr << ")";

//							//========== DOKUMENTACJA: =================================\\
//							|| B£¥D NR: || OBJAŒNIENIE:									||
//							||----------||----------------------------------------------||
//							||	1		|| NIESPÓJNOŒÆ MIÊDZY PESELEM I ROKIEM UR.		||
//							||	2		|| NIESPÓJNOŒÆ MIÊDZY PESELEM I MIESI¥CEM UR.	||
//							||	3		|| NIESPÓJNOŒÆ MIÊDZY PESELEM I DNIEM UR.		||
//							||	4		|| WIEK NIEZGODNY Z ROKIEM UR.					||
//							||	5		|| Z£A ILOŒÆ DNI W DANYM MIESI¥CU				||
//							||	6		|| DATA UR. SPOZA ZAKRESU						||
//							||	7		|| DATA Z PRZYSZ£OŒCI							||
//							||	8		|| WPROWADZONO NIEDOZWOLONE ZNAKI				||
//							||			||												||
//							\\==========================================================//
	//	poprawneDane = true;
		_getch();
		return;
	}

	cout << "	Podaj imie " << podmiotu;		cin >> w_imie; t_imie = w_imie;

	cout << "	Podaj nazwisko " << podmiotu;	cin >> w_nazwisko; t_nazwisko = w_nazwisko; cin.get();

	if (!czyKarta)
	{
		cout << "	Podaj adres " << podmiotu;		cin.getline(w_adres, 1000);
		for (int i = 0; i < 1000; i++)
		{
			if (w_adres[i] == '\\0')	break;
			t_adres[i] = w_adres[i];
		}

		cout << "	Podaj kolor oczu " << podmiotu; cin >> w_oczy; t_oczy = w_oczy;

	}


}

Osoba::Osoba()
	: PESEL("nie ustalono")
	, wiek(0)
	, wzrost(0)
	, dni(0)
	, mies(0)
	, lata(0)
	, imie("KONSTRUKTOR 1")
	, nazwisko("nie ustalono")
	, adres("nie ustalono")
	, oczy("nie ustalono")
{

}

Osoba::Osoba(string t_PESEL, int t_wiek, int t_wzrost, int t_dni, int t_mies, int t_lata, string t_imie, string t_nazwisko, 
				char t_adres[1000], string t_oczy)
	: PESEL("nie ustalono")
	, wiek(0)
	, wzrost(0)
	, dni(0)
	, mies(0)
	, lata(0)
	, imie("KONSTRUKTOR 2")
	, nazwisko("nie ustalono")
	, adres("nie ustalono")
	, oczy("nie ustalono")
{

	//	cout << PESEL << " = " << t_PESEL << endl;
	PESEL = t_PESEL;
	//	cout << wiek << " = " << t_wiek << endl;
	wiek = t_wiek;
	//	cout << wzrost << " = " << t_wzrost << endl;
	wzrost = t_wzrost;
	//	cout << dni << " = " << t_dni << endl;
	dni = t_dni;
	//	cout << mies << " = " << t_mies << endl;
	mies = t_mies;
	//	cout << lata << " = " << t_lata << endl;
	lata = t_lata;
	//	cout << imie << " = " << t_imie << endl;
	imie = t_imie;
	//	cout << nazwisko << " = " << t_nazwisko << endl;
	nazwisko = t_nazwisko;
	//	cout << adres << " = " << t_adres << endl;
	for (int i = 0; i < 1000; i++)
	{
		if (t_adres[i] == '\\0')	break;
		adres[i] = t_adres[i];
		//cout << "KUTAS" << endl;

	}
	//	cout << oczy << " = " << t_oczy << endl;
	oczy = t_oczy;
	//	cout << PESEL << wiek << wzrost << adres << imie << endl;

	if (pierwszeUruchomienie)
	{
		cout << endl << endl << endl << endl << endl <<
			endl << endl << "		/---------------------------------------\\";
		cout << endl << "		| WCISNIJ [Enter] ABY URUCHOMIC PROGRAM |";
		cout << endl << "		\\---------------------------------------/";
		cin.get();
		system("cls");
	}

	if (pierwszeUruchomienie)
	{
		char odp;
		string hasloPoprawne = "Admin1";
		string haslo;
		//char hasloPoprawne[20] = "Admin1";
		//const int dlugoscHasla = hasloPoprawne.length();
		//char haslo[20];
		bool wlasciweHaslo = false;

		cout << endl << endl << endl << endl << endl <<
			endl << endl << endl << "		CZY CHCESZ URUCHOMIC NARZEDZIE JAKO ADMINISTRATOR?";
		cout << endl << "		[T] TAK			[N] NIE";
		odp = _getch();
		if (odp == 't')
		{
			do
			{
				system("cls");
				cout << haslo;
				cout << endl << endl << endl << endl << endl <<
					endl << endl << endl << "		WPISZ HASLO ADMINISTRATORA:";
				cout << endl << "		> ";
				//for (int i = 0; i < 20; i++)
				//{
				//	haslo[i] = _getch();		cout << "*";
				//	if (haslo[i] == 13)
				//		break;
				//}
				cin >> haslo;
				if (haslo == hasloPoprawne)
				{
					trybAdmina = true;
					wlasciweHaslo = true;
				}

			} while (!wlasciweHaslo);

		}
		else
		{
			pierwszeUruchomienie = false;
			return;
		}

		cin.get();
	}


	pierwszeUruchomienie = false;

}

//--------------------------------------------------PRACOWNIK--------------------------------------------------------------

class Pracownik
	: public Osoba
{
public:

	int pensja, id_pracownika;
	string data_zatr, data_zwoln, data_zakUmowy;


	Pracownik(string t_PESEL, int t_wiek, int t_wzrost, int t_dni, int t_mies, int t_lata, string t_imie, string t_nazwisko, 
			char t_adres[1000], string t_oczy, int t_pensja, string t_data_zatr, string t_data_zwoln, string t_data_zakUmowy);

	~Pracownik();

private:

};

Pracownik::Pracownik(string t_PESEL, int t_wiek, int t_wzrost, int t_dni, int t_mies, int t_lata, string t_imie, string t_nazwisko, 
						char t_adres[1000], string t_oczy, int t_pensja, string t_data_zatr, string t_data_zwoln, 
					string t_data_zakUmowy)
	:pensja (1500)
	,id_pracownika(PlicznikID)
	,data_zatr ("01-01-1900")
	,data_zwoln ("01-01-1900")
	,data_zakUmowy("01-01-1900")
	,Osoba(t_PESEL, t_wiek, t_wzrost, t_dni, t_mies, t_lata, t_imie, t_nazwisko, t_adres, t_oczy)
{
	pensja = t_pensja;
	
	for (int i = 0; i < 11; i++)
	{
		//if (t_data_zatr[i] == '\\0')	break;
		data_zatr[i] = t_data_zatr[i];
	}

	for (int i = 0; i < 11; i++)
	{
		//if (t_data_zwoln[i] == '\\0')	break;
		data_zwoln[i] = t_data_zwoln[i];
	}

	for (int i = 0; i < 11; i++)
	{
		//if (t_data_zakUmowy[i] == '\\0')	break;
		data_zakUmowy[i] = t_data_zakUmowy[i];
	}
	PlicznikID++;
}

void pobierzDanePracownika()
{
	string w_data_zatr = "00-00-0000", w_data_zwoln = "00-00-0000", w_data_zakUmowy = "00-00-0000";
	string strPensja;
	int w_pensja = 0;
	int w_dniZatr = 0, w_miesZatr = 0, w_lataZatr = 0;
	int w_dniZwoln = 0, w_miesZwoln = 0, w_lataZwoln = 0;
	int w_dniZakUm = 0, w_miesZakUm = 0, w_lataZakUm = 0;


	time_t czas;
	time(&czas);
	tm czasPodzielony = *localtime(&czas);

	cout << endl;
	

	cout << "	Podaj pensje pracownika: ";	//cin >> w_wiek; t_wiek = w_wiek;
	w_pensja = filtrDoCalkowitych(w_pensja);
	t_pensja = w_pensja;
	if (!poprawneDane)
		bladNr = 8;

	//cout << "	Podaj date zatrudnienia pracownika: " << endl;	// cin >> w_data_zatr; t_data_zatr = w_data_zatr;
	//	cout << "	Dzien: ";	//	cin >> w_dni;	t_dni = w_dni;
	//	w_dniZatr = filtrDoCalkowitych(w_dniZatr);
	//	t_dniZatr = w_dniZatr;
	//	if (!poprawneDane)
	//		bladNr = 8;

	//	cout << "	Miesiac: ";	//cin >> w_mies;	t_mies = w_mies;
	//	w_miesZatr = filtrDoCalkowitych(w_miesZatr);
	//	t_miesZatr = w_miesZatr;
	//	if (!poprawneDane)
	//		bladNr = 8;

	//	cout << "	Rok: ";		//cin >> w_lata;	t_lata = w_lata;
	//	w_lataZatr = filtrDoCalkowitych(w_lataZatr);
	//	t_lataZatr = w_lataZatr;
	//	if (!poprawneDane)
	//		bladNr = 8;

		w_data_zatr[0] = czasPodzielony.tm_mday / 10 + 48;
		w_data_zatr[1] = czasPodzielony.tm_mday % 10 + 48;
		w_data_zatr[2] = '-';
		w_data_zatr[3] = czasPodzielony.tm_mon / 10 + 48;
		w_data_zatr[4] = czasPodzielony.tm_mon % 10 + 48;
		w_data_zatr[5] = '-';
		w_data_zatr[6] = (czasPodzielony.tm_mon + 1900) / 1000 + 48;
		w_data_zatr[7] = ((czasPodzielony.tm_mon + 1900) - (((czasPodzielony.tm_mon + 1900) / 1000) * 1000)) / 100 + 48;
		w_data_zatr[8] = ((czasPodzielony.tm_mon + 1900) - (((czasPodzielony.tm_mon + 1900) / 100) * 100)) / 10 + 48;
		w_data_zatr[9] = (czasPodzielony.tm_mon + 1900) % 10 + 48;

		t_data_zatr = w_data_zatr;

//		cout << w_data_zatr << endl;

	//cout << "	Podaj date zwolnienia pracownika: " << endl;	//cin >> w_data_zwoln; t_data_zwoln = w_data_zwoln;

	//	cout << "	Dzien: ";	//	cin >> w_dni;	t_dni = w_dni;
	//	w_dniZwoln = filtrDoCalkowitych(w_dniZwoln);
	//	t_dniZwoln = w_dniZwoln;
	//	if (!poprawneDane)
	//		bladNr = 8;

	//	cout << "	Miesiac: ";	//cin >> w_mies;	t_mies = w_mies;
	//	w_miesZwoln = filtrDoCalkowitych(w_miesZwoln);
	//	t_miesZwoln = w_miesZwoln;
	//	if (!poprawneDane)
	//		bladNr = 8;

	//	cout << "	Rok: ";		//cin >> w_lata;	t_lata = w_lata;
	//	w_lataZwoln = filtrDoCalkowitych(w_lataZwoln);
	//	t_lataZwoln = w_lataZwoln;
	//	if (!poprawneDane)
	//		bladNr = 8;

	//	w_data_zwoln[0] = w_dniZwoln / 10 + 48;
	//	w_data_zwoln[1] = w_dniZwoln % 10 + 48;
	//	w_data_zwoln[2] = '-';
	//	w_data_zwoln[3] = w_miesZwoln / 10 + 48;
	//	w_data_zwoln[4] = w_miesZwoln % 10 + 48;
	//	w_data_zwoln[5] = '-';
	//	w_data_zwoln[6] = w_lataZwoln / 1000 + 48;
	//	w_data_zwoln[7] = (w_lataZwoln - ((w_lataZwoln / 1000) * 1000)) / 100 + 48;
	//	w_data_zwoln[8] = (w_lataZwoln - ((w_lataZwoln / 100) * 100)) / 10 + 48;
	//	w_data_zwoln[9] = w_lataZwoln % 10 + 48;

	//	t_data_zwoln = w_data_zwoln;

	cout << "	Podaj date zakonczenia umowy z pracownikiem: " << endl;	//cin >> w_data_zakUmowy; t_data_zakUmowy = w_data_zakUmowy;

		cout << "	Dzien: ";	//	cin >> w_dni;	t_dni = w_dni;
		w_dniZakUm = filtrDoCalkowitych(w_dniZakUm);
		t_dniZakUm = w_dniZakUm;
		if (!poprawneDane)
			bladNr = 8;

		cout << "	Miesiac: ";	//cin >> w_mies;	t_mies = w_mies;
		w_miesZakUm = filtrDoCalkowitych(w_miesZakUm);
		t_miesZakUm = w_miesZakUm;
		if (!poprawneDane)
			bladNr = 8;

		cout << "	Rok: ";		//cin >> w_lata;	t_lata = w_lata;
		w_lataZakUm = filtrDoCalkowitych(w_lataZakUm);
		t_lataZakUm = w_lataZakUm;
		if (!poprawneDane)
			bladNr = 8;

		w_data_zakUmowy[0] = w_dniZakUm / 10 + 48;
		w_data_zakUmowy[1] = w_dniZakUm % 10 + 48;
		w_data_zakUmowy[2] = '-';
		w_data_zakUmowy[3] = w_miesZakUm / 10 + 48;
		w_data_zakUmowy[4] = w_miesZakUm % 10 + 48;
		w_data_zakUmowy[5] = '-';
		w_data_zakUmowy[6] = w_lataZakUm / 1000 + 48;
		w_data_zakUmowy[7] = (w_lataZakUm - ((w_lataZakUm / 1000) * 1000)) / 100 + 48;
		w_data_zakUmowy[8] = (w_lataZakUm - ((w_lataZakUm / 100) * 100)) / 10 + 48;
		w_data_zakUmowy[9] = w_lataZakUm % 10 + 48;

		t_data_zakUmowy = w_data_zakUmowy;

	if (!poprawneDane)
	{
		cout << endl << endl << "			BLAD W DANYCH! (NR BLEDU: " << bladNr << ")";

//							//========== DOKUMENTACJA: =================================\\
//							|| B£¥D NR: || OBJAŒNIENIE:									||
//							||----------||----------------------------------------------||
//							||			||												||
//							\\==========================================================//
		poprawneDane = true;
		_getch();
		return;
	}

//	cout << endl << t_data_zatr << " " << t_data_zwoln << " " << t_data_zakUmowy;
	_getch();
}

void wypiszDanePracownika(int t_pensja, int id_pracownika, string t_data_zatr, string t_data_zwoln, string t_data_zakUmowy)
{
	cout << endl;
	cout << "	 ID PRACOWNIKA:		" << id_pracownika << endl;
	cout << "	 PENSJA:		" << t_pensja << endl;
	cout << "	 DATA ZATRUDNIENIA:	" << t_data_zatr << endl;
	cout << "	 DATA ZWOLNIENIA:	" << t_data_zwoln << endl;
	cout << "	 DATA ZAK. UMOWY:	" << t_data_zakUmowy << endl;


	cout << endl << endl << endl;
	cout << "	WCISNIJ [Enter] ABY POWROCIC.";
	cin.get();
	//system("pause");

}

Pracownik::~Pracownik()
{
}

//--------------------------------------------------KARTA-BIBLIOTECZNA-----------------------------------------------------

class KartaBiblioteczna
	: public Osoba
{
public:
	int idKarty, ilosc_wyp, nieZwrocone, oplaty;
	string data_wazn, wypozyczenia[10];

	KartaBiblioteczna::KartaBiblioteczna(string t_PESEL, int t_dni, int t_mies, int t_lata, string t_imie, string t_nazwisko, 
										 int t_ilosc_wyp, int t_nieZwrocone, int t_oplaty, string t_data_wazn, string t_wypozyczenia[]);
		~KartaBiblioteczna();
private:

};

KartaBiblioteczna::KartaBiblioteczna(string t_PESEL, int t_dni, int t_mies, int t_lata, string t_imie, string t_nazwisko,
										int t_ilosc_wyp, int t_nieZwrocone, int t_oplaty, string t_data_wazn, string t_wypozyczenia[])
	:idKarty(KlicznikID)
	, ilosc_wyp(0)
	, nieZwrocone(0)
	, oplaty(0)
	, data_wazn("01-01-1990")
//	, wypozyczenia(t_wypozyczenia)
	, Osoba(t_PESEL, t_wiek = 0, t_wzrost = 0, t_dni, t_mies, t_lata, t_imie, t_nazwisko, t_adres, t_oczy = "")
{
	ilosc_wyp = t_ilosc_wyp;
	nieZwrocone = t_nieZwrocone;
	oplaty = t_oplaty;
	for (int i = 0; i < 10; i++)
	{
		//cout << t_wypozyczenia[i] << endl;

		wypozyczenia[i] = t_wypozyczenia[i];
 		//cout << i << endl;
	}

	for (int i = 0; i < 11; i++)
	{
		//if (t_data_zatr[i] == '\\0')	break;
		data_wazn[i] = t_data_zatr[i];
	}
	KlicznikID++;
}

void pobierzDaneKarty()
{
	string w_data_wazn = "00-00-0000";
	int w_pensja = 0;
	int w_ilosc_wyp = 0, w_nieZwrocone = 0;
	int w_dniWazn = 0, w_miesWazn = 0, w_lataWazn = 0;


	time_t czas;
	time(&czas);
	tm czasPodzielony = *localtime(&czas);

	cout << endl;


	cout << "	Podaj ilosc wypozyczonych ksiazek: ";	//cin >> w_wiek; t_wiek = w_wiek;
	w_ilosc_wyp = filtrDoCalkowitych(w_ilosc_wyp);
	t_ilosc_wyp = w_ilosc_wyp;
	if (!poprawneDane)
		bladNr = 8;

	cout << "	Podaj ilosc nie zwroconych ksiazek: ";	//cin >> w_wiek; t_wiek = w_wiek;
	w_nieZwrocone = filtrDoCalkowitych(w_nieZwrocone);
	t_nieZwrocone = w_nieZwrocone;
	if (!poprawneDane)
		bladNr = 8;

	//cout << "	Podaj date wazniosci karty: " << endl;	//cin >> w_data_zakUmowy; t_data_zakUmowy = w_data_zakUmowy;

	//cout << "	Dzien: ";	//	cin >> w_dni;	t_dni = w_dni;
	//w_dniWazn = filtrDoCalkowitych(w_dniWazn);
	//t_dniWazn = w_dniWazn;
	//if (!poprawneDane)
	//	bladNr = 8;

	//cout << "	Miesiac: ";	//cin >> w_mies;	t_mies = w_mies;
	//w_miesWazn = filtrDoCalkowitych(w_miesWazn);
	//t_miesWazn = w_miesWazn;
	//if (!poprawneDane)
	//	bladNr = 8;

	//cout << "	Rok: ";		//cin >> w_lata;	t_lata = w_lata;
	//w_lataWazn = filtrDoCalkowitych(w_lataWazn);
	//t_lataWazn = w_lataWazn;
	//if (!poprawneDane)
	//	bladNr = 8;

	//w_data_wazn[0] = w_dniWazn / 10 + 48;
	//w_data_wazn[1] = w_dniWazn % 10 + 48;
	//w_data_wazn[2] = '-';
	//w_data_wazn[3] = w_miesWazn / 10 + 48;
	//w_data_wazn[4] = w_miesWazn % 10 + 48;
	//w_data_wazn[5] = '-';
	//w_data_wazn[6] = w_lataWazn / 1000 + 48;
	//w_data_wazn[7] = (w_lataWazn - ((w_lataWazn / 1000) * 1000)) / 100 + 48;
	//w_data_wazn[8] = (w_lataWazn - ((w_lataWazn / 100) * 100)) / 10 + 48;
	//w_data_wazn[9] = w_lataWazn % 10 + 48;

	//t_data_wazn = w_data_wazn;

	if (!poprawneDane)
	{
		cout << endl << endl << "			BLAD W DANYCH! (NR BLEDU: " << bladNr << ")";

		//							//========== DOKUMENTACJA: =================================\\
		//							|| B£¥D NR: || OBJAŒNIENIE:									||
//									||----------||----------------------------------------------||
//									||			||												||
//									\\==========================================================//
		poprawneDane = true;
		_getch();
		return;
	}

	//	cout << endl << t_data_zatr << " " << t_data_zwoln << " " << t_data_zakUmowy;
	_getch();
}

void wypiszDaneKarty(int id_karty, int t_ilosc_wyp, int t_nieZwrocone, string t_data_wazn)
{
	cout << endl;
	cout << "	 ID KARTY:			" << id_karty << endl;
	cout << "	 WYPOZYCZONE KSIAZKI:		" << t_ilosc_wyp << endl;
	cout << "	 NIEODDANE KSIAZKI:		" << t_nieZwrocone << endl;
	cout << "	 DATA WAZNOSCI KARTY:	" << t_data_wazn << endl;


	cout << endl << endl << endl;
	cout << "	WCISNIJ [Enter] ABY POWROCIC.";
	cin.get();
	//system("pause");

}

KartaBiblioteczna::~KartaBiblioteczna()
{
}

//--------------------------------------------------KSI¥¯KA------------------------------------------------------------

class Ksiazka
{
public:
	Ksiazka(string t_tytul);
	~Ksiazka();

	string tytul, data_wyp, data_odd;
	bool dostepna;
	int id_ksiazki;


private:

};

Ksiazka::Ksiazka(string t_tytul)
	:dostepna(1)
	,id_ksiazki(BlicznikID)
	,data_wyp("00-00-0000")
	,data_odd("00-00-0000")
{

}

Ksiazka::~Ksiazka()
{
}

//------------------------------------------------------------------------------------------------------------------------
//													<<<TABELE>>>
//------------------------------------------------------------------------------------------------------------------------

//--------------------------------------------------PRACOWNICY------------------------------------------------------------

class SpisPracownikow
{
public:
	SpisPracownikow();
	~SpisPracownikow();
	// PRACOWNIKÓW BÊDZIE MAKSYMALNIE 10-CIU

	string pesele[10], lata_p[10], wzrosty[10], daty_ur[10], imiona[10], nazwiska[10], adresy[10], kol_oczu[10];
	string pensje[10], identyfikatory[10], daty_zatr[10], daty_zwoln[10], daty_zakUm[10];

private:

};


SpisPracownikow::SpisPracownikow()
{
	for (int i = 0; i < 10; i++)
		pesele[i] = " ";
	for (int i = 0; i < 10; i++)
		lata_p[i] = " ";
	for (int i = 0; i < 10; i++)
		wzrosty[i] = " ";
	for (int i = 0; i < 10; i++)
		daty_ur[i] = " ";
	for (int i = 0; i < 10; i++)
		imiona[i] = " ";
	for (int i = 0; i < 10; i++)
		nazwiska[i] = " ";
	for (int i = 0; i < 10; i++)
		adresy[i] = " ";
	for (int i = 0; i < 10; i++)
		kol_oczu[i] = " ";
	for (int i = 0; i < 10; i++)
		pensje[i] = " ";
	for (int i = 0; i < 10; i++)
		identyfikatory[i] = i + 48;
	for (int i = 0; i < 10; i++)
		daty_zatr[i] = " ";
	for (int i = 0; i < 10; i++)
		daty_zwoln[i] = " ";
	for (int i = 0; i < 10; i++)	
		daty_zakUm[i] = " ";
}

SpisPracownikow::~SpisPracownikow()
{
}

//--------------------------------------------------KLIENCI----------------------------------------------------------------


class SpisKlientow
{
public:
	SpisKlientow();
	~SpisKlientow();

	string pesele[10], daty_ur[10], imiona[10], nazwiska[10];
	string id_kart[10], ilosc_wypozyczen[10], nie_zwrocenia[10], daty_wazn[10], oplaty_klientow[10];
	string wyp_klientow[10][10];	// -- MAX 10 WYPOZYCZONYCH KSIAZEK, BO NIE MOGLEM 1000 ANI 100

private:

};

SpisKlientow::SpisKlientow()
{
	for (int i = 0; i < 10; i++)
		pesele[i] = "";
	for (int i = 0; i < 10; i++)
		daty_ur[i] = "";
	for (int i = 0; i < 10; i++)
		imiona[i] = "";
	for (int i = 0; i < 10; i++)
		nazwiska[i] = "";
	for (int i = 0; i < 10; i++)
		id_kart[i] = i + 48;
	for (int i = 0; i < 10; i++)
		ilosc_wypozyczen[i] = "";

	for (int j = 0; j < 10; j++)
		for (int i = 0; i < 10; i++)
		{
			wyp_klientow[i][j] = "";
		//	cout << i << j << endl;
		}

	for (int i = 0; i < 10; i++)
		nie_zwrocenia[i] = "";
	for (int i = 0; i < 10; i++)
		daty_wazn[i] = "";
	for (int i = 0; i < 10; i++)
		oplaty_klientow[i] = "";

}

SpisKlientow::~SpisKlientow()
{
}

//--------------------------------------------------KSI¥¯KI--------------------------------------------------------------

class SpisKsiazek
{
public:
	SpisKsiazek();
	~SpisKsiazek();

	string tytuly[100], czy_dost[100], identyfikatory[100], daty_wyp[100], daty_odd[100], id_klientow[100];

private:

};

SpisKsiazek::SpisKsiazek()
{
	for (int i = 0; i < 100; i++)
		tytuly[i] = "";
	for (int i = 0; i < 100; i++)
		czy_dost[i] = "0";
	for (int i = 0; i < 100; i++)
		identyfikatory[i] = i + 48;
	for (int i = 0; i < 100; i++)
		daty_wyp[i] = "";
	for (int i = 0; i < 100; i++)
		daty_odd[i] = "";
	for (int i = 0; i < 100; i++)
		id_klientow[i] = "NIKOGO";



}

SpisKsiazek::~SpisKsiazek()
{
}

//--------------------------------------------------ODCZYT/ZAPIS-----------------------------------------------------------------

SpisKsiazek wczytajKsiazkiZPliku(string nazwaPliku, SpisKsiazek ksiazki)
{
	//cout << "wewnatrz";
	//cin.get();
	ifstream Baza("ksiazki.txt");

	string ciagZnakow = " ";
	char znak = ' ', symbol = ' ';
	int i = 0;


	if (!Baza)
	{
		cout << "BLAD WCZYTANIA PLIKU";
		cin.get();
	//	return;
	}

	while (!Baza.eof() )
	{
		getline(Baza, ciagZnakow);

		while (ciagZnakow[i] != ';' && i != ciagZnakow.length())
		{
			if (Baza.eof())
				break;
			if (ciagZnakow[i] == ',')
				ciagZnakow[i] = '-';
			tytulKsiazki += ciagZnakow[i];

			i++;
		}

		//tytulKsiazki = ciagZnakow;
		cout << BlicznikID << " " << tytulKsiazki << endl;
		//cin.get();
		//Ksiazka ksiazka(tytulKsiazki);

		//ksiazki.tytuly[BlicznikID] = ksiazka.tytul;
		ksiazki.tytuly[BlicznikID] = tytulKsiazki;

		ksiazki.identyfikatory[BlicznikID] = intToStr(BlicznikID);
		ksiazki.czy_dost[BlicznikID] = intToStr(1);
		BlicznikID++;
		tytulKsiazki = " ";
		znak = ' ';
		i = 0;
	//	cout << ".";

	}

	//cin.get();
	//cout << "K";
	//cin.get();
	Baza.close();

//	SpisKsiazek ksiazki;
	return ksiazki;
	//return(0);
}

void zapiszKlientowDoPliku(int iloscKlientow, SpisKlientow Klienci)
{
	bool pierwszy = true;
	ofstream BazaZKlientami;
	BazaZKlientami.open("klienci.txt");

	if (!BazaZKlientami)
	{
		cout << "BLAD WCZYTANIA PLIKU";
		cin.get();
		return;
	}

	for (int i = 2; i <= iloscKlientow+1; i++)
	{
		if(!pierwszy)
			BazaZKlientami << endl;
		pierwszy = false;
		BazaZKlientami << Klienci.pesele			[i] << '|';
		BazaZKlientami << Klienci.daty_ur			[i] << '|';
		BazaZKlientami << Klienci.imiona			[i] << ' ';
		BazaZKlientami << Klienci.nazwiska			[i] << '|';
		BazaZKlientami << Klienci.id_kart			[i] << '|';
		BazaZKlientami << Klienci.ilosc_wypozyczen	[i] << '|';
		BazaZKlientami << Klienci.nie_zwrocenia		[i] << '|';
		BazaZKlientami << Klienci.daty_wazn			[i] << '|';
		BazaZKlientami << Klienci.oplaty_klientow	[i] << '|';

		for (int j = 0; j <= stoi(Klienci.ilosc_wypozyczen[i]); j++)
			BazaZKlientami << Klienci.wyp_klientow[i][j] << '|';

		//if(!BazaZKlientami.eof())		// NIE DZIA£A, NIE WIEM CZEMU :C
		//	BazaZKlientami << endl;

		
	}
	BazaZKlientami.close();
	return;
}

SpisKlientow wczytajKlientowZPliku(string nazwaPliku, SpisKlientow &Klienci)
{
	string linijka = " ";
	string pesel = "", data_ur = "", imie = "", nazwisko = "", id_karty = "",
		ilosc_wyp = "", nie_zwrocone = "", data_wazn = "", oplaty = "",
		wypozyczenia[10] = { "","","","","" ,"" ,"" ,"" ,"" ,"" };

	ifstream BazaKlientow(nazwaPliku + ".txt");

	while (!BazaKlientow.eof())
	{
		pesel = ""; 
		data_ur = ""; 
		imie = ""; 
		nazwisko = ""; 
		id_karty = "";
		ilosc_wyp = ""; 
		nie_zwrocone = ""; 
		data_wazn = ""; 
		oplaty = "";
		int i = 0;
		for (int n = 0; n < 10; n++)
			wypozyczenia[n] = "";

		getline(BazaKlientow, linijka);

		while (linijka[i] != '|')
		{
			pesel += linijka[i];
			i++;
		}	i++;	Klienci.pesele			[KlicznikID+1] = pesel;
		while (linijka[i] != '|')
		{
			data_ur += linijka[i];
			i++;
		}	i++;	Klienci.daty_ur			[KlicznikID + 1] = data_ur;
		while (linijka[i] != ' ')
		{
			imie += linijka[i];
			i++;
		}	i++;	Klienci.imiona			[KlicznikID + 1] = imie;
		while (linijka[i] != '|')
		{
			nazwisko += linijka[i];
			i++;
		}	i++;	Klienci.nazwiska		[KlicznikID + 1] = nazwisko;
		while (linijka[i] != '|')
		{
			id_karty += linijka[i];
		//	id_karty = KlicznikID + 48;
			i++;
		}	i++;	Klienci.id_kart			[KlicznikID + 1] = id_karty;
		while (linijka[i] != '|')
		{
			ilosc_wyp += linijka[i];
			i++;
		}	i++;	Klienci.ilosc_wypozyczen[KlicznikID + 1] = ilosc_wyp;
		while (linijka[i] != '|')
		{
			nie_zwrocone += linijka[i];
			i++;
		}	i++;	Klienci.nie_zwrocenia	[KlicznikID + 1] = nie_zwrocone;
		while (linijka[i] != '|')
		{
			data_wazn += linijka[i];
			i++;
		}	i++;	Klienci.daty_wazn		[KlicznikID + 1] = data_wazn;
		while (linijka[i] != '|')
		{
			oplaty += linijka[i];
			i++;
		}	i++;	Klienci.oplaty_klientow	[KlicznikID + 1] = oplaty;

		for (int j = 0; j < 10; j++)
		{
			while (linijka[i] != '|')
			{
				wypozyczenia[j] += linijka[i];
				i++;
			}	i++;	Klienci.wyp_klientow[KlicznikID + 1][j] = wypozyczenia[j];
		//	cout << Klienci.wyp_klientow[KlicznikID][j] << endl;
			if (i == linijka.length())
				break;
		}

		KlicznikID++;
		cin.get();
	}

	BazaKlientow.close();
	return Klienci;
}

void zapiszPracownikowDoPliku(int iloscPracownikow, SpisPracownikow Pracownicy)
{
	bool pierwszy = true;
	ofstream BazaZPracownikami;
	BazaZPracownikami.open("robole.txt");

	if (!BazaZPracownikami)
	{
		cout << "BLAD WCZYTANIA PLIKU";
		cin.get();
		return;
	}

	for (int i = 2; i <= iloscPracownikow + 1; i++)
	{
		//string pesele[10], lata_p[10], wzrosty[10], daty_ur[10], imiona[10], nazwiska[10], adresy[10], kol_oczu[10];
		//string pensje[10], identyfikatory[10], daty_zatr[10], daty_zwoln[10], daty_zakUm[10];

		if (!pierwszy)
			BazaZPracownikami << endl;
		pierwszy = false;
		BazaZPracownikami << Pracownicy.pesele[i] << '|';
		BazaZPracownikami << Pracownicy.lata_p[i] << '|';
		BazaZPracownikami << Pracownicy.wzrosty[i] << '|';
		BazaZPracownikami << Pracownicy.daty_ur[i] << '|';
		BazaZPracownikami << Pracownicy.imiona[i] << '|';
		BazaZPracownikami << Pracownicy.nazwiska[i] << '|';
		BazaZPracownikami << Pracownicy.adresy[i] << '|';
		BazaZPracownikami << Pracownicy.kol_oczu[i] << '|';
		BazaZPracownikami << Pracownicy.pensje[i] << '|';
		BazaZPracownikami << Pracownicy.identyfikatory[i] << '|';
		BazaZPracownikami << Pracownicy.daty_zatr[i] << '|';
		BazaZPracownikami << Pracownicy.daty_zwoln[i] << '|';
		BazaZPracownikami << Pracownicy.daty_zakUm[i] << '|';

	}
	BazaZPracownikami.close();
	return;
}

SpisPracownikow wczytajPracownikowZPliku(string nazwaPliku, SpisPracownikow &Pracownicy)
{
	string linijka = " ";
	//string pesel = "", data_ur = "", imie = "", nazwisko = "", id_karty = "",
	//	ilosc_wyp = "", nie_zwrocone = "", data_wazn = "", oplaty = "",
	//	wypozyczenia[10] = { "","","","","" ,"" ,"" ,"" ,"" ,"" };
	string pesel = "", wiek = "", wzrost = "", data_ur = "", imie = "", nazwisko = "", adres = "", oczy = "";
	string pensja = "", identyfikator = "", data_zatr = "", data_zwoln = "", data_zakUm = "";

	ifstream BazaPracownikow(nazwaPliku + ".txt");

	while (!BazaPracownikow.eof())
	{
		pesel = "";
		wiek = "";
		wzrost = "";
		data_ur = "";
		imie = "";
		nazwisko = "";
		adres = "";
		oczy = "";
		pensja = "";
		identyfikator = "";
		data_zatr = "";
		data_zwoln = "";
		data_zakUm = "";

		int i = 0;


		getline(BazaPracownikow, linijka);
		cout << "start "<< endl;
		cout << "1 " << endl;
		while (linijka[i] != '|')
		{
			pesel += linijka[i];
			i++;
		}	i++;	Pracownicy.pesele[PlicznikID + 1] = pesel;
		cout << "2 " << endl;
		while (linijka[i] != '|')
		{
			wiek += linijka[i];
			i++;
		}	i++;	Pracownicy.lata_p[PlicznikID + 1] = wiek;
		cout << "3 " << endl;
		while (linijka[i] != '|')
		{
			nazwisko += linijka[i];
			i++;
		}	i++;	Pracownicy.wzrosty[PlicznikID + 1] = wzrost;		cout << "4 " << endl;
		while (linijka[i] != '|')
		{
			data_ur += linijka[i];
			i++;
		}	i++;	Pracownicy.daty_ur[PlicznikID + 1] = data_ur;		cout << "5 " << endl;
		while (linijka[i] != '|')
		{
			imie += linijka[i];
			i++;
		}	i++;	Pracownicy.imiona[PlicznikID + 1] = imie;		cout << "6 " << endl;
		while (linijka[i] != '|')
		{
			nazwisko += linijka[i];
			i++;
		}	i++;	Pracownicy.nazwiska[PlicznikID + 1] = nazwisko;		cout << "7 " << endl;
		while (linijka[i] != '|')
		{
			adres += linijka[i];
			i++;
		}	i++;	Pracownicy.adresy[PlicznikID + 1] = adres;		cout << "8 " << endl;
		while (linijka[i] != '|')
		{
			oczy += linijka[i];
			i++;
		}	i++;	Pracownicy.kol_oczu[PlicznikID + 1] = oczy;		cout << "9 " << endl;
		while (linijka[i] != '|')
		{
			pensja += linijka[i];
			i++;
		}	i++;	Pracownicy.pensje[PlicznikID + 1] = pensja;		cout << "10 " << endl;
		while (linijka[i] != '|')
		{
			identyfikator += linijka[i];
			i++;
		}	i++;	Pracownicy.identyfikatory[PlicznikID + 1] = identyfikator;		cout << "11 " << endl;
		while (linijka[i] != '|')
		{
			data_zatr += linijka[i];
			i++;
		}	i++;	Pracownicy.daty_zatr[PlicznikID + 1] = data_zatr;		cout << "12 " << endl;
		while (linijka[i] != '|')
		{
			data_zwoln += linijka[i];
			i++;
		}	i++;	Pracownicy.daty_zwoln[PlicznikID + 1] = data_zwoln;		cout << "13 " << endl;
		while (linijka[i] != '|')
		{
			data_zakUm += linijka[i];
			i++;
		}	i++;	Pracownicy.daty_zakUm[PlicznikID + 1] = data_zakUm;		
		cout << "koniec" << endl;
		PlicznikID++;
		cin.get();
	}

	BazaPracownikow.close();
	return Pracownicy;
}

//--------------------------------------------------RESZTA-----------------------------------------------------------------

void wypiszDane(string w_PESEL, int t_wiek, int t_wzrost, int t_dni, int t_mies, int t_lata, string t_imie,
	string t_nazwisko, char t_adres[1000], string t_oczy)
{
	cout << endl;
	cout << "	 PESEL:		" << w_PESEL << endl;
	cout << "	 LAT:		" << t_wiek << endl;
	cout << "	 WZROST:	" << t_wzrost << endl;
	cout << "	 DATA UR.:	" << t_dni << "-" << t_mies << "-" << t_lata << endl;
	cout << "	 NAZYWA SIE:	" << t_imie << " " << t_nazwisko << endl;
	cout << "	 ADRES:		" << t_adres << endl;
	cout << "	 OCZY:		" << t_oczy << endl;

	cout << endl << endl << endl;
	cout << "	WCISNIJ [Enter] ABY POWROCIC.";
	cin.get();
	//system("pause");

}

void zmienDane(char idDanej)
{
	string w_PESEL = "not set    ", w_imie, w_nazwisko, w_oczy, strLata = "00", strDni = "00", strMies = "00";
	string daneWStr;
	int w_wiek = 0, w_wzrost = 0, w_dni = 0, w_mies = 0, w_lata = 0, testWieku;
	char w_adres[1000];

	time_t czas;
	time(&czas);
	tm czasPodzielony = *localtime(&czas);

	cout << endl;

	switch (idDanej)
	{
		case 48:
			cout << "	Podaj PESEL osoby: ";

			for (int i = 0; i < 11; i++)
			{
				w_PESEL[i] = _getch();		cout << w_PESEL[i];

				if (w_PESEL[i] == 13)
				{
					cout << endl << endl << "			ZBYT KROTKI PESEL!";
					w_PESEL = t_PESEL;
					_getch();
					return;
				}

				if (w_PESEL[i] < 48 || w_PESEL[i] > 57)
				{
					cout << endl << endl << "			PESEL MOZE ZAWIERAC TYLKO CYFRY!";
					w_PESEL = t_PESEL;
					_getch();
					return;
				}
			}

			cout << endl;
			t_PESEL = w_PESEL;
			_getch();
			break;

		case 49:
			cout << "	Podaj wiek osoby: ";	//cin >> w_wiek; t_wiek = w_wiek;
			w_wiek = filtrDoCalkowitych(w_wiek);
			t_wiek = w_wiek;
			if (!poprawneDane)
				bladNr = 8;
			break;

		case 50:
			cout << "	Podaj wzrost osoby: ";	//cin >> w_wzrost; t_wzrost = w_wzrost;
			w_wzrost = filtrDoCalkowitych(w_wzrost);
			t_wzrost = w_wzrost;
			if (!poprawneDane)
				bladNr = 8;
			if (w_wzrost < 50 || !poprawneDane)
			{
				cout << endl << endl << w_wzrost << "			COS NIE TAK ZE WZROSTEM :P";
				w_wzrost = t_wzrost;
				_getch();
				return;
			}
			break;
		case 51:
			cout << "	Podaj date urodzenia osoby" << endl; //cin >> w_lata;

			cout << "	Dzien: ";	//	cin >> w_dni;	t_dni = w_dni;
			w_dni = filtrDoCalkowitych(w_dni);
			t_dni = w_dni;
			if (!poprawneDane)
				bladNr = 8;

			cout << "	Miesiac: ";	//cin >> w_mies;	t_mies = w_mies;
			w_mies = filtrDoCalkowitych(w_mies);
			t_mies = w_mies;
			if (!poprawneDane)
				bladNr = 8;

			cout << "	Rok: ";		//cin >> w_lata;	t_lata = w_lata;
			w_lata = filtrDoCalkowitych(w_lata);
			t_lata = w_lata;
			if (!poprawneDane)
				bladNr = 8;



			if (w_lata >= 2000)
			{
				strLata[0] = (w_lata - 2000) / 10 + 48;
				strLata[1] = (w_lata - 2000) % 10 + 48;
			}
			else
			{
				strLata[0] = (w_lata - 1900) / 10 + 48; //  = 
				strLata[1] = (w_lata - 1900) % 10 + 48;
			}

			strDni[0] = (w_dni / 10) + 48;
			strDni[1] = (w_dni % 10) + 48;

			strMies[0] = (w_mies / 10) + 48;
			strMies[1] = (w_mies % 10) + 48;

			testWieku = 2016 - w_lata;

			if (strLata[0] != t_PESEL[0] || strLata[1] != t_PESEL[1])
			{
				poprawneDane = false;
				bladNr = 1;
			}
			if (strMies[0] != t_PESEL[2] || strMies[1] != t_PESEL[3])
			{
				poprawneDane = false;
				bladNr = 2;
			}
			if (strDni[0] != t_PESEL[4] || strDni[1] != t_PESEL[5])
			{
				poprawneDane = false;
				bladNr = 3;
			}

			if (testWieku != t_wiek && testWieku != t_wiek + 1)
			{
				poprawneDane = false;
				bladNr = 4;
			}

			if ((w_mies == 1 && w_dni > 31)
				|| (w_mies == 2 && w_lata % 4 == 0 && w_dni > 29)
				|| (w_mies == 2 && w_lata % 4 != 0 && w_dni > 28)
				|| (w_mies == 3 && w_dni > 31)
				|| (w_mies == 4 && w_dni > 30)
				|| (w_mies == 5 && w_dni > 31)
				|| (w_mies == 6 && w_dni > 30)
				|| (w_mies == 7 && w_dni > 31)
				|| (w_mies == 8 && w_dni > 31)
				|| (w_mies == 9 && w_dni > 30)
				|| (w_mies == 10 && w_dni > 31)
				|| (w_mies == 11 && w_dni > 30)
				|| (w_mies == 12 && w_dni > 31)
				)
			{
				poprawneDane = false;
				bladNr = 5;
			}

			if (w_mies < 1 || w_mies > 12 || w_dni < 1 || w_lata < 1900 || w_lata > 2016)
			{
				poprawneDane = false;
				bladNr = 6;
			}

			if (w_lata > czasPodzielony.tm_year + 1900)
			{
				poprawneDane = false;
				bladNr = 7;
			}
			else
				if (w_lata == czasPodzielony.tm_year + 1900 && w_mies > czasPodzielony.tm_mon + 1)
				{
					poprawneDane = false;
					bladNr = 7;
				}
				else
					if (w_lata == czasPodzielony.tm_year + 1900 && w_mies == czasPodzielony.tm_mon + 1 && w_dni > czasPodzielony.tm_mday)
					{
						poprawneDane = false;
						bladNr = 7;
					}
			break;

		case 52:
			cout << "	Podaj imie osoby: ";		cin >> w_imie; t_imie = w_imie;
				break;
		case 53:
			cout << "	Podaj nazwisko osoby: ";	cin >> w_nazwisko; t_nazwisko = w_nazwisko; cin.get();
			break;
		case 54:
			cout << "	Podaj adres osoby: ";		cin.getline(w_adres, 1000);
			for (int i = 0; i < 1000; i++)
			{
				if (w_adres[i] == '\\0')	break;
				t_adres[i] = w_adres[i];
			}
			break;
		case 55:
			cout << "	Podaj kolor oczu osoby: "; cin >> w_oczy; t_oczy = w_oczy;
			break;

	default:
		break;
	}

	if (!poprawneDane)
	{
		cout << endl << endl << "			BLAD W DANYCH! (NR BLEDU: " << bladNr << ")";

		poprawneDane = true;
		_getch();
		return;
	}
	
	_getch();
}

void Osoba::wyswietlDane(int idDanej, Osoba &obywatel)
{
	// 0 - PESEL
	// 1 - wiek
	// 2 - wzrost
	// 3 - data urodzenia
	// 4 - imiê
	// 5 - nazwisko
	// 6 - adres
	// 7 - oczy

	if (idDanej == 0)
	{
		cout << "PESEL obywatela: " << obywatel.PESEL << endl;
	}
	else
		if (idDanej == 1)
		{
			cout << "Wiek obywatela: " << obywatel.wiek << endl;
		}
		else
			if (idDanej == 2)
			{
				cout << "Wzrost obywatela: " << obywatel.wzrost << endl;
			}
			else
				if (idDanej == 3)
				{
					cout << "Data urodzenia obywatela: " << obywatel.dni << "-" << obywatel.mies << "-" << obywatel.lata <<  endl;
				}
				else
					if (idDanej == 4)
					{
						cout << "Imie obywatela: " << obywatel.imie << endl;
					}
					else
						if (idDanej == 5)
						{
							cout << "Nazwisko obywatela: " << obywatel.nazwisko << endl;
						}
						else
							if (idDanej == 6)
							{
								cout << "Adres obywatela: " << obywatel.adres << endl;
							}
							else
								if (idDanej == 7)
								{
									cout << "Kolor oczu obywatela: " << obywatel.oczy << endl;
								}
								else
								{
									cout << idDanej << "to z³y parametr do wyswietlenia. " << endl;
									//cout << idDanej;

								}


}

void Osoba::pokazAdresowe(Osoba obywatel)
{
	cout << "Dane adresowe obywatela: " << endl;	
	obywatel.wyswietlDane(4, obywatel);	// --- IMIÊ
	obywatel.wyswietlDane(5, obywatel);	// --- NAZWISKO
	obywatel.wyswietlDane(6, obywatel);	// --- ADRES

	cout << endl;
	cin.get();
	system("pause");
}

void pokazWszystko(Osoba obywatel)
{
	obywatel.wyswietlDane(0, obywatel);	
	obywatel.wyswietlDane(1, obywatel);	
	obywatel.wyswietlDane(2, obywatel);	
	obywatel.wyswietlDane(3, obywatel);	
	obywatel.wyswietlDane(4, obywatel);	
	obywatel.wyswietlDane(5, obywatel);	
	obywatel.wyswietlDane(6, obywatel);	
	obywatel.wyswietlDane(7, obywatel);	
	cout << endl;
	cin.get();
	system("pause");
}

void prawnoscPESELu(KartaBiblioteczna Klient)
{
	int suma, ostCyfra, cyfKontr;
	char cyfPESELU[11];
	int intCyfPESELU[11];

	for (int i = 0; i < 11; i++)
		intCyfPESELU[i] = stoi(Klient.PESEL) - 48;


	suma = intCyfPESELU[0] + intCyfPESELU[1] * 3 + intCyfPESELU[2] * 7 + intCyfPESELU[3] * 9
		+ intCyfPESELU[4] + intCyfPESELU[5] * 3 + intCyfPESELU[6] * 7 + intCyfPESELU[7] * 9
		+ intCyfPESELU[8] + intCyfPESELU[9] * 3;
	ostCyfra = suma % 10;
	cyfKontr = 10 - ostCyfra;

	if (cyfKontr == intCyfPESELU[10])
	{
		cout << "PESEL JEST POPRAWNY. " << endl;
		cin.get();
		system("cls");
	}

	else
	{
		cout << "PESEL JEST NIEPOPRAWNY. " << endl;
		cout << endl;
		cout << "Poprawna cyfra kontrolna: " << cyfKontr << endl;
		cout << "Aktualna cyfra kontrolna: " << Klient.PESEL[10] << endl;
		//cout << intCyfPESELU;
		cout << endl;
		//obywatel.zmienDane(0, obywatel);
		cout << "Czy chcesz zmienic cyfre na poprawna?" << endl;
		cout << "     [T] TAK              [N] NIE " << endl;
		if (_getch() == 't')
		Klient.PESEL[10] = cyfKontr + 48;

		system("cls");


	}
}

string intToStr(int n)
{
	string napis;
	if (n < 0) {
		napis = "-";
		n = -n;
	}
	if (n > 9)
		napis += intToStr(n / 10);
	napis += n % 10 + 48;
	return napis;
}

int main()
{
	time_t czas;
	time(&czas);
	tm czasPodzielony = *localtime(&czas);

	//Osoba osoba;
	Osoba osoba(t_PESEL, t_wiek, t_wzrost, t_dni, t_mies, t_lata, t_imie, t_nazwisko, t_adres, t_oczy);
	Pracownik robol(t_PESEL, t_wiek, t_wzrost, t_dni, t_mies, t_lata, t_imie, t_nazwisko, t_adres,
					t_oczy, t_pensja, t_data_zatr, t_data_zwoln, t_data_zakUmowy);
	KartaBiblioteczna karta(t_PESEL, t_dni, t_mies, t_lata, t_imie, t_nazwisko, t_ilosc_wyp, t_nieZwrocone, t_oplaty, t_data_wazn, t_wypozyczenia);


	SpisPracownikow zbiorPracownikow;
	cin.get();
	SpisKlientow zbiorKlientow;

	SpisKsiazek zbiorKsiazek;
	//cout << "not wczytane";
	//cin.get();
	zbiorKsiazek = wczytajKsiazkiZPliku("ksiazki", zbiorKsiazek);
//	cout << KlicznikID; cin.get();
	zbiorKlientow = wczytajKlientowZPliku("klienci", zbiorKlientow);
	zbiorPracownikow = wczytajPracownikowZPliku( "robole", zbiorPracownikow);
	//cout << "KUTAS";
//	cout << KlicznikID; cin.get();
	system("cls");

	int wybor;
	do
	{
		osoba.PESEL = t_PESEL;
		osoba.wiek = t_wiek;
		osoba.wzrost = t_wzrost;
		osoba.dni = t_dni;
		osoba.mies = t_mies;
		osoba.lata = t_lata;

		for (int i = 0; i < 1000; i++)
		{
			if (t_adres[i] == '\\0')	break;
			osoba.adres[i] = t_adres[i];
		}
		osoba.imie = t_imie;
		osoba.nazwisko = t_nazwisko;
		osoba.oczy = t_oczy;

		robol.pensja = t_pensja;
		robol.id_pracownika = PlicznikID;
		for (int i = 0; i < 11; i++)
			robol.data_zatr[i] = t_data_zatr[i];
		
		for (int i = 0; i < 11; i++)
			robol.data_zwoln[i] = t_data_zwoln[i];

		for (int i = 0; i < 11; i++)
			robol.data_zakUmowy[i] = t_data_zakUmowy[i];

		karta.ilosc_wyp = t_ilosc_wyp;
		karta.nieZwrocone = t_nieZwrocone;
		karta.idKarty = KlicznikID;


		for (int i = 0; i < 11; i++)
			karta.data_wazn[i] = t_data_wazn[i];

		//for (int j = 0; j < 10; j++)
		//	for (int i = 0; i < 1000; i++)
		//		karta.wypozyczenia[i][j] = t_wypozyczenia[i][j];


		if (trybAdmina)
		{
			do
			{
				system("cls");;
				cout << endl;
				cout << "			CO CHCESZ ZROBIC?" << endl;
				cout << "			-----------------" << endl;
				cout << endl;
				cout << "	[0] -> DODAJ KLIENTA" << endl;
				cout << "	[1] -> ZNAJDZ KLIENTA W BAZIE" << endl;
				cout << "	[2] -> USUN KLIENTA " << endl;
				cout << "	[3] -> POKAZ WSZYSTKICH KLIENTOW" << endl;
				cout << "	[4] -> ZMIEN DANE KLIENTA" << endl;
				cout << endl;
				cout << "	[5] -> WYPOZYCZENIE" << endl;
				cout << "	[6] -> ODDANIE" << endl;
				cout << "	[7] -> ZNAJDZ KSIAZKE W BAZIE" << endl;
				cout << "	[B] -> WYSWIETL SPIS KSIAZEK" << endl;


			//	cout << endl;
				cout << endl;
				cout << "	[S] -> ZAPISZ ZMIANY" << endl;
				cout << endl;
				//=========ADMINISTRATORSKIE===========================
				cout << "	[8] -> DODAJ PRACOWNIKA" << endl;
				cout << "	[9] -> ZWOLNIJ PRACOWNIKA" << endl;
				cout << "	[A] -> ZMIEN DANE PRACOWNIKA" << endl;
				cout << "	[C] -> POKAZ WSZYSTKICH PRACOWNIKOW" << endl;

				//=====================================================
				cout << endl;
				cout << "	[X] -> WYJDZ Z PROGRAMU" << endl;

			//	cout << endl;
				cout << endl;
				cout << "	> ";
				wybor = _getch();

			} while (
				wybor != (int)'0' &&
				wybor != (int)'1' &&
				wybor != (int)'2' &&
				wybor != (int)'3' &&
				wybor != (int)'4' &&
				wybor != (int)'5' &&
				wybor != (int)'6' &&
				wybor != (int)'7' &&
				wybor != (int)'8' &&
				wybor != (int)'9' &&
				wybor != (int)'a' &&
				wybor != (int)'b' &&
				wybor != (int)'c' &&

				wybor != (int)'s' &&


				wybor != (int)'x');

			system("cls");

			switch (wybor)
			{
			case '0':		// NOWY KLIENT
			{
				czyKarta = true;
				pobierzDaneOsoby();
				czyKarta = false;

				if (poprawneDane)
				{
					pobierzDaneKarty();

					KartaBiblioteczna karta(t_PESEL, t_dni, t_mies, t_lata, t_imie, t_nazwisko, t_ilosc_wyp,
						t_nieZwrocone, t_oplaty, t_data_wazn, t_wypozyczenia);
					//string rokWaznosci = czasPodzielony.tm_year;

					zbiorKlientow.pesele[KlicznikID] = karta.PESEL;
					zbiorKlientow.daty_ur[KlicznikID] = intToStr(karta.dni) + "-" + intToStr(karta.mies)
						+ "-" + intToStr(karta.lata);
					zbiorKlientow.imiona[KlicznikID] = karta.imie;
					zbiorKlientow.nazwiska[KlicznikID] = karta.nazwisko;
					zbiorKlientow.ilosc_wypozyczen[KlicznikID] = intToStr(karta.ilosc_wyp);
					zbiorKlientow.nie_zwrocenia[KlicznikID] = intToStr(karta.nieZwrocone);
					zbiorKlientow.oplaty_klientow[KlicznikID] = intToStr(karta.oplaty);
					zbiorKlientow.daty_wazn[KlicznikID] = intToStr(czasPodzielony.tm_mday) + '-'
						+ intToStr(czasPodzielony.tm_mon) + "-20" + intToStr(czasPodzielony.tm_year - 100 + 2);

					for (int i = 0; i < 10; i++)
					{
						zbiorKlientow.wyp_klientow[KlicznikID][i] = " ";
					}

					//cout << karta.imie << " " << karta.adres << " " << karta.idKarty << endl;
					//cout << zbiorKlientow.imiona[KlicznikID] << " " << "jakis adres" << zbiorKlientow.id_kart[KlicznikID] << endl;
					//_getch();
				}

				poprawneDane = true;
			}
				break;
			case '1':		// ZNAJD KLIENTA
			{
				int identyfikator;
				do
				{
					identyfikator = 0;
					cout << "PODAJ IDENTYFIKATOR KLIENTA: ";
					cin >> identyfikator;
					system("cls");

				} while (identyfikator >= KlicznikID && identyfikator <= 0);

				cout << zbiorKlientow.id_kart[identyfikator] << "  | "
					<< zbiorKlientow.imiona[identyfikator] << " "
					<< zbiorKlientow.nazwiska[identyfikator] << endl;
				cout << "--------------------------------------------" << endl;
				cout << "Wisi nam				" << zbiorKlientow.oplaty_klientow[identyfikator] << " zl" << endl;
				cout << "Wypozyczyl:				" << zbiorKlientow.ilosc_wypozyczen[identyfikator] << endl;
				cout << "Nie oddal:				" << zbiorKlientow.nie_zwrocenia[identyfikator] << endl;
				cout << "PESEL:				" << zbiorKlientow.pesele[identyfikator] << endl;
				cout << "Urodzony			" << zbiorKlientow.daty_ur[identyfikator] << endl;
				cout << "Urodzony			" << zbiorKlientow.daty_ur[identyfikator] << endl;
				cout << "Wypozyczone ksiazki: ";
				for (int i = 0; i < 10; i++)
					cout << zbiorKlientow.wyp_klientow[KlicznikID][i] << endl;


				_getch();

			}
				break;
			case '2':		// USUÑ KLIENTA 
			{
				int identyfikator;
				do
				{
					identyfikator = 0;
					cout << "PODAJ IDENTYFIKATOR KLIENTA: ";
					cin >> identyfikator;
					system("cls");

				} while (identyfikator >= KlicznikID && identyfikator <= 0);

				zbiorKlientow.pesele[identyfikator] = "";
				zbiorKlientow.daty_ur[identyfikator] = "";
				zbiorKlientow.imiona[identyfikator] = "";
				zbiorKlientow.nazwiska[identyfikator] = "";
				zbiorKlientow.id_kart[identyfikator] = intToStr(-1);
				zbiorKlientow.ilosc_wypozyczen[identyfikator] = "";

				for (int j = 0; j < 10; j++)
					zbiorKlientow.wyp_klientow[identyfikator][j] = "";


				zbiorKlientow.nie_zwrocenia[identyfikator] = "";
				zbiorKlientow.daty_wazn[identyfikator] = "";
				zbiorKlientow.oplaty_klientow[identyfikator] = "";

			}
				break;
			case '3':		// WYŒWIETL WSZYSTKICH KLIENTÓW
			{
				cout << "ID | IMIE I NAZWISKO" << endl;
				//cout << KlicznikID << endl;
				//_getch();
				for (int i = 2; i < KlicznikID + 1; i++)
				{
					if (stoi(zbiorKlientow.id_kart[i]) == -1)
					{

					}
					else
					{
						cout << "============================================" << endl;
						cout << zbiorKlientow.id_kart[i] << "  | "
							<< zbiorKlientow.imiona[i] << " "
							<< zbiorKlientow.nazwiska[i] << endl;
						cout << "--------------------------------------------" << endl;
						cout << "Wisi nam				" << zbiorKlientow.oplaty_klientow[i] << " zl" << endl;
						cout << "Wypozyczyl:				" << endl
							<< "  Ilosc:				" << zbiorKlientow.ilosc_wypozyczen[i] << endl
							<< "  Ksiazki: " << endl;
						for (int j = 1; j <= stoi(zbiorKlientow.ilosc_wypozyczen[i]); j++)
							cout << "	- " << zbiorKlientow.wyp_klientow[i][j] << endl;

						cout << endl;
						cout << "Nie oddal:				" << zbiorKlientow.nie_zwrocenia[i] << endl;
						cout << "Data waznosci karty:		" << zbiorKlientow.daty_wazn[i] << endl;
						cout << "PESEL:				" << zbiorKlientow.pesele[i] << endl;
						cout << "Urodzony			" << zbiorKlientow.daty_ur[i] << endl;
					}

				}
				cin.get();
			}
				break;
			case '4':		// WYŒWIETL WYBRANE DANE KLIENTA (DO DOPRACOWANIA)
			{
				cout << "CO CHCESZ WYSWIETLIC?" << endl;
				cout << endl;
				cout << "[0] -> PESEL" << endl;
				cout << "[1] -> WIEK" << endl;
				cout << "[2] -> WZROST" << endl;
				cout << "[3] -> DATE URODZENIA" << endl;
				cout << "[4] -> IMIE" << endl;
				cout << "[5] -> NAZWISKO" << endl;
				cout << "[6] -> ADRES" << endl;
				cout << "[7] -> KOLOR OCZU" << endl;
				cout << endl;
				cout << endl;

				char opcja = _getch();

				switch (opcja)
				{
				case 48:
					cout << osoba.PESEL;
					cin.get(); break;
				case 49:
					cout << osoba.wiek;
					cin.get(); break;
				case 50:
					cout << osoba.wzrost;
					cin.get(); break;
				case 51:
					cout << osoba.dni << "-" << osoba.mies << "-" << osoba.lata << endl;
					cin.get(); break;
				case 52:
					cout << osoba.imie;
					cin.get(); break;
				case 53:
					cout << osoba.nazwisko;
					cin.get(); break;
				case 54:
					cout << osoba.adres;
					cin.get(); break;
				case 55:
					cout << osoba.oczy;
					cin.get(); break;

				default:
					cout << "Zla dana. " << endl;
					system("pause");
					break;
				}
			}
				break;
			case '5':		// WYPOZYCZENIE
			{
				int Kidentyfikator;
				int Bidentyfikator;
				do
				{
					Kidentyfikator = 0;
					cout << "PODAJ IDENTYFIKATOR KLIENTA: ";
					cin >> Kidentyfikator;
					system("cls");

				} while (Kidentyfikator >= KlicznikID && Kidentyfikator <= 0);



				cin.get();

				cout << "=========================================================================" << endl;

				for (int i = 0; i < BlicznikID; i++)
				{

					cout << "| ID: " << zbiorKsiazek.identyfikatory[i] << " | " << "WYPOZYCZONE PRZEZ: "
						<< zbiorKsiazek.id_klientow[i] << endl;
					cout << "| " << zbiorKsiazek.czy_dost[i] << "	 | " << zbiorKsiazek.tytuly[i] << endl;
					cout << "|-----------------------------------------------------------------------|" << endl;

					//		        Wies³aw Myœliwski, Kamieñ na kamieniu lub Antoni Libera - Madame;



				}
				cout << "=========================================================================" << endl;

				cin.get();

				do
				{
					Bidentyfikator = 0;
					cout << "PODAJ IDENTYFIKATOR KSIAZKI: ";
					cin >> Bidentyfikator;
					system("cls");

				} while (Kidentyfikator >= KlicznikID && Kidentyfikator <= 0);

				int moment;

				cout << zbiorKlientow.imiona[Kidentyfikator] << " " << zbiorKlientow.nazwiska[Kidentyfikator]
					<< " wypozycza" << zbiorKsiazek.tytuly[Bidentyfikator] << "." << endl;
				cout << "Zatwierdzic?" << endl
					<< "	[T] TAK			[N] NIE" << endl;
				if (_getch() == 't')
				{
					cout << zbiorKlientow.ilosc_wypozyczen[Kidentyfikator];
					moment = stoi(zbiorKlientow.ilosc_wypozyczen[Kidentyfikator]);
					moment++;	// - przechowuje iloœæ wpo¿tczonych ksia¿ek danego klienta
					zbiorKlientow.ilosc_wypozyczen[Kidentyfikator] = intToStr(moment);

					//		zbiorKlientow.wyp_klientow[Kidentyfikator][moment] = intToStr(Bidentyfikator);
					zbiorKlientow.wyp_klientow[Kidentyfikator][moment] = zbiorKsiazek.tytuly[Bidentyfikator];

					zbiorKsiazek.czy_dost[Bidentyfikator] = 48; // 0
					zbiorKsiazek.id_klientow[Bidentyfikator] = intToStr(Kidentyfikator);
					zbiorKsiazek.daty_odd[Bidentyfikator] = intToStr(czasPodzielony.tm_mday)
						+ '-'
						+ intToStr(czasPodzielony.tm_mon + 3)
						+ '-'
						+ intToStr(czasPodzielony.tm_year + 1900);

					system("cls");
					cout << "WYPOZYCZONO POMYSLNIE.";
				}




				_getch();
			}
				break;
			case '6':		// ODDANIE
			{
				int Kidentyfikator;
				int Bidentyfikator;
				int moment;
				int ktoraZKolei = 0;
				string tytulKsiazki;

				do
				{
					Kidentyfikator = 0;
					cout << "PODAJ IDENTYFIKATOR KLIENTA: ";
					cin >> Kidentyfikator;
					system("cls");

				} while (Kidentyfikator >= KlicznikID && Kidentyfikator <= 0);

				cin.get();

				cout << "=========================================================================" << endl;

				for (int i = 0; i < BlicznikID; i++)
				{

					cout << "| ID: " << zbiorKsiazek.identyfikatory[i] << " | " << "WYPOZYCZONE PRZEZ: "
						<< zbiorKsiazek.id_klientow[i] << endl;
					cout << "| " << zbiorKsiazek.czy_dost[i] << "	 | " << zbiorKsiazek.tytuly[i] << endl;
					cout << "|-----------------------------------------------------------------------|" << endl;

					//		        Wies³aw Myœliwski, Kamieñ na kamieniu lub Antoni Libera - Madame;



				}
				cout << "=========================================================================" << endl;

				cin.get();

				do
				{
					Bidentyfikator = 0;
					cout << "PODAJ IDENTYFIKATOR KSIAZKI: ";
					cin >> Bidentyfikator;
					system("cls");

				} while (Kidentyfikator >= KlicznikID && Kidentyfikator <= 0);

				moment = stoi(zbiorKlientow.ilosc_wypozyczen[Kidentyfikator]);
				moment++;
				zbiorKlientow.ilosc_wypozyczen[Kidentyfikator] = intToStr(moment);

				do
					ktoraZKolei++;
				while (zbiorKlientow.wyp_klientow[Kidentyfikator][ktoraZKolei] != zbiorKsiazek.tytuly[Bidentyfikator]);

					zbiorKlientow.wyp_klientow[Kidentyfikator][ktoraZKolei] = "";
					zbiorKsiazek.daty_odd[Bidentyfikator] = "";
					zbiorKsiazek.czy_dost[Bidentyfikator] = "1";
					


			}
				break;
			case '7':		// ZNAJD KSI¥¯KÊ
			{
				int identyfikator;
				do
				{
					identyfikator = 0;
					cout << "PODAJ IDENTYFIKATOR KSIAZKI: ";
					cin >> identyfikator;
					system("cls");

				} while (identyfikator >= BlicznikID && identyfikator <= 0);

				cout << "=============================================================================" << endl;
				cout << "| ID: " << zbiorKsiazek.identyfikatory[identyfikator] << " | " << "WYPOZYCZONE PRZEZ: ";
				if (zbiorKsiazek.id_klientow[identyfikator] == "NIKOGO")
					cout << zbiorKsiazek.id_klientow[identyfikator] << endl;
				else
				{
					cout << zbiorKlientow.imiona[stoi(zbiorKsiazek.id_klientow[identyfikator])] << " "
						<< zbiorKlientow.nazwiska[stoi(zbiorKsiazek.id_klientow[identyfikator])];
					cout << " | OCZEKIWANA DATA ZWROTU: " << zbiorKsiazek.daty_odd[identyfikator] << endl;
				}

				cout << "| " << zbiorKsiazek.czy_dost[identyfikator] << "	 | " << zbiorKsiazek.tytuly[identyfikator] << endl;
				cout << "|---------------------------------------------------------------------------|" << endl;
				_getch();
			}
				break;
			case '8':		// ZATRUDNIJ PRACOWNIKA
			{
				pobierzDaneOsoby();
				if (poprawneDane)
				{
					pobierzDanePracownika();
					Pracownik robol(t_PESEL, t_wiek, t_wzrost, t_dni, t_mies, t_lata,
						t_imie, t_nazwisko, t_adres, t_oczy,
						t_pensja, t_data_zatr, t_data_zwoln, t_data_zakUmowy);

					zbiorPracownikow.pesele[PlicznikID] = robol.PESEL;
					zbiorPracownikow.lata_p[PlicznikID] = intToStr(robol.wiek);
					zbiorPracownikow.wzrosty[PlicznikID] = intToStr(robol.wzrost);
					zbiorPracownikow.daty_ur[PlicznikID] = intToStr(robol.dni)
						+ "-" + intToStr(robol.mies) + "-" + intToStr(robol.lata);
					zbiorPracownikow.imiona[PlicznikID] = robol.imie;
					zbiorPracownikow.nazwiska[PlicznikID] = robol.nazwisko;
					zbiorPracownikow.adresy[PlicznikID] = robol.adres;
					zbiorPracownikow.kol_oczu[PlicznikID] = robol.oczy;
					zbiorPracownikow.pensje[PlicznikID] = intToStr(robol.pensja);
					zbiorPracownikow.daty_zatr[PlicznikID] = intToStr(czasPodzielony.tm_mday)
						+ '-' + intToStr(czasPodzielony.tm_mon + 1) + '-' + intToStr(czasPodzielony.tm_year + 1900);
					zbiorPracownikow.daty_zakUm[PlicznikID] = robol.data_zakUmowy;

					//cout << zbiorPracownikow.pesele[PlicznikID] << endl;
					//cout << zbiorPracownikow.adresy[PlicznikID] << endl;
					_getch();
				}

				poprawneDane = true;

			}
				break;
			case '9':		// ZWOLNIJ PRACOWNIKA (DO DOKONCZENIA)
			{
				pobierzDaneKarty();
				KartaBiblioteczna karta(int t_ilosc_wyp, int t_nieZwrocone, string t_data_wazn);
			}
				break;
			case 'a':		// ZMIEN DANE PRACOWNIKA (DO DOKONCZENIA)
			{
				cout << "			CO CHCESZ ZMIENIC?" << endl;
				cout << endl;
				cout << "	[0] -> PESEL" << endl;
				cout << "	[1] -> WIEK" << endl;
				cout << "	[2] -> WZROST" << endl;
				cout << "	[3] -> DATE URODZENIA" << endl;
				cout << "	[4] -> IMIE" << endl;
				cout << "	[5] -> NAZWISKO" << endl;
				cout << "	[6] -> ADRES" << endl;
				cout << "	[7] -> KOLOR OCZU" << endl;
				cout << endl;
				cout << endl;

				char opcja = _getch();
				zmienDane(opcja);
			}
				break;
			case 'b':		// WYŒWIETL SPIS KSI¥¯EK
			{
				cout << "=============================================================================" << endl;

				for (int i = 0; i < BlicznikID - 1; i++)
				{

					cout << "| ID: " << zbiorKsiazek.identyfikatory[i] << " | " << "WYPOZYCZONE PRZEZ: ";
					if (zbiorKsiazek.id_klientow[i] == "NIKOGO")
						cout << zbiorKsiazek.id_klientow[i] << endl;
					else
					{
						cout << zbiorKlientow.imiona[stoi(zbiorKsiazek.id_klientow[i])] << " "
							<< zbiorKlientow.nazwiska[stoi(zbiorKsiazek.id_klientow[i])];
						cout << " | OCZEKIWANA DATA ZWROTU: " << zbiorKsiazek.daty_odd[i] << endl;
					}

					cout << "| " << zbiorKsiazek.czy_dost[i] << "	 | " << zbiorKsiazek.tytuly[i] << endl;
					cout << "|---------------------------------------------------------------------------|" << endl;

					//		        Wies³aw Myœliwski, Kamieñ na kamieniu lub Antoni Libera - Madame;



				}
				cout << "=============================================================================" << endl;

				cin.get();
			}
				break;
			case 'c':		// WYŒWIETL WSZYSTKICH PRACOWNIKÓW
			{
				cout << "ID | IMIE I NAZWISKO" << endl;
				for (int i = 2; i < PlicznikID + 1; i++)
				{
					if (stoi(zbiorKlientow.id_kart[i]) == -1)
					{

					}
					else
					{
						cout << "============================================" << endl;
						cout << zbiorPracownikow.identyfikatory[i] << "  | "
							<< zbiorPracownikow.imiona[i] << " "
							<< zbiorPracownikow.nazwiska[i] << endl;
						cout << "--------------------------------------------" << endl;
						cout << "Pensja: " << zbiorPracownikow.pensje[i] << endl;
						cout << "Adres zam.: " << zbiorPracownikow.adresy[i] << endl;
						cout << "Data zak. umowy: " << zbiorPracownikow.daty_zakUm[i] << endl;
						cout << "Wiek: " << zbiorPracownikow.lata_p[i] << endl;


					}

				}
				cin.get();
			}
				break;
			case 's':		// ZAPISZ (KLIENTÓW) DO PLIKU (DO DOPRACOWNIA - TO DO: PRACOWNICY)
			{
				zapiszKlientowDoPliku(KlicznikID - 1, zbiorKlientow);
				zapiszPracownikowDoPliku(PlicznikID - 1, zbiorPracownikow);
				cout << "ZAPISANO POMYSLNIE" << endl;
				cin.get();

			}
				break;
			case 'x':		// ZAMKNIJ PROGRAM
				exit(0);
				break;
			default:
				break;
			}

													
		}
		else
		{
			do
			{
				system("cls");

				cout << endl;
				cout << "			CO CHCESZ ZROBIC?" << endl;
				cout << "			-----------------" << endl;
				cout << endl;
				cout << "	[0] -> DODAJ KLIENTA" << endl;
				cout << "	[1] -> ZNAJDZ KLIENTA W BAZIE" << endl;
				cout << "	[2] -> USUN KLIENTA " << endl;
				cout << "	[3] -> POKAZ WSZYSTKICH KLIENTOW" << endl;
				cout << "	[4] -> ZMIEN DANE KLIENTA" << endl;
				cout << endl;
				cout << "	[5] -> WYPOZYCZENIE" << endl;
				cout << "	[6] -> ODDANIE" << endl;
				cout << "	[7] -> ZNAJDZ KSIAZKE W BAZIE" << endl;
				cout << "	[B] -> WYSWIETL SPIS KSIAZEK" << endl;

				cout << endl;
				cout << endl;
				cout << "	[S] -> ZAPISZ ZMIANY" << endl;
				cout << endl;
				cout << "	[X] -> WYJDZ Z PROGRAMU" << endl;

				cout << endl;
				cout << endl;
				cout << "	> ";
				wybor = _getch();

			} while (wybor != (int)'0' &&
				wybor != (int)'1' &&
				wybor != (int)'2' &&
				wybor != (int)'3' &&
				wybor != (int)'4' &&
				wybor != (int)'5' &&
				wybor != (int)'6' &&
				wybor != (int)'7' &&

				wybor != (int)'b' &&


				wybor != (int)'x');

			system("cls");

			switch (wybor)
			{
			case '0':
			{
				czyKarta = true;
				pobierzDaneOsoby();
				czyKarta = false;

				if (poprawneDane)
				{
					pobierzDaneKarty();

					KartaBiblioteczna karta(t_PESEL, t_dni, t_mies, t_lata, t_imie, t_nazwisko, t_ilosc_wyp,
						t_nieZwrocone, t_oplaty, t_data_wazn, t_wypozyczenia);
					//string rokWaznosci = czasPodzielony.tm_year;

					zbiorKlientow.pesele[KlicznikID] = karta.PESEL;
					zbiorKlientow.daty_ur[KlicznikID] = intToStr(karta.dni) + "-" + intToStr(karta.mies)
						+ "-" + intToStr(karta.lata);
					zbiorKlientow.imiona[KlicznikID] = karta.imie;
					zbiorKlientow.nazwiska[KlicznikID] = karta.nazwisko;
					zbiorKlientow.ilosc_wypozyczen[KlicznikID] = intToStr(karta.ilosc_wyp);
					zbiorKlientow.nie_zwrocenia[KlicznikID] = intToStr(karta.nieZwrocone);
					zbiorKlientow.oplaty_klientow[KlicznikID] = intToStr(karta.oplaty);
					zbiorKlientow.daty_wazn[KlicznikID] = intToStr(czasPodzielony.tm_mday) + '-'
						+ intToStr(czasPodzielony.tm_mon) + "-20" + intToStr(czasPodzielony.tm_year - 100 + 2);

					for (int i = 0; i < 10; i++)
					{
						zbiorKlientow.wyp_klientow[KlicznikID][i] = " ";
					}

					//cout << karta.imie << " " << karta.adres << " " << karta.idKarty << endl;
					//cout << zbiorKlientow.imiona[KlicznikID] << " " << "jakis adres" << zbiorKlientow.id_kart[KlicznikID] << endl;
					//_getch();
				}

				poprawneDane = true;
			}
			break;
			case '1':
			{
				int identyfikator;
				do
				{
					identyfikator = 0;
					cout << "PODAJ IDENTYFIKATOR KLIENTA: ";
					cin >> identyfikator;
					system("cls");

				} while (identyfikator >= KlicznikID && identyfikator <= 0);

				cout << zbiorKlientow.id_kart[identyfikator] << "  | "
					<< zbiorKlientow.imiona[identyfikator] << " "
					<< zbiorKlientow.nazwiska[identyfikator] << endl;
				cout << "--------------------------------------------" << endl;
				cout << "Wisi nam				" << zbiorKlientow.oplaty_klientow[identyfikator] << " zl" << endl;
				cout << "Wypozyczyl:				" << zbiorKlientow.ilosc_wypozyczen[identyfikator] << endl;
				cout << "Nie oddal:				" << zbiorKlientow.nie_zwrocenia[identyfikator] << endl;
				cout << "PESEL:				" << zbiorKlientow.pesele[identyfikator] << endl;
				cout << "Urodzony			" << zbiorKlientow.daty_ur[identyfikator] << endl;
				cout << "Urodzony			" << zbiorKlientow.daty_ur[identyfikator] << endl;
				cout << "Wypozyczone ksiazki: ";
				for (int i = 0; i < 10; i++)
					cout << zbiorKlientow.wyp_klientow[KlicznikID][i] << endl;


				_getch();

			}
			break;
			case '2':
			{
				int identyfikator;
				do
				{
					identyfikator = 0;
					cout << "PODAJ IDENTYFIKATOR KLIENTA: ";
					cin >> identyfikator;
					system("cls");

				} while (identyfikator >= KlicznikID && identyfikator <= 0);

				zbiorKlientow.pesele[identyfikator] = "";
				zbiorKlientow.daty_ur[identyfikator] = "";
				zbiorKlientow.imiona[identyfikator] = "";
				zbiorKlientow.nazwiska[identyfikator] = "";
				zbiorKlientow.id_kart[identyfikator] = intToStr(-1);
				zbiorKlientow.ilosc_wypozyczen[identyfikator] = "";

				for (int j = 0; j < 10; j++)
					zbiorKlientow.wyp_klientow[identyfikator][j] = "";


				zbiorKlientow.nie_zwrocenia[identyfikator] = "";
				zbiorKlientow.daty_wazn[identyfikator] = "";
				zbiorKlientow.oplaty_klientow[identyfikator] = "";

			}
			break;
			case '3':
			{
				cout << "ID | IMIE I NAZWISKO" << endl;
				for (int i = 2; i < KlicznikID + 1; i++)
				{
					if (stoi(zbiorKlientow.id_kart[i]) == -1)
					{

					}
					else
					{
						cout << "============================================" << endl;
						cout << zbiorKlientow.id_kart[i] << "  | "
							<< zbiorKlientow.imiona[i] << " "
							<< zbiorKlientow.nazwiska[i] << endl;
						cout << "--------------------------------------------" << endl;
						cout << "Wisi nam				" << zbiorKlientow.oplaty_klientow[i] << " zl" << endl;
						cout << "Wypozyczyl:				" << endl
							<< "  Ilosc:				" << zbiorKlientow.ilosc_wypozyczen[i] << endl
							<< "  Ksiazki: " << endl;
						for (int j = 1; j <= stoi(zbiorKlientow.ilosc_wypozyczen[i]); j++)
							cout << "	- " << zbiorKlientow.wyp_klientow[i][j] << endl;

						cout << endl;
						cout << "Nie oddal:				" << zbiorKlientow.nie_zwrocenia[i] << endl;
						cout << "Data waznosci karty::		" << zbiorKlientow.daty_wazn[i] << endl;
						cout << "PESEL:				" << zbiorKlientow.pesele[i] << endl;
						cout << "Urodzony			" << zbiorKlientow.daty_ur[i] << endl;
					}

				}
				cin.get();
			}
			break;
			case '4':
			{
				cout << "CO CHCESZ WYSWIETLIC?" << endl;
				cout << endl;
				cout << "[0] -> PESEL" << endl;
				cout << "[1] -> WIEK" << endl;
				cout << "[2] -> WZROST" << endl;
				cout << "[3] -> DATE URODZENIA" << endl;
				cout << "[4] -> IMIE" << endl;
				cout << "[5] -> NAZWISKO" << endl;
				cout << "[6] -> ADRES" << endl;
				cout << "[7] -> KOLOR OCZU" << endl;
				cout << endl;
				cout << endl;

				char opcja = _getch();

				switch (opcja)
				{
				case 48:
					cout << osoba.PESEL;
					cin.get(); break;
				case 49:
					cout << osoba.wiek;
					cin.get(); break;
				case 50:
					cout << osoba.wzrost;
					cin.get(); break;
				case 51:
					cout << osoba.dni << "-" << osoba.mies << "-" << osoba.lata << endl;
					cin.get(); break;
				case 52:
					cout << osoba.imie;
					cin.get(); break;
				case 53:
					cout << osoba.nazwisko;
					cin.get(); break;
				case 54:
					cout << osoba.adres;
					cin.get(); break;
				case 55:
					cout << osoba.oczy;
					cin.get(); break;

				default:
					cout << "Zla dana. " << endl;
					system("pause");
					break;
				}
			}
			break;
			case '5':
			{
				int Kidentyfikator;
				int Bidentyfikator;
				do
				{
					Kidentyfikator = 0;
					cout << "PODAJ IDENTYFIKATOR KLIENTA: ";
					cin >> Kidentyfikator;
					system("cls");

				} while (Kidentyfikator >= KlicznikID && Kidentyfikator <= 0);



				cin.get();

				cout << "=========================================================================" << endl;

				for (int i = 0; i < BlicznikID; i++)
				{

					cout << "| ID: " << zbiorKsiazek.identyfikatory[i] << " | " << "WYPOZYCZONE PRZEZ: "
						<< zbiorKsiazek.id_klientow[i] << endl;
					cout << "| " << zbiorKsiazek.czy_dost[i] << "	 | " << zbiorKsiazek.tytuly[i] << endl;
					cout << "|-----------------------------------------------------------------------|" << endl;

					//		        Wies³aw Myœliwski, Kamieñ na kamieniu lub Antoni Libera - Madame;



				}
				cout << "=========================================================================" << endl;

				cin.get();

				do
				{
					Bidentyfikator = 0;
					cout << "PODAJ IDENTYFIKATOR KSIAZKI: ";
					cin >> Bidentyfikator;
					system("cls");

				} while (Kidentyfikator >= KlicznikID && Kidentyfikator <= 0);

				int moment;

				cout << zbiorKlientow.imiona[Kidentyfikator] << " " << zbiorKlientow.nazwiska[Kidentyfikator]
					<< " wypozycza" << zbiorKsiazek.tytuly[Bidentyfikator] << "." << endl;
				cout << "Zatwierdzic?" << endl
					<< "	[T] TAK			[N] NIE" << endl;
				if (_getch() == 't')
				{
					cout << zbiorKlientow.ilosc_wypozyczen[Kidentyfikator];
					moment = stoi(zbiorKlientow.ilosc_wypozyczen[Kidentyfikator]);
					moment++;	// - przechowuje iloœæ wpo¿tczonych ksia¿ek danego klienta
					zbiorKlientow.ilosc_wypozyczen[Kidentyfikator] = intToStr(moment);

					//		zbiorKlientow.wyp_klientow[Kidentyfikator][moment] = intToStr(Bidentyfikator);
					zbiorKlientow.wyp_klientow[Kidentyfikator][moment] = zbiorKsiazek.tytuly[Bidentyfikator];

					zbiorKsiazek.czy_dost[Bidentyfikator] = 48; // 0
					zbiorKsiazek.id_klientow[Bidentyfikator] = intToStr(Kidentyfikator);
					zbiorKsiazek.daty_odd[Bidentyfikator] = intToStr(czasPodzielony.tm_mday)
						+ '-'
						+ intToStr(czasPodzielony.tm_mon + 3)
						+ '-'
						+ intToStr(czasPodzielony.tm_year + 1900);

					system("cls");
					cout << "WYPOZYCZONO POMYSLNIE.";
				}




				_getch();
			}
			break;
			case '6':
			{
				Osoba osoba;

				t_PESEL = osoba.PESEL;
				t_wiek = osoba.wiek;
				t_wzrost = osoba.wzrost;
				t_dni = osoba.dni;
				t_mies = osoba.mies;
				t_lata = osoba.lata;
				for (int i = 0; i < 1000; i++)
				{
					if (t_adres[i] == '\\0')	break;
					t_adres[i] = osoba.adres[i];
				}
				t_imie = osoba.imie;
				t_nazwisko = osoba.nazwisko;
				t_oczy = osoba.oczy;

			}
			break;
			case '7':
			{
				int identyfikator;
				do
				{
					identyfikator = 0;
					cout << "PODAJ IDENTYFIKATOR KSIAZKI: ";
					cin >> identyfikator;
					system("cls");

				} while (identyfikator >= BlicznikID && identyfikator <= 0);

				cout << "=============================================================================" << endl;
				cout << "| ID: " << zbiorKsiazek.identyfikatory[identyfikator] << " | " << "WYPOZYCZONE PRZEZ: ";
				if (zbiorKsiazek.id_klientow[identyfikator] == "NIKOGO")
					cout << zbiorKsiazek.id_klientow[identyfikator] << endl;
				else
				{
					cout << zbiorKlientow.imiona[stoi(zbiorKsiazek.id_klientow[identyfikator])] << " "
						<< zbiorKlientow.nazwiska[stoi(zbiorKsiazek.id_klientow[identyfikator])];
					cout << " | OCZEKIWANA DATA ZWROTU: " << zbiorKsiazek.daty_odd[identyfikator] << endl;
				}

				cout << "| " << zbiorKsiazek.czy_dost[identyfikator] << "	 | " << zbiorKsiazek.tytuly[identyfikator] << endl;
				cout << "|---------------------------------------------------------------------------|" << endl;
				_getch();
			}
			break;
			case 's':
			{
				zapiszKlientowDoPliku(KlicznikID - 1, zbiorKlientow);
				cout << "ZAPISANO POMYSLNIE" << endl;
				cin.get();

			}
			break;
			case 'x':
				exit(0);
				break;
			default:
				break;
			}

		}
		
										
					

	} while (wybor != (int)'x');
	

	return 0;

}