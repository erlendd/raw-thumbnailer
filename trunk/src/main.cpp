/*
 *
 * Copyright (C) 2007 Erlend Davidson
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */



#include <iostream>
#include <libopenraw/libopenraw.h>
//#include <libopenraw/debug.h>
#include <libopenraw-gnome/gdkpixbuf.h>


bool save_pixbuf (GdkPixbuf *pixbuf, const char *path, int size)
{
	GdkPixbuf *small = NULL;
	GError *err = NULL;
	char *a_width, *a_height;
	int width, height;
	height = gdk_pixbuf_get_height (pixbuf);
	width = gdk_pixbuf_get_width (pixbuf);
	int new_width, new_height;
	if (width > height) { // landscape
		new_width = size;
		new_height = size * height / width;
	} else { // portrait
		new_height = size;
		new_width = size * width / height;
	}
	//std::cout << "About to scale image from original "<<width<<"x"<<height<<" to "<<new_width<<"x"<<new_height << std::endl;
	small = gdk_pixbuf_scale_simple (pixbuf, new_width, new_height, GDK_INTERP_TILES);
	if(!small) {
		std::cerr << "Error resizing image (memory?)" << std::endl;
	}
		
	a_width = g_strdup_printf ("%d", width);
	a_height = g_strdup_printf ("%d", height);


	if(gdk_pixbuf_save(small, path, "png", &err, "tEXt::Thumb::Image::Width", a_width,"tEXt::Thumb::Image::Height", a_height, NULL) == FALSE) {
		if (err != NULL) {
			g_print ("ERROR: Couldn't write the thumbnail '%s': %s\n", path, err->message);
			g_error_free (err);
			gdk_pixbuf_unref (small);
			return false;
		} else {
			g_print ("ERROR: Couldn't write the thumbnail '%s'\n", path);
			gdk_pixbuf_unref (small);
			return false;
		}
	}
	gdk_pixbuf_unref (small);
	return true;
}

void printUsage()
{
	std::cout << "Usage: rawthumbnailer [options]" << std::endl << std::endl
	 << "Options:" << std::endl
	 << "  -i<s>  : input file" << std::endl
	 << "  -o<s>  : output file" << std::endl
	 << "  -s<n>  : thumbnail size (default: 128)" << std::endl
	 << "  -h     : display this help" << std::endl;
}

int main(int argc, char** argv)
{
	int option;
	unsigned int thumbnailSize = 128;
	const char* inputFile = NULL;
	const char* outputFile = NULL;

	while ((option = getopt (argc, argv, "i:o:s:h")) != -1)
	{
		switch (option)
		{
			case 'i':
				inputFile = optarg;
				break;
			case 'o':
				outputFile = optarg;
				break;
			case 's':
				thumbnailSize = atoi(optarg);
				break;
			case 'h':
				printUsage();
				return 0;
			case '?':
				std::cerr << std::endl << "Unknown command-line option" << std::endl;
				printUsage();
				return -1;
			default:
				std::cerr << std::endl << "invalid arguments" << std::endl;
				printUsage();
				return -1;
		}
	}

	/*std::cout << "thumbnailSize=" << thumbnailSize << std::endl
		<< "inputFile=" << inputFile << std::endl
		<< "outputFile=" << outputFile << std::endl;
	*/

	if(!inputFile || !outputFile) {
		std::cout << std::endl << "Invalid runtime arguments given" << std::endl;
		printUsage();
		return -1;
	}

	g_type_init();
	GdkPixbuf *pixbuf;
	pixbuf = or_gdkpixbuf_extract_thumbnail(inputFile, thumbnailSize);
	if(pixbuf == NULL) return -1;
	if (!save_pixbuf(pixbuf, outputFile, thumbnailSize)) return -1;

	return 0;
}

