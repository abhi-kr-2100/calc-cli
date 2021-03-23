/**
 * calc-cli is a command-line calculator.
 * 
 * It supports the basic four functions, float modulus and float
 * factorial along with user-defined variables, and predefined
 * constants and functions.
 */


#include "calculator/calculator.hpp"
#include "utils.hpp"


int main() {
	auto consts = get_consts();
	auto funcs = get_funcs();

	Calculator calc{ consts, funcs };

	while (true) {
		run(calc);
	}
}
