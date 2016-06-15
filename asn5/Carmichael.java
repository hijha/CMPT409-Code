import java.io.*;
import java.util.*;
import java.math.BigInteger;

/**
    Explanation::
    Since all prime numbers will satisfy the condition of Carmichael numbers, we need to exclude
    that first. We use Sieve of Eratosthenes to find all the Prime numbers till 65000. When we 
    do the calculations for Carmichael numbers, we exclude these.
    
    We apply the (a^n % n) expression to each number and pre-calculate all the Carmichael Numbers.
    When we are given the input, we simply check to see if its one of those numbers.
*/
public class Main {
    boolean array[] = new boolean[65000];
    boolean primes[] = new boolean[65000];
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
        findPrimes();
        findNumbers();
        while ((input = Main.ReadLn(255)) != null) {
            int a = Integer.parseInt(input);
            if (a == 0)
                break;
            if (array[a]) {
                System.out.println("The number " + a + " is a Carmichael number.");
            } else {
                System.out.println(a + " is normal.");
            }
            
        }
    }
    
    void findPrimes() {
        int[] tempArray = new int[65000];
        for (int i = 0; i < 65000; i++) {
            tempArray[i] = i;
            primes[i] = true;
        }
        for (int i = 2; i < 65000; i++) {
            if (tempArray[i] != -1) {
                for (int j = 2*tempArray[i]; j < 65000; j += tempArray[i]) {
                    tempArray[j] = -1;
                    primes[j] = false;
                }
            }
        }
    }

    void findNumbers() {
        for (int i = 3; i < 65000; i++) {
            if (!primes[i]) {
                array[i] = calc(i);
            }
        }
    }

    boolean calc(int n) {
        for (int a = 2; a < n; a++) {
            BigInteger modAVal = modArithmetic(a,n);
            if (modAVal.compareTo(BigInteger.valueOf(a)) != 0) {
                return false;
            }
        }
        return true;
    }

    BigInteger modArithmetic(int a, int n) {
        int modVal = n;
        BigInteger result = BigInteger.valueOf(1);
        int prevMod = a % modVal;
        while (n > 0) {
            int checker = n & 1;
            if (checker == 1) {
                result = result.multiply(BigInteger.valueOf(prevMod));
            }
            BigInteger prod = BigInteger.valueOf(prevMod).multiply(BigInteger.valueOf(prevMod));
            BigInteger val = prod.mod(BigInteger.valueOf(modVal));
            prevMod = val.intValue();
            n = n >> 1;
        }
        result = result.mod(BigInteger.valueOf(modVal));
        return result;
    }
}
