#pragma once
#include "transformer.h"

namespace compression
{
	class entangler: public transformer
	{
	protected:
		affix_base::data::ptr<entangler> m_next = nullptr;

	protected:
		size_t m_index = 0;
		std::vector<uint8_t>* m_input = nullptr;
		std::vector<uint8_t>* m_output = nullptr;

	protected:
		uint8_t m_output_gate = 0xFF;

	public:
		virtual ~entangler();
		entangler(
			const uint8_t& a_max_output_resolution_in_bits = 8
		);

	};
}
