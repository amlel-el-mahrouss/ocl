/*
 * File: embfs.hpp
 * Purpose: Embedded File System.
 * Author: Amlal El Mahrouss (founder@snu.systems)
 * Copyright 2025, Amlal El Mahrouss.
 */

#ifndef _SNU_EMBFS_HPP
#define _SNU_EMBFS_HPP

#include <cstdint>
#include <cstddef>

/// @brief A filesystem designed for tiny storage medias.
/// @author Amlal EL Mahrouss (founder@snu.systems)

namespace snu::embfs
{
	namespace traits
	{
		struct embfs_superblock;
		struct embfs_inode;

		inline constexpr const size_t _superblock_name_len	  = 16;
		inline constexpr const size_t _superblock_reserve_len = 462;
		
		inline constexpr const size_t _inode_name_len		  = 128;
		inline constexpr const size_t _inode_arr_len		  = 12;
		inline constexpr const size_t _inode_lookup_len		  = 8;

#ifdef EMBFS_28BIT_LBA
		typedef std::uint32_t lba_t;
#elif defined(EMBFS_48BIT_LBA)
		typedef std::uint64_t lba_t;
#else
		typedef std::uint32_t lba_t;
#endif

		typedef std::int16_t sword_t;
		typedef std::int32_t sdword_t;

		typedef std::uint8_t utf8_char_t;

		/// @brief Superblock data structure
		struct embfs_superblock
		{
			sword_t		s_block_mag;
			sdword_t	s_num_inodes;
			sdword_t	s_part_size;
			sdword_t	s_part_used;
			sdword_t	s_version;
			sword_t		s_sector_sz;
			lba_t		s_inode_start;
			lba_t		s_inode_end;
			utf8_char_t s_name[_superblock_name_len];
			utf8_char_t s_reserved[_superblock_reserve_len];
		};

		/// @brief Indexed node structure.
		/// @brief i_name file name
		/// @brief i_size_virt, i_size_phys: virtual and physical (sector count) size.
		/// @brief i_offset direct block pointer.
		/// @brief i_checksum crc32 checksum.
		/// @brief i_flags_perms flags and permissions
		/// @brief i_acl_* ACL to keep track of inode allocation status.
		struct embfs_inode
		{
			utf8_char_t i_name[_inode_name_len];
			sword_t		i_size_virt, i_size_phys;
			lba_t		i_offset[_inode_lookup_len];
			sword_t		i_checksum, i_flags_perms;
			lba_t		i_acl_creat, i_acl_edit, i_acl_delet;
		};

		/// @brief Indexed node linear array.
		typedef embfs_inode embfs_inode_arr_t[_inode_arr_len];
	} // namespace traits
} // namespace snu::embfs

#endif // ifndef _SNU_EMBFS_HPP