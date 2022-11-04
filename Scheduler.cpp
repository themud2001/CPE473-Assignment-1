/*
    Assignment #1: LIFO Scheduler

    Moath Zayadneh - 136559
    Mohammed Aborob - ID
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Process {
    public:
    string name;
    int arrivalTime;
    int processingTime;
    int turnAround;
    int response;
};

bool SortingComparator(Process el1, Process el2) {
    return el1.arrivalTime < el2.arrivalTime;
}

class Scheduler {
    private:
    vector<Process> processesList;
    vector<Process> queue;

    public:
    void ReadFile(string fileName) {
        int numberOfProcesses;

        ifstream file(fileName);
        file >> numberOfProcesses;

        if (file.is_open()) {
            for (int i = 0; i < numberOfProcesses; i++) {
                Process temp = Process();
                file >> temp.name;
                file >> temp.arrivalTime;
                file >> temp.processingTime;
                processesList.push_back(temp);
            }
        } else {
            cout << "Cannot read the file!" << endl;
        }

        file.close();
    }

    void SortProcesses() {
        sort(processesList.begin(), processesList.end(), SortingComparator);
    }

    void Schedule() {
        int timeline = 0;

        for (int i = 0; i < processesList.size(); i++) {
            if (processesList[i].arrivalTime < timeline) {
                if (i == processesList.size() - 1) {
                    queue.push_back(processesList[i]);
                    continue;
                } else if (processesList[i + 1].arrivalTime < timeline) {
                    queue.push_back(processesList[i]);
                    continue;
                }
            }

            cout << processesList[i].name;
            timeline += processesList[i].processingTime;
        }

        for (int i = queue.size() - 1; i >= 0; i--) {
            cout << queue[i].name;
        }
    }

    void PrintProcesses() {
        for (int i = 0; i < processesList.size(); i++) {
            cout << processesList[i].name << " ";
            cout << processesList[i].arrivalTime << " ";
            cout << processesList[i].processingTime << " ";
            cout << endl;
        }
    }
};

int main() {
    Scheduler scheduler = Scheduler();

    scheduler.ReadFile("in.txt");
    scheduler.SortProcesses();
    scheduler.Schedule();
    cout << endl;
    scheduler.PrintProcesses();
    
    system("pause");

    return 0;
}