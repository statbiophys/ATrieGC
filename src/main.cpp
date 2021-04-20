#include "trie_container.hpp"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>


namespace py = pybind11;

PYBIND11_MODULE(atriegc, m) {
    m.doc() = R"pbdoc(
        ATrieGC
        -----------------------
        .. currentmodule:: atriegc
        .. autosummary::
           :toctree: _generate
           add
           subtract
    )pbdoc";

    py::class_<TrieContainer>(m, "Trie")
      .def(py::init<str>(), "Generate a Trie given a generic alphabet")
      .def("insert", &TrieContainer::insert,
	   "Insert a nucleotide sequence in the trie." )
      .def("insert_list", &TrieContainer::insert_list,
     "Insert a list nucleotide sequence in the trie." )
      .def("print", &TrieContainer::print,
	   "Output the trie (testing purposes)." )
      .def("remove", &TrieContainer::remove,
	   "Remove the sequence from the trie.")
      .def("contain", &TrieContainer::contain,
	   "Say whether a sequence is in the trie.")
      .def("empty", &TrieContainer::empty,
	   "Check if the trie is empty.")
      .def("next", &TrieContainer::next,
	   "Extract one sequence from the trie.")
      .def("neighbours", &TrieContainer::hamming_neighbours,
	   "List all the neighbours of a sequence s, up to hamming distance d.")
      .def("clusters", &TrieContainer::hamming_clusters,
	   "Single linkage clustering based on Hamming distance.")
      .def("shared_elements", &TrieContainer::shared_elements,
     "List of all the pair of elements shared with a list, up to hamming distance d.")
      ;

    py::class_<TrieContainerNucl, TrieContainer>(m, "TrieNucl")
      .def(py::init<>(), "Generate a Trie for nucleotides A-C-G-T");

    py::class_<TrieContainerAA, TrieContainer>(m, "TrieAA")
      .def(py::init<>(), "Generate a Trie for amino acids");


#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif
}
