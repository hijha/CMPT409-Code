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
        String input = Main.ReadLn(255);
        int testcases = Integer.parseInt(input);
        while (testcases-- > 0) {
            input = Main.ReadLn(255);
            String[] arr = input.split(" ");
            int height = Integer.parseInt(arr[0]);
            int width = Integer.parseInt(arr[1]);
            ArrayList<Point> list = new ArrayList<>();
            int index = 0;
            list.add(new Point(0, 0));
            list.add(new Point(height, 0));
            list.add(new Point(0, width));
            list.add(new Point(height, width));
            while (true) {
                input = Main.ReadLn(255);
                arr = input.split(" ");
                int noOfPoints = Integer.parseInt(arr[0]);
                if (noOfPoints == 0) {
                    break;
                } else {
                    int k = Integer.parseInt(arr[0]);
                    int x = Integer.parseInt(arr[1]);
                    int y = Integer.parseInt(arr[2]);
                    int dx = 0;
                    int dy = 0;
                    if (k > 1) {
                        dx = Integer.parseInt(arr[3]);
                        dy = Integer.parseInt(arr[4]);
                    }
                    int mult = 0;
                    while (k-- > 0) {
                        list.add(new Point(x + mult*dx, y + mult*dy));
                        mult++;
                    }

                }
            }
            
            int area = 0;
            if (list.size() == 0) {
                area = height * width;
            } else {
                Collections.sort(list, new XAxis());
                area = findArea(list, width, true);
                Collections.sort(list, new YAxis());
                area = Math.max(area, findArea(list, height, false));
            }
            System.out.println(area);
        }
    }
    
    int findArea (ArrayList<Point> list, int upperVal, boolean xAxis) {
        int area = 0;
        for (int i = 0; i < list.size(); i++) {
            int lower = 0, upper = upperVal;
            for (int j = i+1; j < list.size(); j++) {
                if (xAxis) {
                    int currentArea = (list.get(j).x - list.get(i).x)*(upper - lower);
                    area = Math.max(area, currentArea);
                    if (list.get(j).x != list.get(i).x) {
                        if (list.get(j).y > list.get(i).y) {
                            upper = Math.min(upper, list.get(j).y);
                        } else {
                            lower = Math.max(lower, list.get(j).y);
                        }
                    }
                } else {
                    int currentArea = (list.get(j).y - list.get(i).y)*(upper - lower);
                    area = Math.max(area, currentArea);
                    if (list.get(j).y != list.get(i).y) {
                        if (list.get(j).x > list.get(i).x) {
                            upper = Math.min(upper, list.get(j).x);
                        } else {
                            lower = Math.max(lower, list.get(j).x);
                        }
                    }
                }
            }
        }
        
        return area;
    }
    
    class Point implements Comparable <Point> {
        int x;
        int y;
        
        Point (int x, int y) {
            this.x = x;
            this.y = y;
        }
        
        public int compareTo (Point p) {
            if (this.x == p.x) {
                return this.y - p.y;
            } else {
                return this.x - p.x;
            }
        }
        
        public String toString() {
            return this.x + " " + this.y;
        }
    }
    
    class XAxis implements Comparator <Point> {
        public int compare (Point a, Point b) {
            if (a.x == b.x) {
                return a.y - b.y;
            }
            return a.x - b.x;
        }
    }
    
    class YAxis implements Comparator <Point> {
        public int compare (Point a, Point b) {
            if (a.y == b.y) {
                return a.x - b.x;
            }
            return a.y - b.y;
        }
    }
    

}
