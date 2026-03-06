#!/usr/bin/env -S uv run --script
# /// script
# requires-python = ">=3.8"
# ///

import sys


def mix(secret, value):
    return secret ^ value


def prune(secret):
    return secret % 16777216


def pseudorandom(secret):
    secret = prune(mix(secret, secret * 64))
    secret = prune(mix(secret, int(secret / 32)))
    return prune(mix(secret, secret * 2048))


def get_price(number):
    return number % 10


def main(secrets, steps=2000):
    # construct hash table "bananas"
    # key: sequence of diffs -> value: total bananas gained
    bananas = {}
    for secret in secrets:
        diffs = []
        diffs_found = set()  # to keep track of first occurrence only
        price = get_price(secret)
        for _ in range(2000):
            secret = pseudorandom(secret)
            new_price = get_price(secret)
            diffs.append(price - new_price)
            price = new_price
            if len(diffs) > 3:
                sequence = tuple(diffs[-4:])
                if sequence in diffs_found:
                    continue
                diffs_found.add(sequence)
                if sequence in bananas:
                    bananas[sequence] += price
                else:
                    bananas[sequence] = price
    max_bananas = 0
    for seq, total in bananas.items():
        if total > max_bananas:
            max_bananas = total
    return max_bananas


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: solution2.py <file>")
        sys.exit(0)
    file_path = sys.argv[1]
    secrets = []
    with open(file_path, "r") as fin:
        for line in fin:
            secrets.append(int(line.strip()))
    print(main(secrets))
