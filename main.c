#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"functions.h"

#define BUFFER_SIZE 256
#define max_input BUFSIZ

int main(){
	int i;
	char mode, *temp = NULL, *s = NULL;
	car **carreiras_all;
	par **paragens_all;

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
			default:
				break;
		}
		s = fgets(s,max_input,stdin);
	}
	for(i=0;i<MAX_NUM_CAR && carreiras_all[i]!=NULL;i++)
		free(carreiras_all[i]);
	for(i=0;i<MAX_NUM_PAR && paragens_all[i]!=NULL;i++)
		free(paragens_all[i]);
	free(carreiras_all);
	free(paragens_all);
	free(temp);
	free(s);
	return 0;
}
