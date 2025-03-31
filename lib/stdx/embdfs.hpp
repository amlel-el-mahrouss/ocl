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

/// @brief A Filesystem designed for tiny storage.
/// @author Amlal EL Mahrouss (amlal@nekernel.org)

namespace stdx::freestanding
{
	struct embdfs_superblock;
	struct embdfs_inode;

	/// @brief Superblock data structure
	struct embdfs_superblock
	{
		std::int16_t  s_block_mag;
		std::int32_t  s_num_inodes;
		std::int32_t  s_part_size;
		std::int32_t  s_part_used;
		std::int16_t  s_sector_sz;
		std::uint32_t s_inode_start, s_inode_end;
		char		  s_name[16];
	};
} // namespace stdx::freestanding

#endif // ifndef _STDX_EMBDFS_HPP