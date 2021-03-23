#pragma once
#ifndef CALC_CLI_CONSTANTS_HPP
#define CALC_CLI_CONSTANTS_HPP


#include <map>
#include <string>


constexpr auto prompt = "> ";
constexpr auto answer = "= ";
constexpr auto error = "Error: ";
constexpr auto quit = "quit";
constexpr auto clear = "clear";
constexpr auto help = "help";


/**
 * Return a map<name, value> of useful mathematical constants.
 */
std::map<std::string, double> get_consts() {
	constexpr double pi = 3.14159;
	constexpr double e = 2.71828;
	constexpr double phi = 1.61803;

	const std::map<std::string, double> consts{
		{"pi", pi},
		{"e", e},
		{"phi", phi}
	};

	return consts;
}


#endif // !CALC_CLI_CONSTANTS_HPP
