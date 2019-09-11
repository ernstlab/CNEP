# CNEP
The Constrained Non-Exonic Predictor (CNEP) provides a score of evidence that each base of the genome in a constrained non-exonic base from information within large-scale collections of epigenomic and transcription factor binding data. The method was applied to the human genome using over ten thousand features defined from such data.

## CNEP predictions
CNEP predictions for the human genome (hg19) is available in BigWig format (.bw) [here](https://ernst.cass.idre.ucla.edu/public/CNEP/cnep.bw) or 
in Wig format (.wig) by chromosome [here](https://ernst.cass.idre.ucla.edu/public/CNEP/WIGFILES_BYCHROM/).
Input files used to generate the predictions are available [here](https://ernst.cass.idre.ucla.edu/public/CNEP/INPUTFILES/).

## Running CNEP

Running CNEP involves seven steps. The first step is preparing the input files. The second set is generating a set of sampled positions for training. The third is creating training files for calling Liblinear. The fourth step is calling Liblinear on each training file. The fifth step is generating predictions for portions of each chromosome. The sixth step is combining predictions from different portions of the same chromosome and label set. The seventh step is to average predictions based on different label sets. 

### Step 1: Prepare Input Files

The input files and directories are specified in Constants.java. If they need to be changed then edit Constants.java and type
> javac -classpath . Constants.java

By default these are the inputs:

*INPUTBEDDIR* - directory containing bed files for the input features; one bed file for input feature

*featurelist_allinputbeds.txt* -- file containing the list of bed files within INPUTBEDDIR one per line

*chrorderlist.txt* -- list of chromosomes to be included one per line

*hg19.chrom.sizes* -- tab delimited text file with chromosome information, two columns with first chromosome and the second chromosome size

*LABELSCOORDSBEDDIR* -- directory containing /bed files for constrained element sets; one .bed file for each constrained
elements

*labellist.txt* -- text file listing constrained elements one per line without .gz extension included if files are
gzipped

*exons_gencode_v19.bed.gz* - bed file with exon coordinates

These are by default directories with intermediate outputs:

*SAMPLEDIR* -- Directory where sample files are written

*TRAINDIR* -- Directory where training files are writen

*MODELSDIR* -- Directory where trained models are written

*PREDICTIONSPORTIONSDIR* -- directory where predictions are written for portions of chromosomes

*FULLCHROMBYLABELDIR* -- directory where full chromosome predictions are written for single label sets

The directory with the final CNEP predictions in wig format is *CNEPDIR*

Additionally the defaults for thenumber of samples per classifier is 1,000,000, the number of classifers
being ensembled is 10, and the number of portions for predictions is 10.


### Step 2: Generate Sampled Positions
This step generates a set of sampled positions for training each of the classifiers. For each chromosome ten sets of a million positions are generated where positions from that chromosome are excluding from sampling. This should be executed by calling:

>java -classpath . MakeSampling


### Step 3: Create Training Files
This generates training files for each of the constrained element sets based on the sampled positions in samplingfile for training Liblinear. 

>java -mx14000M -classpath . MakeTrainFiles samplingfile

This should be called for each sampling file. There are 10 sampling files for each chromosome.

### Step 4: Train Classifers

First obtain Liblinear, which can be downloaded from here https://www.csie.ntu.edu.tw/~cjlin/liblinear/.
Also gunzip must be available. Create the directory MODELSDIR.

For each training file in TRAINDIR created in step 3 execute these set of commands:
>gunzip TRAINDIR/trainfile

>LIBLINEAR/liblinear-2.1/train -s 6 -B 1 -c 1 TRAINDIR/trainfile MODELSDIR/trainfile.model

>gzip TRAINDIR/trainfile

>gzip MODELDIR/trainfile.model

where trainfile is the name of the training file.

### Step 5: Generate Predictions on Portions of Chromosomes
This step takes the trained classifers and makes predictions for each label set in ten different subsets of each chromosome.
Predictions are made on portions of each chromosome to allow execution to be done using less memory and time.
This can be done with the command:

>java -mx8000M -classpath . MakeCNEPPredict portion labelfile chrN

where portion is value between 0 to 9, when there are 10 portions per chromosome 
labelfile should be the name of the label file without the .gz extension if present
chrN is a chromosome to predict on which should be present in labellist.txt

This should be called for each combination of the ten portions, label set, and chromosome.

### Step 6: Combine Chromosome Predictions
This step combines the predictions from different portions to make single .wig files for each chromosome
This can be done with the command:

>java -mx8000M -classpath . CombineFiles chrN

This should be called for each chromosome.

### Step 7: Average Predicitions from Different Label Sets 

>java -mx8000M -classpath . MakeCNEPAverage chrN

This should be called for each chromosome.


## Reference
Grujic O, Phung TN, Kwon SB, Arneson A, Lee Y, Lohmueller KE, Ernst J.
Identification and characterization of constrained non-exonic bases lacking predictive epigenomic and transcription factor binding annotations. bioRxiv 722876; doi: https://doi.org/10.1101/722876 
