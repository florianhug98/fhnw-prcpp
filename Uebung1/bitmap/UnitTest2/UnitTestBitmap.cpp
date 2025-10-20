#include "gtest/gtest.h"
#include "Bitmap.h"

namespace UnitTest2 {
	constexpr auto rgb1 = "../../Images/rgb1.bmp";
	constexpr auto rgb2 = "../../Images/rgb2.bmp";
	constexpr auto argb = "../../Images/argb.bmp";
	constexpr auto file = "../../CMakeLists.txt";
	constexpr auto out = "../../Images/out.bmp";

	Bitmap m_bmp{};

	TEST(UnitTestBitmap, Read1) {
		ASSERT_TRUE(m_bmp.read(rgb1));
		ASSERT_EQ(BitmapSignature, m_bmp.signature());
		ASSERT_EQ(768 * 512 * 3 + 54, (int)m_bmp.fileSize());
		ASSERT_EQ(24, (int)m_bmp.bpp());
		ASSERT_EQ(40, (int)m_bmp.headerSize());
		ASSERT_EQ(512, (int)m_bmp.height());
		ASSERT_EQ(2304, (int)m_bmp.rowSize());
		ASSERT_EQ(1'179'648, (int)m_bmp.imageSize());
		const int x = 204 * 3;
		const int y = 180;
		ASSERT_EQ(5, (int)m_bmp.byteAt(x + 0, y));
		ASSERT_EQ(160, (int)m_bmp.byteAt(x + 1, y));
		ASSERT_EQ(155, (int)m_bmp.byteAt(x + 2, y));
	}
	TEST(UnitTestBitmap, Read2) {
		ASSERT_TRUE(m_bmp.read(rgb2));
		ASSERT_EQ(BitmapSignature, m_bmp.signature());
		ASSERT_EQ(768 * 512 * 3 + 54, (int)m_bmp.fileSize());
		ASSERT_EQ(24, (int)m_bmp.bpp());
		ASSERT_EQ(40, (int)m_bmp.headerSize());
		ASSERT_EQ(768, (int)m_bmp.height());
		ASSERT_EQ(1536, (int)m_bmp.rowSize());
		ASSERT_EQ(1'179'648, (int)m_bmp.imageSize());
		const int x = 449 * 3;
		const int y = 100;
		ASSERT_EQ(188, (int)m_bmp.byteAt(x + 0, y));
		ASSERT_EQ(171, (int)m_bmp.byteAt(x + 1, y));
		ASSERT_EQ(200, (int)m_bmp.byteAt(x + 2, y));
	}
	TEST(UnitTestBitmap, Read3) {
		ASSERT_TRUE(m_bmp.read(argb));
		ASSERT_EQ(BitmapSignature, m_bmp.signature());
		ASSERT_EQ(768 * 512 * 4 + 54, (int)m_bmp.fileSize());
		ASSERT_EQ(32, (int)m_bmp.bpp());
		ASSERT_EQ(40, (int)m_bmp.headerSize());
		ASSERT_EQ(512, (int)m_bmp.height());
		ASSERT_EQ(3072, (int)m_bmp.rowSize());
		ASSERT_EQ(1'572'864, (int)m_bmp.imageSize());
		const int x = 547 * 4;
		const int y = 326;
		ASSERT_EQ(135, (int)m_bmp.byteAt(x + 0, y));
		ASSERT_EQ(154, (int)m_bmp.byteAt(x + 1, y));
		ASSERT_EQ(68, (int)m_bmp.byteAt(x + 2, y));
		ASSERT_EQ(255, (int)m_bmp.byteAt(x + 3, y));
	}
	TEST(UnitTestBitmap, Read4) {
		ASSERT_FALSE(m_bmp.read(file));
	}
	TEST(UnitTestBitmap, Invert1) {
		ASSERT_TRUE(m_bmp.read(rgb1));
		m_bmp.invert();
		const int x = 204 * 3;
		const int y = 180;
		ASSERT_EQ(250, (int)m_bmp.byteAt(x + 0, y));
		ASSERT_EQ(95, (int)m_bmp.byteAt(x + 1, y));
		ASSERT_EQ(100, (int)m_bmp.byteAt(x + 2, y));
	}
	TEST(UnitTestBitmap, Invert2) {
		ASSERT_TRUE(m_bmp.read(rgb2));
		m_bmp.invert();
		const int x = 449 * 3;
		const int y = 100;
		ASSERT_EQ(67, (int)m_bmp.byteAt(x + 0, y));
		ASSERT_EQ(84, (int)m_bmp.byteAt(x + 1, y));
		ASSERT_EQ(55, (int)m_bmp.byteAt(x + 2, y));
	}
	TEST(UnitTestBitmap, Invert3) {
		ASSERT_TRUE(m_bmp.read(argb));
		m_bmp.invert();
		const int x = 547 * 4;
		const int y = 326;
		ASSERT_EQ(120, (int)m_bmp.byteAt(x + 0, y));
		ASSERT_EQ(101, (int)m_bmp.byteAt(x + 1, y));
		ASSERT_EQ(187, (int)m_bmp.byteAt(x + 2, y));
	}
	TEST(UnitTestBitmap, HorFlip1) {
		ASSERT_TRUE(m_bmp.read(rgb1));
		m_bmp.horFlip();
		const int x = (768 - 1 - 204) * 3;
		const int y = 180;
		ASSERT_EQ(5, (int)m_bmp.byteAt(x + 0, y));
		ASSERT_EQ(160, (int)m_bmp.byteAt(x + 1, y));
		ASSERT_EQ(155, (int)m_bmp.byteAt(x + 2, y));
	}
	TEST(UnitTestBitmap, HorFlip2) {
		ASSERT_TRUE(m_bmp.read(rgb2));
		m_bmp.horFlip();
		const int x = (512 - 1 - 449) * 3;
		const int y = 100;
		ASSERT_EQ(188, (int)m_bmp.byteAt(x + 0, y));
		ASSERT_EQ(171, (int)m_bmp.byteAt(x + 1, y));
		ASSERT_EQ(200, (int)m_bmp.byteAt(x + 2, y));
	}
	TEST(UnitTestBitmap, HorFlip3) {
		ASSERT_TRUE(m_bmp.read(argb));
		m_bmp.horFlip();
		const int x = (768 - 1 - 547) * 4;
		const int y = 326;
		ASSERT_EQ(135, (int)m_bmp.byteAt(x + 0, y));
		ASSERT_EQ(154, (int)m_bmp.byteAt(x + 1, y));
		ASSERT_EQ(68, (int)m_bmp.byteAt(x + 2, y));
		ASSERT_EQ(255, (int)m_bmp.byteAt(x + 3, y));
	}
	TEST(UnitTestBitmap, VerFlip1) {
		ASSERT_TRUE(m_bmp.read(rgb1));
		m_bmp.verFlip();
		const int x = 204 * 3;
		const int y = 512 - 1 - 180;
		ASSERT_EQ(5, (int)m_bmp.byteAt(x + 0, y));
		ASSERT_EQ(160, (int)m_bmp.byteAt(x + 1, y));
		ASSERT_EQ(155, (int)m_bmp.byteAt(x + 2, y));
	}
	TEST(UnitTestBitmap, VerFlip2) {
		ASSERT_TRUE(m_bmp.read(rgb2));
		m_bmp.verFlip();
		const int x = 449 * 3;
		const int y = 768 - 1 - 100;
		ASSERT_EQ(188, (int)m_bmp.byteAt(x + 0, y));
		ASSERT_EQ(171, (int)m_bmp.byteAt(x + 1, y));
		ASSERT_EQ(200, (int)m_bmp.byteAt(x + 2, y));
	}
	TEST(UnitTestBitmap, VerFlip3) {
		ASSERT_TRUE(m_bmp.read(argb));
		m_bmp.verFlip();
		const int x = 547 * 4;
		const int y = 512 - 1 - 326;
		ASSERT_EQ(135, (int)m_bmp.byteAt(x + 0, y));
		ASSERT_EQ(154, (int)m_bmp.byteAt(x + 1, y));
		ASSERT_EQ(68, (int)m_bmp.byteAt(x + 2, y));
		ASSERT_EQ(255, (int)m_bmp.byteAt(x + 3, y));
	}
	TEST(UnitTestBitmap, RgbToArgb) {
		ASSERT_TRUE(m_bmp.read(rgb1));
		Bitmap bmp = m_bmp.cvtToARGB();
		ASSERT_EQ(32, (int)bmp.bpp());
		ASSERT_EQ(40, (int)bmp.headerSize());
		ASSERT_EQ(512, (int)bmp.height());
		ASSERT_EQ(3072, (int)bmp.rowSize());
		ASSERT_EQ(1'572'864, (int)bmp.imageSize());
		const int x = 204 * 4;
		const int y = 180;
		ASSERT_EQ(5, (int)bmp.byteAt(x + 0, y));
		ASSERT_EQ(160, (int)bmp.byteAt(x + 1, y));
		ASSERT_EQ(155, (int)bmp.byteAt(x + 2, y));
		ASSERT_EQ(255, (int)bmp.byteAt(x + 3, y));
		ASSERT_TRUE(bmp.write(out));
	}
	TEST(UnitTestBitmap, ArgbToRgb) {
		ASSERT_TRUE(m_bmp.read(argb));
		Bitmap bmp = m_bmp.cvtToRGB();
		ASSERT_EQ(24, (int)bmp.bpp());
		ASSERT_EQ(40, (int)bmp.headerSize());
		ASSERT_EQ(512, (int)bmp.height());
		ASSERT_EQ(2304, (int)bmp.rowSize());
		ASSERT_EQ(1'179'648, (int)bmp.imageSize());
		const int x = 547 * 3;
		const int y = 326;
		ASSERT_EQ(135, (int)bmp.byteAt(x + 0, y));
		ASSERT_EQ(154, (int)bmp.byteAt(x + 1, y));
		ASSERT_EQ(68, (int)bmp.byteAt(x + 2, y));
		ASSERT_TRUE(bmp.write(out));
	}
}