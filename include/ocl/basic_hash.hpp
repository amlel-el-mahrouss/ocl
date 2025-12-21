#ifndef __OCL_CORE_BASIC_HASH
#define __OCL_CORE_BASIC_HASH

#include <ocl/detail/config.hpp>

/// @brief OCL equivalence namespace.
namespace ocl
{
	template <class T>
	struct basic_hash final
	{
		using result_type = typename T::result_type;
		using type		  = T;

		// AMLALE: If it throws, we can't compute the hash correctly.
		constexpr result_type hash() noexcept
		{
			return type{}.hash();
		}
	};
}

#endif