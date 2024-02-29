#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"functions.h"

#define BUFFER_SIZE 256
#define max_input BUFSIZ

int main(){
	int i;
	char mode, *temp = NULL, *s = NULL;
	car **carreiras_all = NULL;
	par **paragens_all = NULL;
	lis_par *temp_p = NULL;
	lis_car *temp_c = NULL;

	s = malloc(sizeof(char)*max_input);
	if(s==NULL){
		printf("ERROR: memory allocation\n");
		exit(-1);
	}

	carreiras_all = malloc(sizeof(car*)*MAX_NUM_CAR);
	if(carreiras_all == NULL){
		printf("ERROR: memory allocation\n");
		exit(-1);
	}
	
	for(i = 0; i<MAX_NUM_CAR; i++)
		carreiras_all[i] = NULL;
	
	paragens_all = malloc(sizeof(par*)*MAX_NUM_PAR);
	if(paragens_all == NULL){
		printf("ERROR: memory allocation\n");
		exit(-1);
	}
	
	for(i = 0; i<MAX_NUM_PAR; i++)
		paragens_all[i] = NULL;
	
	s = fgets(s,max_input,stdin);
	
	while(s != NULL){
		if(sscanf(s,"%c",&mode)!=1)
			exit(-1);
		switch (mode){
			case 'q':
				free(s);
				s=NULL;
				continue;
				break;
			
			case 'c':
				Modo_C(s,carreiras_all);
				break;
			
			case 'p':
				Modo_P(s,paragens_all);
				break;

			case 'l':
				Modo_L(s,carreiras_all,paragens_all);
				break;
			
			case 'i':
				Modo_I(paragens_all);
				break;

			default:
				break;
		}
		s = fgets(s,max_input,stdin);
	}
	for(i=0;i<MAX_NUM_CAR && carreiras_all[i]!=NULL;i++){
		if(carreiras_all[i]->ori!=NULL)
			for(temp_p = carreiras_all[i]->ori->next; temp_p != NULL;
			 temp_p = temp_p->next)
				free(temp_p->prev);
		if(carreiras_all[i]->dest!=NULL)
			free(carreiras_all[i]->dest);
		free(carreiras_all[i]);
	}
	for(i=0;i<MAX_NUM_PAR && paragens_all[i]!=NULL;i++){
		if(paragens_all[i]->cars != NULL){
			for(temp_c = paragens_all[i]->cars->next;
			temp_c != NULL;
			temp_c = temp_c->next){
				free(paragens_all[i]->cars);
				paragens_all[i]->cars = temp_c;
			}
			free(paragens_all[i]->cars);
		}
		free(paragens_all[i]);
	}
	free(carreiras_all);
	free(paragens_all);
	free(temp);
	free(s);
	return 0;
}
