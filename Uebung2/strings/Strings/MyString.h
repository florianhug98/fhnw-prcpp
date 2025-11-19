#pragma once

#include <memory>
#include <iostream>

/// <summary>
/// Mutable string class with performance optimization for short strings.
/// All strings are zero-terminated.
/// All implementations must be done in String.cpp.
/// 
/// Author: C. Stamm
/// </summary>
class String {
public:
	constexpr static size_t ShortCapacity = 16;

private:
	size_t m_size;					// string length without terminating zero
	size_t m_capacity;				// data buffer length
	std::unique_ptr<char[]> m_data;	// zero-terminated long string on heap
	char m_short[ShortCapacity];	// zero-terminated short string on stack

public:
	/// <summary>
	/// Standard constructor initializes m_capacity with ShortCapacity and m_size with 0.
	/// At least the first character in m_short has to be a '\0'-character.
	/// </summary>
	String() noexcept;

	/// <summary>
	/// Copy constructor creates a deep copy of s.
	/// </summary>
	String(const String& s) noexcept;
	
	/// <summary>
	/// Move constructor: short strings are copied, long strings are moved.
	/// </summary>
	String(String&& s) noexcept;

	/// <summary>
	/// Creates a deep copy of the string-literal s.
	/// </summary>
	/// <param name="s">zero-terminated C-String</param>
	String(const char s[]);
	
	/// <summary>
	/// Creates a deep copy of the string-literal s up to length len.
	/// </summary>
	/// <param name="s">zero-terminated string-literal with at least len characters</param>
	/// <param name="len">number of valid characters in s</param>
	String(const char s[], size_t len);

	/// <summary>
	/// Returns true if the string size is 0.
	/// </summary>
	bool isEmpty() const noexcept;

	/// <summary>
	/// Returns the string size.
	/// </summary>
	size_t length() const noexcept;

	/// <summary>
	/// Returns the buffer capacity. The bufer capacity cannot be smaller than ShortCapacity.
	/// </summary>
	size_t capacity() const noexcept;
	
	/// <summary>
	/// Returns a substring of range [beg, end).
	/// Throws std::out_of_range exception if beg > m_size.
	/// If end <= beg or end > m_size, then end = m_size.
	/// </summary>
	/// <param name="beg">position of the first character in the substring</param>
	/// <param name="end">position after the last character in the substring</param>
	String substring(size_t beg, size_t end) const;
	
	/// <summary>
	/// Returns an immutable zero-terminated C-String.
	/// </summary>
	const char* toCString() const noexcept;

	/// <summary>
	/// Assigns a deep copy of string s.
	/// </summary>
	/// <returns>this string</returns>
	String& operator=(const String& s) noexcept;
	
	/// <summary>
	/// Move operator: assigns a copy of short strings and moves long strings.
	/// </summary>
	/// <returns>this string</returns>
	String& operator=(String&& s) noexcept;

	/// <summary>
	/// Appends character c to the end of this string.
	/// Might result in reallocation and string copy.
	/// </summary>
	/// <returns>this string</returns>
	String& operator+=(char c) noexcept;

	/// <summary>
	/// Appends string s to the end of this string
	/// Might result in reallocation and string copy.
	/// </summary>
	/// <returns>this string</returns>
	String& operator+=(const String& s) noexcept;

	/// <summary>
	/// Returns the concatenation of this string with character c.
	/// </summary>
	/// <param name="c">appends character c to the end</param>
	String operator+(char c) const noexcept;

	/// <summary>
	/// Returns the concatenation of this string with string s.
	/// </summary>
	/// <param name="s">appends string s to the end</param>
	String operator+(const String& s) const noexcept;

	/// <summary>
	/// Returns the character at position i.
	/// Can return zero-termination.
	/// Throws std::out_of_range exception if i > size.
	/// </summary>
	/// <param name="i">character position</param>
	char operator[](size_t i) const;
	
	/// <summary>
	/// Returns a reference to the character at position i.
	/// Can return a reference to zero-termination (the behavior is undefined if this character 
	/// is modified to any value other '\0').
	/// Throws std::out_of_range exception if i > size.
	/// </summary>
	/// <param name="i">character position</param>
	char& operator[](size_t i);

	/// <summary>
	/// Compares two strings. The ordering comparisons are done lexicographically.
	/// </summary>
	/// <param name="s">rhs string</param>
	/// <returns>weak total ordering</returns>
	std::weak_ordering operator<=>(const String& s) const noexcept;

	/// <summary>
	/// Compares two strings. The ordering comparisons are done lexicographically.
	/// Two string are equal if both the size of lhs and rhs are equal and each character 
	/// in lhs has an equivalent character in rhs at the same position.
	/// </summary>
	/// <param name="s">rhs string</param>
	/// <returns>true if both string views are equal, else false</returns>
	bool operator==(const String& s) const noexcept { return std::is_eq(*this <=> s); }

	/// <summary>
	/// Iterator pointing to the first character.
	/// </summary>
	const char* begin() const { return m_data ? m_data.get() : m_short; }
	
	/// <summary>
	/// Iterator pointing to the character after the last.
	/// </summary>
	const char* end() const { return begin() + m_size; }
	
	/// <summary>
	/// Output stream operator
	/// </summary>
	/// <param name="os">output stream</param>
	/// <param name="s">string</param>
	/// <returns>os</returns>
	friend std::ostream& operator<<(std::ostream& os, const String& s) {
		return os << s.begin();
	}

private:/// <summary>
	/// Ensures the specified capacity.
	/// If a new array is allocated on heap, then the old array content is copied to the new array and
	/// at least the first character of m_short is set to '\0'.
	/// </summary>
	/// <param name="capacity">new capacity</param>
	void ensureCapacity(size_t capacity);

};
