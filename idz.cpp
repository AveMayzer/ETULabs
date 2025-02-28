#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>

using namespace std;

struct VolleyballStudent {
	string name;
	string sex;
	unsigned short int age;
	unsigned short int course;
	string clothSize;
	bool hasCategory;
};

int countStudents2() {
    ifstream file("db2.txt");
    if (!file.is_open()) {
        return 0;
    }

    int cntStudents;
    int cnt = 0;
    string text;

    while (!file.eof()) {
        getline(file, text);
        cnt++;
    }
    cntStudents = cnt / 6;
    return cntStudents;
}

void printStudentFromStruct2(VolleyballStudent* students, int num) {
    cout << "ФИО: " << students[num].name << endl;
    cout << "Пол: " << students[num].sex << endl;
    cout << "Возаст: " << students[num].age << endl;
    cout << "Номер курса: " << students[num].course << endl;
    cout << "Размер одежды: " << students[num].clothSize << endl;
    cout << "Наличие разряда (1 - Да 2 - Нет): " << students[num].hasCategory << endl;
    cout << endl;
}

void loadStudentsFromFile2(VolleyballStudent* students, int& cntStudents) {
    ifstream file("db2.txt");
    if (!file.is_open()) {
        cout << "Ошибка: не удалось открыть файл!" << endl;
        return;
    }
    for (int i = 0; i < cntStudents; i++) {
        getline(file, students[i].name);
        file >> students[i].sex;
        file >> students[i].age;
        file >> students[i].course;
        file >> students[i].clothSize;
        file >> students[i].hasCategory;
        file.ignore(1);
    }
    file.close();
}

void printAllStudentsWithCategory(VolleyballStudent* students, int& cntStudents) {
    for (int i = 0; i < cntStudents; i++) {
        if (students[i].hasCategory) {
            printStudentFromStruct2(students, i);
        }
        
    }
}

void printAllStudentsFemale(VolleyballStudent* students, int& cntStudents) {
    cout << "Студенты, входящие в женскую сборную: " << endl;
    for (int i = 0; i < cntStudents; i++) {
        if (students[i].sex == "Ж") {
            printStudentFromStruct2(students, i);
        }
    }
    cout << endl;
}

void printStudentsByCourse(VolleyballStudent* students, int& cntStudents) {
    unsigned short int choiceCourse;
    cout << "Введите номер курса: " << endl;
    cin >> choiceCourse;
    cout << "Студениты из " << choiceCourse << " курса" << endl;
    for (int i = 0; i < cntStudents; i++) {
        if (students[i].course == choiceCourse) {
            printStudentFromStruct2(students, i);
        }
    }
    cout << endl;
}
void printStudentsMaleUpperClothSize(VolleyballStudent* students, int& cntStudents) {
    cout << "Студениты мужского пола, которые имеют размер больше S" << endl;
    for (int i = 0; i < cntStudents; i++) {
        string clothSize = students[i].clothSize;
        if ((clothSize.find("S") == -1) && (students[i].sex == "М")) {
            printStudentFromStruct2(students, i);
        }
    }
    cout << endl;

}
int main() {
    setlocale(0, "");
    SetConsoleCP(1251);
    VolleyballStudent students[999];
    int cntStudents = countStudents2();
    loadStudentsFromFile2(students, cntStudents);
    bool started = true;

    int choiceNum;

    while (started) {

        cout << "? | Введите номер действия" << endl;
        cout << "1 | Вывести всех студентов, имебщих разряд" << endl;
        cout << "2 | Вывести женскую сборную команду." << endl;
        cout << "3 | Вывести студентов определённого курса." << endl;
        cout << "4 | Вывести студентов мужского пола, у которых размер одежды больше S." << endl;
        cout << "0 | Выйти." << endl;

        cin >> choiceNum;

        switch (choiceNum) {
        case 1: printAllStudentsWithCategory(students, cntStudents);break;
        case 2: printAllStudentsFemale(students, cntStudents);break;
        case 3: printStudentsByCourse(students, cntStudents);break;
        case 4: printStudentsMaleUpperClothSize(students, cntStudents);break;
        }
    }

    return 0;
}