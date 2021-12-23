#include "compressor/byte_entangler.h"
#include "compressor/byte_detangler.h"
#include "cryptopp/osrng.h"
#include "affix-base/ptr.h"
#include <iostream>

using std::vector;

vector<uint8_t> random_bytes(const size_t& a_size)
{
	vector<uint8_t> l_result(a_size);
	CryptoPP::AutoSeededRandomPool l_random;
	l_random.GenerateBlock(l_result.data(), l_result.size());
	return l_result;
}

std::string to_string(const vector<uint8_t>& a_vec)
{
	std::string result;
	for (int i = 0; i < a_vec.size(); i++)
		result += std::to_string(a_vec[i]) + " ";
	return result;
}

std::string to_string(const bool& a_val)
{
	if (a_val)
		return "true";
	else
		return "false";
}

using affix_base::data::ptr;

void unit_test_entangler_detangler()
{
	while (true)
	{
		vector<uint8_t> l_input = random_bytes(13);
		vector<uint8_t> l_knowns = random_bytes(2);

		vector<uint8_t> l_full_input(l_input.size() + l_knowns.size());

		std::copy(l_input.begin(), l_input.end(), l_full_input.begin());
		std::copy(l_knowns.begin(), l_knowns.end(), l_full_input.begin() + l_input.size());

		vector<uint8_t> l_entangled(l_input.size() + l_knowns.size());

		const uint8_t RESOLUTION_IN_BITS = 7;

		compression::byte_entangler l_entangler(RESOLUTION_IN_BITS, l_input.size());
		l_entangler.push_back(new compression::byte_entangler(8, l_knowns.size()));

		l_entangler.link(l_full_input, l_entangled);
		l_entangler.transform();

		vector<uint8_t> l_detangled(l_entangled.size());

		compression::byte_detangler l_detangler(RESOLUTION_IN_BITS, l_input.size());
		for (int i = 0; i < l_knowns.size(); i++)
			l_detangler.push_back(new compression::byte_detangler(8, 1, l_knowns[i]));

		l_detangler.link(l_entangled, l_detangled);
		bool l_detangling_successful = l_detangler.transform();

		std::cout << "Detangling valid: " << to_string(l_detangling_successful) << std::endl;
		std::cout << to_string(l_full_input) << std::endl;
		std::cout << to_string(l_detangled) << std::endl;
		std::cin.get();
	}
}

void test_compressor()
{
	const int BLOCK_NUM_INPUT_PLAINTEXTS = 10;
	const int NUM_BLOCKS = 3;
	const int ENTANGLED_INPUT_BIT_RESOLUTION = 7;

	vector<uint16_t> l_known_plaintexts_per_block = {1, 1, 3};
	vector<vector<uint8_t>> l_known_plaintexts_per_block_bit_resolution = {
		{4},
		{4},
		{8, 8, 5},
	};

	uint16_t l_total_known_plaintexts = 0;
	for (int i = 0; i < l_known_plaintexts_per_block.size(); i++)
		l_total_known_plaintexts += l_known_plaintexts_per_block[i];

	vector<vector<uint8_t>> l_per_block_known_plaintexts;

	vector<uint8_t> l_entangler_input(NUM_BLOCKS * BLOCK_NUM_INPUT_PLAINTEXTS + l_total_known_plaintexts);
	vector<uint8_t> l_detangler_input(NUM_BLOCKS * BLOCK_NUM_INPUT_PLAINTEXTS + l_total_known_plaintexts);
	vector<uint8_t> l_detangler_output(NUM_BLOCKS * BLOCK_NUM_INPUT_PLAINTEXTS + l_total_known_plaintexts);

	vector<uint8_t>::iterator l_entangler_input_insertion_iterator = l_entangler_input.begin();

	compression::byte_transformer l_entangler;
	compression::byte_transformer l_detangler;

	for (int i = 0; i < NUM_BLOCKS; i++)
	{
		vector<uint8_t> l_random_input_plaintexts = random_bytes(BLOCK_NUM_INPUT_PLAINTEXTS);
		vector<uint8_t> l_random_known_plaintexts = random_bytes(l_known_plaintexts_per_block[i]);
		l_entangler_input_insertion_iterator = std::copy(l_random_input_plaintexts.begin(), l_random_input_plaintexts.end(), l_entangler_input_insertion_iterator);
		l_entangler_input_insertion_iterator = std::copy(l_random_known_plaintexts.begin(), l_random_known_plaintexts.end(), l_entangler_input_insertion_iterator);
		l_per_block_known_plaintexts.push_back(l_random_known_plaintexts);
		l_entangler.push_back(new compression::byte_entangler(ENTANGLED_INPUT_BIT_RESOLUTION, BLOCK_NUM_INPUT_PLAINTEXTS));
		l_detangler.push_back(new compression::byte_detangler(ENTANGLED_INPUT_BIT_RESOLUTION, BLOCK_NUM_INPUT_PLAINTEXTS));
		for (int j = 0; j < l_known_plaintexts_per_block_bit_resolution[i].size(); j++)
		{
			l_entangler.push_back(new compression::byte_entangler(l_known_plaintexts_per_block_bit_resolution[i][j]));
			l_detangler.push_back(new compression::byte_detangler(l_known_plaintexts_per_block_bit_resolution[i][j], 1, l_random_known_plaintexts[j]));
		}
	}

	l_entangler.link(l_entangler_input, l_detangler_input, -1);
	l_detangler.link(l_detangler_input, l_detangler_output, -1);

	l_entangler.transform();
	bool l_detangling_successful = l_detangler.transform();

	std::cout << to_string(l_entangler_input) << std::endl;
	std::cout << to_string(l_detangler_output) << std::endl;
	
}

int main()
{
	while (true)
	{
		test_compressor();
		std::cin.get();
	}
}
