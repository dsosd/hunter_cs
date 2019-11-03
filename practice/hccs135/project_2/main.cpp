#include "main.h"

#include <fstream>
#include <iostream>

#include "dna.h"

namespace tul{
namespace practice{
namespace hccs135{
namespace p2{

int main(int argc, char** argv){
	Dna dna_parser;

	std::fstream file_a1("practice/hccs135/project_2/test_files/dna.txt");
	dna_parser.run_a(file_a1, std::cout);

	std::fstream file_codons("practice/hccs135/project_2/test_files/codons.tsv");
	dna_parser.load_codons(file_codons);

	std::fstream file_b1("practice/hccs135/project_2/test_files/dna2b.txt");
	dna_parser.run_b(file_b1, std::cout);

	std::fstream file_c1("practice/hccs135/project_2/test_files/mutations.txt");
	dna_parser.run_c(file_c1, std::cout);

	std::fstream file_d1("practice/hccs135/project_2/test_files/frameshift_mutations.txt");
	dna_parser.run_d(file_d1, std::cout);
	return 0;
}

}
}
}
}
