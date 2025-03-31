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

/// @brief A Filesystem designed for tiny storage medias.
/// @author Amlal EL Mahrouss (amlal@nekernel.org)

namespace astdx::freestanding
{
	namespace details
	{
		struct embdfs_superblock;
		struct embdfs_inode;

		inline constexpr const size_t g_superblock_name_len_ = 16;

		/// @brief Superblock data structure
		struct embdfs_superblock
		{
			std::int16_t  s_block_mag;
			std::int32_t  s_num_inodes;
			std::int32_t  s_part_size;
			std::int32_t  s_part_used;
			std::int16_t  s_sector_sz;
			std::uint32_t s_inode_start, s_inode_end;
			char		  s_name[g_superblock_name_len_];
		};
	} // namespace details

	/// @brief Creates the library context.
	/// @return Whether it suceeded or not.
	int32_t embdfs_create_context();

	/// @brief Destroys the library context.
	/// @return Whether it suceeded or not.
	int32_t embdfs_destroy_context();
} // namespace astdx::freestanding

#endif // ifndef _STDX_EMBDFS_HPP