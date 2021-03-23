/**
 * calc-cli is a command-line calculator.
 * 
 * It supports the basic four functions, float modulus and float
 * factorial along with user-defined variables.
 */


#include <iostream>
#include <string>
#include <cstdlib>

#include "calculator/calculator.hpp"
#include "calculator/token/token.hpp"
#include "calculator/exceptions/exceptions.hpp"
#include "utils.hpp"


using std::cout;
using std::cin;
using std::cerr;
using std::getline;
using std::string;
using std::exit;


double evaluate(const string& expression, Calculator& calc);
void calculate(const string& input, Calculator& calc);
void run(Calculator& calc);


constexpr auto prompt = "> ";
constexpr auto answer = "= ";
constexpr auto error = "Error: ";
constexpr auto quit = "quit";
constexpr auto clear = "clear";
constexpr auto help = "help";


int main() {
	auto consts = get_consts();
	auto funcs = get_funcs();

	Calculator calc{ consts, funcs };

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
