/// Author: Florian Hug

#include "MyString.h"
#include <stdexcept>

static size_t strLen(const char s[]) {
    if (!s) {
        throw std::invalid_argument("null pointer");
    }
    size_t len = 0;
    while (s[len] != '\0') ++len;
    return len;
}

String::String() noexcept
    : m_size(0), m_capacity(ShortCapacity) {
    m_short[0] = '\0';
}

String::String(const String &s) noexcept
    : m_size(s.m_size), m_capacity(s.m_capacity) {
    if (s.m_data) {
        m_data = std::make_unique<char[]>(m_capacity);
    }
    for (int i = 0; i <= m_size; ++i) {
        (*this)[i] = s[i];
    }
}

String::String(String &&s) noexcept
    : m_size(s.m_size), m_capacity(s.m_capacity) {
    if (s.m_data) {
        m_data = std::move(s.m_data);
    } else {
        for (int i = 0; i <= m_size; ++i) {
            (*this)[i] = s[i];
        }
    }

    s.m_size = 0;
    s.m_capacity = ShortCapacity;
    s.m_short[0] = '\0';
}

String::String(const char s[])
    : String(s, strLen(s)) {
}

String::String(const char s[], size_t len)
    : m_size(len), m_short{} {
    if (!s) {
        throw std::invalid_argument("null pointer");
    }
    if (len < ShortCapacity) {
        m_capacity = ShortCapacity;
        for (int i = 0; i < m_size; ++i) {
            (*this)[i] = s[i];
        }
        m_size = len;
    } else {
        m_capacity = len + 1;
        m_data = std::make_unique<char[]>(len + 1);
        for (int i = 0; i < m_size; ++i) {
            (*this)[i] = s[i];
        }
        m_size = len;
    }
}

String &String::operator=(const String &s) noexcept {
    if (this != &s) {
        *this = String(s);
    }

    return *this;
}

String &String::operator=(String &&s) noexcept {
    if (this != &s) {
        std::swap(m_size, s.m_size);
        std::swap(m_capacity, s.m_capacity);
        std::swap(m_data, s.m_data);
        std::swap(m_short, s.m_short);
    }

    return *this;
}


char String::operator[](size_t i) const {
    if (i > m_size) {
        throw std::out_of_range("Index out of range");
    }
    if (m_capacity <= ShortCapacity) {
        return *(m_short + i);
    }
    return *(m_data.get() + i);
}

char &String::operator[](size_t i) {
    if (i > m_size) {
        throw std::out_of_range("Index out of range");
    }
    if (m_capacity <= ShortCapacity) {
        return *(m_short + i);
    }
    return *(m_data.get() + i);
}

String& String::operator+=(char c) noexcept {
    ensureCapacity(m_size + 2);

    (*this)[m_size] = c;
    m_size++;

    (*this)[m_size] = '\0';

    return *this;
}

String& String::operator+=(const String& s) noexcept {
    ensureCapacity(m_size + s.m_size + 1);

    for (int i = 0; i < s.m_size; ++i) {
        (*this)[m_size] = s[i];
        m_size++;
    }

    (*this)[m_size] = '\0';

    return *this;
}

String String::operator+(char c) const noexcept {
    String result(*this);
    return result += c;
}

String String::operator+(const String& s) const noexcept {
    String result(*this);
    return result += s;
}

std::weak_ordering String::operator<=>(const String& s) const noexcept {
    size_t min_len = m_size < s.m_size ? m_size : s.m_size;
    for (size_t i = 0; i < min_len; ++i) {
        if ((*this)[i] < s[i]) {
            return std::weak_ordering::less;
        }
        if ((*this)[i] > s[i]) {
            return std::weak_ordering::greater;
        }
    }
    return m_size <=> s.m_size;
}

String String::substring(size_t beg, size_t end) const {
    if (beg > m_size) {
        throw std::out_of_range("beg > size");
    }

    if (end <= beg || end > m_size) {
        end = m_size;
    }

    return String(toCString() + beg, end - beg);
}

void String::ensureCapacity(size_t capacity) {
    if (capacity <= m_capacity) {
        return;
    }

    auto buf = std::make_unique<char[]>(capacity);

    for (int i = 0; i < m_size; ++i) {
        buf[i] = (*this)[i];
    }

    if (!m_data) {
        m_short[0] = '\0';
    }

    m_data = std::move(buf);
    m_capacity = capacity;
}



const char *String::toCString() const noexcept {
    return m_data ? m_data.get() : m_short;
}


bool String::isEmpty() const noexcept {
    return m_size == 0;
}

size_t String::length() const noexcept {
    return m_size;
}

size_t String::capacity() const noexcept {
    return m_capacity;
}
