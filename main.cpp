#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <cctype>

#include "ArrayStack.h"

using namespace std;

// Token

struct Token {
    string value;   // number, operator, or parenthesis
};

// Tokenizer

vector<Token> tokenize(const string& line) {
    vector<Token> tokens;

    for (int i = 0; i < line.length(); i++) {
        char c = line[i];

        if (isspace(c)) {
            continue;
        }
        if (isdigit(c)) {
            string num = "";

            while (i < line.length() && isdigit(line[i])) {
                num += line[i];
                i++;
            }
            i--;
            tokens.push_back(Token{num});
        }
        else {
            string other = "";
            other += c;
            tokens.push_back(Token{other});
        }
    }

    return tokens;
}

// Helpers

bool isOperator(const string& s) {
    return s == "+" || s == "-" || s == "*" || s == "/";
}

int precedence(const string& op) {
    if (op == "*" || op == "/") {
        return 2;
    }
    else if (op == "+" || op == "-") {
        return 1;
    }
    return 0;
}

// Detection

bool isValidPostfix(const vector<Token>& tokens) {
    int count = 0;

    for (int i = 0; i < tokens.size(); i++) {
        string s = tokens[i].value;

        if (isdigit(s[0])) {
            count += 1;
        }
        else if (isOperator(s)) {
            if (count < 2) {
                return false;
            }
            count--;
        }
        else {
            return false;
        }
    }
    if (count == 1) {
        return true;
    }
    else {
        return false;
    }

}

bool isValidInfix(const vector<Token>& tokens) {
    int numParentheses = 0;
    bool isNumNext = true;

    for (int i = 0; i < tokens.size(); i++) {
        string s = tokens[i].value;

        if (s == "(") {
            numParentheses += 1;
        }
        else if (s == ")") {
            numParentheses -= 1;
            if (numParentheses < 0) {
                return false;
            }
            else {
                isNumNext = false;
            }
        }
        else if (isdigit(s[0])) {
            if (!isNumNext) {
                return false;
            }
            else {
                isNumNext = false;
            }
        }
        else if (isOperator(s)) {
            if (isNumNext) {
                return false;
            }
            else {
                isNumNext = true;
            }
        }
    }

    if (numParentheses == 0 && !isNumNext) {
        return true;
    }
    else {
        return false;
    }
}

// Conversion

vector<Token> infixToPostfix(const vector<Token>& tokens) {
    vector<Token> output;
    ArrayStack<string> operators;

    for (int i = 0; i < tokens.size(); i++) {
        string s = tokens[i].value;

        if (isdigit(s[0])) {
            output.push_back(Token{s});
        }
        else if (isOperator(s)) {
            while (!operators.empty() && precedence(operators.top()) >= precedence(s) && operators.top() != "(") {
                output.push_back({operators.top()});
                operators.pop();
            }
            operators.push(s);
        }
        else if (s == "(") {
            operators.push(s);
        }
        else if (s == ")") {
            while (!operators.empty() && operators.top() != "(") {
                output.push_back({operators.top()});
                operators.pop();
            }
            if (!operators.empty()) {
                operators.pop();
            }
        }
    }
    while (!operators.empty()) {
        output.push_back({operators.top()});
        operators.pop();
    }


    return output;
}

// Evaluation

double evalPostfix(const vector<Token>& tokens) {
    ArrayStack<double> stack;

    for (int i = 0; i < tokens.size(); i++) {
        string s = tokens[i].value;

        if (isdigit(s[0])) {
            stack.push(stod(s));
        }
        else if (isOperator(s)) {
            double rightValue = stack.top();
            stack.pop();
            double leftValue = stack.top();
            stack.pop();

            if (s == "+") {
                stack.push(leftValue + rightValue);
            }
            else if (s == "-") {
                stack.push(leftValue - rightValue);
            }
            else if (s == "*") {
                stack.push(leftValue * rightValue);
            }
            else if (s == "/") {
                if (rightValue == 0) {
                    return 0;
                }
                stack.push(leftValue / rightValue);
            }
        }
    }

    return stack.top();
}

// Main

int main() {

    string line;
    cout << "Enter expression: ";
    getline(cin, line);

    vector<Token> tokens = tokenize(line);

    if (isValidPostfix(tokens)) {
        cout << "FORMAT: POSTFIX\n";
        cout << "RESULT: " << evalPostfix(tokens) << "\n";
    }
    else if (isValidInfix(tokens)) {
        vector<Token> postfix = infixToPostfix(tokens);
        cout << "FORMAT: INFIX\n";
        cout << "POSTFIX: ";
        for (const auto& t : postfix) {
            cout << t.value << " ";
        }
        cout << "\n";
        cout << "RESULT: " << evalPostfix(postfix) << "\n";
    }
    else {
        cout << "FORMAT: NEITHER\n";
        cout << "ERROR: invalid expression\n";
    }

    return 0;
}