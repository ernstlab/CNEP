import java.io.*;
import java.util.*;
import java.util.zip.*;
import java.text.*;

public class MakeCNEPPredict
{

    //static int DEFAULT_NUMPORTIONS = 10;

    public static void main(String[] args) throws IOException
    {
	NumberFormat nf = NumberFormat.getInstance();
	nf.setMaximumFractionDigits(3);
	nf.setGroupingUsed(false);
	nf.setMinimumFractionDigits(3);

	/*
	String szmodeldir = args[0];
        String szmodelfilelist = args[1];
	String szinputbeddir = args[2];
	String szfeaturelist = args[3];
	String szoutputdir = args[4];
        String szoutprefix = args[5];
	String szchromfile = args[6];
	String szchrom = args[7];
	int nportion = Integer.parseInt(args[8]);
	int numportions = Integer.parseInt(args[9]);
	*/

	String szmodeldir = Constants.MODELDIR;//"MODELS_UPDATED";//args[0];//"MODELS/l1_modelFiles1_GERP_chr10";
	String szinputbeddir = Constants.INPUTBEDDIR;//"ALLINPUTBEDS";
	String szfeaturelist = Constants.FEATUREFILELIST;//"featurelist_allinputbeds.txt";
	String szoutputdir = Constants.PORTIONSDIR;//PREDICTIONSPORTIONS_UPDATED";
	String szlabel = args[0];
	//String szoutprefix = args[1];//"predicts_PhastCons";

	File dir = new File(szoutputdir);
	if (!dir.exists())
	{
	    if (!dir.mkdirs())
	    {
	        throw new IllegalArgumentException(szoutputdir+" does not exist and could not be created!");
	    }
	}

	String szchromfile = Constants.CHROMSIZES;//"hg19.chrom.sizes";
	String szchrom = args[1];//"chr10";
	int nportion = Integer.parseInt(args[2]);//1;
	int numportions = Constants.NUMPORTIONS;//10;//DEFAULT_NUMPORTIONS;
	int nummodels = Constants.NUMENSEMBLES;//10;

	if ((nportion < 0)||(nportion >= numportions))
	{
	    throw new IllegalArgumentException("Invalid value of nportion "+nportion+" expecting value in [0,"+numportions+"]");
	}

	BufferedReader brchromfile = Util.getBufferedReader(szchromfile);
	String szLine;
	int nchromsize = -1;



	while ((szLine = brchromfile.readLine())!=null)
	{
	    StringTokenizer st = new StringTokenizer(szLine,"\t");
	    String szcurrchrom = st.nextToken();
	    if (szchrom.equals(szcurrchrom))
	    {
		nchromsize = Integer.parseInt(st.nextToken());
		break;
	    }
	}
	brchromfile.close();

	int numfeatures = 0;
	BufferedReader brfeatures = Util.getBufferedReader(szfeaturelist);
	while ((szLine = brfeatures.readLine())!=null)
	{
	    numfeatures++;
	}
	brfeatures.close();

	double[][] weights = new double[nummodels][numfeatures];
	double[] intercepts = new double[nummodels];
	for (int nmodel = 0; nmodel < nummodels; nmodel++)
        {
	    BufferedReader brmodel = Util.getBufferedReader(szmodeldir+"/train_samples_"+szchrom+"_"+nmodel+".gz_"+szlabel+".gz.txt.model.gz");
	    brmodel.readLine();
	    brmodel.readLine();
	    brmodel.readLine();
	    brmodel.readLine();
	    brmodel.readLine();
	    brmodel.readLine();

	    double[] weights_nmodel = weights[nmodel];
	    for (int nfeature = 0; nfeature < numfeatures; nfeature++)
	    {
		weights_nmodel[nfeature] = Double.parseDouble(brmodel.readLine());
	    }
	    intercepts[nmodel] = Double.parseDouble(brmodel.readLine());
	    brmodel.close();
	}

	if (nchromsize == -1)
        {
	    throw new IllegalArgumentException("chromosome size not found for "+szchrom+" in "+szchromfile);
	}

        brfeatures = Util.getBufferedReader(szfeaturelist);

	int nregionsize = nchromsize/numportions;
	int nregionstart = nregionsize*nportion;
	int nregionend = nregionsize*(nportion+1); //using bed style end is exclusive

	if (nportion == numportions-1)
	{
	    nregionend = nchromsize;
	    nregionsize = nregionend-nregionstart;
	}


	double[][] weightsum = new double[nummodels][nregionsize];

	int nfeature = 0;
	while ((szLine = brfeatures.readLine())!=null)
        {
	    boolean[] present = new boolean[nregionsize]; 

	    //System.out.println(szLine+"\t"+nfeature);
	    File f = new File(szLine);
	    if (!f.exists())
	    {
		szLine += ".gz";
	    }
	    BufferedReader brcoords = Util.getBufferedReader(szinputbeddir+"/"+szLine);
	    String szLineCoords;
	    while ((szLineCoords = brcoords.readLine())!=null)
	    {
		StringTokenizer st = new StringTokenizer(szLineCoords,"\t");
		String szcurrchrom = st.nextToken();
		if (szchrom.equals(szcurrchrom))
	        {

		    int nbegin = Integer.parseInt(st.nextToken());
		    int nend = Integer.parseInt(st.nextToken());

		    if (nbegin < nregionstart)
		    {
			nbegin = nregionstart;
		    }
		    if (nend > nregionend)
		    {
			nend = nregionend; //nregion end is inclusive
		    }

		    int npos = nbegin-nregionstart;
		    for (int nk = nbegin; nk < nend; nk++)
		    {
			present[npos] = true;
			npos++;
		    }
		}
	    }
	    brcoords.close();

	    for (int nmodel = 0; nmodel < weights.length; nmodel++)
	    {
		double dweights_nmodel_nfeature = weights[nmodel][nfeature];
		double[] weightsum_nmodel = weightsum[nmodel];
		for (int ni = 0; ni < present.length; ni++)
		{
		   if (present[ni])
		   {
		       weightsum_nmodel[ni] += dweights_nmodel_nfeature;
		   }
		}
	    }

	    nfeature++;
	}
	brfeatures.close();

	GZIPOutputStream pw = new GZIPOutputStream(new FileOutputStream(szoutputdir+"/"+szlabel+"_"+szchrom+"_"+nportion+"_"+numportions+".wig.gz"));
	for (int ni = 0; ni < nregionsize; ni++)
	{
	    double dsum = 0;
	    for (int nmodel = 0; nmodel < weightsum.length; nmodel++)
	    {
		dsum += 1.0/(1+Math.exp(-(weightsum[nmodel][ni]+intercepts[nmodel])));
	    }
	    double dprob = dsum/nummodels;

	    byte[] btformat =(nf.format(dprob)+"\n").getBytes();
	    pw.write(btformat,0,btformat.length);
	}

	pw.finish();
	pw.close();

    }

}