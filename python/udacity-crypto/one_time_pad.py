import sys
from utility import *

SPACE = pad_bits(convert_to_bits(32), ASCII_BITS)

key = [None] * (len(C1) / ASCII_BITS)


def convert_to_bit_pack(bit_string, pack_len):
    """converts a string of bits to a list of bit arrays"""
    assert len(bit_string) % pack_len == 0
    result = []
    bits = seq_to_bits(bit_string)
    counter = 0
    while (len(result) < len(bit_string) / pack_len):
        result = result + [bits[counter: counter + pack_len]]
        counter += pack_len
    return result


def xor(a, b):
    """XOR two bit arrays"""
    assert len(a) == len(b)
    return [a[i] ^ b[i] for i in range(len(a))]


def xor_bit_packs(a, b):
    """XOR two bit packs"""
    assert len(a) == len(b)
    return [xor(a[i], b[i]) for i in range(len(a))]


def word_to_bit_pack(word):
    word_bits = string_to_bits(word)
    return convert_to_bit_pack(display_bits(word_bits), ASCII_BITS)


def look_for_word(C1, C2, word):
    word_bit_packs = word_to_bit_pack(word)
    A = convert_to_bit_pack(C1, ASCII_BITS)
    B = convert_to_bit_pack(C2, ASCII_BITS)
    for i in range(len(A) - len(word) + 1):
        result = []
        for j in range(len(word)):
            xored = xor(A[i + j], B[i + j])
            xored = xor(xored, word_bit_packs[j])
            result += xored
        print str(i) + ' ' + bits_to_string([x for x in result])


plaintext1 = "I visualize a time when we will be to robots what dogs are to humans, and I'm rooting for the machines.  (Claude Shannon)"
plaintext2 = "Anyone who considers arithmetical methods of producing random digits is, of course, in a state of sin. (John von Neumann)"