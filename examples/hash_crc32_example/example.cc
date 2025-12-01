#include <hashing/crc_hash.hpp>
#include <io/print.hpp>

int main(int argc, char** argv)
{
    if (argc != 2) return 1;

    std::hash<ocl::crc_hash_trait> hash{};
	ocl::io::print(hash(argv[1]));

	return 0;
}
