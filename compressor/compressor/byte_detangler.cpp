#include "byte_detangler.h"
#include "data_routines.h"
#include <iostream>

using namespace compression;

plaintext::plaintext()
{

}

plaintext::plaintext(
	const uint8_t& a_known_value
)
{
	m_known = true;
	m_value = a_known_value;
}

byte_detangler::~byte_detangler()
{

}

byte_detangler::byte_detangler(
	const uint8_t& a_max_output_resolution_in_bits,
	const size_t& a_transformers_to_instantiate,
	const plaintext& a_known_plaintext
) :
	byte_transformer(a_max_output_resolution_in_bits),
	m_plaintext(a_known_plaintext)
{
	if (a_transformers_to_instantiate > 1)
		m_next = new byte_detangler(a_max_output_resolution_in_bits, a_transformers_to_instantiate - 1, a_known_plaintext);
}

bool byte_detangler::transform()
{
	//std::cout << m_index << std::endl;
	if (m_plaintext.m_known)
	{
		// IF PLAINTEXT IS KNOWN, JUST VERIFY THAT THE OUTPUT SEQUENCE LOOKS CORRECT.
		if (plaintext_valid())
		{
			if (m_next != nullptr)
			{
				return m_next->transform();
			}
			else
			{
				std::cout << "";
				return true;
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		// IF PLAINTEXT UNKNOWN, FIND VALID PLAINTEXT, AND CONTINUE TO NEXT BYTE TRANSFORMER
		while (next_valid_plaintext())
			if (m_next != nullptr)
			{
				if (m_next->transform())
					return true;
			}
			else
			{
				return true;
			}
		return false;
	}
}

bool byte_detangler::next_plaintext()
{
	if (m_plaintext.m_value == 255)
	{
		m_plaintext.m_value = -1;
		return false;
	}
	else
	{
		m_plaintext.m_value++;
		return true;
	}
}

bool byte_detangler::next_valid_plaintext()
{
	while (true)
	{
		if (!next_plaintext())
			return false;

		if (plaintext_valid())
			return true;

	}

}

bool byte_detangler::plaintext_valid()
{
	m_output->at(m_index) = m_plaintext.m_value;
	uint8_t l_entangled = 0;
	compression::entangle(*m_output, m_index, l_entangled, m_output_gate);
	return l_entangled == m_input->at(m_index);
}
