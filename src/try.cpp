#include "trie_container.hpp"



int main(){

	TrieContainer trie = TrieContainerAA();
	trie.insert("CARG");
	trie.insert("CARAG");
	trie.insert("CARRG");
	trie.insert("CAVG");
	std::vector<std::string> l = std::vector<std::string>();
	l.push_back("CVVG");
	l.push_back("CCCRG");
	l.push_back("CCCG");
	trie.insert_list(l);

	std::cout << "Neighbour test\n";
	std::vector<std::string> ng = trie.hamming_neighbours("CARRG", 1);
	for (std::string n : ng) std::cout << n << "\n";

	std::cout << "Cluster test\n";
	std::unordered_map<str, std::size_t> cluster = trie.hamming_clusters(1);
	for (auto& it: cluster) {
	    // Do stuff
	    std::cout << it.first << ": " << it.second << "\n";
	}

	std::cout << "Shared seq test\n";
	std::vector<std::string> l2 = std::vector<std::string>();
	l2.push_back("CVVG");
	l2.push_back("CCCAG");
	l2.push_back("CCCC");
	std::vector<std::pair<str, str>> pairs = trie.shared_elements(l2, 1);
	for (std::pair<str, str>& pair : pairs) std::cout << pair.first << "\t" << pair.second << "\n";


	return 0;
}