#ifndef TRIE_CONT
#define TRIE_CONT

#include "trie.hpp"
#include "utils.hpp"


/* Class that contains a digital Trie, and can work directly with
   strings with the objective of simplifying the python interface */
class TrieContainer{

 private:

  Trie tr;

  const str alphabet;
  // Also contain the sequences, for easy back-and-forth

  vecs seqs; 

  seq string_to_seqence(const str& s) {
    seq sequence = seq(s.size());
    for (short unsigned int i=0; i<s.size(); i++)
      for (short unsigned int j=0; j<alphabet.size(); j++)
        if (s[i] == alphabet[j]){
          sequence[i] = j;
          break;
        }
    return sequence;
  }

  str sequence_to_string(const seq& x) {
    str st = "";
    for(auto l: x){
      st += alphabet[l];
    }
    return st;
  }


 public:
  TrieContainer(str alphabet): tr(Trie(alphabet.size())), alphabet(alphabet) {
    // TODO: check for repeated characters in the alphabet string
  }

  std::size_t size(){
    return tr.size();
  }

  void insert(const str& str_seq){
    seq d = string_to_seqence(str_seq);
    seqs.push_back(str_seq);
    tr.insert(d.begin(), d.end(), seqs.size()-1); 
  }

  void insert_list(const vecs& str_seqs){
    for (const str& str_seq : str_seqs)
      insert(str_seq);
  }

  void remove(const str&  str_seq){
    seq d = string_to_seqence(str_seq);
    tr.remove(d.begin(), d.end());
  }

  bool contain(const str&  str_seq){
    seq d = string_to_seqence(str_seq);
    return tr.contain(d.begin(), d.end());
  }

  bool empty(){
    return tr.empty();
  }

  void print(){
    tr.print(alphabet);
  }

  str next(){
    seq d = seq();
    std::size_t ct;
    tr.next(d, ct);
    return sequence_to_string(d);
  }

  vecs hamming_neighbours(const str& str_seq, std::size_t hamming_distance){
    seq d = string_to_seqence(str_seq);
    std::vector<std::size_t> nb_neighbours;
    tr.hamming_neighbours(d.begin(), d.end(), hamming_distance, nb_neighbours);

    vecs neighbours(nb_neighbours.size(), "");
    for(std::size_t ii = 0; ii < nb_neighbours.size(); ++ii){
      neighbours[ii] = seqs[nb_neighbours[ii]]; //careful, "pos + 1" is inserted in the trie
    }
    return neighbours;
  }

  std::unordered_map<str, std::size_t> hamming_clusters(std::size_t hamming_distance){
    std::unordered_map<str, std::size_t> clusters;
    std::vector<std::size_t> current_nodes, next_nodes;
    current_nodes.reserve(1024), next_nodes.reserve(1024);
    std::size_t current_cluster_nb = 0;
    seq tmp_dna;
    std::size_t current_nb = 0;

    while(!tr.empty()){
      if(current_nodes.empty()){
        tmp_dna.clear();
        tr.next(tmp_dna, current_nb);
        current_nodes.push_back(current_nb);
        current_cluster_nb += 1;
      }
      next_nodes.clear();
      for(std::size_t ii: current_nodes){
        tmp_dna = string_to_seqence(seqs[ii]);
        tr.hamming_neighbours(tmp_dna.begin(), tmp_dna.end(), hamming_distance, next_nodes);
        for(std::size_t jj: next_nodes){
          remove(seqs[jj]);
          clusters[seqs[jj]] = current_cluster_nb;
        }
      }
      current_nodes = next_nodes;
    }

    // re-create the trie
    vecs old_seqs = seqs;
    seqs.clear();
    tr = Trie(alphabet.size());
    for(auto& s: old_seqs){
      insert(s);
    }
    return clusters;
  }

  std::vector<std::pair<str, str>> shared_elements(vecs list, int hamming_dist) {
    std::vector<std::pair<str, str>> sh_list = std::vector<std::pair<str, str>>(0);
    for (const str& elem2 : list){
      vecs sh_elem = hamming_neighbours(elem2, hamming_dist);
      for (const str& elem1 : sh_elem)
        sh_list.push_back(std::pair<str, str>(elem1, elem2));
    }
    return sh_list;
  }
};


class TrieContainerNucl : public TrieContainer{
public:
  TrieContainerNucl() : TrieContainer(NUCL_ALPHABET) {};
};


class TrieContainerAA : public TrieContainer{
public:
  TrieContainerAA() : TrieContainer(AA_ALPHABET) {};
};


#endif // TRIE_CONT
