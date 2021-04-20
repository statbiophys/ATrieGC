#ifndef TRIE_HPP
#define TRIE_HPP

#include "utils.hpp"


/* Class implementing a digital trie, that contain a number
std::size_t in each occupied node.
Nodes have to be occupied.
 */
class Trie{

 private:

    // all the childrens of a trie are trie
    std::vector<Trie*> cs;  
    // if the node is occupied (full = True)
    bool full;
    // if the node is occupied contains the number associated with it
    std::size_t obj; 
    // number of character in the alphabet
    std::size_t alph_size;

 public:

  Trie(std::size_t alph_size) : full(false), obj(0), alph_size(alph_size) {
    cs = std::vector<Trie*>(alph_size, NULL);
  }
  
  ~Trie(){
    for(auto n: cs)
      delete n;
  }

  // return the size of the trie
  std::size_t size(){
    std::size_t size = (full ? 1 : 0);
    for(std::size_t ii=0; ii < alph_size; ++ii){
      if(cs[ii] != NULL){
      size += cs[ii]->size();
      }
    }
    return size;
  }
    
  // insert one sequence into the Trie, overwrite if already here
  void insert(seq::iterator b, seq::iterator e, std::size_t o){
    if(b == e){
      full = true;
      obj = o;
    }
    else{
      if(cs[*b] == NULL)
        cs[*b] = new Trie(alph_size);
      cs[*b]->insert(std::next(b),e,o);
    }
  } 

  // remove an amino sequence from the Trie
  void remove(seq::iterator b, seq::iterator e){
    if(b == e)
      full = false;
    else{
      if(cs[*b] != NULL){ // if not the word is not in the Trie
        cs[*b]->remove(std::next(b), e);
        if(cs[*b]->is_leaf() and not cs[*b]->full){
          delete cs[*b];
          cs[*b] = NULL;
        }
      }
    }
  }

  bool contain(seq::iterator b, seq::iterator e){
    if(b == e)
      return true;
    if(cs[*b] == NULL)
      return false;
    else
      return cs[*b]->contain(std::next(b), e); 
  }

  bool is_leaf(){
    for(std::size_t ii=0; ii < alph_size; ++ii){
      if(cs[ii] != NULL)
      return false;
    }
    return true;
  }
 
  bool empty(){
    for(std::size_t ii=0; ii < alph_size; ++ii){
      if(cs[ii] != NULL)
      return false;
    }
    return !full;
  }

  // display the Trie (folder like)
  void print(str alphabet, str tab="") {
    if(full)
      std::cout << tab << ":" << obj;
    else
      std::cout << tab;
    std::cout << "\n";
    for(std::size_t ii=0; ii < alph_size; ++ii){
      if(cs[ii] != NULL)
        cs[ii]->print("  " + tab + alphabet[ii], alphabet);
    }
  } 
 
  // return the first dna sequence found in the tree and its content
  void next(seq& d, std::size_t& content) const{
    if(not full){ // if we don't find one at the current node
      for(std::size_t ii=0; ii < alph_size; ++ii){
        if(cs[ii] != NULL){
          d.push_back(ii);
          cs[ii]->next(d, content);
          break;
        }
      }
    }
    else{ // if we found an occupied node, we stop
      content = obj;  
    }
  }

  // list all the Hamming neighbours associated with the sequence b, e
  // (at distance d) and put them in the "hamming_neighbours" vector
  // don't clear the vector
  void hamming_neighbours(seq::iterator b,
            seq::iterator e,
            std::size_t d,
            std::vector<std::size_t>& neighbours) const{
    if(b == e){
      if(full){
        // add the number in the node to the vector
        neighbours.push_back(obj);
      }
    }
    else{
      for(std::size_t ii=0; ii < alph_size; ++ii){
        if(cs[ii] != NULL){
          if(ii != *b and d > 0)
            cs[ii]->hamming_neighbours(std::next(b), e, d-1, neighbours);
          if(ii == *b)
            cs[ii]->hamming_neighbours(std::next(b), e, d, neighbours);
        }
      }
    }
  }

};


#endif //TRIE_HPP
