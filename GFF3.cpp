#include "gff_entry.hpp"

using namespace std;
// This program reads a GFF3 file, parses all values and objects for each line and outputs queried seq_id in given range from start to end.
int main(int argc, const char* argv[])
{
    // Initializing variables
    vector<GFFEntry> data;
    string seqid = argv[2], a;
    int start = stoi(argv[3]);
    int end = stoi(argv[4]);
    // only when given right input, processes input file
    if (argc == 5)
    {
        ifstream infile;
        infile.open(argv[1]);
        // Error check
        if (!infile  || seqid.empty() || (start == 0 && end == 0))
        {
            std::cerr << "cannot open input file: " << argv[1] << std::endl;
            return 1;
        }
    } else
        {
        std::cerr << "\nusage: " << argv[0] << "  <input_file> <seq_id> <start> <stop>\n"
                  << std::endl;
        return 1;
    }
    data = readGFF(argv[1]);
    // Processes the output of readGFF and couts respectively.
    writeGFF(data, cout, seqid, start, end);

    return 0;
}
