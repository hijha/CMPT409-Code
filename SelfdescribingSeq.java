import java.io.*;
import java.util.*;
import java.math.BigInteger;


/** 
    Explanation::
    For this problem, we need to think backwards. Rather than finding f(n) for n
    we find out when f(n) changes. For instance, f(n) becomes 2 at n = 2, then 
    f(n) = 3 at n = 4, f(n) = 4 at n = 6.
    Using this logic, we only need an array of about 700000, and we can find
    when f(n) changes for each n and output the value based on that.
*/
class Main {
    int[] array = new int[700000];
    static String ReadLn (int maxLg) {  // utility function to read from stdin
        byte lin[] = new byte [maxLg];
        int lg = 0, car = -1;
        String line = "";

        try {
            while (lg < maxLg) {
                car = System.in.read();
                if ((car < 0) || (car == '\n')) break;
                lin [lg++] += car;
            }
        } catch (IOException e) {
            return (null);
        }

        if ((car < 0) && (lg == 0)) 
            return (null);  // eof

        return (new String (lin, 0, lg));
    }

    public static void main (String args[]) {
        Main myWork = new Main();  // create a dinamic instance
        myWork.Begin();            // the true entry point
    }

    void Begin() {
        String input;
        createArray();
        while ((input = Main.ReadLn(255)) != null) {
            int a = Integer.parseInt(input);
            if (a == 0)
                break;
            int i = 0;
            while (array[i] <= a) {
                i++;
            }
            System.out.println(i-1);

        }
    }
    
    void createArray () {
        array[0] = 1;
        array[1] = 1;
        array[2] = 2;
        array[3] = 4;
        array[4] = 6;
        int index = 4;
        int count = 2;
        while(array[index] <= 2000000000) {
            while (array[count] <= index) {
                count++;
            }
            count--;
            index++;
            array[index] = array[index-1] + count;
        }
    }
}
