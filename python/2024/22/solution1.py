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


def main(secrets, steps=2000):
    total = 0
    for secret in secrets:
        for _ in range(2000):
            secret = pseudorandom(secret)
        total += secret
    return total


if __name__ == "__main__":
    # my unit tests :)
    assert mix(42, 15) == 37
    assert prune(100000000) == 16113920
    assert pseudorandom(123) == 15887950
    assert pseudorandom(15887950) == 16495136
    assert pseudorandom(16495136) == 527345
    if len(sys.argv) < 2:
        print("Usage: solution1.py <file>")
        sys.exit(0)
    file_path = sys.argv[1]
    secrets = []
    with open(file_path, "r") as fin:
        for line in fin:
            secrets.append(int(line.strip()))
    print(main(secrets))
