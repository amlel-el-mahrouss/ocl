/*
 * File: allocator_system.cc
 * Purpose: Allocator System container.
 * Author: Amlal El Mahrouss (amlal@nekernel.org)
 * Copyright 2025, Amlal El Mahrouss. Licensed under the BSL 1.0 license
 */

#include <lib/memory/allocator_system.hpp>
#include <iostream>

class MyClass final
{
public:
	int a{};
	std::string b{};

	MyClass() : a(0), b("default") 
	{
		std::cout << "MyClass() constructed\n";
	}

	MyClass(int x, std::string y) : a(x), b(std::move(y))
	{
		std::cout << "MyClass(int, string) constructed\n";
	}

	~MyClass()
	{
		std::cout << "~MyClass() destroyed\n";
	}
};

int main()
{
	ocl::standard_allocator_type<MyClass> allocator;

	// Test 1: claim() + unclaim()
	std::cout << "=== Test 1: claim/unclaim ===\n";

	MyClass* raw = allocator.claim();

	std::cout << "raw->a = " << raw->a << ", raw->b = " << raw->b << "\n";
	allocator.unclaim(raw); // Manual delete

	// Test 2: construct() → shared_ptr
	std::cout << "\n=== Test 2: construct (shared_ptr) ===\n";

	auto ptr = allocator.construct<int, std::string>(42, "hello");
	std::cout << "ptr->a = " << ptr->a << ", ptr->b = " << ptr->b << "\n";

	// `shared_ptr` will automatically delete the object
	std::cout << "\n=== End of main ===\n";
}
