#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

//for string delimiter
vector<string> split(string s, string delimiter)
{
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;

    while((pos_end = s.find(delimiter, pos_start)) != string::npos)
    {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }

    res.push_back(s.substr(pos_start));
    return res;
}

//prints the output depending on the option chosen
void main1(int argc, char **argv){
    string lineInput;
    string delimiter = " ";
    string option = argv[1];

    //prints the directories
    if(option == "-d"){
        while(getline(cin, lineInput)){
            vector<string> v = split(lineInput, delimiter);
            for(auto i : v){
                if(i == "directories"){
                    cout << lineInput << endl;
                }
            }
        }
    }
    //prints the files
    else if(option == "-f"){
        while(getline(cin, lineInput)){
            vector<string> v = split(lineInput, delimiter);
            for(auto i : v){
                if(i == "files"){
                    cout << lineInput << endl;
                }
            }
        }
    }
    //prints the bytes
    else if(option == "-b"){
        while(getline(cin, lineInput)){
            vector<string> v = split(lineInput, delimiter);
            for(auto i : v){
                if(i == "bytes"){
                    cout << lineInput << endl;
                }
            }
        }
    }
    //prints the error for wrong option
    else{
        cout << "Invalid option was selected." << endl;
    }
}
