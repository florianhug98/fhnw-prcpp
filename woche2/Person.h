#pragma once
#include <string>
#include <iostream>

// class: members sind privat
class Person {
  std::string m_name;
  int m_age;

  public:
    Person(const std::string &name, int age);

    // Destructor
    // *this is a reference to the current object while this is a pointer to the current object
    ~Person() {
      std::cout << "dtor of " << *this << std::endl;
    }

    void setName(const std::string &name) { m_name = name; }
    int getAge() const { return m_age; }

    friend std::ostream &operator<<(std::ostream &os, const Person &person) {
      return os << person.m_name << " ist " << person.m_age << " Jahre alt";
    };
};
