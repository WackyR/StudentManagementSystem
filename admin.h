const int MAX_ADMIN = 1;
const int MAX_STUDENTS = 50;
using namespace std;
void main_menu();
class MasterClass{
    public:
    virtual void login()=0;
    virtual void searchStudent()=0;
    virtual void deletelogin()=0;
};
class Admin : public MasterClass{
public:
    string username;
    string password;
    virtual void admin_options();
    void login();
    virtual void registerAdmin();
    virtual void forgotPassword();
    void deletelogin();
    virtual void addStudent();
    virtual void deleteStudent();
    virtual void updateStudent();
    void searchStudent();
    int countStudents();
};
void Admin::admin_options() {
    MasterClass* ptr3 = new Admin;
    int choice;
    cout << "\n\n\n\n\n\n\n\t\t\t\tChoose an option" << endl;
    cout << "\t\t\t\t1. Add student" << endl;
    cout << "\t\t\t\t2. Delete student" << endl;
    cout << "\t\t\t\t3. Update student" << endl;
    cout << "\t\t\t\t4. Search student" << endl;
    cout << "\t\t\t\t5. Delete login" << endl;
    cout << "\t\t\t\t6. Exit" << endl;
    cout << "\t\t\t\t7. Return to main menu" << endl;
    cout << "\t\t\t\tEnter choice: ";
    cin >> choice;
    cin.ignore();
    system("cls");

    while (choice != 6) {
        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                deleteStudent();
                break;
            case 3:
                updateStudent();
                break;
            case 4:
                ptr3->searchStudent();
                break;
            case 5:
                ptr3->deletelogin(); // Assuming deletelogin() function exists
                break;
            case 7:
                main_menu();
            default:
                cout << "Invalid choice!" << endl;
        }

        cout << "\n\n\n\n\n\n\n\t\t\t\tChoose an option" << endl; // Reprompt for choice after each action
        cout << "\t\t\t\t1. Add student" << endl;
        cout << "\t\t\t\t2. Delete student" << endl;
        cout << "\t\t\t\t3. Update student" << endl;
        cout << "\t\t\t\t4. Search student" << endl;
        cout << "\t\t\t\t5. Delete login" << endl;
        cout << "\t\t\t\t6. Exit" << endl;
        cout << "\t\t\t\t7. Return to main menu" << endl;
        
        cout << "\t\t\t\tEnter choice: ";
        cin >> choice;
        cin.ignore();
        system("cls");
    }

    // Exit the program when choice is 6
    cout << "Exiting program..." << endl;
    exit(0); // Use exit(0) to indicate successful termination
}

void Admin::login()
{
    int login_success = 0;
    string username, password;
    cout << "Enter username: ";
    getline(cin, username);
    cout << "Enter password: ";
    getline(cin, password);
    system("cls");
    ifstream file("admin.txt");
    string line;
    string user, pass;
    while (getline(file, line))
    {
        user = line.substr(0, line.find(','));
        pass = line.substr(line.find(',') + 1);
        if (user == username && pass == password)
        {
            cout << "Login successful!" << endl;
            login_success = 1;
            file.close();
            break;
        }
    }
    if (user != username || pass != password)
    {
        cout << "Invalid username or password!" << endl;
        login_success = 0;
    }
    if (login_success == 1)
    {
        Admin::admin_options();
    }
}
void Admin::registerAdmin()
{
    string username, password;

    // Check if admin already exists
    ifstream infile("admin.txt");
    if (infile.is_open() && infile.peek() != ifstream::traits_type::eof()) {
        cout << "An admin is already registered." << endl;
        infile.close();
        return;
    }
    infile.close();

    // Register new admin
    cout << "Enter username: ";
    getline(cin, username);
    cout << "Enter password: ";
    getline(cin, password);
    ofstream outfile("admin.txt", ios::app);
    outfile << username << "," << password << endl;
    cout << "Admin registered successfully!" << endl;
    outfile.close();

    // Clear screen
    system("cls");
}
void Admin::forgotPassword()
{
    string username;
    cout << "Enter username: ";
    cin >> username;
    ifstream file("admin.txt");
    string line;
    string user, pass;
    while (getline(file, line))
    {
        user = line.substr(0, line.find(','));
        pass = line.substr(line.find(',') + 1);
        if (user == username)
        {
            cout << "Your password is: " << pass << endl;
            break;
        }
    }
    if (user != username)
    {
        cout << "Invalid username!" << endl;
    }
}
void Admin::deletelogin()
{
    string username;
    cout << "Enter username: ";
    getline(cin, username);

    ifstream infile("admin.txt");
    if (!infile.is_open()) {
        cout << "Unable to open file." << endl;
        return;
    }

    string line;
    vector<string> lines;
    bool found = false;

    // Read all lines and store them, except the one to be deleted
    while (getline(infile, line)) {
        string user = line.substr(0, line.find(','));
        if (user != username) {
            lines.push_back(line);
        } else {
            found = true;
        }
    }
    infile.close();

    // Write the remaining lines back to the file
    if (found) {
        ofstream outfile("admin.txt");
        for (const auto& l : lines) {
            outfile << l << endl;
        }
        outfile.close();
        cout << "Account deleted successfully!" << endl;
    } else {
        cout << "Invalid username!" << endl;
    }
}
void Admin::addStudent() {
    int studentCount = countStudents(); 
    if (studentCount >= 50) {
        cout << "Maximum student capacity (50) reached. Cannot add more students." << endl;
        return;
    }

    string name, rollno, department, semester;
    cout << "Enter name: ";
    getline(cin, name);
    cout << "Enter rollno: ";
    getline(cin, rollno);

    regex rollnoPattern("^FA\\d{2}-B(CE|EE)-\\d{3}$");
    if (!regex_match(rollno, rollnoPattern)) {
        cout << "Invalid rollno! Roll number should be in the form (FAXX-BCE-XXX or FAXX-BEE-XXX)" << endl;
        return;
    }

    ifstream infile("student.txt");
    string line;
    bool duplicateFound = false;
    while (getline(infile, line)) {
        size_t pos = line.find(',');
        string existingRollno = line.substr(pos + 1, rollno.size());
        if (existingRollno == rollno) {
            duplicateFound = true;
            break;
        }
    }
    infile.close();

    if (duplicateFound) {
        cout << "Duplicate roll number! A student with this roll number already exists." << endl;
        return;
    }

    cout << "Enter department: ";  
    getline(cin, department);
    string rollnoDepartment = rollno.substr(6, 2); // Extracts "CE" or "EE"

    // Validate department and ensure it matches the roll number
    if ((department != "CE" && department != "EE") || (rollnoDepartment != department)) {
        cout << "Invalid department! Department should be either CE or EE and match the roll number." << endl;
        return;
    }

    cout << "Enter semester: ";
    getline(cin, semester);
    if (semester != "1" && semester != "2" && semester != "3" && semester != "4" && semester != "5" && semester != "6" && semester != "7" && semester != "8") {
        cout << "Invalid semester! Semester should be between 1 and 8" << endl;
        return;
    }

    ofstream outfile("student.txt", ios::app);
    outfile << name << "," << rollno << "," << department << "," << semester << endl;
    outfile.close();

    cout << "Student added successfully!" << endl;

    char choice;
    do {
        cout << "Do you want to add another student (y/n)? ";
        cin >> choice;
        cin.ignore();
        choice = tolower(choice); 
    } while (choice != 'y' && choice != 'n');

    if (choice == 'n') {
        cout << "Student addition completed." << endl;
        system("cls");
        admin_options();
    } else {
        addStudent();
    }
}

int Admin::countStudents() {
  ifstream file("student.txt");

  if (!file.is_open()) {
    return 0; 
  }

  int count = 0;
  string line;
  while (getline(file, line)) {
    count++;
  }

  file.close();
  return count;
}
void Admin::updateStudent() {
    string rollno;
    char choice;

    do {
        cout << "Enter rollno of the student to update: ";
        getline(cin, rollno);
        cout << "You entered " << rollno << endl;

        ifstream file("student.txt");
        if (!file.is_open()) {
            cerr << "Error opening student.txt file!" << endl;
            return;
        }

        ofstream tempFile("temp.txt");
        if (!tempFile.is_open()) {
            cerr << "Error opening temp.txt file!" << endl;
            file.close(); // Close the file before returning
            return;
        }

        string line;
        bool found = false;

        while (getline(file, line)) {
            stringstream ss(line);
            string name, roll, department, semester;

            getline(ss, name, ',');
            getline(ss, roll, ',');
            getline(ss, department, ',');
            getline(ss, semester, ',');

            if (roll == rollno) {
                found = true;
                cout << "Enter new name: ";
                getline(cin, name);
                cout << "Enter new rollno: ";
                string newRoll;
                getline(cin, newRoll);
                regex rollnoPattern("^FA\\d{2}-B(CE|EE)-\\d{3}$");
                if (!regex_match(rollno, rollnoPattern)) {
                    cout << "Invalid rollno! Roll number should be in the form (FAXX-BCE-XXX or FAXX-BEE-XXX)" << endl;
                    file.close();
                    tempFile.close();
                    return; // Return a non-zero value to indicate an error
                }
                cout << "Enter new department: ";
                getline(cin, department);
                string rollnoDepartment = rollno.substr(6, 2); // Extracts "CE" or "EE"

    // Validate department and ensure it matches the roll number
                if ((department != "CE" && department != "EE") || (rollnoDepartment != department)) {
                    cout << "Invalid department! Department should be either CE or EE and match the roll number." << endl;
                    file.close();
                    tempFile.close();
                    return; // Return a non-zero value to indicate an error
                    }
                cout << "Enter new semester: ";
                getline(cin, semester);
                if (semester != "1" && semester != "2" && semester != "3" && semester != "4" && semester != "5" && semester != "6" && semester != "7" && semester != "8") {
                    cout << "Invalid semester! Semester should be between 1 and 8" << endl;
                    tempFile << name << "," << roll << "," << department << "," << semester << endl;
                    file.close();
                    tempFile.close();
                    return;
                }

                // Write updated student data to the temporary file
                tempFile << name << "," << newRoll << "," << department << "," << semester << endl;
                cout << "Student updated successfully!" << endl;
            } else {
                // Write unchanged student data to the temporary file
                tempFile << name << "," << roll << "," << department << "," << semester << endl;
            }
        }

        // Ensure files are closed before attempting to delete/rename
        file.close();
        tempFile.close();

        if (found) {
            // Attempt to remove the old student.txt file
            if (remove("student.txt") != 0) {
                perror("Error deleting old student.txt");
            } else {
                cout << "Old student.txt deleted successfully" << endl;

                // Attempt to rename the temp.txt file to student.txt
                if (rename("temp.txt", "student.txt") != 0) {
                    perror("Error renaming temp.txt to student.txt");
                } else {
                    cout << "temp.txt renamed to student.txt successfully" << endl;
                }
            }
        } else {
            cout << "Invalid rollno!" << endl;
            // Remove the temporary file if no matching record is found
            if (remove("temp.txt") != 0) {
                perror("Error deleting temp.txt");
            }
        }

        // Ask the user if they want to update another student
        do {
            cout << "Do you want to update another student (y/n)? ";
            cin >> choice;
            cin.ignore(); // Consume the newline character after the 'y' or 'n'
            choice = tolower(choice);
        } while (choice != 'y' && choice != 'n');

    } while (choice == 'y');

    // Return to admin menu after updates are done
    admin_options();
}


void Admin::deleteStudent() {
    string rollno;
    char choice;
    bool deleted;

    do {
        cout << "Enter rollno of the student to delete: ";
        getline(cin, rollno);

        ifstream file("student.txt");
        if (!file.is_open()) {
            cerr << "Error opening student.txt file!" << endl;
            return;
        }

        ofstream tempFile("temp.txt");
        if (!tempFile.is_open()) {
            cerr << "Error opening temp.txt file!" << endl;
            return;
        }

        string line;
        bool found = false;

        while (getline(file, line)) {
            stringstream ss(line);
            string name, roll, department, semester;

            getline(ss, name, ',');
            getline(ss, roll, ',');
            getline(ss, department, ',');
            getline(ss, semester, ',');

            if (roll == rollno) {
                found = true;
                cout << "Student with rollno " << rollno << " deleted successfully!" << endl;
            } else {
                tempFile << name << "," << roll << "," << department << "," << semester << endl;
            }
        }

        file.close();
        tempFile.close();

        remove("student.txt");
        rename("temp.txt", "student.txt");

        if (!found) {
            cout << "Invalid rollno!" << endl;
        }

        // Ask the user if they want to delete another student
        do {
            cout << "Do you want to delete another student (y/n)? ";
            cin >> choice;
            cin.ignore(); // Consume the newline character after the 'y' or 'n'
        } while (choice != 'y' && choice != 'n');

    } while (choice == 'y');

    // Return to admin menu after deletions are done
    admin_options();
}

void Admin::searchStudent() {
  string rollno;
  char choice;

  do {
    cout << "Enter rollno of the student to search: ";
    getline(cin, rollno);

    ifstream file("student.txt");
    string line;
    string name, roll, department, semester;
    bool found = false;

    while (getline(file, line)) {
      name = line.substr(0, line.find(','));
      line = line.substr(line.find(',') + 1);
      roll = line.substr(0, line.find(','));
      line = line.substr(line.find(',') + 1);
      department = line.substr(0, line.find(','));
      semester = line.substr(line.find(',') + 1);

      if (roll == rollno) {
        cout << "Name: " << name << endl;
        cout << "Rollno: " << roll << endl;
        cout << "Department: " << department << endl;
        cout << "Semester: " << semester << endl;
        found = true;
        break;
      }
    }

    file.close();

    if (!found) {
      cout << "Invalid rollno!" << endl;
    }

    // Ask the user if they want to search for another student
    do {
      cout << "Do you want to search for another student (y/n)? ";
      cin >> choice;
      system("cls");
      cin.ignore(); // Consume the newline character
      choice = tolower(choice);
    } while (choice != 'y' && choice != 'n');

  } while (choice == 'y');

  // Return to admin menu after search is done
  admin_options();
}

class Teacher : public Admin
{
public:
    void teacher_options();
    void login();
    void registerTeacher();
    void forgotPassword() override;
    void deletelogin();
    void addStudentMarks();
    void updateStudentMarks();
    void addAttendance();
    void updateAttendance();
    void searchStudent();
    void viewAllStudents();
};
void Teacher::viewAllStudents()
{
    ifstream file("student.txt");
    string line;
    string name, roll, department, semester;

    while (getline(file, line)) {
        name = line.substr(0, line.find(','));
        line = line.substr(line.find(',') + 1);
        roll = line.substr(0, line.find(','));
        line = line.substr(line.find(',') + 1);
        department = line.substr(0, line.find(','));
        semester = line.substr(line.find(',') + 1);

        cout << "Name: " << name << endl;
        cout << "Rollno: " << roll << endl;
        cout << "Department: " << department << endl;
        cout << "Semester: " << semester << endl;
        cout << endl;
    }

    file.close();

    // Ask the user if they want to return to teacher options
    char choice;
    do {
        cout << "Do you want to return to teacher options (y/n)? ";
        cin >> choice;
        system("cls");
        cin.ignore(); // Consume the newline character
        choice = tolower(choice);
    } while (choice != 'y' && choice != 'n');

    if (choice == 'y') {
        teacher_options();
    }
}
void Teacher::teacher_options()
{
    MasterClass* ptr4 = new Teacher;
        int choice;
        cout << "\n\n\n\n\n\n\n\t\t\t\tChoose an option" << endl;
        cout << "\t\t\t\t1. Add student marks" << endl;
        cout << "\t\t\t\t2. Update student marks" << endl;
        cout << "\t\t\t\t3. Add attendance" << endl;
        cout << "\t\t\t\t4. Update attendance" << endl;
        cout << "\t\t\t\t5. Search student" << endl;
        cout << "\t\t\t\t6. Delete login" << endl;
        cout << "\t\t\t\t7. Return to main menu" << endl;
        cout << "\t\t\t\t8. Exit" << endl;
        cout << "\t\t\t\t9. View all students" << endl;
        cout << "\t\t\t\tEnter choice: ";
        cin >> choice;
        cin.ignore();
        system("cls");
        while (choice != 8)
        {
            switch (choice)
            {
            case 1:
                addStudentMarks();
                break;
            case 2:
                updateStudentMarks();
                break;
            case 3:
                addAttendance();
                break;
            case 4:
                updateAttendance();
                break;
            case 5:
                ptr4->searchStudent();
                break;
            case 6:
                ptr4->deletelogin();
                break;
            case 7:
                main_menu();
            case 9:
                viewAllStudents();
            default:
                cout << "Invalid choice!" << endl;
            }
        
        cout << "\n\n\n\n\n\n\n\t\t\t\tChoose an option" << endl;
        cout << "\t\t\t\t1. Add student marks" << endl;
        cout << "\t\t\t\t2. Update student marks" << endl;
        cout << "\t\t\t\t3. Add attendance" << endl;
        cout << "\t\t\t\t4. Update attendance" << endl;
        cout << "\t\t\t\t5. Search student" << endl;
        cout << "\t\t\t\t6. Delete login" << endl;
        cout << "\t\t\t\t7. Return to main menu" << endl;
        cout << "\t\t\t\t8. Exit" << endl;
        cout << "\t\t\t\t9. View all students" << endl;
        cout << "\t\t\t\tEnter choice: ";
        cin >> choice;
        cin.ignore();
        system("cls");
        }
        cout << "Exiting program..." << endl;
        exit(0);

}
void Teacher::login()
{
    int login_success = 0;
    string username, password;
    cout << "Enter username: ";
    getline(cin, username);
    cout << "Enter password: ";
    getline(cin, password);
    system("cls");
    ifstream file("teacher.txt");
    string line;
    string user, pass;
    while (getline(file, line))
    {
        user = line.substr(0, line.find(','));
        pass = line.substr(line.find(',') + 1);
        if (user == username && pass == password)
        {
            cout << "Login successful!" << endl;
            login_success = 1;
            break;
        }
    }
    if (user != username || pass != password)
    {
        cout << "Invalid username or password!" << endl;
        login_success = 0;
    }
    if (login_success == 1)
    {
        teacher_options();
    }
}
void Teacher::registerTeacher()
{
    string username, password;

    // Check if a teacher already exists
    ifstream infile("teacher.txt");
    if (infile.is_open() && infile.peek() != ifstream::traits_type::eof()) {
        cout << "A teacher is already registered." << endl;
        infile.close();
        return;
    }
    infile.close();

    // Register new teacher
    cout << "Enter username: ";
    getline(cin, username);
    cout << "Enter password: ";
    getline(cin, password);
    ofstream outfile("teacher.txt", ios::app);
    outfile << username << "," << password << endl;
    cout << "Teacher registered successfully!" << endl;
    outfile.close();
}
void Teacher::forgotPassword()
{
    string username;
    cout << "Enter username: ";
    getline(cin, username);
    ifstream file("teacher.txt");
    string line;
    string user, pass;
    while (getline(file, line))
    {
        user = line.substr(0, line.find(','));
        pass = line.substr(line.find(',') + 1);
        if (user == username)
        {
            cout << "Your password is: " << pass << endl;
            break;
        }
    }
    if (user != username)
    {
        cout << "Invalid username!" << endl;
    }
}
void Teacher::deletelogin()
{
    string username;
    cout << "Enter username: ";
    getline(cin, username);

    ifstream infile("teacher.txt");
    if (!infile.is_open()) {
        cout << "Unable to open file." << endl;
        return;
    }

    string line;
    vector<string> lines;
    bool found = false;

    // Read all lines and store them, except the one to be deleted
    while (getline(infile, line)) {
        string user = line.substr(0, line.find(','));
        if (user != username) {
            lines.push_back(line);
        } else {
            found = true;
        }
    }
    infile.close();

    // Write the remaining lines back to the file
    if (found) {
        ofstream outfile("teacher.txt");
        for (const auto& l : lines) {
            outfile << l << endl;
        }
        outfile.close();
        cout << "Account deleted successfully!" << endl;
    } else {
        cout << "Invalid username!" << endl;
    }
}
void Teacher::addStudentMarks() {
    string rollno;
    cout << "Enter rollno: ";
    getline(cin, rollno);

    ifstream studentFile("student.txt");
    if (!studentFile.is_open()) {
        cout << "Error: Unable to open student file." << endl;
        return;
    }

    ifstream marksFile("marks.txt");
    if (!marksFile.is_open()) {
        cout << "Error: Unable to open marks file." << endl;
        studentFile.close();
        return;
    }

    string line;
    string name, roll, department, semester, marks;
    bool studentFound = false;

    // Check if student exists in student file
    while (getline(studentFile, line)) {
        name = line.substr(0, line.find(','));
        line = line.substr(line.find(',') + 1);
        roll = line.substr(0, line.find(','));
        line = line.substr(line.find(',') + 1);
        department = line.substr(0, line.find(','));
        line = line.substr(line.find(',') + 1);
        semester = line.substr(0, line.find(','));
        line = line.substr(line.find(',') + 1);
        marks = line;

        if (roll == rollno) {
            studentFound = true;
            break;
        }
    }

    if (!studentFound) {
        cout << "Invalid roll number!" << endl;
        studentFile.close();
        marksFile.close();
        return;
    }

    // Check if marks already exist for the student
    bool marksExist = false;
    while (getline(marksFile, line)) {
        roll = line.substr(line.find(',') + 1);
        roll = roll.substr(0, roll.find(','));

        if (roll == rollno) {
            marksExist = true;
            break;
        }
    }

    marksFile.close();

    if (marksExist) {
        cout << "Marks already exist for this student!" << endl;
        studentFile.close();
        return;
    }

    // If marks do not exist, proceed to add new marks
    cout << "Enter marks for 4 assignments (out of 10): ";
    int assignment1, assignment2, assignment3, assignment4;
    cin >> assignment1 >> assignment2 >> assignment3 >> assignment4;

    if (assignment1 < 0 || assignment1 > 10 || assignment2 < 0 || assignment2 > 10 ||
        assignment3 < 0 || assignment3 > 10 || assignment4 < 0 || assignment4 > 10) {
        cout << "Invalid marks entered." << endl;
        studentFile.close();
        return;
    }

    cout << "Enter marks for 4 quizzes (out of 10): ";
    int quiz1, quiz2, quiz3, quiz4;
    cin >> quiz1 >> quiz2 >> quiz3 >> quiz4;

    if (quiz1 < 0 || quiz1 > 10 || quiz2 < 0 || quiz2 > 10 ||
        quiz3 < 0 || quiz3 > 10 || quiz4 < 0 || quiz4 > 10) {
        cout << "Invalid marks entered." << endl;
        studentFile.close();
        return;
    }

    cout << "Enter marks for mid term (out of 25): ";
    int midterm;
    cin >> midterm;
    if (midterm < 0 || midterm > 25) {
        cout << "Invalid marks entered." << endl;
        studentFile.close();
        return;
    }

    cout << "Enter marks for final exam (out of 50): ";
    int finalexam;
    cin >> finalexam;
    if (finalexam < 0 || finalexam > 50) {
        cout << "Invalid marks entered." << endl;
        studentFile.close();
        return;
    }

    // Write marks to the file
    ofstream marksFileOut("marks.txt", ios::app);
    if (!marksFileOut.is_open()) {
        cout << "Error: Unable to open marks file." << endl;
        studentFile.close();
        return;
    }

    marksFileOut << name << "," << roll << "," << department << "," << semester << "," << assignment1 << ","
                 << assignment2 << "," << assignment3 << "," << assignment4 << "," << quiz1 << ","
                 << quiz2 << "," << quiz3 << "," << quiz4 << "," << midterm << "," << finalexam << endl;

    cout << "Marks added successfully!" << endl;

    studentFile.close();
    marksFileOut.close();

    char choice;
    do {
        cout << "Do you want to add marks for another student (y/n)? ";
        cin >> choice;
        cin.ignore(); // Consume the newline character after the 'y' or 'n'
        choice = tolower(choice);
    } while (choice != 'y' && choice != 'n');

    if (choice == 'n') {
        cout << "Student marks addition completed." << endl;
        system("cls");
        teacher_options();
    } else {
        addStudentMarks();
    }
}
void Teacher::updateStudentMarks() {
    string rollno;
    cout << "Enter rollno: ";
    getline(cin, rollno);

    ifstream file("marks.txt");
    if (!file.is_open()) {
        cout << "Error: Unable to open marks file." << endl;
        return;
    }

    string line;
    string name, roll, department, semester, assignment1, assignment2, assignment3, assignment4, quiz1, quiz2, quiz3, quiz4, midterm, finalexam;
    bool studentFound = false;
    ofstream tempFile("temp_marks.txt");
    if (!tempFile.is_open()) {
        cout << "Error: Unable to create temporary file." << endl;
        file.close();
        return;
    }

    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, name, ',');
        getline(ss, roll, ',');
        getline(ss, department, ',');
        getline(ss, semester, ',');
        getline(ss, assignment1, ',');
        getline(ss, assignment2, ',');
        getline(ss, assignment3, ',');
        getline(ss, assignment4, ',');
        getline(ss, quiz1, ',');
        getline(ss, quiz2, ',');
        getline(ss, quiz3, ',');
        getline(ss, quiz4, ',');
        getline(ss, midterm, ',');
        getline(ss, finalexam, ',');

        if (roll == rollno) {
            studentFound = true;
            cout << "Enter new marks for 4 assignments (out of 10): ";
            int newassignment1, newassignment2, newassignment3, newassignment4;
            cin >> newassignment1 >> newassignment2 >> newassignment3 >> newassignment4;

            // Validate marks for assignments
            if (newassignment1 < 0 || newassignment1 > 10 || newassignment2 < 0 || newassignment2 > 10 ||
                newassignment3 < 0 || newassignment3 > 10 || newassignment4 < 0 || newassignment4 > 10) {
                cout << "Invalid marks entered." << endl;
                tempFile.close();
                file.close();
                remove("temp_marks.txt");
                return;
            }

            cout << "Enter new marks for 4 quizzes (out of 10): ";
            int newquiz1, newquiz2, newquiz3, newquiz4;
            cin >> newquiz1 >> newquiz2 >> newquiz3 >> newquiz4;

            // Validate marks for quizzes
            if (newquiz1 < 0 || newquiz1 > 10 || newquiz2 < 0 || newquiz2 > 10 ||
                newquiz3 < 0 || newquiz3 > 10 || newquiz4 < 0 || newquiz4 > 10) {
                cout << "Invalid marks entered." << endl;
                tempFile.close();
                file.close();
                remove("temp_marks.txt");
                return;
            }

            cout << "Enter new marks for mid term (out of 25): ";
            int newmidterm;
            cin >> newmidterm;

            // Validate marks for midterm
            if (newmidterm < 0 || newmidterm > 25) {
                cout << "Invalid marks entered." << endl;
                tempFile.close();
                file.close();
                remove("temp_marks.txt");
                return;
            }

            cout << "Enter new marks for final exam (out of 50): ";
            int newfinalexam;
            cin >> newfinalexam;

            // Validate marks for final exam
            if (newfinalexam < 0 || newfinalexam > 50) {
                cout << "Invalid marks entered." << endl;
                tempFile.close();
                file.close();
                remove("temp_marks.txt");
                return;
            }

            // Write updated student data to the temporary file
            tempFile << name << "," << roll << "," << department << "," << semester << "," << newassignment1 << ","
                     << newassignment2 << "," << newassignment3 << "," << newassignment4 << "," << newquiz1 << ","
                     << newquiz2 << "," << newquiz3 << "," << newquiz4 << "," << newmidterm << "," << newfinalexam << endl;
            cout << "Marks updated successfully!" << endl;
        } else {
            // Write unchanged student data to the temporary file
            tempFile << name << "," << roll << "," << department << "," << semester << "," << assignment1 << ","
                     << assignment2 << "," << assignment3 << "," << assignment4 << "," << quiz1 << ","
                     << quiz2 << "," << quiz3 << "," << quiz4 << "," << midterm << "," << finalexam << endl;
        }
    }

    // Close original file and remove it
    file.close();
    remove("marks.txt");

    // Rename temporary file to original file
    tempFile.close();
    if (rename("temp_marks.txt", "marks.txt") != 0) {
        cout << "Error: Failed to update marks." << endl;
    }

    if (!studentFound) {
        cout << "Invalid roll number!" << endl;
    }
}


void Teacher::addAttendance()
{
    string rollno;
    cout << "Enter rollno: ";
    getline(cin, rollno);
    cin.ignore();
    ifstream file("student.txt");
    string line;
    string name, roll, department, semester;
    while (getline(file, line))
    {
        name = line.substr(0, line.find(','));
        line = line.substr(line.find(',') + 1);
        roll = line.substr(0, line.find(','));
        line = line.substr(line.find(',') + 1);
        department = line.substr(0, line.find(','));
        line = line.substr(line.find(',') + 1);
        semester = line;
        if (roll == rollno)
        {
            int attendance;
            while (true)
            {
                cout << "Enter attendance percentage: ";
                cin >> attendance;
                if (attendance >= 0 && attendance <= 100)
                {
                    break;
                }
                else
                {
                    cout << "Invalid attendance percentage! Please enter a value between 0 and 100." << endl;
                }
            }
            ofstream file("attendance.txt", ios::app);
            file << name << "," << roll << "," << department << "," << semester << "," << attendance << endl;
            cout << "Attendance added successfully!" << endl;
            file.close();
            break;
        }
    }
    if (roll != rollno)
    {
        cout << "Invalid rollno!" << endl;
    }
}
void Teacher::updateAttendance() {
    string rollno;
    cout << "Enter rollno: ";
    getline(cin, rollno);

    ifstream file("attendance.txt");
    if (!file.is_open()) {
        cout << "Error: Unable to open attendance file." << endl;
        return;
    }

    ofstream tempFile("temp_attendance.txt");
    if (!tempFile.is_open()) {
        cout << "Error: Unable to create temporary file." << endl;
        file.close();
        return;
    }

    string line;
    string name, roll, department, semester, attendance;
    bool studentFound = false;

    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, name, ',');
        getline(ss, roll, ',');
        getline(ss, department, ',');
        getline(ss, semester, ',');
        getline(ss, attendance, ',');

        if (roll == rollno) {
            studentFound = true;
            cout << "Enter new attendance percentage: ";
            int newAttendance;
            cin >> newAttendance;

            if (newAttendance < 0 || newAttendance > 100) {
                cout << "Invalid attendance entered." << endl;
                tempFile.close();
                file.close();
                remove("temp_attendance.txt");
                return;
            }

            // Write updated attendance for the student
            tempFile << name << "," << roll << "," << department << "," << semester << "," << newAttendance << endl;
            cout << "Attendance updated successfully!" << endl;
        } else {
            // Write unchanged data for other students
            tempFile << line << endl;
        }
    }

    if (!studentFound) {
        cout << "Invalid roll number!" << endl;
    }

    // Close the files
    file.close();
    tempFile.close();

    // Replace the original file with the updated file
    if (remove("attendance.txt") != 0) {
        cout << "Error: Unable to delete the original attendance file." << endl;
    } else if (rename("temp_attendance.txt", "attendance.txt") != 0) {
        cout << "Error: Unable to rename the temporary attendance file." << endl;
    }
}

void Teacher::searchStudent()
{
    string rollno;
  char choice;

  do {
    cout << "Enter rollno of the student to search: ";
    getline(cin, rollno);

    ifstream file("student.txt");
    string line;
    string name, roll, department, semester;
    bool found = false;

    while (getline(file, line)) {
      name = line.substr(0, line.find(','));
      line = line.substr(line.find(',') + 1);
      roll = line.substr(0, line.find(','));
      line = line.substr(line.find(',') + 1);
      department = line.substr(0, line.find(','));
      semester = line.substr(line.find(',') + 1);

      if (roll == rollno) {
        cout << "Name: " << name << endl;
        cout << "Rollno: " << roll << endl;
        cout << "Department: " << department << endl;
        cout << "Semester: " << semester << endl;
        found = true;
        break;
      }
    }

    file.close();

    if (!found) {
      cout << "Invalid rollno!" << endl;
    }

    // Ask the user if they want to search for another student
    do {
      cout << "Do you want to search for another student (y/n)? ";
      cin >> choice;
      system("cls");
      cin.ignore(); // Consume the newline character
      choice = tolower(choice);
    } while (choice != 'y' && choice != 'n');

  } while (choice == 'y');

  // Return to admin menu after search is done
  teacher_options();
}
class Student : public Teacher
{
public:
    void login();
    void forgotRollno();
    void student_options();
    void viewStudentMarks();
    void viewAttendance();
    void searchStudent();
    string loginroll;
};
void Student::student_options()
{
    int choice;
    cout << "\n\n\n\n\n\n\n\t\t\t\tChoose an option" << endl;
    cout << "\t\t\t\t1. View details" << endl;
    cout << "\t\t\t\t2. View marks" << endl;
    cout << "\t\t\t\t3. View attendance" << endl;
    cout << "\t\t\t\t4. Exit" << endl;
    cout << "\t\t\t\tEnter choice: ";
    cin >> choice;
    cin.ignore();
    system("cls");  
    while (choice != 4)
    {
        switch (choice)
        {
        case 1:
            searchStudent();
            cin.ignore();
            break;
        case 2:
            viewStudentMarks();
            cin.ignore();
            break;
        case 3:
            viewAttendance();
            cin.ignore();
            break;
        default:
            cout << "Invalid choice!" << endl;
        }
        cout << "\n\n\n\n\n\n\n\t\t\t\tChoose an option" << endl;
        cout << "\t\t\t\t1. View details" << endl;
        cout << "\t\t\t\t2. View marks" << endl;
        cout << "\t\t\t\t3. View attendance" << endl;
        cout << "\t\t\t\t4. Exit" << endl;
        cout << "\t\t\t\tEnter choice: ";
        cin >> choice;
        cin.ignore();
        system("cls");
    }
    system("cls");
}
void Student::login()
{
    int login_success = 0;
    string student_name, student_rollno;
    cout << "Enter name: ";
    getline(cin, student_name);
    cout << "Enter rollno: ";
    getline(cin, student_rollno);
    ifstream file("student.txt");
    string line;
    string name, roll, department, semester;
    while (getline(file, line))
    {
        name = line.substr(0, line.find(','));
        line = line.substr(line.find(',') + 1);
        roll = line.substr(0, line.find(','));
        line = line.substr(line.find(',') + 1);
        department = line.substr(0, line.find(','));
        semester = line.substr(line.find(',') + 1);
        if (name == student_name && roll == student_rollno)
        {
            cout << "Login successful!" << endl;
            login_success = 1;
            loginroll = student_rollno;
            system("cls");
            student_options();
            break;
        }
    }
    if (name != student_name || roll != student_rollno)
    {
        cout << "Invalid name or rollno!" << endl;
        system("cls");
        login_success = 0;
    }
}
void Student::searchStudent()
{
    string student_rollno;
    cout << "Enter rollno: ";
    getline(cin, student_rollno);
    if (student_rollno != loginroll)
    {
        cout << "Invalid rollno! You are not logged in as this user" << endl;
    }
    else {
    ifstream file("student.txt");
    string line;
    string name, roll, department, semester;
    while (getline(file, line))
    {
        name = line.substr(0, line.find(','));
        line = line.substr(line.find(',') + 1);
        roll = line.substr(0, line.find(','));
        line = line.substr(line.find(',') + 1);
        department = line.substr(0, line.find(','));
        semester = line.substr(line.find(',') + 1);
        if (roll == student_rollno)
        {
            cout << "Name: " << name << endl;
            cout << "Rollno: " << roll << endl;
            cout << "Department: " << department << endl;
            cout << "Semester: " << semester << endl;
            break;
        }
    }
    if (roll != student_rollno)
    {
        cout << "Invalid rollno!" << endl;
    }
}
}
void Student::forgotRollno()
{
    string student_name;
    cout << "Enter name: ";
    getline(cin, student_name);
    ifstream file("student.txt");
    string line;
    string name, roll, department, semester;
    while (getline(file, line))
    {
        name = line.substr(0, line.find(','));
        roll = line.substr(line.find(',') + 1);
        if (name == student_name)
        {
            cout << "Your rollno is: " << roll << endl;
            break;
        }
    }
    if (name != student_name)
    {
        cout << "Invalid name!" << endl;
    }
}
void Student::viewStudentMarks()
{
    string student_rollno;
    cout << "Enter rollno: ";
    getline(cin, student_rollno);
    cin.ignore();
    if (student_rollno != loginroll)
    {
        cout << "Invalid rollno OR Marks not entered!" << endl;
    }
    else {
    ifstream file("marks.txt");
    string line;
    string name, roll, department, semester, assignment1, assignment2, assignment3, assignment4, quiz1, quiz2, quiz3, quiz4, midterm, finalexam;
    while (getline(file, line))
    {
        name = line.substr(0, line.find(','));
        line = line.substr(line.find(',') + 1);
        roll = line.substr(0, line.find(','));
        line = line.substr(line.find(',') + 1);
        department = line.substr(0, line.find(','));
        line = line.substr(line.find(',') + 1);
        semester = line.substr(0, line.find(','));
        line = line.substr(line.find(',') + 1);
        assignment1 = line.substr(0, line.find(','));
        line = line.substr(line.find(',') + 1);
        assignment2 = line.substr(0, line.find(','));
        line = line.substr(line.find(',') + 1);
        assignment3 = line.substr(0, line.find(','));
        line = line.substr(line.find(',') + 1);
        assignment4 = line.substr(0, line.find(','));
        line = line.substr(line.find(',') + 1);
        quiz1 = line.substr(0, line.find(','));
        line = line.substr(line.find(',') + 1);
        quiz2 = line.substr(0, line.find(','));
        line = line.substr(line.find(',') + 1);
        quiz3 = line.substr(0, line.find(','));
        line = line.substr(line.find(',') + 1);
        quiz4 = line.substr(0, line.find(','));
        line = line.substr(line.find(',') + 1);
        midterm = line.substr(0, line.find(','));
        line = line.substr(line.find(',') + 1);
        finalexam = line;
        if (roll == student_rollno)
        {
            cout << "Name: " << name << endl;
            cout << "Rollno: " << roll << endl;
            cout << "Department: " << department << endl;
            cout << "Semester: " << semester << endl;
            cout << "ASSIGNMENT MARKS" << endl;
            cout << "Assignment 1: " << assignment1 << endl;
            cout << "Assignment 2: " << assignment2 << endl;
            cout << "Assignment 3: " << assignment3 << endl;
            cout << "Assignment 4: " << assignment4 << endl;
            cout << "QUIZ MARKS" << endl;
            cout << "Quiz 1: " << quiz1 << endl;
            cout << "Quiz 2: " << quiz2 << endl;
            cout << "Quiz 3: " << quiz3 << endl;
            cout << "Quiz 4: " << quiz4 << endl;
            cout << "MIDTERM MARKS" << endl;
            cout << "Midterm: " << midterm << endl;
            cout << "TERMINAL MARKS" << endl;
            cout << "Terminal exam: " << finalexam << endl;
            float quizavg = ((stof(quiz1) + stof(quiz2) + stof(quiz3) + stof(quiz4)) / 4) * 10;
            float assignmentavg = ((stof(assignment1) + stof(assignment2) + stof(assignment3) + stof(assignment4)) / 4) * 10;
            float midtermavg = (stof(midterm) / 25) * 100;
            float finalavg = (stof(finalexam) / 50) * 100;
            float total = (0.15 * quizavg) + (0.10 * assignmentavg) + (0.25 * midtermavg) + (0.50 * finalavg);
            cout << "TOTAL:  " << total << endl;
            if (total >= 90)
            {
                cout << "GRADE: A+" << endl;
                cout << "GPA: 4.0" << endl;
            }
            else if (total >= 85 && total < 90)
            {
                cout << "GRADE: A" << endl;
                cout << "GPA: 3.7" << endl;
            }
            else if (total >= 80 && total < 85)
            {
                cout << "GRADE: A-" << endl;
                cout << "GPA: 3.3" << endl;
            }
            else if (total >= 75 && total < 80)
            {
                cout << "GRADE: B+" << endl;
                cout << "GPA: 3.0" << endl;
            }
            else if (total >= 70 && total < 75)
            {
                cout << "GRADE: B" << endl;
                cout << "GPA: 2.7" << endl;
            }
            else if (total >= 65 && total < 70)
            {
                cout << "GRADE: B-" << endl;
                cout << "GPA: 2.3" << endl;
            }
            else if (total >= 60 && total < 65)
            {
                cout << "GRADE: C+" << endl;
                cout << "GPA: 2.0" << endl;
            }
            else if (total >= 55 && total < 60)
            {
                cout << "GRADE: C" << endl;
                cout << "GPA: 1.7" << endl;
            }
            else if (total >= 50 && total < 55)
            {
                cout << "GRADE: C-" << endl;
                cout << "GPA: 1.3" << endl;
            }
            else if (total >= 45 && total < 50)
            {
                cout << "GRADE: D+" << endl;
                cout << "GPA: 1.0" << endl;
            }
            else if (total >= 40 && total < 45)
            {
                cout << "GRADE: D" << endl;
                cout << "GPA: 0.7" << endl;
            }
            else
            {
                cout << "GRADE: F" << endl;
                cout << "GPA: 0.0" << endl;
            }
            break;
        }
    }
    if (roll != student_rollno)
    {
        cout << "Invalid rollno!" << endl;
    }
    }
}
void Student::viewAttendance()
{
    string student_rollno;
    cout << "Enter rollno: ";
    getline(cin, student_rollno);
    if (student_rollno != loginroll)
    {
        cout << "Not logged in as this user or attendance not entered!" << endl;
    }
    else {
    ifstream file("attendance.txt");
    string line;
    string name, roll, department, semester, attendance;
    while (getline(file, line))
    {
        name = line.substr(0, line.find(','));
        line = line.substr(line.find(',') + 1);
        roll = line.substr(0, line.find(','));
        line = line.substr(line.find(',') + 1);
        department = line.substr(0, line.find(','));
        line = line.substr(line.find(',') + 1);
        semester = line.substr(0, line.find(','));
        line = line.substr(line.find(',') + 1);
        attendance = line;
        if (roll == student_rollno)
        {
            cout << "Name: " << name << endl;
            cout << "Rollno: " << roll << endl;
            cout << "Department: " << department << endl;
            cout << "Semester: " << semester << endl;
            cout << "Attendance: " << attendance << "%" << endl;
            break;
        }
    }
    if (roll != student_rollno)
    {
        cout << "Invalid rollno or attendance not entered!" << endl;
    }
    }
}



