void main_menu();
void admin_menu();
void teacher_menu();
void student_menu();
void main_menu() {
    int menu_choice;
    do {
        cout << "\n\n\n\n\n\n\n\t\t\t\t------------------------------------" << endl;
        cout << "\t\t\t\tWelcome to Student Management System" << endl;
        cout << "\t\t\t\t------------------------------------" << endl;
        cout << "\t\t\t\t1. Admin" << endl;
        cout << "\t\t\t\t2. Teacher" << endl;
        cout << "\t\t\t\t3. Student" << endl;
        cout << "\t\t\t\t4. Exit" << endl;
        cout << "\t\t\t\tEnter choice: ";
        cin >> menu_choice;
        cin.ignore();
        system("cls");

        switch (menu_choice) {
            case 1:
                admin_menu();
                break;
            case 2:
                teacher_menu();
                break;
            case 3:
                student_menu();
                break;
            case 4:
                exit(0);
            default:
                cout << "Invalid choice!" << endl;
                system("cls");        
                }
    } while (menu_choice != 4); // Repeat until user chooses to exit
}

void admin_menu() {
    Admin admin;
    MasterClass* ptr1 = new Admin;
    int admin_choice;

    do {
        cout << "\n\n\n\n\n\n\n\t\t\t\tChoose an option" << endl;
        cout << "\t\t\t\t1. Register" << endl;
        cout << "\t\t\t\t2. Login" << endl;
        cout << "\t\t\t\t3. Forgot password" << endl;
        cout << "\t\t\t\t4. Return to menu" << endl;
        cout << "\t\t\t\t5. Exit" << endl;
        cout << "\t\t\t\tEnter choice: ";
        cin >> admin_choice;
        cin.ignore();
        system("cls");

        switch (admin_choice) {
            case 1:
                admin.registerAdmin();
                break;
            case 2:
                ptr1->login();
                break;
            case 3:
                admin.forgotPassword();
                break;
            case 4:
                break; // Return to main menu
            case 5:
                exit(0);
            default:
                cout << "Invalid choice!" << endl;
        }
    } while (admin_choice != 4);
}
void teacher_menu() {
    Teacher teacher;
    MasterClass* ptr2 = new Teacher;
    int teacher_choice; // Declare teacher_choice here

    do { // Add semicolon after do
        cout << "\n\n\n\n\n\n\n\t\t\t\tChoose an option" << endl;
        cout << "\t\t\t\t1. Register" << endl;
        cout << "\t\t\t\t2. Login" << endl;
        cout << "\t\t\t\t3. Forgot password" << endl; // Implement if needed
        cout << "\t\t\t\t4. Return to menu" << endl;
        cout << "\t\t\t\tEnter choice: ";
        cin >> teacher_choice;
        cin.ignore();
        system("cls");

        switch (teacher_choice) {
            case 1:
                teacher.registerTeacher();
                break;
            case 2:
                ptr2->login();
                break;
            case 3:
                teacher.forgotPassword();
                break;
            case 4:
                break;
            default:
                cout << "Invalid choice!" << endl;
        }
    } while (teacher_choice != 4); // Loop condition
}
void student_menu()
{
    Student student;
    MasterClass* ptr3 = new Student;
    int student_choice;

    do {
        cout << "\n\n\n\n\n\n\n\t\t\t\tChoose an option" << endl;
        cout << "\t\t\t\t1. Login" << endl;
        cout << "\t\t\t\t2. Forgot roll number" << endl;
        cout << "\t\t\t\t3. Return to menu" << endl;
        cout << "\t\t\t\tEnter choice: ";
        cin >> student_choice;
        cin.ignore();
        system("cls");

        switch (student_choice) {
            case 1:
                ptr3->login();
                break;
            case 2:
                student.forgotRollno();
                break;
            case 3:
                main_menu();
            default:
                cout << "Invalid choice!" << endl;
        }
    } while (student_choice != 4);
}
