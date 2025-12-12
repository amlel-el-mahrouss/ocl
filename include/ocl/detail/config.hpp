/*
 * File: detail/config.hpp
 * Purpose: Config file of the OCL.CORE library.
 * Author: Amlal El Mahrouss (amlal@nekernel.org)
 * Copyright 2025, Amlal El Mahrouss, licensed under the Boost Software License.
 */

#ifndef __OCL_CORE_CONFIG
#define __OCL_CORE_CONFIG

#include <boost/config.hpp>

#ifndef __OCL_FREESTANDING
#include <boost/core/addressof.hpp>
#include <boost/core/nvp.hpp>
#include <boost/core/demangle.hpp>
#include <boost/core/null_deleter.hpp>
#include <boost/container/allocator.hpp>
#include <boost/assert.hpp>
#endif

#define OCL_DEPRECATED()		[[deprecated]]
#define OCL_DEPRECATED_MSG(MSG) [[deprecated(MSG)]]

#if 202002L > __cplusplus
#error !! OCL.Core works with C++20 and greater !!
#endif

#ifdef __cplusplus
#define OCL_DECL extern "C"
/// DLL/Dylib/So specific macro.
#define OCL_EXPORT_DECL extern "C" __attribute__((visibility("default")))
#else
#define OCL_DECL
#define OCL_EXPORT_DECL
#endif

#ifdef _WIN32
#define OCL_USE_CRLF_ENDINGS 1
#define OCL_WINDOWS			 1
#endif

#ifndef OCL_WINDOWS
#ifndef __OCL_FREESTANDING
#include <unistd.h>
#endif
#endif

#if OCL_WANTS_PRAGMA_ONCE
#define OCL_HAS_PRAGMA_ONCE 1
#endif

#endif