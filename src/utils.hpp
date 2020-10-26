#ifndef UTILS
#define UTILS

#include <chrono>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <map>
#include <tuple>
#include <functional>
#include <array>
#include <random>
#include <stdexcept>
#include <time.h>
#include <unordered_map>

// maximal distance between sequences, used as a default return value
// when the distances are above the threshold.
#define MAX_DISTANCE 10000
// default value for the cluster (means something bad happened)
#define DEFAULT 666666666

// size of the nucleotide alphabet
#define ALPHABET_SIZE 4


/* Nucleotides: A, C, G, T = 0, 1, 2, 3 
   Don't consider degenerate nucleotides (probably not useful)
*/
using dna=std::vector<short unsigned int>;

// Return a nucleotide string from a number (just fail if there's a problem)
std::string nucleotide_to_string(short unsigned int i){
  if(i == 0)
    return "A";
  if(i == 1)
    return "C";
  if(i == 2)
    return "G";
  if(i == 3)
    return "T";
}


/* Return a dna sequence from std::string */
inline dna string_to_dna(const std::string& x){
  dna ns;
  for(char l:x){
    if(l == 'A')
      ns.push_back(0);
    else if(l == 'C')
      ns.push_back(1);
    else if(l == 'G')
      ns.push_back(2);
    else if(l == 'T')
      ns.push_back(3);
  }
  return ns;
}

/* Return a std::string of the dna sequence */
inline std::string dna_to_string(const dna& x){
  const std::string dna_letter = "ACGT";
    std::string st = "";
    for(auto l: x){
      st += dna_letter[l];
    }
    return st;
}




/* Return the hamming distance between two strings. If the string are
   not equal in length, or if their Hamming distance become
   larger than cutoff return MAX_DISTANCE. */
inline std::size_t hamming_distance(const dna& a1, const dna& a2,
				    std::size_t cutoff){
  std::size_t d = 0;
  if(a1.size() != a2.size())
    return MAX_DISTANCE;
  for(std::size_t ii=0; ii < a1.size(); ++ii){
    if(a1[ii] != a2[ii]){
      d += 1;
      if(d > cutoff)
	return MAX_DISTANCE;
    }
  }
  return d;
}



#endif //UTILS
