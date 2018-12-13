#include "AuthorStruct.hpp"
// ------------------------------------------------------------------------------------------
#include <iostream>
// ------------------------------------------------------------------------------------------
Author::Author() {
	std::string authorName = ""; // empty string
	avgSentenceLength = 14; // default
	numPeriods = numExclPoints = numQuestMarks = totalWordCount = avgMessageLength = totalMessageCount = 0; // initially set all var's to 0
}
// ------------------------------------------------------------------------------------------
// formatting output objects to print an Author nicely
std::ostream& operator<<(std::ostream& os, const Author& A) {
	os << "Name: " << A.authorName << std::endl // each thing on a new line
		 << "\tTotal Word Count: " << A.totalWordCount << std::endl
		 << "\tTotal Message Count: " << A.totalMessageCount << std::endl
		 << "\tAvg. Message Length: " << A.avgMessageLength << std::endl
	   << "\tAvg. Sentence Length: " << A.avgSentenceLength << std::endl
	   << "\tNumber of Periods: " << A.numPeriods << std::endl
     << "\tNumber of Exc. Points: " << A.numExclPoints << std::endl
     << "\tNumber of Quest. Marks: " << A.numQuestMarks << std::endl;
	return os; // return the os object
}
// ------------------------------------------------------------------------------------------
