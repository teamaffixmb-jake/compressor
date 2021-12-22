#include "variable_transformer.h"
#include "data_routines.h"

using namespace compression;

variable_transformer::~variable_transformer()
{

}

variable_transformer::variable_transformer(
	const uint8_t& a_output_resolution_in_bits) :
	transformer(a_output_resolution_in_bits)
{

}

void variable_transformer::entangle()
{
	compression::entangle(*m_input, m_index, m_output->at(m_index), m_output_gate);
}

bool variable_transformer::detangle()
{
	
}

bool variable_transformer::next_valid_plaintext()
{

}

bool variable_transformer::next_plaintext()
{
	bool l_last_guess = m_input->at(m_index) == 255;
	m_input->at(m_index)++;
	return plaintext_is_valid();
}

bool variable_transformer::plaintext_is_valid()
{
	uint8_t l_entangled = 0;
	compression::entangle(*m_output, m_index, l_entangled, m_output_gate);
	return l_entangled == m_input->at(m_index);
	
}
