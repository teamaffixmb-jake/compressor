#include "affix-base/pch.h"
#include "byte_entangler.h"
#include "data_routines.h"

using namespace compression;

byte_entangler::~byte_entangler()
{

}

byte_entangler::byte_entangler(
	const uint8_t& a_max_output_resolution_in_bits,
	const size_t& a_transformers_to_instantiate
) :
	byte_transformer(a_max_output_resolution_in_bits)
{
	if (a_transformers_to_instantiate > 1)
		m_next = new byte_entangler(a_max_output_resolution_in_bits, a_transformers_to_instantiate - 1);
}

bool byte_entangler::transform()
{
	compression::entangle(*m_input, m_index, m_output->at(m_index), m_output_gate);
	if (m_next != nullptr)
		return m_next->transform();
	return true;
}
