#include <fstream>
#include <iostream>
#include <algorithm>

#include "Bitmap.h"

// Author: 

///////////////////////////////////////////////////////////////////////////////
// https://en.wikipedia.org/wiki/BMP_file_format

///////////////////////////////////////////////////////////////////////////////
// prototype
struct ARGB;

///////////////////////////////////////////////////////////////////////////////
// TODO Aufgabe 3: Klasse RGB

static_assert(sizeof(RGB) == 24/8);

///////////////////////////////////////////////////////////////////////////////
// TODO Aufgabe 3: Klasse ARGB

static_assert(sizeof(ARGB) == 32/8);

///////////////////////////////////////////////////////////////////////////////
// TODO Aufgabe 3: RGB ctor

///////////////////////////////////////////////////////////////////////////////
// TODO Aufgabe 3: ARGB ctor

///////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Return image height in pixels
/// </summary>
uint32_t Bitmap::height() const {
	// TODO Aufgabe 4: return number of image rows
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Compute and return image row size in bytes
/// </summary>
/// <returns>number of bytes per image row</returns>
uint32_t Bitmap::rowSize() const {
	// TODO Aufgabe 4: compute and return row size (a multiple of 4)
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Compute and return image size in bytes
/// </summary>
/// <returns>image size in bytes</returns>
uint32_t Bitmap::imageSize() const {
	// TODO Aufgabe 4: compute and return image size
	return 0;
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

	// TODO Aufgabe 5: allocate image data

	// TODO Aufgabe 5: read image data

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

	// TODO Aufgabe 6: write image data

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
