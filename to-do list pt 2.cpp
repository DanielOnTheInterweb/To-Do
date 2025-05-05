#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    int menuOption;
    string newTask, editTask;

    cout << "here are your options for the to-do list:\n\n";
    cout << "1: View List\n";
    cout << "2: Add to list\n";
    cout << "3: Remove From List\n";
    cout << "4: Edit Element in List\n";

    cout << "select an option: ";
    cin >> menuOption;

    if (menuOption < 1 || menuOption > 4) {
        cout << "Exiting program. Goodbye!\n";
    }

    switch (menuOption) {
    case 1: {
        ifstream inFile("tasks.txt");
        if (inFile.is_open()) {
            string line;
            int taskNum = 1;
            cout << "Here is your to-do list:\n\n";
            while (getline(inFile, line)) {
                cout << taskNum++ << ": " << line << endl;
            }
            inFile.close();
        }
        else {
            cout << "Unable to open tasks.txt\n";
        }
        break;
    }

    case 2:
        cout << "type in the task to be written in:";
        cin.ignore();  // clear leftover newline
        getline(cin, newTask);

        // Write the new task to the tasks.txt file
        {
            ofstream outFile("tasks.txt", ios::app);  // Open file in append mode
            if (outFile.is_open()) {
                outFile << newTask << endl;  // Write the task followed by a new line
                outFile.close();  // Close the file
                cout << "your new task is: " << newTask << ", press Enter to confirm";
                cin.get();  // Waits for Enter to be pressed
            }
            else {
                cout << "Unable to open the file!";
            }
        }
        break;

    case 3: {
        const int MAX_TASKS = 100;
        string tasks[MAX_TASKS];
        string line;
        int count = 0, removeIndex;

        ifstream inFile("tasks.txt");
        while (getline(inFile, line) && count < MAX_TASKS) {
            tasks[count++] = line;
        }
        inFile.close();

        if (count == 0) {
            cout << "The list is empty.\n";
            break;
        }

        cout << "Current list:\n";
        for (int i = 0; i < count; i++) {
            cout << i + 1 << ": " << tasks[i] << endl;
        }

        cout << "Enter the number of the task to remove: ";
        cin >> removeIndex;

        if (removeIndex < 1 || removeIndex > count) {
            cout << "Invalid task number.\n";
            break;
        }

        // Shift tasks up to overwrite the one to be removed
        for (int i = removeIndex - 1; i < count - 1; i++) {
            tasks[i] = tasks[i + 1];
        }
        count--; // Reduce total count

        ofstream outFile("tasks.txt");
        for (int i = 0; i < count; i++) {
            outFile << tasks[i] << endl;
        }
        outFile.close();

        cout << "Task removed successfully.\n";
        break;
    }
    case 4: {
        const int MAX_TASKS = 100;
        string tasks[MAX_TASKS];
        string line, newTask;
        int count = 0, editIndex;

        ifstream inFile("tasks.txt");
        while (getline(inFile, line) && count < MAX_TASKS) {
            tasks[count++] = line;
        }
        inFile.close();

        if (count == 0) {
            cout << "The list is empty.\n";
            break;
        }

        cout << "Current list:\n";
        for (int i = 0; i < count; i++) {
            cout << i + 1 << ": " << tasks[i] << endl;
        }

        cout << "Enter the number of the task to edit: ";
        cin >> editIndex;
        cin.ignore();  // Clear newline

        if (editIndex < 1 || editIndex > count) {
            cout << "Invalid task number.\n";
            break;
        }

        cout << "Enter the new task text: ";
        getline(cin, newTask);
        tasks[editIndex - 1] = newTask;

        ofstream outFile("tasks.txt");
        for (int i = 0; i < count; i++) {
            outFile << tasks[i] << endl;
        }
        outFile.close();

        cout << "Task updated successfully.\n";
        break;
    }


    default:
        cout << "Please only enter an option between 1 and 4!";
    }

    return 0;
}
