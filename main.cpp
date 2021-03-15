#include <iostream>
#include <fstream>

#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

#include <stdlib.h>  //for rand just for testing 
#include <time.h>

using namespace std; 

int rows = 0;  //Counts the rows of the file
int cols = 0;  //counts the cols of the file

//fstreams can both read in and out data, unlike just ifstream and ofstreams 


//Takes in the fstream, 
//Or maybe, just takes in the vector instead of fstream
//takes in a pointer to 2d vector instead of fstream
//Pass in the row number from loop?                                                                            
//is feature to add just an int?
double leave_one_out_cross_validation(vector<vector<double>> &d , vector<double> &current_set, int feature_to_add) { //, int& r) { //temporarily for testing 
    double accuracy; 

    //initalize vector with cols - 1 with all 0 
    vector<double> object_to_classify(cols - 1, 0);
    double label_object_to_classify;

    //rows 
    //start at 1 or 0?
    for (int i = 0; i < rows; i++) {

        //initalize object to classify 
        //might need to edit with this size
        for (int j = 1; j < cols - 1; ++j) { 
            object_to_classify[j - 1] = d[i][j];        //makes this the value from the data 
        }

        label_object_to_classify = d[i][0];
        


        cout << "Looping over i, at the " << i + 1 << " location" << endl;
        cout << "The " << i + 1 << "th object is in this class: " << label_object_to_classify << endl;
    }
    
    
    return rand(); 
} 


void feature_search(string& file) {//, string& file) {need to take in text file as input 
    //ifstream myFile; 
    fstream myFile; 
    myFile.open(file);

    //Method for getting rows + cols of a text file 
    string line, item; 
    //int rows = 0;  //Counts the rows of the file
    //int cols = 0;  //counts the cols of the file

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

    
        //Make a 2D array from the string stream
        //double fileArray[rows][cols];
        //vector< vector<double>> Data(rows, vector<double>(cols, 0));  //inialize a 2d vector filled with all 0s 
        const int tempRows = rows;
        const int tempCols = cols; 

        //Adapted here: https://stackoverflow.com/questions/36708370/reading-from-txt-file-into-two-dimensional-array-in-c
        //Reads from the file + places data into an array
        
        //double Data[tempRows][tempCols];
        //would vector be better? 
        //vector<vector<double>> Data;

        //n rows, m columns 
        //initalize an n x m vector with 0s 
        vector<vector<double>> Data( rows, vector<double> (cols, 0)); 


        for(int i = 0; i < rows; i++)
            for(int j = 0; j < cols; j++)
                myFile >> Data[i][j];


        //test print of the array 
        /*
        for(int i = 0; i < rows; i++) { 
            //cout << endl;
            for(int j = 0; j < cols ; j++) {
                cout << Data[i][j] << " "; 
                //if (j = rows - 1) { cout << endl;}
            }   
            cout << endl;
        }
        */



        //Does this need to be in the file stream? 

        //psuedo code part from slides
        vector<double> current_set_of_features; //(cols); //initalize an empty set the size of the features
        double accuracy = 0; 

        
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
                else {  //the k feature hasn't been added yet
                    cout << "--Consider adding the " << k << " feature" << endl;

                    //cout << "in the loop test" << endl;

                    
                    accuracy = leave_one_out_cross_validation(Data, current_set_of_features, k+1);

                    if (accuracy > best_so_far_accuracy) {
                        best_so_far_accuracy = accuracy;
                        //feature_to_add_at_this_level.push_back(k);  //puts this feature in the array. 
                        feature_to_add_at_this_level = k;
                    }

                }
    
            }

            //current_set_of_features.at(i) = feature_to_add_at_this_level;   //might need to edit this 
            current_set_of_features.push_back(feature_to_add_at_this_level);

            cout << "On level " << i << " I added feature " << feature_to_add_at_this_level << " to current set" << endl;
        }



        //TESTING STUFF     
            //testing size of the current set of features 
            //for (int j = 0; j < current_set_of_features.size(); j++) { cout << current_set_of_features.at(j) << endl; }

            cout << rows << endl;
            cout << cols << endl;
            
        myFile.close();
    }

    return; 
}

int main() {
    //ifstream myFile; 

    srand(time(0)); //Just for stub 



    string file = "testFile.txt";
    //string file = "CS170_SMALLtestdata__65.txt";
    //string file = "CS170_largetestdata__7.txt";

    //Insert intro here 

    feature_search(file);


    


    return 0;
}