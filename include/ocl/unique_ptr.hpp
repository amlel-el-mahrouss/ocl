/*
 * File: unique_pr.hpp
 * Purpose: Unique Pointer helpers.
 * Author: Amlal El Mahrouss (amlal@nekernel.org)
 * Copyright 2025, Amlal El Mahrouss, Licensed under the Boost Software License. Licensed under the BSL 1.0 license
 */

#ifndef __OCL_UNIQUE_PTR
#define __OCL_UNIQUE_PTR

#include <ocl/detail/config.hpp>
#include <memory>

namespace ocl
{
    template<class T, class Del>
    using unique_ptr = std::unique_ptr<T, Del>;
}

#endif // ifndef __OCL_UNIQUE_PTR