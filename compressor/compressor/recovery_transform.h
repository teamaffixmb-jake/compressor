#pragma once
#include "transform.h"

namespace compression
{
	class recovery_transform : public transform
	{
	protected:
		uint8_t m_truncation_operand;

	public:
		virtual ~recovery_transform();
		recovery_transform(std::vector<uint8_t>& a_input, std::vector<uint8_t>& a_output, const size_t& a_index, const uint8_t& a_truncation_operand);

	public:
		virtual void entangle();
		virtual bool detangle();

	protected:
		void entangle(const std::vector<uint8_t>& a_input, const size_t& a_index, uint8_t& a_output);

	protected:
		bool next_valid_plaintext();
		bool next_plaintext();
		bool plaintext_is_valid();

	};
}
