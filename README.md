# CNEP
Constrained Non-Exonic Predictor (CNEP), created and applied to the human genome using over ten thousand features defined from large-scale epigenomic and transcription factor binding data to score the evidence of each base being in a constrained non-exonic element from such data.

## CNEP predictions
CNEP predictions for the human genome (hg19) is available in BigWig format (.bw) [here](https://ernst.cass.idre.ucla.edu/public/CNEP/cnep.bw) or 
in Wig format (.wig) by chromosome [here](https://ernst.cass.idre.ucla.edu/public/CNEP/WIGFILES_BYCHROM/).
Input files used to generate the predictions are available [here](https://ernst.cass.idre.ucla.edu/public/CNEP/INPUTFILES/).

## Running CNEP
### Step 1 Generate Samples
This step generates a set of sampled positions for training each of the classifiers. For each chromosome ten sets of a million positions are generated where positions from that chromosome are excluding from sampling. This should be executed by calling:

>java -classpath . MakeSampling


### Step 2 Create Training Files
This generates training files for each of the labels based on the sampled positions in samplingfile. 

>java -classpath . MakeTrainFiles samplingfile

This should be called for each sampling file. There are 10 sampling files for each chromosome.

### Step 3 Train Classifers

Classifiers should be trained with Liblinear https://www.csie.ntu.edu.tw/~cjlin/liblinear/




### Step 4 Generate Predictions on Portions of Chromosomes
This step takes the trained classifers and makes predictions for each label set in ten different subsets of each chromosome.
This is done to allow the execution to be done using less memory and time.

>java -mx8000M -classpath . MakeCNEPPredict portion labelfile chrN

portion is value between 0 to 9, when there are 10 portions per chromosome 
labelfile should be the name of the label file without the .gz extension if present
chrN is a chromosome to predict on which should be present in labellist.txt

This should be called for each combination of the ten portions, label sets, and chromosome combinations

### Step 5 Combine Chromosome Predictions
This step combines the predictions from different portions to make single wig files for each chromosome
>java -mx8000M -classpath . CombineFiles chrN

This should be called for each chromosome

### Step 6 Predicitions from Different Label Sets 

>java -mx8000M -classpath . MakeCNEPAverage chrN

This should be called for each chromosome
