#include <bits/stdc++.h>
using namespace std;

ifstream fin("afn.in");
ofstream fout("afn.out");

vector <int> CareAuLambda[100];
unsigned int nrStari, nrAlfabet, stareInitiala=0;
unsigned int nrStariFinale, stariFinale[100], nrMiscari, nrCuvinte;
char alfabet[30];
unsigned int i, j;

class LNFA
{
private:
	vector <int> stariInCarePotAjunge;
public:
	void pushStare(int x);
	unsigned int nrStariInCarePotAjunge();
	int element(int pozitie);
} Miscari[100][30];

void LNFA::pushStare(int nou)
{
	int ok = 1;
    for (unsigned int i = 0; i < stariInCarePotAjunge.size(); i++)
		if (nou == stariInCarePotAjunge[i])
			ok = 0;

	if (ok == 1)
		stariInCarePotAjunge.push_back(nou);
}

unsigned int LNFA::nrStariInCarePotAjunge()
{
	return stariInCarePotAjunge.size();
}

int LNFA::element(int pozitie)
{
	return stariInCarePotAjunge[pozitie];
}

bool stareFinala(unsigned int x)
{
	for (unsigned int i = 0; i < nrStariFinale; i++)
    {
		if (x == stariFinale[i])
            return 1;
    }
	return 0;
}

bool verificareCuvant(int stare, char cuvant[])
{
	unsigned int i;
	if (strlen(cuvant) == 1)
	{
		for (i = 0; i < Miscari[stare][cuvant[0] - 'a'].nrStariInCarePotAjunge(); i++)
        {

			if (stareFinala(Miscari[stare][cuvant[0] - 'a'].element(i)))

				return 1;
        }
		return 0;
	}
	else
	{
		for (i = 0; i < Miscari[stare][cuvant[0] - 'a'].nrStariInCarePotAjunge(); i++)
			if (verificareCuvant(Miscari[stare][cuvant[0] - 'a'].element(i), cuvant + 1))
				return 1;
		return 0;
	}
}

int main()
{
    FILE *f=fopen("afn.in", "r");
	fscanf(f,"%i\n", &nrStari);

	for (i = 0; i < nrStari; i++)
	{
		CareAuLambda[i].push_back(i);
	}
	fscanf(f,"%i\n", &nrStari);
	fgets(alfabet,100,f);

	char *aux;
	aux = (char*)malloc(100);
	fgets(aux,100,f);

	int dist;
    nrStariFinale = strlen(aux);
	for (i = 0; i < nrStariFinale; i++)
    {
        sscanf(aux,"%i%n", &stariFinale[i],&dist);
        aux+=dist;
    }

    fscanf(f,"%i\n",&nrMiscari);
	for (i = 0; i < nrMiscari; i++)
	{
		int st1, st2;
		char caracter;
		fscanf(f,"%c %i %i\n",&caracter,&st1,&st2);
		if (caracter == '$')
		{
			CareAuLambda[st1].push_back(st2);
		}
		else
		{
			Miscari[st1][caracter - 'a'].pushStare(st2);
		}

	}

	unsigned int stare1, stare2, litera, lambda;

	for (stare1 = 0; stare1 < nrStari; stare1++)
		for (litera = 0; litera < nrAlfabet; litera++)
			for (stare2 = 0; stare2 < Miscari[stare1][alfabet[litera] - 'a'].nrStariInCarePotAjunge(); stare2++)
			{
				int element = Miscari[stare1][alfabet[litera] - 'a'].element(stare2);

				for (lambda = 0; lambda < CareAuLambda[element].size(); lambda++)
					Miscari[stare1][alfabet[litera] - 'a'].pushStare(CareAuLambda[element][lambda]);
			}
    fscanf(f,"%i\n",&nrCuvinte);
    for (i = 0; i < nrCuvinte; i++)
	{

		char cuvant[50];
		fgets(cuvant,100,f);
		cuvant[strlen(cuvant)-1]='\0';
		fout<<cuvant<<'\n';
        for (j = 0; j < CareAuLambda[stareInitiala].size(); j++)
        {

			if (verificareCuvant(CareAuLambda[stareInitiala][j], cuvant))
				fout << "DA(1)" << '\n';
			else
				fout << "NU(0)" << '\n';
        }
	}
	return 0;
}
