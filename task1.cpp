#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

void PrintfTablHalfDivisionMethod(double LeftPoint, double RightPoint, int N)
{
    if (N == 1)
    {
        cout << "N";
        cout << "\t     a ";
        cout << "\t\t\t     b ";
        cout << "\t\t\t     b-a ";
        cout << endl;
        cout << "----------------------------------------------------------------------------------";
        cout << endl;
    }
    cout << N << " |";
    cout <<"\t" << setw(10) << LeftPoint;
    cout << "\t\t" << setw(10) << RightPoint;
    cout << "\t\t" << setw(12)<< RightPoint - LeftPoint;
    cout << endl;
}

double function(double x) {
    return sin(x) - 2*x - 1; // Заменить функцией, корни которой мы ищем
}

double df(double x) {
    return cos(x) - 2;  //производная от функцииЫ
}

double g(double x) {
    return x - function(x)/df(x);
}

int findGraficalSolution (float& left, float& right, float& x0){
    for (float x = -1; x < 5; x += 0.01){
        if (ceil(sin(x) - (-2*x - 1)) == 0){
            left = x - 1.0;
            right = x + 1.0;
            x0 = x;
        }
    }
    return 0;
}

// a, b - пределы хорды, epsilon — необходимая погрешность
double findChord(double a, double b, double epsilon) {
    for (int i = 1; abs(b - a) >= epsilon; i++) {
        a = a - (b - a) * function(a) / (function(b) - function(a));
        b = b - (a - b) * function(b) / (function(a) - function(b));
        PrintfTablHalfDivisionMethod(a, b, i);
    }
    return b;
}

//метод Ньютона
double NewtownMethod(double x0, double epsilon) {
    double x;
    for (int i = 1; abs(function(x0)) >= epsilon && i < 10; i++) {
        x = g(x0);
        PrintfTablHalfDivisionMethod(x, x0, i);
        x0 = x;
    }
    return x;
}

double HalfDivisionMethod(double LeftPoint, double RightPoint,double epsilon)
{
    int iteration = 1;
    double midPoint = 0.0;
    if (function(LeftPoint) * function(RightPoint) < 0)// проверка на разность знаков функции на концах отрезка
    {
        while (abs(RightPoint - LeftPoint) > epsilon)// пока интервал больше погрешности
        {
            midPoint = (RightPoint + LeftPoint) / 2;
            PrintfTablHalfDivisionMethod(LeftPoint, RightPoint, iteration);
            if (function(LeftPoint) * function(midPoint) < 0)  RightPoint = midPoint;// если функция имеет разные знаки, то правая точка середина отрезка
            else LeftPoint = midPoint;
            iteration++;
        }
    } 
    else {
        cout << "The interval is not selected correctly. There is no solution in the segment" << endl;
    }
    return midPoint;
}

int main() {
    float left = 0;
    float right = 0;
    float x0 = 0;
    findGraficalSolution(left, right, x0);

    float eps = 0.00001;
    cout << "Root through the chord method:\n" << findChord(left, right, eps) << endl << "\n"; //метод хорд

    cout << "The root through the method of half division:\n" << HalfDivisionMethod(left, right, eps) << endl << "\n"; //метод половинного деления

    cout << "The root through the Newtown method:\n" << NewtownMethod(x0, eps) << "\n"; //метод Ньютона

    cout << "\nBy the rate of convergence" << endl;
    cout << "Newtown method > Chord method > Half divisions"<< endl;
    
    return 0;
}