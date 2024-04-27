#include <iostream>
using namespace std;

bool tit_for_tat(int round_number, bool self_choices[], bool enemy_choices[]) {
    if (round_number == 1) {   //в первом раунде возвращает true
        return true;
    }
    return enemy_choices[round_number - 2]; //в последующих возвращает ответ соперника
}

bool blind_man(int round_number, bool self_choices[], bool enemy_choices[]) { //случайная тактика
    return rand() % 2;
}

bool only_true(int round_number, bool self_choices[], bool enemy_choices[]) {
    return true;        //только правду
}

void battle(bool (*p1)(int, bool[], bool[]), bool (*p2)(int, bool[], bool[]), int &p1_score, int &p2_score) {
    int rounds = rand() % 101 + 100;       //рандомное количество раундов

    bool p1_choices[200], p2_choices[200];  //выбор первого, выбор второго

    for (int r = 1; r <= rounds; ++r) {            //на каждом раунде
        bool ans1 = p1(r, p1_choices, p2_choices);  //генерация ответа первого
        bool ans2 = p2(r, p2_choices, p1_choices);  //генерация ответа второго

        p1_choices[r - 1] = ans1;   //вызов функции и передача ему данных
        p2_choices[r - 1] = ans2;   //вызов функции противника

        //условия присвоения очков
        if (ans1 && ans2) {  //оба сотрудничество
            p1_score += 24;
            p2_score += 24;
        } else if (ans1 && !ans2) {  //второй предал
            p1_score += 0;
            p2_score += 20;
        } else if (!ans1 && ans2) {  //первый предал
            p1_score += 20;
            p2_score += 0;
        } else {               //оба предали
            p1_score += 4;
            p2_score += 4;
        }
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0)));
    
    int titTat_score = 0, blindMan_score = 0, onlyTrue_score = 0;

    battle(tit_for_tat, blind_man, titTat_score, blindMan_score);
    battle(tit_for_tat, only_true, titTat_score, onlyTrue_score);
    battle(only_true, blind_man, onlyTrue_score, blindMan_score);

    cout << "Total score: " << endl;
    cout << "\tTit for tat: " << titTat_score << endl;
    cout << "\tBlind man: " << blindMan_score << endl;
    cout << "\tOnly true: " << onlyTrue_score << endl;

    return 0;
}