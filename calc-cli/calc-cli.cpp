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


using std::cout;
using std::cin;
using std::getline;
using std::string;


double evaluate(const string& expression);


int main() {
	constexpr auto prompt = "> ";
	constexpr auto answer = "= ";
	constexpr auto quit = "quit";

	while (true) {
		cout << prompt;
		string input;
		getline(cin, input);

		if (input == quit) {
			return 0;
		}

		cout << answer << evaluate(input) << "\n";
	}
}


/**
 * Return the value of a math expression.
 */
double evaluate(const string& s) {
	auto tokens = tokenize(s);
	return expression(tokens.begin(), tokens.end());
}