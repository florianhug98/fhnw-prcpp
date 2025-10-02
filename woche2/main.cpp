#include <iostream>
#include "Point.h"
#include "Person.h"
#include <memory>

//v [in] parameter
// by value für primitive Datentypen
int byVal(int v) {
  ++v;
  return v;
}

//r [inout] parameter
// by reference für speziallfälle wo es auch klar kommuniziert ist das es inout ist!
int byRef(int &r) {
  ++r;
  return r;
}

//r [in] parameter
// by const reference für strukturierte Datentypen
int byConstRef(const int &r) {
  return r;
}

using namespace std;

void divider() {
  cout << "--------------------------------" << endl;
}

int main() {

  {
    array<int,4> numbers = {1,2,3,4};
    int sum = 0;

    for (const int &n : numbers) {
      sum += n;
    }

    cout << sum << endl;
  }

  // {
  //   char s[] = "ABC";
  //
  //   cout << s[1] << endl;
  //
  //   // Zeigerarithmetik
  //   *(s + 1) = 'b';
  //   cout << s[1] << endl;
  // }

  // {
  //   // C String and C Array
  //   char s[] = "ABC";
  //
  //   // s ist ein Pointer auf den "Anfang" des arrays
  //   cout << *s << endl;
  //   cout << s[1] << endl;
  //   cout << sizeof(s) << endl;
  // }

  // {
  //   // Shared pointer
  //   auto sp = make_shared<Person>("Peter", 21);
  //   cout << sp.use_count() << endl;
  //
  //   {
  //     auto sp1 = sp;
  //     cout << sp.use_count() << endl;
  //     cout << sp1.use_count() << endl;
  //   }
  //
  //   // nachdem der Block ended, wird sp1 zerstört und der counter dementsprechend auf 1 gesetzt
  //   cout << sp.use_count() << endl;
  // }

  // {
  //   // unique pointer
  //   // pointer lives on stack - object lives on heap
  //   // unique pointer call delete of Object
  //   auto up = make_unique<Person>("Peter", 21);
  //
  //   // Unique pointer kann man nicht kopieren!
  //   // auto p2 = up;
  //
  //   cout << up << endl;
  //   cout << up->getAge() << endl;
  //   cout << *up << endl;
  // }


  // {
  //   const Person peter("Peter", 21);
  //   Person* p = new Person("Monika", 22);
  //   Person& rp = *p;
  //
  //   Person* xp = &rp;
  //
  //   // Referenz auf einen Personen-Pointer
  //   Person*& rp2 = p;
  //
  //   // pointer von pointer
  //   // zweimal dereferenzieren um ans Objekt zu kommen
  //   Person** pp = &p;
  //
  //   cout << "Size of pointer: " << sizeof(p) << endl;
  //   cout << "Size of object: " << sizeof(*p) << endl;
  //
  //   cout << *pp << endl;
  //   cout << **pp << endl;
  //   cout << (**pp).getAge() << endl;
  //   cout << (*pp)->getAge() << endl;
  //   cout << rp;
  //
  //   delete p;
  // }

  // {
  //   // variable
  //   int var = 10;
  //   //pointer zur variable
  //   int* pointer = &var;
  //   *pointer = 500;
  //
  //   cout << var << endl;
  // }


  // {
  //   // object
  //   const Person peter("Peter", 22);
  //   const Person *moni = new Person("Monika", 22);
  //
  //   // p ist ein pointer auf ein konstantes Personenobject
  //   Person const *p = new Person("Fred", 22);
  //
  //   // p1 ist ein konstanter Pointer auf ein veränderbares Personenobject
  //   Person * const p1 = new Person("Max", 21);
  //   p1->setName("Florian");
  //
  //   cout << *moni << endl;
  //   cout << *p << endl;
  //   cout << *p1 << endl;
  //
  //   delete moni;
  //   delete p1;
  // }


  //{
  // Person *moni = new Person("Moni", 22);
  //
  // // pointer
  // cout << moni << endl;
  //
  // // dereferenzierter Pointer = object
  // cout << *moni << endl;
  //
  // delete moni;
  //}

  // {
  //   int x = 5;
  //
  //   int &rx = x; // Referenz auf x
  //
  //   std::cout << "x = " << x << std::endl;
  //   std::cout << "rx = " << rx << std::endl;
  //   x = 99;
  //   int y = 7;
  //   rx = y; //ry (und somit x) bekommen den Wert von y
  //   std::cout << "x = " << x << std::endl;
  //   std::cout << "rx = " << rx << std::endl;
  // }
  // divider();
  // {
  //   //by value
  //   int x = 5;
  //   int y = byVal(x);
  //
  //   cout << "x = " << x << endl;
  //   cout << "y = " << y << endl;
  // }
  // divider();
  // {
  //   //by reference
  //   int x = 5;
  //   int y = byRef(x);
  //
  //   cout << "x = " << x << endl;
  //   cout << "y = " << y << endl;
  // }
  // divider();
  // {
  //   //by const reference
  //   int x = 5;
  //   int y = byConstRef(x);
  //
  //   cout << "x = " << x << endl;
  //   cout << "y = " << y << endl;
  // }
  // divider();
  // {
  //   const Point p1{3};
  //   const Point p2{0, 4};
  //
  //   cout << p1.m_x << endl;
  //   cout << p1.m_y << endl;
  //
  //   cout << p1.dist(p2) << endl;
  //   cout << p1 << endl;
  // }
  // divider();
  // {
  //   Person peter("Peter", 22);
  //   Person moni("Monika", 21);
  //   cout << peter << endl;
  //   cout << moni << endl;
  //
  //   moni.setName("Moni");
  //   cout << moni << endl;
  //   cout << peter.getAge() << endl;
  // }
}
