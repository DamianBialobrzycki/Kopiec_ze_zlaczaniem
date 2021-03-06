// Kopiec_ze_zlaczaniem.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

struct kopiec
{
	int tablica[8192];
	int n;

	kopiec();
	
	void zresetuj();
	void pokaz();
	void usun();
	void dodaj(int v);
	void przywroc_wlasnosc(int i);
	
};

kopiec::kopiec()
{
	n = 0;
}

void kopiec::zresetuj()
{
	n = 0;
}

void kopiec::pokaz()
{
	for (int i = 0; i < n; i++)
	{
		cout << tablica[i] << " ";
	}
	cout << endl;
}

void kopiec::usun()
{
	
	cout << tablica[0] << endl;
	tablica[0] = tablica[n-1];
	n--;
	przywroc_wlasnosc(0);

	/*int i, j, v;

	if (n--)
	{
		v = tablica[n];

		i = 0;
		j = 1;

		while (j < n)
		{
			if (j + 1 < n && tablica[j + 1] > tablica[j])
				j++;
			if (v >= tablica[j])
				break;

			tablica[i] = tablica[j];
			i = j;
			j = 2 * j + 1;
		}

		tablica[i] = v;
	}*/
}

void kopiec::dodaj(int v)
{
	int dziecko = n++;
	int rodzic = (dziecko - 1) / 2;

	//n++;

	while (dziecko > 0 && tablica[rodzic] < v)
	{
		tablica[dziecko] = tablica[rodzic];
		dziecko = rodzic;
		rodzic = (dziecko - 1) / 2;
	}

	tablica[dziecko] = v;
	//cout << tablica[dziecko] << endl;
}

void kopiec::przywroc_wlasnosc(int i)
{
	int max = 0;
	int lewy = 2 * i +1;
	int prawy = 2 * i + 1+1;
	int tmp = 0;

	if (lewy < n && tablica[i] < tablica[lewy])
		max = lewy;
	else
		max = i;

	if (prawy < n && tablica[max] < tablica[prawy])
		max = prawy;

	if (max != i)
	{
		tmp = tablica[i];
		tablica[i] = tablica[max];
		tablica[max] = tmp;
		przywroc_wlasnosc(max);
	}
}

void zlacz(kopiec & k1, kopiec & k2)
{
	kopiec tmp;
	for (int i = 0; i < k1.n; i++)
	{		
		tmp.tablica[i] = k1.tablica[i];
		tmp.n++;
	}

	for (int i = 0; i < k2.n; i++)
	{
		tmp.n++;
		tmp.tablica[k1.n + i] = k2.tablica[i];
	}
		

	k1 = tmp;
	for (int i = k1.n / 2; i >= 0; i--)
		k1.przywroc_wlasnosc(i);

	k2.zresetuj();
}

int main()
{
	kopiec kp[10];


	int v=0;
	int nr=0;
	int n = 0;
	int zlacz1, zlacz2 = 0;
	int nowy = 0;

	char polecenie;
	cin >> polecenie;

	while (polecenie != 'q')
	{
		switch(polecenie)
		{
		case '+':
			cin >> nr;
			cin >> v;

			kp[nr].dodaj(v);
			break;
		case '-':
			cin >> nr;

			kp[nr].usun();
			break;	
		case 'p':
			cin >> nr;
			kp[nr].pokaz();
			break;
		case 'r':
			cin >> nr;
			cin >> n;
			kp[nr].zresetuj();
			
			kp[nr].n = n;

			/*for (int i = 0; i < n; i++)
			{
				cin >> v;
				kp[nr].dodaj(v);
			}*/
			for (int i = 0; i < n; i++)
			{
				//kp[nr].n++;
				cin >> kp[nr].tablica[i];
				//cout << kp[nr].tablica[i] << endl;
			}
				

			for (int i = n / 2; i >= 0; i--)
			{
				kp[nr].przywroc_wlasnosc(i);
				//cout << i << endl;
			}
				
			
			break;
		case 'j':
			cin >> zlacz1;
			cin >> zlacz2;
			zlacz(kp[zlacz1], kp[zlacz2]);
			break;
		default:
			break;
		}

		cin >> polecenie;
	}
    return 0;
}
