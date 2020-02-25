import java.io.*;
import java.util.*;
import java.util.zip.*;
import java.text.*;

public class MakeCNEPAvg
{
    //[ernst@n2190 OLIVERA]$ ls ../../ogrujic/wigFiles_l1_modelFiles1_Pi/
    //countLines.sh      scores_11_OLD.wig  scores_13.wig  scores_16.wig 
    public static void main(String[] args) throws IOException
    {


	NumberFormat nf = NumberFormat.getInstance();
	nf.setMaximumFractionDigits(3);
	//nf.setMinimumFractionDigits(3);

	//	for (int nchrom = 1; nchrom <= 23; nchrom++)
	for (int nchrom = 1; nchrom <= 23; nchrom++)
	{
	    System.out.println(nchrom);
	    //wigFiles_l1_modelFiles1_GERP/      wigFiles_l1_modelFiles1_Omega/     wigFiles_l1_modelFiles1_Phastcons/ wigFiles_l1_modelFiles1_Pi/
	   GZIPOutputStream pw;
           pw = new GZIPOutputStream(new FileOutputStream("CNEPAVG/cnep_chr"+nchrom+".wig.gz"));

	   BufferedReader br1 = Util.getBufferedReader("../../ogrujic/wigFiles_l1_modelFiles1_Pi/scores_"+nchrom+".wig");
	   BufferedReader br2 = Util.getBufferedReader("../../ogrujic/wigFiles_l1_modelFiles1_Phastcons/scores_"+nchrom+".wig");
	   BufferedReader br3 = Util.getBufferedReader("../../ogrujic/wigFiles_l1_modelFiles1_Omega/scores_"+nchrom+".wig");
	   BufferedReader br4 = Util.getBufferedReader("../../ogrujic/wigFiles_l1_modelFiles1_GERP/scores_"+nchrom+".wig");
	   String szLine;

	   br1.readLine();
	   br1.readLine();

	   br2.readLine();
	   br2.readLine();

	   br3.readLine();
	   br3.readLine();

	   br4.readLine();
	   br4.readLine();

	//track type=wiggle_0 name=BED description='Stacking Scores' visibility=2
	//fixedStep chrom=18 start=1 step=1

	   byte[] btheader1 = "track type=wiggle_0 name=CNEP description='CNEP Score' visibility=2\n".getBytes();
	   pw.write(btheader1, 0, btheader1.length);

	   byte[] btheader2;
	   if (nchrom == 23)
	   {
	       btheader2 = "fixedStep chrom=chrX start=1 step=1\n".getBytes();
	   }
	   else
	   {
	       btheader2 = ("fixedStep chrom=chr"+nchrom+" start=1 step=1\n").getBytes();
	   }
	   pw.write(btheader2, 0, btheader2.length);

	   while ((szLine = br1.readLine())!=null)
	   {
	       double dval1 = Double.parseDouble(szLine);
	       double dval2 = Double.parseDouble(br2.readLine());
               double dval3 = Double.parseDouble(br3.readLine());
               double dval4 = Double.parseDouble(br4.readLine());

	       double davg = (dval1+dval2+dval3+dval4)/4.0;

	       byte[] btformat =(nf.format(davg)+"\n").getBytes();
	       pw.write(btformat,0,btformat.length);
	   }
	   br1.close();
	   br2.close();
	   br3.close();
	   br4.close();
	   pw.finish();
	   pw.close();
	}

    }

}