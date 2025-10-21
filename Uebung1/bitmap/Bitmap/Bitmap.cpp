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
// TODO Aufgabe 3: Klasse RGB

struct RGB {
public:
    uint8_t r;
    uint8_t g;
    uint8_t b;

    RGB() : r(0), g(0), b(0) {}

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

    ARGB() : a(255), r(0), g(0), b(0) {}
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
		// TODO Aufgabe 7
	}
}

///////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Flip this image vertically
/// </summary>
void Bitmap::verFlip() const {
	if (m_image) {
		// TODO Aufgabe 8
	}
}

///////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Flip this image horizontally
/// </summary>
void Bitmap::horFlip() const {
	if (m_image) {
		// TODO Aufgabe 9
	}
}

///////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Convert ARGB image to RGB format.
/// </summary>
/// <returns>converted image</returns>
Bitmap Bitmap::cvtToRGB() const {
	Bitmap out{};

	if (m_image && m_infoHeader.m_bpp == 32) {
		// TODO Aufgabe 10
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

	if (m_image && m_infoHeader.m_bpp == 24) {
		// TODO Aufgabe 10
	}
	return out;
}
