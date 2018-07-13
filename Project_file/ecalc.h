#ifndef ECALC_H
#define ECALC_H
#include <iostream>
#include <stack>
#include <deque>
#include <string>
#include <memory>
#include <cmath>
#include <vector>
#include <complex>
#include <algorithm>
#include <QtDebug>

/*Reason for return object: 1. they are optimized by c++ st. they are small
 *                          2. don't want to change value in-place
*/

//used for both ecalc.cpp (model) and signal slots (control)
bool checkValid(const QString &numero);

//detect expression with mismatch
bool mismatch_detect(const std::deque<std::string> &postfx);

//tokenize input string with operators+numbers
std::deque<std::string> str_tokenizr(const std::string &str);

//is this operator unary?
bool isUnary(const std::string &optr);

//returns precedence of operators
int precd(const std::string &optr);

//convert infix to postfix
std::deque<std::string> in2p(const std::deque<std::string> &exp);

//convert degree to rad
std::complex<double> to_rad(const std::complex<double> &deg);

//convert rad to degree
std::complex<double> to_deg(const std::complex<double> &rad);

//evaluate with radian input
std::complex<double> eval(const std::deque<std::string> &pf);

//evaluate with degree input
std::complex<double> eval_deg(const std::deque<std::string> &pf);

//calculate based on degree or radian, returns a double
std::complex<double> calculate(const std::string &expr, bool in_param);

//used for signal slots (control): simplify answers
std::string removeLastZero(const std::string &str);

//used for signal slots (control): convert to expression that ecalc (module) understands
QString replaceSym(const QString &str);

#endif // ECALC_H
