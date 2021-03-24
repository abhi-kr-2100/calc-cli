#pragma once
#ifndef CACL_CLI_EXCEPTIONS_HPP
#define CALC_CLI_EXCEPTIONS_HPP


#include <stdexcept>
#include <string>


class Calc_cli_exception : public std::exception {
public:
	Calc_cli_exception(const std::string& what="")
			:err{ what } {
	}

	virtual const char* what() const noexcept override {
		return err.c_str();
	}

private:
	std::string err;
};

class Unbalanced_parentheses : public Calc_cli_exception {
	using Calc_cli_exception::Calc_cli_exception;
};

class Unknown_token : public Calc_cli_exception {
	using Calc_cli_exception::Calc_cli_exception;
};

class Bad_literal : public Calc_cli_exception {
	using Calc_cli_exception::Calc_cli_exception;
};

class Unsupported_operand : public Calc_cli_exception {
	using Calc_cli_exception::Calc_cli_exception;
};

class Syntax_error : public Calc_cli_exception {
	using Calc_cli_exception::Calc_cli_exception;
};

class Redeclaration_of_variable : public Calc_cli_exception {
	using Calc_cli_exception::Calc_cli_exception;
};

class Variable_not_defined : public Calc_cli_exception {
	using Calc_cli_exception::Calc_cli_exception;
};



#endif // !CACL_CLI_EXCEPTIONS_HPP
