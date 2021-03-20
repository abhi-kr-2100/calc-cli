/**
 * calc-cli is a command-line calculator.
 * 
 * It supports addition, subtraction, multiplication, and division
 * along with parentheses to change the order of evaluation.
 */


#include <iostream>
#include <string>

#include "token.hpp"
#include "grammar.hpp"
#include "exceptions.hpp"


using std::cout;
using std::cin;
using std::cerr;
using std::getline;
using std::string;


double evaluate(const string& expression);


int main() {
	constexpr auto prompt = "> ";
	constexpr auto answer = "= ";
	constexpr auto error = "Error: ";
	constexpr auto quit = "quit";

	while (true) {
		cout << prompt;
		string input;
		getline(cin, input);

		if (input.size() == 0) {
			continue;
		} else if (input == quit) {
			return 0;
		}

		try {
			cout << answer << evaluate(input);
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
		}

		cout << "\n";
	}
}


/**
 * Return the value of a math expression.
 */
double evaluate(const string& s) {
	auto tokens = tokenize(s);
	return expression(tokens.begin(), tokens.end());
}