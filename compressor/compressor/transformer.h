#pragma once
#include "affix-base/pch.h"
#include "affix-base/ptr.h"

namespace compression
{
	class transformer
	{
	protected:
		size_t m_index = 0;
		std::vector<uint8_t>* m_input = nullptr;
		std::vector<uint8_t>* m_output = nullptr;

	protected:
		uint8_t m_output_gate = 0xFF;

	public:
		virtual ~transformer();
		transformer(
			const uint8_t& a_max_output_resolution_in_bits = 8
		);

	public:
		virtual void link(
			std::vector<uint8_t>& a_input,
			std::vector<uint8_t>& a_output,
			const size_t& a_index = 0);
		void append(
			const affix_base::data::ptr<transformer>& a_next
		);

	};
}
