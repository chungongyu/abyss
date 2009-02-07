#include "PairedAlgorithms.h"
#include "PairUtils.h"
#include <cassert>
#include <string>

using namespace std;

namespace PairedAlgorithms
{
	
//
// Read contigs
//
void readContigVec(std::string file, ContigVec& outVec)
{
	std::ifstream fileHandle(file.c_str());	
	assert(fileHandle.is_open());

	while(!fileHandle.eof() && fileHandle.peek() != EOF)
	{
		ContigID strID;
		LinearNumKey numID;
		Sequence seq;
		int length;
		double coverage;

		parseContigFromFile(fileHandle, strID, seq, length, coverage);
		assert(!seq.empty());
		assert(length > 0);

		numID = convertContigIDToLinearNumKey(strID);
		
		// Make sure the index is correct
		assert(numID == outVec.size());
		outVec.push_back(Contig(seq, (unsigned)coverage));
	}
	fileHandle.close();
}

void parseContigFromFile(std::ifstream& stream, ContigID& id, Sequence& seq, int& length, double& coverage)
{
	char head;
	string comment;

	stream >> head;
	assert(head == '>');
	stream >> id;
	stream >> length;
	stream >> coverage;
	getline(stream, comment);
	getline(stream, seq);
	assert(stream.good());
}

};
