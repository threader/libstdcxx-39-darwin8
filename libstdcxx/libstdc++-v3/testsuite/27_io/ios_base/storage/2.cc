// 2000-12-19 bkoz

// Copyright (C) 2000, 2002, 2003, 2004 Free Software Foundation
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 2, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License along
// with this library; see the file COPYING.  If not, write to the Free
// Software Foundation, 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,
// USA.

// 27.4.2.5 ios_base storage functions

// XXX This test will not work for some versions of irix6 because of
// XXX bug(s) in libc malloc for very large allocations.  However
// XXX -lmalloc seems to work.
// See http://gcc.gnu.org/ml/gcc/2002-05/msg01012.html
// { dg-options "-lmalloc" { target mips*-*-irix6* } }

// This fails on some versions of Darwin 8 because malloc doesn't return
// NULL even if an allocation fails (filed as Radar 3884894).
// { dg-do run { xfail *-*-darwin8.[0-4].* } }

// Allocates too much memory on 64-bit systems
// <rdar://problem/6339271>
// { dg-require-effective-target ilp32 }

#include <sstream>
#include <iostream>
#include <testsuite_hooks.h>

// libstdc++/3129
void test02()
{
  bool test __attribute__((unused)) = true;
  int max = std::numeric_limits<int>::max() - 1;
  std::stringbuf        strbuf;
  std::ios              ios(&strbuf);

  ios.exceptions(std::ios::badbit);

  long l = 0;
  void* v = 0;

  // pword
  ios.pword(1) = v;
  VERIFY( ios.pword(1) == v );
  
  try 
    {
      v = ios.pword(max);
    }
  catch(std::ios_base::failure& obj)
    {
      // Ok.
      VERIFY( ios.bad() );
    }
  catch(...)
    {
      test = false;
      VERIFY( test );
    }
  VERIFY( v == 0 );

  VERIFY( ios.pword(1) == v );
  
  // max is different code path from max-1
  v = &test;
  try 
    {
      v = ios.pword(std::numeric_limits<int>::max());
    }
  catch(std::ios_base::failure& obj)
    {
      // Ok.
      VERIFY( ios.bad() );
    }
  catch(...)
    {
      test = false;
      VERIFY( test );
    }
  VERIFY( v == &test );

  // iword
  ios.iword(1) = 1;
  VERIFY( ios.iword(1) == 1 );
  
  try 
    {
      l = ios.iword(max);
    }
  catch(std::ios_base::failure& obj)
    {
      // Ok.
      VERIFY( ios.bad() );
    }
  catch(...)
    {
      test = false;
      VERIFY( test );
    }
  VERIFY( l == 0 );

  VERIFY( ios.iword(1) == 1 );

  // max is different code path from max-1
  l = 1;
  try 
    {
      l = ios.iword(std::numeric_limits<int>::max());
    }
  catch(std::ios_base::failure& obj)
    {
      // Ok.
      VERIFY( ios.bad() );
    }
  catch(...)
    {
      test = false;
      VERIFY( test );
    }
  VERIFY( l == 1 );

}

int main(void)
{
  __gnu_test::set_memory_limits();
  test02();
  return 0;
}