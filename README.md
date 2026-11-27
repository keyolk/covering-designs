# Covering design records

New upper bounds for two covering numbers C(v,k,t), found on 2026-11-27 by Chanhun Jeong.

A (v,k,t) covering design is a set of k-element blocks from {1,…,v} such that every
t-element subset of {1,…,v} is contained in at least one block. C(v,k,t) is the smallest
possible number of blocks. In lottery terms: C(28,10,4) is the fewest 10-number tickets
that guarantee every possible 4-number draw from 28 numbers is fully on some ticket.

| Covering | New bound | Previous best | Previous holder (date) | Lower bound | File |
|---|---|---|---|---|---|
| C(28,10,4) | **≤ 151** | 154 | Jan de Heer and Steve Muir (2008-10-01) | 110 | [`covers/C_28_10_4_151.txt`](covers/C_28_10_4_151.txt) |
| C(30,13,5) | **≤ 249** | 250 | Franco Atzeni (2025-04-22) | 157 | [`covers/C_30_13_5_249.txt`](covers/C_30_13_5_249.txt) |

Previous values and lower bounds are those listed by the
[Covering Repository](https://www.coveringrepository.com/systems.aspx), checked on
2026-11-27 09:10 UTC. (The La Jolla Covering Repository was frozen in March 2026 and its
data continues there.)

## Verify

Each file has one block per line, points numbered 1..v.

```sh
python3 verify.py 28 10 4 covers/C_28_10_4_151.txt   # prints VALID (20475/20475 4-subsets covered)
python3 verify.py 30 13 5 covers/C_30_13_5_249.txt   # prints VALID (142506/142506 5-subsets covered)
shasum -a 256 -c SHA256SUMS
```

`verify.py` needs only the Python standard library. Both covers were also checked with two
other independently written checkers, including `scripts/verify.py` from
[covering-design-records](https://github.com/WynandVStaden/covering-design-records).

## Method

Both covers were obtained by shrinking archived La Jolla records with **wls2**, the weighted
tabu local search by Wynand van Staden
([covering-design-records](https://github.com/WynandVStaden/covering-design-records), MIT),
run in shrink mode with several seeds:

- C(28,10,4): from the archived 154-block record to 153, then 151 (two seeds both reached 151; 300 s each).
- C(30,13,5): from the archived 250-block record to 249 (120 s).

The search was set up and run by AI agents (Claude) on a cloud workspace as part of an
experiment in agent-driven search for open records; every result was re-verified as above.

## Status

Not yet submitted to the Covering Repository, which accepts uploads only through its
Windows validator. This repository is the public, dated record of the results until then.

## License

Covering data: [CC0 1.0](https://creativecommons.org/publicdomain/zero/1.0/). `verify.py`: MIT (see `LICENSE`).
