#ifndef WORDEDGE_H
#define WORDEDGE_H
// ------------------------------------------------------------------------------------------
struct WordVertex;
// ------------------------------------------------------------------------------------------
struct WordEdge {
/*
---------------------------------------------------------------------------------------------
*/
  //////////////////////////////////////////////////
  // THE ACTUAL WORD THAT THE EDGE CONNECTS TO

  // this will take us to the WordVertex in the graph with all of that data
  WordVertex *word;

/*
---------------------------------------------------------------------------------------------
*/
  //////////////////////////////////////////////////
  // THE COUNT THAT THIS SPECIFIC PATH CONTAINS

  // basically the number of times that this->word has preceded the word that has this edge in its adjacency list.. kinda weird
  int pathCount;

  // the probability that we will travel along this edge to the given word vertex above
  double probability;
/*
---------------------------------------------------------------------------------------------
*/
  //////////////////////////////////////////////////
  // CONSTRUCTOR

  WordEdge() {
    this->word = nullptr;
    probability = 0;
    pathCount = 0;
  }

  WordEdge(WordVertex* word) {
    this->word = word;
    probability = 0;
    pathCount = 1;
  }
/*
---------------------------------------------------------------------------------------------
*/
  //////////////////////////////////////////////////
  // OPERATOR OVERLOADING

  friend std::ostream& operator<<(std::ostream& os, WordEdge& E) { // Output Stream Overloading

    os << "Word: " << E.word << "(" << E.pathCount << ")";

    return os; // return the os object
  }
/*
---------------------------------------------------------------------------------------------
*/ };

// struct that is used for make_heap's comparison
struct MakeHeap_Comp {
    bool operator()(WordEdge const * lhs, WordEdge const * rhs) {
      if (lhs->probability != 0 && rhs->probability != 0) {
        return lhs->probability <= rhs->probability;
      }
      else {
        return lhs->pathCount <= rhs->pathCount;
      }
    }
};

// ------------------------------------------------------------------------------------------
#endif
