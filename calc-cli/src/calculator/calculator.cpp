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
#include <algorithm>

#include "calculator.hpp"
#include "token/token.hpp"
#include "exceptions/exceptions.hpp"


using std::string;
using std::vector;

using ull = unsigned long long;


bool is_operator(Token_type t);

bool is_unary(const Token_iter& current_index,
	const Token_iter& start_index);

double factorial(double n);

Token_iter backward_find(const Token_iter& start,
	const Token_iter& end, const vector<Token_type>& to_find);


double Calculator::statement(const Token_iter& s,
		const Token_iter& e) {
	
	double result;
	if (s->type == Token_type::let) {	// variable definition
		result = declaration(s, e);
	} else {
		result = expression(s, e);
	}

	prev = result;
	return result;
}


double Calculator::declaration(const Token_iter& s,
		const Token_iter& e) {

	// let (1) var (2) = (3) exp (4)
	// a valid declaration must have all four parts
	if (!(s + 1 == e || s + 2 == e || s + 3 == e)) {
		throw Syntax_error{};
	}

	if (s->type != Token_type::let ||
			(s + 1)->type != Token_type::variable ||
			(s + 2)->type != Token_type::assignment) {
		throw Syntax_error{};
	}

	// at what position do (2) and (4) start
	auto var_start = s + 1;
	auto exp_start = s + 3;

	string name = var_start->name;
	double val = expression(exp_start, e);

	define_var(name, val);

	// result of a variable definition is the ultimate value
	// assigned to the variable
	return val;
}


double Calculator::expression(const Token_iter& s,
		const Token_iter& e) {

	auto p = backward_find(s, e,
		{ Token_type::plus, Token_type::minus });
	if (p == e) {
		return term(s, e);
	} else if (p->type == Token_type::plus) {
		return expression(s, p) + term(p + 1, e);
	} else {
		return expression(s, p) - term(p + 1, e);
	}
}


double Calculator::term(const Token_iter& s, const Token_iter& e) {
	using std::fmod;

	auto p = backward_find(s, e, {
		Token_type::multiply, Token_type::divide, Token_type::mod });
	if (p == e) {
		return unary(s, e);
	}
	else if (p->type == Token_type::multiply) {
		return term(s, p) * unary(p + 1, e);
	} else {
		auto r = unary(p + 1, e);
		if (r == 0) {
			throw Unsupported_operand{};
		}

		if (p->type == Token_type::divide) {
			return term(s, p) / r;
		} else {
			return fmod(term(s, p), r);
		}
	}
}


double Calculator::unary(const Token_iter& s, const Token_iter& e) {
	int multiplier = 1;

	Token_iter i;
	for (i = s; i->type == Token_type::plus; ++i) {
	}

	for (; i->type == Token_type::minus; ++i) {
		multiplier *= -1;
	}

	return multiplier * power(i, e);
}


double Calculator::power(const Token_iter& s, const Token_iter& e) {
	using std::pow;

	auto p = backward_find(s, e, { Token_type::power });
	if (p == e) {
		return primary(s, e);
	} else {
		return pow(power(s, p), primary(p + 1, e));
	}
}


double Calculator::primary(const Token_iter& s,
		const Token_iter& e) {

	if (e == s) {	// this is caused when a lone `!` is given as
					// input
		throw Syntax_error{};
	}

	if ((e - 1)->type == Token_type::factorial) {
		double n = primary(s, e - 1);
		return factorial(n);
	}

	switch (s->type) {
	case Token_type::number:
		return s->value;
	case Token_type::variable:	// could be a variable or function

		// function: name (1) [ (2) args (3) ] (4)
		if (s != (e - 1) && (s + 1)->type == Token_type::arg_delim_open) {
			if ((e - 1)->type != Token_type::arg_delim_close) {
				throw Unbalanced_parentheses{};
			}
			return invoke_fn(s->name, arguments(s + 1, e));
		}

		// variable
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

	auto p = backward_find(s, e, { Token_type::arg_separator });
	if (p == e) {
		return { expression(s + 1, e - 1) };
	} else {
		auto args = arguments(s, p);
		auto exp = expression(p + 1, e);
		args.push_back(exp);

		return args;
	}
}


/**
 * Define a new variable.
 */
void Calculator::define_var(const string& name, double val) {
	if (variables.find(name) != variables.end()) {
		throw Redeclaration_of_variable{};
	}

	variables[name] = val;
}


/**
 * Return the value of a previously defined variable.
 */
double Calculator::evaluate_var(const string& name) {
	if (variables.find(name) == variables.end()) {
		throw Variable_not_defined{};
	}

	return variables[name];
}


/**
 * Return the result of invoking a predefined function.
 */
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
		t == Token_type::multiply || t == Token_type::divide ||
		t == Token_type::assignment || t == Token_type::mod ||
		t == Token_type::power;
}


/**
 * Return true if the operator at position curr is unary.
 */
bool is_unary(const Token_iter& curr, const Token_iter& start) {
	return (curr == start) || is_operator((curr - 1)->type);
}


/**
 * Float factorial.
 */
double factorial(double n) {
	using std::tgamma;

	return tgamma(n + 1);
}


/**
 * Return the position of the last occurrence of any one of the given
 * Token_types where it doesn't occur inside a nesting. On failure,
 * return the end of the given range.
 * 
 * Also make sure, in case we're finding +/-, they must not be unary.
 */
Token_iter backward_find(const Token_iter& s, const Token_iter& e,
		const vector<Token_type>& tf) {

	using std::find;

	ull nesting = 0;	// are we inside (...)
	ull fnesting = 0;	// are we inside [...]

	for (auto i = e; i != s; ) {
		--i;	// don't put this anywhere in the for-loop
				// or it'll seek before s, resulting in an exception

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
		case Token_type::plus: case Token_type::minus:
			if (is_unary(i, s)) {
				continue;
			}
			break;
		}

		if (find(tf.begin(), tf.end(), i->type) != tf.end() && 
				!(nesting || fnesting)) {
			return i;
		}
	}

	return e;
}
