#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"functions.h"

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

void Modo_L(char* s, car **c, par **p){
	int i_c = 0, i_p_ori = 0, i_p_des = 0;
	char **ret = NULL, *temp = NULL;
	double cost = -1, dur = -1;
	lis_par *l_temp = NULL;

	if(Count_Args(s)!=6){
		printf("Not enough arguments for mode L\n");
		exit(-1);
	}

	ret = Get_Name(MAX_NOME_CAR,s);
	i_c = Find_Car(c,ret[0]);

	if(c[i_c] == NULL){
		printf("%s: no such line.\n", ret[0]);
		if(ret[0]!=NULL)
			free(ret[0]);
		free(ret);
		return;
	}

	temp = ret[1]-1;

	if(ret[0]!=NULL)
		free(ret[0]);
	free(ret);

	ret = Get_Name(MAX_NOME_PAR,temp);
	i_p_ori = Find_Par(p,ret[0]);

	if(p[i_p_ori] == NULL){
		printf("%s: no such stop.\n", ret[0]);
		if(ret[0]!=NULL)
			free(ret[0]);
		free(ret);
		return;
	}

	temp = ret[1]-1;

	if(ret[0]!=NULL)
		free(ret[0]);
	free(ret);

	ret = Get_Name(MAX_NOME_PAR,temp);
	i_p_des = Find_Par(p,ret[0]);

	if(p[i_p_des] == NULL){
		printf("%s: no such stop.\n", ret[0]);
		if(ret[0]!=NULL)
			free(ret[0]);
		free(ret);
		return;
	}

	if(ret[0]!=NULL)
		free(ret[0]);
	free(ret);

	if(sscanf(ret[1], "%lf %lf", &cost, &dur) != 2)
		exit(-1);
	
	if(cost < 0 || dur < 0){
		printf("negative cost or duration\n");
		return;
	}
	
	if(c[i_c]->ori == NULL){
		c[i_c]->ori = Init_lis_par_cell();
		c[i_c]->ori->this = p[i_p_ori];

		c[i_c]->dest = Init_lis_par_cell();
		c[i_c]->dest->this = p[i_p_des];

		c[i_c]->dest->prev = c[i_c]->ori;
		c[i_c]->ori->next = c[i_c]->dest;

		c[i_c]->cost += cost;
		c[i_c]->dur += dur;

	}
	else{
		if(!Check_Lig(c[i_c],p[i_p_ori],p[i_p_des])){
			printf("link cannot be associated with bus line.\n");
			return;
		}
		if(p[i_p_des] == c[i_c]->ori->this){
			l_temp = Init_lis_par_cell();
			l_temp->this = p[i_p_ori];

			l_temp->next = c[i_c]->ori;
			c[i_c]->ori->prev = l_temp;
			c[i_c]->ori = l_temp;
			
			c[i_c]->cost += cost;
			c[i_c]->dur += dur;
		}
		else if(p[i_p_ori] == c[i_c]->dest->this){
			l_temp = Init_lis_par_cell();
			l_temp->this = p[i_p_des];

			l_temp->prev = c[i_c]->dest;
			c[i_c]->dest->next = l_temp;
			c[i_c]->dest = l_temp;
			
			c[i_c]->cost += cost;
			c[i_c]->dur += dur;
		}
	}


}