#include <iostream>
#include <vector>
using namespace std;

int main () {
    vector<int> randArray;
    int xi;
    int repeat;
    bool firstAppear = false;

    cout << "Enter x0, A, B, C" << endl; //x0 - начальное значение; A - множитель; B - инкрементирующее значение; C - диапазон генерации рандомных
    int x0, A, B, C; 
    cin >> x0 >> A >> B >> C;
    if (!(0 <= A && A <= C) || (!(0 <= B && B <= C)) || (!(0 <= x0 && x0 < C))) { //проверка на дурака
        cout << "error";
        return -1;
    }

    randArray.push_back(x0);

    for (int i = 0; i < 9; i++) {
        xi = (A * randArray[i] + B) % C;  //формула генерации рандомных чисел
        randArray.push_back(xi);
        if (x0 == xi && randArray.size() > 1 && firstAppear == false){
            repeat = i + 2; // +2 потому что в индекс с нуля и прибавляется знач только на след итерации
            firstAppear = true;
        }
    }

    for (int n : randArray){
        cout << n << " ";
    }

    cout << "\nIndex element from which the repeat: " << repeat;
}