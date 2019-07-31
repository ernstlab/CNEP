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
     * List of features one per line, where each feature corresponds to a bed file in INPUTBEDDIR
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
    static String LABELBEDDIR = "LABELSCOORDSBED";

    /**
     *  List of label files one per line, where each label file corresponds to a bed file in LABELBEDDIR
     */
    static String LABELLIST = "labellist.txt";

    /**
     * Bed file with exon coordinates
     */
    static String EXONBEDFILE = "exons_gencode_v19.bed.gz";

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


}