#include "byte_transformer.h"
#include "data_routines.h"

using namespace compression;

byte_transformer::~byte_transformer()
{

}

byte_transformer::byte_transformer(
	const uint8_t& a_max_output_resolution_in_bits
)
{
	// ENSURE THE VALUE OF a_max_output_resolution_in_bits IS BETWEEN 0 AND 8
	assert(a_max_output_resolution_in_bits >= 0 && a_max_output_resolution_in_bits <= 8);
	
	// CALCULATE OUTPUT TRUNCATION VALUE
	m_output_gate = 0xFF >> (8 - a_max_output_resolution_in_bits);
	
}

bool byte_transformer::transform()
{
	if (m_next != nullptr)
		return m_next->transform();
	return true;
}

void byte_transformer::link(
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

void byte_transformer::push_back(
	const affix_base::data::ptr<byte_transformer>& a_next
)
{
	if (m_next == nullptr)
		m_next = a_next;
	else
		m_next->push_back(a_next);

}
