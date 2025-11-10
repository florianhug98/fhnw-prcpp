#pragma once

#include <iostream>
#include <exception>
#include <compare>

/// <summary>
/// Leightweight string wrapper with string length.
/// This wrapper is not the owner of the string and does never allocate and free memory on heap.
/// All implementations must be done inside this file.
/// 
/// Author: Florian Hug
/// </summary>
class StringView {
	const char* m_data;	// string (character sequence) of length m_size (or longer, zero termination is not guaranteed)
	size_t m_size;		// string length (without terminating zero)

public:
	/// <summary>
	/// Standard constructor. Set data to nullptr and size to 0.
	/// </summary>
	constexpr StringView() noexcept : m_data(nullptr), m_size(0) {};
	
	constexpr StringView(const StringView& s) noexcept = default;
	
	/// <summary>
	/// Creates string view of a valid C-String. Throws an std::invalid_argument exception for an invalid string literal.
	/// </summary>
	/// <param name="s">zero terminated C-String</param>
		constexpr StringView(const char* s)
		: m_data(s), m_size(s ? strLen(s) : throw std::invalid_argument("invalid string literal")) {}

	
	/// <summary>
	/// Creates string view of a string literal. Throws an std::invalid_argument exception for an invalid string literal.
	/// </summary>
	/// <param name="s">string literal with at least len characters</param>
	/// <param name="len">number of valid characters in s</param>
	constexpr StringView(const char* s, size_t len)
		: m_data(s), m_size(s ? len : throw std::invalid_argument("invalid string literal")) {}

	/// <summary>
	/// Returns true if the string view size is 0.
	/// </summary>
	constexpr bool isEmpty() const noexcept {
		return m_size == 0;
	}

	/// <summary>
	/// Returns string size view.
	/// </summary>
	constexpr size_t length() const noexcept {
		return m_size;
	}
	
	/// <summary>
	/// Moves the start of the resulting string view forward by n characters.
	/// Throws std::out_of_range exception if n > size.
	/// </summary>
	/// <param name="n">number of characters to remove from the start of the string view</param>
	constexpr StringView removePrefix(size_t n) const {
		if (n > m_size) {
			throw std::out_of_range("removePrefix: n > size");
		}
		return {m_data + n, m_size - n};
	}

	/// <summary>
	/// Moves the end of the resulting string view backward by n characters.
	/// Throws std::out_of_range exception if n > size.
	/// </summary>
	/// <param name="n">number of characters to remove from the end of the string view</param>
	constexpr StringView removeSuffix(size_t n) const {
		if (n > m_size) {
			throw std::out_of_range("removeSuffix: n > size");
		}
		return {m_data, m_size - n};
	}

	/// <summary>
	/// Returns pointer to string.
	/// </summary>
	constexpr const char* data() const {
		return m_data;
	}

	StringView& operator=(const StringView& s) noexcept = default;
	
	/// <summary>
	/// Returns character at position i.
	/// Throws std::out_of_range exception if i >= size.
	/// </summary>
	/// <param name="i">character position</param>
	constexpr char operator[](size_t i) const {
		if (i >= m_size) {
			throw std::out_of_range("");
		}
		return *(m_data + i);
	}
	
	/// <summary>
	/// Compares two string views. The ordering comparisons are done lexicographically.
	/// </summary>
	/// <param name="s">rhs string view</param>
	/// <returns>weak total ordering</returns>
	constexpr std::weak_ordering operator<=>(const StringView& s) const noexcept {
		size_t min_len = m_size < s.m_size ? m_size : s.m_size;
		for (size_t i = 0; i < min_len; ++i) {
			if (m_data[i] < s.m_data[i]) {
				return std::weak_ordering::less;
			}
			if (m_data[i] > s.m_data[i]) {
				return std::weak_ordering::greater;
			}
		}
		return m_size <=> s.m_size;
	}

	/// <summary>
	/// Compares two string views.
	/// Two string are equal if both the size of lhs and rhs are equal and each character 
	/// in lhs has an equivalent character in rhs at the same position.
	/// </summary>
	/// <param name="s">rhs string view</param>
	/// <returns>true if both string views are equal, else false</returns>
	bool operator==(const StringView& s) const noexcept { return std::is_eq(*this <=> s); }

	/// <summary>
	/// Iterator pointing to the first character.
	/// </summary>
	constexpr const char* begin() const { return m_data; }

	/// <summary>
	/// Iterator pointing to the character after the last.
	/// </summary>
	constexpr const char* end() const { return m_data + m_size; }

	/// <summary>
	/// Output stream operator
	/// </summary>
	/// <param name="os">output stream</param>
	/// <param name="s">string view</param>
	/// <returns>os</returns>
	friend std::ostream& operator<<(std::ostream& os, const StringView& s) {
		for (const char c : s) os << c;
		return os;
	}

private:
	/// <summary>
	/// Counts the number of characters in C-String s.
	/// </summary>
	/// <param name="s">s must be a zero terminated string literal</param>
	/// <returns>the number of characters in s without terminating zero character</returns>
	constexpr static size_t strLen(const char s[]) {
		size_t len = 0;
		while (s[len] != '\0') ++len;
		return len;
	}
};
