#pragma once
#ifndef CALC_CLI_UTILS_HPP
#define CALC_CLI_UTILS_HPP


/**
 * calc-cli is a command-line calculator.
 * 
 * utils.hpp declares some helpful functions to assist calc-cli.
 */


#include <map>
#include <string>

#include "calculator/calculator.hpp"


void clrscr();
void display_help();

std::map<std::string, double> get_consts();
std::map<std::string, Calc_func> get_funcs();

double evaluate(const std::string& expression, Calculator& calc);
void calculate(const std::string& input, Calculator& calc);
void run(Calculator& calc);


#endif // !CALC_CLI_UTILS_HPP
