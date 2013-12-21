#include <iostream>
#include <string>

#include "lexer.hpp"
#include "parser.hpp"
#include "evaluator.hpp"
#include "errors.hpp"

using std::cout;
using std::cerr;
using std::endl;

int main(int argc, const char *argv[])
{
    if (argc < 2) {
        cout << "Usage: " << argv[0] << " <source filename>" << endl;
        return 1;
    }

    try
    {
        Parser parser(argv[1]);
        Program program = parser.parse();

        Evaluator evaluator(program);
        evaluator.eval();
    }
    catch (LexerError const &e)
    {
        cerr << "Lexer error at line #" << e.line() << ": " << e.what() << endl;
        return 1;
    }
    catch (ParserError const &e)
    {
        cerr << "Syntax error at line #" << e.line() << ": " << e.what() << endl;
        return 1;
    }
    catch (RuntimeError const &e)
    {
        cerr << "Runtime error at line #" << e.line() << ": " << e.what() << endl;
        return 1;
    }

    return 0;
}
