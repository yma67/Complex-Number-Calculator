//============================================================================
// Name        : Ecalc_class.cpp
// Author      : yma67
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include "ecalc.h"

//define constant object used in program: more efficient
const std::complex<double> j(0, 1.0);
const std::complex<double> pi(3.14159265358979323846, 0);
const std::complex<double> theta180(180.0, 0);

/* inputs a string of math expression, check it by identifying whether there is extra symbols
 * true if there is no extra symbols i.e. expression is valid to be pass for futher calc
 * in: string
 * out: boolean
*/
bool checkValid(const QString &numero) {
    QString entered(numero);
    //remove all valid expressions, if the rest is empty, valid
    //also, null expression is not valid
    entered.replace("arcsinh", "");
    entered.replace("arccosh", "");
    entered.replace("arctanh", "");
    entered.replace("arcsinh", "");
    entered.replace("arcsin", "");
    entered.replace("arccos", "");
    entered.replace("arctan", "");
    entered.replace("‖z‖", "");
    entered.replace("sqrt", "");
    entered.replace("PROJ", "");
    entered.replace("CONJ", "");
    entered.replace("sinh", "");
    entered.replace("cosh", "");
    entered.replace("tanh", "");
    entered.replace("sin", "");
    entered.replace("cos", "");
    entered.replace("tan", "");
    entered.replace("exp", "");
    entered.replace("log", "");
    entered.replace("ln", "");
    entered.replace("Re", "");
    entered.replace("Im", "");
    entered.replace("∠θ", "");
    entered.replace("π", "");
    entered.replace("∠", "");
    entered.replace("-", "");
    entered.replace("^", "");
    entered.replace("＋", "");
    entered.replace("—", "");
    entered.replace("×", "");
    entered.replace("÷", "");
    entered.replace("1", "");
    entered.replace("2", "");
    entered.replace("3", "");
    entered.replace("4", "");
    entered.replace("5", "");
    entered.replace("6", "");
    entered.replace("7", "");
    entered.replace("8", "");
    entered.replace("9", "");
    entered.replace("0", "");
    entered.replace("j", "");
    entered.replace(".", "");
    entered.replace("(", "");
    entered.replace(")", "");
    return entered=="";
}

/* Tokenizer takes processed valid expression string and convert into tokenized queue for infix to postfix
 * in: string
 * out: queue
 */
std::deque<std::string> str_tokenizr(const std::string &str) {
    std::deque<std::string> result;
    std::string delim(std::string("()^+*-/abcdefghiklmnoqrstuvwxyzpA"));
    std::string::size_type last=0;
    std::string::size_type curr = str.find_first_of(delim, last);
    while (std::string::npos>curr && std::string::npos>last) {
        result.push_back(str.substr(last, curr-last));
        result.push_back(std::string(1, str[curr]));
        last=curr+1;
        curr=str.find_first_of(delim, last);
    }
    if (curr==std::string::npos && last<str.length()) {
        result.push_back(str.substr(last));
    }
    for (std::deque<std::string>::iterator it=result.begin(); it<result.end(); ) {
        if (*it=="") {
            it = result.erase(it);
        } else {
            ++it;
        }
    }
    return result;
}

/* Is this operator is unary? Note that not all unary operators have highest precedence!
 * if unary, output true
 * input: string
 * output: bool
 */
bool isUnary(const std::string &optr) {
    return  (optr.find("a")!=std::string::npos) || (optr.find("i")!=std::string::npos) || (optr.find("s")!=std::string::npos) ||
            (optr.find("b")!=std::string::npos) || (optr.find("k")!=std::string::npos) || (optr.find("t")!=std::string::npos) ||
            (optr.find("c")!=std::string::npos) || (optr.find("l")!=std::string::npos) || (optr.find("u")!=std::string::npos) ||
            (optr.find("d")!=std::string::npos) || (optr.find("m")!=std::string::npos) || (optr.find("v")!=std::string::npos) ||
            (optr.find("e")!=std::string::npos) || (optr.find("n")!=std::string::npos) || (optr.find("w")!=std::string::npos) ||
            (optr.find("o")!=std::string::npos) || (optr.find("x")!=std::string::npos) || (optr.find("p")!=std::string::npos) ||
            (optr.find("g")!=std::string::npos) || (optr.find("q")!=std::string::npos) || (optr.find("y")!=std::string::npos) ||
            (optr.find("h")!=std::string::npos) || (optr.find("r")!=std::string::npos) || (optr.find("z")!=std::string::npos) ||
            (optr.find("A")!=std::string::npos) || (optr.find("f")!=std::string::npos);
}

/* Precedence of operator, high->high output, not an operator? return -1
 * input: string
 * output: integer (we need negative, if use unsigned, infinity can be used)
 */
int precd(const std::string &optr) {
    //unary negative highest
    if (optr=="n") {
        return 6;
    }
    //arg L operator, second high precedence, but in order to allow rL(-theta), this is 1 less than unary-
    if ((optr.find("p")!=std::string::npos)) {
        return 5;
    }
    //other unary operators are high in precedence
    if (isUnary(optr) && (optr.find("p")==std::string::npos)) {
        return 4;
    }
    //binary operators ^>*/>+-
    if ((optr.find("^")!=std::string::npos)) {
        return 3;
    }
    if ((optr.find("/")!=std::string::npos) || (optr.find("*")!=std::string::npos)) {
        return 2;
    }
    if ((optr.find("+")!=std::string::npos) || (optr.find("-")!=std::string::npos)) {
        return 1;
    }
    return -1;
}

/* This method detects mismatch in string
 * input: queue
 * output: boolean
 */
bool mismatch_detect(const std::deque<std::string> &postfx) {
    int left=0;
    int right=0;
    for (std::string str: postfx) {
        if (str.find(")")!=std::string::npos) {
            right++;
        }
        if (str.find("(")!=std::string::npos) {
            left++;
        }
    }
    return left==right;
}

/* Infix to postfix, we need stack and queue in stl
 * input: tokenized queue
 * output: postfix queue
 */
std::deque<std::string> in2p(const std::deque<std::string> &exp) {
    std::string current;
    std::stack<std::string> operatr;
    std::deque<std::string> expr_queue(exp);
    std::deque<std::string> postfx;
    //loop until input is empty
    while (!expr_queue.empty()) {
        //pop current element
        current=expr_queue.front();
        expr_queue.pop_front();
        //if expression is operator
        if (precd(current)!=-1 || current=="(" || current==")") {
            //push if stack is empty
            if (operatr.empty()) {
                operatr.push(current);
                continue;
            }
            //parenthesis
            if (current=="(") {
                operatr.push(current);
                continue;
            }
            if (current==")") {
                while (!operatr.empty() && operatr.top()!="(") {
                    postfx.push_back(operatr.top());
                    operatr.pop();
                }
                operatr.pop();
                continue;
            }
            //this eliminate a ( and a ), no parenthesis in output
            //to do this , we pop everything between ( and )
            if ((current!="(") && (current!=")")) {
                while (true) {
                    if ((operatr.empty()) || (precd(current)>precd(operatr.top()) && current!=")")) {
                        operatr.push(current);
                        break;
                    } else {
                        postfx.push_back(operatr.top());
                        operatr.pop();
                    }
                }
                continue;
            }
        } else {
            postfx.push_back(current);
        }
    }
    //queue should be empty
    while (!operatr.empty()) {
        postfx.push_back(operatr.top());
        operatr.pop();
    }
    return postfx;
}

//converter
std::complex<double> to_rad(const std::complex<double> &deg) {
    return (deg*pi)/theta180;
}

//converter
std::complex<double> to_deg(const std::complex<double> &rad) {
    return ((rad)*theta180)/pi;
}

/* Evaluate postfix
 * input: postfix queue
 * output: complex number result
 */
std::complex<double> eval(const std::deque<std::string> &pf) {
    std::deque<std::string> postfx(pf);
    std::stack< std::complex<double> > operand;
    std::string current_str;
    std::complex<double> temp;
    std::complex<double> temp1;
    std::complex<double> temp2;
    while (!postfx.empty()) {
        current_str=postfx.front();
        postfx.pop_front();
        //unary operator
        if (isUnary(current_str)) {
            if (current_str=="a") {
                temp=std::abs(operand.top());
                operand.pop();
                operand.push(temp);
                continue;
            }
            if (current_str=="b") {
                temp=std::proj(operand.top());
                operand.pop();
                operand.push(temp);
                continue;
            }
            if (current_str=="c") {
                temp=std::conj(operand.top());
                operand.pop();
                operand.push(temp);
                continue;
            }
            if (current_str=="e") {
                temp=std::exp(operand.top());
                operand.pop();
                operand.push(temp);
                continue;
            }
            if (current_str=="g") {
                temp=std::sqrt(operand.top());
                operand.pop();
                operand.push(temp);
                continue;
            }
            if (current_str=="h") {
                temp=std::sinh(operand.top());
                operand.pop();
                operand.push(temp);
                continue;
            }
            if (current_str=="i") {
                temp=std::cosh(operand.top());
                operand.pop();
                operand.push(temp);
                continue;
            }
            if (current_str=="k") {
                temp=std::tanh(operand.top());
                operand.pop();
                operand.push(temp);
                continue;
            }
            if (current_str=="l") {
                temp=std::asinh(operand.top());
                operand.pop();
                operand.push(temp);
                continue;
            }
            if (current_str=="m") {
                temp=std::acos(operand.top());
                operand.pop();
                operand.push(temp);
                continue;
            }
            if (current_str=="o") {
                temp=std::atanh(operand.top());
                operand.pop();
                operand.push(temp);
                continue;
            }
            if (current_str=="q") {
                temp=std::sin(operand.top());
                operand.pop();
                operand.push(temp);
                continue;
            }
            if (current_str=="r") {
                temp=std::cos(operand.top());
                operand.pop();
                operand.push(temp);
                continue;
            }
            if (current_str=="s") {
                temp=std::tan(operand.top());
                operand.pop();
                operand.push(temp);
                continue;
            }
            if (current_str=="t") {
                temp=std::asin(operand.top());
                operand.pop();
                operand.push(temp);
                continue;
            }
            if (current_str=="u") {
                temp=std::acos(operand.top());
                operand.pop();
                operand.push(temp);
                continue;
            }
            if (current_str=="v") {
                temp=std::asin(operand.top());
                operand.pop();
                operand.push(temp);
                continue;
            }
            if (current_str=="w") {
                temp=std::log(operand.top());
                operand.pop();
                operand.push(temp);
                continue;
            }
            if (current_str=="x") {
                temp=std::log10(operand.top());
                operand.pop();
                operand.push(temp);
                continue;
            }
            if (current_str=="y") {
                temp=std::real(operand.top());
                operand.pop();
                operand.push(temp);
                continue;
            }
            if (current_str=="z") {
                temp=std::imag(operand.top());
                operand.pop();
                operand.push(temp);
                continue;
            }
            if (current_str=="A") {
                temp=std::arg(operand.top());
                operand.pop();
                operand.push(temp);
                continue;
            }
            if (current_str=="n") {
                temp=-operand.top();
                operand.pop();
                operand.push(temp);
                continue;
            }
        }
        //binary operator
        if (current_str=="^") {
            temp2=operand.top();
            operand.pop();
            temp1=operand.top();
            operand.pop();
            operand.push(std::pow(temp1, temp2));
            continue;
        }
        if (current_str=="*") {
            temp2=operand.top();
            operand.pop();
            temp1=operand.top();
            operand.pop();
            operand.push(temp1*temp2);
            continue;
        }
        if (current_str=="/") {
            temp2=operand.top();
            operand.pop();
            temp1=operand.top();
            operand.pop();
            operand.push(temp1/temp2);
            continue;
        }
        if (current_str=="+") {
            temp2=operand.top();
            operand.pop();
            temp1=operand.top();
            operand.pop();
            operand.push(temp1+temp2);
            continue;
        }
        if (current_str=="-") {
            temp2=operand.top();
            operand.pop();
            temp1=operand.top();
            operand.pop();
            operand.push(temp1-temp2);
            continue;
        }
        if (current_str=="f") {
            temp2=operand.top();
            operand.pop();
            temp1=operand.top();
            operand.pop();
            operand.push(std::pow(temp1, temp2));
            continue;
        }
        if (current_str=="p") {
            temp2=operand.top();
            operand.pop();
            temp1=operand.top();
            operand.pop();
            operand.push(temp1*(std::exp(j*(temp2))));
            continue;
        }
        //number
        if (!(precd(current_str)!=-1 || current_str=="(" || current_str==")")) {
            //complex j
            if (current_str.find("j")!=std::string::npos) {
                current_str.erase(std::remove(current_str.begin(), current_str.end(),'j'), current_str.end());
                if (current_str=="") {
                    operand.push(std::complex<double>(0, 1));
                } else {
                    operand.push(std::complex<double>(0, std::stod((current_str))));
                }
                continue;
            }
            //pure number
            if (current_str.find("j")==std::string::npos && current_str.find("p")==std::string::npos) {
                operand.push(std::complex<double>(std::stod(current_str), 0));
                continue;
            }
            //used to reserved for const pi
            if (current_str.find("B")!=std::string::npos) {
                qDebug()<<"find B";
                current_str.erase(std::remove(current_str.begin(), current_str.end(),'B'), current_str.end());
                if (current_str=="") {
                    operand.push(std::complex<double>(pi));
                } else {
                    operand.push(std::complex<double>(pi*std::stod((current_str))));
                }
                continue;
            }
        }
    }
    return operand.top();
}
/*degree version: for every 1. output of inverse-triangular function apply to_deg
 *                          2. input of triangular function apply to_rad
 * input: postfix queue
 * output: complex number result
 */
std::complex<double> eval_deg(const std::deque<std::string> &pf) {
    std::deque<std::string> postfx(pf);
    std::stack< std::complex<double> > operand;
    std::string current_str;
    std::complex<double> temp;
    std::complex<double> temp1;
    std::complex<double> temp2;
    while (!postfx.empty()) {
        current_str=postfx.front();
        postfx.pop_front();
        if (isUnary(current_str)) {
            if (current_str=="a") {
                temp=std::complex<double>(std::abs(operand.top()), 0);
                operand.pop();
                operand.push(temp);
                continue;
            }
            if (current_str=="b") {
                temp=std::proj(operand.top());
                operand.pop();
                operand.push(temp);
                continue;
            }
            if (current_str=="c") {
                temp=std::conj(operand.top());
                operand.pop();
                operand.push(temp);
                continue;
            }
            if (current_str=="e") {
                temp=std::exp(operand.top());
                operand.pop();
                operand.push(temp);
                continue;
            }
            if (current_str=="g") {
                temp=std::sqrt(operand.top());
                operand.pop();
                operand.push(temp);
                continue;
            }
            if (current_str=="h") {
                temp=std::sinh(to_rad(operand.top()));
                operand.pop();
                operand.push(temp);
                continue;
            }
            if (current_str=="i") {
                temp=std::cosh(to_rad(operand.top()));
                operand.pop();
                operand.push(temp);
                continue;
            }
            if (current_str=="k") {
                temp=std::tanh(to_rad(operand.top()));
                operand.pop();
                operand.push(temp);
                continue;
            }
            if (current_str=="l") {
                temp=std::asinh(operand.top());
                operand.pop();
                operand.push(to_deg(temp));
                continue;
            }
            if (current_str=="m") {
                temp=std::acos(operand.top());
                operand.pop();
                operand.push(to_deg(temp));
                continue;
            }
            if (current_str=="o") {
                temp=std::atanh(operand.top());
                operand.pop();
                operand.push(to_deg(temp));
                continue;
            }
            if (current_str=="q") {
                temp=std::sin(to_rad(operand.top()));
                operand.pop();
                operand.push(temp);
                continue;
            }
            if (current_str=="r") {
                temp=std::cos(to_rad(operand.top()));
                operand.pop();
                operand.push(temp);
                continue;
            }
            if (current_str=="s") {
                temp=std::tan(to_rad(operand.top()));
                operand.pop();
                operand.push(temp);
                continue;
            }
            if (current_str=="t") {
                temp=std::asin(operand.top());
                operand.pop();
                operand.push(to_deg(temp));
                continue;
            }
            if (current_str=="u") {
                temp=std::acos(operand.top());
                operand.pop();
                operand.push(to_deg(temp));
                continue;
            }
            if (current_str=="v") {
                temp=std::asin(operand.top());
                operand.pop();
                operand.push(to_deg(temp));
                continue;
            }
            if (current_str=="w") {
                temp=std::log(operand.top());
                operand.pop();
                operand.push(temp);
                continue;
            }
            if (current_str=="x") {
                temp=std::log10(operand.top());
                operand.pop();
                operand.push(temp);
                continue;
            }
            if (current_str=="y") {
                temp=std::real(operand.top());
                operand.pop();
                operand.push(temp);
                continue;
            }
            if (current_str=="z") {
                temp=std::imag(operand.top());
                operand.pop();
                operand.push(temp);
                continue;
            }
            if (current_str=="A") {
                temp=std::arg(operand.top());
                operand.pop();
                operand.push(to_deg(temp));
                continue;
            }
            if (current_str=="n") {
                temp=-operand.top();
                operand.pop();
                operand.push(temp);
                continue;
            }
        }
        if (current_str=="^") {
            temp2=operand.top();
            operand.pop();
            temp1=operand.top();
            operand.pop();
            operand.push(std::pow(temp1, temp2));
            continue;
        }
        if (current_str=="*") {
            temp2=operand.top();
            operand.pop();
            temp1=operand.top();
            operand.pop();
            operand.push(temp1*temp2);
            continue;
        }
        if (current_str=="/") {
            temp2=operand.top();
            operand.pop();
            temp1=operand.top();
            operand.pop();
            operand.push(temp1/temp2);
            continue;
        }
        if (current_str=="+") {
            temp2=operand.top();
            operand.pop();
            temp1=operand.top();
            operand.pop();
            operand.push(temp1+temp2);
            continue;
        }
        if (current_str=="-") {
            temp2=operand.top();
            operand.pop();
            temp1=operand.top();
            operand.pop();
            operand.push(temp1-temp2);
            continue;
        }
        if (current_str=="p") {
            temp2=operand.top();
            operand.pop();
            temp1=operand.top();
            operand.pop();
            operand.push(temp1*(std::exp(j*(to_rad(temp2)))));
            continue;
        }
        if (current_str=="f") {
            temp2=operand.top();
            operand.pop();
            temp1=operand.top();
            operand.pop();
            operand.push(std::pow(temp1, temp2));
            continue;
        }
        if (!(precd(current_str)!=-1 || current_str=="(" || current_str==")")) {
            if (current_str.find("j")!=std::string::npos) {
                current_str.erase(std::remove(current_str.begin(), current_str.end(),'j'), current_str.end());
                if (current_str=="") {
                    operand.push(std::complex<double>(0, 1));
                } else {
                    operand.push(std::complex<double>(0, std::stod((current_str))));
                }
                continue;
            }
            if (current_str.find("j")==std::string::npos && current_str.find("p")==std::string::npos) {
                operand.push(std::complex<double>(std::stod(current_str), 0));
                continue;
            }
            if (current_str.find("B")!=std::string::npos) {
                qDebug()<<"find B";
                current_str.erase(std::remove(current_str.begin(), current_str.end(),'B'), current_str.end());
                if (current_str=="") {
                    operand.push(std::complex<double>(pi));
                } else {
                    operand.push(std::complex<double>(pi*std::stod((current_str))));
                }
                continue;
            }
        }
    }
    return operand.top();
}



//true: degree, false: radian
std::complex<double> calculate(const std::string &expr, bool in_param) {
    //no need for ptr, they are small and indep of length/type contained
    std::deque<std::string> expr_que;
    std::deque<std::string> postfix;

    //tokenize
    expr_que=str_tokenizr(expr);

    //if mismatch, exception
    if (!mismatch_detect(expr_que)) {
        throw "Parenthesis Mismatch";
    }

    //infix to postfix
    postfix=in2p(expr_que);

#ifdef DEBUG
    for (std::string str: expr_que) {
        qDebug()<<QString::fromStdString(str)<<" ";
    }
    qDebug()<<"\n";

    for (std::string str: postfix) {
        qDebug()<<QString::fromStdString(str)<<" ";
    }
    qDebug()<<"\n";
#endif

    //return a complex number according to user selection
    if (in_param) {
        return eval_deg(postfix);
    } else {
        return eval(postfix);
    }
}

/* Simple algorithm used in grade school to remove unnecessary 0s in a number
 * input: string (numeric)
 * putput: string (simplified)
 */
std::string removeLastZero(const std::string &str) {
    std::string numstr(str);
    if (std::string::npos == numstr.find('.')) {
        return numstr;
    }
    size_t length = numstr.length();
    for (size_t i = length - 1; i > 0; --i) {
        if ('0' == numstr[i]) {
            numstr=numstr.substr(0,i);
        } else if ('.' == numstr[i]) {
            numstr=numstr.substr(0,i);
            break;
        } else {
            break;
        }
    }
    return numstr;
}

/* This function convert entered expression to expression that ecalc (model) understands
 * input: QString
 * output: QString
 */
QString replaceSym(const QString &str) {
    QString entered(str);
    entered.replace("arcsinh", "l");
    entered.replace("arccosh", "m");
    entered.replace("arctanh", "o");
    entered.replace("arcsinh", "l");
    entered.replace("arcsin", "t");
    entered.replace("arccos", "u");
    entered.replace("arctan", "v");
    entered.replace("‖z‖", "a");
    entered.replace("sqrt", "g");
    entered.replace("PROJ", "b");
    entered.replace("CONJ", "c");
    entered.replace("sinh", "h");
    entered.replace("cosh", "i");
    entered.replace("tanh", "k");
    entered.replace("sin", "q");
    entered.replace("cos", "r");
    entered.replace("tan", "s");
    entered.replace("exp", "e");
    entered.replace("log", "x");
    entered.replace("ln", "w");
    entered.replace("Re", "y");
    entered.replace("Im", "z");
    entered.replace("∠θ", "A");
    entered.replace("π", "3.14159265358979323846");
    entered.replace("∠", "p");
    entered.replace("-", "n");
    entered.replace("^", "f");
    entered.replace("＋", "+");
    entered.replace("—", "-");
    entered.replace("×", "*");
    entered.replace("÷", "/");
    return entered;
}
