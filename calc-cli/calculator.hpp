#pragma once
#ifndef CALC_CLI_CALCULATOR_HPP
#define CALC_CLI_CALCULATOR_HPP


/**
 * calc-cli is a command-line calculator.
 *
 * calculator.hpp declares the Calculator class that stores
 * calculator state, and provides methods for parsing input and
 * performing calculations.
 * 
 * Calculator uses the following grammar:
 * 
 * <statement>	:= <expression>
 * <expression> := <expression> "+" <term> | <expression> "-" <term> | <term>
 * <term>		:= <term> "*" <unary> | <term> "/" <unary> | <term> "%" <unary> | <unary>
 * <unary>		:= "+" <primary> | "-" <primary> | <primary>
 * <primary>	:= "(" <expression> ")" | <primary> "!" | <number>
 * <number>		:= a floating-point literal as used in C++ without unary + or -
 */


#include <vector>

#include "token.hpp"


using Token_iter = std::vector<Token>::const_iterator;


class Calculator {
public:
	// user of calculator should only have to call the statement method
	double statement(const Token_iter& start, const Token_iter& end);
private:
	double expression(const Token_iter& start, const Token_iter& end);
	double term(const Token_iter& start, const Token_iter& end);
	double unary(const Token_iter& start, const Token_iter& end);
	double primary(const Token_iter& start, const Token_iter& end);

	// result of the previous calculation
	double prev;
};


#endif // !CALC_CLI_CALCULATOR_HPP
