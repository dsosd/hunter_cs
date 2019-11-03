#include "dna.h"

#include <algorithm>
#include <exception>
#include <limits>
#include <sstream>

#include <util/string_parser.h>

namespace tul{
namespace practice{
namespace hccs135{
namespace p2{

void Dna::run_a(std::istream& in, std::ostream& out) const{
	std::string line;
	while (std::getline(in, line)){
		out << transcribe_dna(line) << "\n";
	}
}

void Dna::run_b(std::istream& in, std::ostream& out) const{
	std::string line;
	while (std::getline(in, line)){
		std::string mrna = transcribe_dna(line);
		std::vector<std::string> codons_ = isolate_first_sequence(translate_mrna(mrna));
		out << get_sequence_str(codons_) << "\n";
	}
}

void Dna::run_c(std::istream& in, std::ostream& out) const{
	std::string orig, mutated;
	while (std::getline(in, orig) && std::getline(in, mutated)){
		orig = transcribe_dna(orig);
		mutated = transcribe_dna(mutated);

		int hamming_dist = calc_hamming_dist(orig, mutated);

		std::vector<std::string> orig_codons = isolate_first_sequence(translate_mrna(orig));
		std::vector<std::string> mutated_codons = isolate_first_sequence(translate_mrna(mutated));
		bool codons_identical = orig_codons.size() == mutated_codons.size();

		for (std::size_t i = 0; i < orig_codons.size() && codons_identical; ++i){
			if (orig_codons[i] != mutated_codons[i]){
				codons_identical = false;
			}
		}

		out << hamming_dist << " " << (codons_identical ? "no" : "yes") << "\n";
	}
}

void Dna::run_d(std::istream& in, std::ostream& out) const{
	constexpr int codon_size = 3;

	std::string orig, mutated;
	while (std::getline(in, orig) && std::getline(in, mutated)){
		orig = transcribe_dna(orig);
		mutated = transcribe_dna(mutated);

		//find three sequences with initial offsets [0, 2] to account for the frameshift mutations
		//earliest sequence (smallest overall offset) is the desired sequence
		std::map<std::size_t, std::vector<std::string>> offset_to_codons;

		for (int i = 0; i < codon_size; ++i){
			std::vector<std::string> init_seq = translate_mrna(mutated);
			std::vector<std::string> isolated_seq = isolate_first_sequence(init_seq);

			//check that a sequence was found
			if (isolated_seq.size()){
				//+1 counteracts the stripping of the "Stop" codon when the sequence is isolated
				std::size_t offset = i + codon_size * (init_seq.size() - isolated_seq.size() + 1);
				offset_to_codons[offset] = isolated_seq;
			}
		}

		//find min offset
		std::size_t min_offset = std::numeric_limits<std::size_t>::max();
		for (const auto& it: offset_to_codons){
			min_offset = std::min(it.first, min_offset);
		}

		//MAGIC spec file states that codons should be separated by "-"
		out << get_sequence_str(isolate_first_sequence(translate_mrna(orig))) << "\n";
		//check that a sequence was found
		if (min_offset != std::numeric_limits<std::size_t>::max()){
			out << util::str_join(offset_to_codons.at(min_offset), "-") << "\n";
		}
		else{
			out << "sequence DNE\n";
		}
	}
}

void Dna::load_codons(std::istream& in){
	std::string line;
	while (std::getline(in, line)){
		std::vector<std::string> parts = util::str_split(line, " ");
		codons[parts[0]] = parts[1];
	}
}

std::string Dna::transcribe_dna(const std::string& dna) const{
	std::map<char, char> dna_to_mrna = {
		{'t', 'A'}, {'T', 'A'},
		{'a', 'U'}, {'A', 'U'},
		{'g', 'C'}, {'G', 'C'},
		{'c', 'G'}, {'C', 'G'},
	};

	std::stringstream ss;
	for (char base: dna){
		ss << dna_to_mrna[base];
	}
	return ss.str();
}

std::vector<std::string> Dna::translate_mrna(const std::string& mrna) const{
	//codons must be loaded
	if (!codons.size()){
		throw std::exception();
	}

	//split mrna into groups of 3 bases because each codon is translated from 3 bases
	constexpr int codon_size = 3;
	std::vector<std::string> base_groups;
	for (std::size_t i = 0; i < mrna.size() / codon_size; ++i){
		base_groups.push_back(mrna.substr(i * codon_size, codon_size));
	}

	//translate
	std::vector<std::string> ret;
	for (const std::string& group: base_groups){
		ret.push_back(codons.at(group));
	}
	return ret;
}

int Dna::calc_hamming_dist(const std::string& a, const std::string& b) const{
	//hamming distance is for equal length strings only
	if (a.size() != b.size()){
		throw std::exception();
	}

	int ret = 0;
	for (std::size_t i = 0; i < a.size(); ++i){
		if (a[i] != b[i]){
			++ret;
		}
	}
	return ret;
}

std::vector<std::string> Dna::isolate_first_sequence(const std::vector<std::string>& codons_) const{
	std::vector<std::string> start_codons = {"Met"};
	std::vector<std::string> end_codons = {"Stop"};

	auto start_pos = std::find_first_of(codons_.begin(), codons_.end(), start_codons.begin(), start_codons.end());
	auto end_pos = std::find_first_of(start_pos, codons_.end(), end_codons.begin(), end_codons.end());

	//no sequence exists
	if (start_pos == codons_.end()){
		return std::vector<std::string> ();
	}

	//automatically strips off the "Stop" codon because it's at the end position
	std::vector<std::string> ret(start_pos, end_pos);
	return ret;
}

std::string Dna::get_sequence_str(const std::vector<std::string>& sequence) const{
	//MAGIC spec file states that codons should be separated by "-"
	return util::str_join(sequence, "-");
}

}
}
}
}
