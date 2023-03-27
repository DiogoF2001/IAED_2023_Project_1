#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"functions.h"

void Modo_C(char* s, car** c){
	int args=0, i;
	char *nome, *inv;
	char useless;

	nome=malloc(sizeof(char)*(MAX_NOME_CAR+1));
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
			exit(1);
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
			exit(1);
		i = Find_Car(c,nome);
		if(c[i] == NULL){
			c[i] = Init_Car();
			strcpy(c[i]->nome,nome);
		}
		else{
			if(strncmp(inv,"inverso",strlen(inv) == 0 && strlen(inv)>=3))
				Print_Car(NULL,c[i],1);
			else
				printf("incorrect sort option.\n");
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
			exit(0);
		}
		nome = ret[0];
		i = Find_Par(p,nome);
		if(p[i]==NULL){
			printf("%s: no such stop.\n", nome);
			break;;
		}
		Print_Par(NULL,p[i]);
		break;
	
	case 4:
		ret = Get_Name(MAX_NOME_PAR,s);
		if(ret == NULL){
			printf("RET == NULL\n");
			exit(0);
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
				exit(0);
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

/*
Missing loop lines and interceptions sorting!!!!
*/

void Modo_L(char* s, car **c, par **p){
	int i_c = 0, i_p_ori = 0, i_p_des = 0;
	char **ret = NULL, *temp = NULL;
	double cost = -1, dur = -1;
	lis_par *l_p_temp = NULL;

	if(Count_Args(s)!=6){
		printf("Not enough arguments for mode L\n");
		exit(0);
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

	if(sscanf(ret[1], "%lf %lf", &cost, &dur) != 2)
		exit(0);
	
	if(ret[0]!=NULL)
		free(ret[0]);
	free(ret);

	if(cost < 0 || dur < 0){
		printf("negative cost or duration.\n");
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

		c[i_c]->num_par = 2;
	}
	else{
		if(!Check_Lig(c[i_c],p[i_p_ori],p[i_p_des])){
			printf("link cannot be associated with bus line.\n");
			return;
		}
		if(p[i_p_ori] == c[i_c]->dest->this && p[i_p_des] == c[i_c]->ori->this){
			l_p_temp = Init_lis_par_cell();
			l_p_temp->this = p[i_p_des];

			l_p_temp->prev = c[i_c]->dest;
			c[i_c]->dest->next = l_p_temp;
			c[i_c]->dest = l_p_temp;
			
			c[i_c]->cost += cost;
			c[i_c]->dur += dur;

			c[i_c]->num_par ++;
		}
		else if(p[i_p_ori] == c[i_c]->dest->this){
			if(Find_Par_in_Lis(p[i_p_des],c[i_c]->ori) == NULL)
				c[i_c]->num_par++;

			l_p_temp = Init_lis_par_cell();
			l_p_temp->this = p[i_p_des];

			l_p_temp->prev = c[i_c]->dest;
			c[i_c]->dest->next = l_p_temp;
			c[i_c]->dest = l_p_temp;
			
			c[i_c]->cost += cost;
			c[i_c]->dur += dur;
		}
		else if(p[i_p_des] == c[i_c]->ori->this){
			if(Find_Par_in_Lis(p[i_p_ori],c[i_c]->ori) == NULL)
				c[i_c]->num_par++;

			l_p_temp = Init_lis_par_cell();
			l_p_temp->this = p[i_p_ori];

			l_p_temp->next = c[i_c]->ori;
			c[i_c]->ori->prev = l_p_temp;
			c[i_c]->ori = l_p_temp;
			
			c[i_c]->cost += cost;
			c[i_c]->dur += dur;
		}
	}

	if(Find_Car_in_Lis(c[i_c],p[i_p_ori]->cars) == NULL){
		p[i_p_ori]->num_car ++;
		Add_to_Car_lis(c[i_c],p[i_p_ori]);
	}
	if(Find_Car_in_Lis(c[i_c],p[i_p_des]->cars) == NULL){
		p[i_p_des]->num_car ++;
		Add_to_Car_lis(c[i_c],p[i_p_des]);
	}
	

}

void Modo_I(par** p){
	int i;
	lis_car *temp=NULL;
	for(i=0;i<MAX_NUM_PAR && p[i] != NULL;i++){
		if(p[i]->num_car>1){
			printf("%s %d:", p[i]->nome, p[i]->num_car);
			temp = p[i]->cars;
			while(temp != NULL){
				printf(" %s", temp->this->nome);
				temp = temp->next;
			}
			printf("\n");
		}
	}
	
}