# Covering design records

New upper bounds for 26 covering numbers C(v,k,t), found on 2026-11-27 and 2026-11-28 by Chanhun Jeong.

A (v,k,t) covering design is a set of k-element blocks from {1,…,v} such that every
t-element subset of {1,…,v} is contained in at least one block. C(v,k,t) is the smallest
possible number of blocks. In lottery terms: C(28,10,4) is the fewest 10-number tickets
that guarantee every possible 4-number draw from 28 numbers is fully on some ticket.

| Covering | New bound | Previous best | File |
|---|---|---|---|
| C(55,8,3) | **≤ 571** | 572 | [`covers/C_55_8_3_571.txt`](covers/C_55_8_3_571.txt) |
| C(61,12,3) | **≤ 215** | 216 | [`covers/C_61_12_3_215.txt`](covers/C_61_12_3_215.txt) |
| C(79,15,3) | **≤ 236** | 238 | [`covers/C_79_15_3_236.txt`](covers/C_79_15_3_236.txt) |
| C(28,10,4) | **≤ 150** | 154 | [`covers/C_28_10_4_150.txt`](covers/C_28_10_4_150.txt) |
| C(36,16,4) | **≤ 60** | 62 | [`covers/C_36_16_4_60.txt`](covers/C_36_16_4_60.txt) |
| C(37,9,4) | **≤ 726** | 738 | [`covers/C_37_9_4_726.txt`](covers/C_37_9_4_726.txt) |
| C(54,23,4) | **≤ 71** | 72 | [`covers/C_54_23_4_71.txt`](covers/C_54_23_4_71.txt) |
| C(89,18,4) | **≤ 1668** | 1672 | [`covers/C_89_18_4_1668.txt`](covers/C_89_18_4_1668.txt) |
| C(23,11,5) | **≤ 128** | 131 | [`covers/C_23_11_5_128.txt`](covers/C_23_11_5_128.txt) |
| C(27,9,5) | **≤ 951** | 957 | [`covers/C_27_9_5_951.txt`](covers/C_27_9_5_951.txt) |
| C(30,13,5) | **≤ 247** | 250 | [`covers/C_30_13_5_247.txt`](covers/C_30_13_5_247.txt) |
| C(31,14,5) | **≤ 185** | 186 | [`covers/C_31_14_5_185.txt`](covers/C_31_14_5_185.txt) |
| C(54,18,5) | **≤ 951** | 957 | [`covers/C_54_18_5_951.txt`](covers/C_54_18_5_951.txt) |
| C(72,25,5) | **≤ 756** | 757 | [`covers/C_72_25_5_756.txt`](covers/C_72_25_5_756.txt) |
| C(73,25,5) | **≤ 758** | 759 | [`covers/C_73_25_5_758.txt`](covers/C_73_25_5_758.txt) |
| C(81,23,5) | **≤ 2347** | 2349 | [`covers/C_81_23_5_2347.txt`](covers/C_81_23_5_2347.txt) |
| C(82,23,5) | **≤ 2375** | 2386 | [`covers/C_82_23_5_2375.txt`](covers/C_82_23_5_2375.txt) |
| C(83,23,5) | **≤ 2410** | 2420 | [`covers/C_83_23_5_2410.txt`](covers/C_83_23_5_2410.txt) |
| C(94,24,5) | **≤ 2509** | 2510 | [`covers/C_94_24_5_2509.txt`](covers/C_94_24_5_2509.txt) |
| C(19,10,6) | **≤ 229** | 230 | [`covers/C_19_10_6_229.txt`](covers/C_19_10_6_229.txt) |
| C(22,14,7) | **≤ 128** | 129 | [`covers/C_22_14_7_128.txt`](covers/C_22_14_7_128.txt) |
| C(25,14,7) | **≤ 373** | 377 | [`covers/C_25_14_7_373.txt`](covers/C_25_14_7_373.txt) |
| C(23,15,8) | **≤ 198** | 202 | [`covers/C_23_15_8_198.txt`](covers/C_23_15_8_198.txt) |
| C(36,25,8) | **≤ 127** | 128 | [`covers/C_36_25_8_127.txt`](covers/C_36_25_8_127.txt) |
| C(41,24,8) | **≤ 612** | 613 | [`covers/C_41_24_8_612.txt`](covers/C_41_24_8_612.txt) |
| C(42,24,8) | **≤ 732** | 738 | [`covers/C_42_24_8_732.txt`](covers/C_42_24_8_732.txt) |

"Previous best" is the value in the current (v,k,t) table of the
[Covering Repository](https://www.coveringrepository.com/systems.aspx), downloaded on
2026-11-28 05:05 UTC. The repository lists the holder, date and lower bound of each record.
(The La Jolla Covering Repository was frozen in March 2026 and its data continues there.)

## Verify

Each file has one block per line, points numbered 1..v.

```sh
cc -O2 -o verify verify.c
for f in covers/*.txt; do set -- $(basename "$f" .txt | tr _ ' '); ./verify $2 $3 $4 "$f"; done
shasum -a 256 -c SHA256SUMS
```

`verify.c` keeps one bit per t-subset and checks all 26 files in a few seconds (the largest,
C(42,24,8), has 118,030,185 8-subsets). `verify.py` applies the same rules with only the Python
standard library, for example `python3 verify.py 28 10 4 covers/C_28_10_4_150.txt`, but it keeps
every covered t-subset in memory and needs many GB for the large cases.

Every cover was also checked by the search with two other independently written checkers,
including `scripts/verify.py` from
[covering-design-records](https://github.com/WynandVStaden/covering-design-records).

## Method

All covers were obtained by shrinking existing covers with **wls2**, the weighted tabu local
search by Wynand van Staden
([covering-design-records](https://github.com/WynandVStaden/covering-design-records), MIT),
in shrink mode with several seeds, usually 120–540 s per run. The starting covers were the
archived La Jolla records or earlier results of this search.

Earlier versions of this repository listed C(28,10,4) ≤ 151 and C(30,13,5) ≤ 249
(commit 7136f1c) and C(36,16,4) ≤ 61 (commit ec45e6c); they are superseded by the values above.

The search was set up and run by AI agents (Claude) on a cloud workspace as part of an
experiment in agent-driven search for open records; every result was re-verified as above.

## Status

Not yet submitted to the Covering Repository, which accepts uploads only through its
Windows validator. This repository is the public, dated record of the results until then.

## License

Covering data: [CC0 1.0](https://creativecommons.org/publicdomain/zero/1.0/). `verify.py` and `verify.c`: MIT (see `LICENSE`).
