/*
 * Fast checker for covering designs: verify.c
 * Usage: cc -O2 -o verify verify.c && ./verify v k t FILE
 *
 * Same rules as verify.py: one block per line, k distinct points in 1..v,
 * no duplicate blocks, every t-subset of {1..v} inside some block.
 * verify.py keeps every covered t-subset in a Python set, which needs many GB
 * for the large cases (e.g. C(94,24,5) has 55M 5-subsets). This keeps one bit
 * per t-subset, indexed by its colex rank, so the largest case here needs
 * under 10 MB and runs in seconds to minutes.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static uint64_t binom[129][33];

static int cmp_int(const void *a, const void *b) {
    return *(const int *)a - *(const int *)b;
}

int main(int argc, char **argv) {
    if (argc != 5) {
        fprintf(stderr, "usage: %s v k t FILE\n", argv[0]);
        return 2;
    }
    int v = atoi(argv[1]), k = atoi(argv[2]), t = atoi(argv[3]);
    if (v < 1 || v > 128 || k < 1 || k > 32 || t < 1 || t > k || k > v) {
        fprintf(stderr, "unsupported parameters (need 1<=t<=k<=32, k<=v<=128)\n");
        return 2;
    }
    for (int n = 0; n <= 128; n++) {
        binom[n][0] = 1;
        for (int r = 1; r <= 32; r++)
            binom[n][r] = n == 0 ? 0 : binom[n - 1][r - 1] + binom[n - 1][r];
    }
    uint64_t total = binom[v][t];
    uint8_t *seen = calloc((total + 7) / 8, 1);
    FILE *f = fopen(argv[4], "r");
    if (!seen || !f) {
        perror("setup");
        return 2;
    }

    size_t cap = 1024, nb = 0;
    int *blocks = malloc(cap * k * sizeof(int));
    char line[4096];
    while (fgets(line, sizeof line, f)) {
        int b[64], n = 0;
        char *p = line, *end;
        for (;;) {
            long x = strtol(p, &end, 10);
            if (end == p) break;
            if (n == 64) { fprintf(stderr, "INVALID: line too long\n"); return 1; }
            b[n++] = (int)x;
            p = end;
        }
        if (n == 0) continue;
        if (n != k) { printf("INVALID: block %zu has %d points, expected %d\n", nb + 1, n, k); return 1; }
        qsort(b, k, sizeof(int), cmp_int);
        for (int i = 0; i < k; i++) {
            if (b[i] < 1 || b[i] > v) { printf("INVALID: block %zu has point %d outside 1..%d\n", nb + 1, b[i], v); return 1; }
            if (i && b[i] == b[i - 1]) { printf("INVALID: block %zu repeats point %d\n", nb + 1, b[i]); return 1; }
        }
        if (nb == cap) { cap *= 2; blocks = realloc(blocks, cap * k * sizeof(int)); }
        memcpy(blocks + nb * k, b, k * sizeof(int));
        nb++;
    }
    fclose(f);

    /* duplicate blocks: pairwise compare (at most a few thousand blocks here) */
    for (size_t i = 0; i < nb; i++)
        for (size_t j = i + 1; j < nb; j++)
            if (memcmp(blocks + i * k, blocks + j * k, k * sizeof(int)) == 0) {
                printf("INVALID: blocks %zu and %zu are equal\n", i + 1, j + 1);
                return 1;
            }

    /* enumerate the t-subsets of each block; colex rank = sum binom[x_i - 1][i + 1] */
    int idx[32];
    for (size_t bi = 0; bi < nb; bi++) {
        const int *b = blocks + bi * k;
        for (int i = 0; i < t; i++) idx[i] = i;
        for (;;) {
            uint64_t r = 0;
            for (int i = 0; i < t; i++) r += binom[b[idx[i]] - 1][i + 1];
            seen[r >> 3] |= (uint8_t)(1u << (r & 7));
            int i = t - 1;
            while (i >= 0 && idx[i] == k - t + i) i--;
            if (i < 0) break;
            idx[i]++;
            for (int j = i + 1; j < t; j++) idx[j] = idx[j - 1] + 1;
        }
    }

    uint64_t covered = 0;
    for (uint64_t r = 0; r < total; r++) covered += (seen[r >> 3] >> (r & 7)) & 1;
    printf("C(%d,%d,%d): %zu blocks, %llu/%llu %d-subsets covered\n", v, k, t, nb,
           (unsigned long long)covered, (unsigned long long)total, t);
    puts(covered == total ? "VALID" : "INVALID");
    return covered == total ? 0 : 1;
}
