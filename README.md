# Structured Programming Language (CSE 102)

C programs from my first-year Structured Programming course at BUET. Each folder is one offline assignment, from loops and conditionals up to pointers with dynamic memory, and holds the assignment PDF next to the solution.

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
