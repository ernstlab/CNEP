import java.util.*;
import java.io.*;

public class MakeFeatureConservationList
{
   static class Rec
   {
       double dcountintersect;
       double dcountall;
       double dfreq;
       String szfeature;
   }

   static class RecCompare implements Comparator
   {
      public int compare(Object o1, Object o2)
      {
	  Rec r1 = (Rec) o1;
	  Rec r2 = (Rec) o2;

	  if (r1.dfreq > r2.dfreq)
	  {
	     return -1;
	  }
	  else if (r1.dfreq < r2.dfreq)
	  {
	      return 1;
	  }
	  else
	  {
	      return (r1.szfeature.compareTo(r2.szfeature));
	  }
      }
    }


    public static void main(String[] args) throws IOException
    {
	HashMap hmsize = new HashMap();
	String szLineSize;

	PrintWriter pw = new PrintWriter(new FileWriter(Constants.EXPECTCNEPFILE));

	BufferedReader brsize = Util.getBufferedReader(Constants.CHROMSIZES);
	while ((szLineSize = brsize.readLine())!=null)
	{
	    StringTokenizer st = new StringTokenizer(szLineSize,"\t");
	    String szchrom =st.nextToken();
	    int nlength = Integer.parseInt(st.nextToken());
	    hmsize.put(szchrom, new Integer(nlength));
	}
	brsize.close();


	int numchrom =0;
	HashMap hmchrom = new HashMap();
	BufferedReader brchrom = Util.getBufferedReader(Constants.CHROMORDERFILE);
	String szLineChrom;
	while ((szLineChrom = brchrom.readLine())!=null)
	{
	    hmchrom.put(szLineChrom, new Integer(numchrom));
	    numchrom++;
	}
	brchrom.close();


	// more labellist.txt
	//LABELBEDDIR
	ArrayList allabels = new ArrayList();
	BufferedReader brlabel = Util.getBufferedReader(Constants.LABELLIST);
	String szLineTrain;
	while ((szLineTrain = brlabel.readLine())!=null)
	{
	    allabels.add(szLineTrain);
	}
	brlabel.close();

	boolean[][][] bconserved = new boolean[numchrom][allabels.size()][];
	boolean[][] bexon = new boolean[numchrom][];
	int nchrom =0;
	brchrom = Util.getBufferedReader(Constants.CHROMORDERFILE);

	while ((szLineChrom = brchrom.readLine())!=null)
	{
	    for (int na =0; na < bconserved[0].length; na++)
	    {
	       int nsize = ((Integer) hmsize.get(szLineChrom)).intValue();
	       bconserved[nchrom][na] = new boolean[nsize];
	       bexon[nchrom] = new boolean[nsize];
	    }
	    nchrom++;
	}
	brchrom.close();



        BufferedReader brexon = Util.getBufferedReader(Constants.EXONBEDFILE);
	String szLineExon;
	while ((szLineExon = brexon.readLine())!=null)
	{
	    StringTokenizer st = new StringTokenizer(szLineExon,"\t");
	    String szchrom = st.nextToken();
	    Object obj =  hmchrom.get(szchrom);
	    if (obj != null)
	    {
	       int nchromindex = ((Integer) obj).intValue();
	       int nbegin = Integer.parseInt(st.nextToken());
	       int nend = Integer.parseInt(st.nextToken());
	       boolean[] bexon_nchromindex = bexon[nchromindex];
	       for (int npos = nbegin; npos < nend; npos++)
	       {
	          bexon_nchromindex[npos] = true;
		    //for (int naa
	       }
	    }
	}
	brchrom.close();




	for (int na =0; na < allabels.size(); na++)
	{
	    String szLineConserved;
	    //boolean[][] bconserved;//_na = bconserved[na];
	    String szfile = Constants.LABELBEDDIR+"/"+((String)allabels.get(na));
	    File f = new File(szfile);
	    if (!f.exists())
	    {
		szfile +=".gz";
	    }
	    BufferedReader brconserved = Util.getBufferedReader(szfile);
	    while ((szLineConserved = brconserved.readLine())!=null)
	    {
		StringTokenizer st = new StringTokenizer(szLineConserved,"\t");
		String szchrom = st.nextToken();
		Object obj =  hmchrom.get(szchrom);
		if (obj != null)
		{
		    int nchromindex = ((Integer) obj).intValue();
		    boolean[] bconserved_nchromindex_na = bconserved[nchromindex][na];
		    boolean[] bexon_nchromindex = bexon[nchromindex];
		    int nbegin = Integer.parseInt(st.nextToken());
		    int nend = Integer.parseInt(st.nextToken());

		    for (int npos = nbegin; npos < nend; npos++)
		    {
			if (!bexon_nchromindex[npos])
			{
			   bconserved_nchromindex_na[npos] = true; 
			}
		    }
		    //for (int naa
		}
	    }
	    brconserved.close();
	}


	ArrayList alfeatures = new ArrayList();
        BufferedReader brfeaturefile = Util.getBufferedReader(Constants.TRAINDIRFEATURES);//szfeaturelistdir);
	String szLineDir;
        while ((szLineDir = brfeaturefile.readLine())!=null)
	{
	   if (!szLineDir.trim().equals(""))
	   {
	       StringTokenizer st = new StringTokenizer(szLineDir,"\t");
	       st.nextToken();
	       String szinfile = st.nextToken();
	       String szindir =st.nextToken();;
	       String szFeatureLine;
	       BufferedReader br = Util.getBufferedReader(szinfile);
	       while ((szFeatureLine = br.readLine())!=null)
	       {
	          alfeatures.add(szindir+"/"+szFeatureLine);
	       }
	       br.close();
	   }
	}
        brfeaturefile.close();

	int numfeatures = alfeatures.size();


	Rec[] theRecA = new Rec[numfeatures];

	for (int nfeature = 0; nfeature < theRecA.length; nfeature++)
	{
	    theRecA[nfeature] = new Rec();
	    theRecA[nfeature].szfeature = (String) alfeatures.get(nfeature);
	}




	for (int nfeature = 0; nfeature < theRecA.length; nfeature++)
	{
	   double dcountintersect = 0;
	   double dcountall = 0;
	   String szfile = theRecA[nfeature].szfeature;
	    File f = new File(szfile);
	    if (!f.exists())
	    {
		szfile +=".gz";
	    }
	    BufferedReader brcoords = Util.getBufferedReader(szfile);

	   Rec theRecA_nfeature = theRecA[nfeature];
	   String szLineCoord;


	   boolean[][] bseen = new boolean[numchrom][];//[250000000];
	   for (int nj = 0; nj < bconserved.length; nj++)
	   {
	       bseen[nj] = new boolean[bconserved[nj][0].length];
	   }
	   while ((szLineCoord = brcoords.readLine())!=null)
	   {
	      StringTokenizer st = new StringTokenizer(szLineCoord,"\t");
	      String szchrom = st.nextToken();

	      Object obj =  hmchrom.get(szchrom);
	      if (obj != null)
	      {		
		  int nchromindex = ((Integer) obj).intValue();
		  boolean[] bseen_nchromindex = bseen[nchromindex];
                  boolean[][] bconserved_nchromindex = bconserved[nchromindex];

		  int nbegin = Integer.parseInt(st.nextToken());
		  int nend = Integer.parseInt(st.nextToken());
		  if (nbegin <0)
		      nbegin = 0;
		  if (nend > bseen_nchromindex.length)
		      nend = bseen_nchromindex.length;

		    for (int npos = nbegin; npos < nend; npos++)
		    {
		       if (!bseen_nchromindex[npos])
		       {

			  for (int nel = 0; nel<bconserved_nchromindex.length; nel++)
		          {
			      //boolean[] bconserved_nel_nchromindex = bconserved[nel][nchromindex];

		              if (bconserved_nchromindex[nel][npos])
		              {
			         theRecA_nfeature.dcountintersect++;
			      }
			  }
			  theRecA_nfeature.dcountall++;
			  bseen_nchromindex[npos]=true;
		       }
		    }
	      }
	      
	   }
	   brcoords.close();

	   if (theRecA_nfeature.dcountall==0)
	   {
	       theRecA_nfeature.dfreq = 0;
	   }
	   else
	   {
	      theRecA_nfeature.dfreq = theRecA_nfeature.dcountintersect/(bconserved[0].length*theRecA_nfeature.dcountall);
	   }
	   System.out.println(theRecA_nfeature.szfeature+"\t"+theRecA_nfeature.dfreq);
	}

	Arrays.sort(theRecA, new RecCompare());

	for (int ni = 0; ni < theRecA.length; ni++)
	{
	    pw.println(theRecA[ni].szfeature+"\t"+theRecA[ni].dfreq);
	}
	pw.close();

    }

}