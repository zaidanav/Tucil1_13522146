#include "solver.cpp"
#include <iostream>
#include <string>
#include <chrono> // Include the chrono library for time measurement
using namespace std;
using namespace std::chrono; // Use the chrono namespace

int main() {
    string inputType;
    cout << "Input type: \n1. cli\n2. file .txt\nselect: ";
    cin >> inputType;
    Masukan input;
    while (inputType != "1" && inputType != "2") {
        cout << "Invalid input type." << endl;
        cout << "Input type: \n1. cli\n2. file .txt\nselect: ";
        cin >> inputType;
    }
    if (inputType == "1") {  
        input = cli();
        printInputan(input);
    } else if (inputType == "2") {  
        input = file();
        printInputan(input);
    }

    // Measure the processing time for counting
    auto start = high_resolution_clock::now(); // Get the current time before counting starts
    
    vector<string> route;
    vector<Location> routePoints;
    vector<vector<bool>> visited(input.matrixHeight, vector<bool>(input.matrixWidth, false)); // Initialize visited matrix
    for (int i = 0; i < input.matrixWidth; ++i) {
        exploreRoutes(input, input.matrix, 0, i, route, routePoints, visited, input.bufferSize, true);
    }

    auto stop = high_resolution_clock::now(); // Get the current time after counting finishes
    auto duration = duration_cast<milliseconds>(stop - start); // Calculate the duration of counting
    
    if (maxReward != 0) {
        cout << "Max sequence: ";
        for (int i = 0; i < maxRoute.size(); ++i){
            cout << maxRoute[i] << " ";
        }
        cout << endl << "Location: "<< endl;
        for (int i = 0; i < maxRoute.size(); ++i){
            cout << maxRouteLocations[i].col+1 <<","<<maxRouteLocations[i].row+1 << endl;
        }
        cout << "Reward: " << maxReward << endl;
    }
    cout << "Processing time: " << duration.count() << " milliseconds" << endl; // Print the processing time
    
    string n;
    cout << "\nApakah ingin menyimpan solusi? (y/n)" << endl;
    cin >> n;

    while (n != "y" && n != "n") {
        cout << "Pilihan tidak valid\n"<< endl;
        cout << "Apakah ingin menyimpan solusi? (y/n)" << endl;
        cin >> n;
    }

    if (n == "y") {
        string filename;
        string path = "../test/";
        cout << "Masukkan nama file tanpa (.txt): ";
        cin >> filename;
        filename += ".txt";
        ofstream file(path + filename);

        if (!file.is_open()) {
            cout << "Gagal membuka file untuk penulisan" << endl;
            return 1;
        }

        file << maxReward << endl;

        for (int i = 0; i < maxRoute.size(); ++i) {
            file << maxRoute[i] << " ";
        }

        file << endl;

        for (int i = 0; i < maxRouteLocations.size(); ++i) {
            file << maxRouteLocations[i].col +1 << ", " << maxRouteLocations[i].row + 1 << endl;
        }

        file << endl << duration.count() << " ms";
        file.close();
    }
    return 0;
}
