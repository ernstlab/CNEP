# CNEP and CSS-CNEP
The Constrained Non-Exonic Predictor (CNEP) provides a score for each base of the genome of evidence that the base is in a constrained non-exonic element from information within large-scale collections of epigenomic and transcription factor binding data. The method was applied to the human genome using over sixty thousand features defined from such data. 

The Conservation Signature Score by CNEP (CSS-CNEP) is a complementary score for each base of the genome of its expected CNEP score based on the ConsHMM conservation state annotation and overlapping constrained element annotations of the base.

## CNEP and CSS-CNEP predictions
CNEP predictions for the human genome (hg19) is available in BigWig format (.bw) [here](https://ernst.cass.idre.ucla.edu/public/CNEP/cnep.bw) or 
in Wig format (.wig) by chromosome [here](https://ernst.cass.idre.ucla.edu/public/CNEP/CNEP_WIGFILES_BYCHROM/).
Input files used to generate the predictions are available [here](https://ernst.cass.idre.ucla.edu/public/CNEP/INPUTFILES/).
CSS-CNEP predictions for the human genome (hg19) is available in BigWig format (.bw) [here](https://ernst.cass.idre.ucla.edu/public/CNEP/css_cnep.bw) or
in Wig format (.wig) by chromosome [here](https://ernst.cass.idre.ucla.edu/public/CNEP/CSSCNEP_WIGFILES_BYCHROM/).

## Running CNEP

Running CNEP involves seven steps. The first step is preparing the input files. The second set is generating a set of sampled positions for training. The third is creating training files for calling Liblinear. The fourth step is calling Liblinear on each training file. The fifth step is generating predictions for portions of each chromosome. The sixth step is combining predictions from different portions of the same chromosome and label set. The seventh step is to average predictions based on different label sets. 

### Step 1: Prepare Input Files

The input files and directories are specified in Constants.java. If they need to be changed then edit Constants.java and type
> javac -classpath . *.java

By default these are the inputs:

*INPUTBEDDIR* - directory containing bed files for the input features; one bed file for input feature

*featurelist_allinputbeds.txt* -- file containing the list of bed files within INPUTBEDDIR one per line

*chrorderlist.txt* -- list of chromosomes to be included one per line

*hg19.chrom.sizes* -- tab delimited text file with chromosome information, two columns with first chromosome and the second chromosome size

*LABELSCOORDSBEDDIR* -- directory containing .bed files for constrained element sets; one .bed file for each constrained
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

The directory with the final CNEP predictions in Wig format is *CNEPDIR*

Additionally the defaults for the number of samples per classifier is 1,000,000, the number of classifers
being ensembled is 10, and the number of portions for predictions is 10.


### Step 2: Generate Sampled Positions
This step generates a set of sampled positions for training each of the classifiers. For each chromosome ten sets of a million positions are generated where positions from that chromosome are excluding from sampling. This should be executed by calling:

>java -classpath . MakeSampling


### Step 3: Create Training Files
This generates training files for each of the constrained element sets based on the sampled positions in samplingfile for training Liblinear. 

There are two options for creating training files. Option A creates one set of training files for all the features.
Option B creates training files based on subsets of features that are merged in step 4 Option B. Option A is simpler,
but Option B better scales to large number of features as they can be split into subsets of features and processed in parallel.

Option A

>java -mx14000M -classpath . MakeTrainFiles samplingfile

This should be called for each sampling file. There are 10 sampling files for each chromosome.

Option B

>java -mx14000M -classpath . MakeTrainFiles samplingfile INPUTBEDDIR_SUBSET featurelist_subset.txt TRAINDIR_SUBSET

This should be called for each sampling file and feature subset. *INPUTBEDDIR_SUBSET* is a directory where the bed files are for the subset of features. *featurelist_subset.txt* is a file which lists the file names of features, one per line, that are part of the subset and also in INPUTBEDDIR_SUBSET. *TRAINDIR_SUBSET* is the name of the directory where training data for the subset of features should be written. Each feature subset should have a different output directory since files of the same name are written to each directory.


### Step 4: Train Classifers

First obtain Liblinear, which can be downloaded from here https://www.csie.ntu.edu.tw/~cjlin/liblinear/.
Also gunzip must be available. Next create the directory MODELSDIR.

There are also two options for this step. If Option A was used in Step 3, then option A should be used in this step.
If Option B was used in Step 3, then option B should be used in this step.

Option A

For each training file in TRAINDIR_SUBSET directories created in step 3 option A execute these set of commands:
>gunzip TRAINDIR/trainfile

>LIBLINEAR/liblinear-2.1/train -s 6 -B 1 -c 1 TRAINDIR/trainfile MODELSDIR/trainfile.model

>gzip TRAINDIR/trainfile

>gzip MODELSDIR/trainfile.model

where trainfile is the name of the training file.

Option B

For each training file name in the TRAINDIR_SUBSET created in step 3 option B, trainfile, execute these set of commands:

> java -classpath . MergeTrainFiles trainfile traindirfeatures.txt TRAINDIR_MERGED

> gunzip TRAINDIR_MERGED/trainfile

> LIBLINEAR/liblinear-2.1/train -s 6 -B 1 -c 1 TRAINDIR_MERGED/trainfile MODELSDIR/trainfile.model

> rm TRAINDIR_MERGED/trainfile

> gzip MODELSDIR/trainfile.model

where
*traindirfeatures.txt* - is a tab delimited text file with each line corresponding to a feature subset. The first column contains the directory TRAINDIR_SUBSET for the feature subset from Step 3 option B. The second column contains the featurelist_subset.txt file name for the feature subset from Step 3 option B.

*TRAINDIR_MERGED* is the name of the directory where the merged training data feature files should be written and should be different
than the train directory for any of the subsets

*MODELSDIR* is the name of the directory where the models should be written


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
This step combines the predictions from different portions to make single .wig files for each chromosome.
This can be done with the command:

>java -mx8000M -classpath . CombineFiles chrN

This should be called for each chromosome.

### Step 7: Average Predictions from Different Label Sets 
This step averages predictions based on training with labels from different constrained element sets.
This can be done with the command:

>java -mx8000M -classpath . MakeCNEPAverage chrN

This should be called for each chromosome.

## Running CSS-CNEP

### Step 1: Run CNEP 

Before running CSS-CNEP, CNEP should be run following the procedures above.

### Step 2: Prepare the input files

The input files and directories are specified in Constants.java. If they need to be changed then edit Constants.java and type
> javac -classpath . *.java

The input files should generally be the same as provided when running CNEP.
There is one additional input file with the ConsHMM segmentation file which defaults
to *GW_segmentation.bed.gz*

There is one intermediate directory *CSSCNEP_AVERAGES* where the average CNEP value
for different conservation signatures are written. There is a separate file based on excluding
each chromosome but including all others.

The directory with the final CNEP predictions in wig format is *CNEPDIR*

There is one parameter for the number of states in the ConsHMM model which defaults to 100.

### Step 3: Compute conservation signature averages
This step computes the average CNEP value for each conservation signature, which is a combination
of conservation state and constrained element overlaps.
For each target chromosome, this is computed based on all input chromosomes except the target chromosome.

> java -classpath . ComputeAveragesCSS_CNEP chrN

This should be called for each chromosome.

### Step 4: Generate CSS-CNEP scores
This step generate the CSS-CNEP scores.

This can be done with the command:

> java -classpath . MakeCSS_CNEPPredict chrN

This should be called for each chromosome.

## Reference
Grujic O, Phung TN, Kwon SB, Arneson A, Lee Y, Lohmueller KE, Ernst J.
Identification and characterization of constrained non-exonic bases lacking predictive epigenomic and transcription factor binding annotations. bioRxiv 722876; doi: https://doi.org/10.1101/722876 
