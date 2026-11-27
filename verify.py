#!/usr/bin/env python3
"""Check a (v,k,t) covering design: every t-subset of {1..v} lies in at least one block.

Usage: python3 verify.py v k t FILE   (one block per line, points 1..v, space separated)
"""
import sys
from itertools import combinations
from math import comb


def main():
    if len(sys.argv) != 5:
        sys.exit(__doc__)
    v, k, t = map(int, sys.argv[1:4])
    blocks = [tuple(sorted(map(int, line.split()))) for line in open(sys.argv[4]) if line.strip()]
    errors = []
    for i, b in enumerate(blocks, 1):
        if len(b) != k or len(set(b)) != k:
            errors.append(f"block {i} does not have {k} distinct points: {b}")
        if b and (b[0] < 1 or b[-1] > v):
            errors.append(f"block {i} has a point outside 1..{v}: {b}")
    if len(set(blocks)) != len(blocks):
        errors.append("duplicate blocks")
    covered = set()
    for b in blocks:
        covered.update(combinations(b, t))
    need = comb(v, t)
    print(f"C({v},{k},{t}): {len(blocks)} blocks, {len(covered)}/{need} {t}-subsets covered")
    if errors or len(covered) != need:
        for e in errors[:10]:
            print("ERROR:", e)
        print("INVALID")
        sys.exit(1)
    print("VALID")


if __name__ == "__main__":
    main()
