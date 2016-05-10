#pragma region Copyright (c) 2014-2016 OpenRCT2 Developers
/*****************************************************************************
 * OpenRCT2, an open source clone of Roller Coaster Tycoon 2.
 *
 * OpenRCT2 is the work of many authors, a full list can be found in contributors.md
 * For more information, visit https://github.com/OpenRCT2/OpenRCT2
 *
 * OpenRCT2 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * A full copy of the GNU General Public License can be found in licence.txt
 *****************************************************************************/
#pragma endregion

#ifndef _SAWYERCODING_H_
#define _SAWYERCODING_H_

#include <SDL.h>
#include "../common.h"

typedef struct {
	uint8 encoding;
	uint32 length;
} sawyercoding_chunk_header;

enum {
	CHUNK_ENCODING_NONE,
	CHUNK_ENCODING_RLE,
	CHUNK_ENCODING_RLECOMPRESSED,
	CHUNK_ENCODING_ROTATE
};

enum {
	FILE_VERSION_MASK = (3 << 0),
	FILE_VERSION_RCT1 = (0 << 0),
	FILE_VERSION_RCT1_AA = (1 << 0),
	FILE_VERSION_RCT1_LL = (2 << 0),

	FILE_TYPE_MASK = (3 << 2),
	FILE_TYPE_TD4 = (0 << 2),
	FILE_TYPE_SV4 = (1 << 2),
	FILE_TYPE_SC4 = (2 << 2)
};

int sawyercoding_validate_checksum(SDL_RWops* rw);
uint32 sawyercoding_calculate_checksum(const uint8* buffer, size_t length);
bool sawyercoding_read_chunk_safe(SDL_RWops *rw, void *dst, size_t dstLength);
size_t sawyercoding_read_chunk(SDL_RWops* rw, uint8 *buffer);
size_t sawyercoding_write_chunk_buffer(uint8 *dst_file, uint8* buffer, sawyercoding_chunk_header chunkHeader);
size_t sawyercoding_decode_sv4(const uint8 *src, uint8 *dst, size_t length);
size_t sawyercoding_decode_sc4(const uint8 *src, uint8 *dst, size_t length);
size_t sawyercoding_encode_sv4(const uint8 *src, uint8 *dst, size_t length);
size_t sawyercoding_decode_td6(const uint8 *src, uint8 *dst, size_t length);
size_t sawyercoding_encode_td6(const uint8 *src, uint8 *dst, size_t length);
int sawyercoding_validate_track_checksum(const uint8* src, size_t length);

int sawyercoding_detect_file_type(const uint8 *src, size_t length);
int sawyercoding_detect_rct1_version(int gameVersion);

#endif
