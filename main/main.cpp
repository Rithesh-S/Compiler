#include<iostream>
#include<stdexcept>
#include<string>
#include<fstream>
#include<sstream>
using namespace std;

void run(const string& source) {
    cout<<source<<endl;
}

void fetchFile(const string& path) {
    //stores as ifstream object
    ifstream file(path);

    if(!file) {
        throw runtime_error("Couldn't open the file " + path);
    }
    //reading the file buffer
    stringstream buffer;
    buffer << file.rdbuf();
    string source = buffer.str();

    run(source);
}

// argc contains the number of argument passed
// argv contains the location of the exe file in index 0 and rest of the argument passed
int main(int argc,char* argv[]) {
    try {
        if(argc == 1) {
            cout<<"Please specify the file!"<<endl;
            return 64;                                  //exit code is 64, which means "command line usage error."
        } else if(argc > 2) {
            cout<<"Only single file is accepted!"<<endl;
            return 64;                                  //exit code is 64, which means "command line usage error."
        } else {
            fetchFile(argv[1]);
        }
    } catch(const exception &e) {
        cerr<<"Error: "<<e.what()<<endl;
        return 70;                                      //exit code is 70, which means "internal software error." This is a good general-purpose "something bad happened" error.
    }
    return 0;
}