#include "compressor/compression_routines.h"
#include "cryptopp/osrng.h"

using std::vector;

vector<uint8_t> random_bytes(const size_t& a_size)
{
	vector<uint8_t> l_result(a_size);
	CryptoPP::AutoSeededRandomPool l_random;
	l_random.GenerateBlock(l_result.data(), l_result.size());
	return l_result;
}

int main()
{
	vector<uint8_t> l_input = random_bytes(10);
	vector<uint8_t> l_entangled;
	compression::entangle(l_input, l_entangled);

}
