import java.io.*;
import java.util.*;

public class Constants
{
    //////////////////////////////////////
    //input files
    ///////////////////////////////////
    /**
     * Directory where the input bed files are
     */
    static String INPUTBEDDIR = "INPUTBEDDIR";

    /**
     * List of features one per line, where each feature corresponds to a bed file in INPUTBEDDIR or subdirectory
     */
    static String FEATUREFILELIST = "featurelist_allinputbeds.txt";

    /**
     * List of chromosomes one per line to be included
     */
    static String CHROMORDERFILE = "chrorderlist.txt";

    /**
     * File with chromosome sizes, two columns with first chromosome and second size
     */
    static String CHROMSIZES = "hg19.chrom.sizes";

    /**
     * Directory where the label bed files are constrained elements
     */
    static String LABELBEDDIR = "LABELSCOORDSBEDDIR";

    /**
     *  List of label files one per line, where each label file corresponds to a bed file in LABELBEDDIR
     */
    static String LABELLIST = "labellist.txt";

    /**
     * Bed file with exon coordinates
     */
    static String EXONBEDFILE = "exons_gencode_v19.bed.gz";


    /**
     * The first column contains the directory TRAINDIR_SUBSET for the feature subset.
     * The second column contains the featurelist_subset.txt file name for the feature subset.
     * The third column contains the subdirectory within INPUTBEDDIR containing the bed files for the feature subset.
     */
    static String TRAINDIRFEATURES = "traindirfeatures.txt";

    //////////////////////////////////////
    //intermediate directories
    /////////////////////////////////////
    /**
     * Directory where sample files are written
     */
    static String SAMPLEDIR = "SAMPLEDIR";

    /**
     * Directory where training files are written
     */
    static String TRAINDIR = "TRAINDIR";

    /**
     * Directory where trained models are written
     */
    static String MODELDIR = "MODELSDIR";

    /**
     * Directory where predictions are written for portions of chromosome
     */
    static String PORTIONSDIR = "PREDICTIONSPORTIONSDIR";

    /**
     * Directory where full chromosome predictions are written for single label sets
     */
    static String COMBINEDDIR = "FULLCHROMBYLABELDIR";



    ////////////////////////////
    //final output dir
    ///////////////////////////
    /**
    * Directory where the final CNEP predictions are written
    */
    static String OUTPUTDIR = "CNEPDIR";


    /**
     * Feature Conservation
     */
    static String EXPECTCNEPFILE = "features_conservation.txt";


    /////////////////////////////
    //Numerical parameters
    /////////////////////////////
    /**
     * Number of classifers to average to make the predictions
     */
    static int NUMENSEMBLES = 10;

    /**
     * Number of samples per ensemble
     */
    static int NUMSAMPLES = 1000000;

    /**
     * Number of portions to make per chromosome
     */
    static int NUMPORTIONS = 10;


    ////////////////////////////
    //// CSS-CNEP specific parameters
    ////////////////////////////

    /**
     * Intermediate directory where the combo averages are written
     */
    static String CSSNCEP_AVERAGEDIR = "CSSCNEP_AVERAGES";

    /**
     * Directory where the final CSS_CNEP predictions are written
     */
    static String CSSCNEP_OUTPUTDIR = "CSSCNEP_OUTPUTDIR2018";

    /**
     * Number of ConsHMM conservation states
     */
    static int NUMCONSHMM = 100;

    /**
     * File nae with the ConsHMM segments
     */
    static String CONSHMM_SEGMENTS = "GW_segmentation.bed.gz";

}    
