// compressTMAPS.cpp : Tento soubor obsahuje funkci main. Provádění programu se tam zahajuje a ukončuje.
//

#include <iostream>

#include "png.h"

#pragma comment(lib, "zlib.lib") // must be before libpng!
#ifndef _WIN64
#pragma comment(lib, "libpng15.lib") // must be after zlib!
#else
#endif

//#define level1 //TMAPS1 night
#define level2 //TMAPS0 day
//#define level4 //TMAPS2 cave


#define SIZEOF_UNSIGNED_INT 4

#define SIZEOF_UNSIGNED_CHAR 1

#define SIZEOF_UNSIGNED_SHORT 2

#if SIZEOF_UNSIGNED_SHORT != 2
#  error "sizeof (unsigned short) != 2"
#else
typedef unsigned short Bit16u;
typedef   signed short Bit16s;
#endif

#if SIZEOF_UNSIGNED_INT == 4
typedef unsigned int Bit32u;
typedef   signed int Bit32s;
#elif SIZEOF_UNSIGNED_LONG == 4
typedef unsigned long Bit32u;
typedef   signed long Bit32s;
#else
//#  error "can't find sizeof(type) of 4 bytes!"
#endif

#if SIZEOF_UNSIGNED_CHAR != 1
#  error "sizeof (unsigned char) != 1"
#else
typedef unsigned char Bit8u;
typedef   signed char Bit8s;
#endif

typedef          char   int8;
typedef   signed char   sint8;
typedef unsigned char   uint8;
typedef          short  int16;
typedef   signed short  sint16;
typedef unsigned short  uint16;
typedef          int    int32;
typedef   signed int    sint32;
typedef unsigned int    uint32;

int width, height;
png_byte color_type;
png_byte bit_depth;
png_bytep* row_pointers = NULL;


//png_bytep* row_alphapointers = NULL;


int file_exist(char* filename)
{
	struct stat   buffer;
	return (stat(filename, &buffer) == 0);
}

void read_png_file(char* filename) {
	FILE* fp;
	fopen_s(&fp,filename, "rb");

	png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!png) abort();

	png_infop info = png_create_info_struct(png);
	if (!info) abort();

	if (setjmp(png_jmpbuf(png))) abort();

	png_init_io(png, fp);

	png_read_info(png, info);

	width = png_get_image_width(png, info);
	height = png_get_image_height(png, info);
	color_type = png_get_color_type(png, info);
	bit_depth = png_get_bit_depth(png, info);

	// Read any color_type into 8bit depth, RGBA format.
	// See http://www.libpng.org/pub/png/libpng-manual.txt

	if (bit_depth == 16)
		png_set_strip_16(png);

	if (color_type == PNG_COLOR_TYPE_PALETTE)
		png_set_palette_to_rgb(png);

	// PNG_COLOR_TYPE_GRAY_ALPHA is always 8 or 16bit depth.
	if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
		png_set_expand_gray_1_2_4_to_8(png);

	if (png_get_valid(png, info, PNG_INFO_tRNS))
		png_set_tRNS_to_alpha(png);

	// These color_type don't have an alpha channel then fill it with 0xff.
	if (color_type == PNG_COLOR_TYPE_RGB ||
		color_type == PNG_COLOR_TYPE_GRAY ||
		color_type == PNG_COLOR_TYPE_PALETTE)
		png_set_filler(png, 0xFF, PNG_FILLER_AFTER);

	if (color_type == PNG_COLOR_TYPE_GRAY ||
		color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
		png_set_gray_to_rgb(png);

	png_read_update_info(png, info);

	//if (row_pointers) abort();

	row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * height);
	for (int y = 0; y < height; y++) {
		row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(png, info));
	}

	png_read_image(png, row_pointers);

	fclose(fp);

	png_destroy_read_struct(&png, &info, NULL);
}
/*
void read_pngalpha_file(char* filename) {
	FILE* fp;
	fopen_s(&fp, filename, "rb");

	png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!png) abort();

	png_infop info = png_create_info_struct(png);
	if (!info) abort();

	if (setjmp(png_jmpbuf(png))) abort();

	png_init_io(png, fp);

	png_read_info(png, info);

	width = png_get_image_width(png, info);
	height = png_get_image_height(png, info);
	color_type = png_get_color_type(png, info);
	bit_depth = png_get_bit_depth(png, info);

	// Read any color_type into 8bit depth, RGBA format.
	// See http://www.libpng.org/pub/png/libpng-manual.txt

	if (bit_depth == 16)
		png_set_strip_16(png);

	if (color_type == PNG_COLOR_TYPE_PALETTE)
		png_set_palette_to_rgb(png);

	// PNG_COLOR_TYPE_GRAY_ALPHA is always 8 or 16bit depth.
	if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
		png_set_expand_gray_1_2_4_to_8(png);

	if (png_get_valid(png, info, PNG_INFO_tRNS))
		png_set_tRNS_to_alpha(png);

	// These color_type don't have an alpha channel then fill it with 0xff.
	if (color_type == PNG_COLOR_TYPE_RGB ||
		color_type == PNG_COLOR_TYPE_GRAY ||
		color_type == PNG_COLOR_TYPE_PALETTE)
		png_set_filler(png, 0xFF, PNG_FILLER_AFTER);

	if (color_type == PNG_COLOR_TYPE_GRAY ||
		color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
		png_set_gray_to_rgb(png);

	png_read_update_info(png, info);

	//if (row_alphapointers) abort();

	row_alphapointers = (png_bytep*)malloc(sizeof(png_bytep) * height);
	for (int y = 0; y < height; y++) {
		row_alphapointers[y] = (png_byte*)malloc(png_get_rowbytes(png, info));
	}

	png_read_image(png, row_alphapointers);

	fclose(fp);

	png_destroy_read_struct(&png, &info, NULL);
}
*/
int transparentColor = 0;
int getIndexedColor(int colorR, int colorG, int colorB, unsigned char* palette, int paletteSize) {
	int index;
	int diference = 10000000000;
	for (int i = 0; i < paletteSize / 3; i++)
	{
		if (transparentColor != i)
		{
			int testDiference = (abs(colorR - palette[i * 3 + 0]) + abs(colorG - palette[i * 3 + 1]) + abs(colorB - palette[i * 3 + 2]));
			if (testDiference < diference)
			{
				index = i;
				diference = testDiference;
			}
		}
	}
	return index;
};

inline void setRGBA(png_byte* ptr, Bit8u* val)
{
	ptr[0] = val[0];
	ptr[1] = val[1];
	ptr[2] = val[2];
	ptr[3] = val[3];
}

void writeImagePNG(char* filename, int width, int height, Bit8u* buffer, char* title)
{
	int code = 0;
	FILE* fp = NULL;
	png_structp png_ptr = NULL;
	png_infop info_ptr = NULL;
	png_bytep row = NULL;

	// Open file for writing (binary mode)
	fopen_s(&fp, filename, "wb");
	if (fp == NULL) {
		fprintf(stderr, "Could not open file %s for writing\n", filename);
		code = 1;
		goto finalise;
	}

	// Initialize write structure
	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (png_ptr == NULL) {
		fprintf(stderr, "Could not allocate write struct\n");
		code = 1;
		goto finalise;
	}

	// Initialize info structure
	info_ptr = png_create_info_struct(png_ptr);
	if (info_ptr == NULL) {
		fprintf(stderr, "Could not allocate info struct\n");
		code = 1;
		goto finalise;
	}

	// Setup Exception handling
	if (setjmp(png_jmpbuf(png_ptr))) {
		fprintf(stderr, "Error during png creation\n");
		code = 1;
		goto finalise;
	}

	png_init_io(png_ptr, fp);

	// Write header (8 bit colour depth)
	png_set_IHDR(png_ptr, info_ptr, width, height,
		8, PNG_COLOR_TYPE_RGBA, PNG_INTERLACE_NONE,
		PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

	// Set title
	if (title != NULL) {
		png_text title_text;
		title_text.compression = PNG_TEXT_COMPRESSION_NONE;
		title_text.key = (png_charp)"Title";
		title_text.text = title;
		png_set_text(png_ptr, info_ptr, &title_text, 1);
	}

	png_write_info(png_ptr, info_ptr);

	// Allocate memory for one row (3 bytes per pixel - RGB)
	row = (png_bytep)malloc(4 * width * sizeof(png_byte));

	// Write image data
	int x, y;
	for (y = 0; y < height; y++) {
		for (x = 0; x < width; x++) {
			setRGBA(&(row[x * 4]), buffer + (y * width + x) * 4);
		}
		png_write_row(png_ptr, row);
	}

	// End write
	png_write_end(png_ptr, NULL);

finalise:
	if (fp != NULL) fclose(fp);
	if (info_ptr != NULL) png_free_data(png_ptr, info_ptr, PNG_FREE_ALL, -1);
	if (png_ptr != NULL) png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
	if (row != NULL) free(row);

	//return code;
}

char buffer[4096*4096];

int main()
{
#ifdef level1
	const char* standartpal_filename = "c:\\prenos\\remc2\\tools\\palletelight\\Debug\\\out-n.pal";
	const char* data_filename = "c:\\prenos\\remc2\\tools\\decompressTMAPS\\out\\big\\TMAPS2-1-";
	const char* out_filename = "c:\\prenos\\remc2\\tools\\compressTMAPS\\compressTMAPS\\out\\TMAPS2-1-";
	//const char* orig_filename = "c:\\prenos\\remc2\\tools\\decompressTMAPS\\out\\TMAPS2-1-";
#endif level1
#ifdef level2
	const char* standartpal_filename = "c:\\prenos\\remc2\\tools\\palletelight\\Debug\\out-block.pal";
	const char* data_filename = "c:\\prenos\\remc2\\tools\\decompressTMAPS\\out\\big\\TMAPS2-0-";
	const char* out_filename = "c:\\prenos\\remc2\\tools\\compressTMAPS\\compressTMAPS\\out\\TMAPS2-0-";
	//const char* orig_filename = "c:\\prenos\\remc2\\tools\\decompressTMAPS\\out\\TMAPS2-0-";
#endif level2
#ifdef level4
	const char* standartpal_filename = "c:\\prenos\\remc2\\tools\\palletelight\\Debug\\out-c.pal";
	const char* data_filename = "c:\\prenos\\remc2\\tools\\decompressTMAPS\\out\\big\\TMAPS2-2-";
	const char* out_filename = "c:\\prenos\\remc2\\tools\\compressTMAPS\\compressTMAPS\\out\\TMAPS2-2-";
	//const char* orig_filename = "c:\\prenos\\remc2\\tools\\decompressTMAPS\\out\\TMAPS2-2-";
#endif level4

	FILE* fptr_stdpal;
	fopen_s(&fptr_stdpal, standartpal_filename, "rb");
	fseek(fptr_stdpal, 0L, SEEK_END);
	long szstd = ftell(fptr_stdpal);
	fseek(fptr_stdpal, 0L, SEEK_SET);
	unsigned char* content_stdpal = (unsigned char*)malloc(szstd * sizeof(char*));
	fread(content_stdpal, szstd, 1, fptr_stdpal);
	fclose(fptr_stdpal);

	/*FILE* fptr_stdorig32;
	fopen_s(&fptr_stdorig32, orig32_filename, "rb");
	fseek(fptr_stdorig32, 0L, SEEK_END);
	long szstdorig32 = ftell(fptr_stdorig32);
	fseek(fptr_stdorig32, 0L, SEEK_SET);
	unsigned char* content_data32 = (unsigned char*)malloc(szstdorig32 * sizeof(char*));
	fread(content_data32, szstdorig32, 1, fptr_stdorig32);
	fclose(fptr_stdorig32);*/

	/*
	sprintf_s(buffer,"%s", data_filename);
	FILE* fptr_data;
	fopen_s(&fptr_data, buffer, "rb");
	fseek(fptr_data, 0L, SEEK_END);
	long szdata = ftell(fptr_data);
	fseek(fptr_data, 0L, SEEK_SET);
	unsigned char* content_data = (unsigned char*)malloc(szdata * sizeof(char*));
	fread(content_data, szdata, 1, fptr_data);
	fclose(fptr_data);

	sprintf_s(buffer, "%s", alpha_filename);
	FILE* fptr_alphadata;
	fopen_s(&fptr_alphadata, buffer, "rb");
	fseek(fptr_alphadata, 0L, SEEK_END);
	long szalpha = ftell(fptr_alphadata);
	fseek(fptr_alphadata, 0L, SEEK_SET);
	unsigned char* content_alphadata = (unsigned char*)malloc(szalpha * sizeof(char*));
	fread(content_alphadata, szalpha, 1, fptr_alphadata);
	fclose(fptr_alphadata);*/
	
	for(int fileindex=0; fileindex<1000; fileindex++)
		for (int mainindex = 0; mainindex < 24; mainindex++)
	{
		
		char textbuffer[512];
		sprintf_s(textbuffer, "%s%03d-%02i_out.png", data_filename, fileindex,mainindex);
		if (!file_exist(textbuffer))break;

		read_png_file(textbuffer);


		//sprintf_s(buffer, "%sTMAPS2-0-%03d-alpha_cartoonpainted_400000_gaus.png", alpha_filename, fileindex);//gaus 3x3
		//sprintf_s(buffer, "%sTMAPS2-0-%03d-alpha_cartoonpainted_400000.png", alpha_filename, fileindex);
		//read_pngalpha_file(buffer);

		/*sprintf_s(textbuffer, "%s%03d-%02i.data", orig_filename, fileindex, mainindex);
		FILE* fptr_origdata;
		fopen_s(&fptr_origdata, textbuffer, "rb");
		fseek(fptr_origdata, 0L, SEEK_END);
		long szorig = ftell(fptr_origdata);
		fseek(fptr_origdata, 0L, SEEK_SET);
		unsigned char* content_origdata = (unsigned char*)malloc(szorig * sizeof(char*));
		fread(content_origdata, szorig, 1, fptr_origdata);
		fclose(fptr_origdata);*/


		/*
		void process_png_file() {
	  for(int y = 0; y < height; y++) {
		png_bytep row = row_pointers[y];
		for(int x = 0; x < width; x++) {
		  png_bytep px = &(row[x * 4]);
		  // Do something awesome for each pixel here...
		  //printf("%4d, %4d = RGBA(%3d, %3d, %3d, %3d)\n", x, y, px[0], px[1], px[2], px[3]);
		}
	  }
	}
		*/

		sprintf_s(textbuffer, "%s%03d-%02i.data", out_filename, fileindex, mainindex);
		FILE* fptr_outdata;
		fopen_s(&fptr_outdata, textbuffer, "wb");


		Bit8u alphaweight = 32;
		/*int datapos = 54;
		int wpos = 18;
		int hpos = 22;


		int widthimg = *(Bit32u*)&content_data[wpos]; //18
		int heightimg = *(Bit32u*)&content_data[hpos];//22
		Bit8u* dataimg = content_data + datapos;
			//79x65 4f x 41

		Bit8u* alphaimg = content_alphadata + datapos;*/

		unsigned char* content_outdata = (unsigned char*)malloc(width * height * sizeof(char*));

		unsigned char* pngbuffer = (unsigned char*)malloc(width * height * 4);

		for (int yy = 0; yy < height; yy++)
		{
			png_bytep row = row_pointers[yy];
			//png_bytep rowalpha = row_alphapointers[yy];
			for (int xx = 0; xx < width; xx++) {

				/*int origx = (xx + 2) / 4;
				int origy = (yy + 2) / 4;
				int origindex = 0;
				Bit8u origcolor[100];
				int origwidth = width / 4;
				int origheight = height / 4;				
				for (int oy = origy - 2; oy <= origy + 2; oy++)
					for (int ox = origx - 2; ox <= origx + 2; ox++)
					{							
						if ((ox < 0) || (oy < 0) || (ox >= origwidth) || (oy >= origheight))
							origcolor[origindex] = 0;
						else
							origcolor[origindex] = (content_origdata+6)[origwidth * oy + ox];
						origindex++;
					}*/


				//int bmpx = xx;// widthimg - xx - 1;
				//int bmpy = heightimg- yy - 1;
				//Bit8u alphablue = alphaimg[3 * (bmpy * widthimg + bmpx)];
				png_bytep px = &(row[xx * 4]);
				//png_bytep alpx = &(rowalpha[xx * 4]);
				//Bit8u alphablue = alpx[2];
				Bit8u wrbyte = 0;
				//if (alphablue > alphaweight)
				//{					
					Bit8u datared = px[0];
					Bit8u datagreen = px[1];
					Bit8u datablue = px[2];
					Bit8u dataalpha = px[3];

					pngbuffer[4*(xx+width * yy) + 0] = datared;
					pngbuffer[4 * (xx + width * yy) + 1] = datagreen;
					pngbuffer[4 * (xx + width * yy) + 2] = datablue;
					pngbuffer[4 * (xx + width * yy) + 3] = dataalpha;

					/*unsigned char x = 0;
					if (!notAlpha(width, height))
					{
					}
					else
					{
					}*/
					/*int best = 1000;
					//for (int j = 0; j < szstd / 3; j++)
					for (int j = 0; j < origindex; j++)
					{
						int score = 0;

						score += abs(px[0] - content_stdpal[origcolor[j]*3+0]);
						score += abs(px[1] - content_stdpal[origcolor[j] * 3 + 1]);
						score += abs(px[2] - content_stdpal[origcolor[j] * 3 + 2]);

						bool notinremoved = true;
						if (notinremoved)
							if (score < best)
							{
								best = score;
								x = origcolor[j];
							}
					}*/


					//wrbyte = x;
				//}
				

			}
		}

		Bit8u* buffer2 = (Bit8u*)malloc(width * height * 4);

		int x;
		float colorRIerr[4096];
		float colorGIerr[4096];
		float colorBIerr[4096];
		float colorRJerr[4096];
		float colorGJerr[4096];
		float colorBJerr[4096];
		int colorRerr = 0;
		int colorGerr = 0;
		int colorBerr = 0;
		for (int i = 0; i < width; i++)
		{
			colorRIerr[i] = 0;
			colorGIerr[i] = 0;
			colorBIerr[i] = 0;
		}

		for (int j = 0; j < width; j++)
		{
			colorRJerr[j] = 0;
			colorGJerr[j] = 0;
			colorBJerr[j] = 0;
		}
		
		int j;
		for (int i = 0; i < height; i++)
		{
			for (int jx = 0; jx < width; jx++)
			{
				if (i % 2 == 0)j = jx;
				else j = width - 1 - jx;
				int colorR = pngbuffer[4 * (j + width * i) + 0];
				int colorG = pngbuffer[4 * (j + width * i) + 1];
				int colorB = pngbuffer[4 * (j + width * i) + 2];
				float koef = 0.5;
				colorRerr = koef * (colorRIerr[i] + colorRJerr[j]);
				colorGerr = koef * (colorGIerr[i] + colorGJerr[j]);
				colorBerr = koef * (colorBIerr[i] + colorBJerr[j]);

				colorRIerr[i] -= 0.5 * colorRerr;
				colorGIerr[i] -= 0.5 * colorGerr;
				colorBIerr[i] -= 0.5 * colorBerr;

				colorRJerr[j] -= 0.5 * colorRerr;
				colorGJerr[j] -= 0.5 * colorGerr;
				colorBJerr[j] -= 0.5 * colorBerr;


				x = getIndexedColor(colorR - colorRerr, colorG - colorGerr, colorB - colorBerr, content_stdpal, szstd);
				//fwrite((char*)&x, 1, 1, fptw_outdata2);
				buffer[i * width + j] = (char)x;

				colorRIerr[i] += (content_stdpal[x * 3 + 0] - colorR) * 0.5;
				colorGIerr[i] += (content_stdpal[x * 3 + 1] - colorG) * 0.5;
				colorBIerr[i] += (content_stdpal[x * 3 + 2] - colorB) * 0.5;

				colorRJerr[j] += (content_stdpal[x * 3 + 0] - colorR) * 0.5;
				colorGJerr[j] += (content_stdpal[x * 3 + 1] - colorG) * 0.5;
				colorBJerr[j] += (content_stdpal[x * 3 + 2] - colorB) * 0.5;

				buffer2[(i * width + j) * 4] = content_stdpal[x * 3 + 0];
				buffer2[(i * width + j) * 4 + 1] = content_stdpal[x * 3 + 1];
				buffer2[(i * width + j) * 4 + 2] = content_stdpal[x * 3 + 2];
				buffer2[(i * width + j) * 4 + 3] = 255;
			}
		}

		int minalpha = 128;
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				bool isAlpha = false;
				if (pngbuffer[4 * (j + width * i) + 3] < minalpha)
					isAlpha = true;
				if(i>0)
					if (pngbuffer[4 * (j + width * (i - 1)) + 3] < minalpha)
						isAlpha = true;
				if (i < height-1)
					if (pngbuffer[4 * (j + width * (i + 1)) + 3] < minalpha)
						isAlpha = true;
				if (j > 0)
					if (pngbuffer[4 * ((j-1) + width * i) + 3] < minalpha)
						isAlpha = true;
				if (j < width - 1)
					if (pngbuffer[4 * ((j+1) + width * i) + 3] < minalpha)
						isAlpha = true;
				if ((i > 0) && ((j > 0)))
					if (pngbuffer[4 * ((j-1) + width * (i - 1)) + 3] < minalpha)
						isAlpha = true;
				if ((i < height - 1) && (j < width - 1))
					if (pngbuffer[4 * ((j+1) + width * (i + 1)) + 3] < minalpha)
						isAlpha = true;
				if ((i < height - 1) && (j > 0))
					if (pngbuffer[4 * ((j - 1) + width * (i+1)) + 3] < minalpha)
						isAlpha = true;
				if ((i > 0)&&(j < width - 1))
					if (pngbuffer[4 * ((j + 1) + width * (i-1)) + 3] < minalpha)
						isAlpha = true;

				if (isAlpha)
				{
					buffer[i * width + j] = transparentColor;
				}
			}
		}

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				if (buffer[i * width + j] == transparentColor)
					buffer2[(i * width + j) * 4 + 3] = 0;
				else
					buffer2[(i * width + j) * 4 + 3] = 255;
			}
		}



		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
				fwrite(&buffer[i * width + j], 1, 1, fptr_outdata);

		sprintf_s(textbuffer, "%s%03d-%02i.png", out_filename, fileindex, mainindex);
		writeImagePNG((char*)textbuffer, width, height, buffer2, (char*)"aa");

		free(pngbuffer);

		for (int y = 0; y < height; y++) {
			free(row_pointers[y]);
		}
		free(row_pointers);

		/*for (int y = 0; y < height; y++) {
			free(row_alphapointers[y]);
		}
		free(row_alphapointers);*/

		fclose(fptr_outdata);
	}
	

}

// Spuštění programu: Ctrl+F5 nebo nabídka Ladit > Spustit bez ladění
// Ladění programu: F5 nebo nabídka Ladit > Spustit ladění

// Tipy pro zahájení práce:
//   1. K přidání nebo správě souborů použijte okno Průzkumník řešení.
//   2. Pro připojení ke správě zdrojového kódu použijte okno Team Explorer.
//   3. K zobrazení výstupu sestavení a dalších zpráv použijte okno Výstup.
//   4. K zobrazení chyb použijte okno Seznam chyb.
//   5. Pokud chcete vytvořit nové soubory kódu, přejděte na Projekt > Přidat novou položku. Pokud chcete přidat do projektu existující soubory kódu, přejděte na Projekt > Přidat existující položku.
//   6. Pokud budete chtít v budoucnu znovu otevřít tento projekt, přejděte na Soubor > Otevřít > Projekt a vyberte příslušný soubor .sln.
