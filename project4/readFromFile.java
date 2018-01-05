import java.io.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

/**
 * Created by probal chandra dhar on 12/2/17.
 */
public class readFromFile {

    /**
     * Function to read the VM program from file
     *
     * @param fileName FileName that will be read
     * @param test_metadata FuncMetaData array
     * @param litArray Array of literals
     * @return the list containing operands and operator
     */
    public List<Integer> readFromFileFunc( String fileName, FuncMetaData[] test_metadata, String[] litArray ) {

        // This will reference one line at a time
        String line;

        int counterFuncData = 0, counterLiteral = 0;

        // ArrayList to add the operands and operator
        List<Integer> buildArray = new ArrayList<Integer>();

        try {

            int tempStore, numOpCodesAndOperands = 0, numFuncs = 0, literalCount= 0;

            // scanner class to read the file from disk
            Scanner sc = new Scanner(new File(fileName));

            // check every line from the file
            while (sc.hasNextLine()) {
                String thisString = sc.nextLine();

                // looking for ~ in the file
                if (thisString.equals("~")) {
                    // System.out.println("found ~");
                    // now read the next Int for numOpCodesAndOperands
                    if ( sc.hasNext() ) {
                        numOpCodesAndOperands = sc.nextInt();
                    }
                    for ( int i = 0; i < numOpCodesAndOperands; i++ ) {

                        // getting the next integer value from file
                        tempStore = sc.nextInt();

                        // Adding operands and operator to the arrayList
                        buildArray.add(tempStore);

                        // print to check
//                         System.out.println("tempstore: " + tempStore);
                    }

                    // now read the next Int for numFuncs
                    if ( sc.hasNext() ) {
                        // System.out.println(sc.nextInt());
                        numFuncs = sc.nextInt();
                    }
                    for ( int i = 0; i < numFuncs; i++ ) {
                        // System.out.println(sc.next());
                        // System.out.print(sc.nextInt() + " ");
                        // System.out.print(sc.nextInt() + " ");
                        // System.out.println(sc.nextInt());

                        FuncMetaData metaData = new FuncMetaData(sc.next(), sc.nextInt(), sc.nextInt(), sc.nextInt());
                        test_metadata[counterFuncData] = metaData;
                        counterFuncData++;
                    }

                    // now read the next Int for literalCount
                    if ( sc.hasNext() ) {
                        literalCount = sc.nextInt();
//                         System.out.println(literalCount);
                    }

//                    System.out.println("literalCount: " + literalCount);

                    // make the Scanner class happy
                    sc.nextLine();
                    for ( int i = 0; i < literalCount; i++ ) {
//                         System.out.println(sc.nextLine());

                        // Adding literals to array
                        litArray[counterLiteral] = sc.nextLine();
                        counterLiteral++;
                    }

                } // End if ~
            } // End while

            // closing the file
            sc.close();

            // Return the ArrayList
            return buildArray;

        }
        catch(FileNotFoundException ex) {
            System.err.println("Unable to open file '" + fileName + "'");
        }

        return buildArray;

    } // end of readFromFile

    /**
     * Function to execute a Linux command in Java
     * @param execCommand Unix command
     * @return s - for this program only a number as string will
     */
    public String JavaRunCommand ( String execCommand ) {

        String s = null;

        try {

            // run the Unix "ls -l" command
            // using the Runtime exec method. NOTE: Windows requires more work as demonstrated in class
            Process p = Runtime.getRuntime().exec(execCommand);

            BufferedReader stdInput = new BufferedReader(new InputStreamReader(p.getInputStream()));

            BufferedReader stdError = new BufferedReader(new InputStreamReader(p.getErrorStream()));

            // read the output from the command
            System.out.println("Here is the standard output of the command:\n");
            while ((s = stdInput.readLine()) != null) {
//                System.out.println(s);
                return s;
            }

            // read any errors from the attempted command
            System.out.println("Here is the standard error of the command (if any):\n");
            while ((s = stdError.readLine()) != null) {
                System.out.println(s);
            }

//            System.exit(0);
        }
        catch (IOException e) {
            System.out.println("exception happened - here's what I know: ");
            e.printStackTrace();
            System.exit(-1);
        }

        // Default
        return s;

    }

}
