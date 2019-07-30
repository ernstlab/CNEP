import java.io.*;
import java.util.*;
import java.util.zip.*;

public class CombineFiles
{

    public static void main(String[] args) throws IOException
    {
	/*
	String szinputdir = args[0];
	String szprefix = args[1];
	int numportions = Integer.parseInt(args[2]);
	String szoutputdir = args[3];
	String szname = args[4];
	String szdescription = args[5];
	*/

	String szinputdir = "PREDICTIONSPORTIONS_UPDATED";
	//String szprefix = args[0];//"predicts";
	int numportions = 10;
	String szoutputdir = "COMBINED_UPDATED";
        String szlabelfilelist = "labellist.txt";
        String szchrom = args[0];//index = "chrorderlist.txt";

	//String szname = "CNEP";
	//String szdescription = "CNEP test";



        File dir = new File(szoutputdir);
        if (!dir.exists())
	{
	   if (!dir.mkdirs())
	   {
	      throw new IllegalArgumentException(szoutputdir+" does not exist and could not be created!");
	   }
	}

	String szLabel;
	BufferedReader brlabels = Util.getBufferedReader(szlabelfilelist);
	while ((szLabel = brlabels.readLine())!=null)
	{	
           GZIPOutputStream pw = new GZIPOutputStream(new FileOutputStream(szoutputdir+"/"+szLabel+"_"+szchrom+".wig.gz"));
	   byte[] btheader1 = ("track type=wiggle_0 name=\""+szLabel+"\""+" description=\""+szLabel+"\" visibility=2\n").getBytes();
	   pw.write(btheader1, 0, btheader1.length);

	   byte[] btheader2 = ("fixedStep chrom="+szchrom+" start=1 step=1\n").getBytes();
	   pw.write(btheader2, 0, btheader2.length);

	   for (int nportion = 0; nportion < numportions; nportion++)
           {
	      BufferedReader br;
	      File f = new File(szinputdir+"/"+szLabel+"_"+szchrom+"_"+nportion+"_"+numportions+".wig.gz");
	      if (f.exists())
	      {
	         br = Util.getBufferedReader(szinputdir+"/"+szLabel+"_"+szchrom+"_"+nportion+"_"+numportions+".wig.gz");
	      }
	      else 
	      {
                 f = new File(szinputdir+"/"+szLabel+"_"+szchrom+"_"+nportion+"_"+numportions+".wig");

	         if (f.exists())
	         {
	      	    br = Util.getBufferedReader(szinputdir+"/"+szLabel+"_"+szchrom+"_"+nportion+"_"+numportions+".wig");
	         }
	         else
		 {
	            throw new IllegalArgumentException("Not found "+szinputdir+"/"+szLabel+"_"+szchrom+"_"+nportion+"_"+numportions+".wig or "+
							   szinputdir+"/"+szLabel+"_"+szchrom+"_"+nportion+"_"+numportions+".wig.gz");
	         }
	      }
	      String szLine;

	      while ((szLine = br.readLine())!= null)
	      {
		  byte[] btformat =(szLine+"\n").getBytes();
		  pw.write(btformat,0,btformat.length);
	      }
	   }	    
	   pw.finish();
	   pw.close();
	}	
    }

}