#include <string>
#include <vector>
// ------------------------------------------------------------------------------------------
#include "WordVertexStruct.hpp"
// ------------------------------------------------------------------------------------------
#ifndef HASH_TABLE_H
#define HASH_TABLE_H
// ------------------------------------------------------------------------------------------
class HashTable{
// ------------------------------------------------------------------------------------------
	public:
// ------------------------------------------------------------------------------------------
		/////////////////////////////////////////////////////////////////////////////////////////
		// CONSTRUCTORS AND DESTRUCTORS

		// Constructor with no args
		HashTable();

		// Constructor with Hash Table size
		HashTable(int hashTableSize);

		// Destructor
		~HashTable();
// ------------------------------------------------------------------------------------------
		/////////////////////////////////////////////////////////////////////////////////////////
		// HELPER FUNCTIONS TO MAKE THIS LIBRARY EASIER TO WORK WITH FROM WITHIN

		// returns true if a given string is in the hash table, and false otherwise
		bool isInTable(std::string word);

		// adds a word to the table given a string
		void addWord(std::string word);

		// returns a pointer the a wordVertex if found and nullptr if not...
		WordVertex* searchTable(std::string word);
// ------------------------------------------------------------------------------------------
		/////////////////////////////////////////////////////////////////////////////////////////
		// HELPER FUNCTIONS TO MAKE THIS LIBRARY EASIER TO WORK WITH FROM MY WORD GRAPH CLASS

		// increment the specific word count for a given word
		void incrementCount(std::string word);

		// increment the start count for a given word
		void incrementStartCount(std::string word);

		// increment the end count for a given word
		void incrementEndCount(std::string word);
// ------------------------------------------------------------------------------------------
		// prints each Vertex stored in the Hash Table
		void printTableContents();
// ------------------------------------------------------------------------------------------
		// returns the total number of Vertices stored in the Hash Table
		int getTotalNumUniqueWords();
// ------------------------------------------------------------------------------------------
		// returns the total word count, by adding up each Vertice's word counts
		int getTotalWordCount();
// ------------------------------------------------------------------------------------------
		// helper function that turns the hash table into a vector of the unique vertices
		std::vector<std::string> vectorizeHashTable();
// ------------------------------------------------------------------------------------------
	private:
// ------------------------------------------------------------------------------------------
		// DJB2 hash func
		int hashFunc(std::string word);
// ------------------------------------------------------------------------------------------
		// the size of the table, i.e. how many buckets there are
		int hashTableSize;

		// the actual table... like an array of pointers
		WordVertex** hashTable;
// ------------------------------------------------------------------------------------------
		// the number of collisions our table encounters
		int numCollisions;

		// the number of unique words stored in the table
		int numUniqueWords;
// ------------------------------------------------------------------------------------------
};
// ------------------------------------------------------------------------------------------
#endif
