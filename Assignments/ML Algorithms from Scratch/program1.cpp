/*
    CS 4375 - Intro to Machine Learning
    Dr. Karen Mazidi
    Author- Leo Nguyen
    NetID - ldn190002

    Machine Learning Algorithms from Scratch
    Program1: Logistic Regression
*/ 



#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <regex>
#include <iterator>

using namespace std;

// regex delimiter{ "," };
// constexpr size_t targetColumn;
// const int   survivedColumn = 3;
// const int   sexColumn = 4;

// struct columnExtract(targetColumn) { 

//     // Overload extractor. Read a complete line
//     friend std::istream& operator>>(std::istream& is, String11& s11) { 

//         // Read a complete line
//         if (std::string line{}; std::getline(is, line)) {

//             // Split it into tokens
//             std::vector token(std::sregex_token_iterator(line.begin(), line.end(), delimiter, -1), {});
//             // We only need one column
//             if (targetColumn < token.size()) {
//                 // Get column 11
//                 s11.result = token[targetColumn];
//             }
//         }
//         return is; 
//     }

//     // Cast the type 'String11' to double
//     operator double() const { return std::stod(result); }

//     // Temporary to hold the resulting string
//     std::string result{};
// };


// Sigmoid
double sigmoid(double z) {
    return 1.0 / (1.0 + exp(-z));
}



// main function
int main(int argc, char** argv) 
{
    ifstream        inFS;  // Input file stream
    string          line;
    
    const int       numTrain = 3;
    string          survived_in, sex_in, dummy;
    vector<int>     sex(numTrain);
    vector<int>     survived(numTrain);

 

    // Try to open file
    cout << "Open file titanic_project.csv" << endl;
    inFS.open("titanic_project.csv");
    if (!inFS.is_open()) {
        cout << "Could not open file titanic_project.csv" << endl;
        return 1; // Indicatea error
    }

    // Read print out the heading line of csv file
    cout << "Reading line 1" << endl;
    getline(inFS, line);
    cout << "Heading: " << line << endl;

    int index = 0;
    while (index < 3) {
        
        getline(inFS, dummy, ','); // Remove 1st column
        getline(inFS, dummy, ','); // Remove 2nd column_pclass
        getline(inFS, survived_in, ',');
        getline(inFS, sex_in, ',');

        // cout << "Survived: " << survived_in << endl; // debug
        // cout << "Sex: " << sex_in << endl; // debug
        
        survived.at(index) = stoi(survived_in);
        sex.at(index) = stoi(sex_in);

        index++;
    }

    survived.resize(numTrain);
    sex.resize(numTrain);


    // Set up weight vector, label vector, and data matrix
    vector<int> weight(numTrain, 1);
    vector<int> labels(survived);
    // vector<vector<int>> vect;

   





    
// How to work on vector    
    // vector<vector<int>> vect;
    // {
    //     {1, 2, 3},
    //     {4, 5, 6},
    //     {7, 8, 9}
    // };

    vector<vector<int>> vect(numTrain, vector<int>(2,1));

    int col = 1;
    cout << "2d vectors_single element: " << vect[1][1] << endl;
    // cout << "2d vectors_single column: " << vect[][1] << endl;

   
    // for (int i = 0; i < vect.size(); i++) 
    // {
    //     for (int j = 0; j < vect[i].size(); j++)
    //     {
    //         cout << vect[i][j] << " ";
    //     }    
    //     cout << endl;
    // }

    // for (int i = 0; i < vect.size(); i++) 
    // {   
    //     cout << vect[i][col] << " ";  
    //     cout << endl;
    // }

    vector<int> a = {3,4,5};
    for (int i = 0; i < vect.size(); i++) 
    {   
        vect[i][col] = a[i];
    }

    for (int i = 0; i < vect.size(); i++) 
    {   
        cout << vect[i][col] << " ";  
        cout << endl;
    }

    
    return 0;
}


