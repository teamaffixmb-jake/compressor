#pragma once
#include "affix-base/pch.h"
#include "affix-base/ptr.h"

namespace compression
{
	class transform
	{
	protected:
		size_t m_index = 0;
		std::vector<uint8_t>* m_input;
		std::vector<uint8_t>* m_output;
		affix_base::data::ptr<transform> m_next = nullptr;

	public:
		virtual ~transform();
		transform(std::vector<uint8_t>& a_input, std::vector<uint8_t>& a_output, const size_t& a_index);

	public:
		virtual void entangle();
		virtual bool detangle();

	public:
		void link(std::vector<uint8_t>& a_input, std::vector<uint8_t>& a_output);
		void append(const affix_base::data::ptr<transform>& a_next);

	};
}
