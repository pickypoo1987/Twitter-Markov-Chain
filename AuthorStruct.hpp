#ifndef Author_H
#define Author_H
// ------------------------------------------------------------------------------------------
#include <string>
// ------------------------------------------------------------------------------------------
struct Author {
/*
---------------------------------------------------------------------------------------------
*/
  ///////////////////////////////////////////////////////////////////////////////////////////
  // THE STRING VALUE REPRESENTING THE NAME OF THE AUTHOR

  // author's name
  std::string authorName;
/*
---------------------------------------------------------------------------------------------
*/
  ///////////////////////////////////////////////////////////////////////////////////////////
  // SOME VARIABLES TO HELP MODEL AN AUTHOR'S TWEET TENDENCIES

  // total number of words found in data text
  int totalWordCount;

  // total number of messages found in data text
  int totalMessageCount;

  //  avg length of the Tweet message
  int avgMessageLength;

  // avg length of the sentences used
  // google: says the average is around 14 so we could set it to 14 as a default
  int avgSentenceLength;

  // total number of periods used ( . )
  int numPeriods;

  // total number of exclamation points used ( ! )
  int numExclPoints;

  // total number of question marks used ( ? )
  int numQuestMarks;

  ///////////////////////////////////////////////////////////////////////////////////////////
  // CONSTRUCTOR

  Author();

/*
---------------------------------------------------------------------------------------------
*/ };
// ------------------------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& os, const Author& A); // output stream overloading
// ------------------------------------------------------------------------------------------
#endif
