//Name: Nasif Shah
//ID: 201304650
//Course: CSCI 275
//Date: Jan 18th, 2018


#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <cstring>

using namespace std;

struct student_rec { long id;
                     string last, first;
                   };

struct enroll_rec  { long id, crn;
                     int  year, grade;
                   };

struct section_rec { long crn;
                     int  year;
                     string dept;
                     int  cnum, snum;
                     string building, room;
                   };

struct course_rec { string dept;
                    int num;
                    string name;
                  };

bool read_student(ifstream &f, student_rec &s);
bool read_enroll (ifstream &f, enroll_rec  &e);
bool read_section(ifstream &f, section_rec &s);
bool read_course (ifstream &f, course_rec  &c);

bool find_student(student_rec &student, long id);
bool find_CRN(section_rec &section, string dept, int snum, int cnum, int year);
bool find_Grade(enroll_rec &enroll, long crn, int year);

student_rec student;
section_rec number;
enroll_rec code;

int main()
{

    int course, section, year;
    string dept;


    cout << "Please enter the dept. code, section number, course number and the year\n";
    cin >> dept;
    cin >> section;
    cin >> course;
    cin >> year;


    cout << "     "  << year << "         " << dept << "    " << section << "\n";
    cout << "--------------------------------------------------------------------------------\n";
    cout << "  " << "   ID    " << "      NAMES         " << "               MARKS       " << "\n";



    find_CRN(number, dept, section, course, year);



    return 0;
}

bool find_CRN(section_rec &section, string dept, int snum, int cnum, int year)
{


    ifstream file("section.txt");
    if(!file)
    {
        cout << "File is missing!!!\n";
        return false;
    }


    while (read_section(file, section))
    {
        if(section.dept==dept && section.snum==snum && section.cnum==cnum && section.year==year)
        {


            find_Grade(code, section.crn, section.year);
            return true;
        }

    }
}

bool find_Grade(enroll_rec &enroll, long crn, int year)
{
    int counter = 0;
    double Total = 0, Average;

    ifstream file("enroll.txt");
    if(!file)
    {
       cout << "The file is missing\n";
       return false;
    }

    while(read_enroll(file, enroll))
    {
        student_rec student_result;
        enroll_rec enroll_result;
        if(enroll.crn==crn && enroll.year==year)
        {
            enroll_result.id = enroll.id;
            enroll_result.grade = enroll.grade;

            if(!find_student(student_result, enroll_result.id))
            {
                cout << "Record not found!!!\n";
            }
            else
            {
                cout << "  " << enroll_result.id << " " << student_result.first << " " << student_result.last << "                   " << enroll_result.grade <<" \n";

                Total = Total + enroll_result.grade;
                counter++;

            }


        }

    }

    Average = Total/counter;

    cout << "\n\n The Average = " << Average << "\n";
    return true;
}


bool find_student(student_rec &student, long id)
{
   ifstream file("student.txt");

   if (!file) {
      cout << "Student file not found!" << endl;
      return false;
   }

   while (read_student(file, student)) {
      if (student.id == id) return true;
   }

   file.close();
   return false;
}

bool read_student(ifstream &f, student_rec &s)
{
   char comma;
   if (f.eof()) return false;
   f >> s.id >> comma;
   getline(f, s.last, ',');
   getline(f, s.first);
   return true;
}

bool read_enroll(ifstream &f, enroll_rec &e)
{
    char comma, str[10];
    if (f.eof()) return false;
    f >> e.id >> comma >> e.crn >> comma >> e.year;
    f.getline(str, 10);
    if (strlen(str) > 1) e.grade = atoi(&str[1]);
    else e.grade = -1;
    return true;
}

bool read_section(ifstream &f, section_rec &s)
{
    char comma;
    if (f.eof()) return false;
    f >> s.crn >> comma >> s.year >> comma;

    getline(f, s.dept, ',');
    f >> s.cnum >> comma >> s.snum >> comma;
    if (comma == ',') {
        getline(f, s.building, ',');
        getline(f, s.room);
    } else {
        s.building[0] = s.room[0] = '\0';
    }


    return true;
}

bool read_course(ifstream &f, course_rec &c)
{
    char comma;
    getline(f, c.dept, ',');
    if (f.eof()) return false;
    f >> c.num >> comma;
    getline(f, c.name);
    return true;
}
