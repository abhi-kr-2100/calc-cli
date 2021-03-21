/**
 * calc-cli is a command-line calculator.
 *
 * calculator.cpp defines the grammar functions used by the
 * Calculator class.
 * 
 * Calculator uses the following grammar:
 *
 * <statement>	:= <expression>
 * <expression> := <expression> "+" <term> | <expression> "-" <term> | <term>
 * <term>		:= <term> "*" <unary> | <term> "/" <unary> | <term> "%" <unary> | <unary>
 * <unary>		:= "+" <primary> | "-" <primary> | <primary>
 * <primary>	:= "(" <expression> ")" | <primary> "!" | <number>
 * <number>		:= "_" | a floating-point literal as used in C++ without unary + or -
 */


#include <cmath>

#include "calculator.hpp"
#include "token.hpp"
#include "exceptions.hpp"


using std::fmod;

using ull = unsigned long long;


bool is_operator(Token_type t);
double factorial(ull n);


double Calculator::statement(const Token_iter& s,
		const Token_iter& e) {
	auto result = expression(s, e);
	prev = result;
	return result;
}


double Calculator::expression(const Token_iter& s,
		const Token_iter& e) {
	// look for a "+" or "-" from the end that doesn't occur inside
	// parentheses
	ull nesting = 0;	// inside a "(" ... ")"? How deep?
	for (auto i = e; i != s; ) {
		--i;	// because we already start at one past the end
				// don't put it in the condition as a postfix
				// as it musn't be executed if the condition is false
				// to begin with

		switch (i->type) {
		case Token_type::p_close:
			++nesting;
			break;
		case Token_type::p_open:
			--nesting;
			break;
		case Token_type::plus:
			if (!nesting) {
				// check that this plus is not a unary plus
				if (!(i == s || is_operator((i - 1)->type))) {
					return expression(s, i) + term(i + 1, e);
				}
			}
			break;
		case Token_type::minus:
			if (!nesting) {
				// check that this minus is not a unary minus
				if (!(i == s || is_operator((i - 1)->type))) {
					return expression(s, i) - term(i + 1, e);
				}
			}
			break;
		}
	}	// search for <expression> "+" <term> or
		// <expression> "-" <term> fails

	if (nesting) {
		throw Unbalanced_parentheses{};
	}

	return term(s, e);
}


double Calculator::term(const Token_iter& s, const Token_iter& e) {
	// look for a "*" or "/" from the end that doesn't occur inside
	// parentheses
	ull nesting = 0;	// inside a "(" ... ")"? How deep?
	for (auto i = e; i != s; ) {
		--i;	// as i starts out pointing past the end

		switch (i->type) {
		case Token_type::p_close:
			++nesting;
			break;
		case Token_type::p_open:
			--nesting;
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
					throw Divide_by_zero{};
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

	if (nesting) {
		throw Unbalanced_parentheses{};
	}

	return unary(s, e);
}


double Calculator::unary(const Token_iter& s, const Token_iter& e) {
	switch (s->type) {
	case Token_type::plus:
		return +primary(s + 1, e);
	case Token_type::minus:
		return -primary(s + 1, e);
	default:
		return primary(s, e);
	}
}


double Calculator::primary(const Token_iter& s, const Token_iter& e) {
	if ((e - 1)->type == Token_type::factorial) {
		double n = primary(s, e - 1);
		if (ull(n) != n) {
			throw Unsupported_operand{};
		}
		return factorial(ull(n));
	}

	switch (s->type) {
	case Token_type::number:
		return s->value;
	case Token_type::p_open:
		if ((e - 1)->type != Token_type::p_close) {
			throw Unbalanced_parentheses{};
		}
		return expression(s + 1, e - 1);
	case Token_type::previous:
		return prev;
	default:
		throw Unknown_token{};
	}
}


/**
 * Is the Token referred to by i an operator?
 */
bool is_operator(Token_type t) {
	return t == Token_type::plus || t == Token_type::minus ||
		t == Token_type::multiply || t == Token_type::divide;
}


double factorial(ull n) {
	double r = 1;
	for (ull i = 1; i <= n; ++i) {
		r *= i;
	}

	return r;
}