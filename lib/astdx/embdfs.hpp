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

		inline constexpr const size_t _superblock_name_len = 16;

#ifdef EMBDFS_28BIT_LBA
		typedef std::uint32_t lba_t;
#elif defined(EMBDFS_48BIT_LBA)
		typedef std::uint64_t lba_t;
#endif

		typedef std::int16_t sword_t;
		typedef std::int32_t sdword_t;

		typedef std::uint8_t utf8_char_t;

		/// @brief Superblock data structure
		struct embdfs_superblock
		{
			sword_t		s_block_mag;
			sdword_t	s_num_inodes;
			sdword_t	s_part_size;
			sdword_t	s_part_used;
			sword_t		s_sector_sz;
			lba_t		s_inode_start;
			lba_t		s_inode_end;
			utf8_char_t s_name[_superblock_name_len];
		};
	} // namespace details

	/// @brief Creates the library context.
	/// @return Whether it suceeded or not.
	inline int32_t embdfs_create_context()
	{
		return 0;
	}

	/// @brief Destroys the library context.
	/// @return Whether it suceeded or not.
	inline int32_t embdfs_destroy_context()
	{
		return 0;
	}
} // namespace astdx::freestanding

#endif // ifndef _STDX_EMBDFS_HPP