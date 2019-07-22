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

struct myData {
    double data;
    char label;
};

int myData_compare_inc (const void* a, const void* b) { //sorts in increasing order
    if ((((struct myData*)a)->data) - (((struct myData*)b)->data)>0){
    	return 1;
    } else if ((((struct myData*)a)->data) - (((struct myData*)b)->data)<0){
    	return -1;
    }
    return 0;
}

int myData_compare (const void* a, const void* b) { //sorts in decreasing order
    if ((((struct myData*)a)->data) - (((struct myData*)b)->data)>0)
    	return -1;
    else if ((((struct myData*)a)->data) - (((struct myData*)b)->data)<0)
    	return 1;
	if ((((struct myData*)a)->data) - (((struct myData*)b)->data)==0) //if two numbers are equal, break ties by assigning random number
	{
		srand(time(NULL));
		double r1 = (double) rand()/RAND_MAX; //now they are doubles between 0 and 1 in format 0.xxxxxx
		double r2 = (double) rand()/RAND_MAX; //now they are doubles between 0 and 1 in format 0.xxxxxx
		if (r1 > r2)
			return -1;
		else 
			return 1;
	}
    return 0; //if numbers are still equal...
}

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
int compare_unsigned (const void * a, const void * b)
{
	return ( *(unsigned*)a - *(unsigned*)b );
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

int readTestFile(FILE *test_sample_file, char *response, int numTrRows, int numOfFeatures, int numOfModelFiles, double** probsPositions, double** modelVectors)
{
	char *token, featureToken[10];
	size_t nbytes = 100000;
	int bytes_read=-1, featNum, line=0, i=0, positive=0;	
	char *my_string = (char *) malloc (nbytes + 1);
	while (!feof(test_sample_file)) 
	{
		if( fgets (my_string, nbytes, test_sample_file)!=NULL && (strlen(my_string) != 0)) 
		{
			token = strtok(my_string, " \n"); //get the first token (it'll break on space or enter)
			if (strcmp(token, "-1")==0)
				response[line]='0';
			else if (strcmp(token, "1")==0)
			{
				response[line]='1';
				positive++;
			}
			else printf("invalid token %s \n", token);
			while (token!=NULL)
			{
				token = strtok(NULL, " \n");  //get the next token (it'll break on space or enter)
				if (token!=NULL)
				{
					char *featureToken = (char *) malloc (strlen(token) + 1);//featureToken cannot be defined as *featureToken
					strncpy(featureToken, token, strstr(token, ":")-token); //copies into featureToken the characters before :
					featNum=posStrToInt(featureToken);
					free(featureToken);
					if ((featNum>=1)&&(featNum<=numOfFeatures))
					{
						//needs updated for each row (sample) of training file, where feature is present, add corresponding weight to the running sum
						for (i=1; i<=numOfModelFiles; i++) //do this for all running sums (one per model file)
							probsPositions[line][i]+=modelVectors[featNum][i]; //need probability per position (training sample)
					}
					else
					{
						printf ("Feature number read in seems invalid %d. Total number of features specified is: %d.\n", featNum, numOfFeatures);
						exit(1);
					}
				}
			}
			line++;
		}
	}
	if (line!=numTrRows)
	{
		printf ("Number of samples read in %d doesn't equal specified number of samples %d\n", line, numTrRows);
		exit(1);
	}
	return positive;
}

int main(int argc, char *argv[] ) 
{	
	int numOfFeatures=10836, numTrRows=1000000, line=0, position=0, pos=0, neg=0, i=1, numOfModelFiles=10; 
	if ( argc != 4 ) //argc should be 4 for correct execution (for 4 arguments)
    {   
		printf( "usage: %s model_filename train_liblinear test_liblinear test_chrom_#\n", argv[0] ); //argv[0] is the program name
		// ./scorePredictions train_liblinear test_liblinear 23 > AUC_10samples_l1_lambda1_chr23
		exit(1);
    }

	//reading in test set (labels are read in from train_liblinear format file)
	char fileName2[FILE_PATH_LEN];
	//char filePath2 [FILE_PATH_LEN] = "/u/home/o/ogrujic/project-ernst/zarlab/createTrainX/testLiblinear/"; //this is where one test sample file is
	char filePath2 [FILE_PATH_LEN] = "/u/home/o/ogrujic/project-ernst/zarlab/combinedSampling/testLiblinearGERP/"; //this is where one test sample file is
	strcpy(fileName2,argv[2]); //assume argv[2] is "test_liblinear"
	strcat (filePath2, fileName2); // /u/home/o/ogrujic/project-ernst/zarlab/createTrainX/testLiblinear/test_liblinear
	strcat (filePath2, "_"); //	/u/home/o/ogrujic/project-ernst/zarlab/createTrainX/testLiblinear/test_liblinear_
	strcat (filePath2, argv[3]); //test chromosome number //	/u/home/o/ogrujic/project-ernst/zarlab/createTrainX/testLiblinear/test_liblinear_#
	strcat (filePath2, "m"); //	/u/home/o/ogrujic/project-ernst/zarlab/createTrainX/testLiblinear/test_liblinear_#m
	strcpy (fileName2, filePath2); // put same in fileName2

	char fileName3[FILE_PATH_LEN];
	strcpy(fileName3,"labels_scores_sorted_chr");
	strcat (fileName3, argv[3]); //test chromosome number //labels_scores_sorted_chr#
	FILE *score_file = fopen(fileName3, "w");
	if (score_file == NULL) {
		fprintf(stderr, "Couldn't open output file %s!\n", fileName3); //labels_scores_sorted_chr# (to write scores and labels for ROC plot)
		exit(1);
	}

	//****** begin reading in model files
	double* intercepts=double_vector(0, numOfModelFiles); //cumulative for averaging predictions
	for (i=1; i<=numOfModelFiles; i++)	
		intercepts[i]=0.0; //initialize to zeros

	double **modelVectors=dmatrix(0,numOfFeatures,1,numOfModelFiles);
	for (position=0; position<numOfFeatures; position++)	
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
		char filePath1 [FILE_PATH_LEN] = "/u/home/o/ogrujic/project-ernst/zarlab/averageGenomewide/l1_modelFiles1_GERP_chr"; //this is where one set of model files is
		strcat (filePath1, argv[3]); //test chromosome number
		strcat (filePath1, "/");
		strcpy(fileName1,argv[1]); // We assume argv[1] is a filename "train_liblinear"
		strcat (fileName1, fileExtension); //"train_liblinear_1m.model"
		strcat (filePath1, fileName1); // /u/home/o/ogrujic/project-ernst/zarlab/averageGenomewide/l1_modelFiles1_chr#/train_liblinear_*m.model in filePath1
		strcpy (fileName1, filePath1); // same in fileName1
		FILE *model_file = fopen( fileName1, "r" ); 
		if (model_file == 0 ) // fopen returns 0, the NULL pointer, on failure
		{
			fprintf(stderr, "Couldn't open input file %s!\n", fileName1); //train_liblinear
			exit(1);
		} 
		intercepts[i]=readModelFeatures(model_file, modelVectors, numOfFeatures, i);
		fclose(model_file);
		printf("model file read in: %d \n", i); //*****temp

	}
	//****** end of reading in model files

	//****** begin reading in test file
	char* response = malloc(sizeof(char*)*numTrRows+1); 
	if (response==NULL)
		exit(1);
	for (position=0; position<numTrRows; position++)
		response[position]='0'; //initialize to '0' (since '-1' is 2 characters)

	double* probsPositionsSum=double_vector(0, numTrRows); //cumulative for averaging predictions
	double** probsPositions=dmatrix(0,numTrRows,1,numOfModelFiles);
	for (position=0; position<numTrRows; position++)	
	{
		probsPositionsSum[position]=0.0; //initialize to zeros
		for (i=1; i<=numOfModelFiles; i++)
			probsPositions[position][i]=0.0; //initialize to zeros
	}

	FILE *test_sample_file = fopen(fileName2, "r");
	if (test_sample_file == NULL) {
		fprintf(stderr, "Couldn't open test sample file %s!\n", fileName2); //test_liblinear
		exit(1);
	}
		
	pos=readTestFile(test_sample_file, response, numTrRows, numOfFeatures, numOfModelFiles, probsPositions, modelVectors); //updates probsPositions
	neg=numTrRows-pos;
	printf("response positive: %d, negative: %d\n", pos, neg); 
	fclose(test_sample_file);
	
	for (position=0; position<numTrRows; position++)
		for (i=1; i<=numOfModelFiles; i++)	
		{
			probsPositions[position][i]=1/(1+exp(-(probsPositions[position][i]+intercepts[i]))); //final probability for this position (intercept + all products summed up; all that put through 1/1+e^-) 
			probsPositionsSum[position]+=probsPositions[position][i]; //store current predictions in order to average them at the end
		}
	
	for (position=0; position<numTrRows; position++)
	{
		probsPositionsSum[position]/=numOfModelFiles; //average predictions
		//printf("%.3f\n", probsPositionsSum[position]);
	}
	//calculate AUC for this set 
	struct myData* helpVec = (struct myData*) malloc(numTrRows * sizeof(struct myData));
	for (position=0; position<numTrRows; position++)
	{
		helpVec[position].data=probsPositionsSum[position];
		helpVec[position].label=response[position];
	}
	//void qsort (void *array, size_t count, size_t size, comparison_fn_t compare); //sorts array which contains count elements, each of which is of size. 
	qsort(helpVec, numTrRows, sizeof(struct myData), myData_compare); //sort helpVec by scores in DEcreasing order (and keep corresponding labels)
	for (position=0; position<numTrRows; position++) 
	{
		fprintf (score_file, "%c %.3f\n",helpVec[position].label, helpVec[position].data); //print to 3 decimals
	}
	double auc=0.0, height = 0.0;
	double tpr=1.0/pos, fpr=1.0/neg;
	for (position=0; position<numTrRows; position++)
	{
		if (helpVec[position].label == '1') //helpVec is sorted by scores in DEcreasing order
			height+=tpr;
		else
			auc+=height*fpr;
	}
	printf("AUC is %.10f \n", auc); //0.8230288616 for 10 samples 0.8284 for 100 samples
	free(helpVec); 
	free(response);
	free_double_vector(probsPositionsSum, 0, numTrRows);
	free_dmatrix(probsPositions, 0,numTrRows,1,numOfModelFiles);
	free_double_vector(intercepts, 0, numOfModelFiles);
	free_dmatrix(modelVectors, 0,numOfFeatures,1,numOfModelFiles);
	fclose(score_file); //only close after all while loops finish
	return 0;
}