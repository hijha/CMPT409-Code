import java.io.*;
import java.util.*;
import java.math.BigInteger;

/**
  Explanation::
  In mathematical terms, the expression for finding the number of moves for n discs
  can be expressed as :
  f(n) = 2*f(n-k) + 2^k -1;  
  This is because, the smallest (n-k) discs are first moved from needle 1 to needle 2.
  For the k largest discs remaining on needle 1, the principle of Towers of Hanoi with 
  3 needles can be applied (there are only 3 free needles left). This gives us 2^k -1
  moves.
  The smalles (n-k) discs which were moved to needle 2 can now be moved. Since this set 
  of (n-k) discs are moved twice we multiple f(n-k) by 2.
  
  However, k is an unknown. We can find this by trial and error by checking what value
  of k gives the minimum number of moves for every n disc.
*/
class Main {
    BigInteger array[] = new BigInteger[10001];
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
        for (int i = 0; i <= 10000; i++) {
            myWork.array[i] = BigInteger.valueOf(0);
        }
        myWork.Begin();            // the true entry point
    }
    
    void Begin() {
        String input;
        while ((input = Main.ReadLn(255)) != null) {
            int a = Integer.parseInt(input);
            towers(a);
        }
    }
    
    void towers(int n) {
        if (n == 1) {
            System.out.println(1);
        } else if (n == 2) {
            System.out.println(3);
        } else {
            array[0] = BigInteger.ZERO;
            array[1] = BigInteger.valueOf(1);
            array[2] = BigInteger.valueOf(3);
            for (int i = 3; i <= n; i++) {
                if (array[i].equals(BigInteger.valueOf(0))) {
                    array[i] = findMin(i);
                }  
            }
            System.out.println(array[n]);
        }
    }
    
    BigInteger findMin(int n) {
        BigInteger prev = BigInteger.valueOf(-1); 
        BigInteger min = BigInteger.valueOf(-1);
        for (int k = 1; k <= (n+1)/2; k++) {
            BigInteger val = BigInteger.valueOf(2).multiply(array[n-k]);
            val = val.add(BigInteger.valueOf(2).pow(k));
            val = val.subtract(BigInteger.valueOf(1));
            if (k == 1) {
                prev = val;
                min = val;
            } else {
                if (val.compareTo(prev) == 1) {
                    break;
                }
                if (val.compareTo(min) == -1) {
                    min = val;
                }
                prev = val;
            }
        }
        return min;
    }
}
