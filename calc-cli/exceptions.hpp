#pragma once
#ifndef CACL_CLI_EXCEPTIONS_HPP
#define CALC_CLI_EXCEPTIONS_HPP


#include <stdexcept>


class Calc_cli_exception : std::exception {};
class Unbalanced_parentheses : Calc_cli_exception {};
class Unknown_token : Calc_cli_exception {};
class Bad_literal : Calc_cli_exception {};
class Divide_by_zero : Calc_cli_exception {};
class Unsupported_operand : Calc_cli_exception {};


#endif // !CACL_CLI_EXCEPTIONS_HPP
