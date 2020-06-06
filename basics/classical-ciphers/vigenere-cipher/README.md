# Vigenère Cipher

The Vigenère Cipher is a keyed polyaphabetic substitution cipher that operates with shifts up the alphabet, similar to the Caesar Cipher. A letter of the plaintext is shifted according to the letter at the same position in the key (which is repeated where necessary to be the same length as the plaintext.) The shift amount is the position of key letter in the alphabet, so letters `A`, `B`, `C` will, respectively, shift plaintext characters `0`, `1`, and `2` places. Deciphering is the same process, except the shifts are made down the alphabet, not up.

## Features
- Input via a file or standard input
- Easy usage with Linux I/O redirection
- Non-alphabetic characters are handled and passed unchanged to output.

## Dependencies
- Utility library - `libscutils.so`
  This is automatically compiled when `make` is invoked.

## Usage
From the program's root directory, `make` compiles the `vigenere` binary.

Run the program with `./vigenere KEY`, where `KEY` is the alphabetic encryption key.

Help can be provided with `./vigenere --help`.

```
Usage: ./vigenere [-d|-e] [KEY] [FILE]
       ./vigenere --help

Vigenere Cipher encrypt or decrypt FILE or standard input with KEY, to standard output.

With no FILE, read standard input.

Mandatory arguments to long options are mandatory for short options too.
Cipher:
  -d          Set mode to decrypt
  -e          Set mode to encrypt (default)
Miscellaneous:
      --help  Display this help message and exit

```