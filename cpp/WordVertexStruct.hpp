#include <iostream> // needed for: OS operator overloading
#include <iomanip> // needed for: printing the probabilities nicely
#include <string> // needed for: we hold onto the word string
#include <vector> // needed for: the adjacency list matrix
// ------------------------------------------------------------------------------------------
#include "WordEdgeStruct.hpp"
// ------------------------------------------------------------------------------------------
#ifndef WORDVERTEX_H
#define WORDVERTEX_H
// ------------------------------------------------------------------------------------------
/* the max amount of words the adj list holds */
#define MAX_ADJ_VEC_SIZE 5
// ------------------------------------------------------------------------------------------
struct WordVertex {
/*
---------------------------------------------------------------------------------------------
*/
  //////////////////////////////////////////////////
  // THE ACTUAL WORD THAT THE NODE HOLDS

  // the word we are at in our Markov chain
  std::string Word;

/*
---------------------------------------------------------------------------------------------
*/
  //////////////////////////////////////////////////
  // COUNTS ASSOCIATED WITH THE WORD

  // total number of times this word was read in the sample text
  int totalCount;

  // total number of times this word started a sentence in the sample text
  int sentenceStartCount;

  // total number of times this word ended a sentence in the sample text
  int sentenceEndCount;
/*
---------------------------------------------------------------------------------------------
*/
  //////////////////////////////////////////////////
  // VECTOR THAT HOLDS THE WORDNODE'S ADJACENCY MATRIX (LIST) AND ASSOCIATED INFO

  // vector of adjacency list vectors
  std::vector<std::vector<WordEdge *> > adjacencyList;

  // total number of edges (basically the number of places we could go next in our Markov chain)
  std::vector<int> totalNumEdges;

  // total sum of all the edges in the adjacency list
  std::vector<int> totalSumEdgePaths;
/*
---------------------------------------------------------------------------------------------
*/
  //////////////////////////////////////////////////
  // POINTER THAT HOLDS THE NEXT WORD VERTEX STRUCT FOR COLLSIONS IN THE HASH TABLE

  // hash table collion handling
  WordVertex *nextInTable;
/*
---------------------------------------------------------------------------------------------
*/
  //////////////////////////////////////////////////
  // CONSTRUCTORS

  WordVertex() {
    Word = "";
    nextInTable = nullptr;
    totalCount = sentenceStartCount = sentenceEndCount = 0;

    // initailizing the vectors of size MAX_ADJ_VEC_SIZE with all 0's
    this->totalSumEdgePaths = std::vector<int>(MAX_ADJ_VEC_SIZE, 0); // i like the one-liners...
    this->totalNumEdges = std::vector<int>(MAX_ADJ_VEC_SIZE, 0);

    // initializing the adjacency list of size MAX_ADJ_VEC_SIZE with all empty WordEdge* vectors
    std::vector<WordEdge *> vec;
    this->adjacencyList = std::vector<std::vector<WordEdge *> >(MAX_ADJ_VEC_SIZE, vec);

  }

  WordVertex(std::string word) {

    Word = word;
    nextInTable = nullptr;
    sentenceStartCount = sentenceEndCount = totalCount = 0;

    // initailizing the vectors of size MAX_ADJ_VEC_SIZE with all 0's
    this->totalSumEdgePaths = std::vector<int>(MAX_ADJ_VEC_SIZE, 0); // i like the one-liners...
    this->totalNumEdges = std::vector<int>(MAX_ADJ_VEC_SIZE, 0);

    // initializing the adjacency list of size MAX_ADJ_VEC_SIZE with all empty WordEdge* vectors
    std::vector<WordEdge *> vec;
    this->adjacencyList = std::vector<std::vector<WordEdge *> >(MAX_ADJ_VEC_SIZE, vec);

  }


  // kinda weird, but I'm controlling how cout << WordVertex* << endl; acts...
  friend std::ostream& operator<<(std::ostream& os, WordVertex& W) { // Output Stream Overloading

    os << "Word: " << W.Word << std::endl
              << " Total Word Count: " << W.totalCount << std::endl
              << " Sentence Start Count: " << W.sentenceStartCount << std::endl
              << " Sentence End Count: " << W.sentenceEndCount << std::endl
              << "  Total # of Edges Vector: ";

    int i = MAX_ADJ_VEC_SIZE - 1;
    int x = 0;
    for (auto each : W.totalNumEdges) {
      os << each;
      if (x != i) {
        os << " - ";
      }
      x++;
    }
    os << std::endl << "  Total Sum of Edges Vector: ";
    x = 0;
    for (auto each : W.totalSumEdgePaths) {
      os << each;
      if (x != i) {
        os << " - ";
      }
      x++;
    }

    os << std::endl << "    Adjacency Lists: " << std::endl;
    for (int i = 0; i < W.adjacencyList.size(); i++) {
      os << "     " << i + 1 << ". ";
      if (W.adjacencyList[i].empty()) {
        os << "Adj List @ index " << i << " is empty!" << std::endl;
      }
      else {
        int i1 = 0;
        int last_i = W.adjacencyList[i].size() - 1;
        for (auto each : W.adjacencyList[i]) {
          std::string edgeWord = each->word->Word;
          int pathCount = each->pathCount;
          double prob = each->probability * 100;
          os << edgeWord << " (Path count: " << pathCount << ", Probabilty: " << std::fixed << std::setprecision(2) << prob << "%)";
          if (i1 != last_i) {
            os << " -> ";
          }
          i1++;
        }
        os << std::endl;
      }
    }

    return os; // return the os object
  }

/*
---------------------------------------------------------------------------------------------
*/ };
// ------------------------------------------------------------------------------------------
#endif
