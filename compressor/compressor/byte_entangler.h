#pragma once
#include "byte_transformer.h"

namespace compression
{
	class byte_entangler: public byte_transformer
	{
	public:
		virtual ~byte_entangler();
		byte_entangler(
			const uint8_t& a_max_output_resolution_in_bits = 8,
			const size_t& a_transformers_to_instantiate = 1
		);

	public:
		virtual bool transform();

	};
}
