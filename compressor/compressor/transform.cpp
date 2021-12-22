#include "transform.h"
#include "data_routines.h"

using namespace compression;

transform::~transform()
{

}

transform::transform(std::vector<uint8_t>& a_input, std::vector<uint8_t>& a_output, const size_t& a_index) :
	m_index(a_index)
{
	link(a_input, a_output);
}

void transform::entangle()
{

}

bool transform::detangle()
{
	return m_next->detangle();
}

void transform::link(std::vector<uint8_t>& a_input, std::vector<uint8_t>& a_output)
{
	m_input = &a_input;
	m_output = &a_output;
}

void transform::append(const affix_base::data::ptr<transform>& a_next)
{
	m_next = a_next;
}
