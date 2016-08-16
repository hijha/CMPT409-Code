#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

double calcMoney(double array[], int size) {
  if (size == 1) {
    return array[0];
  }
  double sum = 0;
  for (int i = 0; i < size; i++) {
    sum += array[i];
  }
  double avg = (sum/size);
  double lessThanAvg = 0;
  double moreThanAvg = 0;
  for (int i = 0; i < size; i++) {
    if (array[i] < avg) {
      lessThanAvg += (floor((avg - array[i])*100))/100;
    } else if (array[i] > avg) {
      moreThanAvg += (floor((array[i] - avg)*100))/100;
    }
  }
//  cout << lessThanAvg << " " << moreThanAvg << endl;
  return (lessThanAvg > moreThanAvg) ? lessThanAvg : moreThanAvg;
}

int main() {
    double r = 100;
    int n;
    while(cin >> n) {
	if (n == 0) {
	    break;
	}
	int i = 0;
	double amount[n];
	while (i < n) {
	    cin >> amount[i];
	    i++;
	}
	cout << '$' << setprecision(2) << fixed << calcMoney(amount, n) << endl;
    }
    return 0;
}
