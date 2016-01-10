#include <cassert>
#include "shared_ptr.hpp"

struct C {
  int a;
  int b;
};

int main() {
  C* c1 = new C;
  c1->a = 1;
  c1->b = 2;

  // Constructors
  SharedPtr<C> a;
  assert(!a);
  SharedPtr<C> b(nullptr);
  assert(!b);
  SharedPtr<C> c(c1);
  assert(c);
  SharedPtr<C> d(c);
  assert(d);
  SharedPtr<C> n(a);
  assert(!n);

  // Test operator=
  SharedPtr<C> e;
  e = c;
  assert(e.get() == c.get());

  // Test operator==
  assert(a == b);
  assert(a == c != true);

  // Test operator<
  assert(a < c.get());
  assert(a < c);

  // Test operator*
  assert(&(*c) == (c.get()));

  // Test operator->
  assert((c->a) = c.get()->a);

  // Test operator bool
  if (!c) {
    assert(1 == 2);
  }

  // Test reset
  C* c2 = new C;
  c2->a = 1;
  c2->b = 2;

  C* c3 = new C;
  c3->a = 3;
  c3->b = 4;

  SharedPtr<C> reset(c2);
  assert(reset.get()->a == c2->a);
  reset.reset(c3);
  assert(reset.get()->a == c3->a);

  // Test unique
  C* c4 = new C;
  c4->a = 3;
  c4->b = 4;

  SharedPtr<C> u1(c4);
  assert(u1.unique());
  SharedPtr<C> u2(u1);
  assert(!u1.unique());

  return 0;
}
