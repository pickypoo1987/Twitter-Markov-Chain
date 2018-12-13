#include <iostream>
// ------------------------------------------------------------------------------------------
#include "ProductionWordGraphClass.hpp"
// ------------------------------------------------------------------------------------------
using namespace std;
// ------------------------------------------------------------------------------------------
int main(int argc, char const *argv[]) {

  // takes the filename as a command line argument
  std::string fileName = argv[1];

  // takes the string representation of the markov order as a command line argument
  std::string markovOrderStr = argv[2];

  // changes the string representation of the markov chain to an integer
  int markovOrder = stoi(markovOrderStr);

  // initialize the Graph
  WordGraph Graph(fileName);

  // creates the Graph
  Graph.createGraph();

  // creates a sentence and prints it to the console
  cout << Graph.createSentence(markovOrder) << endl;

  return 0;
}
// ------------------------------------------------------------------------------------------
