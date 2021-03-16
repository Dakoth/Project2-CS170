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

using namespace std; 

int rows = 0;  //Counts the rows of the file
int cols = 0;  //counts the cols of the file

int algorithm_Choice = 0;

//fstreams can both read in and out data, unlike just ifstream and ofstreams 


//Takes in the fstream,                                          
//is feature to add just an int?               
//If I make a copy of Data, then I can freely edit it as I please,
    //But this could make things much more costly if I do that...   
    //got rid of &d, maybe this works?                                                      
double leave_one_out_cross_validation(vector<vector<double>> d, vector<double> &current_set, double feature_to_add) { //temporarily for testing 
    vector<double> tempSet = current_set;   //Temp set is the current set of features + the feature you're looking to add
    tempSet.push_back(feature_to_add);  
    
    
    double accuracy; 
    double nearest_neighbor_distance;
    double nearest_neighbor_location; 
    double nearest_neighbor_label; 
    double distance, sum;   //sum used for eucidean distance 

    double number_correctly_classified = 0;

    //initalize vector with cols - 1 with all 0 
    vector<double> object_to_classify(cols - 1, 0);
    double label_object_to_classify = 0;

    //cout << "object to classifiy is size: " << object_to_classify.size() << endl;
    //cin >> label_object_to_classify;            //TEST



    //Edit parts of the Data vector to IGNORE
   //cout << "Haven't edited data vector, tempSize is " << tempSet.size() << endl;
   //cout << tempSet.at(0) << endl;
   
   for (int i = 0; i < rows; i++) {
        for (int j = 1; j <= cols - 1; j++)  {   
            //Checks at each index if it's equal to the index of the temp set
            for (int x = 0; x < tempSet.size(); x++) {       //Goes thru the testSet 
                //Need to add + 1 to not accidently change the class label?
            
                
                //Forward ...
                if (find(tempSet.begin(), tempSet.end(), j) != tempSet.end()) {
                    //If the feature is in the tempSet, do nothing 
                }
                else { //else, sets the feature value to 0 
                    d[i][j] = 0;             //Sets the value of the i-th row, with added feature to be 0 // should it be +1?
                }
                //cout << "ay" << endl;
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
    */

    //Psuedocode part
    for (int i = 0; i < rows; i++) {

        //initalize object to classify 
        //might need to edit with this size
        //Needed to make sure it gets all the features
        for (int j = 1; j <= cols - 1; j++) { 
            object_to_classify[j - 1] = d[i][j];        //makes this the value from the data 
        }

        label_object_to_classify = d[i][0];
        //cout << "Label to classify is: " << label_object_to_classify << endl;


        //Test printing objecto to classify 
        /*
        for (int l = 0; l < object_to_classify.size(); l++) 
            cout << setprecision(9) << object_to_classify[l] << endl;

        int TEST;
        cin >> TEST;

        */
        setprecision(9);  //Don't know if this makes a difference

        //From here: https://en.cppreference.com/w/cpp/types/numeric_limits/infinity
        nearest_neighbor_distance = numeric_limits<double>::infinity();
        nearest_neighbor_location = numeric_limits<double>::infinity();

        for (int k = 0; k < rows; k++) {
            //cout << "Ask if " << i + 1 << " is nearest neighbor with " << k + 1 << endl;


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
        
        //cout << "Object " << i + 1 << " is class " << label_object_to_classify << endl;
        //cout << "Its nearest_neighbor is " << nearest_neighbor_location + 1 << " which is in class " << nearest_neighbor_label << endl;
                                                //IS THIS CORRECT??????

        //cout << "Looping over i, at the " << i + 1 << " location" << endl;
        //cout << "The " << i + 1 << "th object is in class: " << label_object_to_classify << endl;
    }
    accuracy = number_correctly_classified / (rows);    //number of rows is the size of the data

    cout << "accuracy is " << accuracy << endl;

    //int TESTTT;
    //cin >> TESTTT;

    return accuracy; 
} 


//////////////////////////////////////////////////////////////////////////////////////////////////////
void feature_search(vector<vector<double>> &Data) { //string& file) {//, string& file) {need to take in text file as input 
    //psuedo code part from slides
    vector<double> current_set_of_features; //(cols); //initalize an empty set the size of the features

    vector<double> best_set_of_features;    //Used to measure the best set of features, new addition
    double accuracy = 0; 

    double best_so_far_accuracy = 0; 
    double feature_to_add_at_this_level; 

    double BEST_accuracy = best_so_far_accuracy; 

    //double all_features_accuracy =leave_one_out_cross_validation(Data, current_set_of_features, 0);
    
    for (int i = 1; i <= cols - 1; i++) {
        //vector<double> feature_to_add_at_this_level; 
        best_so_far_accuracy = 0; 
        feature_to_add_at_this_level = 0; //Make this always 0 just in case? 
        
        

        cout << "On the " << i << "th level of the search tree" << endl;      //COMMENTED OUT FOR TESTING

        for (int k = 1; k <= cols - 1; k++) {
            
            //If the k-th feature hasn't been added yet 
            //only consider adding
            //below if statement is from: https://stackoverflow.com/questions/3450860/check-if-a-stdvector-contains-a-certain-object
            if (find(current_set_of_features.begin(), current_set_of_features.end(), k) != current_set_of_features.end()) {
                //k feature has been added to the set 
            }
            else {  //the k feature hasn't been added yet
                cout << "--Consider adding the " << k << " feature" << endl;      //COMMENTED OUT FOR TESTING

                //cout << "in the loop test" << endl;

                //LOOK AT THIS LATER
                //*******************************
                accuracy = leave_one_out_cross_validation(Data, current_set_of_features, k);    //SHOULD THIS BE k instead of k + 1????
                //*******************************


                if (accuracy > best_so_far_accuracy) {
                    best_so_far_accuracy = accuracy;
                    feature_to_add_at_this_level = k;

                    
                    //feature_to_add_at_this_level.push_back(k);  //puts this feature in the array.    
                }
            }
        }

        //Only add to the best accuracy set if the GLOBAL MAX accuracy is best than local max
        if (best_so_far_accuracy > BEST_accuracy) {
            cout << "new global max found" << endl;
            BEST_accuracy = best_so_far_accuracy;
            best_set_of_features.push_back(feature_to_add_at_this_level);
        }

        //current_set_of_features.at(i) = feature_to_add_at_this_level;   //might need to edit this 
        current_set_of_features.push_back(feature_to_add_at_this_level);

        cout << "On level " << i << " I added feature " << feature_to_add_at_this_level << " to current set" << endl;
        ////COMMENTED OUT FOR TESTING ^^^
    }


    double all_features_accuracy = leave_one_out_cross_validation(Data, current_set_of_features, 0);

    //TESTING STUFF     
    //testing size of the current set of features 
    //for (int j = 0; j < current_set_of_features.size(); j++) { cout << current_set_of_features.at(j) << endl; }

    cout << rows << endl;
    cout << cols << endl;
    //cout << "Best Accuracy is: " << best_so_far_accuracy << endl;
    
    cout << "Best Accuracy was " << BEST_accuracy << endl;

    cout << "The set of best features is: ";
    for (int i = 0; i < best_set_of_features.size(); i++) {
        cout << best_set_of_features[i] << " ";
    }
    cout << endl;
    cout << " accuracy with all features is: " << all_features_accuracy << endl;
        
//    myFile.close();
    //}

    return; 
}

int main() {
    //ifstream myFile; 
    //srand(time(0)); //Just for stub 



    string file = "";
    //string file = "testFile.txt";
    //string file = "CS170_SMALLtestdata__1.txt";  //Set up like the example in the slides 
    //string file = "CS170_SMALLtestdata__65.txt";
    //string file = "CS170_largetestdata__7.txt";
    //string file = "CS170_small_special_testdata__99.txt";

    //Insert intro here 
    cout << "Welcome to Alfredo Gonzalez's Feature Selection Algorithm." << endl;
    cout << "Type in the name of the file to test: ";
    //cin >> file; 
    file = "CS170_small_special_testdata__99.txt";
    cout << endl;

    cout << "Type the number of the algorithm you want to run." << endl;


    //Converts file into a 2Darray 
    vector<vector<double>> Data( rows, vector<double> (cols, 0)); 
    fstream myFile; 
    myFile.open(file);

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
        //initalize an n x m vector with 0s 
        //vector<vector<double>> Data( rows, vector<double> (cols, 0)); 
        //int m = number of rows, n = number of columns;
        Data.resize(rows, vector<double>(cols));
        for(int i = 0; i < rows; i++)
            for(int j = 0; j < cols; j++)
                myFile >> Data[i][j];


        //test print of the array 
        /*
        for(int i = 0; i < rows; i++) { 
            //cout << endl;
            for(int j = 1; j <= cols - 1; j++) {
                cout << Data[i][j] << " "; 
                //if (j = rows - 1) { cout << endl;}
            }   
            cout << endl;
        }
        */
        //int TEST;
        //cin >> TEST;

        myFile.close();
    }

    //feature_search(file);

    //TESTING
    feature_search(Data);


    //vector<double> testV;
    //int t;
    //double test = leave_one_out_cross_validation(Data, testV, t);
    return 0;
}