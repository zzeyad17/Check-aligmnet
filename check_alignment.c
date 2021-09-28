/**
 * @Author:    zeyad mohsen
 * @Created:   13.11.2020
 * @Title: assignment lec(10)
 * 
 * 
 * (c) Copyright by NTI C&Embedded-c ClassB ED
 **/
#include <stdio.h>
#include <string.h>
#include "STD_TYPES.h"	
s32 arr_max_element(s32* arr, s32 length);
u8 is_aligned(s32* arr, s32 length);
#define WORDS_NUM 1000
#define WORDS_LENGTH 300
#define STRUCT_NUM 50
#define MEMBERS_NUM 6
int main() {
	struct structures {
				 char 			name[WORDS_LENGTH];
				 s32				member_dts[MEMBERS_NUM];
				 s32				structure_dt;
				 u8					is_align;
	} arr_structures[STRUCT_NUM];
	 

	FILE *fp;
	char ch;
	char word[WORDS_NUM][WORDS_LENGTH];
	char cases[STRUCT_NUM][WORDS_NUM];
	s32 i = 0, j = 0, k, z, f, y = 0;
/*******************Printing the case************************/
	//printf("Case:\n");
	fp = fopen("testCases.txt", "r");
	ch = fgetc(fp);
	while(ch != EOF){
		//printf("%c", ch);
		if(ch == '}'){
			y++;
			i = 0;
			ch = fgetc(fp);
			ch = fgetc(fp);
			ch = fgetc(fp);
		}
	  cases[y][i] = ch;
	  ch = fgetc(fp);
		i++;
	}
	//printf("%s", cases[1]);
	fclose(fp);
	ch = ' ';	
	
	//printf("\n\n");
/*************************************************************/
	fp = fopen("testCases.txt", "r");
/******************filling the word array***********************/	
	while(ch != EOF){
	
		ch = fgetc(fp);
		j = 0;
		while((ch != ' ') && (ch != '\n') && (ch != EOF) && (ch != '\t')){
			word[i][j] = ch;
			ch = fgetc(fp);
			j++;
		}
		
		word[i][j] = '\0';
	
		//printf("%s\n", word[i]);
		i++;
	}
/************************************************************/
	j = 0;
	for(i = 0; i < WORDS_LENGTH; i++){
		if(strcmp(word[i], "struct") == 0){
			strcpy(arr_structures[j].name, word[i + 1]);
			//printf("%s\n", arr_structures[j].name);
		}
		if(strcmp(word[i], "{") == 0){
			//printf("Members:\n");
			for(z = 0; z < MEMBERS_NUM; z++){
				arr_structures[j].member_dts[z] = 0;
			}
			/*structure members loop*/
			for(k = i + 1; k < (MEMBERS_NUM*2) + i + 1; k = k + 2){
				if(strcmp(word[k], "};") != 0){
					if(strcmp(word[k], "u32") == 0){ 
						arr_structures[j].member_dts[(k - (i + 1))/2] = 4;
						//printf("%d\n", arr_structures[j].member_dts[(k - (i + 1))/2]);
					}
					else if(strcmp(word[k], "u16") == 0){
						arr_structures[j].member_dts[(k - (i + 1))/2] = 2;
						//printf("%d\n", arr_structures[j].member_dts[(k - (i + 1))/2]);

					}
					else if(strcmp(word[k], "u8") == 0){
						arr_structures[j].member_dts[(k - (i + 1))/2] = 1;
						//printf("%d\n", arr_structures[j].member_dts[(k - (i + 1))/2]);

					}
					else if(strcmp(word[k], "struct") == 0){
						k = k + 1;
						for(f = 0; f < STRUCT_NUM; f++){
							if(strcmp(arr_structures[f].name, word[k]) == 0){
								arr_structures[j].member_dts[((k - 1) - (i + 1))/2] = arr_structures[f].structure_dt;
								//printf("%d\n", arr_structures[j].member_dts[((k - 1) - (i + 1))/2]);
								break;
							}
						}
					}
					//printf("k = %d\n",k);
				}
				else{
					arr_structures[j].structure_dt = arr_max_element(arr_structures[j].member_dts,MEMBERS_NUM );
					//printf("%d\n", arr_structures[j].structure_dt);
					arr_structures[j].is_align = is_aligned(arr_structures[j].member_dts, MEMBERS_NUM);
					//printf("%d\n", arr_structures[j].is_align);
					if(arr_structures[j].is_align != 0){
						printf("%s};\n", cases[j]);
						printf("\t(%s is alignment(%d Bytes) & optimized to the rules)\n\n", arr_structures[j].name, arr_structures[j].structure_dt);
					}
					else{
						printf("%s};\n", cases[j]);
						
						printf("\t(%s is alignment(%d Bytes) & not optimized to the rules)\n\n", arr_structures[j].name, arr_structures[j].structure_dt);
					}
					j++;
				 	break;
				}
			} /*end of members loop*/
			
		}
		
	}	



	return 0;	
}
/***********************************************************************************************/

s32 arr_max_element(s32* arr, s32 length){
	s32 max = arr[0], i;
	for(i = 1; i < length; i++){
		if(arr[i] > max)
			max = arr[i];
	}
	return max;
}
/***********************************************************************************************/
u8 is_aligned(s32* arr, s32 length){
	u8 i;
	u8 ascending = 1;
	u8 descending = 1;
	
	for(i = 0; i < length - 1; i++){
		if(arr[i] > arr[i + 1]){
			ascending = 0;
			break;
		}
	}	
	for(i = 0; i < length - 1; i++){
		if(arr[i] < arr[i + 1]){
			descending = 0;
			break;
		}		
	}
	
	return (ascending || descending);
}












