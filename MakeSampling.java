import java.io.*;
import java.util.*;
import java.util.zip.*;

public class MakeSampling
{

    public static void main(String[] args) throws IOException
    {

	int numbatches = Constants.NUMENSEMBLES; //10
	int numsamples = Constants.NUMSAMPLES; //1000000
	String szchromindex = Constants.CHROMORDERFILE;//"chrorderlist.txt";
	String szchromsizes = Constants.CHROMSIZES;// "hg19.chrom.sizes";
	String szoutputdir = Constants.SAMPLEDIR;//args[1];

        File dir = new File(szoutputdir);
        if (!dir.exists())
	{
	   if (!dir.mkdirs())
           {
	      throw new IllegalArgumentException(szoutputdir+" does not exist and could not be created!");
	   }
	}


	/*
	int nbatch = Integer.parseInt(args[0]);
	int numsamples = Integer.parseInt(args[1]);
	String szchromindex = args[2];//"chrorderlist.txt"; //only chromosomes including in analysis ok to include szchrompredict;
	String szchrompredict = args[3];// " ";
	String szchromsizes = args[4];//" ";
	String szoutfile = args[5];// " ";
	*/

	String szLine;
	HashMap hmchromsizes = new HashMap();
	BufferedReader brchromsizes = Util.getBufferedReader(szchromsizes);
        while ((szLine = brchromsizes.readLine())!=null)
	{
	   StringTokenizer st = new StringTokenizer(szLine,"\t");
	    String szchrom = st.nextToken();
	    int nsize = Integer.parseInt(st.nextToken());
	    hmchromsizes.put(szchrom,nsize);
	}	
        brchromsizes.close();


	int numchrom = 0;
        BufferedReader brchromfile = Util.getBufferedReader(szchromindex);
	while ((szLine = brchromfile.readLine())!=null)
	{
	    numchrom++;
	}
	brchromfile.close();

        brchromfile = Util.getBufferedReader(szchromindex);
	int nchrom = 0;
	int[] chromsizes = new int[numchrom];
	String[] chromnames = new String[numchrom];
        while ((szLine = brchromfile.readLine())!=null)
	{
	    chromsizes[nchrom] = ((Integer) hmchromsizes.get(szLine)).intValue();
	    chromnames[nchrom] = szLine;
	    nchrom++;
	}
	brchromfile.close();


	for (int nbatch = 0; nbatch < numbatches; nbatch++)
	{
	    for (int nexcludechrom = 0; nexcludechrom < numchrom; nexcludechrom++)
	    {
		Random theRandom = new Random(435+nbatch);

		int nselected = 0;
		double[] cumulprob = new double[numchrom];
		double dtotsum = 0;
	        for (int na = 0; na < cumulprob.length; na++)
 	        {
	           cumulprob[na] = chromsizes[na];
	           dtotsum += chromsizes[na];
		}

	        cumulprob[0] = cumulprob[0]/dtotsum;
	        for (int na = 1; na < cumulprob.length; na++)
	        {
		    cumulprob[na] = cumulprob[na-1]+cumulprob[na]/dtotsum;
		}

		GZIPOutputStream pw = new GZIPOutputStream(new FileOutputStream(szoutputdir+"/samples_"+chromnames[nexcludechrom]+"_"+nbatch+".gz"));
	        while (nselected < numsamples)
	        {
		    double drandomval = theRandom.nextDouble();
		    int nselectchrom = 0;
	            while (drandomval > cumulprob[nselectchrom])
	            {
			nselectchrom++;
		    }

	            if (nselectchrom != nexcludechrom)
	            {
			nselected++;
			int npos = theRandom.nextInt(chromsizes[nselectchrom]);
			String szOutLine = (nselectchrom+1)+" "+npos+"\n";

			byte[] btformat =(szOutLine).getBytes();
			pw.write(btformat,0,btformat.length);
		    }
		}
		pw.finish();
		pw.close();
	    }
	}




    }

}