#include "CppUnitTest.h"
#include "MyString.h"
#include <exception>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

constexpr static size_t ShortCapacity = String::ShortCapacity;

//template<> std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString(const String& t) { return ToString(t.toCString()); }

/// <summary>
/// Author: C. Stamm
/// </summary>
namespace UnitTest
{
	TEST_CLASS(UnitTestString)
	{
		String s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11, s12, s13, s14, s15, s16;

		TEST_METHOD_INITIALIZE(SetUp) {
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

	public:
		TEST_METHOD(A0_Construction) {
			Assert::AreEqual(ShortCapacity, s1.capacity());
			Assert::AreEqual(ShortCapacity, s2.capacity());
			Assert::AreEqual(ShortCapacity, s3.capacity());
			Assert::AreEqual(ShortCapacity, s4.capacity());
			Assert::AreEqual(ShortCapacity, s5.capacity());
			Assert::AreEqual(ShortCapacity, s6.capacity());
			Assert::AreEqual(ShortCapacity, s7.capacity());
			Assert::AreEqual(21ull, s8.capacity());
			Assert::AreEqual(ShortCapacity, s9.capacity());
			Assert::AreEqual(ShortCapacity, s10.capacity());
			Assert::AreEqual(21ull, s11.capacity());
			Assert::AreEqual(ShortCapacity, s12.capacity());
			Assert::AreEqual(ShortCapacity, s13.capacity());
			Assert::AreEqual(ShortCapacity, s14.capacity());
			Assert::AreEqual(21ull, s15.capacity());
			auto r1 = [] { String s(nullptr); };
			Assert::ExpectException<invalid_argument>(r1);
			auto r2 = [] { String s(nullptr, 5); };
			Assert::ExpectException<invalid_argument>(r2);
			auto r3 = [] { String s(nullptr, 0); };
			Assert::ExpectException<invalid_argument>(r3);
		}
		TEST_METHOD(A1_HeapCorruption) {
			try {
				SetUp();
			} catch (...) {
				Assert::Fail();
			}
		}
		TEST_METHOD(A2_Assignment) {
			s11 = s11;
			Assert::IsTrue(s11.length() < s11.capacity());
			Assert::AreEqual(20ull, s11.length());
			Assert::AreEqual(s8.toCString(), s11.toCString());
			s1 = s11;
			Assert::IsTrue(s1.length() < s1.capacity());
			Assert::AreEqual(s11.length(), s1.length());
			Assert::AreEqual(s8.toCString(), s1.toCString());
			s16 = s16;
			Assert::IsTrue(s16.length() < s16.capacity());
			Assert::AreEqual(16ull, s16.length());
			Assert::AreEqual(String(s8.toCString(), ShortCapacity).toCString(), s16.toCString());
			s1 = s16;
			Assert::IsTrue(s1.length() < s1.capacity());
			Assert::AreEqual(s16.length(), s1.length());
			Assert::AreEqual(String(s8.toCString(), ShortCapacity).toCString(), s1.toCString());
			s1 = "";
			Assert::AreEqual(ShortCapacity, s1.capacity());
			Assert::AreEqual(0ull, s1.length());
			s6 = s4;
			Assert::IsTrue(s6.length() < s6.capacity());
			Assert::AreEqual(s4.length(), s6.length());
			Assert::AreEqual(s4.toCString(), s6.toCString());
			s11 = s4;
			Assert::IsTrue(s11.length() < s11.capacity());
			Assert::AreEqual(s4.length(), s11.length());
			Assert::AreEqual(s4.toCString(), s11.toCString());
		}
		TEST_METHOD(A3_MoveSemantic) {

			// move ctor
			String s1m(move(s1));
			Assert::AreEqual("", s1m.toCString());
			Assert::AreEqual("", s1.toCString());
			Assert::AreEqual(0ull, s1.length());
			Assert::AreEqual(ShortCapacity, s1.capacity());

			String s4m(move(s4));
			Assert::AreEqual(s7.toCString(), s4m.toCString());
			Assert::AreEqual("", s4.toCString());
			Assert::AreEqual(0ull, s4.length());
			Assert::AreEqual(ShortCapacity, s4.capacity());

			String s8m(move(s8));
			Assert::AreEqual(s11.toCString(), s8m.toCString());
			Assert::AreEqual("", s8.toCString());
			Assert::AreEqual(0ull, s8.length());
			Assert::AreEqual(ShortCapacity, s8.capacity());

			// move operation
			s1 = move(s1m);
			Assert::AreEqual("", s1.toCString());
			Assert::AreEqual("", s1m.toCString());
			Assert::AreEqual(0ull, s1m.length());
			Assert::AreEqual(ShortCapacity, s1m.capacity());

			s4 = move(s4m);
			Assert::AreEqual(s7.toCString(), s4.toCString());
			Assert::AreEqual("", s4m.toCString());
			Assert::AreEqual(0ull, s4m.length());
			Assert::AreEqual(ShortCapacity, s4m.capacity());

			s8 = move(s8m);
			Assert::AreEqual(s11.toCString(), s8.toCString());
			Assert::AreEqual("", s8m.toCString());
			Assert::AreEqual(0ull, s8m.length());
			Assert::AreEqual(ShortCapacity, s8m.capacity());

			s11 = move(s11);
			Assert::AreEqual(s8.toCString(), s11.toCString());
			Assert::AreEqual(s8.length(), s11.length());
		}
		TEST_METHOD(IsEmpty) {
			Assert::IsTrue(s1.isEmpty());
			Assert::IsTrue(s2.isEmpty());
			Assert::IsTrue(s3.isEmpty());
			Assert::IsFalse(s4.isEmpty());
			Assert::IsTrue(s5.isEmpty());
			Assert::IsFalse(s6.isEmpty());
			Assert::IsFalse(s7.isEmpty());
			Assert::IsFalse(s8.isEmpty());
			Assert::IsTrue(s9.isEmpty());
			Assert::IsFalse(s10.isEmpty());
			Assert::IsFalse(s11.isEmpty());
			Assert::IsTrue(s12.isEmpty());
			Assert::IsTrue(s13.isEmpty());
			Assert::IsFalse(s14.isEmpty());
			Assert::IsFalse(s15.isEmpty());
		}
		TEST_METHOD(Length) {
			Assert::AreEqual(0ull, s1.length());
			Assert::AreEqual(0ull, s2.length());
			Assert::AreEqual(0ull, s3.length());
			Assert::AreEqual(4ull, s4.length());
			Assert::AreEqual(0ull, s5.length());
			Assert::AreEqual(2ull, s6.length());
			Assert::AreEqual(4ull, s7.length());
			Assert::AreEqual(20ull, s8.length());
			Assert::AreEqual(0ull, s9.length());
			Assert::AreEqual(15ull, s10.length());
			Assert::AreEqual(20ull, s11.length());
			Assert::AreEqual(0ull, s12.length());
			Assert::AreEqual(0ull, s13.length());
			Assert::AreEqual(4ull, s14.length());
			Assert::AreEqual(20ull, s15.length());
		}
		TEST_METHOD(Equals) {
			Assert::IsTrue(s1 == s1);
			Assert::IsTrue(s1 == s2);
			Assert::IsTrue(s1 == s3);
			Assert::IsTrue(s4 == s4);
			Assert::IsTrue(s1 == s5);
			Assert::IsTrue(String("ab") == s6);
			Assert::IsTrue(s4 == s7);
			Assert::IsTrue(s8 == s8);
			Assert::IsTrue(s1 == s9);
			Assert::IsTrue(String("123456789012345") == s10);
			Assert::IsTrue(s8 == s11);
			Assert::IsTrue(s1 == s12);
			Assert::IsTrue(s2 == s13);
			Assert::IsTrue(s4 == s14);
			Assert::IsTrue(s8 == s15);
			Assert::IsFalse(String("ABCD") == s4);
			Assert::IsFalse(s4 == String("ABCD"));
		}
		TEST_METHOD(CString) {
			Assert::AreEqual(s1.toCString(), s1.toCString());
			Assert::AreEqual(s1.toCString(), s2.toCString());
			Assert::AreEqual(s1.toCString(), s3.toCString());
			Assert::AreEqual(s4.toCString(), s4.toCString());
			Assert::AreEqual(s1.toCString(), s5.toCString());
			Assert::AreEqual("ab", s6.toCString());
			Assert::AreEqual(s4.toCString(), s7.toCString());
			Assert::AreEqual(s8.toCString(), s8.toCString());
			Assert::AreEqual(s1.toCString(), s9.toCString());
			Assert::AreEqual("123456789012345", s10.toCString());
			Assert::AreEqual(s8.toCString(), s11.toCString());
			Assert::AreEqual(s1.toCString(), s12.toCString());
			Assert::AreEqual(s2.toCString(), s13.toCString());
			Assert::AreEqual(s4.toCString(), s14.toCString());
			Assert::AreEqual(s8.toCString(), s15.toCString());
		}
		TEST_METHOD(SubString) {
			Assert::AreEqual(s1.toCString(), s4.substring(s4.length(), 0).toCString());
			Assert::AreEqual(s1.toCString(), s4.substring(s4.length(), 1).toCString());
			Assert::AreEqual("a", s4.substring(0, 1).toCString());
			Assert::AreEqual("b", s4.substring(1, 2).toCString());
			Assert::AreEqual("c", s4.substring(2, 3).toCString());
			Assert::AreEqual("d", s4.substring(3, 4).toCString());
			Assert::AreEqual("ab", s4.substring(0, 2).toCString());
			Assert::AreEqual("bc", s4.substring(1, 3).toCString());
			Assert::AreEqual("cd", s4.substring(2, 4).toCString());
			Assert::AreEqual("d", s4.substring(3, 5).toCString());
			Assert::AreEqual("bcd", s4.substring(1, 5).toCString());
			Assert::AreEqual("bcd", s4.substring(1, 6).toCString());
			Assert::AreEqual("bcd", s4.substring(1, 0).toCString());
			Assert::AreEqual(s1.toCString(), s8.substring(s8.length(), 0).toCString());
			Assert::AreEqual(s1.toCString(), s8.substring(s8.length(), s8.length() + 1).toCString());
			Assert::AreEqual("1", s8.substring(0, 1).toCString());
			Assert::AreEqual("1", s8.substring(10, 11).toCString());
			Assert::AreEqual("0", s8.substring(19, 20).toCString());
			Assert::AreEqual("12", s8.substring(0, 2).toCString());
			Assert::AreEqual("12", s8.substring(10, 12).toCString());
			Assert::AreEqual("0", s8.substring(19, 21).toCString());
			Assert::AreEqual("5678901234", s8.substring(4, 14).toCString());
			Assert::AreEqual("567890", s8.substring(14, 24).toCString());
			Assert::AreEqual("567890", s8.substring(14, 0).toCString());
			Assert::AreEqual("234567890123456789", s8.substring(1, 19).toCString());
			Assert::AreEqual("56789012345", s10.substring(4, 0).toCString());

			auto r1 = [this] { s1.substring(1, 0); };
			Assert::ExpectException<out_of_range>(r1);
			auto r2 = [this] { s2.substring(1, 0); };
			Assert::ExpectException<out_of_range>(r2);
			auto r4 = [this] { s4.substring(s4.length() + 1, 0); };
			Assert::ExpectException<out_of_range>(r4);
			auto r8 = [this] { s8.substring(s8.length() + 1, 0); };
			Assert::ExpectException<out_of_range>(r8);
		}
		TEST_METHOD(Smaller) {
			Assert::IsTrue(s1 < s4);
			Assert::IsFalse(s4 < s1);
			Assert::IsTrue(s1 < s8);
			Assert::IsFalse(s8 < s1);
			Assert::IsTrue(s8 < s4);
			Assert::IsFalse(s4 < s8);
			Assert::IsTrue(s4 < "abcda");
			Assert::IsTrue(s4 < "abce");
			Assert::IsTrue(s4 < "abd");
			Assert::IsTrue(s4 < "ac");
			Assert::IsTrue(s4 < "b");
			Assert::IsFalse(s4 < "ABCD");

			Assert::IsFalse(s2 < s1);
			Assert::IsFalse(s1 < s2);
			Assert::IsFalse(s5 < s1);
			Assert::IsFalse(s1 < s5);
			Assert::IsFalse(s9 < s1);
			Assert::IsFalse(s1 < s9);
			Assert::IsFalse(s8 < s11);
			Assert::IsTrue(s10 < s11);
		}
		TEST_METHOD(At) {
			// reading
			const String& s1c = static_cast<const String&>(s1);
			const String& s2c = static_cast<const String&>(s2);
			const String& s3c = static_cast<const String&>(s3);
			const String& s4c = static_cast<const String&>(s4);
			const String& s5c = static_cast<const String&>(s5);
			const String& s8c = static_cast<const String&>(s8);
			const String& s9c = static_cast<const String&>(s9);
			const String& s16c = static_cast<const String&>(s16);
			Assert::AreEqual('\0', s1c[0]);
			Assert::AreEqual('\0', s2c[0]);
			Assert::AreEqual('\0', s3c[0]);
			Assert::AreEqual('\0', s5c[0]);
			Assert::AreEqual('\0', s9c[0]);
			Assert::AreEqual('a', s4c[0]);
			Assert::AreEqual('b', s4c[1]);
			Assert::AreEqual('c', s4c[2]);
			Assert::AreEqual('d', s4c[3]);
			Assert::AreEqual('\0', s4c[4]);
			Assert::AreEqual('1', s8c[0]);
			Assert::AreEqual('1', s8c[10]);
			Assert::AreEqual('9', s8c[18]);
			Assert::AreEqual('0', s8c[19]);
			Assert::AreEqual('\0', s8c[20]);
			Assert::AreEqual('\0', s16c[ShortCapacity]);
			Assert::AreEqual('6', s16c[ShortCapacity - 1]);

			auto r1 = [&s1c] { s1c[1]; };
			Assert::ExpectException<out_of_range>(r1);
			auto r2 = [&s2c] { s2c[1]; };
			Assert::ExpectException<out_of_range>(r2);
			auto r3 = [&s3c] { s3c[1]; };
			Assert::ExpectException<out_of_range>(r3);
			auto r4 = [&s4c] { s4c[-1]; };
			Assert::ExpectException<out_of_range>(r4);
			auto r5 = [&s5c] { s5c[1]; };
			Assert::ExpectException<out_of_range>(r5);
			auto r8 = [&s8c] { s8c[-1]; };
			Assert::ExpectException<out_of_range>(r8);
			auto r9 = [&s9c] { s9c[1]; };
			Assert::ExpectException<out_of_range>(r9);

			// writing
			s4[0] = 'A';
			Assert::AreEqual('A', s4[0]);
			s4[3] = 'D';
			Assert::AreEqual('D', s4[3]);
			s4[4] = '\0';
			Assert::AreEqual('\0', s4[4]);
			auto r14 = [this] { s14[-1]; };
			Assert::ExpectException<out_of_range>(r14);

			s8[0] = 'A';
			Assert::AreEqual('A', s8[0]);
			s8[19] = 'D';
			Assert::AreEqual('D', s8[19]);
			s8[20] = '\0';
			Assert::AreEqual('\0', s8[20]);
			auto r15 = [this] { s15[-1]; };
			Assert::ExpectException<out_of_range>(r15);
		}
		TEST_METHOD(AppendChar) {
			String s1c = s1 + 'X';
			Assert::AreEqual("X", s1c.toCString());
			Assert::AreEqual(s1.length() + 1, s1c.length());
			Assert::AreEqual('\0', s1c[s1c.length()]);
			Assert::IsTrue(s1c.capacity() > s1c.length());

			String s4c = s4 + 'X';
			Assert::AreEqual("abcdX", s4c.toCString());
			Assert::AreEqual(s4.length() + 1, s4c.length());
			Assert::AreEqual('\0', s4c[s4c.length()]);
			Assert::IsTrue(s4c.capacity() > s4c.length());

			String s8c = s8 + 'X';
			Assert::AreEqual("12345678901234567890X", s8c.toCString());
			Assert::AreEqual(s8.length() + 1, s8c.length());
			Assert::AreEqual('\0', s8c[s8c.length()]);
			Assert::IsTrue(s8c.capacity() > s8c.length());

			String s10c = s10 + 'X';
			Assert::AreEqual("123456789012345X", s10c.toCString());
			Assert::AreEqual(s10.length() + 1, s10c.length());
			Assert::AreEqual('\0', s10c[s10c.length()]);
			Assert::IsTrue(s10c.capacity() > s10c.length());

			s1 += 'X';
			Assert::AreEqual("X", s1.toCString());
			Assert::AreEqual(s1c.length(), s1.length());
			Assert::AreEqual('\0', s1[s1.length()]);
			Assert::IsTrue(s1.capacity() > s1.length());

			s4 += 'X';
			Assert::AreEqual("abcdX", s4.toCString());
			Assert::AreEqual(s4c.length(), s4.length());
			Assert::AreEqual('\0', s4[s4.length()]);
			Assert::IsTrue(s4.capacity() > s4.length());

			s8 += 'X';
			Assert::AreEqual("12345678901234567890X", s8.toCString());
			Assert::AreEqual(s8c.length(), s8.length());
			Assert::AreEqual('\0', s8[s8.length()]);
			Assert::IsTrue(s8.capacity() > s8.length());

			s10 += 'X';
			Assert::AreEqual("123456789012345X", s10.toCString());
			Assert::AreEqual(s10c.length(), s10.length());
			Assert::AreEqual('\0', s10[s10.length()]);
			Assert::IsTrue(s10.capacity() > s10.length());
		}
		TEST_METHOD(AppendString) {
			String s1c = s1 + "XYZ";
			Assert::AreEqual("XYZ", s1c.toCString());
			Assert::AreEqual(s1.length() + 3, s1c.length());
			Assert::AreEqual('\0', s1c[s1c.length()]);
			Assert::IsTrue(s1c.capacity() > s1c.length());

			String s4c = s4 + "XYZ";
			Assert::AreEqual("abcdXYZ", s4c.toCString());
			Assert::AreEqual(s4.length() + 3, s4c.length());
			Assert::AreEqual('\0', s4c[s4c.length()]);
			Assert::IsTrue(s4c.capacity() > s4c.length());

			String s8c = s8 + "XYZ";
			Assert::AreEqual("12345678901234567890XYZ", s8c.toCString());
			Assert::AreEqual(s8.length() + 3, s8c.length());
			Assert::AreEqual('\0', s8c[s8c.length()]);
			Assert::IsTrue(s8c.capacity() > s8c.length());

			String s10c = s10 + "XYZ";
			Assert::AreEqual("123456789012345XYZ", s10c.toCString());
			Assert::AreEqual(s10.length() + 3, s10c.length());
			Assert::AreEqual('\0', s10c[s10c.length()]);
			Assert::IsTrue(s10c.capacity() > s10c.length());

			String s14c = s4c + s10c;
			Assert::AreEqual("abcdXYZ123456789012345XYZ", s14c.toCString());
			Assert::AreEqual(s4c.length() + s10c.length(), s14c.length());
			Assert::AreEqual('\0', s14c[s14c.length()]);
			Assert::IsTrue(s14c.capacity() > s10c.length());

			s1 += "XYZ";
			Assert::AreEqual("XYZ", s1.toCString());
			Assert::AreEqual(s1c.length(), s1.length());
			Assert::AreEqual('\0', s1[s1.length()]);
			Assert::IsTrue(s1.capacity() > s1.length());

			s4 += "XYZ";
			Assert::AreEqual("abcdXYZ", s4.toCString());
			Assert::AreEqual(s4c.length(), s4.length());
			Assert::AreEqual('\0', s4[s4.length()]);
			Assert::IsTrue(s4.capacity() > s4.length());

			s8 += "XYZ";
			Assert::AreEqual("12345678901234567890XYZ", s8.toCString());
			Assert::AreEqual(s8c.length(), s8.length());
			Assert::AreEqual('\0', s8[s8.length()]);
			Assert::IsTrue(s8.capacity() > s8.length());

			s10 += "XYZ";
			Assert::AreEqual("123456789012345XYZ", s10.toCString());
			Assert::AreEqual(s10c.length(), s10.length());
			Assert::AreEqual('\0', s10[s10.length()]);
			Assert::IsTrue(s10.capacity() > s10.length());

			s4 += s10;
			Assert::AreEqual("abcdXYZ123456789012345XYZ", s4.toCString());
			Assert::AreEqual(s4c.length() + s10.length(), s4.length());
			Assert::AreEqual('\0', s4[s4.length()]);
			Assert::IsTrue(s4.capacity() > s10.length());
		}
	};
}
