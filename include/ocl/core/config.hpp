/*
 * File: core/config.hpp
 * Purpose: Config file of the OCL.
 * Author: Amlal El Mahrouss (amlal@nekernel.org)
 * Copyright 2025, Amlal El Mahrouss, licensed under the Boost Software License.
 */

#pragma once

#include <boost/config.hpp>
#include <boost/core/addressof.hpp>
#include <boost/core/nvp.hpp>
#include <boost/core/demangle.hpp>
#include <boost/core/null_deleter.hpp>
#include <boost/container/allocator.hpp>
#include <boost/assert.hpp>

#include <cassert>

#include <sys/types.h>
#include <unistd.h>

#define OCL_DEPRECATED()		[[deprecated]]
#define OCL_DEPRECATED_MSG(MSG) [[deprecated(MSG)]]

#ifdef __cplusplus
#define OCL_DECL extern "C"
/// DLL/Dylib/So specific macro.
#define OCL_EXPORT_DECL extern "C" BOOST_SYMBOL_EXPORT
#else
#define OCL_DECL
#define OCL_EXPORT_DECL
#endif
