#include "todo.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Task {
public:
    string description;
    bool isCompleted;

    Task(string desc, bool completed = false) : description(desc), isCompleted(completed) {}
};

vector<Task> tasks;

void loadTasksFromFile();
void todo();
void menu();
void save();
void markTaskAsDone();
void deleteTask();
void editTask();

void loadTasksFromFile() {
    ifstream inFile("tasks.txt");
    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            if (!line.empty() && line != "========= TODO LIST =========") {
                bool completed = (line[0] == '*');
                if (completed) {
                    line = line.substr(1); // Remove the '*' indicator
                }
                tasks.emplace_back(line, completed);
            }
        }
        inFile.close();
    }
}

void todo() {
    while (true) {
        string command;
        cout << "\nEnter a command ('menu' to view options, 'exit' to leave): ";
        getline(cin, command);

        if (command == "menu") {
            menu();
        } else if (command == "save") {
            save();
        } else if (command == "exit") {
            break;
        } else if (command == "done") {
            markTaskAsDone();
        } else if (command == "delete") {
            deleteTask();
        } else if (command == "edit") {
            editTask();
        } else if (!command.empty()) {
            tasks.emplace_back(command); // Add the task to the list
        } else {
            cout << "Task cannot be empty. Please try again." << endl;
        }
    }
}

void menu() {
    cout << "\n==============================================" << endl;
    cout << "                 TODO LIST MENU               " << endl;
    cout << "==============================================" << endl;

    if (tasks.empty()) {
        cout << "No tasks have been added yet! Start by adding one." << endl;
    } else {
        cout << "You have " << tasks.size() << " tasks:" << endl;
        cout << "----------------------------------------------" << endl;
        for (size_t i = 0; i < tasks.size(); ++i) {
            cout << " " << i + 1 << ". " << (tasks[i].isCompleted ? "[Done] " : "") << tasks[i].description << endl;
        }
        cout << "----------------------------------------------" << endl;
    }

    cout << "Options:" << endl;
    cout << " - Type a new task to add it to the list." << endl;
    cout << " - Type 'save' to save your tasks to a file." << endl;
    cout << " - Type 'done' to mark a task as completed." << endl;
    cout << " - Type 'delete' to delete a task." << endl;
    cout << " - Type 'edit' to modify a task." << endl;
    cout << " - Type 'exit' to close the program." << endl;
    cout << "==============================================" << endl;
}

void save() {
    ofstream TodoList("tasks.txt");
    if (TodoList.is_open()) {
        for (const auto& task : tasks) {
            TodoList << (task.isCompleted ? "*" : "") << task.description << endl;
        }
        TodoList.close();
        cout << "Tasks saved to tasks.txt" << endl;
    } else {
        cout << "Failed to open file!" << endl;
    }
}

void markTaskAsDone() {
    if (tasks.empty()) {
        cout << "No tasks available to mark as done." << endl;
        return;
    }

    size_t taskNumber;
    cout << "Enter the number of the task to mark as completed: ";
    cin >> taskNumber;
    cin.ignore();

    if (taskNumber >= 1 && taskNumber <= tasks.size()) {
        tasks[taskNumber - 1].isCompleted = true;
        cout << "Task " << taskNumber << " marked as completed." << endl;
    } else {
        cout << "Invalid task number." << endl;
    }
}

void deleteTask() {
    if (tasks.empty()) {
        cout << "No tasks available to delete." << endl;
        return;
    }

    size_t taskNumber;
    cout << "Enter the number of the task to delete: ";
    cin >> taskNumber;
    cin.ignore();

    if (taskNumber >= 1 && taskNumber <= tasks.size()) {
        tasks.erase(tasks.begin() + taskNumber - 1);
        cout << "Task " << taskNumber << " deleted." << endl;
    } else {
        cout << "Invalid task number." << endl;
    }
}

void editTask() {
    if (tasks.empty()) {
        cout << "No tasks available to edit." << endl;
        return;
    }

    size_t taskNumber;
    cout << "Enter the number of the task to edit: ";
    cin >> taskNumber;
    cin.ignore();

    if (taskNumber >= 1 && taskNumber <= tasks.size()) {
        cout << "Enter the new description for task " << taskNumber << ": ";
        string newDescription;
        getline(cin, newDescription);
        if (!newDescription.empty()) {
            tasks[taskNumber - 1].description = newDescription;
            cout << "Task " << taskNumber << " updated." << endl;
        } else {
            cout << "Task description cannot be empty." << endl;
        }
    } else {
        cout << "Invalid task number." << endl;
    }
}
