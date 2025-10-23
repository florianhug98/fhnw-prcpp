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
  uint8_t m_b;
  uint8_t m_g;
  uint8_t m_r;

  RGB(const uint8_t b, const uint8_t g, const uint8_t r) : m_b(b), m_g(g), m_r(r) {}

  explicit RGB(const ARGB &argb);
};

static_assert(sizeof(RGB) == 24 / 8);

///////////////////////////////////////////////////////////////////////////////

struct ARGB {
  uint8_t m_b;
  uint8_t m_g;
  uint8_t m_r;
  uint8_t m_a;

  ARGB(const uint8_t b, const uint8_t g, const uint8_t r) : m_b(b), m_g(g), m_r(r), m_a(255) {
  }
  explicit ARGB(const RGB &rgb);
};

static_assert(sizeof(ARGB) == 32 / 8);

///////////////////////////////////////////////////////////////////////////////
RGB::RGB(const ARGB &argb) : m_b(argb.m_b), m_g(argb.m_g), m_r(argb.m_r) {
}

///////////////////////////////////////////////////////////////////////////////
ARGB::ARGB(const RGB &rgb) : m_a(255), m_r(rgb.m_r), m_g(rgb.m_g), m_b(rgb.m_b) {
}

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
  const auto width = static_cast<uint32_t>(std::abs(m_infoHeader.m_width));

  // width in pixel * bytes per pixel
  const uint32_t rawBytes = width * (m_infoHeader.m_bpp / 8);
  // pads so the size is a multiple of 4
  const uint32_t pad = (4 - rawBytes % 4) % 4;
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
  if (!fs.read(reinterpret_cast<char *>(&m_fileHeader), sizeof(BitmapFileHeader)) || m_fileHeader.
    m_signature != BitmapSignature) {
    std::cerr << "Invalid bitmap file header" << std::endl;
    return false;
  }

  // read bitmap info header
  if (!fs.read(reinterpret_cast<char *>(&m_infoHeader), sizeof(BitmapInfoHeader)) || m_infoHeader.
    m_headerSize < sizeof(BitmapInfoHeader)) {
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

  if (!fs.read(reinterpret_cast<char *>(m_image.get()), imageSize())) {
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
  if (!fs.write(reinterpret_cast<const char *>(&m_fileHeader), sizeof(BitmapFileHeader)) ||
    m_fileHeader.m_signature != BitmapSignature) {
    std::cerr << "Invalid bitmap file header" << std::endl;
    return false;
  }

  // write bitmap info header
  if (!fs.write(reinterpret_cast<const char *>(&m_infoHeader), sizeof(BitmapInfoHeader)) ||
    m_infoHeader.m_headerSize != sizeof(BitmapInfoHeader)) {
    std::cerr << "Invalid bitmap info header" << std::endl;
    return false;
  }

  // jump to image data
  fs.seekp(m_fileHeader.m_imageStart);

  if (!fs.write(reinterpret_cast<const char *>(m_image.get()), imageSize())) {
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
      // pointer to start of row
      uint8_t *pRow1 = m_image.get() + i * rowSize();
      // pointer to start of 'opposite' row of pRow1
      uint8_t *pRow2 = m_image.get() + (height() - 1 - i) * rowSize();
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
    const auto w = static_cast<uint32_t>(std::abs(m_infoHeader.m_width));
    const uint32_t bytesPerPixel = m_infoHeader.m_bpp / 8;
    for (uint32_t j = 0; j < height(); ++j) {
      // pointer to start of row
      uint8_t *pRow = m_image.get() + j * rowSize();
      const uint32_t wLast = w - 1;
      for (uint32_t i = 0; i < w / 2; ++i) {
        // pointer to pixel in row
        uint8_t *pPixel1 = pRow + i * bytesPerPixel;
        // pointer to 'oposite' pixel in row
        uint8_t *pPixel2 = pRow + (wLast - i) * bytesPerPixel;
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

    const auto w = static_cast<uint32_t>(std::abs(m_infoHeader.m_width));

    for (uint32_t y = 0; y < height(); ++y) {
      const uint8_t *pInRow = m_image.get() + y * rowSize();
      uint8_t *pOutRow = out.m_image.get() + y * out.rowSize();

      for (uint32_t x = 0; x < w; ++x) {
        const uint8_t *pInPixel = pInRow + x * 4;
        ARGB argb(pInPixel[0], pInPixel[1], pInPixel[2]);

        // Convert to RGB
        const RGB rgb(argb);

        uint8_t *pOutPixel = pOutRow + x * 3;
        pOutPixel[0] = rgb.m_b;
        pOutPixel[1] = rgb.m_g;
        pOutPixel[2] = rgb.m_r;
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

    const auto w = static_cast<uint32_t>(std::abs(m_infoHeader.m_width));

    // iterate through rows
    for (uint32_t y = 0; y < height(); ++y) {
      const uint8_t *pInRow = m_image.get() + y * rowSize();
      uint8_t *pOutRow = out.m_image.get() + y * out.rowSize();

      // iterate through pixels in given row
      for (uint32_t x = 0; x < w; ++x) {
        const uint8_t *pInPixel = pInRow + x * 3;
        RGB rgb(pInPixel[0], pInPixel[1], pInPixel[2]);

        // Convert to ARGB
        const ARGB argb(rgb);

        uint8_t *pOutPixel = pOutRow + x * 4;
        pOutPixel[0] = argb.m_b;
        pOutPixel[1] = argb.m_g;
        pOutPixel[2] = argb.m_r;
        pOutPixel[3] = argb.m_a;
      }
    }
  }

  return out;
}
