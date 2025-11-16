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

string tokenTypeToString(TokenType type) {
    switch (type) {
        case TokenType::NUMBER:       return "NUMBER";
        case TokenType::MINUS:        return "MINUS";
        case TokenType::PLUS:         return "PLUS";
        case TokenType::SLASH:        return "SLASH";
        case TokenType::ASTERISK:     return "ASTERISK";
        case TokenType::LEFT_PAREN:   return "LEFT_PAREN";
        case TokenType::RIGHT_PAREN:  return "RIGHT_PAREN";
        case TokenType::END_OF_FILE:  return "END_OF_FILE";
        case TokenType::GREATER_THAN: return "GREATER_THAN";
        case TokenType::LESSER_THAN:  return "LESSER_THAN";
        case TokenType::IDENTIFIER:   return "IDENTIFIER";
        case TokenType::EQUAL:        return "EQUAL";
        case TokenType::SEMICOLON:    return "SEMICOLON";
        case TokenType::V_:           return "V_";
        default:                      return "UNKNOWN";
    }
}

void run(const string& source) {
    try {
        Lexer lexer(source);
        vector<Token> tokens = lexer.scanTokens();

        cout<<"--- Scanned Tokens ---"<<endl;
        for(const Token& token : tokens) {
            cout<<"Type: "<<tokenTypeToString(token.type)
                    <<" \t Lexeme: '"<<token.lex<<"'"<<endl;
        }
    
        Parser parser(tokens);
        vector<unique_ptr<Stmt>> program = parser.parse();

        if (!program.empty()) {
            std::cout << "--- Parser Success ---" << std::endl;
            std::cout << "Parsed " << program.size() << " statements." << std::endl;
        } else {
            std::cout << "--- Parser ---" << std::endl;
            std::cout << "Parsed 0 statements." << std::endl;
        }

        // if(ast) {
        //     AstPrinter astPrinter;
        //     cout<<"--- AST --- "<<endl;
        //     cout<<astPrinter.print(ast)<<endl;

        //     Interpreter interpreter;
        //     double ans = interpreter.interpret(ast);
        //     cout<<"--- Result --- "<<endl;
        //     cout<<ans<<endl;
        // } else {
        //     cout<<"--- AST(null) --- "<<endl;
        // }
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