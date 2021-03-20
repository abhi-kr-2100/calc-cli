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
	plus, minus, multiply, divide,
	number,
	p_open, p_close	// parentheses
};


struct Token {
	Token_type type;
	double value;	// used only in case type is Token_type::number
};


std::vector<Token> tokenize(const std::string& expression);


#endif // !CALC_CLI_TOKEN_HPP
