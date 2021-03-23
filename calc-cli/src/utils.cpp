/**
 * calc-cli is a command-line calculator.
 *
 * utils.cpp defines the functions in utils.hpp.
 */


#include <map>
#include <string>
#include <cmath>
#include <iostream>
#include <vector>

#ifdef _WIN32
#include <Windows.h>
#endif

#include "utils.hpp"
#include "calculator/exceptions/exceptions.hpp"


/**
 * Clear the screen by outputing a special terminal sequence.
 *
 * Taken from: https://stackoverflow.com/questions/5866529/how-do-we-clear-the-console-in-assembly/5866648#5866648
 */
void clrscr() {
#ifdef _WIN32
	COORD tl = { 0,0 };
	CONSOLE_SCREEN_BUFFER_INFO s;
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(console, &s);
	DWORD written, cells = s.dwSize.X * s.dwSize.Y;
	FillConsoleOutputCharacter(console, ' ', cells, tl, &written);
	FillConsoleOutputAttribute(console, s.wAttributes, cells, tl, &written);
	SetConsoleCursorPosition(console, tl);
#else
	cout << "clear command is not supported.\n";
#endif
}


void display_help() {
	std::cout << "For help, see: https://github.com/abhi-kr-2100/calc-cli/blob/master/README.md" << '\n';
}


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
	const Calc_func c_sin = sin_func;
	const Calc_func c_cos = cos_func;
	const Calc_func c_tan = tan_func;
	const Calc_func c_sec = sec_func;
	const Calc_func c_csc = csc_func;
	const Calc_func c_cot = cot_func;

	const std::map<std::string, Calc_func> funcs{
		{"sin", c_sin},
		{"cos", c_cos},
		{"tan", c_tan},
		{"sec", c_sec},
		{"csc", c_csc},
		{"cot", c_cot}
	};

	return funcs;
}



double sin_func(const std::vector<double> args) {
	if (args.size() != 1) {
		throw Unsupported_operand{};
	}

	return std::sin(args[0]);
}

double cos_func(const std::vector<double> args) {
	if (args.size() != 1) {
		throw Unsupported_operand{};
	}

	return std::cos(args[0]);
}

double tan_func(const std::vector<double> args) {
	if (args.size() != 1) {
		throw Unsupported_operand{};
	}

	return std::tan(args[0]);
}

double sec_func(const std::vector<double> args) {
	if (args.size() != 1) {
		throw Unsupported_operand{};
	}

	return 1 / std::cos(args[0]);
}

double csc_func(const std::vector<double> args) {
	if (args.size() != 1) {
		throw Unsupported_operand{};
	}

	return 1 / std::sin(args[0]);
}

double cot_func(const std::vector<double> args) {
	if (args.size() != 1) {
		throw Unsupported_operand{};
	}

	return 1 / std::tan(args[0]);
}
