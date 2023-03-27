#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define MAX_NUM_CAR 200
#define MAX_NUM_PAR 10000
#define MAX_NUM_LIG 30000

#define MAX_NOME_CAR 20
#define MAX_NOME_PAR 50

typedef struct Info_Carreira
{
	char nome[MAX_NOME_CAR+1];
	struct Lista_Paragens *ori, *dest;
	int num_par;
	double cost, dur;
} car;

typedef struct Info_Paragem
{
	char nome[MAX_NOME_PAR+1];
	double lat, lon;
	int num_car;
	struct Lista_Carreiras *cars;
} par;

typedef struct Lista_Paragens
{
	par *this;
	struct Lista_Paragens *prev, *next;
} lis_par;

typedef struct Lista_Carreiras
{
	car *this;
	struct Lista_Carreiras *next;
} lis_car;

car* Init_Car();
par* Init_Par();

lis_par* Init_lis_par_cell();
lis_car* Init_lis_car_cell();

int Find_Car(car**,char*);
int Find_Par(par**,char*);

lis_car* Find_Car_in_Lis(car*,lis_car*);
lis_par* Find_Par_in_Lis(par*,lis_par*);

void Add_to_Car_lis(car*,par*);

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
void Modo_I(par**);

#endif