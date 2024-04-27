#include <iostream>
#include <vector>
#include <random>
#include <cmath>

using namespace std;

void fillVectorWithRandom(vector<int>& vec) { //заполнение вектора случайными числами
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(1, 100);

    for (int& num : vec) {
        num = dis(gen);
    }
}

int typeOfElementCount(const vector<int>& container, int element) { //подсчет количества вхождений заданного элемента в вектор
    int count = 0;
    for (const int& value : container) {
        if (value == element) count++;
    }
    return count;
}

double mathExpectation(const vector<int>& container) { //вычисление реального математического ожидания
    double sum = 0;
    for (const int& value : container) {
        sum += value;
    }
    return sum / container.size();
}

double mathExp(vector<int>& array) { //вычисление ожидаемого математического ожидания
    double sum = 0;
	for (auto& a : array) {
		sum += a;
	}
	return sum / array.size();
}

double mathDispersion(const vector<int>& container) { //функция для вычисления дисперсии
    double mean = mathExpectation(container);
    double sum = 0;
    for (const int& value : container) {
        sum += (value - mean) * (value - mean); //дисперсия, сумма отклонения действительных от ожидаемых
    }
    return sum / (container.size() - 1);
}

double tabLaplas(double x) { //функции Лапласа (стандартного нормального распределения) для заданного аргумента x
    return (1.0 / 2.0) * (1.0 + erf(x / sqrt(2.0)));
}

double chiSquare(const vector<int>& container) { // Функция для вычисления критерия хи-квадрат
    int size = container.size();
    double chi2 = 0;
    double mean = mathExpectation(container);
    double stdDev = sqrt(mathDispersion(container));

    for (int i = 1; i <= 100; i++) { //разность между наблюдаемой и ожидаемой частотой, возводится в квадрат и делится на ожидаемую частоту
        double expectedFreq = size * (tabLaplas((i - mean) / stdDev) - tabLaplas((i - 1 - mean) / stdDev));
        double observedFreq = typeOfElementCount(container, i);
        chi2 += pow(observedFreq - expectedFreq, 2) / expectedFreq;//значение хи-квадрат суммируется на каждом элементе
    }

    return chi2;
}

int main() {
    system("chcp 65001");
    vector<int> vector50(50);
    fillVectorWithRandom(vector50);
    vector<int> vector100(100);
    fillVectorWithRandom(vector100);
    vector<int> vector1000(1000);
    fillVectorWithRandom(vector1000);

    double criticalValue = 124.342; // Критическое значение хи-квадрат для 99 степеней свободы и уровня значимости 0.05

    //для 50 элементов
    double chiSquareValue = chiSquare(vector50);
    double meanExpected = mathExpectation(vector50); //реальное математическое ожидание
    double meanObserved = mathExp(vector50);

    cout << "Chi-Square P-value: " << chiSquareValue << endl;

    if (chiSquareValue <= criticalValue) {
        cout << "Гипотеза о нормальном распределении не отвергается." << endl;
    } else {
        cout << "Гипотеза о нормальном распределении отвергается." << endl;
    }

    cout << "Ожидаемое математическое ожидание: " << meanExpected << endl;
    cout << "Реальное математическое ожидание: " << meanObserved << endl;
    cout << endl;

    //для 100 элементов
    chiSquareValue = chiSquare(vector100);
    meanExpected = mathExpectation(vector100);
    meanObserved = mathExp(vector100);

    cout << "Chi-Square P-value: " << chiSquareValue << endl;

    if (chiSquareValue <= criticalValue) {
        cout << "Гипотеза о нормальном распределении не отвергается." << endl;
    } else {
        cout << "Гипотеза о нормальном распределении отвергается." << endl;
    }

    cout << "Ожидаемое математическое ожидание: " << meanExpected << endl;
    cout << "Реальное математическое ожидание: " << meanObserved << endl;
    cout << endl;

    //для 1000 элементов
    chiSquareValue = chiSquare(vector1000);
    meanExpected = mathExpectation(vector1000);
    meanObserved = mathExp(vector1000);

    cout << "Chi-Square P-value: " << chiSquareValue << endl;

    if (chiSquareValue <= criticalValue) {
        cout << "Гипотеза о нормальном распределении не отвергается." << endl;
    } else {
        cout << "Гипотеза о нормальном распределении отвергается." << endl;
    }

    cout << "Ожидаемое математическое ожидание: " << meanExpected << endl;
    cout << "Реальное математическое ожидание: " << meanObserved << endl;
    cout << endl;
    
    return 0;
}