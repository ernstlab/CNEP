import java.io.*;
import java.util.*;

public class GetOverlapCoord
{
    static class Rec
    {
	String szLabel;
	double dval;

	Rec(String szLabel, double dval)
	{
	    this.szLabel = szLabel;
	    this.dval = dval;
	}

    }

    public static void main(String[] args) throws IOException
    {
	if (args.length != 2)
	{
	    System.out.println("USAGE: java -classpath . GetOverlapCoord chrom position");
	    return;
	}

	String szchrom = args[0];
	int npos = Integer.parseInt(args[1])-1;

	String szLine;
	String szfeatureLine;
	BufferedReader brfeatures = Util.getBufferedReader(Constants.EXPECTCNEPFILE);
	//int numcount =
	int nfound = 0;
	int ntry = 0;
	System.out.println("rank_hits\tfeature\tfeature_conservation_non-exon\tfeature_conservation_non-exon_rank");
	while ((szfeatureLine = brfeatures.readLine())!=null)
	{
	    StringTokenizer st = new StringTokenizer(szfeatureLine,"\t");
	    String szfeature = st.nextToken();
	    String szfile = Constants.INPUTBEDDIR+"/"+szfeature;
            File f = new File(szfile);
            if (!f.exists())
	    {
	       szfile +=".gz";
	    }

	    BufferedReader brcoords = Util.getBufferedReader(szfile);

	    while ((szLine = brcoords.readLine())!=null)
	    {
		st = new StringTokenizer(szLine,"\t");
		String szcurrchrom = st.nextToken();

	        if (szcurrchrom.equals(szchrom))
	        {
		    int nbegin = Integer.parseInt(st.nextToken());
		    int nend =  Integer.parseInt(st.nextToken());

		    if ((npos >= nbegin)&&(npos < nend))
		    {
			System.out.println((nfound+1)+"\t"+szfeatureLine+"\t"+ntry);
			nfound++;
			break;			
		    }
		}
	    }
	    brcoords.close();
	    ntry++;
	}
	brfeatures.close();
    }
}