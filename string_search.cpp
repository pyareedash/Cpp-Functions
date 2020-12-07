// This task is about finding out the query words in given list of words and accurately output if the word is found somewhere in the list or not.
// In this program, basic for loops are used to perform the search in linear time.
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

vector<string> wordsFromLines()                                                                                         // Take input string and store in vector , words
{
    vector<string> lines;
    string input_line = " ";

    while(input_line != "")
    {
        getline(cin, input_line);
        lines.push_back(input_line);
    }
    lines.pop_back();
    return lines;
}

int main(int argc, char* argv[])
{
    vector<string> words = wordsFromLines();
    vector<string> arguments;
    string line = " ";

    sort(words.begin(), words.end(), greater<string>());                                                         // sort lexicographically
    words.erase(unique(words.begin(), words.end()), words.end());                                                       // remove duplicates

    if(line.empty())
        for (int i = 1; i <= argc; i++)
        {
            arguments.push_back(argv[i]);                                                                               // Store query words
        }

    for (int i = 0; i <= arguments.size(); i++)
    {
        int count = 0;
        for (int j = 0; j <= words.size(); j++)                                                                         // Linear time for looping, element by element search
        {
            if (arguments[i] == words[j])
                cout << j + 1;
            count++;
        }
        if (count == 0)
            cout << "not found";
    }

}


