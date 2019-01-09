//
//  eval.cpp
//  Homework 2
//
//  Created by Anthony on 2/3/17.
//  Copyright © 2017 CS32. All rights reserved.
//

#include <iostream>
#include <string>
#include <cctype>
#include <stack>
#include <cassert>
#include <cctype> // for isdigit()
using namespace std;

string infixToPostfix(string infix, string& postfix);
int precedence(char ch);

int evaluate(string infix, const bool values[], string& postfix, bool& result){
    // CHECK FOR CORRECTNESS
    string temp = ""; // let's remove the spaces from the infix to make it easier to parse
    int openParen = 0;
    int closeParen = 0;
    for (int i = 0; i < infix.size(); i++){
        if (infix[i] != ' ')
            temp = temp + infix[i];
    }
    
    if (temp[temp.size() - 1] == '|' || temp[temp.size() - 1] == '&' || temp[temp.size() - 1] == '!'){ // the starts and ends of the infix shouldn't be operators | or &
        return 1;
    }
    
    if (temp[0] == '|' || temp[0] == '&'){ // the starts and ends of the infix shouldn't be operators | or &
        return 1;
    }
    
    for (int i = 0; i < temp.size(); i++){
        if (temp[i] == '('){ // ensure the number of opening and closing parenthesis are the same
            openParen++;
        } else if (temp[i] == ')'){
            closeParen++;
        }
        
        if (temp[i] == '&' || temp[i] == '|'){ // if the current is an operator
            if ((!isdigit(temp[i - 1]) && temp[i - 1] != ')') || (!isdigit(temp[i + 1]) && temp[i + 1] !='!' && temp[i + 1] !='(')){ // must be followed/preceeded by a digit or parenthesis
                return 1;
            }
        } else if (isdigit(temp[i])){ // if the current is an operand
            if (isdigit(temp[i + 1]) || temp[i + 1] == '(' || temp[i + 1] == '!'){ // we can't have another digit, an open paren, or !
                return 1;
            }
        }
    }
    
    if (openParen != closeParen){ // // ensure the number of opening and closing parenthesis are the same
        return 1;
    }
    
    // EVALUATE
    stack<bool> bool_stack; // Initialize the operand stack to empty
    
    postfix = infixToPostfix(infix, postfix);
    if (postfix.empty() == true){
        return 1;
    }
    
    for (int i = 0; i < postfix.length(); i++){
        char ch = postfix[i]; // For each character ch in the postfix string
        if (ch == '0' || ch == '1' || ch == '2' || ch == '3' || ch == '4' || ch == '5' || ch == '6' || ch == '7' || ch == '8' || ch == '9'){ // if it's a digit
            int actualInt = ch - '0'; // convert the char to an int
            if (values[actualInt] == true){ // if the digit's index is true
                bool_stack.push(true); // push a true value onto the bool stack
            } else {
                bool_stack.push(false);
            }
        } else { // it's an operator
            if (ch == '!'){
                bool_stack.push(!bool_stack.top()); // perform the operation
                bool_stack.pop();
            } else {
                bool operand2 = bool_stack.top(); //set operand2 to the top of the operand stack
                bool_stack.pop();
                if (bool_stack.empty()){ // ensure you can keep going
                    return 1;
                }
                bool operand1 = bool_stack.top(); //set operand1 to the top of the operand stack
                bool_stack.pop();
                
                if (postfix[i] == '|'){ // since | has higher precendence
                    if (operand1 || operand2){ // perform the approporiate operation
                        bool_stack.push(true);
                    } else {
                        bool_stack.push(false);
                    }
                }
                
                if (postfix[i] == '&'){
                    if (operand1 && operand2){ // perform the approporiate operation
                        bool_stack.push(true);
                    } else {
                        bool_stack.push(false);
                    }
                }
            }
        }
    }
    result = bool_stack.top(); // When the loop is finished, the operand stack will contain one item, the result of evaluating the expression
    return 0;
}

string infixToPostfix(string infix, string& postfix){
    postfix = ""; // Initialize postfix to empty
    stack<char> oper_stack; // Initialize the operator stack to empty
    for (int i = 0; i < infix.size(); i++){ // 	For each character ch in the infix string
        char ch = infix[i];
        switch (ch){ // Switch (ch)
        	// CASE OPERAND
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                postfix += ch; // append ch to end of postfix
                break;
                
            // CASE '('
            case '(': // push ch onto the operator stack
                oper_stack.push(ch);
                break;
                
            // CASE ')'
            case ')':
                while (oper_stack.top() != '('){ // While stack top is not '('
                    postfix += oper_stack.top(); // append the stack top to postfix
                    oper_stack.pop(); // pop the stack
                }
                oper_stack.pop(); // pop the stack  // remove the '('
                break;
                
        	// CASE OPERATOR
            case '&':
            case '|':
            case '!':
//                int precedenceCurrent;
//                if (ch == '!'){
//                    precedenceCurrent = 3;
//                } else if (ch == '&'){
//                    precedenceCurrent = 2;
//                } else if (ch == '|'){
//                    precedenceCurrent = 1;
//                } else {
//                    precedenceCurrent = 0;
//                }
//                
//                int precedenceTop;
//                if (oper_stack.top() == '!'){
//                    precedenceTop = 3;
//                } else if (oper_stack.top() == '&'){
//                    precedenceTop = 2;
//                } else if (oper_stack.top() == '|'){
//                    precedenceTop = 1;
//                } else {
//                    precedenceTop = 0;
//                }
                while (!oper_stack.empty() && oper_stack.top() != '(' && precedence(ch) <= precedence(oper_stack.top())){ // While the stack is not empty and the stack top is not '(' and precedence of ch <= precedence of stack top
                    postfix += oper_stack.top(); // append the stack top to postfix
                    oper_stack.pop(); // pop the stack
                }
                oper_stack.push(ch); // push ch operator on the stack
                break;
            default:
                break;
        }
    }
    
    while (!oper_stack.empty()){ //	While the stack is not empty
        postfix = postfix + oper_stack.top(); // append the stack top to postfix
        oper_stack.pop(); // pop the stack
    }
    
    return postfix;
}

int precedence(char ch){
    if (ch == '!'){ // return a higher number depending on
        return 3;
    } else if (ch == '&'){
        return 2;
    } else if (ch == '|'){
        return 1;
    } else {
        return 0;
    }
}

// 0 is true
// 1 is false
int main()
{
    bool ba[10] = {
        //  0      1      2      3      4      5      6      7      8      9
        true,  true,  true,  false, false, false, true,  false, true,  false
    };
    string pf;
    bool answer;
    assert(evaluate("2| 3", ba, pf, answer) == 0  &&  pf == "23|" &&  answer);
    assert(evaluate("8|", ba, pf, answer) == 1);
    assert(evaluate("8|", ba, pf, answer) == 1);
    assert(evaluate("!8|", ba, pf, answer) == 1);
    assert(evaluate("(8))", ba, pf, answer) == 1);
    assert(evaluate("4 5", ba, pf, answer) == 1);
    assert(evaluate("01", ba, pf, answer) == 1);
    assert(evaluate("()", ba, pf, answer) == 1);
    assert(evaluate("2(9|8)", ba, pf, answer) == 1);
    assert(evaluate("2(&8)", ba, pf, answer) == 1);
    assert(evaluate("(2(8))", ba, pf, answer) == 1);
    assert(evaluate("(6&(7|7)", ba, pf, answer) == 1);
    assert(evaluate("", ba, pf, answer) == 1);
    assert(evaluate("4  |  !3 & (0&3) ", ba, pf, answer) == 0
           &&  pf == "43!03&&|"  &&  !answer);
    assert(evaluate(" 9  ", ba, pf, answer) == 0  &&  pf == "9"  &&  !answer);
    ba[2] = false;
    ba[9] = true;
    assert(evaluate("((9))", ba, pf, answer) == 0  &&  pf == "9"  &&  answer);
    assert(evaluate("2| 3", ba, pf, answer) == 0  &&  pf == "23|" &&  !answer);
    cout << "Passed all tests" << endl;
}
