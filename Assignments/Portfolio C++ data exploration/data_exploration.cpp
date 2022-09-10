#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

// Sum function
double sum(vector<double> vect){
    double sum = 0;
    for (int i = 0; i < vect.size(); i++){
        sum = sum + vect.at(i);
    }
    return sum;
}

// Mean function
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
double median(vector<double> vect){   
    double median = 0;    
    int n = vect.size();

   
    if ( n % 2 == 0){  // Even Case
        double e2 = vect.at((n/2) - 1);
        double e1 = vect.at(n/2);
        median = (e1+e2) / 2;
    }   
    else{              // Odd Case
        median =  vect.at((n/2));
    }               

    return median;
}

// // Range function
// void range(vector<double> vect){
//     cout << "Min:" << vect.front() << "Max:" << vect.back() << endl
// }

// Print Stats function
void print_stats(vector<double> vect){
 
    sort(vect.begin(),vect.end());  // Sorting in Ascending order
    
    cout << "Sum: " << sum(vect) << endl;
    cout << "Mean: " << mean(vect) << endl;
    cout << "Median: " << median(vect) << endl;
    // cout << "Range: " << range(vect) << endl;
    

}
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

/*debug
cout << "1st " << rm.front() << endl;
cout << "last " << rm.back() << endl;
cout << "last " << rm.at((rm.size()-1)) << endl;
*/

    cout << "New length " << rm.size() << endl;
    
    cout << "Closing file Boston.csv" << endl;
    inFS.close();    // Done with file, close it

    cout << "Number of records: " << numObservations << endl;

//debug
    // cout << "Number of records: " << rm.at(0) << endl;
    // cout << "Number of records: " << medv.at(0) << endl;
//



    cout << "\nStats for rm" << endl;
    print_stats(rm);

    // cout << "\nStats for medv" << endl;
    // print_stats(medv);

    // cout << "\nCovariance = " << covar(rm, medv) endl;
    // cout << "\nCorrelation = " << cor(rm, medv) endl;
    // cout << "\nProgram terminated" << endl;
    
    return 0;
}


