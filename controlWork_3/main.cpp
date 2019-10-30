#include <iostream>
#include <sstream>
#include <stdio.h>
#include <unordered_map>
#include <map>
#include <vector>

using namespace std;

struct Student {
    string firstName;
    string lastName;
    int age;
    int group;

    bool operator==(const Student& st) const {
        if ( (this->firstName == st.firstName) &&
             (this->lastName == st.lastName) &&
             (this->age == st.age) &&
             (this->group == st.group) )
            return true;
        return false;
    }

    bool operator<(const Student& st) const {
        if (this->firstName < st.firstName)
             return true;
        if ( (this->firstName == st.firstName) && (this->lastName < st.lastName) )
             return true;
        if ( (this->firstName == st.firstName) && (this->lastName == st.lastName) && (this->age < st.age) )
            return true;
        if ( (this->firstName == st.firstName) && (this->lastName == st.lastName) && (this->age == st.age) && (this->group < st.group) )
            return true;
        return false;
    }

 /* ostream& operator<<(const Student& st) {
        cout << st.firstName << " " << st.lastName << " " << st.age << " " << st.group;
        return cout;
    } */
};


int main()
{
    unordered_map<string, map<int, vector<Student>>> students;
    string str;
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        while (getline(cin, str)) {
            istringstream str_tmp(str);
            string command;
            str_tmp >> command;

            if (command == "add") {
                Student st;
                str_tmp >> st.firstName >> st.lastName >> st.age >> st.group;
                students[st.firstName][st.age].push_back(st); //обращаемся по ключу st.firstName, значение получаем map
            }                                                 //обращаемся по ключу st.age, значение получаем vector

            if ( (command == "find") && (!students.empty()) ) {
                string st;
                int age1, age2;
                str_tmp >> command >> age1 >> command >> age2 >> command >> command >> command >> command >> st;
                map<int, vector<Student>>& intToVec = students[st];
                map<int, vector<Student>>::iterator it1 = intToVec.lower_bound(age1);
                map<int, vector<Student>>::iterator it2 = intToVec.lower_bound(age2);

                for (map<int, vector<Student>>::iterator it = it1; it != it2; it++) {
                    vector<Student>& vec = it->second; //итератор указывает на пару <ключ,значение>, нам нужно значение (вектор)
                    for (auto i = 0; i < vec.size(); i++)
                            cout << vec[i].firstName << " " << vec[i].lastName << " " << vec[i].age << " " << vec[i].group;
                    }
            }
        }
    }

    return 0;
}

