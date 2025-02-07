    // Application project4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <string>


struct Task {
    std::string description;
    bool isCompleted;   
};


void displayTasks(const std::vector<Task>& tasks) {
    std::cout << "\nYour to-do List:\n";
    for (int i = 0; i < tasks.size(); ++i) {
        std::cout << i + 1 << ". " << tasks[i].description
            << (tasks[i].isCompleted ? " (Completed) " : " (Not Completed) ") << std::endl;
    }
}

void addTask(std::vector<Task>& tasks) {
    Task newTask;
    std::cout << "Enter the description of the new task: ";
    std::cin.ignore();
    std::getline(std::cin, newTask.description);
    newTask.isCompleted = false;
    tasks.push_back(newTask);
    std::cout << "Task added successfully!" << std::endl;
}

void markTaskCompleted(std::vector<Task>& tasks) {
    int taskNum;
    displayTasks(tasks);
    std::cout << "Enter the number of the task you want to mark as completed: ";
    std::cin >> taskNum;

    if (taskNum > 0 && taskNum <= tasks.size()) {
        tasks[taskNum - 1].isCompleted = true;
        std::cout << "Task marked as completed!" << std::endl;
    }
    else {
        std::cout << "Invalid task number!" << std::endl;
    }
}

void deleteTask(std::vector<Task>& tasks) {
    int taskNum;
    displayTasks(tasks);
    std::cout << "Enter the number of the task you want to delete: ";
    std::cin >> taskNum;


    if (taskNum > 0 && taskNum <= tasks.size()) {
        tasks.erase(tasks.begin() + taskNum - 1);
        std::cout << "Task deleted sucessfully!" << std::endl;
    }
    else {
        std::cout << "Invalid task number!" << std::endl;
    }
}

void saveTasks(const std::vector<Task>& tasks, const std::string& filename) {
    std::ofstream outFile(filename);
        for (const auto& task : tasks) {
            outFile << task.description << "|" << task.isCompleted << "\n";
        }
        outFile.close();
        std::cout << "Tasks saved!" << std::endl;
}

void loadTasks(std::vector<Task>& tasks, const std::string& filename) {
    std::ifstream inFile(filename);
    std::string line;
    while (std::getline(inFile, line)) {
        Task task;
        size_t delimiterPos = line.find('|');
        task.description = line.substr(0, delimiterPos);
        task.isCompleted = line.substr(delimiterPos + 1) == "1";
        tasks.push_back(task);
    }
    inFile.close();
}

void showMenu() {
    std::cout << "\nTo-Do List Application\n";
    std::cout << "1. Add Task\n";
    std::cout << "2. Mark Task as Completed\n";
    std::cout << "3. Delete Task\n";
    std::cout << "4. Display Tasks\n";
    std::cout << "5. Save Tasks\n";
    std::cout << "6. Exit\n";
}

int main() {
    std::vector<Task> tasks;
    std::string filename = "tasks.txt";

    loadTasks(tasks, filename);

    int choice;
    do {
        showMenu();
        std::cout << "Choose an option: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            addTask(tasks);
            break;
        case 2:
            markTaskCompleted(tasks);
            break;
        case 3:
            deleteTask(tasks);
            break;
        case 4:
            displayTasks(tasks);
            break;
        case 5:
            saveTasks(tasks, filename);
            break;
        case 6:
            std::cout << "Exiting program. Goodbye!" << std::endl;
            break;
        default:
            std::cout << "Invalid choice. Try again." << std::endl;
        }
    } while (choice != 6);

    return 0;
}
