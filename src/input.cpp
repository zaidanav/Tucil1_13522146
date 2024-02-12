#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime> 
#include <cstdlib>
#include <algorithm>

using namespace std;

struct Masukan {
    int bufferSize;
    int matrixHeight;
    int matrixWidth;
    int numberOfSequences;
    int maxSequenceSize;
    vector<vector<string>> matrix;
    vector<vector<string>> sequences;
    vector<int> rewards;
};

int findToken(const string &str) {
    stringstream ss(str);
    string word;
    int count = 0;

    while (ss >> word)
    {
        count++;
    }
    return count;
}

Masukan generateInput(int bufferSize, int matrixHeight, int matrixWidth, int numberOfSequences, int maxSequenceSize, const vector<string>& token, int jumlah_token_unik) {
    Masukan input;

    input.bufferSize = bufferSize;
    input.matrixHeight = matrixHeight;
    input.matrixWidth = matrixWidth;
    input.numberOfSequences = numberOfSequences;
    input.maxSequenceSize = maxSequenceSize;

    // Generate matrix
    input.matrix.resize(matrixHeight, vector<string>(matrixWidth));
    for (int i = 0; i < matrixHeight; i++) {
        for (int j = 0; j < matrixWidth; j++) {
            input.matrix[i][j] = token[rand() % jumlah_token_unik];
        }
    }

    // Generate sequences
    input.sequences.resize(numberOfSequences, vector<string>(maxSequenceSize));
    for (int i = 0; i < numberOfSequences; i++) {
        int seq_random = rand() % (maxSequenceSize - 2 + 1) + 2;
        for (int j = 0; j < seq_random; j++) {
            input.sequences[i][j] = token[rand() % jumlah_token_unik];
        }
    }

    // Generate rewards
    input.rewards.resize(numberOfSequences);
    for (int i = 0; i < numberOfSequences; i++) {
        input.rewards[i] = rand() % 100;
    }

    return input;
}

void printInputan(Masukan input) {
    cout << "\nData yang dihasilkan: \n\n";
    cout << "Buffer size: " << input.bufferSize << endl;
    cout << "Matrix Dimension: " << input.matrixHeight << "x" << input.matrixWidth << endl;
    cout << "\nMatrix: " << endl;
    for (int i = 0; i < input.matrixHeight; i++)
    {
        for (int j = 0; j < input.matrixWidth; j++)
        {
            cout << input.matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << "\nNumber of Sequences: " << input.numberOfSequences << endl;
    cout << "Sequence Length: " << input.maxSequenceSize << endl;
    for (int i = 0; i < input.numberOfSequences; i++)
    {
        cout << "Sequence " << i + 1 << ": ";
        for (int j = 0; j < input.sequences[i].size(); j++)
        {
            cout << input.sequences[i][j] << " ";
        }
        cout << "Reward: " << input.rewards[i] << endl;
    }
    cout << endl;
}

Masukan file() {
    Masukan input;
    string filename, line;
    int temp;
    string stringPath="../test/";
    cout << "Input file name (without .txt): ";
    cin >> filename;
    filename += ".txt";
    ifstream file(stringPath + filename);

    while (!file.is_open())
    {
        cout << "File not found" << endl;
        cout << "Input file name (without .txt): ";
        cin >> filename;
        filename += ".txt";
        file.open(filename);
    }

    file >> input.bufferSize >> input.matrixWidth >> input.matrixHeight;

    input.matrix.resize(input.matrixHeight, vector<string>(input.matrixWidth));
    for (int i = 0; i < input.matrixHeight; i++)
    {
        for (int j = 0; j < input.matrixWidth; ++j)
        {
            file >> input.matrix[i][j];
        }
    }

    file >> input.numberOfSequences;
    getline(file, line);
    input.maxSequenceSize = 0;

    input.sequences.resize(input.numberOfSequences, vector<string>(input.maxSequenceSize));
    for (int i = 0; i < input.numberOfSequences; i++)
    {
        getline(file, line);
        temp = findToken(line);
        if (temp > input.maxSequenceSize)
        {
            input.maxSequenceSize = temp;
            for (int i = 0; i < input.numberOfSequences; i++)
            {
                input.sequences[i].resize(input.maxSequenceSize);
            }
        }
        stringstream ss(line);
        string word;
        vector<string> words;
        int j = 0;
        while (ss >> word)
        {
            input.sequences[i][j] = word;
            j++;
        }
        getline(file, line);
        input.rewards.push_back(stoi(line));
    }

    file.close();
    return input;
}

Masukan cli() {
    Masukan input;
    string temp;
    int jumlah_token_unik;
    vector<string> token;

    cout << "Masukkan format CLI: " << endl;
    cin >> jumlah_token_unik;
    token.resize(jumlah_token_unik);
    for (int i = 0; i < jumlah_token_unik; ++i)
    {
        cin >> temp; 
        token[i] = temp;
    }
    cin >> input.bufferSize; 
    cin >> input.matrixHeight ;
    cin >> input.matrixWidth;
    cin >> input.numberOfSequences; 
    cin >> input.maxSequenceSize;
    input = generateInput(input.bufferSize, input.matrixHeight, input.matrixWidth, input.numberOfSequences, input.maxSequenceSize, token, jumlah_token_unik);    
    return input;
}