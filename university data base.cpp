#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

class student {
  public:
    int age, id;
    char name[10];
};

void addStudent(){
    ofstream f("student.txt", ios::out | ios::app | ios::ate);
    student s1;
    char c;
    do {
       cout << "Enter ID: ";
       cin >> s1.id;
       cout << "Enter Name: ";
       cin >> s1.name;
       cout << "Enter Age: ";
       cin >> s1.age;
       f.write((char*) &s1, sizeof(s1));
       cout << "Do you want to enter again? (Y/N): ";
       cin >> c;
    } while(tolower(c) == 'y');
    f.close();
}

void readAllStudents(){
    student s1;
    ifstream in;
    in.open("student.txt", ios::in);
    if(in.is_open())
    {
        cout << "ID\tName\tAge\n\n";
        in.read((char*)& s1, sizeof(s1));
        while(!in.eof()){
          cout << s1.id << "\t" << s1.name << "\t" << s1.age << "\n";
          in.read((char*)& s1, sizeof(s1));
        }
        in.close();
    }
    else cout << "Can't open the specified file...\n";
}

void searchByID(){
    student s1;
    int ID;
    cout << "Enter an ID to search: ";
    cin >> ID;
    ifstream in;
    in.open("student.txt", ios::in);
    if(in.is_open())
    {
        bool exist = false;
        in.read((char*)& s1, sizeof(s1));
        while(!in.eof()){
          if(ID == s1.id){
            cout << "ID\tName\tAge\n\n";
            cout << s1.id << "\t" << s1.name << "\t" << s1.age << "\n";
            exist = true;
            break;
          }
          in.read((char*)& s1, sizeof(s1));
        }
        if(!exist) cout << "Not exist....\n";
        in.close();
    }
    else cout << "Can't open the specified file...\n";
}

void searchByName(){
    student s1;
    char Name[10];
    cout << "Enter a name to search: ";
    cin >> Name;
    ifstream in;
    in.open("student.txt", ios::in);
    if(in.is_open())
    {
        bool exist = false;
        in.read((char*)& s1, sizeof(s1));
        while(!in.eof()){
          if(strcmp(Name, s1.name) == 0){
            cout << "ID\tName\tAge\n\n";
            cout << s1.id << "\t" << s1.name << "\t" << s1.age << "\n";
            exist = true;
            break;
          }
          in.read((char*)& s1, sizeof(s1));
        }
        if(!exist) cout << "Not exist....\n";
        in.close();
    }
    else cout << "Can't open the specified file...\n";
}

void updateStudent(){
    student s1;
    char Name[10];
    cout << "Enter a name to edit his data: ";
    cin >> Name;
    fstream in;
    in.open("student.txt", ios::in | ios::out);
    if(in.is_open())
    {
        bool exist = false;
        in.read((char*)& s1, sizeof(s1));
        while(!in.eof())
        {
          if(strcmp(Name, s1.name) == 0)
          {
              int ch;
              char c;
              f:
              cout << "Choose what you need to edit :\n";
              cout << "1) ID\n2) Name\n3) Age\n\t:";
              cin >> ch;
              switch(ch)
              {
                case 1:
                  cout << "Enter the new ID: ";
                  cin >> s1.id;
                  break;
                case 2:
                  cout << "Enter the new Name: ";
                  cin >> s1.name;
                  break;
                case 3:
                  cout << "Enter the new Age: ";
                  cin >> s1.age;
                  break;
                default:
                  cout << "Error...\n";
                  goto f;
              }
              cout << "Do you want to edit more? (Y|N): ";
              cin >> c;
              if(tolower(c) != 'n') goto f;
              int curpos = in.tellg();
              in.seekp(curpos - sizeof(s1), ios::beg);
              in.write((char*) &s1, sizeof(s1));
              in.seekg(curpos - sizeof(s1), ios::beg);
              in.read((char*) &s1, sizeof(s1));
              cout << "ID\tName\tAge\n\n";
              cout << s1.id << "\t" << s1.name << "\t" << s1.age << "\n";
              exist = true;
              break;
          }
          in.read((char*)& s1, sizeof(s1));
        }
        if(!exist) cout << "Not exist....\n";
        in.close();
    }
    else cout << "Can't open the specified file...\n";
}

void deleteStudent(){
    ifstream in("student.txt", ios::in);
    ofstream out("temp.txt", ios::out);
    student s1;
    cout << "Enter a name to delete: ";
    char Name[10];
    cin >> Name;
    if(in.is_open())
    {
        bool exist = false;
        
        in.read((char*)& s1, sizeof(s1));
        while(!in.eof()){
          if(strcmp(Name, s1.name) != 0){
            out.write((char*) &s1, sizeof(s1));
          }
          else exist = true;
          in.read((char*)& s1, sizeof(s1));
        }
        in.close();
        out.close();
        remove("student.txt");
        rename("temp.txt", "student.txt");
        if(!exist) cout << "Not exist....\n";
    }
    else cout << "Can't open the specified file...\n";
}

int main()
{   
    cout << "\n";
    int opt;
    do {
        start:
        cout << "\nchoose an option :\n";
        cout << "1] add student\n2] print all students\n3] search\n4] edit student data\n5] delete student\n0] Exit\n";
        cin >> opt;
        switch(opt)
        {
            case 1:
              addStudent();
              break;
            case 2:
              readAllStudents();
              break;
            case 3:
              int ch;
              ff:
              cout << "by Name or ID :\n";
              cout << "1- by name\n2- by ID\nenter choice: ";
              cin >> ch;
              if(ch == 1) searchByName();
              else if(ch == 2) searchByID();
              else {
                cout << "wrong!!\n";
                goto ff;
              }
              break;
            case 4:
              updateStudent();
              break;
            case 5:
              deleteStudent();
              break;
            case 0:
              return 0;
            default:
              cout << "Wrong choice...\nchoose again\n";
              goto start;
        }
    }while(opt != 0);

  return cout << "\n", 0;
}