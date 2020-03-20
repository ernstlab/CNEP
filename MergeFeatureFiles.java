import java.io.*;
import java.util.*;


public class MergeFeatureFiles
{

    public static void main(String[] args) throws IOException
    {

        String szLine;

	PrintWriter pw = new PrintWriter(new FileWriter(Constants.FEATUREFILELIST));//"mergefeaturefiles_2018.txt"));
        BufferedReader brfeaturefile = Util.getBufferedReader(Constants.TRAINDIRFEATURES);//szfeaturelistdir);

        while ((szLine = brfeaturefile.readLine())!=null)
	{
	   if (!szLine.trim().equals(""))
           {
	       StringTokenizer st = new StringTokenizer(szLine,"\t");
	       st.nextToken();
	       String szinfile = st.nextToken();
	       String szindir =st.nextToken();
	       String szFeatureLine;
	       BufferedReader br = Util.getBufferedReader(szinfile);
	       while ((szFeatureLine = br.readLine())!=null)
	       {
		   pw.println(szindir+"/"+szFeatureLine);
	       }
	       br.close();
	   }
	}
        brfeaturefile.close();
	pw.close();

    }

}