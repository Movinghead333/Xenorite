#include "texture.h"

#include <sstream>
#include <errno.h>
#include <fstream>

#include "simple_message_exception.h"
#include "type_definitions.h"


// constructor for creating a texture object with a given image width and height
// and image-data
Texture::Texture(
	int p_width,
	int p_height,
	const std::vector<ubyte>& p_image_data)
	:
	m_image_width(p_width),
	m_image_height(p_height),
	m_image_data(p_image_data)
{
}

// loads an image into a Texture object from given filename
const QImage Texture::load_texture(const std::string& p_filename)
{
	std::cout << "Loading tga-file: " << p_filename << std::endl;

	// open input-file-stream
	std::ifstream input_file(p_filename.c_str(),
		std::ios::in | std::ios::binary);

	if (!input_file.is_open())
	{
		std::stringstream temp_stream;
		temp_stream << "Could not open file: ";
		temp_stream << p_filename;
		throw Simple_Message_Exception(temp_stream.str());
	}

	// read the necessary header info
	ubyte temp_image_id_length = input_file.get();

	ubyte temp_color_map_type = input_file.get();

	ubyte temp_image_type_code = input_file.get();

	uword temp_color_map_origin = 0;
	input_file.read((char*)&temp_color_map_origin, 2);
	uword temp_color_map_length = 0;
	input_file.read((char*)&temp_color_map_length, 2);
	ubyte temp_color_map_entry_size = input_file.get();

	uword temp_x_origin = 0;
	input_file.read((char*)&temp_x_origin, 2);
	uword temp_y_origin = 0;
	input_file.read((char*)&temp_y_origin, 2);

	uword temp_image_width = 0;
	input_file.read((char*)&temp_image_width, 2);
	uword temp_image_height = 0;
	input_file.read((char*)&temp_image_height, 2);

	ubyte temp_bits_per_pixel = input_file.get();

	// skip byte with offset 17
	input_file.get();

	// check if the image type code matches uncompressed rgb
	if (temp_image_type_code != 2)
	{
		std::stringstream exception_stream;
		exception_stream << "Invalid image-data-type: ";
		exception_stream << temp_image_type_code;
		throw Simple_Message_Exception(exception_stream.str());
	}

	// check if the bits per pixel are equal to 32 thus storing ARGB values
	if (temp_bits_per_pixel != 32)
	{
		throw Simple_Message_Exception(
			"Bits per pixel are not equal to 32"
		);
	}

	// temporal variables for reading the imagedata
	std::vector<ubyte> temp_image_data = std::vector<ubyte>();
	temp_image_data.reserve(temp_image_width * temp_image_height *
		(temp_bits_per_pixel / 8));

	// go trough all pixels and read their ARGB values and
	// store them in the temp_image_data vector
	for (int y = 0; y < temp_image_height; y++)
	{
		for (int x = 0; x < temp_image_width; x++)
		{
			// push the 8bit values into the data vector
			temp_image_data.push_back(input_file.get()); // blue
			temp_image_data.push_back(input_file.get()); // green
			temp_image_data.push_back(input_file.get()); // red
			temp_image_data.push_back(input_file.get()); // alpha
		}
	}
	std::cout << "Image successfully loaded!" << std::endl;

	input_file.close();

	// return texture object
	return QImage(
		&temp_image_data[0],
		temp_image_width,
		temp_image_height,
		QImage::Format_ARGB32)
		.mirrored(false, true)
		.copy(); // TODO: cut copy if possible
}

// writes a given texture object back to tga-file on hdd
void Texture::write_texture_to_file(
	const std::string& p_filename,
	const Texture & p_texture)
{
	std::stringstream writing_file_message_stream;
	writing_file_message_stream << "Writing texture to file: ";
	writing_file_message_stream << p_filename;
	std::cout << writing_file_message_stream.str() << std::endl;

	// create output-stream
	std::ofstream outputfile(p_filename.c_str(), std::ios::binary);
	if (!outputfile)
	{
		throw Simple_Message_Exception("Cannot open outputstream");
	}

	ubyte raw_header[18] = { 0 };

	// write necessary information to the fileheader
	raw_header[2] = 2;

	raw_header[12] = p_texture.m_image_width;
	raw_header[13] = (p_texture.m_image_width >> 8) & 0xFF;
	raw_header[14] = p_texture.m_image_height;
	raw_header[15] = (p_texture.m_image_height >> 8) & 0xFF;
	raw_header[16] = 32;

	outputfile.write((const char*)raw_header, 18);

	// get reference to image-data
	std::vector<ubyte> temp_image_data = p_texture.get_image_data();

	// write the actual image-data
	for (int y = 0; y < p_texture.m_image_height; y++)
	{
		for (int x = 0; x < p_texture.m_image_width; x++)
		{
			// multiply by 4 because of the 4byte pixels (ARGB, 32bit)
			int temp_offset = (p_texture.m_image_height * y + x) * 4;
			outputfile.put((char)temp_image_data[temp_offset]); // blue
			outputfile.put((char)temp_image_data[temp_offset + 1]); // green
			outputfile.put((char)temp_image_data[temp_offset + 2]); // red
			outputfile.put((char)temp_image_data[temp_offset + 3]); // alpha
		}
	}

	// file-end tag
	static const char file_end[26] =
		"\0\0\0\0"  // no extension area
		"\0\0\0\0"  // no developer directory
		"TRUEVISION-XFILE"  // truevision tag
		".";
	outputfile.write(file_end, 26);

	// close the file to finish the writing process
	outputfile.close();

	std::cout << "Writing successful" << std::endl;
}

// getter methods
int Texture::get_width() const
{
	return m_image_width;
}

int Texture::get_height() const
{
	return m_image_height;
}

const std::vector<ubyte>& Texture::get_image_data() const
{
	return m_image_data;
}
