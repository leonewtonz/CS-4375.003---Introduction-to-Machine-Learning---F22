/*
    CS 4375 - Intro to Machine Learning
    Dr. Karen Mazidi
    Student - Leo Nguyen
    NetID - ldn190002
*/ 

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cmath>

using namespace std;

// Sum function
// This will sum the value of all elements
double sum(vector<double> vect){
    double sum = 0;
    for (int i = 0; i < vect.size(); i++){
        sum = sum + vect.at(i);
    }
    return sum;
}

// Mean function
// Mean = Average = sum of all elements / number of element
double mean(vector<double> vect){
    double mean = 0;
    double sum = 0;
    for (int i = 0; i < vect.size(); i++){
        sum = sum + vect.at(i);
    }
    mean = sum / vect.size();
    return mean;
}

// Median function
// Median mean we take the medium value of the set of element
// Let n is the number of element. S is the set of element. Index start at 0
// There are 2 cases:
//  -   n is "Odd": median = S[n/2] = Value of set S at index n/2
//  -   n is "Even": median = {S[n/2] + S[(n/2)-1]} / 2
double median(vector<double> vect){   
    double median = 0;    
    int n = vect.size();

   
    if ( n % 2 == 0){  // Even Case
        double e1 = vect.at(n/2);
        double e2 = vect.at((n/2) - 1);   
        median = (e1+e2) / 2;
    }   
    else{              // Odd Case
        median =  vect.at((n/2));
    }               

    return median;
}

// Range function
// range = max -min
double range(vector<double> vect){
    double range = 0;
    double max = 0;
    double min = 0;
    
    min = vect.front();
    max = vect.back();

    range = max - min;

    return range;
}

// Print Stats function
void print_stats(vector<double> vect){
 
    sort(vect.begin(),vect.end());  // Sorting in Ascending order
    
    cout << "Sum: " << sum(vect) << endl;
    cout << "Mean: " << mean(vect) << endl;
    cout << "Median: " << median(vect) << endl;
    cout << "Range: " << range(vect) << endl;
}

// Covariance function
double covar(vector<double> rm_v, vector<double> medv_v){
    double covar = 0;

    double sumEValue = 0;

    double rmMean = mean(rm_v);
    double medvMean = mean(medv_v);

    int n = rm_v.size();

    for (int i = 0; i < n; i++){
        sumEValue = sumEValue + ((rm_v.at(i) - rmMean) * (medv_v.at(i) - medvMean));
    }
    covar = sumEValue / (n-1);
    return covar;
}  

// Correlation function
double cor(vector<double> rm_v, vector<double> medv_v){
    double cor = 0;

    double covarValue = covar(rm_v, medv_v);
    
    double sumSquareDiff_rm = 0;    // Sum of all square different in vector rm
    double sumSquareDiff_medv = 0;  // Sum of all square different in vector medv

    double sigma_rm = 0;  // Standard deviation of vector rm (Sigma of vector rm)
    double sigma_medv = 0; // Standard deviation of vector medv (Sigma of vector medv)


    double rmMean = mean(rm_v);
    double medvMean = mean(medv_v);
    
    int n = rm_v.size();

    for (int i = 0; i < n; i++){
        sumSquareDiff_rm = sumSquareDiff_rm + pow((rm_v.at(i) - rmMean),2);
        sumSquareDiff_medv = sumSquareDiff_medv + pow((medv_v.at(i) - medvMean),2);
    }
    
    sigma_rm = sqrt(sumSquareDiff_rm / n);
    sigma_medv =sqrt(sumSquareDiff_medv / n);

    cor = covarValue / (sigma_rm * sigma_medv);
    return cor;
}  

// main function
int main(int argc, char** argv) 
{
    ifstream        inFS;  // Input file stream
    string          line;
    string          rm_in, medv_in;
    const int       MAX_LEN = 1000;
    vector<double>  rm(MAX_LEN);
    vector<double>  medv(MAX_LEN);

    // Try to open file
    cout << "Open file Boston.csv" << endl;

    inFS.open("Boston.csv");
    if (!inFS.is_open()) {
        cout << "Could not open file Boston.csv" << endl;
        return 1; // Indicatea error
    }

    // Can now use inFS stream like cin stream
    // Boston.csv only contain 2 doubles column

    cout << "Reading line 1" << endl;
    getline(inFS, line);

    // Print out heading
    cout << "Heading: " << line << endl;

    int numObservations = 0;
    while (inFS.good()) {
        
        getline(inFS, rm_in, ',');
        getline(inFS, medv_in, '\n');

        rm.at(numObservations) = stof(rm_in);
        medv.at(numObservations) = stof(medv_in);

        numObservations++;
    }

    rm.resize(numObservations);
    medv.resize(numObservations);

    cout << "New length " << rm.size() << endl;
    
    cout << "Closing file Boston.csv" << endl;
    inFS.close();    // Done with file, close it

    cout << "Number of records: " << numObservations << endl;

    cout << "\nStats for rm" << endl;
    print_stats(rm);

    cout << "\nStats for medv" << endl;
    print_stats(medv);

    cout << "\nCovariance = " << covar(rm, medv) << endl;
    cout << "\nCorrelation = " << cor(rm, medv) << endl;
    cout << "\nProgram terminated" << endl;
    
    return 0;
}


