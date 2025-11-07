#include "gtest/gtest.h"
#include "MyString.h"
#include <exception>

using namespace std;

constexpr static size_t ShortCapacity = String::ShortCapacity;

/// <summary>
/// Author: C. Stamm
/// </summary>
namespace UnitTest
{
	class StringTest : public ::testing::Test {
	protected:
		String s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11, s12, s13, s14, s15, s16;

		void SetUp() override {
			s1 = String();
			s2 = String("");
			s3 = String("", 0);
			s4 = String("abcd");
			s5 = String("abcd", 0);
			s6 = String("abcd", 2);
			s7 = String("abcd", 4);
			s8 = String("12345678901234567890");
			s9 = String("12345678901234567890", 0);
			s10 = String("12345678901234567890", ShortCapacity - 1);
			s11 = String("12345678901234567890", 20);
			s12 = String(s1);
			s13 = String(s2);
			s14 = String(s4);
			s15 = String(s8);
			s16 = String("12345678901234567890", ShortCapacity);
		}
	};

	TEST_F(StringTest, A0_Construction) {
		ASSERT_EQ(ShortCapacity, s1.capacity());
		ASSERT_EQ(ShortCapacity, s2.capacity());
		ASSERT_EQ(ShortCapacity, s3.capacity());
		ASSERT_EQ(ShortCapacity, s4.capacity());
		ASSERT_EQ(ShortCapacity, s5.capacity());
		ASSERT_EQ(ShortCapacity, s6.capacity());
		ASSERT_EQ(ShortCapacity, s7.capacity());
		ASSERT_EQ(21ull, s8.capacity());
		ASSERT_EQ(ShortCapacity, s9.capacity());
		ASSERT_EQ(ShortCapacity, s10.capacity());
		ASSERT_EQ(21ull, s11.capacity());
		ASSERT_EQ(ShortCapacity, s12.capacity());
		ASSERT_EQ(ShortCapacity, s13.capacity());
		ASSERT_EQ(ShortCapacity, s14.capacity());
		ASSERT_EQ(21ull, s15.capacity());
		ASSERT_EQ(ShortCapacity + 1, s16.capacity());
		ASSERT_THROW(String(nullptr), invalid_argument);
		ASSERT_THROW(String(nullptr, 5), invalid_argument);
		ASSERT_THROW(String(nullptr, 0), invalid_argument);
	}
	TEST_F(StringTest, A1_HeapCorruption) {
		try {
			SetUp();
		} catch (...) {
			FAIL();
		}
	}
	TEST_F(StringTest, A2_Assignment) {
		s11 = s11;
		ASSERT_TRUE(s11.length() < s11.capacity());
		ASSERT_EQ(20ull, s11.length());
		ASSERT_STREQ(s8.toCString(), s11.toCString());
		s1 = s11;
		ASSERT_TRUE(s1.length() < s1.capacity());
		ASSERT_EQ(s11.length(), s1.length());
		ASSERT_STREQ(s8.toCString(), s1.toCString());
		s16 = s16;
		ASSERT_TRUE(s16.length() < s16.capacity());
		ASSERT_EQ(16ull, s16.length());
		ASSERT_STREQ(String(s8.toCString(), ShortCapacity).toCString(), s16.toCString());
		s1 = s16;
		ASSERT_TRUE(s1.length() < s1.capacity());
		ASSERT_EQ(s16.length(), s1.length());
		ASSERT_STREQ(String(s8.toCString(), ShortCapacity).toCString(), s1.toCString());
		s1 = "";
		ASSERT_EQ(ShortCapacity, s1.capacity());
		ASSERT_EQ(0ull, s1.length());
		s6 = s4;
		ASSERT_TRUE(s6.length() < s6.capacity());
		ASSERT_EQ(s4.length(), s6.length());
		ASSERT_STREQ(s4.toCString(), s6.toCString());
		s11 = s4;
		ASSERT_TRUE(s11.length() < s11.capacity());
		ASSERT_EQ(s4.length(), s11.length());
		ASSERT_STREQ(s4.toCString(), s11.toCString());
	}
	TEST_F(StringTest, A3_MoveSemantic) {
		// move ctor
		String s1m(move(s1));
		ASSERT_STREQ("", s1m.toCString());
		ASSERT_STREQ("", s1.toCString());
		ASSERT_EQ(0ull, s1.length());
		ASSERT_EQ(ShortCapacity, s1.capacity());

		String s4m(move(s4));
		ASSERT_STREQ(s7.toCString(), s4m.toCString());
		ASSERT_STREQ("", s4.toCString());
		ASSERT_EQ(0ull, s4.length());
		ASSERT_EQ(ShortCapacity, s4.capacity());

		String s8m(move(s8));
		ASSERT_STREQ(s11.toCString(), s8m.toCString());
		ASSERT_STREQ("", s8.toCString());
		ASSERT_EQ(0ull, s8.length());
		ASSERT_EQ(ShortCapacity, s8.capacity());

		// move operation
		s1 = move(s1m);
		ASSERT_STREQ("", s1.toCString());
		ASSERT_STREQ("", s1m.toCString());
		ASSERT_EQ(0ull, s1m.length());
		ASSERT_EQ(ShortCapacity, s1m.capacity());

		s4 = move(s4m);
		ASSERT_STREQ(s7.toCString(), s4.toCString());
		ASSERT_STREQ("", s4m.toCString());
		ASSERT_EQ(0ull, s4m.length());
		ASSERT_EQ(ShortCapacity, s4m.capacity());

		s8 = move(s8m);
		ASSERT_STREQ(s11.toCString(), s8.toCString());
		ASSERT_STREQ("", s8m.toCString());
		ASSERT_EQ(0ull, s8m.length());
		ASSERT_EQ(ShortCapacity, s8m.capacity());

		s11 = move(s11);
		ASSERT_STREQ(s8.toCString(), s11.toCString());
		ASSERT_EQ(s8.length(), s11.length());
	}
	TEST_F(StringTest, IsEmpty) {
		ASSERT_TRUE(s1.isEmpty());
		ASSERT_TRUE(s2.isEmpty());
		ASSERT_TRUE(s3.isEmpty());
		ASSERT_FALSE(s4.isEmpty());
		ASSERT_TRUE(s5.isEmpty());
		ASSERT_FALSE(s6.isEmpty());
		ASSERT_FALSE(s7.isEmpty());
		ASSERT_FALSE(s8.isEmpty());
		ASSERT_TRUE(s9.isEmpty());
		ASSERT_FALSE(s10.isEmpty());
		ASSERT_FALSE(s11.isEmpty());
		ASSERT_TRUE(s12.isEmpty());
		ASSERT_TRUE(s13.isEmpty());
		ASSERT_FALSE(s14.isEmpty());
		ASSERT_FALSE(s15.isEmpty());
	}
	TEST_F(StringTest, Length) {
		ASSERT_EQ(0ull, s1.length());
		ASSERT_EQ(0ull, s2.length());
		ASSERT_EQ(0ull, s3.length());
		ASSERT_EQ(4ull, s4.length());
		ASSERT_EQ(0ull, s5.length());
		ASSERT_EQ(2ull, s6.length());
		ASSERT_EQ(4ull, s7.length());
		ASSERT_EQ(20ull, s8.length());
		ASSERT_EQ(0ull, s9.length());
		ASSERT_EQ(15ull, s10.length());
		ASSERT_EQ(20ull, s11.length());
		ASSERT_EQ(0ull, s12.length());
		ASSERT_EQ(0ull, s13.length());
		ASSERT_EQ(4ull, s14.length());
		ASSERT_EQ(20ull, s15.length());
	}
	TEST_F(StringTest, Equals) {
		ASSERT_TRUE(s1 == s1);
		ASSERT_TRUE(s1 == s2);
		ASSERT_TRUE(s1 == s3);
		ASSERT_TRUE(s4 == s4);
		ASSERT_TRUE(s1 == s5);
		ASSERT_TRUE(String("ab") == s6);
		ASSERT_TRUE(s4 == s7);
		ASSERT_TRUE(s8 == s8);
		ASSERT_TRUE(s1 == s9);
		ASSERT_TRUE(String("123456789012345") == s10);
		ASSERT_TRUE(s8 == s11);
		ASSERT_TRUE(s1 == s12);
		ASSERT_TRUE(s2 == s13);
		ASSERT_TRUE(s4 == s14);
		ASSERT_TRUE(s8 == s15);
		ASSERT_FALSE(String("ABCD") == s4);
		ASSERT_FALSE(s4 == String("ABCD"));
	}
	TEST_F(StringTest, CString) {
		ASSERT_STREQ(s1.toCString(), s1.toCString());
		ASSERT_STREQ(s1.toCString(), s2.toCString());
		ASSERT_STREQ(s1.toCString(), s3.toCString());
		ASSERT_STREQ(s4.toCString(), s4.toCString());
		ASSERT_STREQ(s1.toCString(), s5.toCString());
		ASSERT_STREQ("ab", s6.toCString());
		ASSERT_STREQ(s4.toCString(), s7.toCString());
		ASSERT_STREQ(s8.toCString(), s8.toCString());
		ASSERT_STREQ(s1.toCString(), s9.toCString());
		ASSERT_STREQ("123456789012345", s10.toCString());
		ASSERT_STREQ(s8.toCString(), s11.toCString());
		ASSERT_STREQ(s1.toCString(), s12.toCString());
		ASSERT_STREQ(s2.toCString(), s13.toCString());
		ASSERT_STREQ(s4.toCString(), s14.toCString());
		ASSERT_STREQ(s8.toCString(), s15.toCString());
	}
	TEST_F(StringTest, SubString) {
		ASSERT_STREQ(s1.toCString(), s4.substring(s4.length(), 0).toCString());
		ASSERT_STREQ(s1.toCString(), s4.substring(s4.length(), 1).toCString());
		ASSERT_STREQ("a", s4.substring(0, 1).toCString());
		ASSERT_STREQ("b", s4.substring(1, 2).toCString());
		ASSERT_STREQ("c", s4.substring(2, 3).toCString());
		ASSERT_STREQ("d", s4.substring(3, 4).toCString());
		ASSERT_STREQ("ab", s4.substring(0, 2).toCString());
		ASSERT_STREQ("bc", s4.substring(1, 3).toCString());
		ASSERT_STREQ("cd", s4.substring(2, 4).toCString());
		ASSERT_STREQ("d", s4.substring(3, 5).toCString());
		ASSERT_STREQ("bcd", s4.substring(1, 5).toCString());
		ASSERT_STREQ("bcd", s4.substring(1, 6).toCString());
		ASSERT_STREQ("bcd", s4.substring(1, 0).toCString());
		ASSERT_STREQ(s1.toCString(), s8.substring(s8.length(), 0).toCString());
		ASSERT_STREQ(s1.toCString(), s8.substring(s8.length(), s8.length() + 1).toCString());
		ASSERT_STREQ("1", s8.substring(0, 1).toCString());
		ASSERT_STREQ("1", s8.substring(10, 11).toCString());
		ASSERT_STREQ("0", s8.substring(19, 20).toCString());
		ASSERT_STREQ("12", s8.substring(0, 2).toCString());
		ASSERT_STREQ("12", s8.substring(10, 12).toCString());
		ASSERT_STREQ("0", s8.substring(19, 21).toCString());
		ASSERT_STREQ("5678901234", s8.substring(4, 14).toCString());
		ASSERT_STREQ("567890", s8.substring(14, 24).toCString());
		ASSERT_STREQ("567890", s8.substring(14, 0).toCString());
		ASSERT_STREQ("234567890123456789", s8.substring(1, 19).toCString());
		ASSERT_STREQ("56789012345", s10.substring(4, 0).toCString());

		ASSERT_THROW(s1.substring(1, 0), out_of_range);
		ASSERT_THROW(s2.substring(1, 0), out_of_range);
		ASSERT_THROW(s4.substring(s4.length() + 1, 0), out_of_range);
		ASSERT_THROW(s8.substring(s8.length() + 1, 0), out_of_range);
	}
	TEST_F(StringTest, Smaller) {
		ASSERT_TRUE(s1 < s4);
		ASSERT_FALSE(s4 < s1);
		ASSERT_TRUE(s1 < s8);
		ASSERT_FALSE(s8 < s1);
		ASSERT_TRUE(s8 < s4);
		ASSERT_FALSE(s4 < s8);
		ASSERT_TRUE(s4 < "abcda");
		ASSERT_TRUE(s4 < "abce");
		ASSERT_TRUE(s4 < "abd");
		ASSERT_TRUE(s4 < "ac");
		ASSERT_TRUE(s4 < "b");
		ASSERT_FALSE(s4 < "ABCD");

		ASSERT_FALSE(s2 < s1);
		ASSERT_FALSE(s1 < s2);
		ASSERT_FALSE(s5 < s1);
		ASSERT_FALSE(s1 < s5);
		ASSERT_FALSE(s9 < s1);
		ASSERT_FALSE(s1 < s9);
		ASSERT_FALSE(s8 < s11);
		ASSERT_TRUE(s10 < s11);
	}
	TEST_F(StringTest, At) {
		// reading
		const String& s1c = static_cast<const String&>(s1);
		const String& s2c = static_cast<const String&>(s2);
		const String& s3c = static_cast<const String&>(s3);
		const String& s4c = static_cast<const String&>(s4);
		const String& s5c = static_cast<const String&>(s5);
		const String& s8c = static_cast<const String&>(s8);
		const String& s9c = static_cast<const String&>(s9);
		const String& s16c = static_cast<const String&>(s16);
		ASSERT_EQ('\0', s1c[0]);
		ASSERT_EQ('\0', s2c[0]);
		ASSERT_EQ('\0', s3c[0]);
		ASSERT_EQ('\0', s5c[0]);
		ASSERT_EQ('\0', s9c[0]);
		ASSERT_EQ('a', s4c[0]);
		ASSERT_EQ('b', s4c[1]);
		ASSERT_EQ('c', s4c[2]);
		ASSERT_EQ('d', s4c[3]);
		ASSERT_EQ('\0', s4c[4]);
		ASSERT_EQ('1', s8c[0]);
		ASSERT_EQ('1', s8c[10]);
		ASSERT_EQ('9', s8c[18]);
		ASSERT_EQ('0', s8c[19]);
		ASSERT_EQ('\0', s8c[20]);
		ASSERT_EQ('\0', s16c[ShortCapacity]);
		ASSERT_EQ('6', s16c[ShortCapacity - 1]);

		ASSERT_THROW(s1c[1], out_of_range);
		ASSERT_THROW(s2c[1], out_of_range);
		ASSERT_THROW(s3c[1], out_of_range);
		ASSERT_THROW(s4c[-1], out_of_range);
		ASSERT_THROW(s5c[1], out_of_range);
		ASSERT_THROW(s8c[-1], out_of_range);
		ASSERT_THROW(s9c[1], out_of_range);

		// writing
		s4[0] = 'A';
		ASSERT_EQ('A', s4[0]);
		s4[3] = 'D';
		ASSERT_EQ('D', s4[3]);
		s4[4] = '\0';
		ASSERT_EQ('\0', s4[4]);
		ASSERT_THROW(s14[-1], out_of_range);

		s8[0] = 'A';
		ASSERT_EQ('A', s8[0]);
		s8[19] = 'D';
		ASSERT_EQ('D', s8[19]);
		s8[20] = '\0';
		ASSERT_EQ('\0', s8[20]);
		ASSERT_THROW(s15[-1], out_of_range);
	}
	TEST_F(StringTest, AppendChar) {
		String s1c = s1 + 'X';
		ASSERT_STREQ("X", s1c.toCString());
		ASSERT_EQ(s1.length() + 1, s1c.length());
		ASSERT_EQ('\0', s1c[s1c.length()]);
		ASSERT_TRUE(s1c.capacity() > s1c.length());

		String s4c = s4 + 'X';
		ASSERT_STREQ("abcdX", s4c.toCString());
		ASSERT_EQ(s4.length() + 1, s4c.length());
		ASSERT_EQ('\0', s4c[s4c.length()]);
		ASSERT_TRUE(s4c.capacity() > s4c.length());

		String s8c = s8 + 'X';
		ASSERT_STREQ("12345678901234567890X", s8c.toCString());
		ASSERT_EQ(s8.length() + 1, s8c.length());
		ASSERT_EQ('\0', s8c[s8c.length()]);
		ASSERT_TRUE(s8c.capacity() > s8c.length());

		String s10c = s10 + 'X';
		ASSERT_STREQ("123456789012345X", s10c.toCString());
		ASSERT_EQ(s10.length() + 1, s10c.length());
		ASSERT_EQ('\0', s10c[s10c.length()]);
		ASSERT_TRUE(s10c.capacity() > s10c.length());

		s1 += 'X';
		ASSERT_STREQ("X", s1.toCString());
		ASSERT_EQ(s1c.length(), s1.length());
		ASSERT_EQ('\0', s1[s1.length()]);
		ASSERT_TRUE(s1.capacity() > s1.length());

		s4 += 'X';
		ASSERT_STREQ("abcdX", s4.toCString());
		ASSERT_EQ(s4c.length(), s4.length());
		ASSERT_EQ('\0', s4[s4.length()]);
		ASSERT_TRUE(s4.capacity() > s4.length());

		s8 += 'X';
		ASSERT_STREQ("12345678901234567890X", s8.toCString());
		ASSERT_EQ(s8c.length(), s8.length());
		ASSERT_EQ('\0', s8[s8.length()]);
		ASSERT_TRUE(s8.capacity() > s8.length());

		s10 += 'X';
		ASSERT_STREQ("123456789012345X", s10.toCString());
		ASSERT_EQ(s10c.length(), s10.length());
		ASSERT_EQ('\0', s10[s10.length()]);
		ASSERT_TRUE(s10.capacity() > s10.length());
	}
	TEST_F(StringTest, AppendString) {
		String s1c = s1 + "XYZ";
		ASSERT_STREQ("XYZ", s1c.toCString());
		ASSERT_EQ(s1.length() + 3, s1c.length());
		ASSERT_EQ('\0', s1c[s1c.length()]);
		ASSERT_TRUE(s1c.capacity() > s1c.length());

		String s4c = s4 + "XYZ";
		ASSERT_STREQ("abcdXYZ", s4c.toCString());
		ASSERT_EQ(s4.length() + 3, s4c.length());
		ASSERT_EQ('\0', s4c[s4c.length()]);
		ASSERT_TRUE(s4c.capacity() > s4c.length());

		String s8c = s8 + "XYZ";
		ASSERT_STREQ("12345678901234567890XYZ", s8c.toCString());
		ASSERT_EQ(s8.length() + 3, s8c.length());
		ASSERT_EQ('\0', s8c[s8c.length()]);
		ASSERT_TRUE(s8c.capacity() > s8c.length());

		String s10c = s10 + "XYZ";
		ASSERT_STREQ("123456789012345XYZ", s10c.toCString());
		ASSERT_EQ(s10.length() + 3, s10c.length());
		ASSERT_EQ('\0', s10c[s10c.length()]);
		ASSERT_TRUE(s10c.capacity() > s10c.length());

		String s14c = s4c + s10c;
		ASSERT_STREQ("abcdXYZ123456789012345XYZ", s14c.toCString());
		ASSERT_EQ(s4c.length() + s10c.length(), s14c.length());
		ASSERT_EQ('\0', s14c[s14c.length()]);
		ASSERT_TRUE(s14c.capacity() > s10c.length());

		s1 += "XYZ";
		ASSERT_STREQ("XYZ", s1.toCString());
		ASSERT_EQ(s1c.length(), s1.length());
		ASSERT_EQ('\0', s1[s1.length()]);
		ASSERT_TRUE(s1.capacity() > s1.length());

		s4 += "XYZ";
		ASSERT_STREQ("abcdXYZ", s4.toCString());
		ASSERT_EQ(s4c.length(), s4.length());
		ASSERT_EQ('\0', s4[s4.length()]);
		ASSERT_TRUE(s4.capacity() > s4.length());

		s8 += "XYZ";
		ASSERT_STREQ("12345678901234567890XYZ", s8.toCString());
		ASSERT_EQ(s8c.length(), s8.length());
		ASSERT_EQ('\0', s8[s8.length()]);
		ASSERT_TRUE(s8.capacity() > s8.length());

		s10 += "XYZ";
		ASSERT_STREQ("123456789012345XYZ", s10.toCString());
		ASSERT_EQ(s10c.length(), s10.length());
		ASSERT_EQ('\0', s10[s10.length()]);
		ASSERT_TRUE(s10.capacity() > s10.length());

		s4 += s10;
		ASSERT_STREQ("abcdXYZ123456789012345XYZ", s4.toCString());
		ASSERT_EQ(s4c.length() + s10.length(), s4.length());
		ASSERT_EQ('\0', s4[s4.length()]);
		ASSERT_TRUE(s4.capacity() > s10.length());
	}
}
