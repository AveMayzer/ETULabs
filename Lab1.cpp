#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct Student {
    string name;
    string sex;
    float avg;
    unsigned short int group;
    unsigned short int placeInGroup;
    unsigned short int testGrades[5];
    unsigned short int examGrades[3];
    
};

void printStudentFromStruct(Student* students, int num) {
    cout << "ФИО: " << students[num].name << endl;
    cout << "Пол: " << students[num].sex << endl;
    cout << "Группа: " << students[num].group << endl;
    cout << "Номер в списке группы: " << students[num].placeInGroup << endl;

    cout << "Оценки за дифф. зачёты: " << endl;
    for (int j = 0; j < 5; j++) {
        cout << students[num].testGrades[j] << ' ';
    }
    cout << endl;

    cout << "Оценки за экзамены: " << endl;
    for (int j = 0; j < 3; j++) {
        cout << students[num].examGrades[j] << ' ';
    }

    cout << endl;
    cout << endl;
}

int countStudents() {
    ifstream file("db.txt");
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

void printStudents(Student* students, int& cntStudents) {
    for (int i = 0; i < cntStudents; i++) {
        printStudentFromStruct(students, i);
    }
}

void loadStudentsFromFile(Student* students, int& cntStudents) {
    ifstream file("db.txt");
    if (!file.is_open()) {
        cout << "Ошибка: не удалось открыть файл!" << endl;
        return;
    }
    for (int i = 0; i < cntStudents; i++) {
        getline(file, students[i].name);
        file >> students[i].sex;
        file >> students[i].group;
        file >> students[i].placeInGroup;

        for (int j = 0; j < 5; j++) {
            file >> students[i].testGrades[j];
        }
        for (int j = 0; j < 3; j++) {
            file >> students[i].examGrades[j];
        }
        file.ignore(2);
    }
    file.close();
}

void createNewStudent(Student* students, int& cntStudents) { // Добавить нового студента и записать в базу.
    ofstream file("db.txt", ios::app);
    if (!file.is_open()) {
        cout << "Не получилось открыть файл для новой записи студента";
        return;
    }
    cin.ignore();
    cout << "Его ФИО" << endl;
    getline(cin, students[cntStudents].name);
    cout << "Пол (М/Ж)" << endl;
    cin >> students[cntStudents].sex;
    cout << "Группа" << endl;
    cin >> students[cntStudents].group;
    cout << "Его номер места в группе" << endl;
    cin >> students[cntStudents].placeInGroup;
    cout << "Его оценки за дифф. зачёт (5 оценок)" << endl;

    for (int i = 0; i < 5; i++) {
        cin >> students[cntStudents].testGrades[i];
    }

    cout << "Его оценки за экзамен (3 оценки)" << endl;
    for (int i = 0; i < 3; i++) {
        cin >> students[cntStudents].examGrades[i];
    }

    file << students[cntStudents].name << "\n";
    file << students[cntStudents].sex << "\n";
    file << students[cntStudents].group << "\n";
    file << students[cntStudents].placeInGroup << "\n";

    for (int i = 0; i < 5; i++) {
        file << students[cntStudents].testGrades[i] << ' ';
    }
    file << "\n";

    for (int i = 0; i < 3; i++) {
        file << students[cntStudents].examGrades[i] << ' ';
    }
    file << "\n";
    cout << "Успешно сохранено в базу";

    cntStudents++;
}

void printStudentsByGroup(Student* students, int& cntStudents) {
    unsigned short int searchGroup;
    cout << "Введите номер группы:" << endl;
    cin >> searchGroup;
    
    cout << "\nСтуденты из группы: " << searchGroup << endl;
    for (int i = 0; i < cntStudents; i++) {
        if (students[i].group == searchGroup) {
            printStudentFromStruct(students, i);
        }
    }
}

void countStudentsByGender(Student* students, int& cntStudents) {
    int male = 0, female = 0;

    for (int i = 0; i < cntStudents; i++) {
        if (students[i].sex == "М") { male++; }
        else {
            if (students[i].sex == "Ж") { female++; }
        }
    }

    cout << "Кол-во мужчин: " << male << "\nКол-во женщин: " << female << endl;
}

void printStudentsWithoutScholarship(Student* students, int& cntStudents) {
    cout << "Студенты, которые не получают стипендию." << endl;
    for (int i = 0; i < cntStudents; i++) {
        bool hasLowGrade = false;
        for (int j = 0; (j < 5) && (!hasLowGrade); j++) {
            if (students[i].testGrades[j] == 3) {
                hasLowGrade = true;
            }
        }

        for (int j = 0; (j < 3) && (!hasLowGrade); j++) {
            if (students[i].examGrades[j] == 3) {
                hasLowGrade = true;
            }
        }

        if (hasLowGrade) {
            printStudentFromStruct(students, i);
        }
    }
}

void printStudentsWithRegularScholarship(Student* students, int& cntStudents) {
    cout << "Студенты, которые получают обычную стипендию (только 4 и 5)" << endl;
    for (int i = 0; i < cntStudents; i++) {
        bool hasFour = false, hasOnlyGoodAndExcellent = true;
        for (int j = 0; (j < 5) && (hasOnlyGoodAndExcellent); j++) {
            switch (students[i].testGrades[j]) {
            case 3: hasOnlyGoodAndExcellent = false; break;
            case 4: hasFour = true; break;
            }
        }
        for (int j = 0; (j < 3) && (hasOnlyGoodAndExcellent); j++) {
            switch (students[i].examGrades[j]) {
            case 3: hasOnlyGoodAndExcellent = false; break;
            case 4: hasFour = true; break;
            }
        }

        if (hasFour && hasOnlyGoodAndExcellent) {
            printStudentFromStruct(students, i);
        }
    }
    cout << endl;
}

void printStudentsWithIncreasedScholarship(Student* students, int& cntStudents) {
    cout << "Студенты, которые получают повышенную стипендию (только 5)" << endl;
    for (int i = 0; i < cntStudents; i++) {
        bool hasNotExcellent = false;
        for (int j = 0; (j < 5) && (!hasNotExcellent); j++) {
            if (students[i].testGrades[j] < 5) {
                hasNotExcellent = true;
            }
        }

        for (int j = 0; (j < 3) && (!hasNotExcellent); j++) {
            if (students[i].examGrades[j] < 5) {
                hasNotExcellent = true;
            }
        }

        if (!hasNotExcellent) {
            printStudentFromStruct(students, i);
        }
    }
}

int averageGrade(Student* students, int i) {
    int avg = 0;

    for (int j = 0; j < 5; j++) {
        avg += students[i].testGrades[j];
    }

    for (int j = 0; j < 3; j++) {
        avg += students[i].examGrades[j];
    }

    return avg / 8;
}

void printTopStudents(Student* students, int& cntStudents) {
    Student topStudents[999];

    for (int i = 0; i < cntStudents; i++) { // Заполнение нового массива структуры со средним баллом, чтобы не менять местами старую структуру
        topStudents[i] = students[i];
        float avg = 0;
        for (int j = 0; j < 5; j++) {
            avg += students[i].testGrades[j];
        }

        for (int j = 0; j < 3; j++) {
            avg += students[i].examGrades[j];
        }

        topStudents[i].avg = avg / 8;
    }

    for (int i = 0; i < cntStudents; i++) { // Сортировка студентов по ср. баллу
        for (int j = 0; j < cntStudents - i - 1; j++) {

            if (topStudents[j + 1].avg > topStudents[j].avg) {
                swap(topStudents[j + 1], topStudents[j]);
            }
        }
    }

    cout << "Топ 5 студентов по среднему баллу" << endl;

    for (int i = 0; i < cntStudents && i < 5; i++) {
        cout << "ФИО: " << topStudents[i].name << endl;
        cout << "Группа: " << topStudents[i].group << endl;
        cout << "Ср. балл: " << topStudents[i].avg << endl;
        cout << endl;
    }
    cout << endl;

}

void saveAllStudentsToFile(Student* students, int& cntStudents) { // Перезапись студентов в файл.
    ofstream file("db.txt");
    if (!file.is_open()) {
        cout << "Файл не получилось открыть." << endl;
        return;
    }
    for (int i = 0; i < cntStudents; i++) {
        file << students[i].name << "\n";
        file << students[i].sex << "\n";
        file << students[i].group << "\n";
        file << students[i].placeInGroup << "\n";
        for (int j = 0; j < 5; j++) file << students[i].testGrades[j] << ' ';
        file << "\n";
        for (int j = 0; j < 3; j++) file << students[i].examGrades[j] << ' ';
        file << "\n";
    }
    file.close();
}

void editStudent(Student* students, int& cntStudents) {
    string searchName;
    int choiceNum;
    cout << "Введите ФИО студента, данные которого вы хотите изменить." << endl;
    cin.ignore();
    getline(cin, searchName);

    int index = -1;
    for (int i = 0; (i < cntStudents) && (index == -1); i++) {
        if (students[i].name == searchName) {
            index = i;
        }
    }

    if (index == -1) {
        cout << "Студент не найден." << endl;
        return;
    }

    cout << "Выберите, что хотите изменить" << endl;
    cout << "1 | ФИО" << endl;
    cout << "2 | Пол" << endl;
    cout << "3 | Группу" << endl;
    cout << "4 | Позицию в группе" << endl;
    cout << "5 | Оценки за дифф. зачёты" << endl;
    cout << "6 | Оценки за экзамены" << endl;

    cin >> choiceNum;
    cin.ignore();

    switch (choiceNum) {
        case 1: cout << "Введите новое ФИО" << endl;
            getline(cin, students[index].name); break;
        case 2: cout << "Введите пол (М/Ж)" << endl;
            cin >> searchName;
            students[index].sex = searchName; break;
        case 3: cout << "Введите новую группу" << endl;
            cin >> choiceNum;
            students[index].group = choiceNum; break;
        case 4: cout << "Введите новую позицию в группе" << endl;
            cin >> choiceNum;
            students[index].placeInGroup = choiceNum; break;
        case 5: cout << "Введите новые оценки за дифф. зачёты" << endl;
            for (int i = 0; i < 5; i++) {
                cin >> choiceNum;
                students[index].testGrades[i] = choiceNum;
            }
            break;
        case 6: cout << "Введите новые оценки за экзамены" << endl;
            for (int i = 0; i < 3; i++) {
                cin >> choiceNum;
                students[index].examGrades[i] = choiceNum;
            }
            break;

            

    }
    saveAllStudentsToFile(students, cntStudents);
}

void printStudentsByPlaceNumber(Student* students, int& cntStudents) {
    unsigned short int searchPlace;
    cout << "Введите номер" << endl;
    cin >> searchPlace;
    cout << "Найденные студенты по номеру " << searchPlace << endl;
    for (int i = 0; i < cntStudents; i++) {
        if (students[i].placeInGroup == searchPlace) {
            printStudentFromStruct(students, i);
        }
    }

}

int main() {
    setlocale(0, "");

    Student students[999];
    int cntStudents = countStudents();
    loadStudentsFromFile(students, cntStudents); 
    bool started = true;

    int choiceNum;

    while (started) {
        cout << endl;
        cout << "? | Что хотите сделать?" << endl;
        cout << "1 | Добавить нового студента" << endl;
        cout << "2 | Изменить данные о студенте" << endl;
        cout << "3 | Вывести данные всех студентов" << endl;
        cout << "4 | Вывести студентов определённой группы" << endl;
        cout << "5 | Вывести топ 5 студентов по среднему баллу" << endl;
        cout << "6 | Вывести кол-во студентов мужского и женского пола" << endl;
        cout << "7 | Вывести студентов не получающие стипендию" << endl;
        cout << "8 | Вывести студентов получающие обучную стипендию (на хорошо и отлично)" << endl;
        cout << "9 | Вывести студентов, получающие повышенную стипендию (только отлично)" << endl;
        cout << "10| Вывести студентов, имеющий определённый номер в группе" << endl;
        cout << "0 | Выйти из программы" << endl;

        cin >> choiceNum;

        switch (choiceNum) {
            case 0: started = false; break;
            case 1: createNewStudent(students, cntStudents); break;
            case 2: editStudent(students, cntStudents); break;
            case 3: printStudents(students, cntStudents); break;
            case 4: printStudentsByGroup(students, cntStudents); break;
            case 5: printTopStudents(students, cntStudents); break;
            case 6: countStudentsByGender(students, cntStudents); break;
            case 7: printStudentsWithoutScholarship(students, cntStudents); break;
            case 8: printStudentsWithRegularScholarship(students, cntStudents); break;
            case 9: printStudentsWithIncreasedScholarship(students, cntStudents); break;
            case 10: printStudentsByPlaceNumber(students, cntStudents); break;
        
        }
    }
    cout << "Йоу";
    return 0;
}