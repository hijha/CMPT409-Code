import java.io.*;
import java.util.*;

/**
    Explanation::
    Create two list - one for visited points and the other for non-visited points.
    The first point goes into visited. All other points go into non-visited.
    Find the shortest distance between visited and non-visited and add that point
    to visited. Repeat the process till all points are in visited.
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
        String input = Main.ReadLn(255);
        int testcases = Integer.parseInt(input);
        String blankLine = Main.ReadLn(255);
        while (testcases-- != 0) {
            String pointNum = Main.ReadLn(255);
            int numOfPoints = Integer.parseInt(pointNum);
            String p = Main.ReadLn(255);
            String[] pVal = p.split(" ");
            double x = Double.parseDouble(pVal[0]);
            double y = Double.parseDouble(pVal[1]);
            Point point = new Point(x,y);
            ArrayList<Point> unvisited = new ArrayList<>();
            ArrayList<Point> visited = new ArrayList<>();
            visited.add(point);
            numOfPoints--;
            while (numOfPoints-- != 0) {
                p = Main.ReadLn(255);
                pVal = p.split(" ");
                x = Double.parseDouble(pVal[0]);
                y = Double.parseDouble(pVal[1]);
                point = new Point(x,y);
                unvisited.add(point);
            }
            findTotalDistance(unvisited, visited);
            if (testcases != 0) {
                System.out.println();
                blankLine = Main.ReadLn(255);
            }
        }
    }
    
    class Point {
        double x;
        double y;
        
        Point(double x, double y) {
            this.x = x;
            this.y = y;
        }
    }
    
    void findTotalDistance(ArrayList<Point> unvisited, ArrayList<Point> visited) {
        double totalDist = 0;
        int size = unvisited.size();
        while (size > 0) {
            Point minPoint = null;
            double min = Double.MAX_VALUE;
            for (Point p : visited) {
                for (Point u : unvisited) {
                    double dist = findDistance(p ,u);
                    if (dist < min) {
                        min = dist;
                        minPoint = u;
                    }
                }
            }
            totalDist += min;
            visited.add(minPoint);
            unvisited.remove(minPoint);
            size--;
        }
        System.out.printf("%.2f\n",totalDist);    
    }
    
    double findDistance(Point p, Point u) {
        double distance = Math.sqrt(Math.pow((p.x-u.x), 2) + Math.pow((p.y-u.y), 2));
        return distance;
    }
}
