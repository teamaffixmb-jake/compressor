#include "transformer.h"
#include "data_routines.h"

using namespace compression;

transformer::~transformer()
{

}

transformer::transformer(
	const uint8_t& a_max_output_resolution_in_bits
)
{
	// ENSURE THE VALUE OF a_max_output_resolution_in_bits IS BETWEEN 0 AND 8
	assert(a_max_output_resolution_in_bits >= 0 && a_max_output_resolution_in_bits <= 8);
	
	// CALCULATE OUTPUT TRUNCATION VALUE
	m_output_gate = 0xFF >> (8 - a_max_output_resolution_in_bits);
	
}

void transformer::link(
	std::vector<uint8_t>& a_input,
	std::vector<uint8_t>& a_output,
	const size_t& a_index)
{
	m_input = &a_input;
	m_output = &a_output;
	m_index = a_index;
	if (m_next != nullptr)
		m_next->link(a_input, a_output, a_index + 1);
}

void transformer::append(const affix_base::data::ptr<transformer>& a_next)
{
	m_next = a_next;
}
