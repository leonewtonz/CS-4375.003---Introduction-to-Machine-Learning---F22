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
#include <chrono>

using namespace std;

// Sigmoid function
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

// Evaluate function: calculate accuracy, sensitivity, specificity
void evaluate(vector<double> preds, vector<double> test){
    double  accuracy, sensitivity, specificity;
    double  sum = 0;
    int     size = test.size();

    // cout << "\n\nNumber of test samples: " << test.size();
    // Calculate the total correct predict
    for (int i=0; i<size; i++){
        if (preds.at(i) == test.at(i)){
            sum++;
        }
    }

    // Calculate the confusion matrix
    // 0 mean not survived
    // 1 mean survived
    double actualNotSurvived = 0;
    double predictTotalNotSurvived = 0;

    double tp = 0; 
    double fp, fn, tn;

    for (int i = 0; i<size; i++){
        if (test.at(i) == 0){
            actualNotSurvived ++;
        }
    }
    // cout << "\nactualNotSurvived: " << actualNotSurvived;

    for (int i = 0; i<size; i++){
        if (preds.at(i) == 0){
            predictTotalNotSurvived ++;
        }
    }
    // cout << "\npredictTotalNotSurvived: " << predictTotalNotSurvived;

    for (int i = 0; i<size; i++){
        if(preds.at(i) == 0 && preds.at(i) == test.at(i)){
            tp ++;
        }
    }
    // cout << "\nTP: " << tp;

    fn = actualNotSurvived - tp;
    // cout << "\nFN: " << fn;

    fp = predictTotalNotSurvived - tp;
    // cout << "\nFP: " << fp;

    tn = size - (tp + fp + fn);
    // cout << "\nTN: " << tn;

    // Calculate the accuracy, sensitivity, specificity
    accuracy = sum / size;
    sensitivity = tp / (tp + fn);
    specificity = tn / (tn + fp);

    // Print out the accuracy, sensitivity, specificity
    cout << "\n\nAccuracy: " << accuracy;
    cout << "\nSensitivity: " << sensitivity;
    cout << "\nSpecificity: " << specificity;
}

// main function
int main(int argc, char** argv) 
{
    ifstream            inFS;  // Input file stream
    string              line;
    
    const int           numTrain = 800;
    const int           MAX_ITER = 500000;
    const int           MAX_LEN = 1050;
    string              survived_in, sex_in, dummy;
    vector<double>      sex(MAX_LEN);
    vector<double>      survived(MAX_LEN);

    // Try to open file
    cout << "Open file titanic_project.csv" << endl;
    inFS.open("titanic_project.csv");
    if (!inFS.is_open()) {
        cout << "Could not open file titanic_project.csv" << endl;
        return 1; // Indicatea error
    }

    // Read print out the heading line of csv file
    // cout << "Reading line 1" << endl;
    getline(inFS, line);  // Remove the heading
    // cout << "Heading: " << line << endl;

    // Copy the survived column and sex column
    int index = 0;
    while (inFS.good()) {
        
        getline(inFS, dummy, ','); // Remove 1st column
        getline(inFS, dummy, ','); // Remove 2nd column_pclass
        getline(inFS, survived_in, ',');
        getline(inFS, sex_in, ',');
        
        survived.at(index) = stod(survived_in);
        sex.at(index) = stod(sex_in);

        index++;
    }

    survived.resize(index);
    sex.resize(index);

    cout << "Closing file titanic_project.csv" << endl;
    inFS.close();    // Done with file, close it

    // Devide into train and test set
    // Train data
    vector<double>      trainSurvived(numTrain);
    vector<double>      trainSex(numTrain);
    for (int i=0; i<numTrain; i++){
        trainSurvived.at(i) = survived.at(i);
        trainSex.at(i) = sex.at(i);
    }   

    int numTest = survived.size() - numTrain;
    int k = 0;
    // Test data
    vector<double>      testSurvived(numTest);
    vector<double>      testSex(numTest);
    for (int i=numTrain; i<sex.size(); i++){
        testSurvived.at(k) = survived.at(i);
        testSex.at(k) = sex.at(i);
        k++;
    }

    // Setup test set
    vector<vector<double>> testMatrix(numTest, vector<double>(2,1)); 
    int col = 1;
    for (int i = 0; i < testMatrix.size(); i++){   
        testMatrix[i][col] = testSex[i];  // Fill 2nd column with testSex
    }

    // Set up weight vector, label vector, and data matrix (Train set)
    vector<double> weights(2, 1);  // Two rows with initial value = 1 (w0 = w1 = 1)
    vector<double> labels(trainSurvived);

    vector<vector<double>> dataMatrix(numTrain, vector<double>(2,1)); 
    for (int i = 0; i < dataMatrix.size(); i++){   
        dataMatrix[i][col] = trainSex[i];  // Fill 2nd column with trainSex
    }

    // Gradient Descent
    double             learningRate = 0.001;
    vector<double>     probVector(numTrain);
    vector<double>     error(numTrain);

    auto start = std::chrono::steady_clock::now();  // Begin of training time of algorithm
    for (int iter = 0; iter < MAX_ITER; iter++){   
        probVector = sigmoid(multiply(dataMatrix, weights));
        error      = subtract(labels, probVector);

        vector<double> temp= multiply(transpose(dataMatrix), error);
        
        for (int i=0; i<temp.size(); i++){
            temp.at(i) = temp.at(i) * learningRate;
        }

        weights = addition(weights, temp);
    }                                               
    auto end = std::chrono::steady_clock::now();  // End of training time of algorithm
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "\nElapsed time for training algorithm: " << elapsed_seconds.count() << "s\n";

    // Printout Coefficients
    double w0 = weights.at(0);
    double w1 = weights.at(1);
    cout << "\nCoefficients:";
    cout << "\nw0: " << w0;
    cout << "\nw1: " << w1;

    // Calculate predict vector
    vector<double>     predicted(numTest);
    vector<double>     probabilities(numTest);
    vector<double>     predictions(numTest);

    predicted       = multiply(testMatrix,weights);
    for (int i = 0; i<numTest; i++){
        probabilities.at(i) = exp(predicted.at(i)) / (1 + exp(predicted.at(i)));
        if (probabilities.at(i) > 0.5) {
            predictions.at(i) = 1;
        } else {
            predictions.at(i) = 0;
        }
    }

    // Calculate accuracy, sensitivity, specificity
    evaluate(predictions, testSurvived);

    return 0;
}


