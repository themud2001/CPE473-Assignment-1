/*
    Assignment #1: LIFO Scheduler

    Moath Zayadneh - 136559
    Mohammed Aborob - 126529
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
    int delay;
    int response;
};

bool SortingComparator(Process el1, Process el2) {
    return el1.arrivalTime < el2.arrivalTime;
}

class Scheduler {
    private:
    vector<Process> processesList;
    vector<Process*> queue;
    string processesOrder = "";

    void CalculateStats(Process &element, int &timeline) {
        if (element.arrivalTime > timeline) {
            timeline += element.arrivalTime - timeline;
        }

        element.response = timeline - element.arrivalTime;
        timeline += element.processingTime;
        element.turnAround = timeline - element.arrivalTime;
        element.delay = element.turnAround - element.processingTime;
    }

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

    void WriteFile(string fileName) {
        ofstream file(fileName);

        if (file.is_open()) {
            file << processesOrder << endl;

            for (int i = 0; i < processesList.size(); i++) {
                file << processesList[i].name << ": ";
                file << "(response=" << processesList[i].response << ", ";
                file << "turnaround=" << processesList[i].turnAround << ", ";
                file << "delay=" << processesList[i].delay << ") ";
                file << endl;
            }
        }

        file.close();
    }

    void SortProcesses() {
        sort(processesList.begin(), processesList.end(), SortingComparator);
    }

    void Schedule() {
        int timeline = 0;
        
        for (int i = 0; i < processesList.size(); i++) {
            int tempIndex = i;

            if (i == 0) {
                CalculateStats(processesList[i], timeline);
                cout << processesList[i].name;
                processesOrder += processesList[i].name;
            } else if (processesList[i].arrivalTime < timeline) {
                queue.push_back(&processesList[i]);
            } else {
                CalculateStats(processesList[i], timeline);
                cout << processesList[i].name;
                processesOrder += processesList[i].name;
            }

            for (int j = tempIndex + 1; j < processesList.size(); j++) {
                if (processesList[j].arrivalTime < timeline) {
                    queue.push_back(&processesList[j]);
                    i++;
                } else {
                    break;
                }
            }

            for (int j = queue.size() - 1; j >= 0; j--) {
                CalculateStats(*queue[j], timeline);
                cout << queue[j]->name;
                processesOrder += queue[j]->name;
                queue.pop_back();
            }
        }
    }

    void PrintProcesses() {
        for (int i = 0; i < processesList.size(); i++) {
            cout << processesList[i].name << ": ";
            cout << "(response=" << processesList[i].response << ", ";
            cout << "turnaround=" << processesList[i].turnAround << ", ";
            cout << "delay=" << processesList[i].delay << ") ";
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
    scheduler.WriteFile("out.txt");
    
    system("pause");

    return 0;
}