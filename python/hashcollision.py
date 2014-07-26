# HW2-5 Version 2
#
# In this assignment your job is to write a function, find_collision,
# that finds a hash collision for any given input message.
#
# The input message will be at least four blocks (64 characters) long.
#

from Crypto.Cipher import AES
from copy import copy
from utility import *

# Remember, this is NOT secure cryptology code
# This is for fun and education.  Do not use this
# to protect the classified files from Area 51


def find_collision(message):
    new_message = copy(message)
    #
    # START YOUR CODE HERE
    block_size, _, _, _ = hash_inputs()
    # blocks = []
    # for i in range(len(new_message) / block_size + 1):
    #     blocks = blocks + new_message[i * block_size: min(len(new_message), (i + 1) * block_size)]
    # temp = blocks[0]
    # blocks[0] = blocks[1]
    # blocks[1] = temp
    for i in range(block_size):
        temp = new_message[i]
        new_message[i] = new_message[i+block_size]
        new_message[i+block_size] = temp
    return new_message
    # END OF YOUR CODE
    #


def test():
    messages = [
        "Trust, but verify. -a signature phrase of President Ronald Reagan",
        "The best way to find out if you can trust somebody is to trust them. (Ernest Hemingway)",
        "If you reveal your secrets to the wind, you should not blame the wind for revealing them to the trees. (Khalil Gibran)",
        "I am not very good at keeping secrets at all! If you want your secret kept do not tell me! (Miley Cyrus)",
        "This message is exactly sixty four characters long and no longer"]
    for m in messages:
        mess = m
        m = string_to_bits(m)
        new_message = find_collision(m)
        if not check(m, new_message):
            print "Failed to find a collision for '%s'" % mess
            return False
    return True

from Crypto.Cipher import AES


def xor_bits(bits_a, bits_b):
    """returns a new bit array that is the xor of `bits_a` and `bits_b`"""
    return [a ^ b for a, b in zip(bits_a, bits_b)]


def bits_inc(bits):
    """modifies `bits` array in place to increment by one

    wraps back to zero if `bits` is at its maximum value (each bit is 1)
    """
    # start at the least significant bit and work towards
    # the most significant bit
    for i in range(len(bits) - 1, -1, -1):
        if bits[i] == 0:
            bits[i] = 1
            break
        else:
            bits[i] = 0


def aes_encoder(block, key):
    block = pad_bits_append(block, len(key))
    # the pycrypto library expects the key and block in 8 bit ascii
    # encoded strings so we have to convert from the bit array
    block = bits_to_string(block)
    key = bits_to_string(key)
    ecb = AES.new(key, AES.MODE_ECB)
    return string_to_bits(ecb.encrypt(block))


def get_block(plaintext, i, block_size):
    """returns the ith block of `plaintext`"""
    start = i * block_size
    if start >= len(plaintext):
        return None
    end = min(len(plaintext), (i + 1) * block_size)
    return pad_bits_append(plaintext[start:end], block_size)


def get_blocks(plaintext, block_size):
    """iterates through the blocks of blocksize"""
    i = 0
    while True:
        start = i * block_size
        if start >= len(plaintext):
            break
        end = (i + 1) * block_size
        i += 1
        yield pad_bits_append(plaintext[start:end], block_size)


def _counter_mode_inner(plaintext, key, ctr, block_enc):
    eblock = block_enc(ctr, key)
    cblock = xor_bits(eblock, plaintext)
    bits_inc(ctr)
    return cblock


def counter_mode(plaintext, key, ctr, block_size, block_enc):
    """Return the counter mode encoding of `plaintext"""
    cipher = []
    # break the plaintext into blocks
    # and encode each one
    for block in get_blocks(plaintext, block_size):
        cblock = _counter_mode_inner(block, key, ctr, block_enc)
        cipher.extend(cblock)
    return cipher


def counter_mode_hash(plaintext):
    block_size, block_enc, key, ctr = hash_inputs()
    hash_ = None
    for block in get_blocks(plaintext, block_size):
        cblock = _counter_mode_inner(block, key, ctr, block_enc)
        if hash_ is None:
            hash_ = cblock
        else:
            hash_ = xor_bits(hash_, cblock)
    return hash_


def hash_inputs():
    block_size = 128
    block_enc = aes_encoder
    key = string_to_bits("Vs7mHNk8e39%CXeY")
    ctr = [0] * block_size
    return block_size, block_enc, key, ctr


def _is_same(bits_a, bits_b):
    if len(bits_a) != len(bits_b):
        return False
    for a, b in zip(bits_a, bits_b):
        if a != b:
            return False
    return True


def check(message_a, message_b):
    """return True if `message_a` and `message_b` are
    different but hash to the same value"""

    if _is_same(message_a, message_b):
        print "issame"
        return False

    hash_a = counter_mode_hash(message_a)
    hash_b = counter_mode_hash(message_b)

    return _is_same(hash_a, hash_b)

test()
