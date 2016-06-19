import java.io.*;
import java.util.*;

/**
    Explanation:
    According to the question, Goldbach's conjecture says that every even prime number 
    is a sum of two even primes. We can convert every integer into an even integer.
    If the number n is even, we subtract 2+2 = 4 from it and find the other two prime 
    numbers which sum to n-4. 
    If the number is even, we subtract 2 + 3 = 5 from it and find hte other two prime
    numbers which sum to n - 5;
    The lowest number which can be expressed as a sum of 4 primes is 8, since 2 is the 
    smallest prime and 2 + 2 + 2 + 2 = 8. So, for any number under 8, we print "Impossible".
*/
class Main {
    boolean[] primes = new boolean[10000000];
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
        while ((input = Main.ReadLn(255)) != null) {
            int a = Integer.parseInt(input);
            if (a < 8) {
                System.out.println("Impossible.");
            } else {
                boolean found = false;
                if (a % 2 == 0) {
                    System.out.print("2 2 ");
                    a = a - 4;
                } else {
                    System.out.print("2 3 ");
                    a = a - 5;
                }
                for (int i = 2; i < 10000000; i++) {
                    if (primes[i] && primes[a - i]) {
                        System.out.println(i + " " + (a-i));
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    System.out.println("Impossible.");
                }
            }
        }
    }

    void findPrimes() {
        int[] tempArray = new int[10000000];
        for (int i = 0; i < 10000000; i++) {
            tempArray[i] = i;
            primes[i] = true;
        }
        for (int i = 2; i < 10000000; i++) {
            if (tempArray[i] != -1) {
                for (int j = 2*tempArray[i]; j < 10000000; j += tempArray[i]) {
                    tempArray[j] = -1;
                    primes[j] = false;
                }
            }
        }
    }
    
}
