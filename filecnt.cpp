/*This program take the path and prints out the files, directories,
* and the bytes of all the files of the given directory.
* adding more comments for the assignment
*/
#include <iostream>
#include <dirent.h>
#include <cstring>
#include <sys/stat.h>

using namespace std;

int dirCount, fileCount;
unsigned long long fileSize;

string checkPathString(string strPath)
{
    if(strPath[strPath.length() - 1] == '/')
    {
        strPath = strPath.substr(0, strPath.length() - 1);
    }
    return strPath;
}

//goes through all the files and subdirectories in the directory
void listdir(string initStrPath)
{
    struct dirent *dir;
    struct stat st;
    DIR *dp = opendir(initStrPath.c_str());
    if(dp)
    {
        while((dir=readdir(dp)) != NULL)
        {
            string strPath = "";
            if(strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0) continue;
            if(dir->d_type == DT_DIR)
            {
                initStrPath = checkPathString(initStrPath);
                strPath = initStrPath + "/" + dir->d_name;
                listdir(strPath);
                dirCount++;     //count the subdirectories in the directory
            }
            else{
                initStrPath = checkPathString(initStrPath);
                strPath = initStrPath + "/" + dir->d_name;
                cout << strPath << endl;
            }
            //get the size of the files
            stat(dir->d_name, &st);
            fileSize += st.st_size;
            //count the files in the directory
            fileCount++;
        }
        closedir(dp);
    }
}

//prints the output
int main(int argc, char *argv[])
{
    if(argc <= 1)
    {
        cout << argv[0] << " <dir>" << endl;
        exit(1);
    }
    listdir(argv[1]);
    cout << "The total number of directories in directory " << argv[1] << " is: " << dirCount << endl;
    cout << "The total number of files in directory " << argv[1] << " is: " << fileCount << endl;
    cout << "The total number of bytes occupied by all files in directory " << argv[1] << " is: " << fileSize << endl;
    return 0;
}
