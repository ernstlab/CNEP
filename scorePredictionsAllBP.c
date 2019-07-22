#include <stdio.h>
//#include <conio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <time.h>//#include <sys/time.h>
#include <errno.h>
#include <string.h>
#include <assert.h>
#define FILE_PATH_LEN 250


void nrerror (char error_text[])
//Numerical Recipes standard error handler
{
	void exit();
	fprintf(stderr, "Numerical Recipes run-time error...\n");
	fprintf(stderr, "%s\n", error_text);
	fprintf(stderr, "...now exiting to system...\n");
	exit(1);
}
unsigned *vector(int n1, int nh)
//allocates a unsigned vector with range [n1..nh]
{
	unsigned *v;
	v=(unsigned *)malloc((unsigned)(nh-n1+1)*sizeof(unsigned));
	if(!v) nrerror ("allocation failure in vector()");
	return v-n1;
}
double *double_vector(int n1, int nh)
//allocates a double vector with range [n1..nh]
{
	double *v;
	v=(double *)malloc((double)(nh-n1+1)*sizeof(double));
	if(!v) nrerror ("allocation failure in vector()");
	return v-n1;
}
int *int_vector(int n1, int nh)
//allocates an int vector with range [n1..nh]
{
	int *v;
	v=(int *)malloc((int)(nh-n1+1)*sizeof(int));
	if(!v) nrerror ("allocation failure in vector()");
	return v-n1;
}
void free_vector(unsigned *v, int n1, int nh)
//releases a unsigned vector allocated by vector()
{
	free((char*) (v+n1));
}
void free_double_vector(double *v, int n1, int nh)
//releases a double vector allocated by double_vector()
{
	free((char*) (v+n1));
}
unsigned **umatrix(int nr1, int nrh, int nc1, int nch)
//allocates a unsigned matrix with range [nr1..nrh][nc1..nch]
{
	int i;
	unsigned **m;
	//allocatates pointers to rows
	m=(unsigned **) malloc((unsigned) (nrh-nr1+1)*sizeof(unsigned*));
	if (!m) nrerror("allocation failure 1 in dmatrix()");
	m -= nr1;
	//allocate rows and set pointers to them
	for (i=nr1; i<=nrh; i++)
	{
		m[i]=(unsigned *) malloc((unsigned)(nch-nc1+1)*sizeof(unsigned));
		if (!m[i]) nrerror("allocation failure 2 in dmatrix()");
		m[i] -= nc1;
	}
	//return pointer to arrray of pointers to rows
	return m;
}
void free_umatrix(unsigned **m, int nr1, int nrh, int nc1, int nch)
//frees a matrix allocated with dmatrix()
{
	int i;
	for (i=nrh;i>=nr1;i--)
		free((char*) (m[i]+nc1));
	free((char*) (m+nr1));
}
double **dmatrix(int nr1, int nrh, int nc1, int nch)
//allocates a double matrix with range [nr1..nrh][nc1..nch]
{
	int i;
	double **m;
	//allocatates pointers to rows
	m=(double **) malloc((double) (nrh-nr1+1)*sizeof(double*));
	if (!m) nrerror("allocation failure 1 in dmatrix()");
	m -= nr1;
	//allocate rows and set pointers to them
	for (i=nr1; i<=nrh; i++)
	{
		m[i]=(double*) malloc((double)(nch-nc1+1)*sizeof(double));
		if (!m[i]) nrerror("allocation failure 2 in dmatrix()");
		m[i] -= nc1;
	}
	//return pointer to arrray of pointers to rows
	return m;
}
void free_dmatrix(double **m, int nr1, int nrh, int nc1, int nch)
//frees a matrix allocated with dmatrix()
{
	int i;
	for (i=nrh;i>=nr1;i--)
		free((double*) (m[i]+nc1));
	free((double*) (m+nr1));
}
unsigned posStrToUnNum(char s[])
{
		unsigned sNum=0, multiplier=1, currentNum=0;
		int i=0;
		if (s!="") 
		{	
			for (i=0; i<strlen(s); i++)
			{
				if (isdigit(s[i]))
					{
						currentNum = (currentNum*multiplier) + (s[i]-'0');
						multiplier=10;
					}
				else if (s[i] == ',')
					{
						break;
					}
				else
					{
						//printf("Bad data!");
						break;
					}
			}
			sNum=currentNum;
		}
	return sNum;
}
int posStrToInt(char s[])
{
		int sNum=0, multiplier=1, currentNum=0;
		int i=0;
		if (s!="") 
		{	
			for (i=0; i<strlen(s); i++)
			{
				if (isdigit(s[i]))
					{
						currentNum = (currentNum*multiplier) + (s[i]-'0');
						multiplier=10;
					}
				else if (s[i] == ',')
					{
						break;
					}
				else
					{
						//printf("Bad data!");
						break;
					}
			}
			sNum=currentNum;
		}
	return sNum;
}
void tostring(char str[], int num)
{
	int i, rem, len = 0, n;
	n = num;
	while (n != 0)
	{
		len++;
	    n /= 10;
	}
	for (i = 0; i < len; i++)
	{
        rem = num % 10;
        num = num / 10;
        str[len - (i + 1)] = rem + '0';
    }
    str[len] = '\0';
}

int selectChrRow (char* chrN)
{
		if ((strcmp(chrN, "chr1")== 0) || (strcmp(chrN, "1")== 0))
			return 1;
		if ((strcmp(chrN, "chr2")== 0) || (strcmp(chrN, "2")== 0))
			return 2;
		if ((strcmp(chrN, "chr3")== 0) || (strcmp(chrN, "3")== 0))
			return 3;
		if ((strcmp(chrN, "chr4")== 0) || (strcmp(chrN, "4")== 0))
			return 4;
		if ((strcmp(chrN, "chr5")== 0) || (strcmp(chrN, "5")== 0))
			return 5;
		if ((strcmp(chrN, "chr6")== 0) || (strcmp(chrN, "6")== 0))
			return 6;
		if ((strcmp(chrN, "chr7")== 0) || (strcmp(chrN, "7")== 0))
			return 7;
		if ((strcmp(chrN, "chr8")== 0) || (strcmp(chrN, "8")== 0))
			return 8;
		if ((strcmp(chrN, "chr9")== 0) || (strcmp(chrN, "9")== 0))
			return 9;
		if ((strcmp(chrN, "chr10")== 0) || (strcmp(chrN, "10")== 0))
			return 10;
		if ((strcmp(chrN, "chr11")== 0) || (strcmp(chrN, "11")== 0))
			return 11;
		if ((strcmp(chrN, "chr12")== 0) || (strcmp(chrN, "12")== 0))
			return 12;
		if ((strcmp(chrN, "chr13")== 0) || (strcmp(chrN, "13")== 0))
			return 13;
		if ((strcmp(chrN, "chr14")== 0) || (strcmp(chrN, "14")== 0))
			return 14;
		if ((strcmp(chrN, "chr15")== 0) || (strcmp(chrN, "15")== 0))
			return 15;
		if ((strcmp(chrN, "chr16")== 0) || (strcmp(chrN, "16")== 0))
			return 16;
		if ((strcmp(chrN, "chr17")== 0) || (strcmp(chrN, "17")== 0))
			return 17;
		if ((strcmp(chrN, "chr18")== 0) || (strcmp(chrN, "18")== 0))
			return 18;
		if ((strcmp(chrN, "chr19")== 0) || (strcmp(chrN, "19")== 0))
			return 19;
		if ((strcmp(chrN, "chr20")== 0) || (strcmp(chrN, "20")== 0))
			return 20;
		if ((strcmp(chrN, "chr21")== 0) || (strcmp(chrN, "21")== 0))
			return 21;
		if ((strcmp(chrN, "chr22")== 0) || (strcmp(chrN, "22")== 0))
			return 22; 
		if ((strcmp(chrN, "chr23")== 0) || (strcmp(chrN, "23")== 0))
			return 23;
		if (strcmp(chrN, "chrX")== 0)
			return 23;
		if (strcmp(chrN, "chrY")== 0)
			return -1;
		if (strcmp(chrN, "chrM")== 0)
			return -1;
		else
			return -1; //default for just in case
	return 0;
}

int readFromPiFile(char *inputFileName, char response[], int chrom_num)
{												
	char *mode = "r", *my_string, *token, *chrN, *startPos, *endPos;
	const char s[2] = "\t";
	size_t nbytes = 100;
	unsigned startPosNum, endPosNum;
	int position=0, count=0, r=-1;
	FILE * ifp = fopen(inputFileName,mode);
	if (ifp == NULL) {
		fprintf(stderr, "Can't open input file in list!\n");
		exit(1);
	}
	//*********read from pi file
	my_string = (char *) malloc (nbytes + 1);
	while (!feof(ifp)) 
	{
		if( fgets (my_string, nbytes, ifp)!=NULL ) 
		{
			token = strtok(my_string, s); //get the first token
			chrN = token;
			token = strtok(NULL, s);  //get the second token
			startPos = token;
			token = strtok(NULL, s);    //get the third token
			endPos = token;
			token = strtok(my_string, "\n");      //get the rest of the line
			r = selectChrRow(chrN); 
			if (r==chrom_num) //if this line is for current chromosome, mark labels for the positions in the interval as positive
			{
				startPosNum = posStrToUnNum(startPos);
				endPosNum = posStrToUnNum(endPos);
				for (position=startPosNum; position<=endPosNum; position++) //pi file is zero based (so are training positions), start&end inclusive
				{
					response[position]='1';
					count++;//local
				}
			}
		}	
	}
	free(my_string);
	fclose(ifp);
	return count;
}

int readFromOmegaFile(char *inputFileName, char response[], int chrom_num)
{												
	char *mode = "r", *my_string, *token, *chrN, *startPos, *endPos;
	const char s[2] = "\t";
	size_t nbytes = 100;
	unsigned startPosNum, endPosNum;
	int position=0, count=0, r=-1;
	FILE * ifp = fopen(inputFileName,mode);
	if (ifp == NULL) {
		fprintf(stderr, "Can't open input file in list!\n");
		exit(1);
	}
	//*********read from omega file
	my_string = (char *) malloc (nbytes + 1);
	while (!feof(ifp)) 
	{
		if( fgets (my_string, nbytes, ifp)!=NULL ) 
		{
			token = strtok(my_string, s); //get the first token
			chrN = token;
			token = strtok(NULL, s);  //get the second token
			startPos = token;
			token = strtok(NULL, s);    //get the third token
			endPos = token;
			token = strtok(my_string, "\n");      //get the rest of the line
			r = selectChrRow(chrN); 
			if (r==chrom_num) //if this line is for current chromosome, mark labels for the positions in the interval as positive
			{
				startPosNum = posStrToUnNum(startPos);
				endPosNum = posStrToUnNum(endPos);
				for (position=startPosNum; position<=endPosNum; position++) //omega file is zero based (so are training positions), start&end inclusive
				{
					response[position]='1';
					count++;//local
				}
			}
		}	
	}
	free(my_string);
	fclose(ifp);
	return count;
}
int readFromPhastconsFile(char *inputFileName, char response[], int chrom_num)
{												
	char *mode = "r", *my_string, *token, *chrN, *startPos, *endPos;
	const char s[2] = "\t";
	size_t nbytes = 100;
	unsigned startPosNum, endPosNum;
	int position=0, count=0, r=-1;
	FILE * ifp = fopen(inputFileName,mode);
	if (ifp == NULL) {
		fprintf(stderr, "Can't open input file in list!\n");
		exit(1);
	}
	//*********read from phastcons file
	my_string = (char *) malloc (nbytes + 1);
	while (!feof(ifp)) 
	{
		if( fgets (my_string, nbytes, ifp)!=NULL )
		{
			token = strtok(my_string, s); //get the first token
			chrN = token;
			token = strtok(NULL, s);  //get the second token
			startPos = token;
			token = strtok(NULL, s);    //get the third token
			endPos = token;
			token = strtok(my_string, "\n");      //get the rest of the line
			if (strlen(chrN)<=6) //ignore lines with leftover chromosome fragments
			{
				r = selectChrRow(chrN); 
				if (r==chrom_num) //if this line is for current chromosome, mark labels for the positions in the interval as positive
				{
					startPosNum = posStrToUnNum(startPos);
					endPosNum = posStrToUnNum(endPos);
					for (position=startPosNum; position<=endPosNum; position++) //phastCons file is zero based (so are training positions), start&end inclusive
					{
						response[position]='1';
						count++;//local
					}
				}
			}
		}	
	}
	free(my_string);
	fclose(ifp);
	return count;
}
int readFromGERPFile(char inputFileName[], char response[], int chrom_num)
{			
	char *mode = "r", *my_string, *token, *chrN, *startPos, *endPos, fNumStr[3], currentInputFileName[200];
	const char s[2] = "\t";
	size_t nbytes = 100;
	unsigned startPosNum, endPosNum;
	int position=0, count=0, r=-1, f=1;
	for (f=1; f<=23; f++) //read all GERP files (one per chromosome)
	{
		//*********open single GERP file (there is one per chromosome) 1_elems.txt
		strcpy(currentInputFileName, inputFileName);
		if (f!=23)
			tostring(fNumStr,f);//file number
		else
			strcpy(fNumStr, "X");
		strcat(currentInputFileName,fNumStr); 
		strcat(currentInputFileName, "_elems.txt");
		FILE * ifp = fopen(currentInputFileName,"r");
		if (ifp == NULL) {
			fprintf(stderr, "Can't open input file in list %s!\n", currentInputFileName);
			exit(1);
		}
		//*********read from single GERP file
		my_string = (char *) malloc (nbytes + 1);
		fgets (my_string, 100, ifp); //read header line
		r=f; //chromosome number, comes from file number in GERP files
		while (!feof(ifp)) 
		{
			if( fgets (my_string, nbytes, ifp)!=NULL ) 
			{
				token = strtok(my_string, s);  //get the first token
				startPos = token;
				token = strtok(NULL, s);    //get the second token
				endPos = token;
				token = strtok(my_string, "\n");      //get the rest of the line

				if (r==chrom_num) //if this line is for current chromosome, mark labels for the positions in the interval as positive
				{
					startPosNum = posStrToUnNum(startPos)-1;//GERP file is one based, start&end inclusive (-1 to align it to be 0-based)
					endPosNum = posStrToUnNum(endPos)-1;//GERP file is one based, start&end inclusive (-1 to align it to be 0-based)
					for (position=startPosNum; position<=endPosNum; position++) //GERP file is one based, start&end inclusive (-1 to align it to be 0-based)
					{
						response[position]='1';
						count++;//local
					}
				}
			}
		}
		free(my_string);
		fclose(ifp);
	}
	return count;
}

int readTrainingSampleRemoveExons(char *inputFileName, int chrom_num, char responsePi[], char responseOmega[], char responsePhastCons[],char responseGERP[])
{
	char *mode = "r", *my_string, *token, *chrN, *startPos, *endPos;
	const char s[2] = " ";
	size_t nbytes = 100;
	unsigned startPosNum, endPosNum;
	int position=0, count=0, r=-1;	
	FILE * ifp = fopen(inputFileName,mode);
	if (ifp == NULL) {
		fprintf(stderr, "Can't open input file in.list!\n");
		exit(1);
	}
	my_string = (char *) malloc (nbytes + 1);
	while (!feof(ifp)) 
	{
		if( fgets (my_string, 100, ifp)!=NULL ) 
		{
			token = strtok(my_string, s); //get the first token
			chrN = token;
			token = strtok(NULL, s);  //get the second token
			startPos = token;
			token = strtok(NULL, s);    //get the third token
			endPos = token;
			token = strtok(my_string, "\n");      //get the rest of the line
			r = selectChrRow(chrN); 
			if (r==chrom_num) //if this line is for current chromosome, mark labels for the positions in the interval as NEGATIVE (remove exons)
			{
				startPosNum = posStrToUnNum(startPos)-1;//.gtf (exon) file is one based start&end inclusive (-1 to align it to be 0-based)
				endPosNum = posStrToUnNum(endPos)-1; //.gtf (exon) file is one based start&end inclusive (-1 to align it to be 0-based)
				for (position=startPosNum; position<=endPosNum; position++) //.gtf (exon) file is one based start&end inclusive
				{
					responsePi[position]='0';
					responseOmega[position]='0';
					responsePhastCons[position]='0';
					responseGERP[position]='0';
					count++;//local
				}
			}
		}	
	}
	fclose(ifp);
	free(my_string);
	return count;
}

int main(int argc, char *argv[] ) 
{	
	int chromSize[]= {-1, 249250621, 243199373, 198022430, 191154276, 180915260, 171115067, 159138663, 146364022, 141213431, 135534747, 135006516,
		133851895, 115169878, 107349540, 102531392, 90354753, 81195210, 78077248, 59128983, 63025520, 48129895, 51304566, 155270560};
	int chrom_num = 1, position=0, numOfOnes=0, numExons=0;

	if ( argc != 2 ) //argc should be 2 for correct execution (for 1 argument and program name)
    {   
		printf( "usage: %s conserved_elements_file_name\n", argv[0] ); //argv[0] is the program name
		// ./scorePredictionsAllBP cnep_chr ***doesn't use argument!
		exit(1);
    }
	
	for (chrom_num=1; chrom_num<=23; chrom_num++)
	{

		//***initializtions***
		char chrom_num_string[5];
		tostring(chrom_num_string, chrom_num);

		double* probsPositionsPi=double_vector(0, chromSize[chrom_num]);
		if (probsPositionsPi==NULL)
			exit(1);
		double* probsPositionsOmega=double_vector(0, chromSize[chrom_num]);
		if (probsPositionsOmega==NULL)
			exit(1);
		double* probsPositionsPhastCons=double_vector(0, chromSize[chrom_num]);
		if (probsPositionsPhastCons==NULL)
			exit(1);
		double* probsPositionsGERP=double_vector(0, chromSize[chrom_num]);
		if (probsPositionsGERP==NULL)
			exit(1);
		double* probsPositions=double_vector(0, chromSize[chrom_num]);
		if (probsPositions==NULL)
			exit(1);
		char* responsePi = malloc(sizeof(char*)*chromSize[chrom_num]+1); 
		if (responsePi==NULL)
			exit(1);
		char* responseOmega = malloc(sizeof(char*)*chromSize[chrom_num]+1); 
		if (responseOmega==NULL)
			exit(1);
		char* responsePhastCons = malloc(sizeof(char*)*chromSize[chrom_num]+1); 
		if (responsePhastCons==NULL)
			exit(1);
		char* responseGERP = malloc(sizeof(char*)*chromSize[chrom_num]+1); 
		if (responseGERP==NULL)
			exit(1);
		for (position=0; position<chromSize[chrom_num]; position++)	
		{
			probsPositionsPi[position]=0.0; //initialize to zeros
			probsPositionsOmega[position]=0.0; //initialize to zeros
			probsPositionsPhastCons[position]=0.0; //initialize to zeros
			probsPositionsGERP[position]=0.0; //initialize to zeros
			probsPositions[position]=0.0; //initialize to zeros
			responsePi[position]='0'; //initialize to '0' (since '-1' is 2 characters)
			responseOmega[position]='0'; //initialize to '0' (since '-1' is 2 characters)
			responsePhastCons[position]='0'; //initialize to '0' (since '-1' is 2 characters)
			responseGERP[position]='0'; //initialize to '0' (since '-1' is 2 characters)
		}
		
		//***opening files***
		char fileName1[FILE_PATH_LEN] = "/u/project/ernst/ogrujic/wigFiles_l1_modelFiles1_Pi/scores_";
		strcpy(fileName1, strcat(strcat(fileName1, chrom_num_string), ".wig"));
		FILE *ifp1 = fopen(fileName1, "r");
		if (ifp1 == NULL) {
			fprintf(stderr, "Can't open input file %s!\n", fileName1);
			exit(1);
		}

		char fileName2[FILE_PATH_LEN] = "/u/project/ernst/ogrujic/wigFiles_l1_modelFiles1_Omega/scores_";
		strcpy(fileName2, strcat(strcat(fileName2, chrom_num_string), ".wig"));
		FILE *ifp2 = fopen(fileName2, "r");
		if (ifp2 == NULL) {
			fprintf(stderr, "Can't open input file %s!\n", fileName2);
			exit(1);
		}
		char fileName3[FILE_PATH_LEN] = "/u/project/ernst/ogrujic/wigFiles_l1_modelFiles1_Phastcons/scores_";
		strcpy(fileName3, strcat(strcat(fileName3, chrom_num_string), ".wig"));
		FILE *ifp3 = fopen(fileName3, "r");
		if (ifp3 == NULL) {
			fprintf(stderr, "Can't open input file %s!\n", fileName3);
			exit(1);
		}
		char fileName4[FILE_PATH_LEN] = "/u/project/ernst/ogrujic/wigFiles_l1_modelFiles1_GERP/scores_";
		strcpy(fileName4, strcat(strcat(fileName4, chrom_num_string), ".wig"));
		FILE *ifp4 = fopen(fileName4, "r");
		if (ifp4 == NULL) {
			fprintf(stderr, "Can't open input file %s!\n", fileName4);
			exit(1);
		}
		
		char fileName5[FILE_PATH_LEN] = "/u/home/o/ogrujic/project-ernst/CNEPAVG/cnep_chr";
		strcpy(fileName5, strcat(strcat(fileName5, chrom_num_string), ".wig")); //  /u/home/o/ogrujic/project-ernst/CNEPAVG/cnep_chr#.wig
		FILE *ifp5 = fopen(fileName5, "r");
		if (ifp5 == NULL) {
			fprintf(stderr, "Can't open input file %s!\n", fileName5);
			exit(1);
		}

		char fileName6[FILE_PATH_LEN]="/u/home/o/ogrujic/project-ernst/zarlab/scorePredictionsAllBP/Pi_labels_scores/labels_scores_chr";
		strcat (fileName6, chrom_num_string); //chromosome number //labels_scores_sorted_chr#
		FILE *score_file1 = fopen(fileName6, "w");
		if (score_file1 == NULL) {
			fprintf(stderr, "Couldn't open output file %s!\n", fileName6); //labels_scores_sorted_chr# (to write scores and labels for ROC plot)
			exit(1);
		}	

		char fileName7[FILE_PATH_LEN]="/u/home/o/ogrujic/project-ernst/zarlab/scorePredictionsAllBP/Omega_labels_scores/labels_scores_chr";
		strcat (fileName7, chrom_num_string); //chromosome number //labels_scores_sorted_chr#
		FILE *score_file2 = fopen(fileName7, "w");
		if (score_file2 == NULL) {
			fprintf(stderr, "Couldn't open output file %s!\n", fileName7); //labels_scores_sorted_chr# (to write scores and labels for ROC plot)
			exit(1);
		}	

		char fileName8[FILE_PATH_LEN]="/u/home/o/ogrujic/project-ernst/zarlab/scorePredictionsAllBP/PhastCons_labels_scores/labels_scores_chr";
		strcat (fileName8, chrom_num_string); //chromosome number //labels_scores_sorted_chr#
		FILE *score_file3 = fopen(fileName8, "w");
		if (score_file3 == NULL) {
			fprintf(stderr, "Couldn't open output file %s!\n", fileName8); //labels_scores_sorted_chr# (to write scores and labels for ROC plot)
			exit(1);
		}	

		char fileName9[FILE_PATH_LEN]="/u/home/o/ogrujic/project-ernst/zarlab/scorePredictionsAllBP/GERP_labels_scores/labels_scores_chr";
		strcat (fileName9, chrom_num_string); //chromosome number //labels_scores_sorted_chr#
		FILE *score_file4 = fopen(fileName9, "w");
		if (score_file4 == NULL) {
			fprintf(stderr, "Couldn't open output file %s!\n", fileName9); //labels_scores_sorted_chr# (to write scores and labels for ROC plot)
			exit(1);
		}	


		char fileName10[FILE_PATH_LEN]="/u/home/o/ogrujic/project-ernst/zarlab/scorePredictionsAllBP/CNEPAVG_Pi_labels_scores/labels_scores_chr";
		strcat (fileName10, chrom_num_string); //chromosome number //labels_scores_sorted_chr#
		FILE *score_file5 = fopen(fileName10, "w");
		if (score_file5 == NULL) {
			fprintf(stderr, "Couldn't open output file %s!\n", fileName10); //labels_scores_sorted_chr# (to write scores and labels for ROC plot)
			exit(1);
		}	

		char fileName11[FILE_PATH_LEN]="/u/home/o/ogrujic/project-ernst/zarlab/scorePredictionsAllBP/CNEPAVG_Omega_labels_scores/labels_scores_chr";
		strcat (fileName11, chrom_num_string); //chromosome number //labels_scores_sorted_chr#
		FILE *score_file6 = fopen(fileName11, "w");
		if (score_file6 == NULL) {
			fprintf(stderr, "Couldn't open output file %s!\n", fileName11); //labels_scores_sorted_chr# (to write scores and labels for ROC plot)
			exit(1);
		}	

		char fileName12[FILE_PATH_LEN]="/u/home/o/ogrujic/project-ernst/zarlab/scorePredictionsAllBP/CNEPAVG_PhastCons_labels_scores/labels_scores_chr";
		strcat (fileName12, chrom_num_string); //chromosome number //labels_scores_sorted_chr#
		FILE *score_file7 = fopen(fileName12, "w");
		if (score_file7 == NULL) {
			fprintf(stderr, "Couldn't open output file %s!\n", fileName12); //labels_scores_sorted_chr# (to write scores and labels for ROC plot)
			exit(1);
		}	

		char fileName13[FILE_PATH_LEN]="/u/home/o/ogrujic/project-ernst/zarlab/scorePredictionsAllBP/CNEPAVG_GERP_labels_scores/labels_scores_chr";
		strcat (fileName13, chrom_num_string); //chromosome number //labels_scores_sorted_chr#
		FILE *score_file8 = fopen(fileName13, "w");
		if (score_file8 == NULL) {
			fprintf(stderr, "Couldn't open output file %s!\n", fileName13); //labels_scores_sorted_chr# (to write scores and labels for ROC plot)
			exit(1);
		}	

		//***read in scores from .wig file and store in probsPositions array***
		char *my_string, *token;
		const char s[2] = "\n";
		size_t nbytes = 100;
		my_string = (char *) malloc (nbytes + 1);
		position=0;
		while (!feof(ifp1)) 
		{
			if( fgets (my_string, nbytes, ifp1)!=NULL ) 
			{
				token = strtok(my_string, s); //get the first token
				probsPositionsPi[position]= atof(token);
				//printf("%.3f\n", probsPositions[position]);
				position++;
			}
		}

		position=0;
		while (!feof(ifp2)) 
		{
			if( fgets (my_string, nbytes, ifp2)!=NULL ) 
			{
				token = strtok(my_string, s); //get the first token
				probsPositionsOmega[position]= atof(token);
				//printf("%.3f\n", probsPositions[position]);
				position++;
			}
		}

		position=0;
		while (!feof(ifp3)) 
		{
			if( fgets (my_string, nbytes, ifp3)!=NULL ) 
			{
				token = strtok(my_string, s); //get the first token
				probsPositionsPhastCons[position]= atof(token);
				//printf("%.3f\n", probsPositions[position]);
				position++;
			}
		}

		position=0;
		while (!feof(ifp4)) 
		{
			if( fgets (my_string, nbytes, ifp4)!=NULL ) 
			{
				token = strtok(my_string, s); //get the first token
				probsPositionsGERP[position]= atof(token);
				//printf("%.3f\n", probsPositions[position]);
				position++;
			}
		}

		position=0;
		while (!feof(ifp5)) 
		{
			if( fgets (my_string, nbytes, ifp5)!=NULL ) 
			{
				token = strtok(my_string, s); //get the first token
				probsPositions[position]= atof(token);
				//printf("%.3f\n", probsPositions[position]);
				position++;
			}
		}

		free(my_string);

		char gtfFile[200]="/u/home/o/ogrujic/project-ernst/zarlab/sourceDataFiles/gencode.v19.annotation.gtf";
		char exonFile[200]="/u/home/o/ogrujic/project-ernst/zarlab/sourceDataFiles/exon_pos_v19.txt";
		char PiFileName[200]="/u/home/o/ogrujic/project-ernst/zarlab/sourceDataFiles/hg19_29way_pi_lods_elements_12mers.chr_specific.fdr_0.1_with_scores.txt";
		char OmegaFileName[200]="/u/home/o/ogrujic/project-ernst/zarlab/sourceDataFiles/hg19_29way_omega_lods_elements_12mers.chr_specific.fdr_0.1_with_scores.txt";
		char PhastconsFileName[200]="/u/home/o/ogrujic/project-ernst/zarlab/sourceDataFiles/phastconselements_100_hg19.txt";
		char GERPfileName[200]="/u/home/o/ogrujic/project-ernst/zarlab/sourceDataFiles/GERP/hg19_chr";

		//first mark all positions in conserved regions as positive labels
		numOfOnes=readFromPiFile(PiFileName, responsePi, chrom_num); 
		printf("There are %d ones in labels \n", numOfOnes); 
		numOfOnes=readFromOmegaFile(OmegaFileName, responseOmega, chrom_num); 
		printf("There are %d ones in labels \n", numOfOnes);
		numOfOnes=readFromPhastconsFile(PhastconsFileName, responsePhastCons, chrom_num); 
		printf("There are %d ones in labels \n", numOfOnes);
		numOfOnes=readFromGERPFile(GERPfileName, responseGERP, chrom_num); 
		printf("There are %d ones in labels \n", numOfOnes);

		//then mark all positions that are in exons as negative labels (exclude exons)
		numExons=readTrainingSampleRemoveExons(exonFile, chrom_num, responsePi, responseOmega, responsePhastCons, responseGERP);
		printf ("number of exons excluded %d\n", numExons); 

		//***writing to file***
		for (position=0; position<chromSize[chrom_num]; position++) //python code for plotting needs labels as one and zero
		{
			//Pi scores with Pi labels
			fprintf(score_file1, "%c ", responsePi[position]);
			fprintf (score_file1, "%.3f\n", probsPositionsPi[position]); //print to 3 decimals

			//Omega scores with Omega labels
			fprintf(score_file2, "%c ", responseOmega[position]);
			fprintf (score_file2, "%.3f\n", probsPositionsOmega[position]); //print to 3 decimals

			//PhastCons scores with PhastCons labels
			fprintf(score_file3, "%c ", responsePhastCons[position]);
			fprintf (score_file3, "%.3f\n", probsPositionsPhastCons[position]); //print to 3 decimals

			//GERP scores with GERP labels
			fprintf(score_file4, "%c ", responseGERP[position]);
			fprintf (score_file4, "%.3f\n", probsPositionsGERP[position]); //print to 3 decimals

			//CNEPAVG scores with Pi labels:
			fprintf(score_file5, "%c ", responsePi[position]);
			fprintf (score_file5, "%.3f\n", probsPositions[position]); //print to 3 decimals

			//CNEPAVG scores with Omega labels:
			fprintf(score_file6, "%c ", responseOmega[position]);
			fprintf (score_file6, "%.3f\n", probsPositions[position]); //print to 3 decimals

			//CNEPAVG scores with PhastCons labels:
			fprintf(score_file7, "%c ", responsePhastCons[position]);
			fprintf (score_file7, "%.3f\n", probsPositions[position]); //print to 3 decimals

			//CNEPAVG scores with GERP labels:
			fprintf(score_file8, "%c ", responseGERP[position]);
			fprintf (score_file8, "%.3f\n", probsPositions[position]); //print to 3 decimals
		}
		//***clean up****
		free_double_vector(probsPositionsPi, 0, chromSize[chrom_num]); 
		free_double_vector(probsPositionsOmega, 0, chromSize[chrom_num]); 
		free_double_vector(probsPositionsPhastCons, 0, chromSize[chrom_num]); 
		free_double_vector(probsPositionsGERP, 0, chromSize[chrom_num]); 
		free_double_vector(probsPositions, 0, chromSize[chrom_num]); 
		free(responsePi);
		free(responseOmega);
		free(responsePhastCons);
		free(responseGERP);
		fclose(ifp1);
		fclose(ifp2);
		fclose(ifp3);
		fclose(ifp4);
		fclose(ifp5);
		fclose(score_file1);
		fclose(score_file2);
		fclose(score_file3);
		fclose(score_file4);
		fclose(score_file5);
		fclose(score_file6);
		fclose(score_file7);
		fclose(score_file8);
	}
	return 0;
}