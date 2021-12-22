#pragma once
#include "affix-base/pch.h"
#include "affix-base/ptr.h"

namespace compression
{
	class byte_transformer
	{
	protected:
		affix_base::data::ptr<byte_transformer> m_next = nullptr;

	protected:
		size_t m_index = 0;
		std::vector<uint8_t>* m_input = nullptr;
		std::vector<uint8_t>* m_output = nullptr;

	protected:
		uint8_t m_output_gate = 0xFF;

	public:
		virtual ~byte_transformer();
		byte_transformer(
			const uint8_t& a_max_output_resolution_in_bits = 8
		);

	public:
		virtual bool transform();

	public:
		virtual void link(
			std::vector<uint8_t>& a_input,
			std::vector<uint8_t>& a_output,
			const size_t& a_index = 0);

		virtual void push_back(
			const affix_base::data::ptr<byte_transformer>& a_next
		);

	};
}
