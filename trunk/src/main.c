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



//#include <iostream>
#include <libopenraw/libopenraw.h>
//#include <libopenraw/debug.h>
#include <libopenraw-gnome/gdkpixbuf.h>


int save_pixbuf (GdkPixbuf *pixbuf, const char *path, int size)
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
	small = gdk_pixbuf_scale_simple (pixbuf, new_width, new_height, GDK_INTERP_TILES);
	if(!small) {
	  fprintf(stderr,"Error resizing image (memory?)\n");
	}
		
	a_width = g_strdup_printf ("%d", width);
	a_height = g_strdup_printf ("%d", height);


	if(gdk_pixbuf_save(small, path, "png", &err, "tEXt::Thumb::Image::Width", a_width,"tEXt::Thumb::Image::Height", a_height, NULL) == FALSE) {
		if (err != NULL) {
			g_print ("ERROR: Couldn't write the thumbnail '%s': %s\n", path, err->message);
			g_error_free (err);
			gdk_pixbuf_unref (small);
			return 1;
		} else {
			g_print ("ERROR: Couldn't write the thumbnail '%s'\n", path);
			gdk_pixbuf_unref (small);
			return 1;
		}
	}
	gdk_pixbuf_unref (small);
	return 0;
}

void printUsage()
{
	printf("Usage: rawthumbnailer [options] \n\n");
	printf("Options: \n");
	printf(" -i<s> : input file \n");
	printf(" -o<s> : output file \n");
	printf(" -s<n> : thumbnail size (default: 128) \n");
	printf(" -h     : display this help \n");
}

int main(int argc, char** argv)
{
	int option;
	unsigned int thumbnailSize = 128;
	const char* inputFile = NULL;
	const char* outputFile = NULL;

	while ((option = getopt (argc, argv, "i:o:s:r:h")) != -1)
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
				printf("Unknown command-line option\n");
				printUsage();
				return -1;
			default:
				fprintf(stderr, "Invalud arguments\n");
				printUsage();
				return -1;
		}
	}

	if(!inputFile || !outputFile) {
		printf("Invalud runtime arguments given\n");
		printUsage();
		return -1;
	}

	g_type_init();
	GdkPixbuf *pixbuf;
	pixbuf = or_gdkpixbuf_extract_rotated_thumbnail(inputFile, thumbnailSize);
	if(pixbuf == NULL) return -1;
	if (!save_pixbuf(pixbuf, outputFile, thumbnailSize)) return -1;

	return 0;
}

