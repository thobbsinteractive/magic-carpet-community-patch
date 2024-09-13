#pragma once

#ifndef TYPE_E37A0_SOUNDBUFFER_H
#define TYPE_E37A0_SOUNDBUFFER_H
#include <cstdint>

#pragma pack (1)
typedef struct {                //length 32
	int8_t filename_14[18];
	uint8_t* wavData_0;
	int8_t stub_4[4];
	int32_t wavSize_8;
	int16_t word_12;
} sub2type_E37A0_sound_buffer;


typedef struct {                //length 3090
	int8_t byte_0;
	int8_t byte_1;
	int8_t byte_2;
	int8_t byte_3;
	int8_t byte_4;
	int8_t byte_5;
	int8_t byte_6;
	int8_t byte_7;
	sub2type_E37A0_sound_buffer wavDataList_10[96]; //3072 length
	int8_t next_str[10];
} type_E37A0_sound_buffer;

typedef struct {                //length 32
	int8_t filename_14[18];
	int32_t wavData_0;
	int8_t stub_4[4];
	int32_t wavSize_8;
	int16_t word_12;
} sub2type_32bit_E37A0_sound_buffer;


typedef struct {                //length 3090
	int8_t byte_0;
	int8_t byte_1;
	int8_t byte_2;
	int8_t byte_3;
	int8_t byte_4;
	int8_t byte_5;
	int8_t byte_6;
	int8_t byte_7;
	sub2type_32bit_E37A0_sound_buffer wavDataList_10[96];  //3072 length
	int8_t next_str[10];
} type_32bit_E37A0_sound_buffer;

typedef struct {                //length 16*6=96
	int32_t dword_0;
	int32_t dword_4;
	int32_t sizeBytes_8;
	int32_t dword_12;
} type_v8;

/*
typedef struct {//length 80656
	int8_t byte_0;
	int8_t byte_1;
	int8_t byte_2;
	int8_t byte_3;
	int8_t byte_4;
	int8_t byte_5;
	int8_t byte_6;
	int8_t byte_7;
	int8_t data_8[];
}
type_E3810_music_data;*/

#pragma pack (16)

#endif //TYPE_E37A0_SOUNDBUFFER_H