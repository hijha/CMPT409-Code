import java.io.*;
import java.util.*;

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
        while (true) {
            String input = Main.ReadLn(255);
            int noOfPoints = Integer.parseInt(input);
            if (noOfPoints == 0) {
                break;
            }
            ArrayList<Point> listOfPoints = new ArrayList<Point>();
            while (noOfPoints-- > 0) {
                input = Main.ReadLn(255);
                String[] arr = input.split(" ");
                long x = Long.parseLong(arr[0]);
                long y = Long.parseLong(arr[1]);
                listOfPoints.add(new Point(x,y));
            }
            long area = findArea(listOfPoints);
            long borderPoints = findBorderPoints(listOfPoints);
            long internalPoints = (area - borderPoints + 2) /2;
            System.out.println(internalPoints);
        }
    }

    long findArea(ArrayList<Point> list) {
        long area = 0;
        for (int i = 0; i < list.size(); i++) {
            long val = 0;
            if (i == 0) {
                val = list.get(i).x * (list.get(i+1).y - list.get(list.size()-1).y);
            } else if (i+1 == list.size()) {
                val = list.get(i).x * (list.get(0).y - list.get(i-1).y);
            } else {
                val = list.get(i).x * (list.get(i+1).y - list.get(i-1).y);
            }
            area += val;
        }
        if (area < 0) {
            area = -area;
        }
        return area;
    }

    long findBorderPoints (ArrayList<Point> list) {
        long numOfBorderPoints = 0;
        int i = 0;
        int j = list.size() -1;
        while (i < list.size()) {
            long x = list.get(i).x - list.get(j).x;
            long y = list.get(i).y - list.get(j).y;
            long val = gcd(Math.abs(x), Math.abs(y));
            numOfBorderPoints += val;
            j = i;
            i++;
        }
        return numOfBorderPoints;
    }

    long gcd(long x, long y) {
        if (y == 0) {
            return x;
        }
        return gcd(y, x % y);
    }

    class Point {
        long x;
        long y;

        Point (long x, long y) {
            this.x = x;
            this.y = y;
        }
    }
}
