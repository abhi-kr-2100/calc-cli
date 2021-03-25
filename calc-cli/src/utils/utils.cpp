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
#include "consts.hpp"
#include "calc_consts.hpp"
#include "calc_funcs.hpp"
#include "../calculator/exceptions/exceptions.hpp"


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
	std::cout << "\033[2J\033[1; 1H";
#endif
}


/**
 * Display instructions on how to use calc-cli to the standard
 * output.
 */
void display_help() {
	std::cout << "For help, see: " << README_URL << '\n';
}


/**
 * Helper function to display the value of an expression, and handle
 * resulting exceptions.
 */
void calculate(const std::string& input, Calculator& calc) {
	try {
		std::cout << answer << calc.evaluate(input);
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

	if (!std::cin) {
		std::exit(0);
	}

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
