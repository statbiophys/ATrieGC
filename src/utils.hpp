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

#define NUCL_ALPHABET "ACGT"

#define AA_ALPHABET "RHKDESTNQCUGPAVILMFYW"


using seq = std::vector<short unsigned int>;
using str = std::string;
using vecs = std::vector<str>;


/* Return the hamming distance between two strings. If the string are
   not equal in length, or if their Hamming distance become
   larger than cutoff return MAX_DISTANCE. */
inline std::size_t hamming_distance(const seq& a1, const seq& a2, std::size_t cutoff){
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
