# ATrieGC

A python/c++ module to store large amount of sequences and look at hamming distance clustering. Should be a lot faster than the naive method (measuring every hamming distances between pairs).

## Installation

After cloning the git repository:

```
cd ATrieGC/
pip3 install .
```

## Usage

```python
import atriegc

tr = atriegc.Trie()
tr.insert("AAAATGC")
tr.insert("ATAATGC")
tr.insert("TTTTTGC")

max_hamming_distance = 1
print(tr.neighbours("AAATTGC", max_hamming_distance))
print(tr.clusters(max_hamming_distance))
```

## Caveat

Don't work with generalized nucleotides.
