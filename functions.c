#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"functions.h"

car* Init_Car(){
	car *c;
	c = malloc(sizeof(car));
	if(c==NULL){
		printf("ERROR: memory allocation\n");
		exit(-1);
	}
	c->nome[0] = '\0';
	c->dest = NULL;
	c->ori = NULL;
	c->num_par = 0;
	c->cost = 0;
	c->dur = 0;
	return c;
}

par* Init_Par(){
	par* p;
	p = malloc(sizeof(par));
	if(p==NULL){
		printf("ERROR: memory allocation\n");
		exit(-1);
	}
	p->nome[0] = '\0';
	p->lat = 0;
	p->lon = 0;
	p->num_car = 0;
	p->cars = NULL;
	return p;
}

lis_car* Init_lis_car_cell(){
	lis_car *c = NULL;
	c = malloc(sizeof(lis_car));
	if(c==NULL){
		printf("ERROR: memory allocation\n");
		exit(-1);
	}
	c->next = NULL;
	c->this = NULL;
	
	return c;
}

lis_car* Find_Car_in_Lis (car* c, lis_car* l){
	lis_car *temp = l;
	while(temp!=NULL){
		if(temp->this == c)
			break;
		else
			temp = temp->next;
	}
	return temp;
}

lis_par* Find_Par_in_Lis(par* p, lis_par* l){
	lis_par *temp = l;
	while(temp!=NULL){
		if(temp->this == p)
			break;
		else{
			temp = temp->next;
			if(temp == l){
				temp = NULL;
				break;
			}
		}
	}
	return temp;
}

void Add_to_Car_lis(car* c, par* p){
	lis_car *temp = p->cars, *new = NULL/*, *aux = NULL*/;

	new = Init_lis_car_cell();
	new->this = c;
	if(temp == NULL){
		p->cars = new;
	}
	else {
		while(temp->next !=NULL){
			/*if(strncmp(temp->this->nome,c->nome,strlen(temp->this->nome))>0){

			}*/
			temp = temp->next;
		}
		temp->next = new;
		
	}
}

lis_par* Init_lis_par_cell(){
	lis_par *c = NULL;

	c = malloc(sizeof(lis_par));
	if(c==NULL){
		printf("ERROR: memory allocation\n");
		exit(-1);
	}
	c->next = NULL;
	c->this = NULL;
	c->prev = NULL;
	
	return c;
}

int Check_Lig(car* c, par* ori, par *dest){
	if(c->ori->this == dest || c->dest->this == ori)
		return 1;
	else
		return 0;
}

int Rem_blank(){
	char a = getchar();
	while((a == ' ') && (a != '\n') && (a != EOF))
		a = getchar();
	return a;
}

char** Get_Name(int max, char* str){
	int i = 0, size = 0;
	char *temp = NULL, **ret = NULL;

	ret = malloc(sizeof(char*)*2);
	if(ret==NULL){
		printf("ERRO: memory allocation\n\n");
		exit(-1);
	}

	ret[0] = malloc(sizeof(char)*(max+1));
	if(ret[0]==NULL){
		printf("ERRO: memory allocation\n\n");
		exit(-1);
	}
	ret[0][0]='\0';

	temp = str+1;
	for(i=0;temp[i] == ' '; i++);

	if(temp[i] == '"'){
		i++;
		while(temp[i] != '"' && size<max-1){
			ret[0][size]=temp[i];
			i++;
			size++;
		}
		ret[0][++size] = '\0';
		ret[1]=temp+i+1;
	}
	else{
		if(sscanf(temp,"%s", ret[0]) != 1)
			exit(-1);
		ret[1]=temp+strlen(ret[0])+1;
	}
	return ret;
}

void Print_Car(car** c_l, car* c, int inv){
	int i;
	lis_par* next = NULL;
	if(c == NULL && c_l == NULL)
		exit(-1);
	
	/*If it's a single bus line*/
	if(c != NULL && c_l == NULL){
		/*REVIEW*******************************************************/
		if(c->ori != NULL && c->dest != NULL)
			switch (inv){
				/*If it IS supposed to invert the order*/
				case 1:
					next = c->dest;
					while(next!=c->ori){
						printf("%s, ", next->this->nome);
						next = next->prev;
					}
					printf("%s", c->ori->this->nome);
					break;
				/*If it IS NOT supposed to invert the order*/
				case 0:
					next = c->ori;
					while(next!=c->dest){
						printf("%s, ", next->this->nome);
						next = next->next;
					}
					printf("%s", c->dest->this->nome);
					break;
				default:
					break;
			}
		printf("\n");
	}
	if(c == NULL && c_l != NULL){
		for(i=0; c_l[i] != NULL && i<MAX_NUM_CAR; i++){
			printf("%s ", c_l[i]->nome);
			if(c_l[i]->ori != NULL && c_l[i]->dest != NULL){
				printf("%s ", c_l[i]->ori->this->nome);
				printf("%s ", c_l[i]->dest->this->nome);
			}
			printf("%d %.2f %.2f\n",c_l[i]->num_par, c_l[i]->cost, c_l[i]->dur);
		}
	}
}

void Print_Par(par** p_l, par* p){
	int i;
	if(p == NULL && p_l == NULL)
		exit(-1);
	
	/*If it's a single stop*/
	if(p != NULL && p_l == NULL){
		printf("%16.12f %16.12f\n", p->lat, p->lon);
	}
	/*If it's all the stops*/
	if(p == NULL && p_l != NULL){
		for(i=0; p_l[i] != NULL && i<MAX_NUM_PAR; i++){
			printf("%s: %16.12f ", p_l[i]->nome, p_l[i]->lat);
			printf("%16.12f %d\n", p_l[i]->lon, p_l[i]->num_car);
		}
	}
}


/* Tries to find the bus line with the name "s":
if it DOES FIND, returns the index to that bus line in the array
if it DOESN'T, returns the index to the first free slot */

int Find_Car(car** c,char* s){
	int i;
	for(i=0;i<MAX_NUM_CAR;i++){
		if(c[i]!=NULL){
			if(strcmp(c[i]->nome, s) == 0)
				return i;
		}
		else
			return i;
	}
	return(-1);
}

/* Tries to find the stop with the name "s":
if it DOES FIND, returns the index to that stop in the array
if it DOESN'T, returns the index to the first free slot */

int Find_Par(par** p,char* s){
	int i;
	for(i=0;i<MAX_NUM_PAR;i++){
		if(p[i]!=NULL){
			if(strcmp(p[i]->nome, s) == 0)
				return i;
		}
		else
			return i;
	}
	return(-1);
}

int Is_Text(char c){
	if(c >= '0' && c <= '9')
		return 1;
	if(c >= 'A' && c <= 'Z')
		return 1;
	if(c >= 'a' && c <= 'z')
		return 1;
	if(c == '.')
		return 1;
	return 0;
}

int Count_Args(char* str){
	int i = 0, args = 0, in = 0, special = 0;
	while(i < (int) strlen(str)){
		if(!special && str[i] == '"'){
			special = 1;
			i++;
			continue;
		}
		if(special){
			if(str[i] == '"'){
				special = 0;
				args++;
				i++;
				continue;
			}
			else{
				i++;
				continue;
			}
		}
		if(Is_Text(str[i])){
			i++;
			if(in == 0){
				args++;
				in = 1;
			}
			continue;
		}
		else{
			in = 0;
			i++;
		}
	}
	return args;
}
