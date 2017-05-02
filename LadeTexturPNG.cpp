/*
 * imageloader.cpp
 *
 *  Created on: Feb 12, 2017
 *      Author: nopper
 */

/* Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above notice and this permission notice shall be included in all copies
 * or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
/* File for "Textures" lesson of the OpenGL tutorial on
 * www.videotutorialsrock.com
 */

#include <GL/glut.h>
#include <assert.h>
#include <fstream>
#include <map>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <png.h>
#include <iostream>

#include "LadeTexturPNG.h"

using namespace std;

Image::Image(char* ps, int w, int h) :
		pixels(ps), width(w), height(h) {

}

Image::~Image() {
	delete[] pixels;
}

namespace {
//Converts a four-character array to an integer, using little-endian form
int toInt(const char* bytes) {
	return (int) (((unsigned char) bytes[3] << 24)
			| ((unsigned char) bytes[2] << 16) | ((unsigned char) bytes[1] << 8)
			| (unsigned char) bytes[0]);
}

//Converts a two-character array to a short, using little-endian form
short toShort(const char* bytes) {
	return (short) (((unsigned char) bytes[1] << 8) | (unsigned char) bytes[0]);
}

//Reads the next four bytes as an integer, using little-endian form
int readInt(ifstream &input) {
	char buffer[4];
	input.read(buffer, 4);
	return toInt(buffer);
}

//Reads the next two bytes as a short, using little-endian form
short readShort(ifstream &input) {
	char buffer[2];
	input.read(buffer, 2);
	return toShort(buffer);
}

//Just like auto_ptr, but for arrays
template<class T>
class auto_array {
private:
	T* array;
	mutable bool isReleased;
public:
	explicit auto_array(T* array_ = NULL) :
			array(array_), isReleased(false) {
	}

	auto_array(const auto_array<T> &aarray) {
		array = aarray.array;
		isReleased = aarray.isReleased;
		aarray.isReleased = true;
	}

	~auto_array() {
		if (!isReleased && array != NULL) {
			delete[] array;
		}
	}

	T* get() const {
		return array;
	}

	T &operator*() const {
		return *array;
	}

	void operator=(const auto_array<T> &aarray) {
		if (!isReleased && array != NULL) {
			delete[] array;
		}
		array = aarray.array;
		isReleased = aarray.isReleased;
		aarray.isReleased = true;
	}

	T* operator->() const {
		return array;
	}

	T* release() {
		isReleased = true;
		return array;
	}

	void reset(T* array_ = NULL) {
		if (!isReleased && array != NULL) {
			delete[] array;
		}
		array = array_;
	}

	T* operator+(int i) {
		return array + i;
	}

	T &operator[](int i) {
		return array[i];
	}
};
}

Image* loadBMP(const std::string filename) {
	ifstream input;
	input.open(filename.c_str(), ifstream::binary);
	assert(!input.fail() || !"Could not find file");
	char buffer[2];
	input.read(buffer, 2);
	assert((buffer[0] == 'B' && buffer[1] == 'M') || !"Not a bitmap file");
	input.ignore(8);
	int dataOffset = readInt(input);

	//Read the header
	int headerSize = readInt(input);
	int width;
	int height;
	switch (headerSize) {
	case 40:
		//V3
		width = readInt(input);
		height = readInt(input);
		input.ignore(2);
		assert(readShort(input) == 24 || !"Image is not 24 bits per pixel");
		assert(readShort(input) == 0 || !"Image is compressed");
		break;
	case 12:
		//OS/2 V1

		width = readShort(input);
		height = readShort(input);
		input.ignore(2);
		assert(readShort(input) == 24 || !"Image is not 24 bits per pixel");
		break;
	case 64:
		//OS/2 V2
		assert(!"Can't load OS/2 V2 bitmaps");
		break;
	case 108:
		//Windows V4
		assert(!"Can't load Windows V4 bitmaps");
		break;
	case 124:
		//Windows V5
		assert(!"Can't load Windows V5 bitmaps");
		break;
	default:
		assert(!"Unknown bitmap format");
	}

	//Read the data
	int bytesPerRow = ((width * 3 + 3) / 4) * 4 - (width * 3 % 4);
	int size = bytesPerRow * height;
	auto_array<char> pixels(new char[size]);
	input.seekg(dataOffset, ios_base::beg);
	input.read(pixels.get(), size);

	//Get the data into the right format
	auto_array<char> pixels2(new char[width * height * 3]);
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			for (int c = 0; c < 3; c++) {
				pixels2[3 * (width * y + x) + c] = pixels[bytesPerRow * y
						+ 3 * x + (2 - c)];
			}
		}
	}

	input.close();
	return new Image(pixels2.release(), width, height);
}

void ladeTexturBMP(std::string filename, std::map<std::string, GLuint>& Texturen) {
	// Lade das Bild in das Objekt image
	Image* myImage = loadBMP(filename.c_str());
	GLuint textureNr = 0;
	// Lege das Bild als Textur an.
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &textureNr);
	glBindTexture(GL_TEXTURE_2D, textureNr);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, myImage->width, myImage->height, 0,
	GL_RGB, GL_UNSIGNED_BYTE, myImage->pixels);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //GL_NEAREST);//
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	Texturen[filename] = textureNr;
	std::cout << "Bild '" << filename << "' geladen, ist jetzt Textur Nr. "
			<< Texturen[filename] << std::endl;
}


float Image::getPixelValue(int x, int y, int c) {

	float rt = pixels[3 * (width * y + x) + 0];
	if (rt < 0)
		rt += 256;
	rt /= 255;

	float gt = pixels[3 * (width * y + x) + 1];
	if (gt < 0)
		gt += 256;
	gt /= 255;

	float bt = pixels[3 * (width * y + x) + 2];
	if (bt < 0)
		bt += 256;
	bt /= 255;

	float yt = 0.299 * rt + 0.587 * gt + 0.114 * bt;
	float ut = (bt - yt) * .493;
	float vt = (rt - yt) * .877;

	if (c == 0)
		return yt;
	if (c == 1)
		return ut;
	return vt;

}

bool loadPngImage(const char *name, int &outWidth, int &outHeight, bool &outHasAlpha,
		GLubyte **outData) {
	png_structp png_ptr;
	png_infop info_ptr;
	unsigned int sig_read = 0;
	int color_type, interlace_type;
	FILE *fp;

	if ((fp = fopen(name, "rb")) == NULL)
		return false;

	/* Create and initialize the png_struct
	 * with the desired error handler
	 * functions.  If you want to use the
	 * default stderr and longjump method,
	 * you can supply NULL for the last
	 * three parameters.  We also supply the
	 * the compiler header file version, so
	 * that we know if the application
	 * was compiled with a compatible version
	 * of the library.  REQUIRED
	 */
	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,
	NULL, NULL, NULL);

	if (png_ptr == NULL) {
		fclose(fp);
		return false;
	}

	/* Allocate/initialize the memory
	 * for image information.  REQUIRED. */
	info_ptr = png_create_info_struct(png_ptr);
	if (info_ptr == NULL) {
		fclose(fp);
		png_destroy_read_struct(&png_ptr, NULL, NULL);
		return false;
	}

	//if (png_get_color_type(png_ptr, info_ptr) == PNG_COLOR_TYPE_RGB) outHasAlpha = false;
	//else if (png_get_color_type(png_ptr, info_ptr) == PNG_COLOR_TYPE_RGBA) outHasAlpha = true;
	//else if (png_get_color_type(png_ptr, info_ptr) == PNG_COLOR_TYPE_RGB_ALPHA) outHasAlpha = true;
	//else exit(0);

	/* Set error handling if you are
	 * using the setjmp/longjmp method
	 * (this is the normal method of
	 * doing things with libpng).
	 * REQUIRED unless you  set up
	 * your own error handlers in
	 * the png_create_read_struct()
	 * earlier.
	 */
	if (setjmp(png_jmpbuf(png_ptr))) {
		/* Free all of the memory associated
		 * with the png_ptr and info_ptr */
		png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
		fclose(fp);
		/* If we get here, we had a
		 * problem reading the file */
		return false;
	}

	/* Set up the output control if
	 * you are using standard C streams */
	png_init_io(png_ptr, fp);

	/* If we have already
	 * read some of the signature */
	png_set_sig_bytes(png_ptr, sig_read);

	/*
	 * If you have enough memory to read
	 * in the entire image at once, and
	 * you need to specify only
	 * transforms that can be controlled
	 * with one of the PNG_TRANSFORM_*
	 * bits (this presently excludes
	 * dithering, filling, setting
	 * background, and doing gamma
	 * adjustment), then you can read the
	 * entire image (including pixels)
	 * into the info structure with this
	 * call
	 *
	 * PNG_TRANSFORM_STRIP_16 |
	 * PNG_TRANSFORM_PACKING  forces 8 bit
	 * PNG_TRANSFORM_EXPAND forces to
	 *  expand a palette into RGB
	 */
	png_read_png(png_ptr, info_ptr,
	PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND,
			NULL);

	png_uint_32 width, height;
	int bit_depth;
	png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type,
			&interlace_type, NULL, NULL);
	outWidth = width;
	outHeight = height;

	outHasAlpha =
			((png_get_color_type(png_ptr, info_ptr) & PNG_COLOR_MASK_ALPHA) != 0);

	unsigned int row_bytes = png_get_rowbytes(png_ptr, info_ptr);
	*outData = (unsigned char*) malloc(row_bytes * outHeight);

	png_bytepp row_pointers = png_get_rows(png_ptr, info_ptr);

	for (int i = 0; i < outHeight; i++) {
		// note that png is ordered top to
		// bottom, but OpenGL expect it bottom to top
		// so the order or swapped
		memcpy(*outData + (row_bytes * (outHeight - 1 - i)), row_pointers[i],
				row_bytes);
	}

	/* Clean up after the read,
	 * and free any memory allocated */
	png_destroy_read_struct(&png_ptr, &info_ptr, NULL);

	/* Close the file */
	fclose(fp);

	/* That's it */
	return true;
}


GLuint LadeTexturPNG(const std::string filename)
{
	int width, height;
		bool hasAlpha;

		GLubyte *textureImage;
		bool success = loadPngImage(filename.c_str(), width, height, hasAlpha,
				&textureImage);
		if (!success) {
			std::cerr << "Unable to load png file " << filename << std::endl;
			return -1;
		}

		glEnable(GL_TEXTURE_2D);
		GLuint textureNr = 0;
		glGenTextures(1, &textureNr);
		glBindTexture(GL_TEXTURE_2D, textureNr);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexImage2D(GL_TEXTURE_2D, 0, hasAlpha ? 4 : 3, width, height, 0,
				hasAlpha ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, textureImage);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //GL_NEAREST);//
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		std::cout << "Bild '" << filename << "' geladen, ist jetzt Textur Nr. "
				<< textureNr << std::endl;
		return textureNr;
}


void LadeTexturPNG(const std::string filename, std::map<std::string, GLuint>& Texturen)
{
	Texturen[filename] = LadeTexturPNG(filename);
}

