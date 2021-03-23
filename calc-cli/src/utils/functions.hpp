#pragma once
#ifndef CALC_CLI_FUNCTIONS_HPP
#define CALC_CLI_FUNCTIONS_HPP


#include <vector>
#include <cmath>

#include "../calculator/calculator.hpp"
#include "../calculator/exceptions/exceptions.hpp"


void check_args(const std::vector<double> args, std::size_t n) {
	if (args.size() != n) {
		throw Unsupported_operand{};
	}
}


double cos_func(const std::vector<double> args);
double tan_func(const std::vector<double> args);
double sec_func(const std::vector<double> args);
double csc_func(const std::vector<double> args);
double sin_func(const std::vector<double> args);
double cot_func(const std::vector<double> args);


/**
 * Return a map<name, function> of useful mathematical functions.
 */
std::map<std::string, Calc_func> get_funcs() {
	const std::map<std::string, Calc_func> funcs{
		{"sin", sin_func},
		{"cos", cos_func},
		{"tan", tan_func},
		{"sec", sec_func},
		{"csc", csc_func},
		{"cot", cot_func}
	};

	return funcs;
}


double sin_func(const std::vector<double> args) {
	check_args(args, 1);
	return std::sin(args[0]);
}

double cos_func(const std::vector<double> args) {
	check_args(args, 1);
	return std::cos(args[0]);
}

double tan_func(const std::vector<double> args) {
	check_args(args, 1);
	return std::tan(args[0]);
}

double sec_func(const std::vector<double> args) {
	check_args(args, 1);
	return 1 / std::cos(args[0]);
}

double csc_func(const std::vector<double> args) {
	check_args(args, 1);
	return 1 / std::sin(args[0]);
}

double cot_func(const std::vector<double> args) {
	check_args(args, 1);
	return 1 / std::tan(args[0]);
}


#endif // !CALC_CLI_FUNCTIONS_HPP
