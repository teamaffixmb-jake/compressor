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

int main()
{
	while (true)
	{
		vector<uint8_t> l_input = random_bytes(9);
		vector<uint8_t> l_knowns = random_bytes(3);

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
		compression::byte_detangler l_detangler(RESOLUTION_IN_BITS, 9);
		l_detangler.push_back(new compression::byte_detangler(8, 1, l_full_input[9]));
		l_detangler.push_back(new compression::byte_detangler(8, 1, l_full_input[10]));
		l_detangler.push_back(new compression::byte_detangler(8, 1, l_full_input[11]));

		l_detangler.link(l_entangled, l_detangled);
		bool l_detangling_successful = l_detangler.transform();

		std::cout << "Detangling valid: " << to_string(l_detangling_successful) << std::endl;
		std::cout << to_string(l_full_input) << std::endl;
		std::cout << to_string(l_detangled) << std::endl;
		std::cin.get();
	}

}
