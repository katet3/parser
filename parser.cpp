#include <iostream>
#include "syntax_analyzer.h"

using std::cout;
using std::cin;
using std::endl;

int main()
{
    cout << "Hello pidr!\n";
    std::string in_file = "PATH_TO_FILE";
    std::string result_file = "PATH_OUT_FILE";
    
    SyntaxAnalyzer niga = SyntaxAnalyzer(in_file, result_file);
    cout << niga << endl;
}
