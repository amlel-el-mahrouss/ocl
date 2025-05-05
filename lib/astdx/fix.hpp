/*
 * File: fix.hpp
 * Purpose: Financial Information Protocol implementation in C++.
 * Author: Amlal El Mahrouss (amlal@nekernel.org)
 * Copyright 2025, Amlal El Mahrouss all rights reserved.
 */

#ifndef _STDX_FIX_HPP
#define _STDX_FIX_HPP

#include <cstdint>
#include <cstddef>
#include <cassert>
#include <string>
#include <arpa/inet.h>
#include <sys/socket.h>

namespace astdx::fix
{
	struct fix_reader;
	struct fix_writer;
	struct fix_visitor;
	struct fix_range;
	struct fix_metadata;

	/// @brief Buffer+Length structure
	typedef fix_range* fix_range_ptr_t;

	struct fix_range final
	{
		char*	 ascii_bytes_;
		uint16_t length_;
	};

	/// @brief Convert range to usable string.
	inline std::string to_string(fix_range& range) noexcept
	{
		assert(range.length_ > 0);
		return std::string(range.ascii_bytes_, range.length_);
	}

	struct fix_metadata final
	{
		std::string begin_string_;
		size_t		body_len_;
		uint16_t	msg_type_;
		uint32_t	msg_seq_num_;
		uint32_t	sender_comp_id_;
		uint32_t	target_comp_id_;
		std::string send_time_;
		std::string ci_ord_id_;
		uint16_t	side_;
		uint16_t	security_type_;
		std::string symbol_;
		uint32_t	order_qty_;
		uint16_t	order_type_;
		uint64_t	price_;
		uint64_t	time_in_force_;
		uint32_t	checksum_;
	};
} // namespace astdx::fix

#endif // ifndef _STDX_FIX_HPP
