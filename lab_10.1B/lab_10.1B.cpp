#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>

using namespace std;

#pragma pack(push, 1)

enum Speciality { ITIS, ME, KN, FI, TN };
string speciality_str[] = { "Інформатика ",
                            "Математика та економіка", "Комп'ютерні науки",
                            "Фізика та інформатика", "Трудове навчання" };

struct Students
{
    string surname;
    int course;
    Speciality speciality;
    int grade_physics;
    int grade_math;
    union
    {
        int grade_nm;
        int grade_program;
        int grade_ped;
    };
};

#pragma pack(pop)

void Create(Students* S, const int N);
void count_math_grades(Students* S, int N, int& count_5, int& count_4, int& count_3);
void Print_students_with_5_in_physics_and_math(Students* S, const int N);
void Print(Students* S, const int N);

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int N;
    cout << "Введіть кількість студентів: "; cin >> N;

    Students* S = new Students[N];

    Create(S, N);
    Print(S, N);

    int count_5 = 0;
    int count_4 = 0;
    int count_3 = 0;
    count_math_grades(S, N, count_5, count_4, count_3);

    cout << "Кількість оцінок '5' з математики: " << count_5 << endl;
    cout << "Кількість оцінок '4' з математики: " << count_4 << endl;
    cout << "Кількість оцінок '3' з математики: " << count_3 << endl;

    cout << "\nСтуденти, які отримали '5' з фізики та математики:" << endl;
    Print_students_with_5_in_physics_and_math(S, N);;

    return 0;
}

void Create(Students* S, const int N)
{
    for (int i = 0; i < N; i++)
    {
        int speciality;
        cout << "Номер студента: " << i + 1 << endl;
        cin.get();
        cin.sync();
        cout << "Прізвище: "; getline(cin, S[i].surname); cout << endl;
        cout << "Курс: "; cin >> S[i].course; cout << endl;
        cout << "Спеціальність(0 - Інформатика, 1 - Математика та економіка, 2 - Комп'ютерні науки, ";
        cout << "\n3 - Фізика та інформатика, 4 - Трудове навчання): ";
        cin >> speciality;
        S[i].speciality = (Speciality)speciality;
        cout << "Оцінка з фізики: "; cin >> S[i].grade_physics; cout << endl;
        cout << "Оцінка з математики: "; cin >> S[i].grade_math; cout << endl;
        switch (S[i].speciality)
        {
        case KN:
            cout << "Оцінка з програмування: "; cin >> S[i].grade_program; cout << endl;
            break;
        case ITIS:
            cout << "Оцінка з чисельних методів: "; cin >> S[i].grade_nm; cout << endl;
            break;
        default:
            cout << "Оцінка з педагогіки: "; cin >> S[i].grade_ped; cout << endl;
            break;
        }
        cout << endl;
    }
}

void count_math_grades(Students* S, const int N, int& count_5, int& count_4, int& count_3)
{
    count_5 = 0;
    count_4 = 0;
    count_3 = 0;
 
    for (int i = 0; i < N; i++) {
        if (S[i].grade_math == 5) count_5++;
        else if (S[i].grade_math == 4) count_4++;
        else if (S[i].grade_math == 3) count_3++;
    }
}

void PrintStudentsWithFiveInMathAndPhysics(Students* S, const int N)
{
    for (int i = 0; i < N; i++)
    {
        if (S[i].grade_math == 5 && S[i].grade_physics == 5)
        {
            cout << S[i].surname << endl;
        }
    }
}

void Print(Students* S, const int N)
{
    cout << "======================================================================================================================================" << endl;
    cout << "|  №  |   Прізвище   | Курс |      Спеціальність      |  Фізика  |  Математика  |  Програмування  |  Чисельні методи  |  Педагогіка  |" << endl;
    cout << "--------------------------------------------------------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < N; i++)
    {
        cout << "| " << setw(3) << right << i + 1 << " ";
        cout << "| " << setw(13) << left << S[i].surname
            << "| " << setw(4) << right << S[i].course << " "
            << "| " << setw(24) << left << speciality_str[S[i].speciality]
            << "|  " << setw(7) << right << S[i].grade_physics << " "
            << "|  " << setw(11) << right << S[i].grade_math << " ";

        switch (S[i].speciality)
        {
        case KN:
            cout << "|" << setw(9) << S[i].grade_program << setw(9);
            cout << "|" << setw(9) << "-" << setw(11);
            cout << "|" << setw(8) << "-" << setw(7) << "|";
            break;
        case ITIS:
            cout << "|" << setw(9) << "-" << setw(9);
            cout << "|" << setw(9) << S[i].grade_nm << setw(11);
            cout << "|" << setw(8) << "-" << setw(7) << "|";
            break;
        default:
            cout << "|" << setw(9) << "-" << setw(9);
            cout << "|" << setw(9) << "-" << setw(11);
            cout << "|" << setw(8) << S[i].grade_ped << setw(7) << "|";
        }

        cout << endl;
    }
    cout << "======================================================================================================================================" << endl << endl;
}
