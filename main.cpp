#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdlib.h>  //for rand just for testing 
#include <math.h>
#include <limits>   //Used for infinity 
#include <iomanip>  //setprecision
#include <time.h>

#include <numeric>  //Used to fill array for backward selection

#include <chrono>   //For getting execution time 

using namespace std; 

int rows = 0;  //Counts the rows of the file
int cols = 0;  //counts the cols of the file
int algorithm_Choice = 0;

//fstreams can both read in and out data, unlike just ifstream and ofstreams                                      
//is feature to add just an int?               
//If I make a copy of Data, then I can freely edit it as I please,
    //But this could make things much more costly if I do that...   
    //got rid of &d, maybe this works?                                                      
double leave_one_out_cross_validation(vector<vector<double>> d, vector<double> &current_set, double feature_to_add) { //temporarily for testing 
    vector<double> tempSet = current_set;   //Temp set is the current set of features + the feature you're looking to add

    //Add the feature to add to the set for forward selection
    if (algorithm_Choice == 1) {
        tempSet.push_back(feature_to_add);  
    }
    else {  //else take the feature to remove it for back elim 
        if ( feature_to_add != 0) {             //Just sets the feature to 0
            //tempSet.erase(tempSet.begin() + feature_to_add - 1);
            tempSet.at(feature_to_add - 1) = 0;
        }
    }
    
    
    double accuracy; 
    double nearest_neighbor_distance;
    double nearest_neighbor_location; 
    double nearest_neighbor_label; 
    double distance, sum;   //sum used for eucidean distance 

    double number_correctly_classified = 0;

    //initalize vector with cols - 1 with all 0 
    vector<double> object_to_classify(cols - 1, 0);
    double label_object_to_classify = 0;

    //Edit parts of the Data vector to IGNORE 
   for (int i = 0; i < rows; i++) {
        for (int j = 1; j <= cols - 1; j++)  {   
            //Checks at each index if it's equal to the index of the temp set
            for (int x = 0; x < tempSet.size(); x++) {       //Goes thru the testSet 
                //Need to add + 1 to not accidently change the class label?
            
                
                //FORWARD SELECTION
                if (algorithm_Choice == 1) {   
                    if (find(tempSet.begin(), tempSet.end(), j) != tempSet.end()) {
                        //If the feature is in the tempSet, do nothing 
                    }
                    else { //else, sets the feature value to 0 
                        d[i][j] = 0;             //Sets the value of the i-th row, with added feature to be 0 // should it be +1?
                    }
                }
                else {  //BACKWARDS ELIMATION
                   
                    if (find(tempSet.begin(), tempSet.end(), j) != tempSet.end()) {
                    //if (j != tempSet.at(x)) {
                        //d[i][j] = 0;             //Sets the value of the i-th row, with added feature to be 0 
                        //If the feature is in the tempSet, do nothing 
                    }
                    else { //else, sets the feature value to 0 
                        //if (d[i][j] != 0)
                        d[i][j] = 0; 
                        //d[i][j] = 0;
                        //else do nothing 
                    }
                    
                    /*if (tempSet.at(x) == 0) {       //If comes arcross a 0, change that element in the data 
                        d[i][j] = 0;
                    }
                    */
                }
            }
        }
   }
    //test print of edited vector
     /*
        for(int i = 0; i < rows; i++) { 
            //cout << endl;
            for(int j = 0; j <= cols - 1; j++) {
                cout << d[i][j] << " "; 
                //if (j = rows - 1) { cout << endl;}
            }   
            cout << endl;
        }
    //*/

    //Psuedocode part
    for (int i = 0; i < rows; i++) {

        //initalize object to classify 
        for (int j = 1; j <= cols - 1; j++) { 
            object_to_classify[j - 1] = d[i][j];        //makes this the value from the data 
        }

        label_object_to_classify = d[i][0];

        //setprecision(9);  //Don't know if this makes a difference

        //From here: https://en.cppreference.com/w/cpp/types/numeric_limits/infinity
        nearest_neighbor_distance = numeric_limits<double>::infinity();
        nearest_neighbor_location = numeric_limits<double>::infinity();

        for (int k = 0; k < rows; k++) {
            //Eucludean Distance part 
            if (k != i) {   //Don't compare to yourself

                //Calculate Euclidean distance
                //MIGHT NEED TO FIX 
                sum = 0;
                double diff = 0;
                for(int z = 1; z <= cols - 1; z++){     //Should be cols - 1?
                        sum += pow(object_to_classify[z - 1] - d[k][z], 2);
                        //diff = object_to_classify[z - 1] - d[k][z];
                        //sum += diff*diff;
                }
                distance = sqrt(sum);          

                if (distance < nearest_neighbor_distance) {
                    nearest_neighbor_distance = distance;
                    nearest_neighbor_location = k;                      ///IS THIS CORRECT?????
                    nearest_neighbor_label = d[nearest_neighbor_location][0];
                }
            }
        }
        
        if (label_object_to_classify == nearest_neighbor_label) {
            number_correctly_classified += 1;
        }
    }
    accuracy = number_correctly_classified / (rows);    //number of rows is the size of the data
    //cout << "accuracy is " << setprecision(2) << accuracy << endl;

    //int TESTTT;
    //cin >> TESTTT;

    return accuracy; 
} 


//////////////////////////////////////////////////////////////////////////////////////////////////////
void feature_search(vector<vector<double>> &Data) { //string& file) {//, string& file) {need to take in text file as input 
    //psuedo code part from slides

    vector<double> current_set_of_features;
    //For Foward Selection
    if (algorithm_Choice == 1) {
    }
    else {      //For back elim
        current_set_of_features.resize(cols -1);
        //From here: https://stackoverflow.com/questions/17694579/use-stdfill-to-populate-vector-with-increasing-numbers
        iota(current_set_of_features.begin(), current_set_of_features.end(), 1);

        //for (int i = 0; i < current_set_of_features.size(); i++ )
        //    cout << current_set_of_features.at(i) << endl;
    }
    
    //int TESTTTT;
    //cin >> TESTTTT;

    vector<double> best_set_of_features = current_set_of_features;    //Used to measure the best set of features
    double accuracy = 0; 

    double best_so_far_accuracy = 0; 
    double feature_to_add_at_this_level; 

    double BEST_accuracy = best_so_far_accuracy; 

    double inital_accuracy = leave_one_out_cross_validation(Data, current_set_of_features, 0);

    cout << "Beginning Search" << endl;
    cout << endl;
    for (int i = 1; i <= cols - 1; i++) {
        best_so_far_accuracy = 0; 
        feature_to_add_at_this_level = 0; //Make this always 0 just in case? 

       //cout << "On the " << i << "th level of the search tree" << endl;      //COMMENTED OUT

        for (int k = 1; k <= cols - 1; k++) {
            
            //FORWARD SELECTION 
            if (algorithm_Choice == 1) {
                //If the k-th feature hasn't been added yet 
                //below if statement is from: https://stackoverflow.com/questions/3450860/check-if-a-stdvector-contains-a-certain-object
                if (find(current_set_of_features.begin(), current_set_of_features.end(), k) != current_set_of_features.end()) {
                    //k feature has been added to the set 
                }
                else {  //the k feature hasn't been added yet
                    //cout << "--Consider adding the " << k << " feature" << endl;      
                    //*******************************
                    accuracy = leave_one_out_cross_validation(Data, current_set_of_features, k);    
                    //*******************************

                    cout << "   Using feature(s) { ";
                    for (int p = 0; p < current_set_of_features.size(); p++) {
                        cout << current_set_of_features[p] << " ";
                    }
                    cout << k << " } accuracy is " << accuracy << endl;


                    if (accuracy > best_so_far_accuracy) {
                        best_so_far_accuracy = accuracy;
                        feature_to_add_at_this_level = k;
                    }
                }
            }           
            else {  //BACKWARD ELIMINATION
                //If the k-th feature hasn't been added yet 
                if (find(current_set_of_features.begin(), current_set_of_features.end(), k) != current_set_of_features.end()) {
                    
                    //k feature has been added to the set 
                    //cout << "--Consider removing the " << k << " feature" << endl;     
                    //*******************************
                    accuracy = leave_one_out_cross_validation(Data, current_set_of_features, k);    
                    //*******************************

                    //Print matching paper
                    cout << "   Using feature(s) { ";
                    for (int p = 0; p < current_set_of_features.size(); p++) {  //size  -1? 
                        if (current_set_of_features[p] > 0) { // && (p == k - 1) )
                            if (p != k - 1) 
                                cout << current_set_of_features[p] << " ";
                        }
                    }
                    cout << " } accuracy is " << accuracy << endl;


                    if (accuracy > best_so_far_accuracy) {
                        best_so_far_accuracy = accuracy;
                        feature_to_add_at_this_level = k;
                    }
                }
                else {  //the k feature hasn't been added yet
                    
                }
            }
        }

        //Only add to the best accuracy set if the GLOBAL MAX accuracy is best than local max
        if (best_so_far_accuracy > BEST_accuracy) {
            BEST_accuracy = best_so_far_accuracy;

            if (algorithm_Choice == 1) {
                best_set_of_features.push_back(feature_to_add_at_this_level);
            }
            else {
                best_set_of_features.at(feature_to_add_at_this_level - 1) = 0;//.erase(best_set_of_features.begin() + feature_to_add_at_this_level - 1); //this should work?
            }

           
        }


        if (algorithm_Choice == 1) { //Forward selection
            current_set_of_features.push_back(feature_to_add_at_this_level);
            //cout << "On level " << i << " I added feature " << feature_to_add_at_this_level << " to current set" << endl;
        }
        else { //BACK ELIM, ****
            //current_set_of_features.erase(current_set_of_features.begin() + feature_to_add_at_this_level - 1);
            current_set_of_features.at(feature_to_add_at_this_level - 1) = 0;       //Sets the removed feature to 0, Don't know if this works
            //cout << "On level " << i << " I removed feature " << feature_to_add_at_this_level << " from current set" << endl;
        }

        //If the BEST Accuracy decreases as it's going
        if (BEST_accuracy > best_so_far_accuracy) {
            cout << "(Warning, Accuracy has decreased! Continuing search in case of local maxima)" << endl;
        }

        cout << "Feature set { "; 
            for (int p = 0; p < current_set_of_features.size(); p++) {
                if (current_set_of_features.at(p) > 0)
                    cout << current_set_of_features[p] << " ";
            }
            cout << " } was best, accuracy is " << best_so_far_accuracy << endl;
    }


    double all_features_accuracy = leave_one_out_cross_validation(Data, current_set_of_features, 0);

    //TESTING STUFF     
    //testing size of the current set of features 
    //for (int j = 0; j < current_set_of_features.size(); j++) { cout << current_set_of_features.at(j) << endl; }

    //cout << rows << endl;
    //cout << cols << endl;

    cout << "Inital Accuracy (with all/no features) is: " << inital_accuracy << endl;
    //cout << "Best Accuracy was " << BEST_accuracy << endl;


    cout << "Finished Search!!! The best feature subset is { ";
    for (int i = 0; i < best_set_of_features.size(); i++) {
        if (best_set_of_features[i] > 0)            //Accounts for backwards selection
            cout << best_set_of_features[i] << " ";
    }
    cout << "}, which has an accuracy of " << BEST_accuracy << endl;


    cout << "Final Accuracy (with all/no features) is: " << all_features_accuracy << endl;
    return; 
}

int main() {
    string file = "";
    fstream myFile; 
    //file = "CS170_SMALLtestdata__1.txt";  //Set up like the example in the slides 
    // file = "CS170_SMALLtestdata__65.txt";
    // file = "CS170_largetestdata__7.txt";
    // file = "CS170_small_special_testdata__99.txt";

    //Insert intro here 
    cout << "Welcome to Alfredo Gonzalez's Feature Selection Algorithm." << endl;

    bool is_open = 0;
    while (!is_open) {
        cout << "Type in the name of the file to test: ";
        //cin >> file; 
        //file = "CS170_small_special_testdata__99.txt";
        //file = "CS170_SMALLtestdata__1.txt";

        //file = "CS170_SMALLtestdata__65.txt";        //My test files
        file = "CS170_largetestdata__7.txt";
        cout << endl;
        myFile.open(file);
        if (myFile.fail()) {
            cout << "Please enter a valid file name" << endl;
        }
        else { is_open = 1;}
        //cout << is_open << endl;
    }


    cout << "Type the number of the algorithm you want to run." << endl;
    cout << "   1.) Forward Selection" << endl;
    cout << "   2.) Backward Selection" << endl;
    while (algorithm_Choice != 1 && algorithm_Choice != 2) { 
        cin >> algorithm_Choice;    //Used later in the program 
        if (algorithm_Choice != 1 && algorithm_Choice != 2) {
            cout << "Please pick a valid choice." << endl;
        }
    }


    //Converts file into a 2Darray 
    vector<vector<double>> Data( rows, vector<double> (cols, 0)); 
    
    //fstream myFile; 
    //myFile.open(file);

    //Method for getting rows + cols of a text file 
    string line, item; 
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
        //Clears the fstream + restarts it to the beginning
        //From here: https://stackoverflow.com/questions/7681555/resetting-the-end-of-file-state-of-a-ifstream-object-in-c
        myFile.clear();
        myFile.seekg(0, ios::beg);    
        //Make a 2D array from the string stream
        //Adapted here: https://stackoverflow.com/questions/36708370/reading-from-txt-file-into-two-dimensional-array-in-c
        //Reads from the file + places data into an array


        //n rows, m columns 
        Data.resize(rows, vector<double>(cols));
        for(int i = 0; i < rows; i++)
            for(int j = 0; j < cols; j++)
                myFile >> Data[i][j];


        myFile.close();
    }

    
    cout << "This dataset has " << cols - 1 << " features (not including the class attribute), with " << rows << " instances" << endl;
    
    //TESTING
    chrono::time_point<chrono::system_clock> start, end; 
    start = chrono::system_clock::now();
    feature_search(Data);
    end = chrono::system_clock::now();     

    chrono::duration<double> elapsed_seconds = end - start;    
    cout << "Elapsed time of algorithm is: " << elapsed_seconds.count() << " s" << endl; //FOR TESTING
   
    return 0;
}