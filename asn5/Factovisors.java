import java.io.*;
import java.util.*;

class Main {
    Map<Integer, Integer> divisor;
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
            boolean divides = true;
            divisor = new LinkedHashMap<Integer, Integer>();
            String[] array = input.split(" ");
            
            int a = Integer.parseInt(array[0]);
            int b = Integer.parseInt(array[1]);
            
            if (b == 1 || a >= b) {
                System.out.println(b + " divides " + a + "!");
            } else {
                findPrimeFactors(b);
                for (Map.Entry<Integer, Integer> entry : divisor.entrySet()) {
                    int prime = entry.getKey();
                    int count = findPowersOfPrimesInFactorial(a, prime);
                    if (entry.getValue() > count) {
                        divides = false;
                        break;
                    }
                }

                if (divides) {
                    System.out.println(b + " divides " + a + "!");
                } else {
                    System.out.println(b + " does not divide " + a + "!");
                }
            }
        }
    }
    
    void findPrimeFactors(int b) {
        int n = b;
        int count = 0;
        while (n % 2 == 0) {
            count++;
            n /= 2;
        }
        if (count != 0)
            divisor.put(2, count);
        count = 0;
        int p = 3;
        int root = (int) Math.sqrt(n) + 1;
        while (p < root) {
            if (n % p == 0) {
                count++;
                n /= p;
            } else {
                if (count != 0)
                    divisor.put(p, count);
                count = 0;
                p += 2;
            }
        }
        if (n > 1) {
            divisor.put(n, 1);
        }
    }

    int findPowersOfPrimesInFactorial(int a, int p) {
        int pk = p;
        int factors = 0;
        while (true) {
            if (a / pk > 0) {
                factors += (a / pk);
                pk = pk * p;
            } else
                break;
        }
        
        return factors;
    }
}
