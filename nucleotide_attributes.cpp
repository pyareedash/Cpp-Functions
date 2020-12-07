#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>

using namespace std;

struct Complementer{
    string loop;
    bool val{};
};
// Count Residues (A, G, C, U content)
vector<double> NucleotideRatio(const vector<string>& seq){

    vector<double> percentages;
    string seq_total;

    for(const auto& s : seq){
        seq_total += s;
    }

    double a = count(seq_total.begin(), seq_total.end(), 'A');
    double c = count(seq_total.begin(), seq_total.end(), 'C');
    double g = count(seq_total.begin(), seq_total.end(), 'G');
    double u = count(seq_total.begin(), seq_total.end(), 'U');
    double gc = g + c;

    double seq_all = seq_total.size() * 1.0;

    percentages.push_back(gc/seq_all);
    percentages.push_back(a/seq_all);
    percentages.push_back(c/seq_all);
    percentages.push_back(g/seq_all);
    percentages.push_back(u/seq_all);

    return percentages;
}

// Check for DNA sequences to convert them to RNA or report ID if any other sequence found.
void NucleotideConverter(vector<string>& id, vector<string>& seq){
    for(auto & i : seq){
        // Convert DNA to RNA
        replace(i.begin(), i.end(), 'T', 'U');
        // Capitalize already
        transform(i.begin(), i.end(),i.begin(), ::toupper);
    }
    // Check if non-nucleotide sequence found, exclude them
    for(unsigned int i=0; i < seq.size();i++) {
        if(seq[i].find_first_not_of("AUGC") != string::npos){
            cerr << id[i] << endl;
            id.erase(id.begin() + static_cast<int>(i));
            seq.erase(seq.begin() + static_cast<int>(i));
        }
        }
}

// Check complementary sequence
void CheckComplement(Complementer a){
    string first, last;

    if(a.loop.size() % 2 ==0 ){
        first = {a.loop.begin(), a.loop.end() - a.loop.size()/2};
        last = {a.loop.begin() + a.loop.size()/2, a.loop.end()};
    }
    else{
        first = {a.loop.begin(), a.loop.end() - (a.loop.size()/2 + 1)};
        last = {a.loop.begin() + (a.loop.size()/2 + 1), a.loop.end()};
    }

    reverse(first.begin(), first.end());
    for (auto e:first){
        switch (e){
            case 'A':
                e = 'T';
                break;
            case 'C':
                e = 'G';
                break;
            case 'G':
                e = 'C';
                break;
            case 'T':
                e = 'A';
                break;
            default: cerr << "oops" << endl;
        }
    }
    a.loop = first;
    if (first==last)
        a.val = true;
    else
        a.val = false;
}

// Find hairpin loops
    vector<string> HairpinChecker(const vector<string>& seq){
        vector<string> hairpins;

        for(const string& s : seq){
            Complementer sc;
            sc.loop = s;
            CheckComplement(sc);
            if (sc.val){
                hairpins.push_back(s);
            }
        }
        return hairpins;
    }

    int main(int argc, char** argv){

    ifstream file(argv[1]);
    ofstream output_file(argv[2]);
    // Input preprocessing
    string line;
    vector<string> lines;
    while(getline(file, line)){
        lines.push_back(line);
    }
    int numberLines = static_cast<int>(lines.size());

    vector<string> id;
    vector<string> sequence;

    string temp = "";

    int count = 0;
   for(auto & s : lines){
        if(s[0] == '>'){
            id.push_back(s);
            count++;
        }
        else{
            sequence.push_back(s);
        }
    }

    NucleotideConverter(id, sequence);


    vector<double> ratios = NucleotideRatio(sequence);
    // Output data
    cout << "Lines: " << numberLines << endl;
    cout << "Sequences: " << count << endl;
    cout << "GC content: " << ratios[0] << endl;
    cout << "A: " << ratios[1] << endl;
    cout << "C: " << ratios[2] << endl;
    cout << "G: " << ratios[3] << endl;
    cout << "U: " << ratios[4] << endl;


    vector<string> harp = HairpinChecker(sequence);
    // Print hairpins in output fasta file
    for(const string& s : harp){
        output_file << s << endl;
    }

    file.close();
    output_file.close();

    return 0;

}
