/* 
  string checksum example
  written by Amlal El Mahrouss.
  licensed under GPL-2 license
 */

#include <stdx>

extern "C" {
#  include <string.h>
}

static const char do_hash(const char* in)
{
  int hash = 0;
  
  for (long index = 0; index < strlen(in); ++index)
  {
    hash += in[index];
  }

  return hash;
}

static auto do_some(const char* recv_data, const char* check_data)
{
  const int hash_to_check = do_hash(check_data); /* here we assume this should match opt_hash */
  const int opt_hash = do_hash(recv_data); /* we assume that the hash is correct */
  
  auto opt = stdx::opt(stdx::eval_eq(hash_to_check, opt_hash)); /* do the compute */
  return opt;
}

/* finally test it */
int main(int argc, char** argv)
{
  // ... let's assume we fetch data from network...
  
  auto opt = do_some("Michigan", "Ohio");
  opt.expect("Checksum failed, Michigan isn't Ohio!");
  
  return 0;
}
