#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;

class User
{
protected:

string username;
string password;
string type;
fstream file1, file2, file3;

public:

User()
{
    username = "";
    password = "";
    type = "";
}

virtual string getType()
{
    return type;
}

virtual void user_menu() = 0;

virtual bool login(int x)
{
    string line;
    string start = username;
    string pass1;
    if (x == 1)
    {
        file2.open("file2.txt", ios::in);
        file2.seekg(0, ios::beg);
        while (getline(file2, line))
        {
            pass1 = line;
        }
        file2.close();
    }

    else if (x == 2)
    {
        file3.open("file3.txt", ios::in);
        file3.seekg(0, ios::beg);
        while (getline(file3, line))
        {
            pass1 = line;
        }
        file3.close();
    }
    int i = 0;
    string input1, input2;
    cout<<"Enter your username: ";
    cin>>input1;
    cout<<"Enter your password: ";
    cin>>input2;

    while (input1 != start || input2 != pass1)
    {
        if (i == 2)
        {
            cout<<"Too many failed attempts. Try again later\n";
            return 0;
        }
        i++;
        cout<<"Incorrect credentials, re-enter correct credentials\n";
        cout<<"Enter your username: ";
        cin>>input1;
        cout<<"Enter your password: ";
        cin>>input2;

    }

    password = pass1;
    return 1;
}

};


class Student : public User
{

protected: 

string roll;
string program;

public:

Student()
{
    username = "student1";
    password = "1234";
    type = "Student";
    roll = "abc1234";
    program = "CS";
}

Student(string a, string b, string c, string d)
{
    username = a;
    password = b;
    roll = c;
    program = d;
    type = "Student";
}

void user_menu() override
{
    bool flag = 0;
    while (!flag)
    {
        int x;
        cout<<"Welcome "<<type;
        cout<<"\nWould you like to:\n1.Mark Attendance\n2.View Attendance\n";
        cin>>x;
        system("CLS");

        if (x == 1)
        {
            mark();
        }

        else if (x == 2)
        {
            view();
        }

        else if (x >= 3)
        {    
            flag = 1;
            return;
        }
            
    }
}

void view()
{
    file1.open("file1.txt", ios::in);
    file1.seekg(0, ios::beg);
    string start = username;
    string end = "student";
    string line;
    bool flag = 0;

    while (getline(file1, line))
    {
        int pos_start = line.find(start);
        int pos_end = line.find(end);

        if (pos_start != string::npos)
        {
            flag = 1;
            continue;
        }
        if (pos_end != string::npos && flag == 1)
        {
            flag = 0;
            continue;
        }

        if (flag)
            cout<<line<<endl;
    }

    file1.close();

    int y;
    cout<<"Press 1 to continue\n";
    cin>>y;
    system("CLS");
}

void mark()
{
    file1.open("file1.txt", ios::in);
    file1.seekg(0, ios::beg);
    ofstream tempfile("temp.txt");
    string start = username;
    string end = "student2";
    string line;
    string new_line;
    bool flag = 0;
    int x, y, z;
    char a;
    // cout<<"Enter attendance in following format: DD/MM/YYYY - P\n";
    // cin.ignore();
    // getline(cin, new_line);
    cout<<"Enter date: ";
//    cin>>x;
    while (!(cin >> x) || (x <= 0 || x > 31)) 
    { 
        std::cin.clear(); 
        std::cin.ignore();
        std::cout << "Invalid input; please re-enter.\n"; 
    } 
    cout<<"Enter Month (in MM): ";
//    cin>>y;
    while (!(cin >> y) || (y <= 0 || y > 12)) 
    { 
        std::cin.clear(); 
        std::cin.ignore();
        std::cout << "Invalid input; please re-enter.\n"; 
    } 
    cout<<"Enter Year: ";
//    cin>>z;
    while (!(cin >> z) || (z <= 1900 || z >= 2023)) 
    { 
        std::cin.clear(); 
        std::cin.ignore();
        std::cout << "Invalid input; please re-enter.\n"; 
    } 
    cout<<"Press A if absent or P if present: ";
    cin>>a;

    if (a != 'A')
    {
        if (a != 'P')
        {
            cout<<"Enter correct attendance\n";
            return;
        }
    }

    while (getline(file1, line))
    {
        int pos_start = line.find(start);
        int pos_end = line.find(end);

        if (pos_start != string::npos)
        {
            flag = 1;
        }
        if (pos_end != string::npos && flag == 1)
        {
            tempfile<<x<<"/"<<y<<"/"<<z<<"/"<<" - "<<a<<endl;
            flag = 0;
        }

        tempfile<<line<<endl;
    }

    file1.close();
    tempfile.close();
    remove("file1.txt");
    rename("temp.txt", "file1.txt");

    int i;
    cout<<"Press 1 to continue\n";
    cin>>i;
    system("CLS");
}

};

class Admin : public User
{

private:

Student *s1[5];

public:

Admin()
{
    for (int i=0; i<5; i++)
    {
        s1[i] = NULL;
    }
    username = "admin";
    password = "admin@123";
    type = "Admin";
}

void register_student()
{
    string a, b, c, d;
    cout<<"Enter Student name: \n";
    cin>>a;
    cout<<"Enter password:\n";
    cin>>b;
    cout<<"Enter roll number\n";
    cin>>c;
    cout<<"Enter program\n";
    cin>>d;

    for (int i=0; i<5; i++)
    {
        if (s1[i] == NULL)
        {
            s1[i] = new Student(a,b,c,d);
            break;
        }

        else
        {
            cout<<"Number of students full. Kindly delete some then try again\n";
            return;
        }
    }

    file1.open("file1.txt", ios::app);
    file1<<c<<" "<<a<<endl;
    file1.close();

    int y;
    cout<<"Press 1 to continue\n";
    cin>>y;
    system("CLS");
}

void user_menu() override
{
    int x;
    while (x != -1)
    {
        cout<<"Welcome "<<type;
        cout<<" Would you like to:\n1.Register new student\n2.Delete a student's attendance record\n3.Delete all students' attendance record";
        cout<<"\n4.View all students' attendance record\n5.Search student\n6.Change admin password\n";
        cin>>x;
        system("CLS");
        switch (x)
        {
            case 1: 
                register_student();
                break;
            case 2:
                delete_student();
                break;
            case 3:
                delete_all();
                break;
            case 4: 
                view_all();
                break;
            case 5: 
                view_roll();
                break;
            case 6:
                change_password();
                break;
            default:
                x = -1;
                break;
        }
    }
}

void delete_student()
{
    file1.open("file1.txt", ios::in);
    file1.seekg(0, ios::beg);
    ofstream tempfile("temp.txt");
    string start;
    string end = "student";
    string line;
    string new_line = " ";
    bool flag = 0;

    cout<<"Enter Student Roll Number:\n";
    cin>>start;

    while (getline(file1, line))
    {
        int pos_start = line.find(start);
        int pos_end = line.find(end);

        if (pos_start != string::npos)
        {
            flag = 1;
            continue;
        }
        if (pos_end != string::npos && flag == 1)
        {
            flag = 0;
        }

        if (!flag)
            tempfile<<line<<endl;
    }

    file1.close();
    tempfile.close();
    remove("file1.txt");
    rename("temp.txt", "file1.txt");

    int y;
    cout<<"Press 1 to continue\n";
    cin>>y;
    system("CLS");
}

void delete_all()
{
    file1.open("file1.txt", ios::out | ios::trunc);
    file1.close();

    int y;
    cout<<"Press 1 to continue\n";
    cin>>y;
    system("CLS");
}

void view_all()
{
    file1.open("file1.txt", ios::in);
    file1.seekg(0, ios::beg);
    string line;
    while (getline(file1, line))
    {
        cout<<line<<endl;
    }
    file1.close();

    int y;
    cout<<"Press 1 to continue\n";
    cin>>y;
    system("CLS");
}

void view_roll()
{
    file1.open("file1.txt", ios::in);
    file1.seekg(0, ios::beg);
    string start;
    string end = "student";
    string line;
    bool flag = 0;


    int x;

    cout<<"Would you like to search by roll number or name:\n1.Roll Number\n2.Name\n";
    cin>>x;
    system("CLS");

    if (x == 1)
    {
        cout<<"Enter roll number\n";
        cin>>start;
    }

    else if (x == 2)
    {
        cout<<"Enter name\n";
        cin>>start;
    }

    while (getline(file1, line))
    {
        int pos_start = line.find(start);
        int pos_end = line.find(end);

        if (pos_start != string::npos)
        {
            flag = 1;
            continue;
        }
        if (pos_end != string::npos && flag == 1)
        {
            flag = 0;
            continue;
        }

        if (flag)
            cout<<line<<endl;
    }

    file1.close();

    int y;
    cout<<"Press 1 to continue\n";
    cin>>y;
    system("CLS");
}

void change_password()
{
    string a;
    cout<<"Re-enter password\n";
    cin>>a;

    if (a != password)
    {
        cout<<"Incorrect Password\n";
        return;
    }

    cout<<"Enter new password\n";
    cin>>a;
    file2.open("file2.txt", ios::out);
    file2<<username<<endl<<a;
    password = a;
    file2.close();

    int y;
    cout<<"Press 1 to continue\n";
    cin>>y;
    system("CLS");
}
};


class Menu
{

private: 
User* u1;

public:

Menu()
{
    u1 = NULL;
}

void display_menu()
{
    int x=0;
    bool flag = 0;
    while (!flag)
    {
        cout<<"Are you:\n1.Admin\n2.Student\n";
        cin>>x;
        
        if (x >= 3)
        {
            flag == 1;
            return;
        }
        
        if (x == 1)
        {
            u1 = new Admin;
        }

        else if (x == 2)
        {
            u1 = new Student;
        }


        if (u1->login(x) == 0)
        {
            return;
        }
        

        u1->user_menu();
    }
}
};

int main()
{
    Menu m;
    m.display_menu();

return 0;
}