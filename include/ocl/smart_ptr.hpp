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
	template <class T, class Del>
	using unique_ptr = std::unique_ptr<T, Del>;

    template<class T, class _Deleter>
    inline auto delete_ptr(T& obj) -> auto { return std::shared_ptr<T>{obj, _Deleter()}; }

    /// @brief Constructs a `null_ptr`, that is, a pointer that isn't deleted from the heap.
    template<class T>
    inline auto null_deleter(T& obj) -> auto { return delete_ptr<T, boost::null_deleter>(obj); }

}

#endif // ifndef __OCL_SMART_PTR