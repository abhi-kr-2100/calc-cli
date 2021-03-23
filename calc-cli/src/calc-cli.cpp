/**
 * calc-cli is a command-line calculator.
 * 
 * It supports the basic four functions, float modulus and float
 * factorial along with user-defined variables.
 */


#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <map>

#ifdef _WIN32
#include <Windows.h>
#endif

#include "calculator/calculator.hpp"
#include "calculator/token/token.hpp"
#include "calculator/exceptions/exceptions.hpp"


using std::cout;
using std::cin;
using std::cerr;
using std::getline;
using std::string;
using std::exit;
using std::map;


double evaluate(const string& expression, Calculator& calc);
void clrscr();
void display_help();
void calculate(const string& input, Calculator& calc);
void run(Calculator& calc);


constexpr auto prompt = "> ";
constexpr auto answer = "= ";
constexpr auto error = "Error: ";
constexpr auto quit = "quit";
constexpr auto clear = "clear";
constexpr auto help = "help";


constexpr double pi = 3.14159;
constexpr double e = 2.71828;
constexpr double phi = 1.61803;


int main() {
	const map<string, double> consts{
		{"pi", pi},
		{"e", e},
		{"phi", phi}
	};

	Calculator calc{ consts };

	while (true) {
		run(calc);
	}
}


/**
 * Return the value of a math expression.
 */
double evaluate(const string& s, Calculator& calc) {
	auto tokens = tokenize(s);
	return calc.statement(tokens.begin(), tokens.end());
}


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
 * Helper function to display the value of an expression, and handle
 * resulting exceptions.
 */
void calculate(const string& input, Calculator& calc) {
	try {
		cout << answer << evaluate(input, calc);
	} catch (Unbalanced_parentheses&) {
		cerr << error << "unbalanced parentheses.";
	} catch (Unknown_token&) {
		cerr << error << "unknown token.";
	} catch (Bad_literal&) {
		cerr << error << "not a valid number.";
	} catch (Unsupported_operand&) {
		cerr << error << "operation not supported by operand.";
	} catch (Syntax_error&) {
		cerr << error << "syntax error.";
	} catch (Redeclaration_of_variable&) {
		cerr << error << "variable already exists.";
	} catch (Variable_not_defined&) {
		cerr << error << "no such variable.";
	}

	cout << "\n";
}


/**
 * Take input, and produce the right output.
 */
void run(Calculator& calc) {
	cout << prompt;
	string input;
	getline(cin, input);

	if (input.size() == 0) {
		return;
	} else if (input == quit) {
		exit(0);
	} else if (input == clear) {
		clrscr();
		return;
	} else if (input == help) {
		display_help();
		return;
	}

	calculate(input, calc);
}


void display_help() {
	cout << "For help, see: https://github.com/abhi-kr-2100/calc-cli/blob/master/README.md" << '\n';
}