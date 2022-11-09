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

    void SortProcesses() {
        sort(processesList.begin(), processesList.end(), SortingComparator);
    }

    void Schedule() {
        int timeline = 0;
        vector<Process*> earlyQueue;
        vector<Process*> lateQueue;

        for (int i = 0; i < processesList.size(); i++) {
            if (processesList[i].arrivalTime <= timeline) {
                if (i == processesList.size() - 1) {
                    earlyQueue.push_back(&processesList[i]);
                    continue;
                } else if (processesList[i + 1].arrivalTime < timeline) {
                    earlyQueue.push_back(&processesList[i]);
                    continue;
                } else {
                    if (earlyQueue.size() > 0) {
                        earlyQueue.push_back(&processesList[i]);
                        continue;
                    }
                }
            } else {
                if (i == processesList.size() - 1) {
                    CalculateStats(processesList[i], timeline);
                    cout << processesList[i].name << " " << timeline << endl;
                } else if (processesList[i + 1].arrivalTime < processesList[i].arrivalTime + processesList[i].processingTime) {
                    lateQueue.push_back(&processesList[i]);
                    continue;
                }
            }

            CalculateStats(processesList[i], timeline);
            cout << processesList[i].name << " " << timeline << endl;
        }

        for (int i = earlyQueue.size() - 1; i >= 0; i--) {
            CalculateStats(*earlyQueue[i], timeline);
            cout << earlyQueue[i]->name;
            cout << " " << timeline << endl;
            earlyQueue.pop_back();
        }

        for (int i = lateQueue.size() - 1; i >= 0; i--) {
            CalculateStats(*lateQueue[i], timeline);
            cout << lateQueue[i]->name;
            cout << " " << timeline << endl;
            lateQueue.pop_back();
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
    
    system("pause");

    return 0;
}