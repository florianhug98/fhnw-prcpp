#include "CppUnitTest.h"
#include "Bitmap.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

constexpr auto rgb1 = "../../Images/rgb1.bmp";
constexpr auto rgb2 = "../../Images/rgb2.bmp";
constexpr auto argb = "../../Images/argb.bmp";
constexpr auto file = "../../CMakeLists.txt";
constexpr auto out = "../../Images/out.bmp";

namespace UnitTest1
{
	TEST_CLASS(UnitTestBitmap)
	{
		Bitmap m_bmp{};
	public:
		
		TEST_METHOD(Read1)
		{
			Assert::IsTrue(m_bmp.read(rgb1));
			Assert::AreEqual(BitmapSignature, m_bmp.signature());
			Assert::AreEqual(768*512*3 + 54, (int)m_bmp.fileSize());
			Assert::AreEqual(24, (int)m_bmp.bpp());
			Assert::AreEqual(40, (int)m_bmp.headerSize());
			Assert::AreEqual(512, (int)m_bmp.height());
			Assert::AreEqual(2304, (int)m_bmp.rowSize());
			Assert::AreEqual(1'179'648, (int)m_bmp.imageSize());
			const int x = 204*3;
			const int y = 180;
			Assert::AreEqual(5, (int)m_bmp.byteAt(x + 0, y));
			Assert::AreEqual(160, (int)m_bmp.byteAt(x + 1, y));
			Assert::AreEqual(155, (int)m_bmp.byteAt(x + 2, y));
		}
		TEST_METHOD(Read2)
		{
			Assert::IsTrue(m_bmp.read(rgb2));
			Assert::AreEqual(BitmapSignature, m_bmp.signature());
			Assert::AreEqual(768*512*3 + 54, (int)m_bmp.fileSize());
			Assert::AreEqual(24, (int)m_bmp.bpp());
			Assert::AreEqual(40, (int)m_bmp.headerSize());
			Assert::AreEqual(768, (int)m_bmp.height());
			Assert::AreEqual(1536, (int)m_bmp.rowSize());
			Assert::AreEqual(1'179'648, (int)m_bmp.imageSize());
			const int x = 449*3;
			const int y = 100;
			Assert::AreEqual(188, (int)m_bmp.byteAt(x + 0, y));
			Assert::AreEqual(171, (int)m_bmp.byteAt(x + 1, y));
			Assert::AreEqual(200, (int)m_bmp.byteAt(x + 2, y));
		}
		TEST_METHOD(Read3)
		{
			Assert::IsTrue(m_bmp.read(argb));
			Assert::AreEqual(BitmapSignature, m_bmp.signature());
			Assert::AreEqual(768*512*4 + 54, (int)m_bmp.fileSize());
			Assert::AreEqual(32, (int)m_bmp.bpp());
			Assert::AreEqual(40, (int)m_bmp.headerSize());
			Assert::AreEqual(512, (int)m_bmp.height());
			Assert::AreEqual(3072, (int)m_bmp.rowSize());
			Assert::AreEqual(1'572'864, (int)m_bmp.imageSize());
			const int x = 547*4;
			const int y = 326;
			Assert::AreEqual(135, (int)m_bmp.byteAt(x + 0, y));
			Assert::AreEqual(154, (int)m_bmp.byteAt(x + 1, y));
			Assert::AreEqual(68, (int)m_bmp.byteAt(x + 2, y));
			Assert::AreEqual(255, (int)m_bmp.byteAt(x + 3, y));
		}
		TEST_METHOD(Read4)
		{
			Assert::IsFalse(m_bmp.read(file));
		}
		TEST_METHOD(Invert1)
		{
			Assert::IsTrue(m_bmp.read(rgb1));
			m_bmp.invert();
			const int x = 204*3;
			const int y = 180;
			Assert::AreEqual(250, (int)m_bmp.byteAt(x + 0, y));
			Assert::AreEqual(95, (int)m_bmp.byteAt(x + 1, y));
			Assert::AreEqual(100, (int)m_bmp.byteAt(x + 2, y));
		}
		TEST_METHOD(Invert2)
		{
			Assert::IsTrue(m_bmp.read(rgb2));
			m_bmp.invert();
			const int x = 449*3;
			const int y = 100;
			Assert::AreEqual(67, (int)m_bmp.byteAt(x + 0, y));
			Assert::AreEqual(84, (int)m_bmp.byteAt(x + 1, y));
			Assert::AreEqual(55, (int)m_bmp.byteAt(x + 2, y));
		}
		TEST_METHOD(Invert3)
		{
			Assert::IsTrue(m_bmp.read(argb));
			m_bmp.invert();
			const int x = 547*4;
			const int y = 326;
			Assert::AreEqual(120, (int)m_bmp.byteAt(x + 0, y));
			Assert::AreEqual(101, (int)m_bmp.byteAt(x + 1, y));
			Assert::AreEqual(187, (int)m_bmp.byteAt(x + 2, y));
		}
		TEST_METHOD(HorFlip1)
		{
			Assert::IsTrue(m_bmp.read(rgb1));
			m_bmp.horFlip();
			const int x = (768 - 1 - 204)*3;
			const int y = 180;
			Assert::AreEqual(5, (int)m_bmp.byteAt(x + 0, y));
			Assert::AreEqual(160, (int)m_bmp.byteAt(x + 1, y));
			Assert::AreEqual(155, (int)m_bmp.byteAt(x + 2, y));
		}
		TEST_METHOD(HorFlip2)
		{
			Assert::IsTrue(m_bmp.read(rgb2));
			m_bmp.horFlip();
			const int x = (512 - 1 - 449)*3;
			const int y = 100;
			Assert::AreEqual(188, (int)m_bmp.byteAt(x + 0, y));
			Assert::AreEqual(171, (int)m_bmp.byteAt(x + 1, y));
			Assert::AreEqual(200, (int)m_bmp.byteAt(x + 2, y));
		}
		TEST_METHOD(HorFlip3)
		{
			Assert::IsTrue(m_bmp.read(argb));
			m_bmp.horFlip();
			const int x = (768 - 1 - 547)*4;
			const int y = 326;
			Assert::AreEqual(135, (int)m_bmp.byteAt(x + 0, y));
			Assert::AreEqual(154, (int)m_bmp.byteAt(x + 1, y));
			Assert::AreEqual(68, (int)m_bmp.byteAt(x + 2, y));
			Assert::AreEqual(255, (int)m_bmp.byteAt(x + 3, y));
		}
		TEST_METHOD(VerFlip1)
		{
			Assert::IsTrue(m_bmp.read(rgb1));
			m_bmp.verFlip();
			const int x = 204*3;
			const int y = 512 - 1 - 180;
			Assert::AreEqual(5, (int)m_bmp.byteAt(x + 0, y));
			Assert::AreEqual(160, (int)m_bmp.byteAt(x + 1, y));
			Assert::AreEqual(155, (int)m_bmp.byteAt(x + 2, y));
		}
		TEST_METHOD(VerFlip2)
		{
			Assert::IsTrue(m_bmp.read(rgb2));
			m_bmp.verFlip();
			const int x = 449*3;
			const int y = 768 - 1 - 100;
			Assert::AreEqual(188, (int)m_bmp.byteAt(x + 0, y));
			Assert::AreEqual(171, (int)m_bmp.byteAt(x + 1, y));
			Assert::AreEqual(200, (int)m_bmp.byteAt(x + 2, y));
		}
		TEST_METHOD(VerFlip3)
		{
			Assert::IsTrue(m_bmp.read(argb));
			m_bmp.verFlip();
			const int x = 547*4;
			const int y = 512 - 1 - 326;
			Assert::AreEqual(135, (int)m_bmp.byteAt(x + 0, y));
			Assert::AreEqual(154, (int)m_bmp.byteAt(x + 1, y));
			Assert::AreEqual(68, (int)m_bmp.byteAt(x + 2, y));
			Assert::AreEqual(255, (int)m_bmp.byteAt(x + 3, y));
		}
		TEST_METHOD(RgbToArgb)
		{
			Assert::IsTrue(m_bmp.read(rgb1));
			Bitmap bmp = m_bmp.cvtToARGB();
			Assert::AreEqual(32, (int)bmp.bpp());
			Assert::AreEqual(40, (int)bmp.headerSize());
			Assert::AreEqual(512, (int)bmp.height());
			Assert::AreEqual(3072, (int)bmp.rowSize());
			Assert::AreEqual(1'572'864, (int)bmp.imageSize());
			const int x = 204*4;
			const int y = 180;
			Assert::AreEqual(5, (int)bmp.byteAt(x + 0, y));
			Assert::AreEqual(160, (int)bmp.byteAt(x + 1, y));
			Assert::AreEqual(155, (int)bmp.byteAt(x + 2, y));
			Assert::AreEqual(255, (int)bmp.byteAt(x + 3, y));
			Assert::IsTrue(bmp.write(out));
		}
		TEST_METHOD(ArgbToRgb)
		{
			Assert::IsTrue(m_bmp.read(argb));
			Bitmap bmp = m_bmp.cvtToRGB();
			Assert::AreEqual(24, (int)bmp.bpp());
			Assert::AreEqual(40, (int)bmp.headerSize());
			Assert::AreEqual(512, (int)bmp.height());
			Assert::AreEqual(2304, (int)bmp.rowSize());
			Assert::AreEqual(1'179'648, (int)bmp.imageSize());
			const int x = 547*3;
			const int y = 326;
			Assert::AreEqual(135, (int)bmp.byteAt(x + 0, y));
			Assert::AreEqual(154, (int)bmp.byteAt(x + 1, y));
			Assert::AreEqual(68, (int)bmp.byteAt(x + 2, y));
			Assert::IsTrue(bmp.write(out));
		}
	};
}
