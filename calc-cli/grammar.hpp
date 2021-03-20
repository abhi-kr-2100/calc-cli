#pragma once
#ifndef CALC_CLI_GRAMMAR_HPP
#define CALC_CLI_GRAMMAR_HPP


/**
 * calc-cli is a command-line calculator.
 * 
 * grammar.hpp declares functions that parse a given math expression.
 * grammar.hpp uses the following grammar:
 * 
 * <expression> := <expression> "+" <term> | <expression> "-" <term> | <term>
 * <term>		:= <term> "*" <unary> | <term> "/" <unary> | <unary>
 * <unary>		:= "+" <primary> | "-" <primary> | <primary>
 * <primary>	:= "(" <expression> ")" | <primary> "!" | <number>
 * <number>		:= a floating-point literal as used in C++ without unary + or -
 */


#include <vector>

#include "token.hpp"


using Token_iter = std::vector<Token>::const_iterator;


double expression(const Token_iter& start, const Token_iter& end);
double term(const Token_iter& start, const Token_iter& end);
double unary(const Token_iter& start, const Token_iter& end);
double primary(const Token_iter& start, const Token_iter& end);


#endif // !CALC_CLI_GRAMMAR_HPP
