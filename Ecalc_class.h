/*
 * Ecalc_class.h
 *
 *  Created on: 2018年7月8日
 *      Author: yuxiangma
 */

#ifndef ECALC_CLASS_H_
#define ECALC_CLASS_H_
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
namespace ecalc{
std::deque<std::string> str_tokenizr(const std::string &str);
bool isUnary(const std::string &optr);
int precd(const std::string &optr);
std::deque<std::string> in2p(const std::deque<std::string> &exp);
std::complex<double> to_rad(const std::complex<double> &deg);
std::complex<double> to_deg(const std::complex<double> &rad);
std::complex<double> eval(const std::deque<std::string> &pf);
std::complex<double> eval_deg(const std::deque<std::string> &pf);
int mismatch_detect(const std::deque<std::string> &postfx);
std::string calculate(const std::string &expr, bool in_param, bool out_param);
std::string toPolar(const std::complex<double> &c);
}


#endif /* ECALC_CLASS_H_ */
