#pragma once
#ifndef CALC_CLI_TOKEN_HPP
#define CALC_CLI_TOKEN_HPP


/**
 * calc-cli is a command-line calculator.
 * 
 * token.hpp declares the Token type, and the related tokenize
 * function.
 */


#include <vector>
#include <string>


enum class Token_type {
	plus, minus, multiply, divide, mod, power,
	number,
	p_open, p_close,	// parentheses
	factorial,
	previous,			// token which prints the value of the
						// previous calculation
	let,				// used to start a variable definition
	variable,
	assignment,
	arg_delim_open, arg_delim_close,	// used to delimit arguments
										// to a function
	arg_separator
};


struct Token {
	Token_type type;
	double value;		// used only when type is Token_type::number
	std::string name;	// used only when type is
						// Token_type::variable
};


std::vector<Token> tokenize(const std::string& expression);


#endif // !CALC_CLI_TOKEN_HPP
