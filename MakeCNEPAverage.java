import java.io.*;
import java.util.*;
import java.util.zip.*;
import java.text.*;

public class MakeCNEPAverage
{

    public static void main(String[] args) throws IOException
    {
	NumberFormat nf = NumberFormat.getInstance();
	nf.setMaximumFractionDigits(3);

	//if (args.length != 3)
	//{
	//    System.out.println("USAGE: MakeCNEPAverage scorefile chrmappingfile outdir");
	//    throw new IllegalArgumentException("Argument length of "+args.length+" does not match expected 3");
	//}

        String szlabelfilelist = "labellist.txt";
	//file contains one line per directory that contains files that should be averaged
	//files in the directory should be named scores_CHRKEY.wig or scores_CHRKEY.wig.gz 
	String szchrom = args[0];
	//file contains one line per directory where each line has a chromosome key 
	//and identifier split by a tab 
	String szinputdir = "COMBINED_UPDATED"; 
	String szoutputdir = "CNEP_UPDATED";//args[2];

        File dir = new File(szoutputdir);
        if (!dir.exists())
        {
	   if (!dir.mkdirs())
           {
              throw new IllegalArgumentException(szoutputdir+" does not exist and could not be created!");
	   }
	}

	ArrayList alscorefiles = new ArrayList();

	String szLine;

	BufferedReader brscorefile = Util.getBufferedReader(szlabelfilelist);
	while ((szLine = brscorefile.readLine())!=null)
	{
	    StringTokenizer st = new StringTokenizer(szLine, "\t");
	    String szdir = st.nextToken();
	    alscorefiles.add(szdir);
	}
	brscorefile.close();

	GZIPOutputStream pw;
	pw = new GZIPOutputStream(new FileOutputStream(szoutputdir+"/cnep_"+szchrom+".wig.gz"));

	ArrayList albr = new ArrayList();

	for (int ni = 0; ni < alscorefiles.size(); ni++)
	{
	   String szlabel = (String) alscorefiles.get(ni);

	   String szfile = szinputdir+"/"+szlabel+"_"+szchrom+".wig";
	   File f = new File(szfile);

	   BufferedReader br = null;
	   if (f.exists())
	   {
              br = Util.getBufferedReader(szfile);
	   }
           else if (!f.exists())
	   {
	      String szfilegz = szfile+".gz";
	      f = new File(szfilegz);
	      if (f.exists())
	      {
                 br =  Util.getBufferedReader(szfilegz);
              }
	      else
	      {
                 throw new IllegalArgumentException(szfile+" and "+szfilegz+" does not exist");
	      }
	   }
           br.readLine();
           br.readLine();
           albr.add(br);
	}
	   
	byte[] btheader1 = "track type=wiggle_0 name=CNEP description='CNEP Score' visibility=2\n".getBytes();
        pw.write(btheader1, 0, btheader1.length);

        byte[] btheader2 = ("fixedStep chrom="+szchrom+" start=1 step=1\n").getBytes();
        pw.write(btheader2, 0, btheader2.length);

	BufferedReader br1 = (BufferedReader) albr.get(0);
	int numbr = albr.size();
	while ((szLine = br1.readLine())!=null)
        {
           //double dval1 = Double.parseDouble(szLine);
	   double dsum = Double.parseDouble(szLine);
	   for (int ni = 1; ni < numbr; ni++)
	   {
	       BufferedReader br = (BufferedReader) albr.get(ni);
	       dsum += Double.parseDouble(br.readLine());
	   }
	   double davg = dsum/numbr;

	   byte[] btformat =(nf.format(davg)+"\n").getBytes();
           pw.write(btformat,0,btformat.length);
	}

        for (int na = 0; na < albr.size(); na++)
        {
           BufferedReader br = (BufferedReader) albr.get(na);
           br.close();
	}

        pw.finish();
        pw.close();
   	
    }

}