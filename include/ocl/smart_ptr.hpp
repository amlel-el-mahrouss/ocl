/*
 * File: smart_ptr.hpp
 * Purpose: Smart Pointer helpers.
 * Author: Amlal El Mahrouss (amlal@nekernel.org)
 * Copyright 2025, Amlal El Mahrouss, Licensed under the Boost Software License. Licensed under the BSL 1.0 license
 */

#ifndef __OCL_SMART_PTR
#define __OCL_SMART_PTR

#include <boost/core/null_deleter.hpp>
#include <ocl/detail/config.hpp>
#include <ocl/tracked_ptr.hpp>
#include <memory>

namespace ocl
{
	template <class T, class Del = std::default_delete<T>>
	using unique_ptr = std::unique_ptr<T, Del>;

	template <class T>
	using shared_ptr = std::shared_ptr<T>;

    /// @brief Constructs a `delete_ptr`, that is, a pointer that isn't deleted from the heap.
    template<class T>
    inline auto delete_ptr(T* object) -> auto { return shared_ptr<T>{ object, boost::null_deleter{}}; }

}

#endif // ifndef __OCL_SMART_PTR