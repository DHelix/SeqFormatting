//#####################################################################################
//Author: DHelix
//Date: March 11, 2011
//Version: 1.0
//Contact: j.d.helix@gmail.com
//
//How to use this program:
//	1. Copy the file containing DNA sequence on Desktop. Rename it as "D.txt"
//	2. Copy the file containing Protein sequence on Desktop. Rename it as "P.txt"
//	3. Run the program and it will generate a new txt file named "new.txt" on your 
//	   desktop with formatted sequence.
//#####################################################################################



#include <stdio.h>
#include <stdlib.h> //function itoa
#include <time.h>
#include<math.h> // modulus operator
#include <memory.h> //function memset, set initial value for array

#include <dirent.h>
#include <string.h>

#define DNA_LEN 30000 //the length of string for saving DNA squence.
#define PRO_LEN 10000 //the length of string for saving corresponding protein sequence.

#define LABEL_NUM 5 //for the number labeled at the begining of each line

#define FILE_LEN 50 //the length of string for saving file names.
#define DIR_LEN 100 //the length of string for saving directory.



int main()
{
	//#########################  PART 0: DEFINE & DECLARATION  #########################
	
	char *itoa(int value, char *string, int radix);
	
	int i=0,j=0,m=0; //counting
	
	//	char DNADirPath[DIR_LEN]; //store directory of DNA sequenc file
	//	gets(DNADirPath); //get directory from input
	char *DNADirPath="/Users/Dan/Desktop/D.txt";
	char DNASeq[DNA_LEN]; //store DNA sequence read from the file
	
	//	char ProDirPath[DIR_LEN]; //store directory of protein sequenc file
	//	gets(ProDirPath); //get directory from input
	char *ProDirPath="/Users/Dan/Desktop/P.txt";
	char ProSeq[DNA_LEN]; //store protein sequence read from the file
	
	
	//############################  PART I: GET DNA & PROTEIN SEQUENCE, STORE IN CHARS ############################
	
	//Read DNA sequence from file
	FILE *fpD;
	
	if((fpD=fopen(DNADirPath,"r"))==NULL)
	{
		printf("cannot open file\n");
		exit(0);
	}
	
	i=0;
	while(!feof(fpD))
	{
		fscanf(fpD,"%c",& DNASeq[i]);
		if ((DNASeq[i]!='\0') && (DNASeq[i]!='\n') && (DNASeq[i]!='\t') && (DNASeq[i]!=' ')) {
			i++;
		}
		DNASeq[i]='\0'; //delete the last char
	}
	fclose(fpD);
	
	
	//Read protein sequence from file
	FILE *fpP;
	
	if((fpP=fopen(ProDirPath,"r"))==NULL)
	{
		printf("cannot open file\n");
		exit(0);
	}
	
	i=0;
	while(!feof(fpP))
	{
		fscanf(fpP,"%c",& ProSeq[i]);
		if ((ProSeq[i]!='\0') && (ProSeq[i]!='\n') && (ProSeq[i]!='\t') && (ProSeq[i]!=' ')) {
			i++;
		}
		ProSeq[i]='*'; //Add stop codon
	}
	fclose(fpP);
	
	
	//#########################  PART II: REQUEST FORMATTING PARAMETERS  #########################
	
	//How many aa per line?
	printf("How many aa per line?\n");
	int AaPerLine;
	scanf("%d", & AaPerLine);
	int NtPerLine=AaPerLine*3;
	
	//Add spacing at every ___ aa?
	printf("Add spacing between aa?\n If YES, enter spacing at every ___ aa?\n If No, input 0 (zero)\n");
	int SpcPerAa;
	scanf("%d", & SpcPerAa);
	if (SpcPerAa==0){
		SpcPerAa=AaPerLine; //if do not add spacing, set SpcPerAa=AaPerLine
	}
	
	int SpcNum=AaPerLine/SpcPerAa-1;
	
	//How many space lines are going to be added?
	printf("Add space lines?\n If YES, enter the number of space lines?\n If NO, input 0 (zero)\n");
	int SpcLineNum;
	scanf("%d", & SpcLineNum);	
	
	
	//#########################  PART III: FORMATTING  #########################
	
	
	
	int NtLines=ceil((double)strlen(DNASeq)/NtPerLine);
	
	char FormattedSeq[NtPerLine+SpcNum+LABEL_NUM+1][NtLines*(SpcLineNum+2)];
	memset(FormattedSeq, ' ', sizeof(FormattedSeq)); //set initial value = ' ' for each element in FormattedSeq
	
	char DNALabel[LABEL_NUM], ProLabel[LABEL_NUM];
	
	
	int k=0,kk=0; //DNASeq[k], ProSeq[kk]
	for(k=0;k<=(strlen(DNASeq)-1);){  //read until reach the end of DNA sequence (DNA seq should always be longer than protein seq)
		for(i=0;i<=(NtLines*(SpcLineNum+2)-1);i=i+(SpcLineNum+2)){ //Row cycle. don't forget the spacing lines
			for(j=0;(j<=NtPerLine+SpcNum) && (DNASeq[k]!='\0');){ //column cycle.
				if (!(ceil((j+1)%(SpcPerAa*3+1)))) { //insert one space (skip) every SpcPerAa amino acids
					j++;
				}
				else {
					FormattedSeq[j][i]=DNASeq[k]; //read DNA seq into final array.
					if (!(ceil((k+2)%3))) { //align the aa codon just under the second DNA codon
						FormattedSeq[j][i+1]=ProSeq[kk];
						kk++;
					}
					j++;
					k++;
				}
				
			}
			j++;
			itoa(k,DNALabel,10);
			itoa(kk,ProLabel,10);
			for(m=0;m<=(strlen(DNALabel)-1);m++){ //Add labels at the end of each line
				FormattedSeq[j][i]=DNALabel[m];
				FormattedSeq[j][i+1]=ProLabel[m];
				j++;
			}				
			printf("\n");
		}
	}
	
	
	
	//#########################  PART IV: OUTPUT FORMATTED SEQUENCE ON SCREEN AND INTO A FILE  #########################
	
	//print the final formatted sequence on screen
	for(i=0;i<=NtLines*(SpcLineNum+2)-1;i++){
		for(j=0; j<=NtPerLine+SpcNum+LABEL_NUM;j++)
			printf("%c", FormattedSeq[j][i]);
		printf("\n");
	}
	
	char *NewFileName="/Users/Dan/Desktop/new.txt";
	
	FILE *fpO = fopen(NewFileName, "w");
	
	if(NewFileName)
	{			
		if(!fpO)
		{
			printf("create and open file failed\n");
		}
		for(i=0;i<=NtLines*(SpcLineNum+2)-1;i++){
			for(j=0; j<=NtPerLine+SpcNum+LABEL_NUM;j++)
				fprintf(fpO,"%c",FormattedSeq[j][i]);
			fprintf(fpO,"\n");
		}
		
		fclose(fpO);
	}
}
	
	


	
	