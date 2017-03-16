A library of arbitrarily large integers
=======================================

As you know, C provides fixed-size integers.  You can use a variety
of sizes (e.g., `short`, `int`, `long`), but you don't necessarily
know how big those sizes are.  There are usually some associated
libraries that let you choose the sizes of your integers (e.g.,
`int8`, `int16`, `int32`, `int64`), but those are still fixed size.
C's `double` and `long double` type provide a wider range of values,
but sacrifice accuracy.

In contrast, some other languages, like Scheme, provide arbitrarily
large integers.  Why?  Because programmers can't always predict
what size they will need.  (There is an apocraphal story of a Scheme
program for automated trading doing really well on a day that the
market changed significantly because it was the only one that
adjusted on the fly.)

This library provides ...

