#include "recovery_transform.h"
#include "data_routines.h"

using namespace compression;

recovery_transform::~recovery_transform()
{

}

recovery_transform::recovery_transform(std::vector<uint8_t>& a_input, std::vector<uint8_t>& a_output, const size_t& a_index, const uint8_t& a_truncation_operand) :
	transform(a_input, a_output, a_index),
	m_truncation_operand(a_truncation_operand)
{

}

void recovery_transform::entangle()
{
	entangle(*m_input, m_index, m_output->at(m_index));
}

bool recovery_transform::detangle()
{
	
}

void recovery_transform::entangle(const std::vector<uint8_t>& a_input, const size_t& a_index, uint8_t& a_output)
{
	compression::entangle(a_input, a_index, a_output);
	a_output &= m_truncation_operand;
}

bool recovery_transform::next_valid_plaintext()
{

}

bool recovery_transform::next_plaintext()
{
	bool l_last_guess = m_input->at(m_index) == 255;
	m_input->at(m_index)++;
	return plaintext_is_valid();
}

bool recovery_transform::plaintext_is_valid()
{
	uint8_t l_entangled = 0;
	entangle(a_plain_text, a_index, l_entangled);
	return l_entangled == a_entangled;
	
}
