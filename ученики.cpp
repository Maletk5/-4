#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <numeric>
#include <iomanip>
#include <algorithm>
#include <Windows.h>;
#pragma execution_character_set("utf-8");
using namespace std;
int a = 0;
struct Student {
    string id; 
    string name;
    string groupname;
    vector<int> grades;
};
vector<string> groups;
vector<Student> Students;
auto findGroup(const string& groupname) {
    return find(groups.begin(), groups.end(), groupname);
}
auto findStudentById(const string& id) {
    return find_if(Students.begin(), Students.end(), [&id](const Student& s) {
        return s.id == id;
        });
}
bool hasStudentsInGroup(const string& groupname) {
    return any_of(Students.begin(), Students.end(), [&groupname](const Student& s) {
        return s.groupname == groupname;
        });
}
void initDefaultData() {
    groups.push_back("БД-1-25");
    groups.push_back("ИС-1-25");

    Students.push_back({ "1", "Иванов Иван Иванович", "БД-1-25", {5, 5, 5, 4, 5} });
    Students.push_back({ "2", "Петров Петр Петрович", "БД-1-25", {4, 4, 4, 4, 5} });
    Students.push_back({ "3", "Сидоров Сидор Сидорович", "БД-1-25", {5, 5, 5, 5, 5} });
    Students.push_back({ "4", "Алексеев Алексей Алексеевич", "ИС-1-25", {3, 4, 3, 5, 4} });
}
void manageStudentsMenu() {
    while (true) {
        cout << "МЕНЮ студентов" "\n"
            << "1. Добавить студента" "\n"
            << "2. Изменить студента" "\n"
            << "3. Удалить студента" "\n"
            << "4. Вернуться в главное меню" "\n"
            << "Выберите номер действия : " "\n";
        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 4) break;

        if (choice == 1) {
            if (groups.empty()) {
                cout << "надо создать группу " "\n";
                continue;
            }
            Student s;
            cout << "введите ID студента ";
            getline(cin, s.id);
            if (findStudentById(s.id) != Students.end()) {
                cout << "такого ID нет" "\n";
                continue;
            }
            cout << "Введите ФИО студента: ";
            getline(cin, s.name);
            cout << "Доступные группы:" "\n";
            for (const auto& g : groups) cout << "- " << g << "\n";
            cout << "Введите группу студента: ";
            getline(cin, s.groupname);

            if (findGroup(s.groupname) == groups.end()) {
                cout << "такой  группы нет" "\n";
            }
            else {
                Students.push_back(s);
                cout << "студент добавлен" "\n";
            }
        }
        else if (choice == 2) {
            cout << "введите ID студента что-бы изменить: ";
            string id;
            getline(cin, id);
            auto it = findStudentById(id);
            if (it == Students.end()) {
                cout << "такого студента нет" "\n";
                continue;
            }
            cout << "Текущее ФИО: " << it->name << ". Введите новое ФИО: ";
            getline(cin, it->name);
            cout << "Текущая группа: " << it->groupname << ". Введите новую группу: ";
            string newgroup;
            getline(cin, newgroup);
            if (findGroup(newgroup) == groups.end()) {
                cout << "такой группы нет" "\n";
            }
            else {
                it->groupname = newgroup;
                cout << "инфа о студенте обнавилась" "\n";
            }
        }
        else if (choice == 3) {
            cout << "Введите ID студента для удаления: ";
            string id;
            getline(cin, id);
            auto it = findStudentById(id);
            if (it == Students.end()) {
                cout << "такого студента нет" "\n";
            }
            else {
                Students.erase(it);
                cout << "студентт удалился" "\n";
            }
        }
    }
}
void manageGroupsMenu() {
    while (true) {
        cout << "меню для управления группами" "\n"
            << "1. Добавить группу" "\n"
            << "2. Изменить название группы" "\n"
            << "3. Удалить группу" "\n"
            << "4. Вернуться в главное меню" "\n"
            << "Выберите действие: ";
        int choice;
        cin >> choice;
        cin.ignore();
        if (choice == 4) break;
        if (choice == 1) {
            cout << "Введите название новой группы: ";
            string groupname;
            getline(cin, groupname);
            if (findGroup(groupname) != groups.end()) {
                cout << "Ошибка: Такая группа уже существует." "\n";
            }
            else {
                groups.push_back(groupname);
                cout << "Группа успешно добавлена." "\n";
            }
        }
        else if (choice == 2) {
            cout << "Введите название группы для изменения: ";
            string oldname;
            getline(cin, oldname);
            auto it = findGroup(oldname);
            if (it == groups.end()) {
                cout << "Группа не найдена.\n";
                continue;
            }
            cout << "Введите новое название группы: ";
            string newname;
            getline(cin, newname);
            if (findGroup(newname) != groups.end()) {
                cout << "Ошибка: Группа с таким названием уже существует." "\n";
                continue;
            }
            for (auto& s : Students) {
                if (s.groupname == oldname) {
                    s.groupname = newname;
                }
            }
            *it = newname;
            cout << "название группы изменилось" "\n";
        }
        else if (choice == 3) {
            cout << "введите название группы что бы её удалить " "\n";
            string groupname;
            getline(cin, groupname);
            auto it = findGroup(groupname);
            if (it == groups.end()) {
                cout << "такой группы нет " "\n";
            }
            else if (hasStudentsInGroup(groupname)) {
                cout << "группу нельзя удалить в ней студенты" "n";
            }
            else {
                groups.erase(it);
                cout << "группа удалилась" "\n";
            }
        }
    }
}
void addGradesMenu() {
    cout << "введите ID студента для оценки ";
    string id;
    cin.ignore();
    getline(cin, id);
    auto it = findStudentById(id);
    if (it == Students.end()) {
        cout << "такого студента нет" "\n";
        return;
    }
    cout << "студент: " << it->name << " (группа: " << it->groupname << ")\n";
    cout << "текущие оценки: ";
    for (int g : it->grades) cout << g << " ";
    cout << "\n" "сколько оченок добавить";
    int count;
    cin >> count;
    cout << "введите " << count << " целых оценок через пробел: ";
    for (int i = 0; i < count; ++i) {
        int grade;
        cin >> grade;
        it->grades.push_back(grade);
    }
    cout << "оценки добавились" "\n";
}
void showAverageScoresMenu() {
    cout << "МЕНЮ ДЛЯ СР БАЛЛА  "
        << "1. Средний балл конкретного студента" "\n"
        << "2. Средний балл по группе" "\n"
        << "Выберете номер оппрации  ";
    int choice;
    cin >> choice;
    cin.ignore();
    if (choice == 1) {
        cout << "Введите ID студента: ";
        string id;
        getline(cin, id);
        auto it = findStudentById(id);
        if (it == Students.end()) {
            cout << "такого студента нет" "\n";
        }
        else if (it->grades.empty()) {
            cout << "У студента " << it->name << " еще нет оценок." "\n";
        }
        else {
            double sum = accumulate(it->grades.begin(), it->grades.end(), 0.0);
            cout << "ср балл студента " << it->name << ": "
                << fixed << setprecision(2) << (sum / it->grades.size()) << "\n";
        }
    }
    else if (choice == 2) {
        cout << "Введите название группы: ";
        string groupname;
        getline(cin, groupname);
        if (findGroup(groupname) == groups.end()) {
            cout << "Группа не найдена.\n";
            return;
        }
        double totalSum = 0;
        int totalGradesCount = 0;

        for (const auto& s : Students) {
            if (s.groupname == groupname && !s.grades.empty()) {
                totalSum += accumulate(s.grades.begin(), s.grades.end(), 0.0);
                totalGradesCount += s.grades.size();
            }
        }
        if (totalGradesCount == 0) {
            cout << "В группе " << groupname << " нет оценок или студентов" "\n";
        }
        else {
            cout << "Средний балл группы " << groupname << ": "
                << fixed << setprecision(2) << (totalSum / totalGradesCount) << "\n";
        }
    }
}
void showGroupStatisticsMenu() {
    cout << "ввведите имя группы для её статы ";
    string groupname;
    cin.ignore();
    getline(cin, groupname);
    if (findGroup(groupname) == groups.end()) {
        cout << "такой группы нет" "\n";
        return;
    }
    int excellent = 0;
    int good = 0;
    int satisfactory = 0;
    int failing = 0;
    int nogrades = 0;
    int totalStudentsInGroup = 0;
    for (const auto& s : Students) {
        if (s.groupname == groupname) {
            totalStudentsInGroup++;
            if (s.grades.empty()) {
                nogrades++;
                continue;
            }
        }
    }
  }

        bool hasTwo = false;
        int main(){
            SetConsoleCP(65001);
            SetConsoleOutputCP(65001);
            do {
                cout << "выбор меню" "\n";
                cout << "0. меню существующих групп их студентов и их оценок" "\n";
                cout << "1. Меню студентов" "\n";
                cout << "2. Мнею для управления группами" "\n";
                cout << "3. Меню для оценки сдудента" "\n";
                cout << "4. Меню для ср балла" "\n";
                cout << "5. Меню статистики группы" "\n";
                cout << "6. выход из программы" "\n";
                cout << "введите номер меню " "\n";
                cin >> a;
                if (a == 0) {
                    initDefaultData();
                }
                if (a == 1) {
                    manageStudentsMenu();
                }
                if (a == 2) {
                    manageGroupsMenu();
                }
                if (a == 3) {
                    addGradesMenu();
                }
                if (a == 4) {
                    showAverageScoresMenu();
                }
                if (a == 5) {
                    showGroupStatisticsMenu();
                }

            } while (a != 6);

}
   
