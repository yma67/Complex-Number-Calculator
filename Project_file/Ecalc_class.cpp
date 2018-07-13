//============================================================================
// Name        : Ecalc_class.cpp
// Author      : yma67
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include "Ecalc_class.h"

namespace ecalc {
//============================================================================
// Name        : Ecalc_class.cpp
// Author      : yma67
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================




const std::complex<double> j(0, 1);
const std::complex<double> pi(3.14159265358979323846, 0);
const std::complex<double> theta180(180, 0);


std::deque<std::string> str_tokenizr(const std::string &str) {
    std::deque<std::string> result;
    std::string delim("()^+*-/abcdeghiklmnoqrstuvwxyzpAB");
    std::string::size_type last=0;
    std::string::size_type curr = str.find_first_of(delim, last);
    while (str.length()>curr && str.length()>last) {
        result.push_back(str.substr(last, curr-last));
        result.push_back(std::string(1, str[curr]));
        last=curr+1;
        curr=str.find_first_of(delim, last);
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

bool isUnary(const std::string &optr) {
    return  (optr.find("a")!=std::string::npos) || (optr.find("i")!=std::string::npos) || (optr.find("s")!=std::string::npos) ||
            (optr.find("b")!=std::string::npos) || (optr.find("k")!=std::string::npos) || (optr.find("t")!=std::string::npos) ||
            (optr.find("c")!=std::string::npos) || (optr.find("l")!=std::string::npos) || (optr.find("u")!=std::string::npos) ||
            (optr.find("d")!=std::string::npos) || (optr.find("m")!=std::string::npos) || (optr.find("v")!=std::string::npos) ||
            (optr.find("e")!=std::string::npos) || (optr.find("n")!=std::string::npos) || (optr.find("w")!=std::string::npos) ||
            (optr.find("o")!=std::string::npos) || (optr.find("x")!=std::string::npos) || (optr.find("p")!=std::string::npos) ||
            (optr.find("g")!=std::string::npos) || (optr.find("q")!=std::string::npos) || (optr.find("y")!=std::string::npos) ||
            (optr.find("h")!=std::string::npos) || (optr.find("r")!=std::string::npos) || (optr.find("z")!=std::string::npos) ||
            (optr.find("A")!=std::string::npos) || (optr.find("B")!=std::string::npos);
}

int precd(const std::string &optr) {
    if (isUnary(optr) && (optr.find("p")==std::string::npos)) {
        return 5;
    }
    if ((optr.find("p")!=std::string::npos)) {
        return 4;
    }
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
std::deque<std::string> in2p(const std::deque<std::string> &exp) {
    std::string current;
    std::stack<std::string> operatr;
    std::deque<std::string> expr_queue(exp);
    //std::unique_ptr< std::stack<std::string> > operatr=std::make_unique< std::stack<std::string> >();
    std::deque<std::string> postfx;
    //postfx=std::make_unique< std::stack<std::string> >;
    while (!expr_queue.empty()) {
        current=expr_queue.front();
        expr_queue.pop_front();
        if (precd(current)!=-1 || current=="(" || current==")") {
            if (operatr.empty()) {
                operatr.push(current);
                continue;
            }
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

    while (!operatr.empty()) {
        postfx.push_back(operatr.top());
        operatr.pop();
    }
    return postfx;
}

std::complex<double> to_rad(const std::complex<double> &deg) {
    return (deg*pi)/theta180;
}
std::complex<double> to_deg(const std::complex<double> &rad) {
    return ((rad)*theta180)/pi;
}
std::complex<double> eval(const std::deque<std::string> &pf) {
    std::deque<std::string> postfx(pf);
    std::stack< std::complex<double> > operand;
    std::string current_str;
    while (!postfx.empty()) {
        current_str=postfx.front();
        postfx.pop_front();
        if (isUnary(current_str)) {
            if (current_str=="a") {
                std::complex<double> temp=std::complex<double>(std::abs(operand.top()), 0);
                operand.pop();
                operand.push(temp);
                continue;
            }
            if (current_str=="b") {
                std::complex<double> temp=std::proj(operand.top());
                operand.pop();
                operand.push(temp);
                continue;
            }
            if (current_str=="c") {
                std::complex<double> temp=std::conj(operand.top());
                operand.pop();
                operand.push(temp);
                continue;
            }
            if (current_str=="e") {
                std::complex<double> temp=std::exp(operand.top());
                operand.pop();
                operand.push(temp);
                continue;
            }
            if (current_str=="g") {
                std::complex<double> temp=std::sqrt(operand.top());
                operand.pop();
                operand.push(temp);
                continue;
            }
            if (current_str=="h") {
                std::complex<double> temp=std::sinh(operand.top());
                operand.pop();
                operand.push(temp);
                continue;
            }
            if (current_str=="i") {

                std::complex<double> temp=std::cosh(operand.top());
                operand.pop();
                operand.push(temp);
                continue;
            }
            if (current_str=="k") {
                std::complex<double> temp=std::tanh(operand.top());
                operand.pop();
                operand.push(temp);
                continue;
            }
            if (current_str=="l") {
                std::complex<double> temp=std::asinh(operand.top());
                operand.pop();
                operand.push(temp);
                continue;
            }
            if (current_str=="m") {
                std::complex<double> temp=std::acos(operand.top());
                operand.pop();
                operand.push(temp);
                continue;
            }
            if (current_str=="o") {
                std::complex<double> temp=std::atanh(operand.top());
                operand.pop();
                operand.push(temp);
                continue;
            }
            if (current_str=="q") {
                std::complex<double> temp=std::sin(operand.top());
                operand.pop();
                operand.push(temp);
                continue;
            }
            if (current_str=="r") {
                std::complex<double> temp=std::cos(operand.top());
                operand.pop();
                operand.push(temp);
                continue;
            }
            if (current_str=="s") {
                std::complex<double> temp=std::tan(operand.top());
                operand.pop();
                operand.push(temp);
                continue;
            }
            if (current_str=="t") {
                std::complex<double> temp=std::asin(operand.top());
                operand.pop();
                operand.push(temp);
                continue;
            }
            if (current_str=="u") {
                std::complex<double> temp=std::acos(operand.top());
                operand.pop();
                operand.push(temp);
                continue;
            }
            if (current_str=="v") {
                std::complex<double> temp=std::asin(operand.top());
                operand.pop();
                operand.push(temp);
                continue;
            }
            if (current_str=="w") {
                std::complex<double> temp=std::log(operand.top());
                operand.pop();
                operand.push(temp);
                continue;
            }
            if (current_str=="x") {
                std::complex<double> temp=std::log10(operand.top());
                operand.pop();
                operand.push(temp);
                continue;
            }
            if (current_str=="y") {
                std::complex<double> temp=std::real(operand.top());
                operand.pop();
                operand.push(temp);
                continue;
            }
            if (current_str=="z") {
                std::complex<double> temp=std::imag(operand.top());
                operand.pop();
                operand.push(temp);
                continue;
            }
            if (current_str=="A") {
                std::complex<double> temp=std::arg(operand.top());
                operand.pop();
                operand.push(temp);
                continue;
            }
            if (current_str=="B") {
                std::complex<double> temp=std::norm(operand.top());
                operand.pop();
                operand.push(temp);
                continue;
            }
            if (current_str=="n") {
                std::complex<double> temp=-operand.top();
                operand.pop();
                operand.push(temp);
                continue;
            }
        }
        if (current_str=="^") {
            std::complex<double> temp2=operand.top();
            operand.pop();
            std::complex<double> temp1=operand.top();
            operand.pop();
            operand.push(std::pow(temp1, temp2));
            continue;
        }
        if (current_str=="*") {
            std::complex<double> temp2=operand.top();
            operand.pop();
            std::complex<double> temp1=operand.top();
            operand.pop();
            operand.push(temp1*temp2);
            continue;
        }
        if (current_str=="/") {
            std::complex<double> temp2=operand.top();
            operand.pop();
            std::complex<double> temp1=operand.top();
            operand.pop();
            operand.push(temp1/temp2);
            continue;
        }
        if (current_str=="+") {
            std::complex<double> temp2=operand.top();
            operand.pop();
            std::complex<double> temp1=operand.top();
            operand.pop();
            operand.push(temp1+temp2);
            continue;
        }
        if (current_str=="-") {
            std::complex<double> temp2=operand.top();
            operand.pop();
            std::complex<double> temp1=operand.top();
            operand.pop();
            operand.push(temp1-temp2);
            continue;
        }
        if (current_str=="p") {
            std::complex<double> temp2=operand.top();
            operand.pop();
            std::complex<double> temp1=operand.top();
            operand.pop();
            operand.push(temp1*(std::exp(j*(temp2))));
            continue;
        }
        if (!(precd(current_str)!=-1 || current_str=="(" || current_str==")")) {
            if (current_str.find("j")!=std::string::npos) {
                current_str.erase(std::remove(current_str.begin(), current_str.end(),'j'), current_str.end());
                if (current_str=="") {
                    operand.push(std::complex<double>(0, 1));
                } else {
                    operand.push(std::complex<double>(0, std::stof((current_str))));
                }
                continue;
            }
            if (current_str.find("j")==std::string::npos && current_str.find("p")==std::string::npos) {
                operand.push(std::complex<double>(std::stof(current_str), 0));
                continue;
            }
        }
    }
    return operand.top();
}
std::complex<double> eval_deg(const std::deque<std::string> &pf) {
    std::deque<std::string> postfx(pf);
    std::stack< std::complex<double> > operand;
    std::string current_str;
    while (!postfx.empty()) {
        current_str=postfx.front();
        postfx.pop_front();
        if (isUnary(current_str)) {
            if (current_str=="a") {
                std::complex<double> temp=std::complex<double>(std::abs(operand.top()), 0);
                operand.pop();
                operand.push(temp);
                continue;
            }
            if (current_str=="b") {
                std::complex<double> temp=std::proj(operand.top());
                operand.pop();
                operand.push(temp);
                continue;
            }
            if (current_str=="c") {
                std::complex<double> temp=std::conj(operand.top());
                operand.pop();
                operand.push(temp);
                continue;
            }
            if (current_str=="e") {
                std::complex<double> temp=std::exp(operand.top());
                operand.pop();
                operand.push(temp);
                continue;
            }
            if (current_str=="g") {
                std::complex<double> temp=std::sqrt(operand.top());
                operand.pop();
                operand.push(temp);
                continue;
            }
            if (current_str=="h") {
                std::complex<double> temp=std::sinh(to_rad(operand.top()));
                operand.pop();
                operand.push(temp);
                continue;
            }
            if (current_str=="i") {

                std::complex<double> temp=std::cosh(to_rad(operand.top()));
                operand.pop();
                operand.push(temp);
                continue;
            }
            if (current_str=="k") {
                std::complex<double> temp=std::tanh(to_rad(operand.top()));
                operand.pop();
                operand.push(temp);
                continue;
            }
            if (current_str=="l") {
                std::complex<double> temp=std::asinh(operand.top());
                operand.pop();
                operand.push(to_deg(temp));
                continue;
            }
            if (current_str=="m") {
                std::complex<double> temp=std::acos(operand.top());
                operand.pop();
                operand.push(to_deg(temp));
                continue;
            }
            if (current_str=="o") {
                std::complex<double> temp=std::atanh(operand.top());
                operand.pop();
                operand.push(to_deg(temp));
                continue;
            }
            if (current_str=="q") {
                std::complex<double> temp=std::sin(to_rad(operand.top()));
                operand.pop();
                operand.push(temp);
                continue;
            }
            if (current_str=="r") {
                std::complex<double> temp=std::cos(to_rad(operand.top()));
                operand.pop();
                operand.push(temp);
                continue;
            }
            if (current_str=="s") {
                std::complex<double> temp=std::tan(to_rad(operand.top()));
                operand.pop();
                operand.push(temp);
                continue;
            }
            if (current_str=="t") {
                std::complex<double> temp=std::asin(operand.top());
                operand.pop();
                operand.push(to_deg(temp));
                continue;
            }
            if (current_str=="u") {
                std::complex<double> temp=std::acos(operand.top());
                operand.pop();
                operand.push(to_deg(temp));
                continue;
            }
            if (current_str=="v") {
                std::complex<double> temp=std::asin(operand.top());
                operand.pop();
                operand.push(to_deg(temp));
                continue;
            }
            if (current_str=="w") {
                std::complex<double> temp=std::log(operand.top());
                operand.pop();
                operand.push(temp);
                continue;
            }
            if (current_str=="x") {
                std::complex<double> temp=std::log10(operand.top());
                operand.pop();
                operand.push(temp);
                continue;
            }
            if (current_str=="y") {
                std::complex<double> temp=std::real(operand.top());
                operand.pop();
                operand.push(temp);
                continue;
            }
            if (current_str=="z") {
                std::complex<double> temp=std::imag(operand.top());
                operand.pop();
                operand.push(temp);
                continue;
            }
            if (current_str=="A") {
                std::complex<double> temp=std::arg(operand.top());
                operand.pop();
                operand.push(to_deg(temp));
                continue;
            }
            if (current_str=="B") {
                std::complex<double> temp=std::norm(operand.top());
                operand.pop();
                operand.push(temp);
                continue;
            }
            if (current_str=="n") {
                std::complex<double> temp=-operand.top();
                operand.pop();
                operand.push(temp);
                continue;
            }
        }
        if (current_str=="^") {
            std::complex<double> temp2=operand.top();
            operand.pop();
            std::complex<double> temp1=operand.top();
            operand.pop();
            operand.push(std::pow(temp1, temp2));
            continue;
        }
        if (current_str=="*") {
            std::complex<double> temp2=operand.top();
            operand.pop();
            std::complex<double> temp1=operand.top();
            operand.pop();
            operand.push(temp1*temp2);
            continue;
        }
        if (current_str=="/") {
            std::complex<double> temp2=operand.top();
            operand.pop();
            std::complex<double> temp1=operand.top();
            operand.pop();
            operand.push(temp1/temp2);
            continue;
        }
        if (current_str=="+") {
            std::complex<double> temp2=operand.top();
            operand.pop();
            std::complex<double> temp1=operand.top();
            operand.pop();
            operand.push(temp1+temp2);
            continue;
        }
        if (current_str=="-") {
            std::complex<double> temp2=operand.top();
            operand.pop();
            std::complex<double> temp1=operand.top();
            operand.pop();
            operand.push(temp1-temp2);
            continue;
        }
        if (current_str=="p") {
            std::complex<double> temp2=operand.top();
            operand.pop();
            std::complex<double> temp1=operand.top();
            operand.pop();
            operand.push(temp1*(std::exp(j*(to_rad(temp2)))));
            continue;
        }
        if (!(precd(current_str)!=-1 || current_str=="(" || current_str==")")) {
            if (current_str.find("j")!=std::string::npos) {
                current_str.erase(std::remove(current_str.begin(), current_str.end(),'j'), current_str.end());
                if (current_str=="") {
                    operand.push(std::complex<double>(0, 1));
                } else {
                    operand.push(std::complex<double>(0, std::stof((current_str))));
                }
                continue;
            }
            if (current_str.find("j")==std::string::npos && current_str.find("p")==std::string::npos) {
                operand.push(std::complex<double>(std::stof(current_str), 0));
                continue;
            }
        }
    }
    return operand.top();
}

int mismatch_detect(const std::deque<std::string> &postfx) {
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
    if (left!=right) {
        return -1;
    }
    return 1;
}
//true: degree, false: radian
std::string calculate(const std::string &expr, bool in_param, bool out_param) {
    std::deque<std::string> expr_que;
    std::deque<std::string> postfix;
    std::complex<double> result;
    expr_que=str_tokenizr(expr);
    if (mismatch_detect(expr_que)==-1) {
        return std::string("Parenthesis mismatch");
    }
    postfix=in2p(expr_que);
    if (in_param) {
        result=eval_deg(postfix);
    } else {
        result=eval(postfix);
    }
    if (out_param) {
        return std::to_string(std::abs(result))+"p"+std::to_string(std::abs(to_deg(std::arg(result))));
    } else {
        return std::to_string(result.real())+"+j"+std::to_string(result.imag());
    }
}
std::string toPolar(const std::complex<double> &c) {
    return "("+std::to_string(std::abs(c))+", "+std::to_string((std::arg(c)*180)/M_PI)+")";
}

}
