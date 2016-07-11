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

        while (true) {
            int noOfTeams, noOfTables;
            String[] ar = input.split(" ");
            noOfTeams = Integer.parseInt(ar[0]);
            noOfTables = Integer.parseInt(ar[1]);

            if (noOfTeams == 0 && noOfTables == 0) {
                break;
            }
            HashMap<Integer, Integer> teams = new HashMap<>();
            HashMap<Integer, Integer> tables = new HashMap<>();
            
            input = Main.ReadLn(255);
            ar = input.split(" ");
            int index = 1;
            for (int i =0; i < ar.length; i++) {
                teams.put(index, Integer.parseInt(ar[i]));
                index++;
            }
            input = Main.ReadLn(255);
            ar = input.split(" ");
            index = 1;
            for (int i =0; i < ar.length; i++) {
                int cap = Integer.parseInt(ar[i]);
                tables.put(index, cap);
                index++;
            }

            teams = sortMap(teams);

            int maxTeam = (Integer) teams.values().toArray()[0];
            if (maxTeam > tables.size()) {
                System.out.println(0);
            } else {
                findDistribution(teams, tables);
            }
            input = Main.ReadLn(255);
        }
    }
    
    void findDistribution(HashMap<Integer, Integer> teams, HashMap<Integer, Integer> tables) {
        Iterator<Map.Entry<Integer, Integer> > teamIt = teams.entrySet().iterator();
        HashMap<Integer, Integer[]> result = new HashMap<>();
        boolean success = true;
        
        while (teamIt.hasNext()) {
            tables = sortMap(tables);
            Map.Entry entry = teamIt.next();
            int teamKey = (Integer) entry.getKey();
            int teamVal = (Integer) entry.getValue();
            int[] array = new int[teamVal];
            int j = 0;
            Iterator<Map.Entry<Integer, Integer>> it = tables.entrySet().iterator();
            while (j < array.length) {
                Integer val = (Integer) ((Map.Entry)it.next()).getKey();
                int tableVal = tables.get(val);
                if (tableVal == 0) {
                    success = false;
                    break;
                }
                array[j] = val;
                j++;
                tableVal = tableVal - 1;
                tables.put(val, tableVal);
            }
            //Integer[] newArray = (Integer[]) sort(array);
            Integer[] newArray = new Integer[array.length];
            for (int i = 0; i < array.length; i++) {
                newArray[i] = (Integer) array[i];
            }
            result.put(teamKey, newArray);
            
        }
        
        if (!success) {
            System.out.println(0);
            return;
        }
        System.out.println(1);
        for (Integer[] dist : result.values()) {
            for (int a : dist) {
                System.out.print(a + " ");
            }
            System.out.println();
        }
    }
    
    HashMap<Integer, Integer> sortMap(HashMap<Integer, Integer> map) { 
       List<Integer> list = new LinkedList(map.entrySet());
       Collections.sort(list, new Comparator() {
            public int compare(Object o1, Object o2) {
               return ((Comparable) ((Map.Entry) (o2)).getValue())
                  .compareTo(((Map.Entry) (o1)).getValue());
            }
       });
       HashMap<Integer, Integer> sortedHashMap = new LinkedHashMap<>();
       for (Iterator it = list.iterator(); it.hasNext();) {
              Map.Entry entry = (Map.Entry) it.next();
              sortedHashMap.put((Integer) entry.getKey(), (Integer) entry.getValue());
       } 
       return sortedHashMap;
    }
    
    Integer[] sort (int[] array) {
        int length = array.length;
        sort (array, 0, length-1);
        Integer[] result = new Integer[array.length];
        for (int i = 0; i < array.length; i++) {
            result[i] = (Integer)array[i];
        }
        return result;
    }

    void sort (int[] array, int first, int last) {
        int index = partition(array, first, last);
        if (first < index - 1) {
            sort(array, first, index-1);            
        }
        if (index < last) {
            sort (array, index, last);
        }
    }   

    int partition (int[] array, int first, int last) {
        int i = first;
        int j = last;
        int mid = (i+j)/2;
        int pivot = array [mid];
        while (i <= j) {
            while (array[i] < pivot) {
                i++;
            }
            while (array[j] > pivot) {
                j--;
            }

            if (i <= j) {
                int temp = array[i];
                array[i] = array[j];
                array[j] = temp;
                i++;
                j--;
            }
        }
        return i;
    }
}
