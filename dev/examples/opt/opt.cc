/* 
  string checksum example
  written by Amlal El Mahrouss.
  licensed under the MIT license
 */

#include <lib/logic/opt.hpp>
#include <lib/io/print.hpp>
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

	auto opt = snu::opt::opt(snu::opt::eval_eq(hash_to_check, opt_hash)); /* do the compute */
	return opt;
}

/* finally test it */
int main(int argc, char** argv)
{
	// ... let's assume we fetch data from network...

	snu::println("Testing data...");

	auto opt = do_some("Ohio", "Ohio");
	opt.expect("Checksum failed, Ohio isn't Ohio!");


	return 0;
}
