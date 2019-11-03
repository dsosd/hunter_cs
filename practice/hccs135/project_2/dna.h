#ifndef uuid_guard_3424ae31_7c3f8fa0_d53bbaa0_2209f928
#define uuid_guard_3424ae31_7c3f8fa0_d53bbaa0_2209f928

#include <iostream>
#include <map>
#include <string>
#include <vector>

namespace tul{
namespace practice{
namespace hccs135{
namespace p2{

class Dna{
public:
	//each part of the project can be run individually
	void run_a(std::istream& in, std::ostream& out) const;
	void run_b(std::istream& in, std::ostream& out) const;
	void run_c(std::istream& in, std::ostream& out) const;
	void run_d(std::istream& in, std::ostream& out) const;

	void load_codons(std::istream& in);
private:
	std::string transcribe_dna(const std::string& dna) const;
	std::vector<std::string> translate_mrna(const std::string& mrna) const;
	int calc_hamming_dist(const std::string& a, const std::string& b) const;

	std::vector<std::string> isolate_first_sequence(const std::vector<std::string>& codons_) const;
	std::string get_sequence_str(const std::vector<std::string>& sequence) const;

	std::map<std::string, std::string> codons;
};

}
}
}
}

#endif // uuid_guard_3424ae31_7c3f8fa0_d53bbaa0_2209f928
