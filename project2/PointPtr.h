#pragma once
#include "Point.h"

struct PointPtr {

  Point* m_p;

  explicit PointPtr(const Point& p) {
    m_p = new Point(p.m_x, p.m_y);
  }

  ~PointPtr() {
    delete m_p;
  }

  Point& operator*() const {
    return *m_p;
  }

  Point* operator->() const {
    return  m_p;
  }


  auto operator<=>(const PointPtr &) const = default;

  friend std::ostream &operator<<(std::ostream &os, const PointPtr& pp) {
    return os << *pp.m_p;
  }
};
