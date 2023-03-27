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

/*
These functions allocate and initialise new structs or elements of a list
*/

car* Init_Car();
par* Init_Par();

lis_par* Init_lis_par_cell();
lis_car* Init_lis_car_cell();

/*
These functions return the indice of the element they're looking for
or the indice for the first open slot
*/

int Find_Car(car**,char*);
int Find_Par(par**,char*);

lis_car* Find_Car_in_Lis(car*,lis_car*);
lis_par* Find_Par_in_Lis(par*,lis_par*);

/*
Adds a new line to the list of lines that the stop belongs to
*/

void Add_to_Car_lis(car*,par*);

/*
These functions deal with the output from Modes C and P
*/

void Print_Car(car**,car*,int);
void Print_Par(par**, par*);

/*
Returns 1 if the link is valid, 0 if not
*/

int Check_Lig(car*,par*,par*);


/*
Gets the name of something even if it's delimited by "" 
*/
char** Get_Name(int,char*);

/*
Returns the number of arguments in the input read
*/
int Count_Args(char*);

/*
Returns 1 if its a digit, a letter, or a dot
*/
int Is_Text(char);

/*
These functions receive the input read and process the various commands
*/
void Modo_C(char*,car**);
void Modo_P(char*,par**);
void Modo_L(char*,car**,par**);
void Modo_I(par**);

#endif