#include "gtest/gtest.h"
#include "StringView.h"
#include <cstring>

using namespace std;

/// <summary>
/// Author: C. Stamm
/// </summary>
namespace UnitTest
{
	TEST(UnitTestStringView, Construction) {
		constexpr StringView s0;
		constexpr StringView s1("");
		constexpr StringView s2("abc");
		constexpr StringView s3("abcd", 4);
		constexpr StringView s4("abcd", 2);
		constexpr StringView s5(s0);
		constexpr StringView s6(s1);
		constexpr StringView s7(s2);
		ASSERT_THROW(StringView(nullptr), invalid_argument);
		ASSERT_THROW(StringView(nullptr, 5), invalid_argument);
		ASSERT_THROW(StringView(nullptr, 0), invalid_argument);
	}
	TEST(UnitTestStringView, Assignment) {
		constexpr StringView s0;
		constexpr StringView s1("");
		constexpr StringView s2("abc");
		constexpr StringView s3("abcd", 4);
		constexpr StringView s4("abcd", 2);
		constexpr StringView s0c = s0;
		ASSERT_TRUE(s0c == s0);
		constexpr StringView s1c = s1;
		ASSERT_TRUE(s1c == s1);
		constexpr StringView s2c = s2;
		ASSERT_TRUE(s2c == s2);
		constexpr StringView s3c = s3;
		ASSERT_TRUE(s3c == s3);
		constexpr StringView s4c = s4;
		ASSERT_TRUE(s4c == s4);
	}
	TEST(UnitTestStringView, IsEmpty) {
		ASSERT_TRUE(StringView().isEmpty());
		ASSERT_TRUE(StringView("").isEmpty());
		ASSERT_FALSE(StringView("abc").isEmpty());
		constexpr StringView s("abc");
		constexpr bool b = s.isEmpty();
		ASSERT_FALSE(b);
	}
	TEST(UnitTestStringView, Length) {
		ASSERT_EQ(0ull, StringView().length());
		ASSERT_EQ(0ull, StringView("").length());
		ASSERT_EQ(3ull, StringView("abc").length());
		constexpr StringView s("abc");
		constexpr size_t l = s.length();
		ASSERT_EQ(3ull, l);
		constexpr StringView s1("abcd", 2);
		constexpr size_t l1 = s1.length();
		ASSERT_EQ(2ull, l1);
		constexpr StringView s2("abcd", 0);
		constexpr size_t l2 = s2.length();
		ASSERT_EQ(0ull, l2);
	}
	TEST(UnitTestStringView, Data) {
		constexpr StringView s("abc");
		ASSERT_STREQ("abc", s.data());
		ASSERT_EQ('a', *s.data());
		ASSERT_EQ(3ull, strlen(s.data()));
		constexpr const char* p = s.data();
		ASSERT_EQ('b', *(p + 1));
	}
	TEST(UnitTestStringView, Equals) {
		constexpr StringView s("abc");
		constexpr StringView s3("abcd", 3);
		constexpr StringView s4("abx");
		ASSERT_TRUE(StringView() == StringView(""));
		ASSERT_TRUE(StringView("") == StringView());
		ASSERT_TRUE(s == s);
		ASSERT_FALSE(s == StringView("ab"));
		ASSERT_FALSE(s == s4);
		StringView s1;
		StringView s2;
		StringView& r1 = (s1 = s2);
		ASSERT_TRUE(s1 == s2);
		ASSERT_TRUE(r1 == s2);
		StringView& r2 = (s1 = s);
		ASSERT_TRUE(s1 == s);
		ASSERT_TRUE(r2 == s);
		ASSERT_TRUE(s == s3);
		ASSERT_TRUE(s3 == s);
	}
	TEST(UnitTestStringView, Smaller) {
		constexpr StringView s("abc");
		constexpr StringView s3("abcd", 3);
		ASSERT_FALSE(StringView() < StringView(""));
		ASSERT_TRUE(s < StringView("bcd"));
		ASSERT_TRUE(s < StringView("abde"));
		ASSERT_TRUE(s < StringView("abcd"));
		ASSERT_TRUE(s3 < StringView("bcd"));
		ASSERT_TRUE(s3 < StringView("abde"));
		ASSERT_TRUE(s3 < StringView("abcd"));
		ASSERT_TRUE(StringView("abbb") < s);
		ASSERT_TRUE(StringView("ABC") < s);
		ASSERT_TRUE(StringView("") < s);
		ASSERT_TRUE(StringView() < s);
		ASSERT_TRUE(StringView("abbb") < s3);
		ASSERT_TRUE(StringView("ABC") < s3);
		ASSERT_TRUE(StringView("") < s3);
		ASSERT_TRUE(StringView() < s3);
		constexpr bool b = StringView() < s;
		ASSERT_TRUE(b);
		ASSERT_FALSE(s < StringView("ab"));
		ASSERT_FALSE(s < StringView("aba"));
	}
	TEST(UnitTestStringView, CharAt) {
		constexpr StringView s("abc");
		constexpr char c = s[0];
		ASSERT_EQ('a', c);
		ASSERT_EQ('a', s[0]);
		ASSERT_EQ('b', s[1]);
		ASSERT_EQ('c', s[2]);
		ASSERT_THROW(s[3], out_of_range);
		ASSERT_THROW(StringView()[1], out_of_range);
	}
	TEST(UnitTestStringView, RemovePrefix) {
		constexpr StringView s("abcd");
		ASSERT_TRUE(s.removePrefix(0) == "abcd");
		ASSERT_TRUE(s.removePrefix(1) == "bcd");
		ASSERT_TRUE(s.removePrefix(2) == "cd");
		ASSERT_TRUE(s.removePrefix(3) == "d");
		ASSERT_TRUE(s.removePrefix(4) == "");
		ASSERT_THROW(s.removePrefix(5), out_of_range);
		ASSERT_TRUE(s.removePrefix(1).length() == 3);
		ASSERT_STREQ("bcd", s.removePrefix(1).data());
		ASSERT_TRUE(s.removePrefix(1) == StringView("bcd"));
		ASSERT_TRUE(s < s.removePrefix(1));
		ASSERT_EQ('b', s.removePrefix(1)[0]);
		ASSERT_TRUE(s.removePrefix(2).removePrefix(1) == "d");
		ASSERT_TRUE(s.removePrefix(1).removeSuffix(1) == "bc");
		constexpr StringView s2 = s.removePrefix(1).removeSuffix(1);
		ASSERT_TRUE(s2 == "bc");
	}
	TEST(UnitTestStringView, RemoveSuffix) {
		constexpr StringView s("abcd");
		ASSERT_TRUE(s.removeSuffix(0) == "abcd");
		ASSERT_TRUE(s.removeSuffix(1) == "abc");
		ASSERT_TRUE(s.removeSuffix(2) == "ab");
		ASSERT_TRUE(s.removeSuffix(3) == "a");
		ASSERT_TRUE(s.removeSuffix(4) == "");
		ASSERT_TRUE(s.removeSuffix(3).length() == 1);
		ASSERT_THROW(s.removeSuffix(5), out_of_range);
		ASSERT_TRUE(s.removeSuffix(1).length() == 3);
		constexpr auto t = s.removeSuffix(1);
		ASSERT_TRUE(StringView("abc") == StringView(t.data(), t.length()));
		ASSERT_TRUE(s.removeSuffix(1) == StringView("abc"));
		ASSERT_TRUE(s.removeSuffix(1) < s);
		ASSERT_EQ('a', s.removeSuffix(1)[0]);
		ASSERT_TRUE(s.removeSuffix(2).removeSuffix(1) == "a");
		ASSERT_TRUE(s.removeSuffix(1).removePrefix(1) == "bc");
		constexpr StringView s2 = s.removeSuffix(1).removePrefix(1);
		ASSERT_TRUE(s2 == "bc");
	}
}