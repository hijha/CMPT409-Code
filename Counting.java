import java.io.*;
import java.util.*;
import java.math.BigInteger;

/**
 Explanation ::
 The number of permutations for expressing an integer n as a sum of smaller integers
 can be found by summing the permutations for all integers from 1 to n-1 and adding 1 
 for integer n. For example, to find such a permutation of 6, we can simply find the 
 sum of permutations for 1, 2, 3, 4 and 5 and then add 1 to it, since 6 can also be expressed
 as sum of just 1 number (6).
 
 If we want to express a number n only as a sum of first k numbers, then the above idea 
 can be modified to be the sum of permutations of (n-1), (n-2), (n-3) ... (n-k) and adding 1. 
 Using the same example as above, number of permutations for 6 to  be expressed as sums of 
 1,2,3 and 4 can  be found by summing the permutations of 2, 3, 4, 5. Number of permutations 
 of 9 expressed only as  sums of 1, 2 and 3 is found by summing permutations of 6, 7 and 8.
 
 We can apply this idea to our problem. Gustavo only understands numbers 1, 2 and 3. So, any 
 number will only be expressed as sum of these 3 numbers. However, since 1 and 4 mean the same
 for Gustavo, the permutations for (n-1) are counted twice. 
 Finally, 1 is not added for these permutations because Gustavo does not recognize any number
 greater than 3. So, for example, 13 cannot be expressed as just 13, since Gustavo doesn't
 recognize the number.
 
 As a result, the expression for finding the permutation is :
    f(n) = 2*f(n-1) + f(n-2) + f(n-3)
*/

class Main {
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
        while ((input = Main.ReadLn(255)) != null) {
            int a = Integer.parseInt(input);
            counting(a);
        }
    }
    
    void counting(int n) {
        if (n == 1) {
            System.out.println(2);
        } else if (n == 2) {
            System.out.println(5);
        } else if (n == 3) {
            System.out.println(13);
        } else {
            BigInteger array[] = new BigInteger[n+1];
            array[0] = BigInteger.ZERO;
            array[1] = BigInteger.valueOf(2);
            array[2] = BigInteger.valueOf(5);
            array[3] = BigInteger.valueOf(13);
            for (int i = 4; i <= n; i++) {
                array[i] = BigInteger.valueOf(2).multiply(array[i-1]);
                array[i] = array[i].add(array[i-2]);
                array[i] = array[i].add(array[i-3]);
            }
            System.out.println(array[n]);
        }
    }
}
/*
class Counting {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int n;
        while (in.hasNextInt()) {
            n = in.nextInt();
        }
    }
}
*/
