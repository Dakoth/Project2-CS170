#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <stdlib.h>  //for rand just for testing 

using namespace std; 


double accuracy(fstream& f) { //temporarily for testing 
    return rand() % 100; 
} 

void feature_search() {//need to take in text file as input 
    vector<double> current_set_of_features; 



    return; 
}

int main() {
    ifstream myFile; 

    string file = "testFile.txt";

    myFile.open(file);

    while (myFile.fail()) {
        cout << "file opened ebic" << endl;
    }

    cout << "ebic" << endl;
    myFile.close();

    return 0;
}