#include "data_routines.h"
#include "affix-base/sha.h"

void compression::entangle(const std::vector<uint8_t>& a_plain_text, const size_t& a_index, uint8_t& a_result)
{
	std::vector<uint8_t> l_resized_plain_text = a_plain_text;
	l_resized_plain_text.resize(a_index + 1);
	std::vector<uint8_t> l_hash;
	affix_base::data::sha256_digest(l_resized_plain_text, l_hash, 1);
	a_result = l_hash[0];
}
