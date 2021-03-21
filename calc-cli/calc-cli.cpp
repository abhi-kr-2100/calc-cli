/**
 * calc-cli is a command-line calculator.
 * 
 * It supports addition, subtraction, multiplication, division, and
 * factorial of positive integers along with parentheses to change
 * the order of evaluation.
 */


#include <iostream>
#include <string>

#ifdef _WIN32
#include <Windows.h>
#endif

#include "calculator.hpp"
#include "token.hpp"
#include "exceptions.hpp"


using std::cout;
using std::cin;
using std::cerr;
using std::getline;
using std::string;


double evaluate(const string& expression, Calculator& calc);
void clrscr();


int main() {
	constexpr auto prompt = "> ";
	constexpr auto answer = "= ";
	constexpr auto error = "Error: ";
	constexpr auto quit = "quit";
	constexpr auto clear = "clear";

	Calculator calc{};
	while (true) {
		cout << prompt;
		string input;
		getline(cin, input);

		if (input.size() == 0) {
			continue;
		} else if (input == quit) {
			return 0;
		} else if (input == clear) {
			clrscr();
			continue;
		}

		try {
			cout << answer << evaluate(input, calc);
		} catch (Unbalanced_parentheses&) {
			cerr << error << "unbalanced parentheses.";
		} catch (Unknown_token&) {
			cerr << error << "unknown token.";
		} catch (Bad_literal&) {
			cerr << error << "not a valid number.";
		} catch (Divide_by_zero&) {
			cerr << error << "can't divide by zero.";
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