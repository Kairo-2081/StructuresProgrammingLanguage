# Structured Programming Language (CSE 102)

C programs from my first-year Structured Programming course at BUET. Each folder is one offline assignment, from loops and conditionals up to pointers with dynamic memory, and holds the assignment PDF next to the solution.

## Contents

- [Assignments](#assignments)
- [Loops and conditionals](#loops-and-conditionals)
- [Arrays](#arrays)
- [Strings](#strings)
- [Pointers](#pointers)
- [Build and run](#build-and-run)
- [Repository layout](#repository-layout)
- [Notes](#notes)

## Assignments

| Topic | Folder | Program | What it does |
| --- | --- | --- | --- |
| Loops and conditionals | `Loops/` | `offline 01.c` | Scores rows of numbers on four rules and prints an activity level per row |
| Arrays | `Arrays/` | `2405010/offline 2.c` | Command-driven statistics and histogram tool for a generated array |
| Strings | `Strings/` | `2405010.c` | Command-driven text pipeline that computes TF, IDF and TF-IDF |
| Pointers | `Pointers/` | `2405010-1.c`, `2405010-2.c` | Filter negatives and sort words, both with pointer arithmetic only |

## Loops and conditionals

`Loops/offline 01/offline 01.c` models an "energy machine" with `n` rows of numbers. For each row it checks four rules on the row's values:

| Rule | Condition | Energy |
| --- | --- | --- |
| Prime-active | the row sum is prime | +5 |
| Palindrome-active | the row sum reads the same backwards | +3 |
| Harmonic | the alternating sum (first - second + third ...) is divisible by 7 | +4 |
| Balanced | the odd-position sum equals the even-position sum | +2 |

A row is `ULTRA` when it meets all four rules, `HIGH` for three, `MEDIUM` for two, `LOW` for one and `INACTIVE` for none. The program ends with the total energy.

Input is `n`, then one line per row that starts with the row length `k` followed by `k` integers. Example:

```text
3
3 1 2 4
4 3 5 3 5
2 7 7
```

```text
Row 1: MEDIUM - Energy level 8
Row 2: INACTIVE - Energy level 0
Row 3: MEDIUM - Energy level 6
Total Energy: 14
```

## Arrays

`Arrays/2405010/offline 2.c` is an interactive statistics tool. It fills an array of up to 100,000 doubles with random values from a seed, then answers commands. The random generators (`populate_array_uniform`, `populate_array_gaussian`) come from the supplied `utils.c`.

| Command | Action |
| --- | --- |
| `set` | Ask for the size, the seed and the distribution (`uniform` or `gaussian`), then fill the array |
| `min`, `max`, `mean`, `stddev`, `median` | Print one statistic |
| `summary` | Print min, max, mean and standard deviation |
| `hist` | Ask for a bin count and draw a histogram of `*` characters, scaled to at most 50 stars per bin |
| `help`, `exit` | Show the command list, or quit |

Every command except `set`, `help` and `exit` first checks that the array has been initialised. The median sorts the data with `qsort`.

The assignment folder `Arrays/offline2/` has the starter `utils.c` and two sample sessions (`sampleio1.txt`, `sampleio2.txt`) to compare against. The numbers differ from the samples, because they depend on the random generator and the platform.

## Strings

`Strings/2405010.c` is a small natural language processing pipeline over up to 50 documents of up to 5,000 characters each. It uses `<string.h>` and `<ctype.h>` and no pointers, as the assignment requires.

| Command | Action |
| --- | --- |
| `set` | Read the number of documents and their text |
| `preprocess` | Run all four steps below in order, printing the result of each |
| `tf` | Term frequency of a word in each document |
| `idf` | Inverse document frequency of a word across all documents |
| `tfidf` | TF-IDF of a word in each document |
| `stat` | Print TF, IDF and TF-IDF for every remaining token as matrices |
| `help`, `exit` | Show the command list, or quit |

`preprocess` does four things:

1. **Normalise**: convert every document to lowercase.
2. **Tokenise**: split the text into alphanumeric words.
3. **Remove stop words**: drop `the`, `is`, `a`, `an`, `and`, `in`, `of` and `to`.
4. **Stem**: strip a trailing `ing`, `ed` or `s`.

Run `set` and `preprocess` before `tf`, `idf`, `tfidf` or `stat`, since they work on the processed tokens.

## Pointers

Both programs avoid array indexing and use pointer arithmetic such as `*(p + i)`, as the assignment requires.

### Remove negatives (`Pointers/2405010-1.c`)

Reads `N` integers into a `malloc`ed array. `removeNegatives(int *input, int n, int **output, int *newSize)` allocates a second array that holds only the non-negative values and reports its size through `newSize`. Both arrays are freed at the end.

```text
6
3 -1 0 -7 8 2
```

```text
4
3 0 8 2
```

### Sort words (`Pointers/2405010-2.c`)

Reads `n` words into a `char **` list, each word allocated separately, and sorts them lexicographically with bubble sort and a pointer-swapping `swap`. Each word is typed with a trailing `.` as its terminator, and the compare function stops at that dot.

```text
3
banana.
apple.
cherry.
```

```text
apple.
banana.
cherry.
```

## Build and run

Everything compiles with gcc. Compile and run each program from its own folder, because the folder names contain spaces and `offline 2.c` includes `utils.c` from the same folder.

```bash
# Loops
gcc "Loops/offline 01/offline 01.c" -o loops
./loops < input.txt

# Arrays
cd "Arrays/2405010"
gcc "offline 2.c" -o arrays -lm
./arrays

# Strings
gcc Strings/2405010.c -o strings -lm
./strings

# Pointers
gcc Pointers/2405010-1.c -o remove_negatives
gcc Pointers/2405010-2.c -o sort_words
```

`-lm` links the math library, which the arrays and strings programs need for `sqrt` and `log`.

## Repository layout

```text
.
├── Loops/       CSE102_Offline1.pdf and "offline 01/" (source, plus a committed .exe and .o)
├── Arrays/      offline2/ (assignment PDF, starter utils.c, sample sessions) and 2405010/ (solution)
├── Strings/     assignment PDF and 2405010.c
└── Pointers/    assignment PDF, 2405010-1.c and 2405010-2.c
```

Folders named `2405010` are my solutions (my student ID). `Arrays/__MACOSX/` holds macOS metadata that came with the downloaded zip.

## Notes

- The `hist` command in the arrays program prints an error for a bin count outside 1 to 1000 but then carries on with that value, so enter a valid count.
- In `Pointers/2405010-1.c` the index `j` is declared without a value before it is used. It happened to work in my test run, but initialising it to `0` is the safe fix.
- The loops program prints `Energy level` in lower case, where the assignment text shows `Energy Level`.
- This repository is coursework kept for reference.
