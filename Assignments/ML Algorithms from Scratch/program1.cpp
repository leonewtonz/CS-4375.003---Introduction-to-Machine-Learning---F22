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


using namespace std;
// using matrix = vector<vector<int>>;

// Sigmoid
vector<double> sigmoid(vector<double> z) {
    vector<double> resultSig(z.size());
    for (int i=0; i<z.size(); i++){
        resultSig.at(i) = 1.0 / (1.0 + exp(-z.at(i)));
    }
    return resultSig;
}

// Matrix multiplication
vector<double> multiply(vector<vector<double>> m1, vector<double> m2)
{
    vector<double> resultMul(m1.size());
    for(int row = 0; row < m1.size(); row++) {
        for(int col = 0; col < m1.at(0).size(); col++) {
                resultMul.at(row) += m1.at(row).at(col) * m2.at(col) ;
            }
    }
    return resultMul;
}

// Matrix subtraction
vector<double> subtract(vector<double> m1, vector<double> m2)
{
    vector<double> resultSub(m1.size()); 
    for(int i = 0; i < resultSub.size(); i++) {
                resultSub.at(i) = m1.at(i) - m2.at(i);
    }
    return resultSub;
}

// Matrix addition
vector<double> addition(vector<double> m1, vector<double> m2)
{
    vector<double> resultAdd(m1.size()); 
    for(int i = 0; i < resultAdd.size(); i++) {
                resultAdd.at(i) = m1.at(i) + m2.at(i);
    }
    return resultAdd;
}

// Matrix transpose
vector<vector<double>> transpose(vector<vector<double>> m)
{
    vector<vector<double>> resultTrans(m.at(0).size(), vector<double>(m.size()));
    for (int row = 0; row < m.size(); row++) {
        for (int col = 0; col < m.at(0).size(); col++) {
            resultTrans.at(col).at(row) = m.at(row).at(col);
        }
    }
    return resultTrans;
}

// main function
int main(int argc, char** argv) 
{
    ifstream            inFS;  // Input file stream
    string              line;
    
    const int           numTrain = 800;
    const int           MAX_ITER = 100;
    string              survived_in, sex_in, dummy;
    vector<double>      sex(numTrain);
    vector<double>      survived(numTrain);

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
    while (index < numTrain) {
        
        getline(inFS, dummy, ','); // Remove 1st column
        getline(inFS, dummy, ','); // Remove 2nd column_pclass
        getline(inFS, survived_in, ',');
        getline(inFS, sex_in, ',');
        
        survived.at(index) = stod(survived_in);
        sex.at(index) = stod(sex_in);

        index++;
    }

    survived.resize(numTrain);
    sex.resize(numTrain);

    // Set up weight vector, label vector, and data matrix
    vector<double> weights(2, 1);  // Two rows with initial value = 1 (w0 = w1 = 1)
    vector<double> labels(survived);

    vector<vector<double>> dataMatrix(numTrain, vector<double>(2,1)); 
    int col = 1;
    for (int i = 0; i < dataMatrix.size(); i++){   
        dataMatrix[i][col] = sex[i];  // Fill 2nd column with vector sex
    }

    // Gradient Descent
    double             learningRate = 0.001;
    vector<double>     probVector(numTrain);
    vector<double>     error(numTrain);

 
    for (int iter = 0; iter < MAX_ITER; iter++){   
        probVector = sigmoid(multiply(dataMatrix, weights));
        error      = subtract(labels, probVector);

        vector<double> temp= multiply(transpose(dataMatrix), error);
        
        for (int i=0; i<temp.size(); i++){
            temp.at(i) = temp.at(i) * learningRate;
        }

        weights = addition(weights, temp);
    }

    cout << "\nCofficients:\t\tw0" << "\t\t\t\t\tw1" << endl;
    for(int i=0; i<weights.size(); i++){
        cout << "\t\t\t" << weights.at(i);
    }     
// debug
    return 0;
}


