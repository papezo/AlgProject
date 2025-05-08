// ConsoleApplication3.cpp : Tento soubor obsahuje funkci main. Provádění programu se tam zahajuje a ukončuje.
//

#include <iostream>
#include <fstream> 
#include <queue>
#include <string>
#include <map>
#include <unordered_map>
#include <iomanip>
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
    queue<int> restComponents;
    
    string line;
    int totalComponents = 0;
    int timePerFloor = 0;
    int finalTime = 0;

    // First line is the amount of the comps so we load it to totalComponents var
    if (getline(file, line))
    {
        totalComponents = stoi(line);
    }

    // Loading first 10 components from the file
    while (floors.size() < STORAGE_MAX && getline(file, line))
    {
        int number = stoi(line);
        floors.push_back(number);
    }

    // Rest of the components to the restComponents var
    while (getline(file, line))
    {
        restComponents.push(stoi(line));
    }

    while (!floors.empty())
    {
        map<int, int> floorCounts; // Time compelexity is O(log n), with unordered_map its O(1)
        int floorWithMost = 0;
        int max = 0;

        for (auto i : floors)
        {
            floorCounts[i]++;
        }

        // Find floor where the most components has to go
        for(const auto& pair : floorCounts)
        {
            int targetFloor = pair.first;
            int count = pair.second;

            if (count > max)
            {
                max = count;
                floorWithMost = targetFloor;
            }
        }

        int removedComps = 0; // max 3 comps can elevator transfer
        for (auto i = floors.begin(); i != floors.end();)
        {
            if (*i == floorWithMost && removedComps < 3)
            {
                i = floors.erase(i);
                removedComps++;
            }
            else {
                i++;
            }
        }
        if (removedComps > 0)
        {
            timePerFloor = 2 * floorWithMost;
            finalTime += timePerFloor;
        }
        
        // Loading restComponents to floors to repeat the process until its full (max 10 comps)
        while (floors.size() < STORAGE_MAX && !restComponents.empty())
        {
            floors.push_back(restComponents.front());
            restComponents.pop();
        }
    }
    return finalTime;

}


int second_simulation_UM(ifstream& file)
{
    vector<int> floors;
    queue<int> restComponents;

    string line;
    int totalComponents = 0;
    int timePerFloor = 0;
    int finalTime = 0;

    // First line is the amount of the comps so we load it to totalComponents var
    if (getline(file, line))
    {
        totalComponents = stoi(line);
    }

    // Loading first 10 components from the file
    while (floors.size() < STORAGE_MAX && getline(file, line))
    {
        int number = stoi(line);
        floors.push_back(number);
    }

    // Rest of the components to the restComponents var
    while (getline(file, line))
    {
        restComponents.push(stoi(line));
    }

    while (!floors.empty())
    {
        unordered_map<int, int> floorCounts; // Time compelexity is O(log n), with unordered_map its O(1)
        int floorWithMost = 0;
        int max = 0;

        for (auto i : floors)
        {
            floorCounts[i]++;
        }

        // Find floor where the most components has to go
        for (const auto& pair : floorCounts)
        {
            int targetFloor = pair.first;
            int count = pair.second;

            if (count > max)
            {
                max = count;
                floorWithMost = targetFloor;
            }
        }

        int removedComps = 0; // max 3 comps can elevator transfer
        for (auto i = floors.begin(); i != floors.end();)
        {
            if (*i == floorWithMost && removedComps < 3)
            {
                i = floors.erase(i);
                removedComps++;
            }
            else {
                i++;
            }
        }
        if (removedComps > 0)
        {
            timePerFloor = 2 * floorWithMost;
            finalTime += timePerFloor;
        }

        // Loading restComponents to floors to repeat the process until its full (max 10 comps)
        while (floors.size() < STORAGE_MAX && !restComponents.empty())
        {
            floors.push_back(restComponents.front());
            restComponents.pop();
        }
    }
    return finalTime;
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
    file.close();

    ifstream file2("lift_input_small.txt");

    if (!file2.is_open())
    {
        cout << "Can't open the input file" << endl;
        return 1;
    }
    int time2 = second_simulation_UM(file2);
    file2.close();

    cout << "Time of First Simulation : " << time << " unit of time" << endl;
    cout << "Time of Second Simulation: " << time2 << " unit of time" << endl;
    cout << "\n" << endl;

    int diff = time - time2;

    double percOfSecond = ((double)(time - time2) / time) * 100.0;

    cout << "Difference between simulations: " << diff << " unit of time" << endl;

    cout << fixed << setprecision(2);
    cout << "Second simulation (optimized) is faster by: " << percOfSecond << " %" << endl;

    return 0;
}

