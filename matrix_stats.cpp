#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <cstdlib>
#include <sstream>

using namespace std;
// Finds minimum element in given vector
double Minimum(vector<double>& v){
    return *min_element(v.begin(), v.end()); // <algorithm>
}

// Finds maximum element in given vector
double Maximum(vector<double>& v) {
    return *max_element(v.begin(), v.end()); // <algorithm>
}

// Finds mean of elements in vector
double Mean(vector<double>& v) {
    return accumulate( v.begin(), v.end(), 0.0)/v.size(); // <numeric>
}

// Find the median, required to find quartiles
double Median(vector<double>& v){
    sort(v.begin(), v.end()); // Step 1 to finding median <algorithm>
    if (v.size() % 2 == 0) { // if even number of elements
        return (v[(v.size() - 1) / 2] + v[v.size() / 2]) / 2.0;
    }

    return v[v.size() / 2]; // if odd number of elements
}

// Finds the third quartile
double ThirdQuartile(vector<double>& v) {
    sort(v.begin(), v.end());
    vector<double> left;
    vector<double> right;

    if (v.size() % 2 == 0){
        left.assign(v.begin(), v.begin() + v.size() / 2);
        right.assign(v.begin() + v.size() / 2, v.end());
    }else {
        left.assign(v.begin(), v.begin() + (v.size() - 1) / 2);
        right.assign(v.begin() + (v.size() + 1) / 2, v.end());
    }

    return Median(right);
}

// Prints nth smallest
void Smallest(vector<double>& v, int n){
    sort(v.begin(), v.end());
    if(n > v.size()){
        cout<< "In";
    }else{
        cout << v[static_cast<unsigned int>(n - 1)];
    }
}

// Prints mth largest
void Largest(vector<double>& v, int m){
    sort(v.begin(), v.end(), greater<double>());
    if(m > v.size()){
        cout << "Im";
    }else{
        cout << v[static_cast<unsigned int>(m - 1)];
    }
}



int main(int argc, char* argv[]) {
    int n = atoi(argv[1]); // nth number
    int m = atoi(argv[2]); // mth number
    vector<vector<double>> input_data;
    string input;

    // get square matrix
    while(getline(cin, input)){
        istringstream iss(input);
        vector<double> v;
        double x;
        while (iss >> x){
            v.push_back(x);
        }
        input_data.push_back(v);
    }
    unsigned int rows = input_data.size();

    // Get transpose of matrix, so rows become columns and vice versa.
    vector<vector<double> > input_data_t(rows, vector<double>(rows));
    for (unsigned int i = 0; i < rows; ++i){
        for (unsigned int j = 0; j < rows; ++j)
            input_data_t[j][i] = input_data[i][j];                                                                                          // Transpose makes rows to columns so, yeah why not!
    }
    // Get diagonal
    vector<double> diagonal;
    for (unsigned int i = 0; i < rows; ++i){
        for (unsigned int j = 0; j < rows; ++j)
            if (i == j)
                diagonal.push_back(input_data[i][j]);                                                                            // Stores diagonals
    }
    // Get Upper diagonal
    vector<double> upper_triangle;
    for (unsigned int i = 0; i < rows; ++i){
        for (unsigned int j = 0; j < rows; ++j)
            if (i < j)
                upper_triangle.push_back(input_data[i][j]);                                                                       // lower traingle is where i (row index) is higher than j (column index)
    }
    //Print results
    for(auto e:input_data){
        cout << Minimum(e) << " " << Maximum(e) << " " << Mean(e) << " " << ThirdQuartile(e) << " " ; Smallest(e, n); cout << " ";Largest(e, m);cout << endl;

    }
    for(auto e:input_data_t){
        cout << Minimum(e) << " " << Maximum(e) << " " << Mean(e) << " " << ThirdQuartile(e) << " " ; Smallest(e, n); cout << " ";Largest(e, m);cout << endl;

    }
    cout << Minimum(diagonal) << " " << Maximum(diagonal) << " " << Mean(diagonal) << " " << ThirdQuartile(diagonal) << " " ; Smallest(diagonal, n); cout << " ";Largest(diagonal, m);cout << endl;
    cout << Minimum(upper_triangle) << " " << Maximum(upper_triangle) << " " << Mean(upper_triangle) << " " << ThirdQuartile(upper_triangle) << " " ; Smallest(upper_triangle, n); cout << " ";Largest(upper_triangle, m);cout << endl;


    return 0;
}
