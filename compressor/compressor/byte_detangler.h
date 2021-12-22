#pragma once
#include "byte_transformer.h"

namespace compression
{
	struct plaintext
	{
		bool m_known = false;
		uint16_t m_value = -1;
		plaintext();
		plaintext(const uint8_t& a_known_value);
	};

	class byte_detangler : public byte_transformer
	{
	public:
		plaintext m_plaintext;

	public:
		virtual ~byte_detangler();
		byte_detangler(
			const uint8_t& a_max_output_resolution_in_bits = 8,
			const size_t& a_transformers_to_instantiate = 1,
			const plaintext& a_plaintext = {}
		);

	public:
		virtual bool transform();

	protected:
		bool next_plaintext();
		bool next_valid_plaintext();
		bool plaintext_valid();

	};
}
