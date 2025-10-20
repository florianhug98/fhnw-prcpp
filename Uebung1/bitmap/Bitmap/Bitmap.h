#pragma once

#include <string_view>
#include <cstdint>
#include <memory>

// Author: 

///////////////////////////////////////////////////////////////////////////////
// https://en.wikipedia.org/wiki/BMP_file_format

///////////////////////////////////////////////////////////////////////////////
// Constants
constexpr uint16_t BitmapSignature = 'B' | ('M' << 8);

///////////////////////////////////////////////////////////////////////////////
#pragma pack(2)
struct BitmapFileHeader {
	uint16_t m_signature;
	uint32_t m_fileSize;
	uint16_t m_reserved1;
	uint16_t m_reserved2;
	uint32_t m_offset;
};
static_assert(sizeof(BitmapFileHeader) == 14);
#pragma pack()

///////////////////////////////////////////////////////////////////////////////
struct BitmapInfoHeader {
	uint32_t m_headerSize;
	uint32_t m_width;
	uint32_t m_height;
	uint16_t m_colorPlanes;
	uint16_t m_bpp;
	uint32_t m_compression;
	uint32_t m_imageSize;
	uint32_t m_horizontalRes;
	uint32_t m_verticalRes;
	uint32_t m_colorsUsed;
	uint32_t m_importantColors;
};
static_assert(sizeof(BitmapInfoHeader) == 40);

///////////////////////////////////////////////////////////////////////////////
class Bitmap {
	BitmapFileHeader m_fileHeader;
	BitmapInfoHeader m_infoHeader;
	std::unique_ptr<uint8_t[]> m_image;

public:
	// getters
	uint16_t signature() const { return m_fileHeader.m_signature; }
	uint32_t fileSize() const { return m_fileHeader.m_fileSize; }
	uint16_t bpp() const { return m_infoHeader.m_bpp; }
	uint32_t headerSize() const { return m_infoHeader.m_headerSize; }
	uint8_t byteAt(int32_t x, int32_t y) const { return m_image[(height() - 1 - y)*rowSize() + x]; }

	uint32_t height() const;
	uint32_t rowSize() const;
	uint32_t imageSize() const;

	bool read(std::string_view filename);
	bool write(std::string_view filename) const;

	// image processing
	void invert() const;
	void verFlip() const;
	void horFlip() const;

	// image conversion
	Bitmap cvtToRGB() const;
	Bitmap cvtToARGB() const;
};
