#ifndef TRIE_CONT
#define TRIE_CONT

#include "trie.hpp"
#include "utils.hpp"

/* Class that contains a digital Trie, and can work directly with
   strings with the objective of simplifying the python interface */
class TrieContainer{
private:
  Trie tr;

  // Also contain the sequences, for easy back-and-forth
  std::vector<std::string> seqs; 

public:
  TrieContainer(){
  }

  std::size_t size(){
    return tr.size();
  }

  void insert(const std::string& nuc_seq){
    dna d = string_to_dna(nuc_seq);
    seqs.push_back(nuc_seq);
    tr.insert(d.begin(), d.end(), seqs.size()); // insert "pos + 1"
  }

  void remove(const std::string&  nuc_seq){
    dna d = string_to_dna(nuc_seq);
    tr.remove(d.begin(), d.end());
  }

  bool contain(const std::string&  nuc_seq){
    dna d = string_to_dna(nuc_seq);
    return tr.contain(d.begin(), d.end());
  }

  bool empty(){
    return tr.empty();
  }

  void print(){
    tr.print();
  }

  std::string next(){
    dna d = dna();
    std::size_t ct;
    tr.next(d, ct);
    return dna_to_string(d);
  }

  std::vector<std::string> hamming_neighbours(const std::string&  seq,
					      std::size_t hamming_distance){
    dna d = string_to_dna(seq);
    std::vector<std::size_t> nb_neighbours;
    tr.hamming_neighbours(d.begin(), d.end(), hamming_distance, nb_neighbours);

    std::vector<std::string> neighbours(nb_neighbours.size(), "");
    for(std::size_t ii = 0; ii < nb_neighbours.size(); ++ii){
      neighbours[ii] = seqs[nb_neighbours[ii]-1]; //careful, "pos + 1" is inserted in the trie
    }
    return neighbours;
  }

  std::vector< std::vector<std::string> > hamming_clusters(std::size_t hamming_distance){
    std::vector< std::vector<std::string> > clusters;
    std::vector<std::size_t> current_cluster, tmp_cluster;
    current_cluster.reserve(128); tmp_cluster.reserve(128);
    std::size_t current_cluster_nb = 0;
    dna tmp_dna;
    std::size_t current_nb = 0;

    while(!tr.empty()){
      if(current_cluster.empty()){
	clusters.push_back(std::vector<std::string>());
	tmp_dna.clear();
	tr.next(tmp_dna, current_nb);
	current_cluster.push_back(current_nb);
	current_cluster_nb += 1;
      }
      tmp_cluster.clear();
      for(std::size_t ii: current_cluster){
	tmp_dna.clear();
	tmp_dna = string_to_dna(seqs[ii-1]);
	tr.hamming_neighbours(tmp_dna.begin(), tmp_dna.end(),
			      hamming_distance, tmp_cluster);
	for(std::size_t jj: tmp_cluster){
	  remove(seqs[jj-1]);
	  clusters[current_cluster_nb - 1].push_back(seqs[jj-1]);
	}
      }
      current_cluster = tmp_cluster;
    }

    // re-create the trie
    tr = Trie();
    for(auto& s: seqs){
      insert(s);
    }
    return clusters;
  }
};


#endif // TRIE_CONT
