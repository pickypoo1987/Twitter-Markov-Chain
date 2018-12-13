#include <vector>
#include <queue>
#include <map> // unused currently
// ------------------------------------------------------------------------------------------
#ifndef WORDGRAPH_H
#define WORDGRAPH_H
// ------------------------------------------------------------------------------------------
#include "AuthorStruct.hpp"
#include "HashTable.hpp"
// ------------------------------------------------------------------------------------------
class WordGraph {
// ------------------------------------------------------------------------------------------
  public:
// ------------------------------------------------------------------------------------------
    ////////////////////////////////////////////////////
    // INITIALIZER AND DESTRUCTOR ---> INITIALIZES THE WORDGRAPH OBJECT, AND THEN FREES ALL THE MEMORY ASSOCIATED

    // initializer given a table size
    WordGraph(std::string fileName);

    // destructor
    ~WordGraph();


// ------------------------------------------------------------------------------------------
    ////////////////////////////////////////////////////
    // NECESSARY FOR SETTING UP THE GRAPH FROM A TEXT FILE

    // creates the graph with all the necessary components
    void createGraph();


// ------------------------------------------------------------------------------------------
    ////////////////////////////////////////////////////
    // PUBLIC FUNCTIONS FOR TESTING PURPOSES

    std::string createSentence(int);


// ------------------------------------------------------------------------------------------
  private:
// ------------------------------------------------------------------------------------------
    ////////////////////////////////////////////////////
    // MARKOV CHAIN HELPER FUNCTIONS
/*
    Markov Chain private {
*/

    // picks a starting word at random
    std::string pickStartWord(); // COMPLETE (will NOT give me punctuation to start sentences...)

    // outputs a given sentence length based on a range calculated on the author object's avg sentence length
    int getRandomSentenceLength();

    // get a vector filled with the needed adjacency list at the correct input...
    // quite a cool func IMHO..
    std::vector<std::vector<WordEdge *> > getAdjLists(std::queue<WordVertex *>, int);

    // gets the next word with a given markov order and adjacency List
    std::string getNextWord(std::vector<std::vector<WordEdge *> >, int, int);

    // turns a vector of word tokens into a message with proper spacing and punctuation
    std::string createMessage(std::vector<std::string>);

    // initializes a probability map correctly...
    // if a word is not found in each adjList, that word is initialized to 0
    // otherwise they are initialized to the last indices probability
    std::map<std::string, double> mapInitializer(std::vector<std::vector<WordEdge *> > adjList, int);


/*
    }
*/
// ------------------------------------------------------------------------------------------
    ////////////////////////////////////////////////////
    // FUNCTIONS THAT WILL HELP BUILD THE GRAPH
/*
    Vertices functions {
*/
    // creates the graph vertices from a given file name
    void createGraphVertices();

    // adds a word vertex to the hashtable
    void addWord(std::string);

/*
    }
*/
// ------------------------------------------------------------------------------------------
/*
    Edges functions {
*/

    // adds all of the edges to the graph
    void createGraphEdges();

    // adds an edge for the first parameter to the second parameter
    void addEdge(std::string, std::string, int);

    // heapify's the adj lists
    void heapifyAdjLists();

    // returns true if one word is in a given adj list or false otherwise
    bool isInAdjList(std::string, std::string, int);

    // increments a path count with the same parameters as above
    void incrementPathCount(std::string, std::string, int);

    // increments the total number of edges at a given index
    void incrementNumEdges(std::string, int);

    // increments the total sum of the edges at a given index
    void incrementTotalSumEdges(std::string, int);

    // sets the probabilities of each edge
    void setEdgeProbabilities();

    // takes the asterisks out of the fileContents vector so they don't screw up our edges func
    void fixFileContents();

/*
    }
*/
// ------------------------------------------------------------------------------------------
/*
    Miscellaneous functions {
*/

    // sets the wordVertex vector to hold onto the word of each vertex, useful for iterating through the table
    // implemented in createGraphVertices()
    void setWordVertices();

    // sets the startWord vector to hold onto all the words that start sentences
    // implemented in createGraphVertices()
    void setStartWordVertices();

    // sets the fileContents string to the data from the file
    // implemented in the constructor
    void setFileContents(std::string);

/*
    }
*/
// ------------------------------------------------------------------------------------------

    ////////////////////////////////////////////////////
    // HASH TABLE STUFF

    // actual hash table object that holds onto the word vertices
    HashTable wordVertexTable;

// ------------------------------------------------------------------------------------------
    ////////////////////////////////////////////////////
    // OTHER PRIVATE STUFF

    // vector that holds every vertex in the graph
    std::vector<std::string> wordVertices;

    // vector that holds any potential start words
    std::vector<std::string> startWordVertices;

    // vector of strings that holds the contents of the file
    std::vector<std::string> fileContents;

    // total num of unique words
    int numWordVertices;

    // the author struct that holds onto some specific stats about the given author
    Author *author;
// ------------------------------------------------------------------------------------------
};
// ------------------------------------------------------------------------------------------
#endif
