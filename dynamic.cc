#include <iostream>
#include <cassert>

struct A {
  A(): _value(1) {}
  A(int value) : _value(value) {}

  virtual const int GetValue() { return _value; }
  virtual void Hello() { std::cout << "Hello from A" << std::endl; }
  
 private:
  int _value;
};

struct B : virtual A {
  B(): A(2) {}
  virtual void Hello() { std::cout << "Hello from B" << std::endl; }
};

struct C : virtual B {
  C(): A(3) {}
  virtual void Hello() { std::cout << "Hello from C" << std::endl; }
};

void printHello(A *a) {
  if (!dynamic_cast<B *>(a)) {
    std::cout << "Caught A!" << std::endl;
    a->Hello();
  } else {
    B *b = dynamic_cast<B *>(a);
    if (!dynamic_cast<C *>(b)) {
      std::cout << "Caught B!" << std::endl;
      b->Hello();
    } else {
      std::cout << "Caught C!" << std::endl;
      C *c = dynamic_cast<C *>(b);
      c->Hello();
    }
  }
}

int main(int argc, char **argv)
{
  A *a = new A;
  B *b = new B;
  C *c = new C;

  B& bref = *c;
  C& cref = dynamic_cast<C&>(bref);

  cref.Hello();

  std::cout << "B._value: " << b->GetValue() << std::endl;

  A *ac = dynamic_cast<A *>(c);
  B *bc = dynamic_cast<B *>(c);

  // downcast
  C *cb = dynamic_cast<C *>(b);
  if (!cb) {
    std::cout << "downcast failed" << std::endl;
  } else {
    std::cout << "downcast successful" << std::endl;
  }

  printHello(ac);
  printHello(bc);
  
  return 0;
}
