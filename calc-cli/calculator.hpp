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
 * <statement>		:= <expression> | <declaration>
 * <declaration>	:= "let" <variable> = <expression>
 * <expression>		:= <expression> "+" <term> | <expression> "-" <term> | <term>
 * <term>			:= <term> "*" <unary> | <term> "/" <unary> | <term> "%" <unary> | <unary>
 * <unary>			:= "+" <primary> | "-" <primary> | <primary>
 * <primary>		:= "(" <expression> ")" | <primary> "!" | <number>
 * <number>			:= <variable> | "_" | a floating-point literal as used in C++ without unary + or -
 * <variable>		:= a group of letters with no underscore or digits allowed
 */


#include <vector>
#include <map>
#include <string>

#include "token.hpp"


using Token_iter = std::vector<Token>::const_iterator;


class Calculator {
public:
	// user of calculator should only have to call the statement method
	double statement(const Token_iter& start, const Token_iter& end);
private:
	double declaration(const Token_iter& start, const Token_iter& end);
	double expression(const Token_iter& start, const Token_iter& end);
	double term(const Token_iter& start, const Token_iter& end);
	double unary(const Token_iter& start, const Token_iter& end);
	double primary(const Token_iter& start, const Token_iter& end);

	void define_var(const std::string& name, double value);
	double evaluate_var(const std::string& name);

	// result of the previous calculation
	double prev{};

	std::map<std::string, double> variables;
};


#endif // !CALC_CLI_CALCULATOR_HPP
