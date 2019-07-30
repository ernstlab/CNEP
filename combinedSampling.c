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
void free_vector(unsigned *v, int n1, int nh)
//releases a unsigned vector allocated by vector()
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
int compare_unsigned (const void * a, const void * b)
{
	return ( *(unsigned*)a - *(unsigned*)b );
}

void computeProbabilities(int chromSize[], double probabilities[], int N)
{
	int j=0;
    double overallProb = 0.0;

	for (j = 1; j <= N; j++) //N=23
    {
		probabilities[j] = chromSize[j];
		overallProb += probabilities[j];
    }
	//normalize probabilities (sum equal to 1)
    for (j = 1; j <= N; j++)
      probabilities[j] /= overallProb;    
}
void writeChromPosFile(unsigned **chromPos, int numLines,char *outputFileName)
{
	int i=0;
	char *mode = "w"; 
	FILE *ofp = fopen(outputFileName, mode);
	if (ofp == NULL) {
		fprintf(stderr, "Can't open output file %s!\n", outputFileName);
		exit(1);
	}
	for (i=0; i<numLines; i++)
		fprintf(ofp, " %u, %u \n", chromPos[i][0], chromPos[i][1]);
	fclose(ofp);
}
int sampleChromPos(int chromSize[], double probabilities[], int totalChrom, unsigned **trRows, int numTrRows, unsigned testChr, char outputFileNameTr[])
{
	int chrSelect, posSelect, numRows=0, j=0, p=0;
	double cumulativeProbability = 0.0;
	computeProbabilities(chromSize, probabilities, totalChrom);
	srand(time(NULL));
	while (numTrRows!=numRows) //make sure number of training rows and test rows is 100000
	{
		p=(rand()%101); //random int between 0 and 100
		cumulativeProbability = 0.0;		
		for (j=1; j<=totalChrom;j++) //totalChrom=23
		{
			cumulativeProbability += probabilities[j];
			if (p<=(cumulativeProbability*100))
			{
				chrSelect=j; 
				posSelect=(rand() % chromSize[chrSelect]); //random int between 0 and size of that chromosome
				if (chrSelect!=testChr)
				{
					trRows[numRows][0]=chrSelect;
					trRows[numRows][1]=posSelect;
					//if (numTrRows != numRows)//make sure number of training rows reached sample size (e.g. 100000)
					numRows++;
				}
				break;
			}
		}
	}
	writeChromPosFile(trRows, numTrRows, outputFileNameTr);
	return numRows;
}
int readTrainingSample(unsigned **trRows, int numTrRows, char *inputFileName)
{	//sample file contains sorted positions
	char *mode = "r";
	char chrN[20], trPos[20];
	unsigned chrNNum, trPosNum;
	int line=0;	
	
	FILE * ifp = fopen(inputFileName,mode);
	if (ifp == NULL) {
		fprintf(stderr, "Can't open input file %s in list!\n", inputFileName);
		//exit(1);
		return 0;
	}

	while (!feof(ifp)) 
	{
		fscanf(ifp, "%s %s", &chrN, &trPos);
		chrNNum = posStrToUnNum(chrN);
		trPosNum = posStrToUnNum(trPos);
		trRows[line][0]=chrNNum;
		trRows[line][1]=trPosNum;
		line++;
		if (line>numTrRows) //this is for just in case...
			break;
	}
	fclose(ifp);
	return numTrRows;
}
int countMaxPosChrNum (unsigned **trRows, int numTrRows, int numOfPosPerChr[])
{
	int l=0, maxCountPos=0;
	for (l=0; l<24; l++) 
	{
		numOfPosPerChr[l]=0;
	}
	for (l=0; l<numTrRows; l++) 
	{
		switch (trRows[l][0])
		{
			case 1: numOfPosPerChr[1]++;
			break;
			case 2: numOfPosPerChr[2]++;
			break;
			case 3: numOfPosPerChr[3]++;
			break;
			case 4: numOfPosPerChr[4]++;
			break;
			case 5: numOfPosPerChr[5]++;
			break;
			case 6: numOfPosPerChr[6]++;
			break;
			case 7: numOfPosPerChr[7]++;
			break;
			case 8: numOfPosPerChr[8]++;
			break;
			case 9: numOfPosPerChr[9]++;
			break;
			case 10: numOfPosPerChr[10]++;
			break;
			case 11: numOfPosPerChr[11]++;
			break;
			case 12: numOfPosPerChr[12]++;
			break;
			case 13: numOfPosPerChr[13]++;
			break;
			case 14: numOfPosPerChr[14]++;
			break;
			case 15: numOfPosPerChr[15]++;
			break;
			case 16: numOfPosPerChr[16]++;
			break;
			case 17: numOfPosPerChr[17]++;
			break;
			case 18: numOfPosPerChr[18]++;
			break;
			case 19: numOfPosPerChr[19]++;
			break;
			case 20: numOfPosPerChr[20]++;
			break;
			case 21: numOfPosPerChr[21]++;
			break;
			case 22: numOfPosPerChr[22]++;
			break;
			case 23: numOfPosPerChr[23]++;
			break;
		}
	}
	for (l=0; l<24; l++) 
	{
			if (numOfPosPerChr[l] > maxCountPos)
				maxCountPos=numOfPosPerChr[l];
	}
	return maxCountPos;
}
void sortSamplePos2D(unsigned** trRows2D, int numOfPosPerChr[])
{
	int l=0, i=0;
	for (l=1; l<=23; l++)
	{
		unsigned* teVector=vector(0, numOfPosPerChr[l]); //temp vector used for sorting positions on single chromosome
		for (i=0; i<numOfPosPerChr[l]; i++)
			teVector[i]=trRows2D[l][i];
		//void qsort (void *array, size_t count, size_t size, comparison_fn_t compare); //sorts array which contains count elements, each of which is of size. 
		qsort (teVector, numOfPosPerChr[l], sizeof (unsigned), compare_unsigned);
		for (i=0; i<numOfPosPerChr[l]; i++)
			trRows2D[l][i]=teVector[i];
		free_vector(teVector, 0, numOfPosPerChr[l]);
	}
}
void storeSamplePos2D (unsigned ** trRows2D, unsigned **trRows, int numTrRows, int numOfPosPerChr[], int cumulIndArr[])
{
	int i=0, l=0, sum=0, chr1=0, chr2=0, chr3=0, chr4=0, chr5=0, chr6=0, chr7=0, chr8=0, chr9=0, chr10=0, chr11=0, 
		chr12=0, chr13=0, chr14=0, chr15=0, chr16=0, chr17=0, chr18=0, chr19=0, chr20=0, chr21=0, chr22=0, chr23=0;
	for (l=0; l<numTrRows; l++) 
	{
		switch (trRows[l][0])
		{
			case 1: trRows2D[1][chr1]=trRows[l][1];
					chr1++; break;
			case 2: trRows2D[2][chr2]=trRows[l][1];
					chr2++; break;
			case 3: trRows2D[3][chr3]=trRows[l][1];
					chr3++; break;
			case 4: trRows2D[4][chr4]=trRows[l][1];
					chr4++; break;
			case 5: trRows2D[5][chr5]=trRows[l][1];
					chr5++; break;
			case 6: trRows2D[6][chr6]=trRows[l][1];
					chr6++; break;
			case 7: trRows2D[7][chr7]=trRows[l][1];
					chr7++; break;
			case 8: trRows2D[8][chr8]=trRows[l][1];
					chr8++; break;
			case 9: trRows2D[9][chr9]=trRows[l][1];
					chr9++; break;
			case 10: trRows2D[10][chr10]=trRows[l][1];
					chr10++; break;
			case 11: trRows2D[11][chr11]=trRows[l][1];
					chr11++; break;
			case 12: trRows2D[12][chr12]=trRows[l][1];
					chr12++; break;
			case 13: trRows2D[13][chr13]=trRows[l][1];
					chr13++; break;
			case 14: trRows2D[14][chr14]=trRows[l][1];
					chr14++; break;
			case 15: trRows2D[15][chr15]=trRows[l][1];
					chr15++; break;
			case 16: trRows2D[16][chr16]=trRows[l][1];
					chr16++; break;
			case 17: trRows2D[17][chr17]=trRows[l][1];
					chr17++; break;
			case 18: trRows2D[18][chr18]=trRows[l][1];
					chr18++; break;
			case 19: trRows2D[19][chr19]=trRows[l][1];
					chr19++; break;
			case 20: trRows2D[20][chr20]=trRows[l][1];
					chr20++; break;
			case 21: trRows2D[21][chr21]=trRows[l][1];
					chr21++; break;
			case 22: trRows2D[22][chr22]=trRows[l][1];
					chr22++; break;
			case 23: trRows2D[23][chr23]=trRows[l][1];
					chr23++; break;
		}
	}
	for (i=1; i<24;i++) //build cumulative index array for reference
	{
		sum+=numOfPosPerChr[i-1];//offset is zero for 1st row
		cumulIndArr[i]=sum;
	}
	sortSamplePos2D(trRows2D, numOfPosPerChr); //sort each row in the matrix (positions on single chromosome)
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

int readFromPiFile(char *inputFileName, unsigned **trRows, int numTrRows, unsigned *train_b, unsigned **trRows2D, int numOfPosPerChr[], int cumulIndArr [], char ext[], char testChrom[])
{												
	char *mode = "r", *my_string, *token, *chrN, *startPos, *endPos, chrNPrev[6]="chr1";
	const char s[2] = "\t";
	size_t nbytes = 100;
	unsigned currentTrPos, startPosNum, endPosNum;
	int count=0, r=1, c=0, i=0, offset=0;
	FILE * ifp = fopen(inputFileName,mode);
	if (ifp == NULL) {
		fprintf(stderr, "Can't open input file in list %s!\n", inputFileName);
		exit(1);
	}
	//********write labels file
	mode = "w";
	//char train_b_FN [200]="/u/home/o/ogrujic/project-ernst/zarlab/combinedSampling/labels_pi_chr";
	char train_b_FN [200]="/u/home/o/ogrujic/project-ernst/zarlab/combinedSampling/labels_pi_test_chr";
	strcat(train_b_FN, testChrom); //test chromosome #
	strcat(train_b_FN, "/labels_pi");
	strcat(train_b_FN, ext);
	FILE *ofp = fopen(train_b_FN, mode);
	if (ofp == NULL) {
		fprintf(stderr, "Can't open output file %s!\n", train_b_FN);
		exit(1);
	}
	//*********read from pi file
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
			if (strcmp(chrN, chrNPrev)!= 0)//if chromosome changed
			{
				r = selectChrRow(chrN);
				strcpy(chrNPrev,chrN);//update chrNPrev
			}
			if (r!=-1) //r is chromosome row in trRows 2D 
			{
				startPosNum = posStrToUnNum(startPos);
				endPosNum = posStrToUnNum(endPos);
				//checking whether current interval is on current chromosome and encompassing one of training sample positions
				for (c=0; c < numOfPosPerChr[r]; c++)
				{
					currentTrPos=trRows2D[r][c]; //searches through all columns for that row
					if ((currentTrPos>=startPosNum)&&(currentTrPos<=endPosNum))//pi file is zero based (so are training positions), start&end inclusive
					{
						//exons were marked with 888,888,888 so they won't be in any range
						offset=cumulIndArr[r];
						train_b[c+offset]=train_b[c+offset]++;//*****Jason's suggestion for debugging (goes from 0 to 1 to 2, etc). 
						count++;//local
					}
				}
			}
		}	
	}
	free(my_string);
	fclose(ifp);
	for (i=0; i<numTrRows; i++)
	{
		if (train_b[i]==1)
			fprintf(ofp, "%d\n", 1);
		else
			fprintf(ofp, "%d\n", -1);//NOTE: Label is -1 even though the value in array is zero because of unsigned array
	}
	fclose(ofp);
	return count;
}
int readFromOmegaFile(char *inputFileName, unsigned **trRows, int numTrRows, unsigned *train_b, unsigned **trRows2D, int numOfPosPerChr[], int cumulIndArr [], char ext[], char testChrom[])
{												
	char *mode = "r", *my_string, *token, *chrN, *startPos, *endPos, chrNPrev[6]="chr1";
	const char s[2] = "\t";
	size_t nbytes = 100;
	unsigned currentTrPos, startPosNum, endPosNum;
	int count=0, r=1, c=0, i=0, offset=0;
	FILE * ifp = fopen(inputFileName,mode);
	if (ifp == NULL) {
		fprintf(stderr, "Can't open input file in list%s!\n", inputFileName);
		exit(1);
	}
	//********write labels file
	mode = "w";
	//char train_b_FN [200]="/u/home/o/ogrujic/project-ernst/zarlab/combinedSampling/labels_omega_chr";
	char train_b_FN [200]="/u/home/o/ogrujic/project-ernst/zarlab/combinedSampling/labels_omega_test_chr";
	strcat(train_b_FN, testChrom); //test chromosome #
	strcat(train_b_FN, "/labels_omega");
	strcat(train_b_FN, ext);
	FILE *ofp = fopen(train_b_FN, mode);
	if (ofp == NULL) {
		fprintf(stderr, "Can't open output file %s!\n", "labels_omega");
		exit(1);
	} 
	//*********read from omega file
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
			if (strcmp(chrN, chrNPrev)!= 0)//if chromosome changed
			{
				r = selectChrRow(chrN);
				strcpy(chrNPrev,chrN);//update chrNPrev
			}
			if (r!=-1) //r is chromosome row in trRows 2D 
			{
				startPosNum = posStrToUnNum(startPos);
				endPosNum = posStrToUnNum(endPos);
				//checking whether current interval is on current chromosome and encompassing one of training sample positions
				for (c=0; c < numOfPosPerChr[r]; c++)
				{
					currentTrPos=trRows2D[r][c]; //searches through all columns for that row
					if ((currentTrPos>=startPosNum)&&(currentTrPos<=endPosNum))//omega file is zero based (so are training positions), start&end inclusive
					{
						//exons were marked with 888,888,888 so they won't be in any range
						offset=cumulIndArr[r];
						train_b[c+offset]=train_b[c+offset]++;//*****Jason's suggestion for debugging (goes from 0 to 1 to 2, etc). 
						count++;//local
					}
				}
			}
		}	
	}
	free(my_string);
	fclose(ifp);
	for (i=0; i<numTrRows; i++)
	{
		if (train_b[i]==1)
			fprintf(ofp, "%d\n", 1);
		else
			fprintf(ofp, "%d\n", -1);//NOTE: Label is -1 even though the value in array is zero because of unsigned array
	}
	fclose(ofp);
	return count;
}
int readFromPhastconsFile(char *inputFileName, unsigned **trRows, int numTrRows, unsigned *train_b, unsigned **trRows2D, int numOfPosPerChr[], int cumulIndArr [], char ext[], char testChrom[])
{												
	char *mode = "r", *my_string, *token, *chrN, *startPos, *endPos, chrNPrev[6]="chr1";
	const char s[2] = "\t";
	size_t nbytes = 100;
	unsigned currentTrPos, startPosNum, endPosNum;
	int count=0, r=1, c=0, i=0, offset=0;
	FILE * ifp = fopen(inputFileName,mode);
	if (ifp == NULL) {
		fprintf(stderr, "Can't open input file in list!\n");
		exit(1);
	}
	//********write labels file
	mode = "w";
	//char train_b_FN [200]="/u/home/o/ogrujic/project-ernst/zarlab/combinedSampling/labels_phastcons_chr";
	char train_b_FN [200]="/u/home/o/ogrujic/project-ernst/zarlab/combinedSampling/labels_phastcons_test_chr";
	strcat(train_b_FN, testChrom); //test chromosome #
	strcat(train_b_FN, "/labels_phastcons");
	strcat(train_b_FN, ext);
	FILE *ofp = fopen(train_b_FN, mode);
	if (ofp == NULL) {
		fprintf(stderr, "Can't open output file %s!\n", "labels_phastcons");
		exit(1);
	} 
	//*********read from phastcons file
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
			if (strlen(chrN)<=6) //ignore lines with leftover chromosome fragments
			{
				if (strcmp(chrN, chrNPrev)!= 0)//if chromosome changed
				{ 
					r = selectChrRow(chrN);
					strcpy(chrNPrev,chrN);//update chrNPrev
				}
				if (r!=-1) //r is chromosome row in trRows 2D 
				{
					startPosNum = posStrToUnNum(startPos);
					endPosNum = posStrToUnNum(endPos);
					//printf("%d %d %d\n", r, startPosNum, endPosNum);
					//checking whether current interval is on current chromosome and encompassing one of training sample positions
					for (c=0; c < numOfPosPerChr[r]; c++)
					{
						currentTrPos=trRows2D[r][c]; //searches through all columns for that row
						if ((currentTrPos>=startPosNum)&&(currentTrPos<=endPosNum))//phastcons file is zero based (so are training positions), start&end inclusive
						{
							//exons were marked with 888,888,888 so they won't be in any range
							offset=cumulIndArr[r];
							train_b[c+offset]=train_b[c+offset]++;//*****Jason's suggestion for debugging (goes from 0 to 1 to 2, etc). 
							count++;//local
						}
					}
				}
			}
		}	
	}
	free(my_string);
	fclose(ifp);
	for (i=0; i<numTrRows; i++)
	{
		if (train_b[i]==1)
			fprintf(ofp, "%d\n", 1);
		else
			fprintf(ofp, "%d\n", -1);//NOTE: Label is -1 even though the value in array is zero because of unsigned array
	}
	fclose(ofp);
	return count;
}
int readFromGERPFile(char inputFileName[], unsigned **trRows, int numTrRows, unsigned *train_b, unsigned **trRows2D, int numOfPosPerChr[], int cumulIndArr [], char ext[], char testChrom[])
{			
	char *mode = "r", *my_string, *token, *chrN, *startPos, *endPos, chrNPrev[6]="chr1", fNumStr[3], currentInputFileName[200];
	const char s[2] = "\t";
	size_t nbytes = 100;
	unsigned currentTrPos, startPosNum, endPosNum;
	int count=0, r=1, c=0, i=0, offset=0, f=1;
	//********write labels file
	//char train_b_FN [200]="/u/home/o/ogrujic/project-ernst/zarlab/combinedSampling/labels_GERP_chr";
	char train_b_FN [200]="/u/home/o/ogrujic/project-ernst/zarlab/combinedSampling/labels_GERP_test_chr";
	strcat(train_b_FN, testChrom); //test chromosome #
	strcat(train_b_FN, "/labels_GERP");
	strcat(train_b_FN, ext);
	FILE *ofp = fopen(train_b_FN, "w");
	if (ofp == NULL) {
		fprintf(stderr, "Can't open output file %s!\n", train_b_FN);
		exit(1);
	} 
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
			if( fgets (my_string, 100, ifp)!=NULL ) 
			{
				token = strtok(my_string, s);  //get the first token
				startPos = token;
				token = strtok(NULL, s);    //get the second token
				endPos = token;
				token = strtok(my_string, "\n");      //get the rest of the line
				startPosNum = posStrToUnNum(startPos)-1;//GERP file is one based, start&end inclusive (-1 to align it to be 0-based)
				endPosNum = posStrToUnNum(endPos)-1;//GERP file is one based, start&end inclusive (-1 to align it to be 0-based)
				//printf("%d %d %d\n", r, startPosNum, endPosNum);
				//checking whether current interval is on current chromosome and encompassing one of training sample positions
				for (c=0; c < numOfPosPerChr[r]; c++)
				{
					currentTrPos=trRows2D[r][c]; //searches through all columns for that row
					if ((currentTrPos>=startPosNum)&&(currentTrPos<=endPosNum))//GERP file is one based, start&end inclusive (-1 to align it to be 0-based)
					{
						//exons were marked with 888,888,888 so they won't be in any range
						offset=cumulIndArr[r];
						train_b[c+offset]=train_b[c+offset]++;//*****Jason's suggestion for debugging (goes from 0 to 1 to 2, etc). 
						count++;//local
					}
				}
			}	
		}
		free(my_string);
		fclose(ifp);
	}
	for (i=0; i<numTrRows; i++)
	{
		if (train_b[i]==1)
			fprintf(ofp, "%d\n", 1);
		else
			fprintf(ofp, "%d\n", -1);//NOTE: Label is -1 even though the value in array is zero because of unsigned array
	}
	fclose(ofp);
	return count;
}
int readGtfFile(char *gtfFileName, char *exonFileName)
{
	char *mode = "r", *my_string, *token;
	const char s[2] = "\t";
	unsigned startPosNum, endPosNum;
	int numExons=0, line=1, bytes_read=-1, gtfCol=1, chrN;
	size_t nbytes = 100;
	FILE * ifp = fopen(gtfFileName,mode);
	if (ifp == NULL) {
		fprintf(stderr, "Can't open input file .gtf!\n");
		exit(1);
	}
	mode = "w";
	FILE *ofp = fopen(exonFileName, mode);
	if (ofp == NULL) {
		fprintf(stderr, "Can't open output file %s!\n", exonFileName);
		exit(1);
	} 
	//********read exons from .gtf file
	while (!feof(ifp)) 
	{
		my_string = (char *) malloc (nbytes + 1);
		bytes_read = getline (&my_string, &nbytes, ifp); //reads in line from file as a string of nbytes
		if (bytes_read == -1)
		{
			printf ("ERROR!");
		}
		else
		{	
			token = strtok(my_string, s);//get the first token
			chrN=selectChrRow(token); //returns zero for chrM and chrY (returns 23 for chrX)
			if (chrN!=0) //chrM or chrY
			{
				token = strtok(NULL, s);
				token = strtok(NULL, s);
				if (strcmp(token, "exon")== 0)
				{  //if it's an exon (in 3rd column of .gtf file)
					numExons++;
					token = strtok(NULL, s);
					startPosNum = posStrToUnNum(token);
					token = strtok(NULL, s);
					endPosNum = posStrToUnNum(token);
					fprintf(ofp, "%d %u %u\n", chrN, startPosNum, endPosNum); //********write exon interval to file
				}
			}
		}
		free(my_string);
	}
	fclose(ifp);
	fclose(ofp);
	return numExons;
}
int readTrainingSampleRemoveExons(unsigned **trRows, int numTrRows, char *inputFileName, unsigned **trRows2D, int numOfPosPerChr[], int cumulIndArr [])
{
	char *mode = "r", *my_string, *token, *chrN, *startPos, *endPos, chrNPrev[6]="1";
	const char s[2] = " ";
	size_t nbytes = 100;
	unsigned currentTrPos, startPosNum, endPosNum;
	int count=0, r=1, c=0;	
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
			if (strcmp(chrN, chrNPrev)!= 0)//if chromosome changed
			{
				r = selectChrRow(chrN);
				strcpy(chrNPrev,chrN);//update chrNPrev
			}
			if (r!=-1) //r is chromosome row in trRows 2D 
			{
				startPosNum = posStrToUnNum(startPos)-1;//.gtf (exon) file is one based start&end inclusive (-1 to align it to be 0-based)
				endPosNum = posStrToUnNum(endPos)-1; //.gtf (exon) file is one based start&end inclusive (-1 to align it to be 0-based)
				//checking whether current interval is on current chromosome and encompassing one of training sample positions
				for (c=0; c < numOfPosPerChr[r]; c++)
				{
					currentTrPos=trRows2D[r][c]; //searches through all columns for that row
					if ((currentTrPos>=startPosNum)&&(currentTrPos<=endPosNum))//.gtf (exon) file is one based start&end inclusive
					{
						trRows2D[r][c]=888888888; //mark as exon, they're not going to be in the interval
						count++;
					}
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
	int numTrRows=1000000, totalFeatures=10836;
	int chromSize[]= {-1, 249250621, 243199373, 198022430, 191154276, 180915260, 171115067, 159138663, 146364022, 141213431, 135534747, 135006516,
		133851895, 115169878, 107349540, 102531392, 90354753, 81195210, 78077248, 59128983, 63025520, 48129895, 51304566, 155270560};
	int m=0, k=0, l=0, numExons=0, maxCountPos=0, caseNum, numOfOnes=0;
	int numOfPosPerChr[24], cumulIndArr[24]; //chr [1 - 23], ignore 0th element
	double probabilities [24];

	char gtfFile[200]="/u/home/o/ogrujic/project-ernst/zarlab/sourceDataFiles/gencode.v19.annotation.gtf";
	char exonFile[200]="/u/home/o/ogrujic/project-ernst/zarlab/sourceDataFiles/exon_pos_v19.txt";
	char PiFileName[200]="/u/home/o/ogrujic/project-ernst/zarlab/sourceDataFiles/hg19_29way_pi_lods_elements_12mers.chr_specific.fdr_0.1_with_scores.txt";
	char OmegaFileName[200]="/u/home/o/ogrujic/project-ernst/zarlab/sourceDataFiles/hg19_29way_omega_lods_elements_12mers.chr_specific.fdr_0.1_with_scores.txt";
	char PhastconsFileName[200]="/u/home/o/ogrujic/project-ernst/zarlab/sourceDataFiles/phastconselements_100_hg19.txt";
	char GERPfileName[200]="/u/home/o/ogrujic/project-ernst/zarlab/sourceDataFiles/GERP/hg19_chr";

	if ( argc != 6 ) 
	{   
        printf( "usage: %s filename [1-12] [0-23] sampleNumber testChrom\n", argv[0] ); //argv[0] is the program name argv[2] for switch, argv[3] 0 if not sampling, test chromosome number otherwise, argv[5] testChromNum for file names
		exit(1);
    }
    FILE *file = fopen( argv[1], "w" ); // We assume argv[1] is a filename to write to
    if ( file == 0 ) // fopen returns 0, the NULL pointer, on failure
    {
        printf( "Could not open file %s\n", argv[1] );
		exit(1);
    }
	//*****creating training rows*****
	unsigned **trRows=umatrix(0,numTrRows,0,1), **trRows2D;
	for (l=0; l<numTrRows; l++) 
	{
		trRows[l][0]=0; //initialize training rows to zeros
		trRows[l][1]=0; 
	}	
	//char trSamplesFile[200]="/u/home/o/ogrujic/project-ernst/zarlab/createTrainX/sampleTrainingPositionsChr";
	char trSamplesFile[200]="/u/home/o/ogrujic/project-ernst/zarlab/createTrainX/sampleTestPositions/";
	//strcat(trSamplesFile, argv[5]); //test chromosome #
	//strcat(trSamplesFile, "/sampleTrainingPositions");
	strcat(trSamplesFile, "/sampleTestPositions");
	char ext[20]="_";
	strcat(ext, argv[4]); //_11
	strcat(ext, "m"); //_11m
	strcat(trSamplesFile, ext);
	strcat(trSamplesFile, ".txt");
	if (strcmp(argv[3],"0")!=0) //new sample
	{
		unsigned testChr=posStrToUnNum(argv[3]);
		int numRows=sampleChromPos(chromSize, probabilities, 23, trRows, numTrRows, testChr, trSamplesFile);//new sample
		if (numRows!=numTrRows)
		{
			printf("Sampling Error! Exiting... \n");
			exit(1);
		}
	}
	numTrRows=readTrainingSample(trRows, numTrRows, trSamplesFile); //*****reading training rows*****
	//*****transform the training sample into a matrix*****
	maxCountPos=countMaxPosChrNum (trRows, numTrRows, numOfPosPerChr); //count chr# with max # of sampled positions
	printf ("MaxCountPos is: %d \n", maxCountPos); //*****temp
	trRows2D=umatrix(0,24,0,maxCountPos);
	for (m=0; m<24; m++)	
		for (k=0; k<maxCountPos; k++)
			trRows2D[m][k]=999999999; //initialize to 999999999
	storeSamplePos2D (trRows2D, trRows, numTrRows, numOfPosPerChr, cumulIndArr);

	//*****Create train_b NOTE: Needs to be done AFTER creating train_x as training vector gets modified (exon positions get excluded)*****
	unsigned *train_b_pi=vector(0, numTrRows); //output vector (sparse format); unsigned, but needs to have '-1' printed
	unsigned *train_b_omega=vector(0, numTrRows); //output vector (sparse format); unsigned, but needs to have '-1' printed
	unsigned *train_b_phastcons=vector(0, numTrRows); //output vector (sparse format); unsigned, but needs to have '-1' printed
	unsigned *train_b_GERP=vector(0, numTrRows); //output vector (sparse format); unsigned, but needs to have '-1' printed
	for (l=0;l<numTrRows;l++)
	{
		train_b_pi[l]=0; //should be -1, but this is unsigned vector, checking for that before writing to a file
		train_b_omega[l]=0;
		train_b_phastcons[l]=0;
		train_b_GERP[l]=0;
	}
	//numExons=readGtfFile(gtfFile, exonFile);//first find exons in .gtf file v19
	//printf("Num of exon lines read from .gtf file is: %d\n", numExons); //num of exon lines: 1,191,627 
	//*****update training rows: if training pos is an exon, mark 888,888,888 in that position (sampled positions):
	numExons=readTrainingSampleRemoveExons(trRows, numTrRows, exonFile, trRows2D, numOfPosPerChr, cumulIndArr);
	printf ("number of exons excluded %d\n", numExons);
	numOfOnes=readFromPiFile(PiFileName, trRows, numTrRows, train_b_pi, trRows2D, numOfPosPerChr, cumulIndArr, ext, argv[5]); 
	numOfOnes=readFromOmegaFile(OmegaFileName, trRows, numTrRows, train_b_omega, trRows2D, numOfPosPerChr, cumulIndArr, ext, argv[5]); 
	numOfOnes=readFromPhastconsFile(PhastconsFileName, trRows, numTrRows, train_b_phastcons, trRows2D, numOfPosPerChr, cumulIndArr, ext, argv[5]); 
	numOfOnes=readFromGERPFile(GERPfileName, trRows, numTrRows, train_b_GERP, trRows2D, numOfPosPerChr, cumulIndArr, ext, argv[5]); 
	
	printf("There are %d ones in response vector \n", numOfOnes);
	free_vector(train_b_pi, 0, numTrRows);
	free_vector(train_b_omega, 0, numTrRows);
	free_vector(train_b_phastcons, 0, numTrRows);
	free_vector(train_b_GERP, 0, numTrRows);
	free_umatrix(trRows2D,0,24,0,maxCountPos);
	free_umatrix(trRows,0,numTrRows,0,1); 
	return 0;
}