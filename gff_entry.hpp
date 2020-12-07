#ifndef GFF_ENTRY_HPP
#define GFF_ENTRY_HPP

#include <cstdint>
#include <string>
#include <map>
#include<iostream>
#include<vector>
#include<string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstdint>

using namespace std;
// GFFEntry structure
struct GFFEntry {
	std::string seqid;
	std::string source;
	std::string type;
	uint64_t start;
	uint64_t end;
	float score;
	char strand;
	uint8_t phase;
	std::map<std::string, std::string> tags;
};

// Checks for empty '.' and replaces with ""
void checkDelim(string d)
{
    if(d ==".")
    {
        d = "";
    }
}

// Checks for empty '.' and replaces with float value 0.0
float checkDelimf(string d)
{
    if(d == ".")
    {
        return 0.0;
    }
}

// Checks for empty '.' and replaces with uint64_t value 0
uint64_t checkDelim64(string d)
{
    if(d == ".")
    {
        return 0;
    }
    else
    {
        return strtoull(d.c_str(), nullptr, 0);
    }
}

// Checks for empty '.' and replaces with uint8_t value 0
uint8_t checkDelim8(string d)
{
    if(d == ".")
    {
        return 0;
    }
    else
    {
        return static_cast<uint8_t>(stoi(d));
    }
}

// Reverse checks checkDelim()
void rcheckDelim(string d)
{
    if(d.empty())
    {
        d = ".";
    }
}

// Reverse checks checkDelim64()
string writeCheck64(uint64_t d)
{
    if(d == 0)
    {
        return ".";
    }
    else
    {
        return to_string(d);
    }
}

// Reverse checks checkDelimf()
string writeCheckf(float d)
{
    if(d == 0)
    {
        return ".";
    }
    else
    {
        return to_string(d);
    }
}

// Reverse checks checkDelim8()
string writeCheck8(uint8_t d)
{
    if(d == 0)
    {
        return ".";
    }
    else
    {
        return to_string(d);
    }
}

// Reads GFF3 file from given input file.
vector<GFFEntry> readGFF(const string& filename)
{
    vector<GFFEntry> data;
    ifstream infile(filename);
    string line;

    while(getline(infile, line))
    {
        // To Skip # lines
        if (line.find("#") == 0)
        {
            continue;
        }
        // Basic Parsing: Takes the line as a string, splits that string with a delimiter to make new string.
        GFFEntry each;
        string d;
        istringstream row(line);
        getline(row, d, '\t');
        checkDelim(d);
        each.seqid = d;

        getline(row, d, '\t');
        checkDelim(d);
        each.source = d;

        getline(row, d, '\t');
        checkDelim(d);
        each.type = d;

        getline(row, d, '\t');
        uint64_t sta = checkDelim64(d);
        each.start = sta;

        getline(row, d, '\t');
        sta = checkDelim64(d);
        each.end = sta;

        getline(row, d, '\t');
        float v = checkDelimf(d);
        each.score = v;

        getline(row, d, '\t');
        each.strand = d[0];

        getline(row, d, '\t');
        uint8_t p = checkDelim8(d);
        each.phase = p;

        // Basic Parsing: Takes the line as a string, splits that string with a delimiter to make new string and then again the same.
        getline(row, d);
        istringstream da(d);
        while(getline(da, d, ';'))
        {
            string val;
            istringstream is(d);
            while((getline(is, d, '=') && getline(is,val)))
            {
                each.tags[d] = val;
            }
        }
        data.push_back(each);
    }
    return data;
}

// Takes the data from readGFF and couts query seq_id data-points in closed interval of start and end.
// Every attribute of GFF3 is printed after it's checked for empty values.
void writeGFF(const vector<GFFEntry>& entries, ostream& out_stream, string seqid, int start, int end)
{
    string a;
    for(const auto& i : entries)
    {
        if(i.seqid == seqid && i.start >= start && i.end <= end)
        {
            GFFEntry each = i;
            rcheckDelim(each.source);
            out_stream << each.seqid << '\t' << each.source <<'\t';
            rcheckDelim(each.type);
            out_stream << each.type <<'\t';
            a = writeCheck64(each.start);
            out_stream << a <<'\t';
            a = writeCheck64(each.end);
            out_stream << a <<'\t';
            a = writeCheckf(each.score);
            out_stream << a <<'\t' << each.strand <<'\t';
            a = writeCheck8(each.phase);
            out_stream << a <<'\t';
            a = "";
            auto stop = true;
            // prints attributes with ';'
            for(const auto& j : each.tags)
            {
                if(stop) stop = false; else out_stream << ';';
                out_stream << j.first << '=' << j.second;
            }
            out_stream << '\n';
        }

    }
}

#endif // GFF_ENTRY_HPP
