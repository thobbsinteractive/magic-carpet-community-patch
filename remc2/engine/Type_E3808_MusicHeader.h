#pragma once

#ifndef TYPE_E3808_MUSIC_H
#define TYPE_E3808_MUSIC_H

#include <cstdint>

#pragma pack (1)
typedef struct {                //length 32 - this is may be format of wav sound file
	uint8_t* xmiData_0;         //data of wav//18
	int8_t stub_4[4];           //22
	int32_t xmiSize_8;          //24
	int16_t word_12;            //28
	int8_t filename_14[18];     //first 18 chars - name//30
} sub2type_E3808_music_header;

typedef struct {                //length 216
	int8_t stub[10];
	sub2type_E3808_music_header track_10[6];
	int8_t stubb[14];
} sub1type_E3808_music_header;

typedef struct {                //length 224
	int8_t byte_0;
	int8_t byte_1;
	int8_t byte_2;
	int8_t byte_3;
	int8_t byte_4;
	int8_t byte_5;
	int8_t byte_6;
	int8_t byte_7;
	sub1type_E3808_music_header str_8;  //216 length
} type_E3808_music_header;

//shadow shadow_type_E3808_music_header
typedef struct {                //length 32 - this is may be format of wav sound file
	int32_t xmiData_0;          //data of wav//18
	int8_t stub_4[4];           //22
	int32_t xmiSize_8;          //24
	int16_t word_12;            //28
	int8_t filename_14[18];     //first 18 chars - name//30
} shadow_sub2type_E3808_music_header;

typedef struct {                //length 216
	int8_t stub[10];
	shadow_sub2type_E3808_music_header track_10[6];
	int8_t stubb[14];
} shadow_sub1type_E3808_music_header;

typedef struct {                //length 224
	int8_t byte_0;
	int8_t byte_1;
	int8_t byte_2;
	int8_t byte_3;
	int8_t byte_4;
	int8_t byte_5;
	int8_t byte_6;
	int8_t byte_7;
	shadow_sub1type_E3808_music_header str_8;   //216 length
} shadow_type_E3808_music_header;
#pragma pack (16)

#endif //TYPE_E3808_MUSIC_H