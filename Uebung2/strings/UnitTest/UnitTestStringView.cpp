#include "CppUnitTest.h"
#include "StringView.h"
#include <cstring>

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

/// <summary>
/// Author: C. Stamm
/// </summary>
namespace UnitTest
{
	TEST_CLASS(UnitTestStringView)
	{
	public:
		
		TEST_METHOD(Construction) {
			constexpr StringView s0;
			constexpr StringView s1("");
			constexpr StringView s2("abc");
			constexpr StringView s3("abcd", 4);
			constexpr StringView s4("abcd", 2);
			constexpr StringView s5(s0);
			constexpr StringView s6(s1);
			constexpr StringView s7(s2);
			auto r1 = [] { StringView(nullptr); };
			Assert::ExpectException<invalid_argument>(r1);
			auto r2 = [] { StringView s(nullptr, 5); };
			Assert::ExpectException<invalid_argument>(r2);
			auto r3 = [] { StringView s(nullptr, 0); };
			Assert::ExpectException<invalid_argument>(r3);
		}
		TEST_METHOD(Assignment) {
			constexpr StringView s0;
			constexpr StringView s1("");
			constexpr StringView s2("abc");
			constexpr StringView s3("abcd", 4);
			constexpr StringView s4("abcd", 2);
			constexpr StringView s0c = s0;
			Assert::IsTrue(s0c == s0);
			constexpr StringView s1c = s1;
			Assert::IsTrue(s1c == s1);
			constexpr StringView s2c = s2;
			Assert::IsTrue(s2c == s2);
			constexpr StringView s3c = s3;
			Assert::IsTrue(s3c == s3);
			constexpr StringView s4c = s4;
			Assert::IsTrue(s4c == s4);
		}
		TEST_METHOD(IsEmpty) {
			Assert::IsTrue(StringView().isEmpty());
			Assert::IsTrue(StringView("").isEmpty());
			Assert::IsFalse(StringView("abc").isEmpty());
			constexpr StringView s("abc");
			constexpr bool b = s.isEmpty();
			Assert::IsFalse(b);
		}
		TEST_METHOD(Length) {
			Assert::AreEqual(0ull, StringView().length());
			Assert::AreEqual(0ull, StringView("").length());
			Assert::AreEqual(3ull, StringView("abc").length());
			constexpr StringView s("abc");
			constexpr size_t l = s.length();
			Assert::AreEqual(3ull, l);
			constexpr StringView s1("abcd", 2);
			constexpr size_t l1 = s1.length();
			Assert::AreEqual(2ull, l1);
			constexpr StringView s2("abcd", 0);
			constexpr size_t l2 = s2.length();
			Assert::AreEqual(0ull, l2);
		}
		TEST_METHOD(Data) {
			constexpr StringView s("abc");
			Assert::AreEqual("abc", s.data());
			Assert::AreEqual('a', *s.data());
			Assert::AreEqual(3ull, strlen(s.data()));
			constexpr const char* p = s.data();
			Assert::AreEqual('b', *(p + 1));
		}
		TEST_METHOD(Equals) {
			constexpr StringView s("abc");
			constexpr StringView s3("abcd", 3);
			constexpr StringView s4("abx");
			Assert::IsTrue(StringView() == StringView(""));
			Assert::IsTrue(StringView("") == StringView());
			Assert::IsTrue(s == s);
			Assert::IsFalse(s == StringView("ab"));
			Assert::IsFalse(s == s4);
			StringView s1;
			StringView s2;
			StringView& r1 = (s1 = s2);
			Assert::IsTrue(s1 == s2);
			Assert::IsTrue(r1 == s2);
			StringView& r2 = (s1 = s);
			Assert::IsTrue(s1 == s);
			Assert::IsTrue(r2 == s);
			Assert::IsTrue(s == s3);
			Assert::IsTrue(s3 == s);
		}
		TEST_METHOD(Smaller) {
			constexpr StringView s("abc");
			constexpr StringView s3("abcd", 3);
			Assert::IsFalse(StringView() < StringView(""));
			Assert::IsTrue(s < StringView("bcd"));
			Assert::IsTrue(s < StringView("abde"));
			Assert::IsTrue(s < StringView("abcd"));
			Assert::IsTrue(s3 < StringView("bcd"));
			Assert::IsTrue(s3 < StringView("abde"));
			Assert::IsTrue(s3 < StringView("abcd"));
			Assert::IsTrue(StringView("abbb") < s);
			Assert::IsTrue(StringView("ABC") < s);
			Assert::IsTrue(StringView("") < s);
			Assert::IsTrue(StringView() < s);
			Assert::IsTrue(StringView("abbb") < s3);
			Assert::IsTrue(StringView("ABC") < s3);
			Assert::IsTrue(StringView("") < s3);
			Assert::IsTrue(StringView() < s3);
			constexpr bool b = StringView() < s;
			Assert::IsTrue(b);
			Assert::IsFalse(s < StringView("ab"));
			Assert::IsFalse(s < StringView("aba"));
		}
		TEST_METHOD(CharAt) {
			constexpr StringView s("abc");
			constexpr char c = s[0];
			Assert::AreEqual('a', c);
			Assert::AreEqual('a', s[0]);
			Assert::AreEqual('b', s[1]);
			Assert::AreEqual('c', s[2]);
			auto r1 = [s] { s[3]; };
			Assert::ExpectException<out_of_range>(r1);
			auto r2 = [] { StringView()[1]; };
			Assert::ExpectException<out_of_range>(r2);
		}
		TEST_METHOD(RemovePrefix) {
			constexpr StringView s("abcd");
			Assert::IsTrue(s.removePrefix(0) == "abcd");
			Assert::IsTrue(s.removePrefix(1) == "bcd");
			Assert::IsTrue(s.removePrefix(2) == "cd");
			Assert::IsTrue(s.removePrefix(3) == "d");
			Assert::IsTrue(s.removePrefix(4) == "");
			auto r = [s] { s.removePrefix(5); };
			Assert::ExpectException<out_of_range>(r);
			Assert::IsTrue(s.removePrefix(1).length() == 3);
			Assert::AreEqual("bcd", s.removePrefix(1).data());
			Assert::IsTrue(s.removePrefix(1) == StringView("bcd"));
			Assert::IsTrue(s < s.removePrefix(1));
			Assert::AreEqual('b', s.removePrefix(1)[0]);
			Assert::IsTrue(s.removePrefix(2).removePrefix(1) == "d");
			Assert::IsTrue(s.removePrefix(1).removeSuffix(1) == "bc");
			constexpr StringView s2 = s.removePrefix(1).removeSuffix(1);
			Assert::IsTrue(s2 == "bc");
		}
		TEST_METHOD(RemoveSuffix) {
			constexpr StringView s("abcd");
			Assert::IsTrue(s.removeSuffix(0) == "abcd");
			Assert::IsTrue(s.removeSuffix(1) == "abc");
			Assert::IsTrue(s.removeSuffix(2) == "ab");
			Assert::IsTrue(s.removeSuffix(3) == "a");
			Assert::IsTrue(s.removeSuffix(4) == "");
			Assert::IsTrue(s.removeSuffix(3).length() == 1);
			auto r = [s] { s.removeSuffix(5); };
			Assert::ExpectException<out_of_range>(r);
			Assert::IsTrue(s.removeSuffix(1).length() == 3);
			constexpr auto t = s.removeSuffix(1);
			Assert::IsTrue(StringView("abc") == StringView(t.data(), t.length()));
			Assert::IsTrue(s.removeSuffix(1) == StringView("abc"));
			Assert::IsTrue(s.removeSuffix(1) < s);
			Assert::AreEqual('a', s.removeSuffix(1)[0]);
			Assert::IsTrue(s.removeSuffix(2).removeSuffix(1) == "a");
			Assert::IsTrue(s.removeSuffix(1).removePrefix(1) == "bc");
			constexpr StringView s2 = s.removeSuffix(1).removePrefix(1);
			Assert::IsTrue(s2 == "bc");
		}
	};
}
