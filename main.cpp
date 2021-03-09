#include <iostream>
#include <fstream>

#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

#include <stdlib.h>  //for rand just for testing 

using namespace std; 


//fstreams can both read in and out data, unlike just ifstream and ofstreams 


//Takes in the fstream, 
//Or maybe, just takes in the vector...
double leave_one_out_cross_validation(fstream& f, vector<double> current_set, double feature_to_add) { //temporarily for testing 
    return rand() % 100; 
} 


void feature_search(string& file) {//, string& file) {need to take in text file as input 
    //ifstream myFile; 
    fstream myFile; 
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

    
        //Maybe make a 2D array from the string stream
        //double fileArray[rows][cols];
        vector< vector<double>> fileMatrix(rows, vector<double>(cols, 0));  //inialize a 2d vector filled with all 0s 



        //Does this need to be in the file stream? 

        vector<double> current_set_of_features(cols); //initalize an empty set the size of the features
        double accuracy = 0; 

        //psuedo code part from slides
        for (int i = 1; i <= cols - 1; i++) {
            //vector<double> feature_to_add_at_this_level; 
            double feature_to_add_at_this_level; 

            double best_so_far_accuracy = 0; 
            cout << "On the " << i << "th level of the search tree" << endl;

            for (int k = 1; k <= cols - 1; k++) {
                
                //If the k-th feature hasn't been added yet 
                //only consider adding
                //below if statement is from: https://stackoverflow.com/questions/3450860/check-if-a-stdvector-contains-a-certain-object
                if (find(current_set_of_features.begin(), current_set_of_features.end(), k) != current_set_of_features.end()) {
                    //k feature has been added to the set 
                }
                else { 
                    cout << "--Consider adding the " << k << "th feature" << endl;

                    //cout << "in the loop test" << endl;

                    
                    accuracy = leave_one_out_cross_validation(myFile, current_set_of_features, k+1);

                    if (accuracy > best_so_far_accuracy) {
                        best_so_far_accuracy = accuracy;
                        //feature_to_add_at_this_level.push_back(k);  //puts this feature in the array. 
                        feature_to_add_at_this_level = k;
                    }

                }
    
            }
            current_set_of_features.at(i) = feature_to_add_at_this_level;   //might need to edit this 
            cout << "On level " << i << " I added featue " << feature_to_add_at_this_level << " to current set" << endl;
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