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
	p->prev = NULL;
	p->next = NULL;
	return p;
}

lig* Init_Lig(){
	lig *l;
	l = malloc(sizeof(par));
	if(l==NULL){
		printf("ERROR: memory allocation\n");
		exit(-1);
	}
	l->carr = NULL;
	l->ori = NULL;
	l->des = NULL;
	l->cost = 0;
	l->dur = 0;
	return l;
}

int Ckeck_Lig(car* c, par* ori, par *dest){
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

	ret[0] = malloc(sizeof(char)*max);
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
		printf("%s ", c->nome);
		/*REVIEW*******************************************************/
		if(c->ori != NULL && c->dest != NULL)
			switch (inv){
				/*If it IS supposed to invert the order*/
				case '1':
					next = c->dest;
					while(next!=c->ori){
						printf("%s, ", next->this->nome);
						next = next->prev;
					}
					printf("%s", c->ori->this->nome);
					break;
				/*If it IS NOT supposed to invert the order*/
				case '0':
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
	exit(-1);
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
	exit(-1);
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

void Modo_C(char* s, car** c){
	int args=0, i;
	char *nome, *inv;
	char useless;

	nome=malloc(sizeof(char)*MAX_NOME_CAR);
	if(nome == NULL){
		printf("ERROR: memory allocation\n");
		exit(-1);
	}

	inv=malloc(sizeof(char)*(strlen("inverso")+1));
	if(inv == NULL){
		printf("ERROR: memory allocation\n");
		exit(-1);
	}

	args = Count_Args(s);
	switch (args)
	{
	case 1:
		Print_Car(c,NULL,0);
		break;
	
	case 2:
		if(sscanf(s,"%c %s", &useless, nome)!=2)
			exit(-1);
		i = Find_Car(c,nome);
		if(c[i] == NULL){
			c[i] = Init_Car();
			strcpy(c[i]->nome,nome);
		}
		else
			Print_Car(NULL,c[i],0);
		break;
	
	case 3:
		if(sscanf(s,"%c %s %s", &useless, nome, inv)!=3)
			exit(-1);
		i = Find_Car(c,nome);
		if(c[i] == NULL){
			c[i] = Init_Car();
			strcpy(c[i]->nome,nome);
		}
		else{
			if(strncmp(inv,"inverso",strlen(inv) == 0 && strlen(inv)>=3))
				Print_Car(NULL,c[i],1);
			else
				printf("incorrect sort option\n");
		}
		break;
	
	default:
		break;
	}
	free(nome);
	free(inv);
}

void Modo_P(char *s, par** p){
	int args=0, i;
	double lat = 0, lon = 0;
	char *nome = NULL, *temp = NULL, **ret = NULL;

	args = Count_Args(s);

	switch (args)
	{
	case 1:
		Print_Par(p,NULL);
		break;
	
	case 2:
		ret = Get_Name(MAX_NOME_PAR,s);
		if(ret == NULL){
			printf("RET == NULL\n");
			exit(-1);
		}
		nome = ret[0];
		i = Find_Par(p,nome);
		if(p[i]==NULL){
			printf("%s: no such stop.\n", nome);
		}
		break;
	
	case 4:
		ret = Get_Name(MAX_NOME_PAR,s);
		if(ret == NULL){
			printf("RET == NULL\n");
			exit(-1);
		}
		nome = ret[0];
		temp = ret[1];
		i = Find_Par(p,nome);
		if(p[i]!=NULL){
			printf("%s: stop already exists.\n", nome);
		}
		else{
			p[i] = Init_Par();
			if(sscanf(temp,"%lf %lf", &lat, &lon) != 2)
				exit(-1);
			strcpy(p[i]->nome,nome);
			p[i]->lat = lat;
			p[i]->lon = lon;
			
		}
		break;

	default:
		break;
	}

	if(nome != NULL)
		free(nome);
	if(ret != NULL)
		free(ret);
}