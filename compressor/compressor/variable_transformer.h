#pragma once
#include "transformer.h"

namespace compression
{
	class variable_transformer : public transformer
	{
	public:
		virtual ~variable_transformer();
		variable_transformer(
			const uint8_t& a_output_resolution_in_bits
		);

	public:
		virtual void entangle();
		virtual bool detangle();

	protected:
		bool next_valid_plaintext();
		bool next_plaintext();
		bool plaintext_is_valid();

	};
}
