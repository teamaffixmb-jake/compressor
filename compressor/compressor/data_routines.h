#pragma once
#include "affix-base/pch.h"

namespace compression
{
	void entangle(
		const std::vector<uint8_t>& a_plain_text,
		const size_t& a_index,
		uint8_t& a_result,
		const uint8_t& a_output_gate = 0xFF);
}
