/**
 * calc-cli is a command-line calculator.
 *
 * token.cpp defines the tokenize function from token.hpp.
 */


#include <vector>
#include <string>
#include <sstream>
#include <cctype>

#include "token.hpp"
#include "../exceptions/exceptions.hpp"


using namespace std::literals::string_literals;

using std::vector;
using std::string;
using std::istringstream;
using std::isalpha;

using ull = unsigned long long;


double read_number(istringstream& source, char start);
string read_name(istringstream& source);


// how a variable definition starts
constexpr auto var_decl_start = "let";


/**
 * Tokenize the given string into mathematical symbols and
 * floating-point literal.
 */
vector<Token> tokenize(const string& s) {
	vector<Token> toks;

	ull nesting = 0;	// are we inside a "(" .. ")", how deep?
	ull fnesting = 0;	// are we inside a "[" .. "]", how deep?

	istringstream sin{ s };
	for (char token; sin >> token; ) {
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
		case '%':
			toks.push_back(Token{ Token_type::mod });
			break;
		case '^':
			toks.push_back(Token{ Token_type::power });
			break;
		case '(':
			toks.push_back(Token{ Token_type::p_open });
			++nesting;
			break;
		case ')':
			toks.push_back(Token{ Token_type::p_close });
			--nesting;
			break;
		case '[':
			toks.push_back(Token{ Token_type::arg_delim_open });
			++fnesting;
			break;
		case ']':
			toks.push_back(Token{ Token_type::arg_delim_close });
			--fnesting;
			break;
		case ',':
			toks.push_back(Token{ Token_type::arg_separator });
			break;
		case '_':
			toks.push_back(Token{ Token_type::previous });
			break;
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
		case '.': {	// floating-point literal may start with a "."
			sin.putback(token);
			double n = read_number(sin, token);

			toks.push_back(Token{ Token_type::number, n });
			break;
		}
		case '!':
			toks.push_back(Token{ Token_type::factorial });
			break;
		case '=':
			toks.push_back(Token{ Token_type::assignment });
			break;
		default:
			if (isalpha(token)) {
				// variable or "let"-variable definition
				
				sin.putback(token);
				string name = read_name(sin);
				if (name == "let") {
					toks.push_back(Token{ Token_type::let });
				} else {
					toks.push_back(
						Token{ Token_type::variable, 0, name});
				}
			} else {
				throw Unknown_token{};
			}
		}
	}

	if (nesting || fnesting) {
		throw Unbalanced_parentheses{};
	}

	return toks;
}


/**
 * Read and return a floating-point number from the given input
 * source.
 */
double read_number(istringstream& in, char) {
	double n;
	in >> n;

	if (in.bad()) {
		throw Bad_literal{};
	}

	return n;
}


/**
 * Read and return a variable name.
 * 
 * A variable name consists of alphabetical characters and no spaces.
 * Unlike a variable name in C++, it can't contain underscore or
 * digits.
 */
string read_name(istringstream& in) {
	string name;

	char c;
	while (in.get(c) && isalpha(c)) {
		name += c;
	}
	in.putback(c);

	return name;
}
