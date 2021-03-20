/**
 * calc-cli is a command-line calculator.
 *
 * token.cpp defines the tokenize function from token.hpp.
 */


#include <vector>
#include <string>
#include <sstream>

#include "token.hpp"
#include "exceptions.hpp"


using namespace std::literals::string_literals;

using std::vector;
using std::string;
using std::istringstream;

using ull = unsigned long long;


double read_number(istringstream& source, char start);


/**
 * Tokenize the given string into mathematical symbols and
 * floating-point literal.
 */
vector<Token> tokenize(const string& s) {
	vector<Token> toks;
	ull nesting = 0;	// are we inside a "(" .. ")", how deep?

	istringstream sin{ s };
	while (true) {
		char token;
		sin >> token;

		if (!sin) {
			break;
		}

		switch (token) {
		case '+':
			toks.push_back(Token{ Token_type::plus });
			break;
		case '-':
			toks.push_back(Token{ Token_type::minus });
			break;
		case '*':
			toks.push_back(Token{ Token_type::multiply });
			break;
		case '/':
			toks.push_back(Token{ Token_type::divide });
			break;
		case '(':
			toks.push_back(Token{ Token_type::p_open });
			++nesting;
			break;
		case ')':
			toks.push_back(Token{ Token_type::p_close });
			--nesting;
			break;
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
		case '.': {	// floating-point literal may start with a "."
			sin.putback(token);
			double n = read_number(sin, token);

			toks.push_back(Token{ Token_type::number, n });
			break;
		}
		default:
			throw Unknown_token{};
		}
	}

	if (nesting) {
		throw Unbalanced_parentheses{};
	}

	return toks;
}


double read_number(istringstream& in, char c) {
	double n;
	in >> n;

	if (in.bad()) {
		throw Bad_literal{};
	}

	return n;
}