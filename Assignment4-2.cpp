#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX_PATIENTS = 20; 
struct Patient {
    int patientID;
    string name;
    int age;
    string disease;
    int roomNumber;
};

void addPatient(Patient patients[], int &count) {
    if (count >= MAX_PATIENTS) {
        cout << "Hospital is full. Cannot add more patients.\n";
        return;
    }
    cout << "Enter Patient ID: ";
    cin >> patients[count].patientID;
    cin.ignore(); 
    cout << "Enter Name: ";
    getline(cin, patients[count].name);
    cout << "Enter Age: ";
    cin >> patients[count].age;
    cin.ignore(); 
    cout << "Enter Disease: ";
    getline(cin, patients[count].disease);
    cout << "Enter Room Number: ";
    cin >> patients[count].roomNumber;
    count++;
    cout << "Patient added successfully!\n";
}

void searchPatient(Patient patients[], int count) {
    int id;
    cout << "Enter Patient ID to search: ";
    cin >> id;

    for (int i = 0; i < count; i++) {
        if (patients[i].patientID == id) {
            cout << "Patient Found:\n";
            cout << "ID: " << patients[i].patientID << "\n";
            cout << "Name: " << patients[i].name << "\n";
            cout << "Age: " << patients[i].age << "\n";
            cout << "Disease: " << patients[i].disease << "\n";
            cout << "Room Number: " << patients[i].roomNumber << "\n";
            return;
        }
    }
    cout << "Patient not found.\n";
}

void displayPatients(Patient patients[], int count) {
    if (count == 0) {
        cout << "No patients admitted.\n";
        return;
    }
    cout << "Admitted Patients:\n";
    for (int i = 0; i < count; i++) {
        cout << "ID: " << patients[i].patientID << "\n";
        cout << "Name: " << patients[i].name << "\n";
        cout << "Age: " << patients[i].age << "\n";
        cout << "Disease: " << patients[i].disease << "\n";
        cout << "Room Number: " << patients[i].roomNumber << "\n\n";
    }
}

void saveToFile(Patient patients[], int count) {
    ofstream outFile("patients.txt");
    if (outFile.is_open()) {
        cout << "Error saving data to file.\n";
        return;
    }
  
    outFile << count << "\n"; 
    for (int i = 0; i < count; i++) {
        outFile << patients[i].patientID << "\n"
                << patients[i].name << "\n"
                << patients[i].age << "\n"
                << patients[i].disease << "\n"
                << patients[i].roomNumber << "\n";
    }
    outFile.close();
}

void loadFromFile(Patient patients[], int &count) {
    ifstream inFile("patients.txt");
    if (inFile.is_open()) {
        cout << "No previous data found.\n";
        return;
    }
    inFile >> count;
    inFile.ignore(); 
    for (int i = 0; i < count; i++) {
        inFile >> patients[i].patientID;
        inFile.ignore();
        getline(inFile, patients[i].name);
        inFile >> patients[i].age;
        inFile.ignore();
        getline(inFile, patients[i].disease);
        inFile >> patients[i].roomNumber;
        inFile.ignore();
    }
    inFile.close();
    cout << "Patient records loaded successfully. " << count << " patients available.\n";
}

int main() {
    Patient patients[MAX_PATIENTS]; 
    int patientCount = 0;           

    loadFromFile(patients, patientCount);

    int choice;
    do {
        cout << "\nHospital Patient Management System\n";
        cout << "1. Add a New Patient\n";
        cout << "2. Search for a Patient\n";
        cout << "3. Display All Patients\n";
        cout << "4. Save and Exit\n";
        cout << "Choose 1 to 4 ";
        cin >> choice;

        switch (choice) {
            case 1:
                addPatient(patients, patientCount);
                break;
            case 2:
                searchPatient(patients, patientCount);
                break;
            case 3:
                displayPatients(patients, patientCount);
                break;
            case 4:
                saveToFile(patients, patientCount);
                cout << "Bye\n";
                break;
            default:
                cout << "Invalid choice. \n";
        }
    } while (choice != 4);

    return 0;
}
