# Covering design records

New upper bounds for seven covering numbers C(v,k,t), found on 2026-11-27 by Chanhun Jeong.

A (v,k,t) covering design is a set of k-element blocks from {1,…,v} such that every
t-element subset of {1,…,v} is contained in at least one block. C(v,k,t) is the smallest
possible number of blocks. In lottery terms: C(28,10,4) is the fewest 10-number tickets
that guarantee every possible 4-number draw from 28 numbers is fully on some ticket.

| Covering | New bound | Previous best | Previous holder (date) | Lower bound | File |
|---|---|---|---|---|---|
| C(23,11,5) | **≤ 128** | 131 | Jan de Heer and Steve Muir (2005-07-25) | 99 | [`covers/C_23_11_5_128.txt`](covers/C_23_11_5_128.txt) |
| C(28,10,4) | **≤ 150** | 154 | Jan de Heer and Steve Muir (2008-10-01) | 110 | [`covers/C_28_10_4_150.txt`](covers/C_28_10_4_150.txt) |
| C(30,13,5) | **≤ 249** | 250 | Franco Atzeni (2025-04-22) | 157 | [`covers/C_30_13_5_249.txt`](covers/C_30_13_5_249.txt) |
| C(31,14,5) | **≤ 185** | 186 | Franco Atzeni (2026-11-23) | 129 | [`covers/C_31_14_5_185.txt`](covers/C_31_14_5_185.txt) |
| C(55,8,3) | **≤ 571** | 572 | Sarg (2026-11-24) | 482 | [`covers/C_55_8_3_571.txt`](covers/C_55_8_3_571.txt) |
| C(36,16,4) | **≤ 61** | 62 | Jan de Heer and Steve Muir (2008-12-30) | 48 | [`covers/C_36_16_4_61.txt`](covers/C_36_16_4_61.txt) |
| C(79,15,3) | **≤ 236** | 238 | Terenzio Lazzarotto (2026-04-09) | 201 | [`covers/C_79_15_3_236.txt`](covers/C_79_15_3_236.txt) |

Previous values and lower bounds are those listed by the
[Covering Repository](https://www.coveringrepository.com/systems.aspx), checked on
2026-11-27 (09:10, 10:10, 11:05 and 11:55 UTC). (The La Jolla Covering Repository was frozen in March 2026 and its
data continues there.)

## Verify

Each file has one block per line, points numbered 1..v.

```sh
python3 verify.py 23 11 5 covers/C_23_11_5_128.txt   # prints VALID (33649/33649 5-subsets covered)
python3 verify.py 28 10 4 covers/C_28_10_4_150.txt   # prints VALID (20475/20475 4-subsets covered)
python3 verify.py 30 13 5 covers/C_30_13_5_249.txt   # prints VALID (142506/142506 5-subsets covered)
python3 verify.py 31 14 5 covers/C_31_14_5_185.txt   # prints VALID (169911/169911 5-subsets covered)
python3 verify.py 36 16 4 covers/C_36_16_4_61.txt    # prints VALID (58905/58905 4-subsets covered)
python3 verify.py 79 15 3 covers/C_79_15_3_236.txt   # prints VALID (79079/79079 3-subsets covered)
python3 verify.py 55 8 3 covers/C_55_8_3_571.txt     # prints VALID (26235/26235 3-subsets covered)
shasum -a 256 -c SHA256SUMS
```

`verify.py` needs only the Python standard library. All covers were also checked with two
other independently written checkers, including `scripts/verify.py` from
[covering-design-records](https://github.com/WynandVStaden/covering-design-records).

## Method

All covers were obtained by shrinking archived La Jolla records with **wls2**, the weighted
tabu local search by Wynand van Staden
([covering-design-records](https://github.com/WynandVStaden/covering-design-records), MIT),
run in shrink mode with several seeds:

- C(23,11,5): from the archived 131-block record to 130, then 128 (a further 330 s run).
- C(28,10,4): from the archived 154-block record to 153, 151 (two seeds, 300 s each), then 150 (three seeds, 540 s each, all reached 150).
- C(30,13,5): from the archived 250-block record to 249 (120 s).
- C(31,14,5): from the archived 189-block record to 185 (120 s).
- C(36,16,4): from the archived 62-block record to 61 (120 s).
- C(79,15,3): from the archived 239-block record to 238, then 236 (a further 330 s run).
- C(55,8,3): from the archived 573-block record to 571 (120 s).

An earlier version of this repository (commit 7136f1c) listed C(28,10,4) ≤ 151; it is superseded by 150.

The search was set up and run by AI agents (Claude) on a cloud workspace as part of an
experiment in agent-driven search for open records; every result was re-verified as above.

## Status

Not yet submitted to the Covering Repository, which accepts uploads only through its
Windows validator. This repository is the public, dated record of the results until then.

## License

Covering data: [CC0 1.0](https://creativecommons.org/publicdomain/zero/1.0/). `verify.py`: MIT (see `LICENSE`).
