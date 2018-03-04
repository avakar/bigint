# Compile-time arbitrary-precision integers

Here we encode arbitrary integers into types by representing
them with a template pack of digits of an integer type `D`.
The range of `D` determines the integer's numeric base.

For example, given digits of type `uint8_t`, the following type
represents the value 

We can represent an arbitrary non-negative integer using
a sequence of digits, where each digit is an integer in range $[0, b)$.