# calc-cli

`calc-cli` is a powerful command-line calculator. It supports the basic four arithmetic operations, exponentiation, float mod, and float factorial (the gamma function).

Results can be stored in user-defined variables. Pre-defined constants for popular mathematical constants are available as well. Additionally, to support quick calculations, a dynamic variable, `_` (underscore) is provided which stores the result of the most recent successful calculation.

Pre-defined functions are a planned feature.

## Usage

Upon running `calc-cli.exe`, the user will be presented with a console window with a prompt at which expressions can be typed. An example is shown below:

```
> 1 + 2
= 3
> (2 / 3) * (4 + 1)
= 3.33333
```

Exponentiation is supported through the `^` operator. One or both operands may be fractional:

```
> 2 ^ 2
= 4
> 2 ^ 2 ^ 3
= 64
> 2 ^ (2 ^ 3)
= 256
> -2 ^ 2
= -4
> (-2) ^ 2
= 4
> 2 ^ 0.5
= 1.41421
```

The following constants are provided:
- pi
- e
- phi

```
> e^2 + phi^2 - pi^2
= 0.13748
```

Users can define their own variables (although a defined variable can't be changed; hence a variable in `calc-cli` is really a constant):

```
> let x = 3
= 3
> x ^ x
= 27
```

The only changing variable in `calc-cli` is `_` (the underscore). It stores the result of the last successful calculation:

```
> let sum = 3 + 2 + 1 + 5
= 11
> let average = _ / 4
= 2.75
> _ * 4
= 11
```

To quit, simply type `quit` and press enter. To clear the screen, type `clear` followed by the enter key.