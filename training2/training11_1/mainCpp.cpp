#include <iostream>
#include <map>
#include <string>

using namespace std;

struct Student {
    string name;
    float middle_score;
    float final_score;

    Student(){}
    Student(const string& name, float middle_score, float final_score){
        this->name = name;
        this->middle_score = middle_score;
        this->final_score = final_score;
    }
};

int main() {
    int num_students;
    cout << "student number: ";
    cin >> num_students;

    map<string, Student> studentMap;

    for (int i = 0; i < num_students; i++) {
        string name;
        float middle_score, final_score;

        cout << "name: ";
        cin >> name;
        cout << "middle_score: ";
        cin >> middle_score;
        cout << "final_score: ";
        cin >> final_score;

        studentMap[name] = Student(name, middle_score, final_score);
    }

    for (const auto& pair : studentMap) {
        const Student& student = pair.second;
        cout << "name: " << student.name << ", middle_score: " << student.middle_score
                  << ", final_score: " << student.final_score << endl;
    }

    return 0;
}
