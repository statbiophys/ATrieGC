# ATrieGC

A python/c++ module to store large amount of sequences and look at hamming distance clustering. Should be a lot faster than the naive method (measuring every hamming distances between pairs).

## Installation

After cloning the git repository:

```
pip3 install atriegc
```

## Usage

### Working with the nucleotide alphabet
```python
import atriegc

tr = atriegc.TrieNucl()
tr.insert("AAAATGC")
tr.insert("ATAATGC")
tr.insert("TTTTTGC")

max_hamming_distance = 1
print(tr.neighbours("AAATTGC", max_hamming_distance))
print(tr.clusters(max_hamming_distance))
```

### Working with the amino acid alphabet
Where aminoacid are indicated with capital letters.
```python
tr = atriegc.TrieAA()
tr.insert("CARGKYSPATFDSW")
```

### Working with a generic alphabet
The alphabet should be passed as a string which lists all the 
possible characters of the alphabet
```python
tr = atriegc.Trie("abcdef")
```
