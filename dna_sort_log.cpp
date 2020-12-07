#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Constant values of each nucleotide
const double A = 135;
const double G = 151;
const double C = 111;
const double T = 126;
const double Backbone = 180;

// Datatype for DNA sequences
struct DNA{
    double mass;
    string seq;
};

// Compute molar mass of a string (sequence)
double MolarMass(const string& s){
    double sum1, sum2 = 0;
    sum1 = Backbone*s.length();
    for(char i : s) {
        switch (i) {
            case 'A': sum2 += A; break;
            case 'G': sum2 += G; break;
            case 'C': sum2 += C; break;
            case 'T': sum2 += T; break;
            default: cout <<"Default! Returning -1" << endl; break;
        }
    }
    return (sum1+sum2);
}

// Fill a vector<DNA> type from input strings
void FillData(const vector<string>& input_data, vector<DNA>& data_){
    for(auto & i : input_data){
        DNA unit;
        unit.seq = i;
        unit.mass = MolarMass(i);
        data_.push_back(unit);
    }
}

// Sort by molar mass
bool CompareMass(const DNA &x, const DNA &y)
{
    return x.mass < y.mass;
}

// sort lexicographically

bool CompareLex(const DNA &x, const DNA &y){
    return x.seq < y.seq;
}

int main(int argc, char* argv[]) {
    vector<string> args;
    vector<string> input_data;
    vector<DNA> data_;
    vector<string> final_data;

    // Get all argument fragments
    for(int i=1;i<argc;i++){
        args.emplace_back(argv[i]);
    }

    // Get input sequences
    string l;
    while(!cin.eof()){
        getline(cin, l);
        input_data.push_back(l);
    }

    input_data.pop_back();
    // Find fragment in input data
    FillData(input_data, data_);
    // Sort by Lexicography
    sort(data_.begin(), data_.end(), CompareLex);
    // Sort by molar mass
    sort(data_.begin(), data_.end(), CompareMass);

    for(auto & i : data_){
        string point = i.seq;
        final_data.push_back(point);
    }

    // Find arguments (Binary Search)
    for(const string& arg:args){
        int count = 0;
        if(binary_search(final_data.begin(), final_data.end(), arg)){
            ptrdiff_t pos = distance(final_data.begin(), find(final_data.begin(), final_data.end(), arg));
            cout << pos + 1 << endl;
            count++;
        }
        if(count == 0) {
            cout << "not found" << endl;
        }
    }
    return 0;
}