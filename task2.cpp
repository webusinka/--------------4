#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
using namespace std;

int getRandomNumber(int min, int max) {
    random_device rd;
    //объект с именем gen для генерации, иницифлизируется с помощью (7) для случайного начального значени генератора
    mt19937 gen(rd());
    //объект с именем dist, отвечает за равномерное распределение целых чисел в диапазоне
    uniform_int_distribution<int> dist(min, max);
    //вызывает dist для генерации через генерации с использованием mt19937
    return dist(gen);
}

vector<int> getLargeArray(vector<int>& array) {
    int min = 100;
    int max = 900;
    for(auto& item : array) {
        item = getRandomNumber(min, max);
    }
    return array;
}

vector<int> getLargeArray2(vector<int>& array) {
    int min = 2;
    int max = 50;
    for(auto& item : array) {
        item = getRandomNumber(min, max);
    }
    return array;
}

vector<int> task2(const vector<int>& array1, const vector<int>& array2, int& len) {
    vector<int> array;
    int minLen = min(array1.size(), array2.size());
    for (int i = 0; i < minLen; i++) {
        if ((i == 0 || i % 2 == 0) && array2[i] % 2 != 0) {
            array.push_back(array2[i]);
        } else if (i % 2 != 0 && array1[i] % 2 == 0) {
            array.push_back(array1[i]);
        } else {
            array.push_back(-1);
        }
    }
    return array;
}

vector<int> task3(const vector<int>& array1, const vector<int>& array2, int& len){
    vector<int> array(len);
    for (auto& item : array) {
        int randomNum1 = array1[getRandomNumber(0, array1.size()-1)];
        int randomNum2 = array2[getRandomNumber(0, array2.size()-1)];
        item = randomNum1 / randomNum2;
    }
    return array;
}

vector<char> task4(const int& len){
    vector<char> array(len);
    for (auto& item: array) {
        int numberGenerat = getRandomNumber(65, 122);
        item = static_cast<char>(numberGenerat);
    }
    array.erase(remove_if(array.begin(), array.end(), [](char c) { return isupper(c); }), array.end());
    return array;
}

int main() {
    //сгенерировать два рандомных вектора
    cout << "Two generated vectors:" << endl;
    int len = 20;
    vector<int> firstArray(len);
    vector<int> secondArray(len/2);

    getLargeArray(firstArray);
    getLargeArray2(secondArray);
    for(auto item: firstArray){
        cout << item << " ";
    }
    cout << endl;
    for(auto item: secondArray){
        cout << item << " ";
    }
    cout << endl;

    // Выведите чётные элементы массива 1 на нечётных местах и нечётные элементы массива 2 на чётных местах
    cout << "\nOn odd even ones of 1, on even odd ones of 2:" << endl;
    vector<int> arrayChetNechet;
    arrayChetNechet = task2(firstArray, secondArray, len);
    for(auto item: arrayChetNechet){
        cout << item << " ";
    }
    cout << endl;

    // Массив из 𝑘 чисел, где элемент: случайный из 1 / случайный из 2
    cout << "\nRandom ones from 1 and 2 dividing them:" << endl;
    int len3 = 10;
    vector<int> arrayDiv(len);
    arrayDiv = task3(firstArray, secondArray, len3);
    for(auto item: arrayDiv) {
        cout << item << " ";
    }
    cout << endl;

    //массив из случайных символов, без заглавных букв
    cout << "\nAn array of random characters, without capital letters:" << endl;
    vector<char> arraySimbols(20);
    const int len4 = arraySimbols.size();
    arraySimbols = task4(len4); 
    for(auto item: arraySimbols) {
        cout << item << " ";
    }
    cout << endl;

    //массив случайных чисел [0, 300], отсортировать по возрастанию и создать массив содержащий элементы исходного массива, в которых цифры повторяются дважды.
    cout << "\nAn array of doubled numbers:" << endl;
    const int size = 20;
    vector<int> array300(size);
    for (auto& item: array300){
        item = getRandomNumber(0, 300);
    }
    sort(array300.begin(), array300.end());
    vector<int> array2;
    for (auto item: array300){
        array2.push_back(item);
        array2.push_back(item);
    }
    for(auto item: array300) {
        cout << item << " ";
    }
    cout << endl;
    for(auto item: array2) {
        cout << item << " ";
    }
    cout << endl;

    return 0;
}