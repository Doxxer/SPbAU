#include "lexer.hpp"
#include <iostream>
#include <string>
#include <fstream>

Lexer::Lexer(std::string const &sourceFileName) : state_(true)
{
    std::ifstream inputFile_(sourceFileName, std::ifstream::in);
    std::string line;

    for (int lineNumber = 1; !inputFile_.eof(); ++lineNumber) {
        std::getline(inputFile_, line);

        if (line.length() > 0 && !processLine(line, lineNumber)) {
            break;
        }
    }
    position_ = content_.begin();
    inputFile_.close();
}

bool Lexer::processLine(std::string &str, int lineNumber)
{
    std::cout << ">>> parsing line number " << lineNumber << ": " << str << std::endl;

    for (std::string::iterator it = str.begin(); it != str.end(); ++it) {
        Token currentToken(Token::tt_unknown, "", lineNumber);

        switch (*it) {
            case ' ':
                continue;
            case ':':
                currentToken.type = Token::tt_colon;
                content_.push_back(currentToken);
                break;
            case ',':
                currentToken.type = Token::tt_comma;
                content_.push_back(currentToken);
                break;
            case '+':
            case '-':
            case '*':
            case '/':
            case '=':
                currentToken.type = Token::tt_operation;
                currentToken.name = *it;
                content_.push_back(currentToken);
                break;
            case '(':
                currentToken.type = Token::tt_opening_bracket;
                content_.push_back(currentToken);
                break;
            case ')':
                currentToken.type = Token::tt_closing_bracket;
                content_.push_back(currentToken);
                break;
            case '#':
                return true;
        }

        if (isalpha(*it)) {
            std::string identifier;

            while (it != str.end()) {
                identifier += *it;
                if ((it + 1) == str.end() ||
                    !(isalpha(*(it + 1)) || isdigit(*(it + 1)) || *(it + 1) == '_')) {
                    break;
                }
                ++it;
            }

            if (identifier == "def")
                currentToken.type = Token::tt_def;
            else if (identifier == "end")
                currentToken.type = Token::tt_end;
            else if (identifier == "while")
                currentToken.type = Token::tt_while;
            else if (identifier == "if")
                currentToken.type = Token::tt_if;
            else if (identifier == "return")
                currentToken.type = Token::tt_return;
            else if (identifier == "print")
                currentToken.type = Token::tt_print;
            else if (identifier == "read")
                currentToken.type = Token::tt_read;
            else {
                currentToken.type = Token::tt_identifier;
                currentToken.name = identifier;
            }

            content_.push_back(currentToken);
            continue;
        }

        if (isdigit(*it)) {
            std::string number;
            while (it != str.end()) {
                number += *it;
                if ((it + 1) == str.end() || !isdigit(*(it + 1))) {
                    break;
                }
                ++it;
            }
            currentToken.type = Token::tt_number;
            currentToken.name = number;
            content_.push_back(currentToken);
            continue;
        }

        if (currentToken.type == Token::tt_unknown) {
            std::cerr << "Lexer error: unknown symbol <" << *it << "> at line " << lineNumber
                      << std::endl;
            return state_ = false;
        }
    }
    return true;
}
