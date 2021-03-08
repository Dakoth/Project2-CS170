#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

#include <stdlib.h>  //for rand just for testing 

using namespace std; 


double accuracy(fstream& f) { //temporarily for testing 
    return rand() % 100; 
} 

void feature_search(string& file) {//, string& file) {need to take in text file as input 
    

    ifstream myFile; 
    myFile.open(file);

    //Method for getting rows + cols of a text file 
    string line, item; 
    int rows = 0;  //Counts the rows of the file
    int cols = 0;  //counts the cols of the file

    while (myFile.is_open()) {
        //Gets the number of cols and Rows from the file 
        //Adapted from here: http://www.cplusplus.com/forum/beginner/228327/
        while( getline(myFile, line)) {
            rows++;
            if ( rows == 1 ) {                // First row only: determine the number of columns
                stringstream ss( line );      // Set up up a stream from this line 
                while ( ss >> item ) cols++;  // Each item delineated by spaces adds one to cols
            }   
        }
        //

        //cols--; //accounts for the extra column counted
        //Clears the fstream + restarts it to the beginning
        //From here: https://stackoverflow.com/questions/7681555/resetting-the-end-of-file-state-of-a-ifstream-object-in-c
        myFile.clear();
        myFile.seekg(0, ios::beg);
        //

    


        vector<int> current_set_of_features; 

        //psuedo code part from slides
        for (int i = 1; i <= cols - 1; i++) {
            cout << "On the " << i << "th level of the search tree" << endl;

            for (int k = 1; k <= cols - 1; k++) {
                cout << "--Consider adding the " << k << "th feature" << endl;
            }
        }

        


        cout << rows << endl;
        cout << cols << endl;
        myFile.close();
    }



    return; 
}

int main() {
    //ifstream myFile; 

    //string file = "testFile.txt";
    string file = "CS170_SMALLtestdata__65.txt";
    //string file = "CS170_largetestdata__7.txt";

    //myFile.open(file);

    feature_search(file);



    return 0;
}