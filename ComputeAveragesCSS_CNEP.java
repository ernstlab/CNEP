import java.io.*;
import java.util.*;

public class ComputeAveragesCSS_CNEP
{

    public static void main(String[] args) throws IOException
    {

        String szLine;
        int numlabels = 0;
        BufferedReader brlabels = Util.getBufferedReader(Constants.LABELLIST);
        while ((szLine = brlabels.readLine())!=null)
        {
	    numlabels++;
	}
        brlabels.close();

        int numcombos = Constants.NUMCONSHMM;
        for (int na = 1; na <= numlabels; na++)
	{
	    numcombos = 2*numcombos;
	}

	String szchrompredict =args[0];

        HashMap hmchromsizes = new HashMap();
        BufferedReader brchromsizes = Util.getBufferedReader(Constants.CHROMSIZES);
        while ((szLine = brchromsizes.readLine())!=null)
	{
           StringTokenizer st = new StringTokenizer(szLine,"\t");
	   String szchrom = st.nextToken();
	   int nsize = Integer.parseInt(st.nextToken());
           hmchromsizes.put(szchrom,nsize);
	}
        brchromsizes.close();

        File dir = new File(Constants.CSSNCEP_AVERAGEDIR);
        if (!dir.exists())
        {
	   if (!dir.mkdirs())
	   {
	       throw new IllegalArgumentException(Constants.CSSNCEP_AVERAGEDIR+" does not exist and could not be created!");
	   }
	}


	PrintWriter pw = new PrintWriter(Constants.CSSNCEP_AVERAGEDIR+"/average_exclude_"+szchrompredict+".txt");
	double dstatecount = 0;

	double[] hitsum = new double[numcombos];
	double[] hittally  = new double[numcombos];

	double[] hitsumconserved = new double[numcombos];
	double[] hittallyconserved  = new double[numcombos];

        int numchrom = 0;
        BufferedReader brchromfile = Util.getBufferedReader(Constants.CHROMORDERFILE);
        while ((szLine = brchromfile.readLine())!=null)
	{
	    numchrom++;
	}
        brchromfile.close();

        brchromfile = Util.getBufferedReader(Constants.CHROMORDERFILE);
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


	for (nchrom = 0; nchrom < chromnames.length; nchrom++)
	{
	    String szcurrchrom = chromnames[nchrom];
	    if (szcurrchrom.equals(szchrompredict)) continue;
	    System.out.println(szcurrchrom);
	    boolean[][] bconserved = new boolean[numlabels][chromsizes[nchrom]];
	    boolean[] bexon = new boolean[chromsizes[nchrom]];
	    int[] state = new int[chromsizes[nchrom]];

	    BufferedReader brstate = Util.getBufferedReader(Constants.CONSHMM_SEGMENTS);

	    while ((szLine = brstate.readLine())!=null)
	    {
		StringTokenizer st = new StringTokenizer(szLine,"\t");
		String szchrom =st.nextToken();
		if (!szchrom.equals(szcurrchrom)) continue;
		int nbegin = Integer.parseInt(st.nextToken());
		int nend = Integer.parseInt(st.nextToken());

		int nval = Integer.parseInt(st.nextToken().substring(1))-1;
		for (int nk = nbegin; nk < nend; nk++)
	        {
		    state[nk] = nval;
		    dstatecount++;
		}
	    }
	    brstate.close();
	    //System.out.println("state count\t"+dstatecount);


	    BufferedReader br = Util.getBufferedReader(Constants.EXONBEDFILE);//"COORDS/exons_gencode_v19.bed.gz");
	    while ((szLine = br.readLine())!=null)
	    {
	       StringTokenizer st = new StringTokenizer(szLine,"\t");
	       String szchrom = st.nextToken();

	       if (szchrom.equals(szcurrchrom))
	       {
		   int nbegin = Integer.parseInt(st.nextToken());
		   int nend = Integer.parseInt(st.nextToken());

		   for (int nj = nbegin; nj < nend; nj++)
		   {
		       bexon[nj] = true;
		   }
	       }
	    }
	    br.close();

            brlabels = Util.getBufferedReader(Constants.LABELLIST);
	    int nel = 0;
	    String szLabelFile;
	    while ((szLabelFile = brlabels.readLine())!=null)
	    {

	       File f = new File(szLabelFile);
	       if (!f.exists())
	       {
	          szLabelFile += ".gz";
	       }

	       BufferedReader brconserved = Util.getBufferedReader(Constants.LABELBEDDIR+"/"+szLabelFile);
	       boolean[] bconserved_nel = bconserved[nel];

	       while ((szLine = brconserved.readLine())!=null)
	       {
		   StringTokenizer st = new StringTokenizer(szLine);
		   String szchrom = st.nextToken();

		   if (szchrom.equals(szcurrchrom))
		   {
		      int nbegin = Integer.parseInt(st.nextToken());
		      int nend = Integer.parseInt(st.nextToken());

		      for (int nj = nbegin; nj < nend; nj++)
		      {
		         bconserved_nel[nj] = true;
		      }
		   }
	       }
	       brconserved.close();
	       nel++;
	    }
	    brlabels.close();

	    BufferedReader brscore = Util.getBufferedReader(Constants.OUTPUTDIR+"/cnep_"+chromnames[nchrom]+".wig.gz"); //CNEPDIR_2018
	    brscore.readLine();
	    brscore.readLine();
	    int nline = 0;

	    while ((szLine = brscore.readLine())!=null)
	    {
		int nval = (int) (1000*Double.parseDouble(szLine));
		int nconshmmstate = state[nline];
		int nconservedcombo = 0;
		int npow = 1;

		for (int na = 0; na < numlabels; na++)
		{
		   if (bconserved[na][nline])
		   {
		       nconservedcombo += npow;
		   }
		   npow = npow*2;
		}
		int nstate = Constants.NUMCONSHMM*nconservedcombo + nconshmmstate;


	        if (!bexon[nline])
		{
		    hitsum[nstate] += nval;
		    hittally[nstate]++;		          
		}
		    
		nline++;
		    
	    }
	    brscore.close();
	}

	for (int ns = 0; ns < numcombos; ns++)
        {
	    pw.println(ns+"\t"+hitsum[ns]/hittally[ns]+"\t"+hittally[ns]);
	}

	pw.close();
       
    }
}