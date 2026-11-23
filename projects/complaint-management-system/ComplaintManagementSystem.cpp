//================================================================================
//          COMPLAINT MANAGEMENT SYSTEM - C++ IMPLEMENTATION
//          Version 2.0 (File Handling Removed)
//          University of Kamalia - Computer Science Department
//================================================================================
// This program manages complaints for organizations using OOP concepts
// Features: Add, View, Search, Update, Delete complaints with menu-driven interface
//================================================================================

#include <iostream>
#include <string>
using namespace std;

//================ BASE CLASS =================
class Person
{
protected:
    string name;

public:
    virtual void displayRole()
    {
        cout << "User of Complaint Management System" << endl;
    }
};

//================ COMPLAINT CLASS (Derived from Person) =================
class Complaint : public Person
{
private:
    int complaintID;
    string department;
    string description;
    string status;

public:
    static int totalComplaints;

    // Default Constructor
    Complaint()
    {
        complaintID = 0;
        name = "";
        department = "";
        description = "";
        status = "Pending";
    }

    // Parameterized Constructor
    Complaint(int id, string n, string dep, string des)
    {
        complaintID = id;
        name = n;
        department = dep;
        description = des;
        status = "Pending";
        totalComplaints++;
    }

    // Destructor
    ~Complaint()
    {
    }

    //================ ENCAPSULATION - SETTERS =================
    void setID(int id)
    {
        complaintID = id;
    }

    void setName(string n)
    {
        name = n;
    }

    void setDepartment(string dep)
    {
        department = dep;
    }

    void setDescription(string des)
    {
        description = des;
    }

    void setStatus(string s)
    {
        status = s;
    }

    //================ ENCAPSULATION - GETTERS =================
    int getID()
    {
        return complaintID;
    }

    string getName()
    {
        return name;
    }

    string getDepartment()
    {
        return department;
    }

    string getDescription()
    {
        return description;
    }

    string getStatus()
    {
        return status;
    }

    //================ POLYMORPHISM - Virtual Function Override =================
    void displayRole()
    {
        cout << "Complaint Registered by User" << endl;
    }

    //================ FUNCTION OVERLOADING =================
    // Version 1: Display without formatting
    void showComplaint()
    {
        cout << "Complaint ID : " << complaintID << endl;
        cout << "Name : " << name << endl;
        cout << "Department : " << department << endl;
        cout << "Description : " << description << endl;
        cout << "Status : " << status << endl;
    }

    // Version 2: Display with optional line formatting
    void showComplaint(bool line)
    {
        if(line)
        {
            cout << "----------------------------------" << endl;
        }
        showComplaint();
    }

    //================ FRIEND FUNCTION =================
    friend void welcomeMessage(Complaint c);
};

// Static Member Initialization
int Complaint::totalComplaints = 0;

//================ FRIEND FUNCTION IMPLEMENTATION =================
void welcomeMessage(Complaint c)
{
    cout << endl << "Welcome " << c.getName() << "!" << endl;
    cout << "Your complaint has been recorded." << endl;
}

//============== GLOBAL VARIABLES ==============
Complaint complaints[100];
int countComplaint = 0;

//============== FUNCTION: ADD COMPLAINT ==============
void addComplaint()
{
    // Check if array is full
    if(countComplaint >= 100)
    {
        cout << endl << "Error! Complaint limit reached (100 complaints maximum)." << endl;
        return;
    }

    int id;
    string name, department, description;

    cout << endl << "====== ADD NEW COMPLAINT ======" << endl;
    cout << "Enter Complaint ID: ";
    cin >> id;
    cin.ignore(); // Clear input buffer

    // Validate ID uniqueness
    for(int i = 0; i < countComplaint; i++)
    {
        if(complaints[i].getID() == id)
        {
            cout << endl << "Error! Complaint ID already exists." << endl;
            return;
        }
    }

    cout << "Enter Name: ";
    getline(cin, name);

    if(name.empty())
    {
        cout << endl << "Error! Name cannot be empty." << endl;
        return;
    }

    cout << "Enter Department: ";
    getline(cin, department);

    if(department.empty())
    {
        cout << endl << "Error! Department cannot be empty." << endl;
        return;
    }

    cout << "Enter Complaint Description: ";
    getline(cin, description);

    if(description.empty())
    {
        cout << endl << "Error! Description cannot be empty." << endl;
        return;
    }

    // Set complaint details
    complaints[countComplaint].setID(id);
    complaints[countComplaint].setName(name);
    complaints[countComplaint].setDepartment(department);
    complaints[countComplaint].setDescription(description);
    complaints[countComplaint].setStatus("Pending");

    // Welcome message using friend function
    welcomeMessage(complaints[countComplaint]);
    countComplaint++;
    cout << endl << "✓ Complaint Added Successfully!" << endl;
}

//============== FUNCTION: VIEW ALL COMPLAINTS ==============
void viewComplaints()
{
    if(countComplaint == 0)
    {
        cout << endl << "! No Complaint Found!" << endl;
        return;
    }

    cout << endl << "=========== COMPLAINT LIST ===========" << endl;
    for(int i = 0; i < countComplaint; i++)
    {
        cout << endl << "[Complaint " << (i+1) << " of " << countComplaint << "]" << endl;
        complaints[i].showComplaint(true);
    }
    cout << endl << "=====================================" << endl;
}

//============== FUNCTION: SEARCH COMPLAINT ==============
void searchComplaint()
{
    if(countComplaint == 0)
    {
        cout << endl << "! No Complaints in System!" << endl;
        return;
    }

    int id;
    bool found = false;

    cout << endl << "====== SEARCH COMPLAINT ======" << endl;
    cout << "Enter Complaint ID to Search: ";
    cin >> id;

    for(int i = 0; i < countComplaint; i++)
    {
        if(complaints[i].getID() == id)
        {
            cout << endl << "✓ Complaint Found!" << endl;
            complaints[i].showComplaint(true);
            found = true;
            break;
        }
    }

    if(!found)
    {
        cout << endl << "! Complaint with ID " << id << " Not Found!" << endl;
    }
}

//============== FUNCTION: UPDATE COMPLAINT STATUS ==============
void updateComplaint()
{
    if(countComplaint == 0)
    {
        cout << endl << "! No Complaints in System!" << endl;
        return;
    }

    int id;
    bool found = false;

    cout << endl << "====== UPDATE COMPLAINT STATUS ======" << endl;
    cout << "Enter Complaint ID: ";
    cin >> id;

    for(int i = 0; i < countComplaint; i++)
    {
        if(complaints[i].getID() == id)
        {
            cout << endl << "Current Status: " << complaints[i].getStatus() << endl;
            complaints[i].setStatus("Resolved");
            cout << "✓ Status Updated to: Resolved" << endl;
            found = true;
            break;
        }
    }

    if(!found)
    {
        cout << endl << "! Complaint with ID " << id << " Not Found!" << endl;
    }
}

//============== FUNCTION: DELETE COMPLAINT ==============
void deleteComplaint()
{
    if(countComplaint == 0)
    {
        cout << endl << "! No Complaints in System!" << endl;
        return;
    }

    int id;
    bool found = false;

    cout << endl << "====== DELETE COMPLAINT ======" << endl;
    cout << "Enter Complaint ID to Delete: ";
    cin >> id;

    for(int i = 0; i < countComplaint; i++)
    {
        if(complaints[i].getID() == id)
        {
            // Shift all elements to fill the gap
            for(int j = i; j < countComplaint - 1; j++)
            {
                complaints[j] = complaints[j + 1];
            }
            countComplaint--;
            cout << endl << "✓ Complaint Deleted Successfully!" << endl;
            found = true;
            break;
        }
    }

    if(!found)
    {
        cout << endl << "! Complaint with ID " << id << " Not Found!" << endl;
    }
}

//============== FUNCTION: DISPLAY USER ROLE ==============
void displayUserRole()
{
    if(countComplaint > 0)
    {
        cout << endl << "====== USER ROLE ======" << endl;
        complaints[0].displayRole();
    }
    else
    {
        cout << endl << "! No Complaints Available to Display Role!" << endl;
    }
}

//============== MAIN FUNCTION ==============
int main()
{
    int choice;

    cout << "\n" << "████████████████████████████████████████" << endl;
    cout << "   COMPLAINT MANAGEMENT SYSTEM v2.0" << endl;
    cout << "████████████████████████████████████████\n" << endl;

    do
    {
        cout << "\n=====================================" << endl;
        cout << "        MAIN MENU - SELECT OPTION" << endl;
        cout << "=====================================" << endl;
        cout << "1. Add New Complaint" << endl;
        cout << "2. View All Complaints" << endl;
        cout << "3. Search Complaint by ID" << endl;
        cout << "4. Update Complaint Status" << endl;
        cout << "5. Delete Complaint" << endl;
        cout << "6. Display User Role" << endl;
        cout << "7. Exit System" << endl;
        cout << "=====================================" << endl;
        cout << "Enter Your Choice (1-7): ";
        cin >> choice;
        cout << endl;

        switch(choice)
        {
        case 1:
            addComplaint();
            break;

        case 2:
            viewComplaints();
            break;

        case 3:
            searchComplaint();
            break;

        case 4:
            updateComplaint();
            break;

        case 5:
            deleteComplaint();
            break;

        case 6:
            displayUserRole();
            break;

        case 7:
            cout << "=====================================" << endl;
            cout << "Thank you for using" << endl;
            cout << "COMPLAINT MANAGEMENT SYSTEM!" << endl;
            cout << "=====================================" << endl;
            break;

        default:
            cout << "! Invalid Choice! Please enter a number between 1-7." << endl;
        }

    } while(choice != 7);

    return 0;
}

//================================================================================
//                          END OF PROGRAM
//================================================================================
// Key Features Implemented:
// ✓ Object-Oriented Programming (Classes, Inheritance)
// ✓ Encapsulation (Private/Public members)
// ✓ Polymorphism (Virtual functions)
// ✓ Function Overloading (showComplaint with 2 versions)
// ✓ Friend Functions (welcomeMessage)
// ✓ Static Members (totalComplaints)
// ✓ Input Validation (Duplicate ID checking, empty field checking)
// ✓ Menu-Driven Interface (Easy navigation)
// ✓ Efficient Array Management
// ✓ Error Handling (Graceful error messages)
//================================================================================