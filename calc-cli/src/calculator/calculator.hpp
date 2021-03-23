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
 * <unary>			:= "+" <power> | "-" <power> | <power>
 * <power>			:= <power> "^" <primary> | <primary>
 * <primary>		:= "(" <expression> ")" | <primary> "!" | <number>
 * <number>			:= <call> | <variable> | "_" | a floating-point literal as used in C++ without unary + or -
 * <call>			:= <function> "[" <arguments> "]"
 * <function>		:= a group of letters with no underscore or digits allowed
 * <arguments>		:= <expression> | <arguments> "," <expression>
 * <variable>		:= a group of letters with no underscore or digits allowed
 */


#include <vector>
#include <map>
#include <string>
#include <functional>

#include "token/token.hpp"


using Token_iter = std::vector<Token>::const_iterator;
using Calc_func = std::function<double(const std::vector<double>&)>;


class Calculator {
public:
	Calculator(const std::map<std::string, double>& consts={},
			const std::map<std::string, Calc_func>& functions={}) {
		for (const auto& c : consts) {
			variables[c.first] = c.second;
		}

		for (const auto& f : functions) {
			funcs[f.first] = f.second;
		}
	}

	// users of calculator should only have to call statement
	double statement(const Token_iter& start, const Token_iter& end);

private:
	double declaration(const Token_iter& start, const Token_iter& end);
	double expression(const Token_iter& start, const Token_iter& end);
	double term(const Token_iter& start, const Token_iter& end);
	double unary(const Token_iter& start, const Token_iter& end);
	double power(const Token_iter& start, const Token_iter& end);
	double primary(const Token_iter& start, const Token_iter& end);
	std::vector<double> arguments(const Token_iter& start,
		const Token_iter& end);

	// result of the previous calculation
	double prev{};

	std::map<std::string, double> variables;

	void define_var(const std::string& name, double value);
	double evaluate_var(const std::string& name);


	std::map<std::string,
		std::function<double(const std::vector<double>&)>> funcs;
	double invoke_fn(const std::string& name,
		const std::vector<double>& args);
};


#endif // !CALC_CLI_CALCULATOR_HPP
