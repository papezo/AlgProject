// ConsoleApplication3.cpp : Tento soubor obsahuje funkci main. Provádění programu se tam zahajuje a ukončuje.
//

#include <iostream>
#include <fstream> 
#include <queue>
#include <string>
#include <map>
#include <unordered_map>
using namespace std;


const int STORAGE_MAX = 10; // Robot capacity of storage for components
const int ELEVATOR_MAX = 3; // Max elevator capacity of components at once

int first_simulation(ifstream& file)
{
    queue<int> q;
    string lineComponents;

    int final_time = 0;
    int timePerFloor = 0;
    int totalComponents = 0;

    // Storing the first line (which is amount of the components) in the totalComponents variable
    if (getline(file, lineComponents))
    {
        totalComponents = stoi(lineComponents);
    }

    // From now we start working from second line of the inout file
    while (q.size() < STORAGE_MAX && getline(file, lineComponents))
    {
        int number = stoi(lineComponents);
        q.push(number);
    }


    while (!q.empty())
    {
        int component = q.front();
        q.pop();

        timePerFloor = 2 * component;
        final_time += timePerFloor;

        if (q.size() < STORAGE_MAX && getline(file, lineComponents))
        {
            int number = stoi(lineComponents);
            q.push(number);
        }
    }

    
    return final_time;
}

int second_simulation(ifstream& file)
{
    vector<int> floors;
    
    string line;
    int totalComponents = 0;



    if (getline(file, line))
    {
        totalComponents = stoi(line);
    }



    while (floors.size() < STORAGE_MAX && getline(file, line))
    {
        int number = stoi(line);
        floors.push_back(number);
    }

    while (!floors.empty())
    {
        map<int, int> floorCounts; // Time compelexity is O(log n), with unordered_map its O(1)

        for (auto i : floors)
        {
            floorCounts[i]++;
        }
    }

}
int main()
{
    ifstream file("lift_input_small.txt");

    if (!file.is_open())
    {
        cout << "Can't open the input file" << endl;
        return 1;
    }

    int time = first_simulation(file);

    cout << "Celkovy cas: " << time << " unit of time" << endl;

    file.close();
    return 0;
}

