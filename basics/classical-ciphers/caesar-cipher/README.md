# Caesar Cipher

The Caesar Cipher is the simplest of substitution ciphers: every letter in the plaintext is shifted by a fixed amount down the alphabet, it is monoalphabetic. Deciphering is simply done by performing the same shift but the other way down the alphabet. ROT13 is a special case where the shift amount is 13, meaning (because the basic alphabet has 26 letters) it is its own inverse.

## Features
- Input via a file or standard input
- Easy usage with Linux I/O redirection
- Non-alphabetic characters are handled and passed unchanged to output.

## Dependencies
- Utility library - `libscutils.so`
  This is automatically compiled when `make` is invoked.

## Usage
From the program's root directory, `make` compiles the `caesar` binary.

Run the program with `./caesar`. By default, the program is set to encrypt with a shift of `3` (e.g. `A` maps to `D`).

Help can be provided with `./caesar --help`.

```
Usage: ./caesar [-d|-e] [-s SHIFT] [FILE]
       ./caesar --rot13 [FILE]
       ./caesar --help

Caesar Cipher encrypt or decrypt FILE or standard input, to standard output.

With no FILE, read standard input.

Mandatory arguments to long options are mandatory for short options too.
Cipher:
  -d                       Set mode to decrypt
  -e                       Set mode to encrypt (default)
            --rot13        Use a shift of 13 - overrides cipher mode and SHIFT
  -s SHIFT, --shift=SHIFT  Specify cipher shift amount
                           [+] Default = 3

Miscellaneous:
            --help         Display this help message and exit

```