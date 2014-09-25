from utility import *
from one_time_pad import *

key = [None] * (len(C1) / ASCII_BITS)

A = convert_to_bit_pack(C1, ASCII_BITS)
B = convert_to_bit_pack(C2, ASCII_BITS)


def find_key(word, pos):
    key[pos:pos + len(word)] = xor_bit_packs(
        word_to_bit_pack(word), A[pos:pos + len(word)])

find_key('the', 44)
find_key(', and ', 68)
find_key('in a state of sin.', 83)
find_key('and', 102)
find_key('.', 119)


def write_deciphered():
    M1 = [[0,0,1,1,1,1,1]]* len(A)
    M2 = [[0,0,1,1,1,1,1]] * len(B)
    for i in range(len(key)):
        if key[i] != None:
            M1[i] = xor(A[i], key[i])
            M2[i] = xor(B[i], key[i])
    print bits_to_string([x for y in M1 for x in y])
    print bits_to_string([x for y in M2 for x in y])
