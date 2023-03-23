#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define MAX_NUM_CAR 200
#define MAX_NUM_PAR 10000
#define MAX_NUM_LIG 30000

#define MAX_NOME_CAR 20
#define MAX_NOME_PAR 50

typedef struct Carreira
{
	char nome[MAX_NOME_CAR];
	struct Lista_Paragem *ori, *dest;
	int num_par;
	double cost, dur;
} car;

typedef struct Info_Paragem
{
	char nome[MAX_NOME_PAR];
	double lat, lon;
	int num_car;
	struct Ligacao *prev, *next;
} par;

typedef struct Lista_Paragem
{
	par *this;
	struct Lista_Paragem *prev, *next;
} lis_par;

typedef struct Ligacao
{
	car *carr;
	par *ori, *des;
	double cost, dur;
} lig;

typedef struct Lista_Ligacao
{
	lig *prev, *this, *next;
} lis_lig;

car* Init_Car();
par* Init_Par();
lig* Init_Lig();
lis_par* Init_lis_par_cell();

int Find_Car(car**,char*);
int Find_Par(par**,char*);

void Print_Car(car**,car*,int);
void Print_Par(par**, par*);

int Check_Lig(car*,par*,par*);

int Rem_blank();
char** Get_Name(int,char*);

int Count_Args(char*);
int Is_Text(char);

void Modo_C(char*,car**);
void Modo_P(char*,par**);
void Modo_L(char*,car**,par**);

#endif