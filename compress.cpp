//--------------------------------------------------------
// You can only use these headers

#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>

#include "treap_bst.h"

using namespace std;

void addTree(TreapBST<std::string, uint32_t> &compt, std::string &input, std::ifstream &in, std::ofstream &outstream, uint32_t &inc);
void writeEnc(TreapBST<std::string, uint32_t> &compt, std::string &input, std::ifstream &in, std::ofstream &outstream);
void readEnc(TreapBST<uint32_t, std::string> &dect, std::string &output, std::ofstream &out, std::ifstream &instream);

int main(int argc, char *argv[]) {
	uint32_t inc = 1;
	std::string input;
	std::string comp;
	std::string output;
	std::vector<std::string>  arguments;
	for (int i = 0; i < argc; ++i) arguments.push_back(argv[i]);
	if (argc==3) {
		input = argv[1];
		comp = argv[2];
	}
	else if (argc == 4) {
		if (strcmp(argv[1], "-d") == 0) {
			comp = argv[2];
			output = argv[3];
		}
		else {
			std::cerr << "Error Code 1" << endl;
			return EXIT_FAILURE;
		}
	}
	else {
		std::cerr << "Error Code 2" << endl;
		return EXIT_FAILURE;
	}

	std::ifstream in;
	std::ofstream out;
	
	//compressing
	if (argc == 3) {
		TreapBST<std::string, uint32_t> compt;
		std::ofstream outstream(comp, std::ios::binary);
		addTree(compt, input, in,outstream, inc);//Assembling Dictionary
		writeEnc(compt, input, in, outstream);
	}
	//decompressing
	else if (argc == 4) {
		TreapBST<uint32_t, std::string> dect;
		std::ifstream instream(comp, std::ios::binary);
		readEnc(dect, output, out, instream);
	}
	return EXIT_SUCCESS;
}

void addTree(TreapBST<std::string, uint32_t> &compt,std::string &input,std::ifstream &in, std::ofstream &outstream,uint32_t &inc) {
	in.open(input);
	while (in.good()) {
		std::string word;
		bool found;
		in >> word;
		compt.search(word, found);
		if (word != "") {
			if (found == false) {
				compt.insert(word, inc);
				//add dictionary
				outstream.write(reinterpret_cast<const char*>(&inc), sizeof inc);//key
				for (int i = 0; i < word.length(); i++) {						//word
					char x = word[i];
					outstream.write(reinterpret_cast<const char*>(&x), sizeof x);
				}
				uint8_t z = 0;
				outstream.write(reinterpret_cast<const char*>(&z), sizeof z);
				inc++;
			}
		}
	}
	in.close();
	//end of dictionary
	uint32_t zero = 0;
	outstream.write(reinterpret_cast<const char*>(&zero), sizeof zero);
}

void writeEnc(TreapBST<std::string, uint32_t> &compt , std::string &input, std::ifstream &in, std::ofstream &outstream) {
	in.open(input);
	while (in.good()) {
		std::string word;
		bool found;
		in >> word;
		if (word != "") {
			uint32_t dicnum = compt.search(word, found);
			if (found == false) {
				std::cerr << "Dictionary Mistake" << endl;
			}
			outstream.write(reinterpret_cast<const char*>(&dicnum), sizeof dicnum);
		}
	}
}

void readEnc(TreapBST<uint32_t, std::string> &dect, std::string &output, std::ofstream &out, std::ifstream &instream) {
	bool check = true;
	bool found;
	while (check==true) {
		std::string word;
		uint32_t key;
		instream.read(reinterpret_cast<char*>(&key), sizeof key);
		if (key == 0) {
			break;
		}
		char x='7';
		while (x!='\0') {
			instream.read(reinterpret_cast<char*>(&x), sizeof x);
			if(x != '\0')
			word.push_back(x);
		}
		dect.insert(key, word);
	}

	out.open(output);
	while (instream.good()) {
		uint32_t dickey=uint32_t();
		instream.read(reinterpret_cast<char*>(&dickey), sizeof dickey);
		std::string oword = dect.search(dickey, found);
		if (found == true) {
			out << oword << " ";
		}
	}
}