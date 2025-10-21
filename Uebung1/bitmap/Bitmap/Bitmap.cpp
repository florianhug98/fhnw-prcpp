#include <fstream>
#include <iostream>
#include <algorithm>

#include "Bitmap.h"

// Author: Florian Hug

///////////////////////////////////////////////////////////////////////////////
// https://en.wikipedia.org/wiki/BMP_file_format

///////////////////////////////////////////////////////////////////////////////
// prototype
struct ARGB;
struct RGB;

///////////////////////////////////////////////////////////////////////////////
struct RGB {
public:
    uint8_t r;
    uint8_t g;
    uint8_t b;

    RGB(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b) {}

    explicit RGB(const ARGB& argb);
};

static_assert(sizeof(RGB) == 24/8);

///////////////////////////////////////////////////////////////////////////////

struct ARGB {
public:
    uint8_t a;
    uint8_t r;
    uint8_t g;
    uint8_t b;

    ARGB(uint8_t r, uint8_t g, uint8_t b) : a(255), r(r), g(g), b(b) {}
	explicit ARGB(const RGB& rgb);
};

static_assert(sizeof(ARGB) == 32/8);

///////////////////////////////////////////////////////////////////////////////
RGB::RGB(const ARGB& argb) : r(argb.r), g(argb.g), b(argb.b) {}

///////////////////////////////////////////////////////////////////////////////
ARGB::ARGB(const RGB& rgb) : a(255), r(rgb.r), g(rgb.g), b(rgb.b) {}

///////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Return image height in pixels
/// </summary>
uint32_t Bitmap::height() const {
	return static_cast<uint32_t>(std::abs(m_infoHeader.m_height));
}

///////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Compute and return image row size in bytes
/// </summary>
/// <returns>number of bytes per image row</returns>
uint32_t Bitmap::rowSize() const {

	uint32_t width = static_cast<uint32_t>(std::abs(m_infoHeader.m_width));

	// width in pixel * bytes per pixel
	uint32_t rawBytes = width * (m_infoHeader.m_bpp / 8);
	// pads so the size is a multiple of 4
	uint32_t pad = (4 - (rawBytes % 4)) % 4;
	return rawBytes + pad;
}

///////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Compute and return image size in bytes
/// </summary>
/// <returns>image size in bytes</returns>
uint32_t Bitmap::imageSize() const {
	return height() * rowSize();
}

///////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Read Windows bitmap file
/// </summary>
/// <param name="filename">file path</param>
/// <returns>true: reading was successful</returns>
bool Bitmap::read(std::string_view filename) {
	std::ifstream fs(filename.data(), std::ios::in | std::ios::binary);

	if (!fs) {
		std::cerr << "File can't be opened for reading" << std::endl;
		return false;
	}

	// read bitmap file header
	if (!fs.read(reinterpret_cast<char*>(&m_fileHeader), sizeof(BitmapFileHeader)) || m_fileHeader.m_signature != BitmapSignature) {
		std::cerr << "Invalid bitmap file header" << std::endl;
		return false;
	}

	// read bitmap info header
	if (!fs.read(reinterpret_cast<char*>(&m_infoHeader), sizeof(BitmapInfoHeader)) || m_infoHeader.m_headerSize < sizeof(BitmapInfoHeader)) {
		std::cerr << "Invalid bitmap info header" << std::endl;
		return false;
	}

	// check info header
	if (m_infoHeader.m_bpp != 24 && m_infoHeader.m_bpp != 32) {
		std::cerr << "Unsupported bitmap format" << std::endl;
		return false;
	}
	if (m_infoHeader.m_imageSize != 0 && m_infoHeader.m_imageSize != imageSize()) {
		std::cerr << "Invalid image size" << std::endl;
		return false;
	}

	// jump to image data
	fs.seekg(m_fileHeader.m_imageStart);

	m_image = std::make_unique_for_overwrite<uint8_t[]>(imageSize());

	if (!fs.read(reinterpret_cast<char*>(m_image.get()), imageSize())) {
		std::cerr << "Error reading image data" << std::endl;
		return false;
	}

	return true;
}

///////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Write bitmap to file
/// </summary>
/// <param name="filename">file path</param>
/// <returns>true: writing was successful</returns>
bool Bitmap::write(std::string_view filename) const {
	std::ofstream fs(filename.data(), std::ios::out | std::ios::binary);

	if (!fs) {
		std::cerr << "File can't be opened for writing" << std::endl;
		return false;
	}

	// check info header
	if (m_infoHeader.m_bpp != 24 && m_infoHeader.m_bpp != 32) {
		std::cerr << "Unsupported bitmap format" << std::endl;
		return false;
	}
	if (m_infoHeader.m_imageSize != 0 && m_infoHeader.m_imageSize != imageSize()) {
		std::cerr << "Invalid image size" << std::endl;
		return false;
	}

	// write bitmap file header
	if (!fs.write(reinterpret_cast<const char*>(&m_fileHeader), sizeof(BitmapFileHeader)) || m_fileHeader.m_signature != BitmapSignature) {
		std::cerr << "Invalid bitmap file header" << std::endl;
		return false;
	}

	// write bitmap info header
	if (!fs.write(reinterpret_cast<const char*>(&m_infoHeader), sizeof(BitmapInfoHeader)) || m_infoHeader.m_headerSize != sizeof(BitmapInfoHeader)) {
		std::cerr << "Invalid bitmap info header" << std::endl;
		return false;
	}

	// jump to image data
	fs.seekp(m_fileHeader.m_imageStart);

	if (!fs.write(reinterpret_cast<const char*>(m_image.get()), imageSize())) {
		std::cerr << "Error writing image data" << std::endl;
		return false;
	}

	return true;
}

///////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Invert this image
/// </summary>
void Bitmap::invert() const {
	if (m_image) {
		for (uint32_t i = 0; i < imageSize(); ++i) {
			m_image[i] = ~m_image[i];
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Flip this image vertically
/// </summary>
void Bitmap::verFlip() const {
	if (m_image) {
		for (uint32_t i = 0; i < height() / 2; ++i) {
			uint8_t* pRow1 = m_image.get() + i * rowSize();
			uint8_t* pRow2 = m_image.get() + (height() - 1 - i) * rowSize();
			for (uint32_t j = 0; j < rowSize(); ++j) {
				std::swap(pRow1[j], pRow2[j]);
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Flip this image horizontally
/// </summary>
void Bitmap::horFlip() const {
	if (m_image) {
		uint32_t w = static_cast<uint32_t>(std::abs(m_infoHeader.m_width));
		uint32_t bytesPerPixel = m_infoHeader.m_bpp / 8;
		for (uint32_t y = 0; y < height(); ++y) {
			uint8_t* pRow = m_image.get() + y * rowSize();
			uint32_t wLast = w - 1;
			for (uint32_t i = 0; i < w / 2; ++i) {
				uint8_t* pPixel1 = pRow + i * bytesPerPixel;
				uint8_t* pPixel2 = pRow + (wLast - i) * bytesPerPixel;
				for (uint32_t b = 0; b < bytesPerPixel; ++b) {
					std::swap(pPixel1[b], pPixel2[b]);
				}
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Convert ARGB image to RGB format.
/// </summary>
/// <returns>converted image</returns>
Bitmap Bitmap::cvtToRGB() const {
	Bitmap out{};

	// if image is ARGB
	if (m_image && m_infoHeader.m_bpp == 32) {

		out.m_fileHeader = m_fileHeader;
		out.m_infoHeader = m_infoHeader;

		// Adjust for RGB format
		out.m_infoHeader.m_bpp = 24;
		out.m_infoHeader.m_imageSize = out.imageSize();
		out.m_fileHeader.m_fileSize = out.m_fileHeader.m_imageStart + out.m_infoHeader.m_imageSize;

		out.m_image = std::make_unique_for_overwrite<uint8_t[]>(out.imageSize());

		uint32_t w = static_cast<uint32_t>(std::abs(m_infoHeader.m_width));
		uint32_t h = height();

		std::cout << w << std::endl;
		std::cout << rowSize() / 4 << std::endl;

		for (uint32_t y = 0; y < h; ++y) {
			const uint8_t* inRow = m_image.get() + y * rowSize();
			uint8_t* outRow = out.m_image.get() + y * out.rowSize();

			for (uint32_t x = 0; x < w; ++x) {
				const uint8_t* inPixel = inRow + x * 4;
				ARGB argb(inPixel[2], inPixel[1], inPixel[0]);

				// Convert to RGB
				RGB rgb(argb);

				uint8_t* outPixel = outRow + x * 3;
				outPixel[0] = rgb.b;
				outPixel[1] = rgb.g;
				outPixel[2] = rgb.r;
			}
		}
	}

	return out;
}

///////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Convert RGB image to ARGB format.
/// </summary>
/// <returns>converted image</returns>
Bitmap Bitmap::cvtToARGB() const {
	Bitmap out{};

	// if image is RGB
	if (m_image && m_infoHeader.m_bpp == 24) {

		out.m_fileHeader = m_fileHeader;
		out.m_infoHeader = m_infoHeader;

		// Adjust for ARGB format
		out.m_infoHeader.m_bpp = 32;
		out.m_infoHeader.m_imageSize = out.imageSize();
		out.m_fileHeader.m_fileSize = out.m_fileHeader.m_imageStart + out.m_infoHeader.m_imageSize;

		out.m_image = std::make_unique_for_overwrite<uint8_t[]>(out.imageSize());

		uint32_t w = static_cast<uint32_t>(std::abs(m_infoHeader.m_width));

		std::cout << w << std::endl;
		std::cout << rowSize() / 3 << std::endl;

		// iterate through rows
		for (uint32_t y = 0; y < height(); ++y) {
			const uint8_t* inRow = m_image.get() + y * rowSize();
			uint8_t* outRow = out.m_image.get() + y * out.rowSize();

			// iterate through pixels in given row
			for (uint32_t x = 0; x < w; ++x) {
				const uint8_t* inPixel = inRow + x * 3;
				RGB rgb(inPixel[2], inPixel[1], inPixel[0]);

				// Convert to ARGB
				ARGB argb(rgb);

				uint8_t* outPixel = outRow + x * 4;
				outPixel[0] = argb.b;
				outPixel[1] = argb.g;
				outPixel[2] = argb.r;
				outPixel[3] = argb.a;
			}
		}
	}

	return out;
}
