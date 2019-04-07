#pragma once

#include <vector>
#include <iostream> // debug
#include <string>

#include <qimage.h>

#include "type_definitions.h"

// stores the important header and data information from a tga-file in
// suited data-structure
class Texture
{
public:
	// creates a Texture object by passing a width and height of the image
	// as well as a Pixel-vector holding the image-data
	Texture(int p_width, int p_height, const std::vector<ubyte>& p_image_data);

	// load Texture from filename
	static const QImage load_texture(const std::string& p_filename);

	// load Texture from png file
	static const QImage load_png(const std::string& p_filename);

	// write a texture to a tga file in local directory
	static void write_texture_to_file(
		const std::string& filename,
		const Texture& p_texture);


	// getter methods
	int get_width()  const;
	int get_height() const;

	const std::vector<ubyte>& get_image_data() const;

private:
	// width and height of the image
	const int m_image_width;
	const int m_image_height;

	// stores every pixel from the input image in an ARGB Pixelobject
	const std::vector<ubyte> m_image_data;
};
