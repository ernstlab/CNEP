import java.io.*;
import java.util.*;
import java.util.zip.*;
import java.text.*;

public class MakeCSS_CNEPPredict
{

    public static void main(String[] args) throws IOException
    {

        NumberFormat nf = NumberFormat.getInstance();
        nf.setMaximumFractionDigits(3);
        nf.setGroupingUsed(false);
        nf.setMinimumFractionDigits(3);

        File dir = new File(Constants.CSSCNEP_OUTPUTDIR);
        if (!dir.exists())
	{
	    if (!dir.mkdirs())
            {
	       throw new IllegalArgumentException(Constants.CSSNCEP_AVERAGEDIR+" does not exist and could not be created!");
	    }
	}


	String szcurrchrom = args[0]; //should include chr prefix
	String szLine;

	int nchromsize = -1;
        BufferedReader brchromsizes = Util.getBufferedReader(Constants.CHROMSIZES);
        while ((szLine = brchromsizes.readLine())!=null)
	{
	   StringTokenizer st = new StringTokenizer(szLine,"\t");
	   String szchrom = st.nextToken();
	   if (szchrom.equals(szcurrchrom))
	   {
	      nchromsize = Integer.parseInt(st.nextToken());
	      break;
	   }
	}
        brchromsizes.close();

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

	double dstatecount = 0;

	double[] mapping = new double[numcombos];
	BufferedReader brmapping = Util.getBufferedReader(Constants.CSSNCEP_AVERAGEDIR+"/average_exclude_"+szcurrchrom+".txt");

	while ((szLine = brmapping.readLine())!=null)
	{
	    StringTokenizer st = new StringTokenizer(szLine,"\t");
	    int ncombo = Integer.parseInt(st.nextToken());
	    String szval = st.nextToken();
	    double dcount = Double.parseDouble(st.nextToken());
	    if (dcount > 0)
	    {
	       mapping[ncombo] = Double.parseDouble(szval)/1000;
	    }
	    //mapping[Integer.parseInt(st.nextToken())] = Double.parseDouble(st.nextToken())/1000;
	}
	brmapping.close();



        boolean[][] bconserved = new boolean[numlabels][nchromsize];

        String[] szlabelsA = new String[numlabels];

        int nel = 0;
        brlabels = Util.getBufferedReader(Constants.LABELLIST);
	String szLabelFile;
        while ((szLabelFile = brlabels.readLine())!=null)
	{
	   File f = new File(szLabelFile);
	   if (!f.exists())
           {
	      szLabelFile += ".gz";
	   }


	   BufferedReader brconserved = Util.getBufferedReader(Constants.LABELBEDDIR+"/"+//+"COORDS/"+
                                                                 szLabelFile);
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


	GZIPOutputStream pw = new GZIPOutputStream(new FileOutputStream(Constants.CSSCNEP_OUTPUTDIR+"/csscnep_"+szcurrchrom+".wig.gz"));
	                                                    //"CONSHMMCOMBO_AVERAGECNEP/conshmmcombo_avgcnep_"+szcurrchrom+".wig.gz"));

	int[] state = new int[nchromsize];

	BufferedReader brstate = Util.getBufferedReader(Constants.CONSHMM_SEGMENTS);
	//	  "CONSHMM/ernst.cass.idre.ucla.edu/public/ConsHMM/Segmentation/"+szcurrchrom+"/"+szcurrchrom+"_segmentation.bed.gz");

	int nmaxchrom = -1;
	while ((szLine = brstate.readLine())!=null)
	{
	    StringTokenizer st = new StringTokenizer(szLine,"\t");
	    String szchrom = st.nextToken();
	    if (!szchrom.equals(szcurrchrom)) continue;
	    int nbegin = Integer.parseInt(st.nextToken());
	    int nend = Integer.parseInt(st.nextToken());

	    int nval = Integer.parseInt(st.nextToken().substring(1))-1;
	    for (int nk = nbegin; nk < nend; nk++)
	    {
		state[nk] = nval;
	    }

	    if (nmaxchrom < nend)
	    {
		nmaxchrom = nend;
	    }
	}
        brstate.close();

	byte[] btheader1 = ("track type=wiggle_0 name=\"css_cnep\" description=\"css_cnep\" visibility=2\n").getBytes();
	pw.write(btheader1, 0, btheader1.length);
	byte[] btheader2 = ("fixedStep chrom="+szcurrchrom+" start=1 step=1\n").getBytes();
	pw.write(btheader2, 0, btheader2.length);

	for (int na = 0; na < nmaxchrom; na++)
	{
	    int nconshmmstate = state[na];
	    int nconservedcombo = 0;
	    int npow = 1;

            for (int nb = 0; nb < numlabels; nb++)
	    {
	       if (bconserved[nb][na])
	       {
		   nconservedcombo += npow;
	       }
	       npow = npow*2;
	    }
            int nstate = Constants.NUMCONSHMM*nconservedcombo + nconshmmstate;

	    byte[] btformat =(nf.format(mapping[nstate])+"\n").getBytes();
	    pw.write(btformat,0,btformat.length);
	}
	pw.finish();
	pw.close();	    
    }

}