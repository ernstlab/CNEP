import java.io.*;
import java.util.*;
import java.util.zip.*;

public class MakeTrainFiles
{


    public static void main(String[] args) throws IOException
    {

	String szsamplesdir = Constants.SAMPLEDIR;//"SAMPLING_UPDATED/";
	String szsamplefiles = args[0];//"sampleTrainingPositions_5m.txt.gz";
        String szinputbeddir;
        String szfeaturelist;
        String szoutputdir;

	if (args.length == 4)
	{
	   szinputbeddir = args[1];//Constants.INPUTBEDDIR;//"ALLINPUTBEDS";
	   szfeaturelist = args[2];//Constants.FEATUREFILELIST;//"featurelist_allinputbeds.txt";
	   szoutputdir = args[3];//Constants.TRAINDIR;//"TRAINDIR_UPDATED";
	}
	else if (args.length == 1)
	{
           szinputbeddir = Constants.INPUTBEDDIR;//"ALLINPUTBEDS";
           szfeaturelist = Constants.FEATUREFILELIST;//"featurelist_allinputbeds.txt";
           szoutputdir = Constants.TRAINDIR;//"TRAINDIR_UPDATED";
	}
	else
        {
	   throw new IllegalArgumentException("expecting either 1 or 4 parameters to MakeTrainFiles received "+args.length+" parameters");
	}

	String szlabelfiledir = Constants.LABELBEDDIR;//"COORDS";
	String szlabelfilelist = Constants.LABELLIST;//"labellist.txt";
	String szexonfile = Constants.EXONBEDFILE;//"COORDS/exons_gencode_v19.bed.gz";
        String szchromindex = Constants.CHROMORDERFILE;//"chrorderlist.txt";



        File dir = new File(szoutputdir);
        if (!dir.exists())
        {
	   if (!dir.mkdirs())
	   {
	      throw new IllegalArgumentException(szoutputdir+" does not exist and could not be created!");
	   }
	}


	String szLine;
        HashMap hmChromToIndex = new HashMap();
        BufferedReader brchromfile = Util.getBufferedReader(szchromindex);

	int numchrom = 0;
        while ((szLine = brchromfile.readLine())!=null)
	{
	   hmChromToIndex.put(szLine, new Integer(numchrom));
	   numchrom++;
        }
	brchromfile.close();


	int[] count = new int[numchrom];
	int[] indexA = new int[numchrom];
	int[] offsets = new int[numchrom];
	int[][] positionsA = new int[numchrom][];
	String[] chromA = new String[numchrom];

	int nchromindex = 0;
        brchromfile = Util.getBufferedReader(szchromindex);
        while ((szLine = brchromfile.readLine())!=null)
	{
	    chromA[nchromindex] = szLine;
	    nchromindex++;
	}
        brchromfile.close();




	int numsamples = 0;
	BufferedReader brsamples = Util.getBufferedReader(szsamplesdir+"/"+szsamplefiles);
	while ((szLine = brsamples.readLine())!=null)
	{
	    StringTokenizer st = new StringTokenizer(szLine, " ,\t");
	    int nchrom = Integer.parseInt(st.nextToken())-1;
	    count[nchrom]++;
	    numsamples++;
	}
	brsamples.close();

	for (int na = 0; na < positionsA.length; na++)
        {
	    positionsA[na] = new int[count[na]];
	}

	for (int na = 1; na < offsets.length; na++)
	{
	    offsets[na] = offsets[na-1] + count[na-1];
	}



	brsamples = Util.getBufferedReader(szsamplesdir+"/"+szsamplefiles);
	while ((szLine = brsamples.readLine())!=null)
	{
	    StringTokenizer st = new StringTokenizer(szLine, " ,\t");
	    int nchrom = Integer.parseInt(st.nextToken())-1;
	    positionsA[nchrom][indexA[nchrom]] = Integer.parseInt(st.nextToken());
	    indexA[nchrom]++;
	    //hmcount
	}
	brsamples.close();

	for (int na = 0; na < positionsA.length; na++)
	{
	    Arrays.sort(positionsA[na]);
	}

	int numlabels = 0;
        BufferedReader brlabels = Util.getBufferedReader(szlabelfilelist);
	while ((szLine = brlabels.readLine())!=null)
        {
	    numlabels++;
	}
	brlabels.close();

	String[] szlabelsA = new String[numlabels];


	boolean[][] blabelsA = new boolean[numsamples][numlabels];
	int nlabelindex = 0;
        brlabels = Util.getBufferedReader(szlabelfilelist);
	while ((szLine = brlabels.readLine())!=null)
	{
            File f = new File(szLine);
            if (!f.exists())
	    {
		szLine += ".gz";
	    }

	    szlabelsA[nlabelindex] = szLine;
            BufferedReader brlabelscoords = Util.getBufferedReader(szlabelfiledir+"/"+szLine);
	    String szLineLabel;
            String szprevchrom = "";
            int[] positions_nchrom = null;
            int noffset = 0;

            while ((szLineLabel = brlabelscoords.readLine())!=null)
	    {
                StringTokenizer st = new StringTokenizer(szLineLabel,"\t");
                String szcurrchrom = st.nextToken();
		int nstart = Integer.parseInt(st.nextToken());
		int nend = Integer.parseInt(st.nextToken());

		if (!szcurrchrom.equals(szprevchrom))
		{
		   Integer objIndex = (Integer) hmChromToIndex.get(szcurrchrom);
		   if (objIndex == null)
		   {
		       continue; //we don't handle this chromosome
		   }
		   int ncurrchromindex = objIndex.intValue();
		   positions_nchrom = (int[]) positionsA[ncurrchromindex];
		   noffset = offsets[ncurrchromindex];
		}

		int nfirstindex = Arrays.binarySearch(positions_nchrom,nstart);
		if (nfirstindex < 0)
		{
		    nfirstindex = -nfirstindex - 1;
		}
		else
		{
		    //get first occurence of start
		    while ((nfirstindex >0)&&(positions_nchrom[nfirstindex] ==positions_nchrom[nfirstindex-1]))
		    {
			nfirstindex--;
		    }
		}
		for (int na = nfirstindex; na < positions_nchrom.length; na++)
	        {
		   int npositions_nchrom_na = positions_nchrom[na];
		   if (npositions_nchrom_na >= nend)
		   {
		       break;
		   }
		   else if (nstart <= npositions_nchrom_na)// && (positions_nchrom_na < nend))
		   {
	               blabelsA[noffset+na][nlabelindex] = true;
		   }
	        }

		szprevchrom = szcurrchrom;
	    }
	    brlabelscoords.close();
	    nlabelindex++;
	}
	brlabels.close();

	int numfeatures = 0;
        BufferedReader brfeatures = Util.getBufferedReader(szfeaturelist);
	while ((szLine = brfeatures.readLine())!=null)
        {
	    numfeatures++;
	}
	brfeatures.close();
	boolean[][] presentA = new boolean[numsamples][numfeatures];


	//going through all features to compute presentA matrix 
	int nfeature = 0;
        brfeatures = Util.getBufferedReader(szfeaturelist);
	while ((szLine = brfeatures.readLine())!=null)
	{
            File f = new File(szLine);
            if (!f.exists())
	    {
		szLine += ".gz";
	    }

            BufferedReader brcoords = Util.getBufferedReader(szinputbeddir+"/"+szLine);
            String szLineCoords;
	    String szprevchrom = "";
	    int[] positions_nchrom = null;
	    int noffset = 0;

            while ((szLineCoords = brcoords.readLine())!=null)
	    {
                StringTokenizer st = new StringTokenizer(szLineCoords,"\t");
                String szcurrchrom = st.nextToken();
		int nstart = Integer.parseInt(st.nextToken());
		int nend = Integer.parseInt(st.nextToken());

		if (!szcurrchrom.equals(szprevchrom))
		{
		   Integer objIndex = (Integer) hmChromToIndex.get(szcurrchrom);
		   if (objIndex == null)
		   {
		       continue; //we don't handle this chromosome
		   }
		   int ncurrchromindex = objIndex.intValue();
		   positions_nchrom = (int[]) positionsA[ncurrchromindex];
		   noffset = offsets[ncurrchromindex];
		}

		int nfirstindex = Arrays.binarySearch(positions_nchrom,nstart);
		if (nfirstindex < 0)
		{
		    nfirstindex = -nfirstindex - 1;
		}
		else
		{
		    //get first occurence of start
		    while ((nfirstindex >0)&&(positions_nchrom[nfirstindex] ==positions_nchrom[nfirstindex-1]))
		    {
			nfirstindex--;
		    }
		}

		for (int na = nfirstindex; na < positions_nchrom.length; na++)
	        {
		   int npositions_nchrom_na = positions_nchrom[na];
		   if (npositions_nchrom_na >= nend)
		   {
		       break;
		   }
		   else if (nstart <= npositions_nchrom_na)// && (positions_nchrom_na < nend))
		   {
	               presentA[noffset+na][nfeature] = true;
		   }
	        }

		szprevchrom = szcurrchrom;
	    }
	    brcoords.close();

	    nfeature++;
	}


	boolean[] bexonsA = new boolean[numsamples];

	String szLineExon;
        String szprevchrom = "";
        int[] positions_nchrom = null;
        int noffset = 0;

        BufferedReader brexons = Util.getBufferedReader(szexonfile);
        while ((szLineExon = brexons.readLine())!=null)
	{
	    StringTokenizer st = new StringTokenizer(szLineExon,"\t");
	    String szcurrchrom = st.nextToken();
	    int nstart = Integer.parseInt(st.nextToken());
	    int nend = Integer.parseInt(st.nextToken());

	    if (!szcurrchrom.equals(szprevchrom))
	    {
	       Integer objIndex = (Integer) hmChromToIndex.get(szcurrchrom);
	       if (objIndex == null)
	       {
	          continue; //we don't handle this chromosome
	       }
	       int ncurrchromindex = objIndex.intValue();
	       positions_nchrom = (int[]) positionsA[ncurrchromindex];
	       noffset = offsets[ncurrchromindex];
	    }

	    int nfirstindex = Arrays.binarySearch(positions_nchrom,nstart);
	    if (nfirstindex < 0)
	    {
	       nfirstindex = -nfirstindex - 1;
	    }
	    else
	    {
	       //get first occurence of start
	       while ((nfirstindex >0)&&(positions_nchrom[nfirstindex] ==positions_nchrom[nfirstindex-1]))
	       {
	          nfirstindex--;
	       }
	    }

	    for (int na = nfirstindex; na < positions_nchrom.length; na++)
	    {
	       int npositions_nchrom_na = positions_nchrom[na];
	       if (npositions_nchrom_na >= nend)
	       {
	          break;
	       }
	       else if (nstart <= npositions_nchrom_na)// && (positions_nchrom_na < nend))
	       {
                  bexonsA[noffset+na] = true;
	       }
	    }
	    szprevchrom = szcurrchrom;
	}
        brexons.close();





	
	//outputs zip file for liblinear
	GZIPOutputStream[] pwA = new GZIPOutputStream[szlabelsA.length];
	for (int ni = 0; ni < pwA.length; ni++)
	{
	    pwA[ni] = new GZIPOutputStream(new FileOutputStream(szoutputdir+"/train_"+szsamplefiles+"_"+szlabelsA[ni]+".txt.gz"));
	}

	for (int nsample = 0; nsample < presentA.length; nsample++)
	{
	    boolean[] presentA_nsample = presentA[nsample];
	    boolean[] blabelsA_nsample = blabelsA[nsample];
	    boolean bexons_nsample = bexonsA[nsample];

	    StringBuffer sbfeatures = new StringBuffer();
	    for (nfeature = 0; nfeature < presentA_nsample.length; nfeature++)
	    {
		if (presentA_nsample[nfeature])
		{
		    sbfeatures.append(" "+(nfeature+1)+":1");
		}
	    }
	    for (int nlabel = 0; nlabel < szlabelsA.length; nlabel++)
	    {
		StringBuffer sbfull = new StringBuffer();
		if (blabelsA_nsample[nlabel]&&(!bexons_nsample))
		{
		    sbfull.append("1");
		}
		else
		{
		    sbfull.append("-1");
		}

		sbfull.append(sbfeatures);

		byte[] btformat =(sbfull.toString()+"\n").getBytes();
		pwA[nlabel].write(btformat,0,btformat.length);
	    }
	}

	for (int ni = 0; ni < pwA.length; ni++)
	{
	    pwA[ni].finish();
	    pwA[ni].close();
	}
	

    }

}