/* 
  String checksum example
  Written by Amlal El Mahrouss.
  Licensed under the Boost Software License
 */

#include <logic/opt.hpp>
#include <io/print.hpp>
#include <utility/crc32.hpp>
#include <string>

static const char do_hash(const std::string& in)
{
	int hash = 0;

	for (long index = 0; index < in.size(); ++index)
	{
		hash += in[index];
	}

	return hash;
}

static auto do_some(const std::string recv_data, const std::string check_data)
{
	const int hash_to_check = do_hash(check_data); /* here we assume this should match opt_hash */
	const int opt_hash		= do_hash(recv_data);  /* we assume that the hash is correct */

	auto opt = ocl::opt(ocl::eval_eq(hash_to_check, opt_hash)); /* do the compute */
	return opt;
}

/* finally test it */
int main(int argc, char** argv)
{
	// ... let's assume we fetch data from network...

	ocl::io::println("Testing data...");

	auto opt = do_some("Foo", "Foo");
	opt.expect("Checksum failed, Foo isn't Foo!");


	return 0;
}
