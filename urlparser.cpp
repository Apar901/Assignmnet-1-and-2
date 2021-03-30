/*This program asks the user to enter a URL and it parses the URL
into specific parts. Then, it check each part to see if it is valid.
If it is valid the program prints out the parts of the URL, else it
print out the errors in the parts.
*/
#include <iostream>
#include <cstring>
#include <string>
#include <bits/stdc++.h>

using namespace std;

//method parses the protocol from the URL
bool getProtocol(char input[], int &index, string &protocol)
{
    //gets protocol from the users URL
    for(; input[index] != ':'; index++)
    {
        protocol += input[index];
    }

    //checks to see if protocol is valid
    if(protocol == "http" || protocol == "https" || protocol == "ftp" || protocol == "fttps")
    {
        return true;
    }

    return false;
}

//method parses the domain
bool getDomain(char input[], int &index, string &domain, string &z)
{
    //skips the "://" part of the URL
    index += 3;

    //gets domain
    for(; input[index] != ':'; index++)
    {
        domain += input[index];
    }

    vector<string> v;
    stringstream ss(domain);

    //get rid of the period to check the form
    while(ss.good())
    {
        string substr;
        getline(ss, substr, '.');
        v.push_back(substr);
    }
    z += v[2];

    //checks if part z is valid
    if(z == "com" || z == "edu" || z == "net" || z == "biz" || z == "gov")
    {
        return true;
    }

    return false;
}

//method parser the port number
bool getPort(char input[], int &index, string &port)
{
    index += 1;

    //gets the port
    for(; input[index] != '/'; index++)
    {
        port += input[index];
    }

    stringstream degree(port);

    //converts the string into int
    int newPort = 0;
    degree >> newPort;

    //checks the port is in the valid range
    if(newPort >= 1 && newPort <= 65535)
    {
        return true;
    }

    return false;
}

//method parses the file path
bool getPath(char input[], int &index, string &path)
{
    //gets the path
    for(; input[index] != '?'; index++)
    {
        path += input[index];
    }

    vector<string> v;
    stringstream ss(path);

    //parses the path to the end
    while(ss.good())
    {
        string substr;
        getline(ss, substr, '.');
        v.push_back(substr);
    }

    //checks if the end is valid
    if(v[1] == "html" || v[1] == "htm")
    {
        return true;
    }

    return false;
}

//method parses the parameters
void getParameters(char input[], int & index, string &parameters, int urlSize)
{
    index += 1;

    //gets the parameters
    while(index < urlSize)
    {
        parameters += input[index];
        index++;
    }
}

int main()
{
    string url;
    string protocol, domain,
    port, path, parameters, z;
    int index = 0;

    //asks the user to enter URL
    cout << "Enter the URL: ";
    cin >> url;

    char url_array[url.length()];

    //converts the string to char array
    for(int i = 0; i < sizeof(url_array); i++)
    {
        url_array[i] = url[i];
    }

    int urlSize = sizeof(url_array);

    bool checkProtocol = getProtocol(url_array, index, protocol);
    bool checkDomain = getDomain(url_array, index, domain, z);
    bool checkPort = getPort(url_array, index, port);
    bool checkPath = getPath(url_array, index, path);

    //print the URL parts if all part are valid otherwise print the errors
    if(checkProtocol == true && checkDomain == true
       && checkPort == true && checkPath == true)
    {
        cout << setw(12) << left << "Protocal: " << protocol << endl;
        cout << setw(12) << left << "Domain: " << domain << endl;
        cout << setw(12) << left << "Port: " << port << endl;
        cout << setw(12) << left << "File Path: " << path << endl;
        getParameters(url_array, index, parameters, urlSize);
        cout << "Parameters: " << parameters << endl;
    }
    else
    {
        cout << "Invalid URL with following erroneous components:" << endl;

        if(checkProtocol == false)
        {
            cout << setw(12) << left << "Protocol: " << protocol << " is not a valid components" << endl;
        }
        if(checkDomain == false)
        {
            cout << setw(12) << left << "Domain: " << z << " is a invalid domain name." << endl;
        }
        if(checkPort == false)
        {
            cout << setw(12) << left << "Port: " << "port number must be between 1 and 65535";
        }
    }

    return 0;
}
