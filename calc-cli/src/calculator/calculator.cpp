/**
 * calc-cli is a command-line calculator.
 *
 * calculator.cpp defines the grammar functions used by the
 * Calculator class.
 * 
 * Calculator uses the following grammar:
 *
 * <statement>		:= <expression> | <declaration>
 * <declaration>	:= "let" <variable> = <expression>
 * <expression>		:= <expression> "+" <term> | <expression> "-" <term> | <term>
 * <term>			:= <term> "*" <unary> | <term> "/" <unary> | <term> "%" <unary> | <unary>
 * <unary>			:= "+" <power> | "-" <power> | <power>
 * <power>			:= <power> "^" <primary> | <primary>
 * <primary>		:= "(" <expression> ")" | <primary> "!" | <number>
 * <number>			:= <call> | <variable> | "_" | a floating-point literal as used in C++ without unary + or -
 * <call>			:= <function> "[" <arguments> "]"
 * <function>		:= a group of letters with no underscore or digits allowed
 * <arguments>		:= <expression> | <arguments> "," <expression>
 * <variable>		:= a group of letters with no underscore or digits allowed
 */


#include <cmath>
#include <string>
#include <vector>

#include "calculator.hpp"
#include "token/token.hpp"
#include "exceptions/exceptions.hpp"


using std::string;
using std::fmod;
using std::tgamma;
using std::pow;
using std::vector;

using ull = unsigned long long;


bool is_operator(Token_type t);
bool is_unary(const Token_iter& current_index,
	const Token_iter& start_index);
double factorial(double n);


double Calculator::statement(const Token_iter& s,
		const Token_iter& e) {
	auto result = (s->type == Token_type::let) ? declaration(s, e) :
		expression(s, e);

	prev = result;
	return result;
}


double Calculator::declaration(const Token_iter& s,
		const Token_iter& e) {
	if (s->type != Token_type::let ||
			(s + 1)->type != Token_type::variable ||
			(s + 2)->type != Token_type::assignment) {
		throw Syntax_error{};
	}

	string name = (s + 1)->name;
	double val = expression(s + 3, e);

	define_var(name, val);

	return val;
}


double Calculator::expression(const Token_iter& s,
		const Token_iter& e) {
	// look for a "+" or "-" from the end that doesn't occur inside
	// parentheses
	ull nesting = 0;	// inside a "(" ... ")"? How deep?
	ull fnesting = 0;	// inside a "[" ... "]"? How deep?

	for (auto i = e; i != s; ) {
		--i;	// because we already start at one past the end
				// don't put it in the condition as a postfix
				// as it musn't be executed when the condition
				// becomes false

		switch (i->type) {
		case Token_type::p_close:
			++nesting;
			break;
		case Token_type::p_open:
			--nesting;
			break;
		case Token_type::arg_delim_close:
			++fnesting;
			break;
		case Token_type::arg_delim_open:
			--fnesting;
			break;
		case Token_type::plus:
			if (!nesting) {
				if (!is_unary(i, s)) {
					return expression(s, i) + term(i + 1, e);
				}
			}
			break;
		case Token_type::minus:
			if (!nesting) {
				if (!is_unary(i, s)) {
					return expression(s, i) - term(i + 1, e);
				}
			}
			break;
		}
	}	// search for <expression> "+" <term> or
		// <expression> "-" <term> fails

	if (nesting || fnesting) {
		throw Unbalanced_parentheses{};
	}

	return term(s, e);
}


double Calculator::term(const Token_iter& s, const Token_iter& e) {
	// look for a "*" or "/" from the end that doesn't occur inside
	// parentheses
	ull nesting = 0;	// inside a "(" ... ")"? How deep?
	ull fnesting = 0;	// inside a "[" ... "]"? How deep?

	for (auto i = e; i != s; ) {
		--i;	// as i starts out pointing past the end
				// see why i should be here in Calculator::expression

		switch (i->type) {
		case Token_type::p_close:
			++nesting;
			break;
		case Token_type::p_open:
			--nesting;
			break;
		case Token_type::arg_delim_close:
			++fnesting;
			break;
		case Token_type::arg_delim_open:
			--fnesting;
			break;
		case Token_type::multiply:
			if (!nesting) {
				return term(s, i) * unary(i + 1, e);
			}
			break;
		case Token_type::divide:
			if (!nesting) {
				double u = unary(i + 1, e);
				if (u == 0) {
					throw Unsupported_operand{};
				}
				return term(s, i) / u;
			}
			break;
		case Token_type::mod:
			if (!nesting) {
				double u = unary(i + 1, e);
				if (u == 0) {
					throw Unsupported_operand{};
				}
				return fmod(term(s, i), u);
			}
		}
	}	// search for <term> "*" <unary> or
		// <term> "/" <unary> fails or <term> "%" <unary> fails

	if (nesting || fnesting) {
		throw Unbalanced_parentheses{};
	}

	return unary(s, e);
}


double Calculator::unary(const Token_iter& s, const Token_iter& e) {
	switch (s->type) {
	case Token_type::plus:
		return +power(s + 1, e);
	case Token_type::minus:
		return -power(s + 1, e);
	default:
		return power(s, e);
	}
}


double Calculator::power(const Token_iter& s, const Token_iter& e) {
	// look for a "^" from the end that doesn't occur inside
	// parentheses
	ull nesting = 0;	// inside a "(" ... ")"? How deep?
	ull fnesting = 0;	// inside a "[" ... "]"? How deep?
	for (auto i = e; i != s; ) {
		--i;	// as i starts out pointing past the end
				// see why i should be here in Calculator::expression

		switch (i->type) {
		case Token_type::p_close:
			++nesting;
			break;
		case Token_type::p_open:
			--nesting;
			break;
		case Token_type::arg_delim_close:
			++fnesting;
			break;
		case Token_type::arg_delim_open:
			--fnesting;
			break;
		case Token_type::power:
			if (!nesting) {
				return pow(power(s, i), primary(i + 1, e));
			}
			break;
		}
	}	// search for <power> "^" <primary> fails

	if (nesting || fnesting) {
		throw Unbalanced_parentheses{};
	}

	return primary(s, e);
}


double Calculator::primary(const Token_iter& s, const Token_iter& e) {
	if ((e - 1)->type == Token_type::factorial) {
		double n = primary(s, e - 1);
		return factorial(n);
	}

	switch (s->type) {
	case Token_type::number:
		return s->value;
	case Token_type::variable:
		if (s != (e - 1) && (s + 1)->type == Token_type::arg_delim_open) {
			if ((e - 1)->type != Token_type::arg_delim_close) {
				throw Unbalanced_parentheses{};
			}
			return invoke_fn(s->name, arguments(s + 1, e));
		}
		return evaluate_var(s->name);
	case Token_type::previous:
		return prev;
	case Token_type::p_open:
		if ((e - 1)->type != Token_type::p_close) {
			throw Unbalanced_parentheses{};
		}
		return expression(s + 1, e - 1);
	default:
		throw Unknown_token{};
	}
}


vector<double> Calculator::arguments(const Token_iter& s,
		const Token_iter& e) {
	// look for a "," from the end that doesn't occur inside
	// parentheses
	ull nesting = 0;	// inside a "(" ... ")"? How deep?
	ull fnesting = 0;	// inside a "[" ... "]"? How deep?

	for (auto i = e; i != s; ) {
		--i;	// as i starts out pointing past the end
				// see why i should be here in Calculator::expression

		switch (i->type) {
		case Token_type::p_close:
			++nesting;
			break;
		case Token_type::p_open:
			--nesting;
			break;
		case Token_type::arg_delim_close:
			++fnesting;
			break;
		case Token_type::arg_delim_open:
			--fnesting;
			break;
		case Token_type::arg_separator: {
			vector<double> args = arguments(s, i);
			args.push_back(expression(i + 1, e));
			return args;
		}
		}
	}	// search for <arguments> "," <expression> fails

	if (nesting || fnesting) {
		throw Unbalanced_parentheses{};
	}
	
	double arg = expression(s + 1, e - 1);
	return { arg };
}


void Calculator::define_var(const string& name, double val) {
	if (variables.find(name) != variables.end()) {
		throw Redeclaration_of_variable{};
	}

	variables[name] = val;
}


double Calculator::evaluate_var(const string& name) {
	if (variables.find(name) == variables.end()) {
		throw Variable_not_defined{};
	}

	return variables[name];
}


double Calculator::invoke_fn(const std::string& name,
		const std::vector<double>& args) {
	if (funcs.find(name) == funcs.end()) {
		throw Variable_not_defined{};
	}

	return funcs[name](args);
}


/**
 * Is the Token referred to by i an operator?
 */
bool is_operator(Token_type t) {
	return t == Token_type::plus || t == Token_type::minus ||
		t == Token_type::multiply || t == Token_type::divide;
}


/**
 * Return true if the operator at position curr is unary.
 */
bool is_unary(const Token_iter& curr, const Token_iter& start) {
	return (curr == start) || is_operator((curr - 1)->type);
}


double factorial(double n) {
	return tgamma(n + 1);
}
