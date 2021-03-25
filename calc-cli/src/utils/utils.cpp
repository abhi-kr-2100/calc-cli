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
#include "calc_consts.hpp"
#include "calc_funcs.hpp"
#include "../calculator/exceptions/exceptions.hpp"
#include "../calculator/token/token.hpp"


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


/**
 * Display instructions on how to use calc-cli to the standard
 * output.
 */
void display_help() {
	std::cout << "For help, see: https://github.com/abhi-kr-2100/calc-cli/blob/master/README.md" << '\n';
}


/**
 * Return the value of a math expression.
 */
double evaluate(const std::string& s, Calculator& calc) {
	auto tokens = tokenize(s);
	return calc.statement(tokens.begin(), tokens.end());
}


/**
 * Helper function to display the value of an expression, and handle
 * resulting exceptions.
 */
void calculate(const std::string& input, Calculator& calc) {
	try {
		std::cout << answer << evaluate(input, calc);
	} catch (Calc_cli_exception& e) {
		std::cerr << error << e.what();
	}

	std::cout << "\n";
}


/**
 * Take input, and produce the right output.
 */
void run(Calculator& calc) {

	std::cout << prompt;
	std::string input;
	std::getline(std::cin, input);

	if (input.size() == 0) {
		return;
	}
	else if (input == quit) {
		std::exit(0);
	}
	else if (input == clear) {
		clrscr();
		return;
	}
	else if (input == help) {
		display_help();
		return;
	}

	calculate(input, calc);
}
