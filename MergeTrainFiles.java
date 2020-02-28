import java.io.*;
import java.util.*;
import java.util.zip.*;

public class MergeTrainFiles
{

    public static void main(String[] args) throws IOException
    {

	//String szprefixchrom = "train_samples_"+args[0];
	//int nbatch = Integer.parseInt(args[1]);
	//String szelset = args[2];
        //String szelset = "gz_"+args[2]+".gz.txt";
	String sztrainfile = args[0];
	String szfeaturelistdir = args[1];
	String szoutputdir = args[2];

        File dir = new File(szoutputdir);
        if (!dir.exists())
	{
	   if (!dir.mkdirs())
	   {
	       throw new IllegalArgumentException(szoutputdir+" does not exist and could not be created!");
	   }
	}


	String szLine;
	BufferedReader brfeaturefile = Util.getBufferedReader(szfeaturelistdir);
	int nfeatureline = 0;
	while ((szLine = brfeaturefile.readLine())!=null)
	{
	    if (!szLine.trim().equals(""))
	    {
	       nfeatureline++;
	    }
	}
	brfeaturefile.close();
	String[] traindir = new String[nfeatureline];
	String[] featurefiles = new String[nfeatureline];

	brfeaturefile = Util.getBufferedReader(szfeaturelistdir);
	nfeatureline = 0;
	while ((szLine = brfeaturefile.readLine())!=null)
	{
	    if (!szLine.trim().equals(""))
	    {
		StringTokenizer st = new StringTokenizer(szLine,"\t");
		traindir[nfeatureline] = st.nextToken();
		featurefiles[nfeatureline] = st.nextToken();
		nfeatureline++;
	    }
	}
	brfeaturefile.close();


	BufferedReader[] brA = new BufferedReader[traindir.length];
	for (int ndir = 0; ndir < brA.length; ndir++)
	{
	    brA[ndir] = Util.getBufferedReader(traindir[ndir]+"/"+sztrainfile);//szprefixchrom+"_"+nbatch+"."+szelset+".gz");
	}

	//String szLine;
	int[] offsetA = new int[featurefiles.length];
        for (int ndir = 0; ndir < featurefiles.length-1; ndir++)
	{
	    int nlinecount = 0;
            BufferedReader brfeature = Util.getBufferedReader(featurefiles[ndir]);
	    while ((szLine = brfeature.readLine())!=null)
	    {
		nlinecount++;
	    }
	    offsetA[ndir+1] = nlinecount+offsetA[ndir];
	    brfeature.close();
	}

	GZIPOutputStream pw = new GZIPOutputStream(new FileOutputStream(szoutputdir+"/"+sztrainfile));//szprefixchrom+"_"+nbatch+"."+szelset+".gz"));

	int noffset = 0;
	while ((szLine = brA[0].readLine())!=null)
	{
	    StringBuffer sb = new StringBuffer(szLine);
	    for (int nfile = 1; nfile < brA.length; nfile++)
	    {
		szLine = brA[nfile].readLine();
		StringTokenizer st = new StringTokenizer(szLine," ");
		st.nextToken(); //skip label
		while (st.hasMoreTokens())
		{
		    StringTokenizer stcolon = new StringTokenizer(st.nextToken(),":");
		    sb.append(" "+(Integer.parseInt(stcolon.nextToken())+offsetA[nfile])+":1");
		}
	    }
		
            byte[] btformat =(sb.toString()+"\n").getBytes();
	    pw.write(btformat,0,btformat.length);
	    
	}
        pw.finish();
	pw.close();

	for (int ndir = 0; ndir < brA.length; ndir++)
	{
	    brA[ndir].close();
	}

    }

}