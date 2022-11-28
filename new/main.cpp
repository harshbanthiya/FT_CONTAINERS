#include <vector>
#include "includes/vector.hpp"
#include <iostream>
#include <ostream>

#ifndef TEST_NAMESPACE 
#define TEST_NAMESPACE ft
#endif 

void	vector_erase(){
	std::cout << "BEFORE ERASE OF 4\n";
	TEST_NAMESPACE::vector<int> v;
	for (int i = 0; i < 8; i++) v.push_back(i);
	TEST_NAMESPACE::vector<int>::iterator it = v.begin();
	TEST_NAMESPACE::vector<int>::iterator after = v.begin();
	while (it != v.end()){
		std::cout << *it << std::endl;
		it++;
	}
	int i = 0;
	it = v.begin();
	while (i <= 3){
		it++;
		i++;
	}
	v.erase(it);
	std::cout << "AFTER ERASE OF 4\n";
	after = v.begin();
	while (after != v.end()){
		std::cout << *after << std::endl;
		after++;
	}
}

void	vector_insert(){
	TEST_NAMESPACE::vector<int> a;
	TEST_NAMESPACE::vector<int> b;
	TEST_NAMESPACE::vector<int> c;
	TEST_NAMESPACE::vector<int>::iterator it;
	TEST_NAMESPACE::vector<int>::iterator ite;

	std::cout << "---------- 1 ----------"<< std::endl;
	a.push_back(42);
	a.push_back(24);
	a.push_back(3);
	it = a.begin();
	ite = a.end();
	it = a.insert(++it, 500);
	it = a.begin();
	ite = a.end();
	while (it != ite){
		std::cout << *it << std::endl;
		it++;
	}
	std::cout << "---------- 2 ----------"<< std::endl;
	int	x = 42;
	for (int i = 0; i < 10 ; i++) b.push_back(i);
	it = b.begin();
	ite = b.end();
	b.insert((it + 3), 5, x);
	ite = b.end();
	it = b.begin();
	while (it != ite){
		std::cout << *it << std::endl;
		it++;
	}
	std::cout << "---------- 3 ----------"<< std::endl;
	
	TEST_NAMESPACE::vector<int> range;

	for (int i = 42; i < 46 ; i++) range.push_back(i);
	it = range.begin();
	ite = range.end();
	for (int i = 0; i < 10 ; i++) c.push_back(i);
	c.insert(c.begin() + 1, it, ite);
	it = c.begin();
	ite = c.end();
	while (it != ite){
		std::cout << *it << std::endl;
		it++;
	}
}

void	vector_iterators() {
	TEST_NAMESPACE::vector<int>			vect;
	

	for (int i = 42; i < 46 ; i++) vect.push_back(i);
	std::cout << "iterator\n";
	for (TEST_NAMESPACE::vector<int>::iterator it = vect.begin(); it != vect.end(); it++) std::cout << *it << " ";
	std::cout << std::endl;
	std::cout << "reverse iterator\n";
	for (TEST_NAMESPACE::vector<int>::reverse_iterator rit = vect.rbegin() ; rit != vect.rend(); rit++) std::cout << *rit << " ";
	std::cout << std::endl;
	std::cout << "iterator\n";
	for (TEST_NAMESPACE::vector<int>::iterator it = vect.begin(); it != vect.end(); it++) std::cout << *it << " ";
	std::cout << std::endl;
	TEST_NAMESPACE::vector<int>			copy(vect);
	for (TEST_NAMESPACE::vector<int>::iterator it = copy.begin(); it != copy.end(); it++) std::cout <<  *it << " ";
	std::cout << std::endl;
	
}

void  vector_reserve(){
  TEST_NAMESPACE::vector<int>::size_type sz;

  TEST_NAMESPACE::vector<int> foo;
  sz = foo.capacity();
  std::cout << "making foo grow:\n";
  for (int i=0; i<100; ++i) {
    foo.push_back(i);
    if (sz!=foo.capacity()) {
      sz = foo.capacity();
      std::cout << "capacity changed: " << sz << '\n';
    }
  }

  TEST_NAMESPACE::vector<int> bar;
  sz = bar.capacity();
  bar.reserve(100);   // this is the only difference with foo above
  std::cout << "making bar grow:\n";
  for (int i=0; i<100; ++i) {
    bar.push_back(i);
    if (sz!=bar.capacity()) {
      sz = bar.capacity();
      std::cout << "capacity changed: " << sz << '\n';
    }
  }
}

void  vector_empty(){
  TEST_NAMESPACE::vector<int> myvector;
  int sum (0);

  for (int i=1;i<=10;i++) myvector.push_back(i);

  while (!myvector.empty())
  {
     sum += myvector.back();
     myvector.pop_back();
  }

  std::cout << "total: " << sum << '\n';
}

void	vector_at(){
	TEST_NAMESPACE::vector<int> myvector (10);   // 10 zero-initialized ints

  // assign some values:
  for (unsigned i=0; i<myvector.size(); i++)
    myvector.at(i)=i;

  std::cout << "myvector contains:";
  for (unsigned i=0; i<myvector.size(); i++)
    std::cout << ' ' << myvector.at(i);
  std::cout << '\n';
}

void	vector_front(){
  TEST_NAMESPACE::vector<int> myvector;

  myvector.push_back(78);
  myvector.push_back(16);

  // now front equals 78, and back 16

  myvector.front() -= myvector.back();

  std::cout << "myvector.front() is now " << myvector.front() << '\n';
}

void  vector_back(){
  TEST_NAMESPACE::vector<int> myvector;

  myvector.push_back(10);

  while (myvector.back() != 0)
  {
    myvector.push_back ( myvector.back() -1 );
  }

  std::cout << "myvector contains:";
  for (unsigned i=0; i<myvector.size() ; i++)
    std::cout << ' ' << myvector[i];
  std::cout << '\n';
}

void	vector_assign(){
  TEST_NAMESPACE::vector<int> first;
  TEST_NAMESPACE::vector<int> second;
  TEST_NAMESPACE::vector<int> third;

  first.assign (7,100);             // 7 ints with a value of 100

  TEST_NAMESPACE::vector<int>::iterator it;
  it=first.begin()+1;

  second.assign (it,first.end()-1); // the 5 central values of first

  int myints[] = {1776,7,4};
  third.assign (myints,myints+3);   // assigning from array.

  std::cout << "Size of first: " << int (first.size()) << '\n';
  std::cout << "Size of second: " << int (second.size()) << '\n';
  std::cout << "Size of third: " << int (third.size()) << '\n';
}

void	vector_capacity_and_size(){
  TEST_NAMESPACE::vector<int> myvector;

  // set some content in the vector:
  for (int i=0; i<100; i++) myvector.push_back(i);

  std::cout << "size: " << (int) myvector.size() << '\n';
  std::cout << "capacity: " << (int) myvector.capacity() << '\n';
  std::cout << "max_size: " << (int) myvector.max_size() << '\n';
}

void	vector_get_alloc(){
  TEST_NAMESPACE::vector<int> myvector;
  int * p;
  unsigned int i;
  
  // allocate an array with space for 5 elements using vector's allocator:
  p = myvector.get_allocator().allocate(5);
  
  // construct values in-place on the array:
  for (i=0; i<5; i++) myvector.get_allocator().construct(&p[i],i);
  
  std::cout << "The allocated array contains:";
  for (i=0; i<5; i++) std::cout << ' ' << p[i];
  std::cout << '\n';
  
  // destroy and deallocate:
  for (i=0; i<5; i++) myvector.get_allocator().destroy(&p[i]);
  myvector.get_allocator().deallocate(p,5);
}

void	vector_tests(){
	std::cout << "______________ VECTOR _______________\n";

	std::cout << "--- Test erase ---" << std::endl;
	vector_erase();
	std::cout << "--- Test insert ---" << std::endl;
	vector_insert();
	std::cout << "--- Test iterators ---" << std::endl;
	vector_iterators();
	std::cout << "--- Test reserve ---" << std::endl;
	vector_reserve();
	std::cout << "--- Test empty ---" << std::endl;
	vector_empty();
	std::cout << "--- Test at ---" << std::endl;
	vector_at();
	std::cout << "--- Test front ---" << std::endl;
	vector_front();
	std::cout << "--- Test back ---" << std::endl;
	vector_back();
	std::cout << "--- Test assign ---" << std::endl;
	vector_assign();
	std::cout << "--- Test size/capacity/max_size ---" << std::endl;
	vector_capacity_and_size();
	std::cout << "--- Test get_allocator ---" << std::endl;
	vector_get_alloc();
}

int main()
{
    vector_tests();
    return (0);
}