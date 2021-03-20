/**
 * calc-cli is a command-line calculator.
 *
 * grammar.cpp defines the functions that parse input expressions
 * according to the following grammar:
 * 
 * <expression> := <expression> "+" <term> | <expression> "-" <term> | <term>
 * <term>		:= <term> "*" <primary> | <term> "/" <primary> | <primary>
 * <primary>	:= <number> | "(" <expression> ")"
 * <number>		:= a floating-point literal as used in C++
 */


#include "grammar.hpp"
#include "token.hpp"
#include "exceptions.hpp"

#include <iostream>


using ull = unsigned long long;


double expression(const Token_iter& s, const Token_iter& e) {
	// look for a "+" or "-" from the end that doesn't occur inside
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
		case Token_type::plus:
			if (!nesting) {
				return expression(s, i) + term(i + 1, e);
			}
			break;
		case Token_type::minus:
			if (!nesting) {
				return expression(s, i) - term(i + 1, e);
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


double term(const Token_iter& s, const Token_iter& e) {
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
				return term(s, i) * primary(i + 1, e);
			}
			break;
		case Token_type::divide:
			if (!nesting) {
				double p = primary(i + 1, e);
				if (p == 0) {
					throw Divide_by_zero{};
				}
				return term(s, i) / p;
			}
			break;
		}
	}	// search for <term> "*" <primary> or
		// <term> "/" <primary> fails

	if (nesting) {
		throw Unbalanced_parentheses{};
	}

	return primary(s, e);
}


double primary(const Token_iter& s, const Token_iter& e) {
	switch (s->type) {
	case Token_type::number:
		return s->value;
	case Token_type::p_open:
		if ((e - 1)->type != Token_type::p_close) {
			throw Unbalanced_parentheses{};
		}
		return expression(s + 1, e - 1);
	default:
		throw Unknown_token{};
	}
}