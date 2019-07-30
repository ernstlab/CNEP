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
void free_umatrix(unsigned **m, int nr1, int nrh, int nc1, int nch)
//frees a matrix allocated with dmatrix()
{
	int i;
	for (i=nrh;i>=nr1;i--)
		free((char*) (m[i]+nc1));
	free((char*) (m+nr1));
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
int selectChr (char* chrN)
{
		if (strcmp(chrN, "1")== 0)
			return 1;
		if (strcmp(chrN, "2")== 0)
			return 2;
		if (strcmp(chrN, "3")== 0)
			return 3;
		if (strcmp(chrN, "4")== 0)
			return 4;
		if (strcmp(chrN, "5")== 0)
			return 5;
		if (strcmp(chrN, "6")== 0)
			return 6;
		if (strcmp(chrN, "7")== 0)
			return 7;
		if (strcmp(chrN, "8")== 0)
			return 8;
		if (strcmp(chrN, "9")== 0)
			return 9;
		if (strcmp(chrN, "10")== 0)
			return 10;
		if (strcmp(chrN, "11")== 0)
			return 11;
		if (strcmp(chrN, "12")== 0)
			return 12;
		if (strcmp(chrN, "13")== 0)
			return 13;
		if (strcmp(chrN, "14")== 0)
			return 14;
		if (strcmp(chrN, "15")== 0)
			return 15;
		if (strcmp(chrN, "16")== 0)
			return 16;
		if (strcmp(chrN, "17")== 0)
			return 17;
		if (strcmp(chrN, "18")== 0)
			return 18;
		if (strcmp(chrN, "19")== 0)
			return 19;
		if (strcmp(chrN, "20")== 0)
			return 20;
		if (strcmp(chrN, "21")== 0)
			return 21;
		if (strcmp(chrN, "22")== 0)
			return 22; 
		if (strcmp(chrN, "X")== 0)
			return 23;
		if (strcmp(chrN, "23")== 0)
			return 23;
		if (strcmp(chrN, "Y")== 0)
			return -1;
		if (strcmp(chrN, "M")== 0)
			return -1;
	return 0;
}
int selectChrNum (char* chrN)
{
		if (strcmp(chrN, "chr1")== 0)
			return 1;
		if (strcmp(chrN, "chr2")== 0)
			return 2;
		if (strcmp(chrN, "chr3")== 0)
			return 3;
		if (strcmp(chrN, "chr4")== 0)
			return 4;
		if (strcmp(chrN, "chr5")== 0)
			return 5;
		if (strcmp(chrN, "chr6")== 0)
			return 6;
		if (strcmp(chrN, "chr7")== 0)
			return 7;
		if (strcmp(chrN, "chr8")== 0)
			return 8;
		if (strcmp(chrN, "chr9")== 0)
			return 9;
		if (strcmp(chrN, "chr10")== 0)
			return 10;
		if (strcmp(chrN, "chr11")== 0)
			return 11;
		if (strcmp(chrN, "chr12")== 0)
			return 12;
		if (strcmp(chrN, "chr13")== 0)
			return 13;
		if (strcmp(chrN, "chr14")== 0)
			return 14;
		if (strcmp(chrN, "chr15")== 0)
			return 15;
		if (strcmp(chrN, "chr16")== 0)
			return 16;
		if (strcmp(chrN, "chr17")== 0)
			return 17;
		if (strcmp(chrN, "chr18")== 0)
			return 18;
		if (strcmp(chrN, "chr19")== 0)
			return 19;
		if (strcmp(chrN, "chr20")== 0)
			return 20;
		if (strcmp(chrN, "chr21")== 0)
			return 21;
		if (strcmp(chrN, "chr22")== 0)
			return 22; 
		if (strcmp(chrN, "chr23")== 0)
			return 23;
		if (strcmp(chrN, "chrX")== 0)
			return 23;
		if (strcmp(chrN, "chrY")== 0)
			return -1;
		if (strcmp(chrN, "chrM")== 0)
			return -1;
	return 0;
}

void writePosProfFile(double *probsPositions, int size, FILE *ofp, int chrNum)
{
	int position=0;
	fprintf (ofp, "track type=wiggle_0 name=BED description='Stacking Scores' visibility=2\n"); //wig file header
	fprintf (ofp, "fixedStep chrom=%d start=1 step=1\n", chrNum); //wig file header
	for (position=0; position<size; position++) 
		fprintf (ofp, "%.3f\n",probsPositions[position]); //print to 3 decimals
}
double readModelFeatures(FILE *ifp, double** modelVectors, int numOfFeatures, int modelFileNumber)
{
	char *mode = "r", *my_string;
	double intercept, coefficient;
	int line=1, numRows, numCols, bytes_read=-1;	
	size_t nbytes = 100;
	my_string = (char *) malloc (nbytes + 1);
	//for (line=1; line<=8; line++) //ignores header 8 lines for l1 log reg model file
	for (line=1; line<=6; line++) //ignores header 6 lines for lib linear
	{
		bytes_read = getline (&my_string, &nbytes, ifp); //reads in line from file as a string of nbytes
		if (bytes_read == -1)
		{
			printf ("ERROR!");
		}
	}
	//fscanf(ifp, "%d %d", &numrows, &numcols);//for l1 log reg model file
	//fscanf(ifp, "%lf", &intercept);//1st line in l1 log reg matrix
	line=1;
	while (!feof(ifp)) 
	{
		if (line>numOfFeatures)
		{
			fscanf(ifp, "%lf", &intercept); //last line in liblinear matrix
		}
		else
		{
			fscanf(ifp, "%lf", &coefficient);
			modelVectors[line][modelFileNumber]=coefficient; //line will start with 1 and should go to number of features
			line++; 
		}
	}
	return intercept;
}

int featurePresent(char startPos[], char endPos[], int numOfFiles, int numOfFeatures, double** modelVectors, double** probsPositions, unsigned* featurePresence, FILE* ofpFL, int size, int begin_pos, int end_pos, int numOfModelFiles)
{
	unsigned startPosNum, endPosNum;
	int c=0, numOfOnes=0;

	//Jason's fix for bug about peaks on the boundaries
	startPosNum = (begin_pos > posStrToUnNum(startPos) ? begin_pos : posStrToUnNum(startPos)); // maximum of begin_pos and tartPos
	endPosNum = (end_pos < posStrToUnNum(endPos) ? end_pos : posStrToUnNum(endPos)); // minimum of end_pos and endPos

	if ((startPosNum>=begin_pos) && (endPosNum<=end_pos)) //if this position is on the current chromosome chunk (end_pos is included for chromosome chunks so no base gets skipped)
	{
		for (c=startPosNum; c<endPosNum; c++) 
		{
			featurePresence[c-begin_pos]=1; //added -begin_pos offset 
			numOfOnes++; //local
			//fprintf(ofpFL, "%d: %d %d:%d %d:%d %d %d [%d]\n", numOfFeatures, size, begin_pos, end_pos, startPosNum, endPosNum, c, c-begin_pos, featurePresence[c-begin_pos]); //*****temp
		}
	}
	return numOfOnes;	
}
int readSingleFeatureFile(FILE *ifp, int chrNum, int numOfFiles, int numOfFeatures, double** modelVectors, double** probsPositions, unsigned* featurePresence, FILE* ofpFL, int size, int begin_pos, int end_pos,  int numOfModelFiles)
{
	char *my_string, *token, *chrN, *startPos, *endPos, chrNumStr[6];
	const char s[2] = "\t";
	size_t nbytes = 100;
	int numOfOnes=0, pos=0, i=0;
	for (pos=0; pos<size; pos++)	
		featurePresence[pos]=0; //initialize to zeros for each feature
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
			if (selectChrNum(chrN) == chrNum)
				numOfOnes+=featurePresent(startPos, endPos, numOfFiles, numOfFeatures, modelVectors, probsPositions, featurePresence, ofpFL, size, begin_pos, end_pos, numOfModelFiles); //numOfOnes gets accumulated
		}
	}
	for (pos=0; pos<size; pos++) //size is step, which is 1/10 of actual chromosome size
		for (i=1; i<=numOfModelFiles; i++)
		{
			probsPositions[pos][i]+=featurePresence[pos]*modelVectors[numOfFeatures][i]; //adds up this product for all features at particular position (numOfFeatures is number of current feature)
			if ((pos==0) && (i==1)) //*****temp 643253
				fprintf(ofpFL, "%d: %d %.3f %d %d %.3f\n", numOfFeatures, i, modelVectors[numOfFeatures][i], pos+begin_pos, featurePresence[pos], probsPositions[pos][i]); //*****temp
		}
	free(my_string);
	return numOfOnes;
}
int readMultipleFeatureFile(FILE *ifp, int chrNum, int numOfFiles, char *featureArray, int numOfFeatures, double** modelVectors, double** probsPositions, unsigned* featurePresence, FILE* ofpFL, int size, int begin_pos, int end_pos, int numOfModelFiles)
{
	char *my_string, *token, *chrN, *startPos, *endPos, *val1, chrNumStr[6];
	const char s[2] = "\t";
	size_t nbytes = 200;
	int numOfOnes=0, pos=0, i=0;
	my_string = (char *) malloc (nbytes + 1);
	for (pos=0; pos<size; pos++)	
		featurePresence[pos]=0; //initialize to zeros for each feature
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
			token = strtok(NULL, s);      //get the fourth token
			val1 = strtok(token,"\n");
			token = strtok(my_string, "\n");      //get the rest of the line
			if (strcmp(val1, featureArray)== 0) //1st check whether it's current feature
			{
				if (selectChrNum(chrN) == chrNum)
					numOfOnes+=featurePresent(startPos, endPos, numOfFiles, numOfFeatures, modelVectors, probsPositions, featurePresence, ofpFL, size, begin_pos, end_pos, numOfModelFiles); //numOfOnes gets accumulated
			}
		}
	}	
	for (pos=0; pos<size; pos++) //size is step, which is 1/10 of actual chromosome size
		for (i=1; i<=numOfModelFiles; i++)
		{
			probsPositions[pos][i]+=featurePresence[pos]*modelVectors[numOfFeatures][i]; //adds up this product for all features at particular position
			if ((pos==0) && (i==1)) //*****temp 643253
				fprintf(ofpFL, "%d: %d %.3f %d %d %.3f\n", numOfFeatures, i, modelVectors[numOfFeatures][i], pos+begin_pos, featurePresence[pos], probsPositions[pos][i]); //*****temp
		}
	free(my_string);
	return numOfOnes;
}

int readECFeatureFile(char *inputFileName, int chrNum, int numOfFiles, int numOfFeatures, double** modelVectors, double** probsPositions, unsigned* featurePresence, FILE* ofpFL, int size, int begin_pos, int end_pos, int numOfModelFiles)
{
	char *mode = "r";
	int numOfOnes=0;
	char inputFilePath[150]="/u/home/o/ogrujic/project-ernst/zarlab/sourceDataFiles/EC/";
	FILE * ifp = fopen(strcat(inputFilePath,strtok(inputFileName, "\n")),mode);
	if (ifp == NULL) {
		fprintf(stderr, "Can't open input file in list EC!\n");
		//exit(1);
		return 0;
	}
	numOfOnes=readSingleFeatureFile(ifp, chrNum, numOfFiles, numOfFeatures, modelVectors, probsPositions, featurePresence, ofpFL, size, begin_pos, end_pos, numOfModelFiles);
	fclose(ifp);
	return numOfOnes;
}
int readEC2FeatureFile(char *inputFileName, int chrNum, int numOfFiles, int numOfFeatures, double** modelVectors, double** probsPositions, unsigned* featurePresence, FILE* ofpFL, int size, int begin_pos, int end_pos, int numOfModelFiles)
{
	char *mode = "r";
	int numOfOnes=0;
	char inputFilePath[150]="/u/home/o/ogrujic/project-ernst/zarlab/sourceDataFiles/EC2/";
	FILE * ifp = fopen(strcat(inputFilePath,strtok(inputFileName, "\n")),mode);
	if (ifp == NULL) {
		fprintf(stderr, "Can't open input file in list EC2!\n");
		//exit(1);
		return 0;
	}
	numOfOnes=readSingleFeatureFile(ifp, chrNum, numOfFiles, numOfFeatures, modelVectors, probsPositions, featurePresence, ofpFL, size, begin_pos, end_pos, numOfModelFiles);
	fclose(ifp);
	return numOfOnes;
}
int readEC3FeatureFile(char *inputFileName, int chrNum, int numOfFiles, int numOfFeatures, double** modelVectors, double** probsPositions, unsigned* featurePresence, FILE* ofpFL, int size, int begin_pos, int end_pos, int numOfModelFiles)
{
	char *mode = "r";
	int numOfOnes=0;
	char inputFilePath[150]="/u/home/o/ogrujic/project-ernst/zarlab/sourceDataFiles/EC3/";
	FILE * ifp = fopen(strcat(inputFilePath,strtok(inputFileName, "\n")),mode);
	if (ifp == NULL) {
		fprintf(stderr, "Can't open input file in list EC3!\n");
		//exit(1);
		return 0;
	}
	numOfOnes=readSingleFeatureFile(ifp, chrNum, numOfFiles, numOfFeatures, modelVectors, probsPositions, featurePresence, ofpFL, size, begin_pos, end_pos, numOfModelFiles);
	fclose(ifp);
	return numOfOnes;
}
int readEC4FeatureFile(char *inputFileName, int chrNum, int numOfFiles, int numOfFeatures, double** modelVectors, double** probsPositions, unsigned* featurePresence, FILE* ofpFL, int size, int begin_pos, int end_pos, int numOfModelFiles)
{
	char *mode = "r";
	int numOfOnes=0;
	char inputFilePath[150]="/u/home/o/ogrujic/project-ernst/zarlab/sourceDataFiles/EC4/";
	FILE * ifp = fopen(strcat(inputFilePath,strtok(inputFileName, "\n")),mode);
	if (ifp == NULL) {
		fprintf(stderr, "Can't open input file in list EC4!\n");
		//exit(1);
		return 0;
	}
	numOfOnes=readSingleFeatureFile(ifp, chrNum, numOfFiles, numOfFeatures, modelVectors, probsPositions, featurePresence, ofpFL, size, begin_pos, end_pos, numOfModelFiles);
	fclose(ifp);
	return numOfOnes;
}
int readEC5FeatureFile(char *inputFileName, int chrNum, int numOfFiles, int numOfFeatures, double** modelVectors, double** probsPositions, unsigned* featurePresence, FILE* ofpFL, int size, int begin_pos, int end_pos, int numOfModelFiles)
{
	char *mode = "r";
	int numOfOnes=0;
	char inputFilePath[150]="/u/home/o/ogrujic/project-ernst/zarlab/sourceDataFiles/EC5/";
	FILE * ifp = fopen(strcat(inputFilePath,strtok(inputFileName, "\n")),mode);
	numOfOnes=readSingleFeatureFile(ifp, chrNum, numOfFiles, numOfFeatures, modelVectors, probsPositions, featurePresence, ofpFL, size, begin_pos, end_pos, numOfModelFiles);
	fclose(ifp);
	return numOfOnes;
}
int readRMFeatureFile(char *inputFileName, int chrNum, int numOfFiles, int numOfFeatures, double** modelVectors, double** probsPositions, unsigned* featurePresence, FILE* ofpFL, int size, int begin_pos, int end_pos, int numOfModelFiles)
{
	char *mode = "r";
	int numOfOnes=0;
	char inputFilePath[150]="/u/home/o/ogrujic/project-ernst/zarlab/sourceDataFiles/RM/";
	FILE * ifp = fopen(strcat(inputFilePath,strtok(inputFileName, "\n")),mode);
	if (ifp == NULL) {
		fprintf(stderr, "Can't open input file in list RM!\n");
		//exit(1);
		return 0;
	}
	numOfOnes=readSingleFeatureFile(ifp, chrNum, numOfFiles, numOfFeatures, modelVectors, probsPositions, featurePresence, ofpFL, size, begin_pos, end_pos, numOfModelFiles);
	fclose(ifp);
	return numOfOnes;
}
int readFPFeatureFile(char *inputFileName, int chrNum, int numOfFiles, int numOfFeatures, double** modelVectors, double** probsPositions, unsigned* featurePresence, FILE* ofpFL, int size, int begin_pos, int end_pos, int numOfModelFiles)
{ 
	char *mode = "r";
	int numOfOnes=0;
	char inputFilePath[150]="/u/home/o/ogrujic/project-ernst/zarlab/sourceDataFiles/FP/";
	FILE * ifp = fopen(strcat(inputFilePath,strtok(inputFileName, "\n")),mode);
	if (ifp == NULL) {
		fprintf(stderr, "Can't open input file in list FP!\n");
		//exit(1);
		return 0;
	}
	numOfOnes=readSingleFeatureFile(ifp, chrNum, numOfFiles, numOfFeatures, modelVectors, probsPositions, featurePresence, ofpFL, size, begin_pos, end_pos, numOfModelFiles);
	fclose(ifp);
	return numOfOnes;
}
int readPFeatureFile(char *inputFileName, int chrNum, int numOfFiles, char *featureArrayP, int numOfFeatures, double** modelVectors, double** probsPositions, unsigned* featurePresence, FILE* ofpFL, int size, int begin_pos, int end_pos, int numOfModelFiles)
{ 
	char *mode = "r";
	int numOfOnes=0;
	char inputFilePath[150]="/u/home/o/ogrujic/project-ernst/zarlab/sourceDataFiles/P/";
	FILE * ifp = fopen(strcat(inputFilePath,strtok(inputFileName, "\n")),mode);
	if (ifp == NULL) {
		fprintf(stderr, "Can't open input file in list P!\n");
		//exit(1);
		return 0;
	}
	numOfOnes=readMultipleFeatureFile(ifp, chrNum, numOfFiles, featureArrayP, numOfFeatures, modelVectors, probsPositions, featurePresence, ofpFL, size, begin_pos, end_pos, numOfModelFiles);
	fclose(ifp);
	return numOfOnes;
}
int readCHMMFeatureFile(char *inputFileName, int chrNum, int numOfFiles, char *featureArrayCHMM, int numOfFeatures, double** modelVectors, double** probsPositions, unsigned* featurePresence, FILE* ofpFL, int size, int begin_pos, int end_pos, int numOfModelFiles)
{ 
	char *mode = "r";
	int numOfOnes=0;
	char inputFilePath[150]="/u/home/o/ogrujic/project-ernst/zarlab/sourceDataFiles/CHMM/";
	FILE * ifp = fopen(strcat(inputFilePath,strtok(inputFileName, "\n")),mode);
	if (ifp == NULL) {
		fprintf(stderr, "Can't open input file in list CHMM!\n");
		//exit(1);
		return 0;
	}
	numOfOnes=readMultipleFeatureFile(ifp, chrNum, numOfFiles, featureArrayCHMM, numOfFeatures, modelVectors, probsPositions, featurePresence, ofpFL, size, begin_pos, end_pos, numOfModelFiles);
	fclose(ifp);
	return numOfOnes;
}
int readCHMM2FeatureFile(char *inputFileName, int chrNum, int numOfFiles, char *featureArrayCHMM2, int numOfFeatures, double** modelVectors, double** probsPositions, unsigned* featurePresence, FILE* ofpFL, int size, int begin_pos, int end_pos, int numOfModelFiles)
{ 
	char *mode = "r";
	int numOfOnes=0;
	char inputFilePath[150]="/u/home/o/ogrujic/project-ernst/zarlab/sourceDataFiles/CHMM2/";
	FILE * ifp = fopen(strcat(inputFilePath,strtok(inputFileName, "\n")),mode);
	if (ifp == NULL) {
		fprintf(stderr, "Can't open input file in list CHMM2!\n");
		//exit(1);
		return 0;
	}
	numOfOnes=readMultipleFeatureFile(ifp, chrNum, numOfFiles, featureArrayCHMM2, numOfFeatures, modelVectors, probsPositions, featurePresence, ofpFL, size, begin_pos, end_pos, numOfModelFiles);
	fclose(ifp);
	return numOfOnes;
}
int readHMMFeatureFile(char *inputFileName, int chrNum, int numOfFiles, char *featureArrayHMM, int numOfFeatures, double** modelVectors, double** probsPositions, unsigned* featurePresence, FILE* ofpFL, int size, int begin_pos, int end_pos, int numOfModelFiles)
{ 
	char *mode = "r";
	int numOfOnes=0;
	char inputFilePath[150]="/u/home/o/ogrujic/project-ernst/zarlab/sourceDataFiles/HMM/";
	FILE * ifp = fopen(strcat(inputFilePath,strtok(inputFileName, "\n")),mode);
	if (ifp == NULL) {
		fprintf(stderr, "Can't open input file in list HMM!\n");
		//exit(1);
		return 0;
	}
	numOfOnes=readMultipleFeatureFile(ifp, chrNum, numOfFiles, featureArrayHMM, numOfFeatures, modelVectors, probsPositions, featurePresence, ofpFL, size, begin_pos, end_pos, numOfModelFiles);
	fclose(ifp);
	return numOfOnes;
}

int readFeatureFileList(char inputFileName[], int chrNum, int numOfFeatures, double** modelVectors, double** probsPositions, unsigned* featurePresence, FILE* ofpFL, int size, int begin_pos, int end_pos, int numOfModelFiles)
{
	int numOfOnes=0, numOfFiles=0, i=0, numOfFeaturesHMM=15, numOfFeaturesCHMM=15, numOfFeaturesCHMM2=25, numOfFeaturesP=131;
	char *mode = "r", featureFileName[200], fileName[10], featureNameP[20], featureNameCHMM[20], PFeatureNames[132][20];
	char CHMMFeatureNames[16][25]={"", "1_TssA","2_TssAFlnk","3_TxFlnk","4_Tx","5_TxWk","6_EnhG","7_Enh",
	"8_ZNF/Rpts","9_Het","10_TssBiv","11_BivFlnk","12_EnhBiv","13_ReprPC","14_ReprPCWk","15_Quies"};
	char HMMFeatureNames[16][25]={"", "1_Active_Promoter","2_Weak_Promoter","3_Poised_Promoter","4_Strong_Enhancer",
	"5_Strong_Enhancer","6_Weak_Enhancer","7_Weak_Enhancer","8_Insulator","9_Txn_Transition","10_Txn_Elongation",
	"11_Weak_Txn","12_Repressed","13_Heterochrom/lo","14_Repetitive/CNV","15_Repetitive/CNV"};
	char CHMM2FeatureNames[26][25]={"", "1_TssA","2_PromU","3_PromD1","4_PromD2","5_Tx5'", "6_Tx","7_Tx3'","8_TxWk",
	"9_TxReg","10_TxEnh5'","11_TxEnh3'","12_TxEnhW","13_EnhA1","14_EnhA2","15_EnhAF","16_EnhW1","17_EnhW2","18_EnhAc",
	"19_DNase","20_ZNF/Rpts","21_Het","22_PromP","23_PromBiv","24_ReprPC","25_Quies"};
	FILE * ifp = fopen(inputFileName,mode);
	if (ifp == NULL) {
		fprintf(stderr, "Can't open input file in list!\n");
		//exit(1);
		return 0;
	}
	if (strcmp(inputFileName, "/u/home/o/ogrujic/project-ernst/zarlab/sourceDataFiles/ListRM.txt") == 0)
		while (!feof(ifp)) 
		{
			fscanf(ifp, "%s", &featureFileName);
			numOfFiles++;
			tostring(fileName, numOfFiles);
			numOfFeatures++;
			//fprintf(ofpFL, "%s \n", featureFileName); //*****temp
			numOfOnes=readRMFeatureFile(featureFileName, chrNum, numOfFiles, numOfFeatures, modelVectors, probsPositions, featurePresence, ofpFL, size, begin_pos, end_pos, numOfModelFiles);
		}
		
	if (strcmp(inputFileName, "/u/home/o/ogrujic/project-ernst/zarlab/sourceDataFiles/ListEC.txt") == 0)
		while (!feof(ifp)) 
		{
			fscanf(ifp, "%s", &featureFileName);
			numOfFiles++;
			tostring(fileName, numOfFiles);
			numOfFeatures++;
			//fprintf(ofpFL, "%s \n", featureFileName); //*****temp
			numOfOnes=readECFeatureFile(featureFileName, chrNum, numOfFiles, numOfFeatures, modelVectors, probsPositions, featurePresence, ofpFL, size, begin_pos, end_pos, numOfModelFiles);
		}
	if (strcmp(inputFileName, "/u/home/o/ogrujic/project-ernst/zarlab/sourceDataFiles/ListEC2.txt") == 0)
		while (!feof(ifp)) 
		{
			fscanf(ifp, "%s", &featureFileName);
			numOfFiles++;
			tostring(fileName, numOfFiles);
			numOfFeatures++;
			//fprintf(ofpFL, "%s \n", featureFileName); //*****temp
			numOfOnes=readEC2FeatureFile(featureFileName, chrNum, numOfFiles, numOfFeatures, modelVectors, probsPositions, featurePresence, ofpFL, size, begin_pos, end_pos, numOfModelFiles);
		}
	if (strcmp(inputFileName, "/u/home/o/ogrujic/project-ernst/zarlab/sourceDataFiles/ListEC3.txt") == 0)
		while (!feof(ifp)) 
		{
			fscanf(ifp, "%s", &featureFileName);
			numOfFiles++;
			tostring(fileName, numOfFiles);
			numOfFeatures++;
			//fprintf(ofpFL, "%s \n", featureFileName); //*****temp
			numOfOnes=readEC3FeatureFile(featureFileName, chrNum, numOfFiles, numOfFeatures, modelVectors, probsPositions, featurePresence, ofpFL, size, begin_pos, end_pos, numOfModelFiles);
		}
	if (strcmp(inputFileName, "/u/home/o/ogrujic/project-ernst/zarlab/sourceDataFiles/ListEC4.txt") == 0)
		while (!feof(ifp)) 
		{
			fscanf(ifp, "%s", &featureFileName);
			numOfFiles++;
			tostring(fileName, numOfFiles);
			numOfFeatures++;
			//fprintf(ofpFL, "%s \n", featureFileName); //*****temp
			numOfOnes=readEC4FeatureFile(featureFileName, chrNum, numOfFiles, numOfFeatures, modelVectors, probsPositions, featurePresence, ofpFL, size, begin_pos, end_pos, numOfModelFiles);
		}
	if (strcmp(inputFileName, "/u/home/o/ogrujic/project-ernst/zarlab/sourceDataFiles/ListEC5.txt") == 0)
		while (!feof(ifp)) 
		{
			fscanf(ifp, "%s", &featureFileName);
			numOfFiles++;
			tostring(fileName, numOfFiles);
			numOfFeatures++;
			//fprintf(ofpFL, "%s \n", featureFileName); //*****temp
			numOfOnes=readEC5FeatureFile(featureFileName, chrNum, numOfFiles, numOfFeatures, modelVectors, probsPositions, featurePresence, ofpFL, size, begin_pos, end_pos, numOfModelFiles);
		}
	if (strcmp(inputFileName, "/u/home/o/ogrujic/project-ernst/zarlab/sourceDataFiles/ListFP.txt") == 0)
		while (!feof(ifp))
		{
			fscanf(ifp, "%s", &featureFileName);
			numOfFiles++;
			tostring(fileName, numOfFiles);
			numOfFeatures++;
			//fprintf(ofpFL, "%s \n", featureFileName); //*****temp
			numOfOnes=readFPFeatureFile(featureFileName, chrNum, numOfFiles, numOfFeatures, modelVectors, probsPositions, featurePresence, ofpFL, size, begin_pos, end_pos, numOfModelFiles); 
		}
	if (strcmp(inputFileName, "/u/home/o/ogrujic/project-ernst/zarlab/sourceDataFiles/ListP.txt") == 0)
	{
		FILE * ifpTEMP = fopen("/u/home/o/ogrujic/project-ernst/zarlab/sourceDataFiles/P/filPeaks_public.bed","r");
		if (ifpTEMP == NULL)
		{
			//fprintf(stderr, "Can't open input file in list!\n");
			//exit(1);
			return 0;
		}
		int found=0;
		size_t nbytes = 200;
		const char s[2] = "\t"; 
		char *my_string, *token, PFeatureNames[396][nbytes];
		my_string = (char *) malloc (nbytes + 1);
		numOfFeaturesP=0;
		while (!feof(ifpTEMP))
		{
			if( fgets (my_string, nbytes, ifpTEMP)!=NULL )
			{
				token = strtok(my_string, s); //get the first token
				token = strtok(NULL, s);      //get 2nd token
				token = strtok(NULL, s);      //get 3rd token
				token = strtok(NULL, s);      //get 4th token
				found=0; 
				for (i=1; i<=numOfFeaturesP; i++)
					if ((strcmp(token, PFeatureNames[i]) == 0)&&(strcmp(token, "")!= 0))
					{
						found=1;
						break;
					}
				if ((found!=1) && (strcmp(token, "")!= 0))
				{
					numOfFeaturesP++; //features [1,395]
					strcpy(PFeatureNames[numOfFeaturesP], token); //copy feature into array of features
				}
				token = strtok(my_string, "\n");      //get the rest of the line
			}
		}
		fclose(ifpTEMP);
		
		/* //***** This section creates file with list of feature names for reference*****
		FILE * ifpP = fopen("/u/home/o/ogrujic/project-ernst/zarlab/sourceDataFiles/PFeatureNames.txt","w");
		if (ifpP == NULL) 
		{
			//fprintf(stderr, "Can't open input file in list!\n");
			//exit(1);
			return 0;
		}
		for (i=1; i<=numOfFeaturesP; i++)//features [1,395]
		{
			fprintf(ifpP, "%s\n", PFeatureNames[i]);//*****temp, needs removed
		}
		fclose(ifpP);
		*/

		while (!feof(ifp))
		{
			fscanf(ifp, "%s", &featureFileName); //This is only one file (P.bed)
			for (i=1; i<=numOfFeaturesP; i++) //This creates 395 files, features [1,395]
			{
				tostring(fileName, numOfFiles+=1);
				numOfFeatures++;
				//fprintf(ofpFL, "%s %s \n", featureFileName, PFeatureNames[i]); //*****temp
				numOfOnes=readPFeatureFile(featureFileName, chrNum, numOfFiles, PFeatureNames[i], numOfFeatures, modelVectors, probsPositions, featurePresence, ofpFL, size, begin_pos, end_pos, numOfModelFiles);
			}
		}
	}

	if (strcmp(inputFileName, "/u/home/o/ogrujic/project-ernst/zarlab/sourceDataFiles/ListCHMM.txt") == 0)
	{	
		numOfFeaturesCHMM=15;
		while (!feof(ifp))
		{
			fscanf(ifp, "%s", &featureFileName); 
			for (i=1; i<=numOfFeaturesCHMM; i++) //This creates 1905 files 
			{
				tostring(fileName, numOfFiles+=1);
				numOfFeatures++;
				//fprintf(ofpFL, "%s %s \n", featureFileName, CHMMFeatureNames[i]); //*****temp
				numOfOnes=readCHMMFeatureFile(featureFileName, chrNum, numOfFiles, CHMMFeatureNames[i], numOfFeatures, modelVectors, probsPositions, featurePresence, ofpFL, size, begin_pos, end_pos, numOfModelFiles);
			}
		}
	}

	if (strcmp(inputFileName, "/u/home/o/ogrujic/project-ernst/zarlab/sourceDataFiles/ListCHMM2.txt") == 0)
	{	
		numOfFeaturesCHMM2=25;
		while (!feof(ifp))
		{
			fscanf(ifp, "%s", &featureFileName); 
			for (i=1; i<=numOfFeaturesCHMM2; i++) //This creates 3175 files
			{
				tostring(fileName, numOfFiles+=1);
				numOfFeatures++;
				//fprintf(ofpFL, "%s %s \n", featureFileName, CHMM2FeatureNames[i]); //*****temp
				numOfOnes=readCHMM2FeatureFile(featureFileName, chrNum, numOfFiles, CHMM2FeatureNames[i], numOfFeatures, modelVectors, probsPositions, featurePresence, ofpFL, size, begin_pos, end_pos, numOfModelFiles);
			}
		}
	}

	if (strcmp(inputFileName, "/u/home/o/ogrujic/project-ernst/zarlab/sourceDataFiles/ListHMM.txt") == 0)
	{	
		numOfFeaturesHMM=15;
		while (!feof(ifp))
		{
			fscanf(ifp, "%s", &featureFileName); //This is 9 files (wgEncodeBroadHmmGm12878HMM.bed)
			for (i=1; i<=numOfFeaturesHMM; i++)
			{
				tostring(fileName, numOfFiles+=1);
				numOfFeatures++;
				//fprintf(ofpFL, "%s %s \n", featureFileName, HMMFeatureNames[i]); //*****temp
				numOfOnes=readHMMFeatureFile(featureFileName, chrNum, numOfFiles, HMMFeatureNames[i], numOfFeatures, modelVectors, probsPositions, featurePresence, ofpFL, size, begin_pos, end_pos, numOfModelFiles);
			}
		}
	}
	
	fclose(ifp);
	return numOfFiles;
}

int main(int argc, char *argv[] ) 
{	
	int chromSize[]= {-1, 249250621, 243199373, 198022430, 191154276, 180915260, 171115067, 159138663, 146364022, 141213431, 135534747, 135006516,
		133851895, 115169878, 107349540, 102531392, 90354753, 81195210, 78077248, 59128983, 63025520, 48129895, 51304566, 155270560};
	int numOfFeatures=10836, line=0, position=0, neg=0, i=1, chrNum=-1, numOfModelFiles=10;//*****temp (needs changed to 100 when more samples availble)
	if ( argc != 5 ) //argc should be 4 for correct execution (for 3 arguments)
    {   
        printf( "usage: %s model_filename score_file_name chromosome_number section\n", argv[0] ); //argv[0] is the program name
		exit(1);
    }
	chrNum=selectChr(argv[3]);
	int size=chromSize[chrNum];
	
	char fileName2[FILE_PATH_LEN]="/u/home/o/ogrujic/project-ernst/zarlab/averageGenomewide/";
	strcat(fileName2,argv[2]);
	strcat(fileName2, "_");
	strcat(fileName2, argv[3]); //chromosome number
	strcat(fileName2, "_");
	if (strcmp(argv[4], "10")==0) //this is because part 0 cannot be scheduled, so part 10 becomes part 0
		strcat(fileName2, "0"); //section number
	else
		strcat(fileName2, argv[4]); //section number
	FILE *score_file = fopen(strcat (fileName2, ".wig"), "w");
	if (score_file == NULL) 
	{
		fprintf(stderr, "Couldn't open input file %s!\n", fileName2); //score_file_name (to write scores to for single chromosome)
		exit(1);
	}

	char fileName3[FILE_PATH_LEN]="/u/home/o/ogrujic/project-ernst/zarlab/averageGenomewide/"; //*****temp
	strcat(fileName3,argv[2]); //*****temp
	strcat(fileName3, "_");//*****temp
	strcat(fileName3, argv[3]); //chromosome number //*****temp
	strcat(fileName3, "_"); //*****temp
	if (strcmp(argv[4], "10")==0) //this is because part 0 cannot be scheduled, so part 10 becomes part 0
		strcat(fileName3, "0"); //section number
	else
		strcat(fileName3, argv[4]); //section number //*****temp
	FILE * ofpFL = fopen(strcat(fileName3,"_log.txt"),"w");//*****temp
	if (ofpFL == NULL) //*****temp
		fprintf(stderr, "Can't open output file %s!\n", fileName3);//*****temp
	fprintf(ofpFL, "ChromosomeNum: %d\n", chrNum); //*****temp
	fprintf(ofpFL, "FeatureNum: modelNum Parameter pos PresentPos[pos] SumPos[pos]\n"); //*****temp

	//****** begin reading in model files
	double* intercepts=double_vector(0, numOfModelFiles); //cumulative for averaging predictions
	for (i=1; i<=numOfModelFiles; i++)	
		intercepts[i]=0.0; //initialize to zeros

	double **modelVectors=dmatrix(1,numOfFeatures,1,numOfModelFiles);
	for (position=1; position<=numOfFeatures; position++)	
			for (i=1; i<=numOfModelFiles; i++)
				modelVectors[position][i]=0.0; //initialize to zeros

	for (i=1; i<=numOfModelFiles; i++) //read in all model_vectors
	{
		//reading in model file(s)
		char fileName[FILE_PATH_LEN], fileExtension[110]="_";
		tostring(fileName, i);//"1"
		strcat(fileExtension, fileName);//"_1"
		strcat(fileExtension, "m.model");//"_1m.model"

		char fileName1[FILE_PATH_LEN];
		char filePath1 [FILE_PATH_LEN] = "/u/home/o/ogrujic/project-ernst/zarlab/averageGenomewide/l1_modelFiles1_Omega_chr"; //this is where one set of model files is
		strcat (filePath1, argv[3]); //chromosome number
		strcat (filePath1, "/");
		strcpy(fileName1,argv[1]); // We assume argv[1] is a filename "train_liblinear"
		strcat (fileName1, fileExtension); //"train_liblinear_1m.model"
		strcat (filePath1, fileName1); // /u/home/o/ogrujic/project-ernst/zarlab/averageGenomewide/modelFiles/train_liblinear_*m.model in filePath1
		strcpy (fileName1, filePath1); // same in fileName1
		FILE *model_file = fopen( fileName1, "r" ); 
		if (model_file == 0 ) // fopen returns 0, the NULL pointer, on failure
		{
			fprintf(stderr, "Couldn't open input file %s!\n", fileName1); //model_filename
			exit(1);
		} 
		intercepts[i]=readModelFeatures(model_file, modelVectors, numOfFeatures, i);
		fclose(model_file);
		//printf("model file read in: %d \n", i); //*****temp
	}
	//****** end of reading in model files

	
	//apply weights genomewide, one chunck at a time:
	int section=posStrToInt(argv[4]);//section is [0,9] for 10 chunks
	if (strcmp(argv[4], "10")==0) //this is because part 0 cannot be scheduled, so part 10 becomes part 0
		section=0; 
	int step=size/10, updatedChrSize=step, begin_pos=section*step, end_pos=(section+1)*step-1;
	if (section==9)
	{
		end_pos=size-1;
		step=end_pos-begin_pos+1;
	}
	unsigned* featurePresence=vector(0, step);
	double* probsPositionsSum=double_vector(0, step); //cumulative for averaging predictions
	double** probsPositions=dmatrix(0,step,1,numOfModelFiles);
	for (position=0; position<step; position++)	
	{
		featurePresence[position]=0; //initialize to zeros
		probsPositionsSum[position]=0.0; //initialize to zeros
		for (i=1; i<=numOfModelFiles; i++)
			probsPositions[position][i]=0.0; //initialize to zeros
	}
	numOfFeatures=0; //reset
	numOfFeatures+=readFeatureFileList("/u/home/o/ogrujic/project-ernst/zarlab/sourceDataFiles/ListRM.txt", chrNum, numOfFeatures, modelVectors, probsPositions, featurePresence, ofpFL, step, begin_pos, end_pos, numOfModelFiles); //1915	
	numOfFeatures+=readFeatureFileList("/u/home/o/ogrujic/project-ernst/zarlab/sourceDataFiles/ListEC.txt", chrNum, numOfFeatures, modelVectors, probsPositions, featurePresence, ofpFL, step, begin_pos, end_pos, numOfModelFiles);//690	
	numOfFeatures+=readFeatureFileList("/u/home/o/ogrujic/project-ernst/zarlab/sourceDataFiles/ListEC2.txt", chrNum, numOfFeatures, modelVectors, probsPositions, featurePresence, ofpFL, step, begin_pos, end_pos, numOfModelFiles);//125
	numOfFeatures+=readFeatureFileList("/u/home/o/ogrujic/project-ernst/zarlab/sourceDataFiles/ListEC3.txt", chrNum, numOfFeatures, modelVectors, probsPositions, featurePresence, ofpFL, step, begin_pos, end_pos, numOfModelFiles);//274
	numOfFeatures+=readFeatureFileList("/u/home/o/ogrujic/project-ernst/zarlab/sourceDataFiles/ListEC4.txt", chrNum, numOfFeatures, modelVectors, probsPositions, featurePresence, ofpFL, step, begin_pos, end_pos, numOfModelFiles);//1208	
	numOfFeatures+=readFeatureFileList("/u/home/o/ogrujic/project-ernst/zarlab/sourceDataFiles/ListEC5.txt", chrNum, numOfFeatures, modelVectors, probsPositions, featurePresence, ofpFL, step, begin_pos, end_pos, numOfModelFiles);//972	
	numOfFeatures+=readFeatureFileList("/u/home/o/ogrujic/project-ernst/zarlab/sourceDataFiles/ListFP.txt", chrNum, numOfFeatures, modelVectors, probsPositions, featurePresence, ofpFL, step, begin_pos, end_pos, numOfModelFiles);//42	
	numOfFeatures+=readFeatureFileList("/u/home/o/ogrujic/project-ernst/zarlab/sourceDataFiles/ListP.txt", chrNum, numOfFeatures, modelVectors, probsPositions, featurePresence, ofpFL, step, begin_pos, end_pos, numOfModelFiles);//395
	numOfFeatures+=readFeatureFileList("/u/home/o/ogrujic/project-ernst/zarlab/sourceDataFiles/ListCHMM.txt", chrNum, numOfFeatures, modelVectors, probsPositions, featurePresence, ofpFL, step, begin_pos, end_pos, numOfModelFiles);//1905
	numOfFeatures+=readFeatureFileList("/u/home/o/ogrujic/project-ernst/zarlab/sourceDataFiles/ListCHMM2.txt",chrNum, numOfFeatures, modelVectors, probsPositions, featurePresence, ofpFL, step, begin_pos, end_pos, numOfModelFiles);//3175
	numOfFeatures+=readFeatureFileList("/u/home/o/ogrujic/project-ernst/zarlab/sourceDataFiles/ListHMM.txt", chrNum, numOfFeatures, modelVectors, probsPositions, featurePresence, ofpFL, step, begin_pos, end_pos, numOfModelFiles);//135

	for (position=0; position<step; position++)
		for (i=1; i<=numOfModelFiles; i++)	
		{
			probsPositions[position][i]=1/(1+exp(-(probsPositions[position][i]+intercepts[i]))); //final probability for this position (intercept + all products summed up; all that put through 1/1+e^-) 
			if ((position==643253) && (i==1)) //*****temp
				fprintf(ofpFL, "position: %d i: %d intercepts[i]: %.5f probsPositions[position][i]%.5f\n", position, i, intercepts[i], probsPositions[position][i]); //*****temp
			probsPositionsSum[position]+=probsPositions[position][i]; //store current predictions in order to average them at the end
		}
	for (position=0; position<step; position++)
	{
		probsPositionsSum[position]/=numOfModelFiles; //average predictions
		if ((position==643253) && (i==1)) //*****temp
			fprintf(ofpFL, "cumulative position: %d numOfModelFiles%d averagedProbability%.5f\n", position, numOfModelFiles, probsPositionsSum[position]); //*****temp
	}
	writePosProfFile(probsPositionsSum, step, score_file, chrNum);
	free_double_vector(probsPositionsSum, 0, step); 
	free_dmatrix(probsPositions, 0,step,1,numOfModelFiles); 

	free_double_vector(intercepts, 0, numOfModelFiles); 
	free_dmatrix(modelVectors, 1,numOfFeatures,1,numOfModelFiles);
	fclose(score_file); 
	fclose(ofpFL);//*****temp
	return 0;
}