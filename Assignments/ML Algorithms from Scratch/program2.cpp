/*
    CS 4375 - Intro to Machine Learning
    Dr. Karen Mazidi
    Author- Leo Nguyen
    NetID - ldn190002

    Machine Learning Algorithms from Scratch
    Program2: Naive Bayes
*/ 

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <chrono>
#include <iomanip>

using namespace std;

// main function
int main(int argc, char** argv) 
{
    ifstream            inFS;  // Input file stream
    string              line;
    
    const int           numTrain = 800;
    const int           MAX_ITER = 500000;
    const int           MAX_LEN = 1050;
    string              pclass_in, survived_in, sex_in, age_in, dummy;
    vector<double>      pclass(MAX_LEN);
    vector<double>      survived(MAX_LEN);
    vector<double>      sex(MAX_LEN);
    vector<double>      age(MAX_LEN);
    
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
        getline(inFS, pclass_in, ','); 
        getline(inFS, survived_in, ',');
        getline(inFS, sex_in, ',');
        getline(inFS, age_in, '\n');
        
        pclass.at(index) = stod(pclass_in);
        survived.at(index) = stod(survived_in);
        sex.at(index) = stod(sex_in);
        age.at(index) = stod(age_in);

        index++;
    }

    pclass.resize(index);
    survived.resize(index);
    sex.resize(index);
    age.resize(index);

    cout << "Closing file titanic_project.csv" << endl;
    inFS.close();    // Done with file, close it

    // Devide into train and test set
    // Train data
    vector<double>      trainPclass(numTrain);
    vector<double>      trainSurvived(numTrain);
    vector<double>      trainSex(numTrain);
    vector<double>      trainAge(numTrain);
    for (int i=0; i<numTrain; i++){
        trainPclass.at(i) = pclass.at(i);
        trainSurvived.at(i) = survived.at(i);
        trainSex.at(i) = sex.at(i);
        trainAge.at(i) = age.at(i);
    }   

    int numTest = survived.size() - numTrain;
    int k = 0;
    // Test data
    vector<double>      testPclass(numTest);
    vector<double>      testSurvived(numTest);
    vector<double>      testSex(numTest);
    vector<double>      testAge(numTest);
    for (int i=numTrain; i<sex.size(); i++){
        testPclass.at(k) = pclass.at(i);
        testSurvived.at(k) = survived.at(i);
        testSex.at(k) = sex.at(i);
        testAge.at(k) = age.at(i);
        k++;
    }

    // Calculate priors 
    vector<double> apriori(2,0);
    double  numSv   = 0;  // Number of survived
    double  numNSv  = 0;    // Number of not survived

    for( int i=0; i<numTrain; i++){
        if(trainSurvived.at(i) == 0){
            numNSv++;
        }else{
            numSv++;
        }
    }

    apriori.at(0) = numNSv / numTrain;
    apriori.at(1) = numSv / numTrain;

    cout << "\nPrior probability:"<< endl;
    cout << "Survived=no: " << apriori.at(0) << endl;
    cout << "Survived=no: " << apriori.at(1) << endl;
    // cout << "Survived=no: " << fixed << setprecision(6) << apriori.at(1) << endl;


    // Calculate likehoods for quanlitative data
    // Get survived counts for no or yes
    vector<double> countSurvived(2,0);
    countSurvived.at(0) = numNSv;
    countSurvived.at(1) = numSv;

    // Likehood for pclass
    vector<vector<double>> lhPclass(2, vector<double>(3,0));  // Matrix lhPclss [2 X 3]
    for (int row=0; row < lhPclass.size(); row++){
        for (int col=0; col < lhPclass.at(row).size(); col++){
            double numerator = 0;
            for (int k=0; k<numTrain; k++){
                if(trainPclass.at(k) == double(col + 1) && trainSurvived.at(k) == double(row)){
                    numerator++;
                }
            }
            lhPclass.at(row).at(col) = numerator / countSurvived.at(row);
        }
    }

    // Likehood for sex
    vector<vector<double>> lhSex(2, vector<double>(2,0));  // Matrix lhSex [2 x 2]
    for (int row=0; row < lhSex.size(); row++){
        for (int col=0; col < lhSex.at(row).size(); col++){
            double numerator = 0;
            for (int k=0; k<numTrain; k++){
                if(trainSex.at(k) == double(col) && trainSurvived.at(k) == double(row)){
                    numerator++;
                }
            }
            lhPclass.at(row).at(col) = numerator / countSurvived.at(row);
        }
    }

    // Likehood for age
    vector<double> ageMean(2,0);
    vector<double> ageVar(2,0);

    for (int sv=0; sv<2; sv++){  // sv = 0: mean not survived;   sv = 1 mean survived
        double sum   = 0;
        double count = 0;
        for (int k=0; k<numTrain; k++){
            if(trainSurvived.at(k) == sv){
                count++;
                sum += trainAge.at(k);
            }
        }

        ageMean.at(sv) = sum / count;
        double sumSquare = 0;

        for (int k=0; k<numTrain; k++){
            if(trainSurvived.at(k) == sv){
                sumSquare += pow(trainAge.at(k) - ageMean.at(sv), 2);
            }
        }
        ageVar.at(sv) = sumSquare / (count - 1);
    }

    // Probability density

    // Print out likehood for p(pClass|survived)
    cout << "\nLikehood values for p(pClass|survived)\n";
    for (int i = 0; i < lhPclass.size(); i++)
    {
        for (int j = 0; j < lhPclass.at(i).size(); j++)
        {
            cout << lhPclass.at(i).at(j) << " ";
        }
        cout << endl;
    }

    // Print out likehood for p(sex|survived)
    cout << "\nLikehood values for p(sex|survived)\n";
    for (int i = 0; i < lhSex.size(); i++)
    {   
        for (int j = 0; j < lhSex.at(i).size(); j++)
        {
        cout << lhPclass.at(i).at(j) << " ";
        }
    cout << endl;
    }

    // Print out ageMean and ageVar
    cout << "ageMean:\n";
    for(auto e:ageMean){
        cout << e << " ";
    }

    cout << "\nageVar:\n";
    for(auto e:ageVar){
        cout << e << " ";
    }

    return 0;
}


