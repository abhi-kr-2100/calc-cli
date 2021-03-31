#pragma once
#ifndef CALC_CLI_FUNCTIONS_HPP
#define CALC_CLI_FUNCTIONS_HPP


#include <vector>
#include <cmath>

#include "../calculator/calculator.hpp"
#include "../calculator/exceptions/exceptions.hpp"


bool check_args(const std::vector<double> args, std::size_t n,
		bool should_throw = true) {

	if (args.size() != n) {
		if (should_throw) {
			throw Unsupported_operand{
				"invalid number of arguments" };
		}

		return false;
	}

	return true;
}


double sin_func(const std::vector<double> args);
double cos_func(const std::vector<double> args);
double tan_func(const std::vector<double> args);
double csc_func(const std::vector<double> args);
double sec_func(const std::vector<double> args);
double cot_func(const std::vector<double> args);

double asin_func(const std::vector<double> args);
double acos_func(const std::vector<double> args);
double atan_func(const std::vector<double> args);
double acsc_func(const std::vector<double> args);
double asec_func(const std::vector<double> args);
double acot_func(const std::vector<double> args);

double sinh_func(const std::vector<double> args);
double cosh_func(const std::vector<double> args);
double tanh_func(const std::vector<double> args);
double csch_func(const std::vector<double> args);
double sech_func(const std::vector<double> args);
double coth_func(const std::vector<double> args);

double asinh_func(const std::vector<double> args);
double acosh_func(const std::vector<double> args);
double atanh_func(const std::vector<double> args);
double acsch_func(const std::vector<double> args);
double asech_func(const std::vector<double> args);
double acoth_func(const std::vector<double> args);

double d_func(const std::vector<double> args);
double r_func(const std::vector<double> args);

double ln_func(const std::vector<double> args);
double log_func(const std::vector<double> args);
double log2_func(const std::vector<double> args);

double sqrt_func(const std::vector<double> args);
double cbrt_func(const std::vector<double> args);

double abs_func(const std::vector<double> args);
double round_func(const std::vector<double> args);

double sum_func(const std::vector<double> args);
double average_func(const std::vector<double> args);

double factorial_func(const std::vector<double> args);
double permutation_func(const std::vector<double> args);
double combination_func(const std::vector<double> args);


/**
 * Return a map<name, function> of useful mathematical functions.
 */
std::map<std::string, Calc_func> get_funcs() {
	const std::map<std::string, Calc_func> funcs{
		{ "sin", sin_func },
		{ "cos", cos_func },
		{ "tan", tan_func },
		{ "csc", csc_func },
		{ "sec", sec_func },
		{ "cot", cot_func },

		{ "asin", asin_func },
		{ "acos", acos_func },
		{ "atan", atan_func },
		{ "acsc", acsc_func },
		{ "asec", asec_func },
		{ "acot", acot_func },

		{ "sinh", sinh_func },
		{ "cosh", cosh_func },
		{ "tanh", tanh_func },
		{ "csch", csch_func },
		{ "sech", sech_func },
		{ "coth", coth_func },

		{ "asinh", asinh_func },
		{ "acosh", acosh_func },
		{ "atanh", atanh_func },
		{ "acsch", acsch_func },
		{ "asech", asech_func },
		{ "acoth", acoth_func },

		{ "d", d_func },
		{ "r", r_func },

		{ "ln", ln_func },
		{ "log", log_func },
		{ "logb", log2_func },

		{ "sqrt", sqrt_func },
		{ "cbrt", cbrt_func },

		{ "abs", abs_func },
		{ "round", round_func },

		{ "sum", sum_func },
		{ "average", average_func },

		{ "factorial", factorial_func },
		{ "combination", combination_func },
		{ "permutation", permutation_func },
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

double csc_func(const std::vector<double> args) {
	check_args(args, 1);
	return 1 / std::sin(args[0]);
}

double sec_func(const std::vector<double> args) {
	check_args(args, 1);
	return 1 / std::cos(args[0]);
}

double cot_func(const std::vector<double> args) {
	check_args(args, 1);
	return 1 / std::tan(args[0]);
}

double asin_func(const std::vector<double> args) {
	check_args(args, 1);
	return std::asin(args[0]);
}

double acos_func(const std::vector<double> args) {
	check_args(args, 1);
	return std::acos(args[0]);
}


double atan_func(const std::vector<double> args) {
	check_args(args, 1);
	return std::atan(args[0]);
}

double acsc_func(const std::vector<double> args) {
	check_args(args, 1);
	return std::asin(1 / args[0]);
}

double asec_func(const std::vector<double> args) {
	check_args(args, 1);
	return std::acos(1 / args[0]);
}

double acot_func(const std::vector<double> args) {
	check_args(args, 1);
	return std::atan(1 / args[0]);
}

double sinh_func(const std::vector<double> args) {
	check_args(args, 1);
	return std::sinh(args[0]);
}

double cosh_func(const std::vector<double> args) {
	check_args(args, 1);
	return std::cosh(args[0]);
}


double tanh_func(const std::vector<double> args) {
	check_args(args, 1);
	return std::tanh(args[0]);
}

double csch_func(const std::vector<double> args) {
	check_args(args, 1);
	return 1 / std::sinh(args[0]);
}

double sech_func(const std::vector<double> args) {
	check_args(args, 1);
	return 1 / std::cosh(args[0]);
}

double coth_func(const std::vector<double> args) {
	check_args(args, 1);
	return 1 / std::tanh(args[0]);
}

double asinh_func(const std::vector<double> args) {
	check_args(args, 1);
	return std::asinh(args[0]);
}

double acosh_func(const std::vector<double> args) {
	check_args(args, 1);
	return std::acosh(args[0]);
}


double atanh_func(const std::vector<double> args) {
	check_args(args, 1);
	return std::atanh(args[0]);
}

double acsch_func(const std::vector<double> args) {
	check_args(args, 1);
	return std::asinh(1 / args[0]);
}

double asech_func(const std::vector<double> args) {
	check_args(args, 1);
	return std::acosh(1 / args[0]);
}

double acoth_func(const std::vector<double> args) {
	check_args(args, 1);
	return std::atanh(1 / args[0]);
}


double d_func(const std::vector<double> args) {
	check_args(args, 1);
	return args[0] * 57.2958;
}


double r_func(const std::vector<double> args) {
	check_args(args, 1);
	return args[0] * 0.0174533;
}


double ln_func(const std::vector<double> args) {
	check_args(args, 1);
	return std::log(args[0]);
}

double log_func(const std::vector<double> args) {
	check_args(args, 1);
	return std::log10(args[0]);
}

double log2_func(const std::vector<double> args) {
	check_args(args, 1);
	return std::log2(args[0]);
}


double sqrt_func(const std::vector<double> args) {
	check_args(args, 1);
	return std::sqrt(args[0]);
}

double cbrt_func(const std::vector<double> args) {
	check_args(args, 1);
	return std::cbrt(args[0]);
}


double abs_func(const std::vector<double> args) {
	check_args(args, 1);
	return std::fabs(args[0]);
}

double round_func(const std::vector<double> args) {
	check_args(args, 1);
	return std::round(args[0]);
}


double sum_func(const std::vector<double> args) {
	double s = 0;
	for (auto i : args) {
		s += i;
	}

	return s;
}

double average_func(const std::vector<double> args) {
	if (check_args(args, 0, false)) {
		throw Unsupported_operand{
			"can't take average of zero numbers" };
	}

	return sum_func(args) / args.size();
}


double factorial_func(const std::vector<double> args) {
	check_args(args, 1);
	return std::tgamma(args[0] + 1);
}


double permutation_func(const std::vector<double> args) {
	check_args(args, 2);
	return std::tgamma(args[0] + 1) / 
		std::tgamma(args[0] - args[1] + 1);
}

double combination_func(const std::vector<double> args) {
	auto p = permutation_func(args);
	return p / std::tgamma(args[1] + 1);
}

#endif // !CALC_CLI_FUNCTIONS_HPP
