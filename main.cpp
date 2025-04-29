#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <vector>
using namespace std;

struct Patient {
    string id;
    string name;
    string condition;
    int priority;

    bool operator<(const Patient& other) const {
        return priority > other.priority;
    }
};

struct PatientNode {
    Patient data;
    PatientNode* next;
};

class PatientList {
private:
    static const int MAX_PATIENTS = 100;
    Patient patients[MAX_PATIENTS];
    int count;
    PatientNode* head;

public:
    PatientList() {
        count = 0;
        head = nullptr;
    }

    void addPatient(string id, string name, string condition) {
        if (count < MAX_PATIENTS) {
            patients[count++] = {id, name, condition, 3};
            cout << "Patient added successfully.\n";
        } else {
            PatientNode* newNode = new PatientNode{{id, name, condition, 3}, nullptr};
            if (!head) {
                head = newNode;
            } else {
                PatientNode* temp = head;
                while (temp->next) temp = temp->next;
                temp->next = newNode;
            }
            cout << "Patient added successfully.\n";
        }
    }

    void displayPatients() {
        if (count == 0 && !head) {
            cout << "No patients to show.\n";
            return;
        }

        cout << "--- Patients in Array ---\n";
        for (int i = 0; i < count; i++) {
            cout << "ID: " << patients[i].id << ", Name: " << patients[i].name << ", Condition: " << patients[i].condition << endl;
        }

        cout << "--- Patients in Linked List ---\n";
        PatientNode* temp = head;
        while (temp) {
            cout << "ID: " << temp->data.id << ", Name: " << temp->data.name << ", Condition: " << temp->data.condition << endl;
            temp = temp->next;
        }
    }

    void deletePatient(string id) {
        int index = -1;
        for (int i = 0; i < count; i++) {
            if (patients[i].id == id) {
                index = i;
                break;
            }
        }

        if (index != -1) {
            for (int i = index; i < count - 1; i++) {
                patients[i] = patients[i + 1];
            }
            count--;
            cout << "Patient deleted.\n";
            return;
        }

        PatientNode* temp = head;
        PatientNode* prev = nullptr;
        while (temp) {
            if (temp->data.id == id) {
                if (prev) {
                    prev->next = temp->next;
                } else {
                    head = temp->next;
                }
                delete temp;
                cout << "Patient deleted.\n";
                return;
            }
            prev = temp;
            temp = temp->next;
        }

        cout << "No patient with that ID found.\n";
    }

    ~PatientList() {
        PatientNode* temp;
        while (head) {
            temp = head;
            head = head->next;
            delete temp;
        }
    }
};

class EmergencyRoom {
private:
    priority_queue<Patient> erQueue;
public:
    void addEmergency(Patient p) {
        erQueue.push(p);
        cout << "Emergency patient added with priority " << p.priority << ".\n";
    }

    void treatEmergency() {
        if (erQueue.empty()) {
            cout << "No emergency patients.\n";
            return;
        }
        Patient p = erQueue.top();
        erQueue.pop();
        cout << "Treating emergency: " << p.name << " (ID: " << p.id << ", Condition: " << p.condition << ")\n";
    }
};

class TreatmentHistory {
private:
    stack<string> treatments;
public:
    void addTreatment(string treatment) {
        treatments.push(treatment);
        cout << "Treatment recorded.\n";
    }

    void undo() {
        if (treatments.empty()) {
            cout << "No treatments to undo.\n";
            return;
        }
        cout << "Undoing: " << treatments.top() << endl;
        treatments.pop();
    }
};

int getPriorityFromCondition(string condition) {
    if (condition == "Heart Attack" || condition == "Stroke")
        return 1;
    else if (condition == "Fracture" || condition == "Serious Injury")
        return 2;
    else
        return 3;
}

int main() {
    PatientList list;
    EmergencyRoom er;
    TreatmentHistory history;

    string choiceStr;
    int choice;

    while (true) {
        cout << "\n--- Hospital Menu ---\n";
        cout << "1. Add Patient\n";
        cout << "2. Show Patients\n";
        cout << "3. Delete Patient\n";
        cout << "4. Add Emergency Patient\n";
        cout << "5. Handle Emergency\n";
        cout << "6. Add Treatment\n";
        cout << "7. Undo Treatment\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        getline(cin, choiceStr);

        if (choiceStr.empty() || choiceStr.find_first_not_of("0123456789") != string::npos) {
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        choice = stoi(choiceStr);

        if (choice == 1) {
            string id, name, cond;
            cout << "ID: ";
            getline(cin, id);
            if (id.empty()) getline(cin, id);
            cout << "Name: ";
            getline(cin, name);
            cout << "Condition: ";
            getline(cin, cond);
            list.addPatient(id, name, cond);
        }
        else if (choice == 2) {
            list.displayPatients();
        }
        else if (choice == 3) {
            string id;
            cout << "Enter ID to delete: ";
            getline(cin, id);
            list.deletePatient(id);
        }
        else if (choice == 4) {
            string id, name, cond;
            cout << "Emergency ID: ";
            getline(cin, id);
            cout << "Name: ";
            getline(cin, name);
            cout << "Condition: ";
            getline(cin, cond);
            int priority = getPriorityFromCondition(cond);
            er.addEmergency({id, name, cond, priority});
        }
        else if (choice == 5) {
            er.treatEmergency();
        }
        else if (choice == 6) {
            string treatment;
            cout << "Enter Treatment Name: ";
            getline(cin, treatment);
            history.addTreatment(treatment);
        }
        else if (choice == 7) {
            history.undo();
        }
        else if (choice == 0) {
            cout << "Exiting program. Goodbye!\n";
            break;
        }
        else {
            cout << "Invalid choice.\n";
        }
    }

    return 0;
}
