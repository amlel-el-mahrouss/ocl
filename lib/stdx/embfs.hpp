/* 
 * File: embfs.hpp
 * Purpose: Embedded File System.
 * Author: Amlal El Mahrouss, 
 * Copyright 2025, Amlal El Mahrouss all rights reserved. 
 */

#ifndef _STDX_EMBDFS_HPP
#define _STDX_EMBDFS_HPP

#include <new>
#include <cstdint>
#include <cstddef>

/// @brief A Fail-safe filesystem designed for tiny MCUs.
/// @author Amlal EL Mahrouss (amlal@nekernel.org)

namespace stdx::freestanding
{
    struct embdfs_superblock;
    struct embdfs_inode;
}

#endif // ifndef _STDX_EMBDFS_HPP