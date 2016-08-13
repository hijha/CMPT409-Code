import java.io.*;
import java.util.*;

class Main {
    HashSet<Integer> visited;
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
        String input = Main.ReadLn(255);
        int testcases = 0;
        if (input != null) {
            testcases = Integer.parseInt(input);
        }
        String blankLine = Main.ReadLn(255);
        String origin = "";
        String destination = "";
        while (testcases-- != 0) {
            visited = new HashSet<Integer>();
            origin = Main.ReadLn(255);
            destination = Main.ReadLn(255);
            int originVal = parseNum(origin);
            int destVal = parseNum(destination);
            int noOfForbiddenPoints = Integer.parseInt(Main.ReadLn(255));
            while (noOfForbiddenPoints-- > 0) {
                String point = Main.ReadLn(255);
                int val = parseNum(point);
                visited.add(val);
            }
            System.out.println(findSteps(originVal, destVal));
        }
    }
    
    int parseNum(String input) {
        int mult = 1;
        int val = 0;
        for (int i = 6; i >= 0; i-=2) {
            int p = input.charAt(i) - '0';
            val += (mult*p);
            mult *= 10;
        }
        return val;
    }
    
    int findSteps(int origin, int destination) {
        LinkedList<Integer> queue = new LinkedList<>();
        Map<Integer, Integer> map = new HashMap<>();
        queue.add(origin);
        map.put(origin, 0);

        while (!queue.isEmpty()) {
            int val = queue.pop();
            int distance = map.get(val);

            if (!visited.contains(val)) {
                int newDistance = distance + 1;
                visited.add(val);
                int mult = 1;
                for (int i = 0; i < 4; i++) {
                    int newVal = val + mult;
                    if (newVal >= 0 && newVal < 10000 && !visited.contains(newVal)) {
                        if (newVal == destination) {
                            //System.out.println("+ " + newDistance);
                            return newDistance;
                        }
                        map.put(newVal, newDistance);
                        queue.add(newVal);
                    }
                    newVal = val - mult;
                    if (newVal >= 0 && newVal < 10000 && !visited.contains(newVal)) {
                        if (newVal == destination) {
                            //System.out.println("- " + newDistance);
                            return newDistance;
                        }
                        map.put(newVal, newDistance);
                        queue.add(newVal);
                    }
                    mult *= 10;
                }
            }
        }
        return -1;
    }
    
    int[] findNewVals(int init) {
        int[] newArray = new int[2];
        
    }
    
}
