#include <iostream>
#include <stdexcept>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include "token/Lexer.h"
#include "token/type/Token.h"
#include "parser/expr/Expr.h"
#include "parser/Parser.h"
#include "print/AstPrinter.h"
#include "interpreter/Interpreter.h"

using namespace std;

void run(const string& source) {
    try {
        Lexer lexer(source);
        vector<Token> tokens = lexer.scanTokens();
    
        Parser parser(tokens);
        unique_ptr<Expr> ast = parser.parse();

        if(ast) {
            AstPrinter astPrinter;
            cout<<" --- AST --- "<<endl;
            cout<<astPrinter.print(ast)<<endl;

            Interpreter interpreter;
            double ans = interpreter.interpret(ast);
            cout<<" --- Result --- "<<endl;
            cout<<ans<<endl;
        } else {
            cout<<" --- AST(null) --- "<<endl;
        }
    } catch(const exception& e) {
        cerr<<"Error: "<<e.what()<<endl;
    }
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