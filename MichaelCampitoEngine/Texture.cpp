#include "Texture.h"



Texture::Texture()
{
}


Texture::~Texture()
{
}

void Texture::load(char* name) {
	image = FreeImage_Load(FreeImage_GetFileType(name, 0), name);
	image32Bit = FreeImage_ConvertTo32Bits(image);
	FreeImage_Unload(image);
	glGenTextures(1, &texID);
}

void Texture::use() {
	glBindTexture(GL_TEXTURE_2D, texID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB_ALPHA, FreeImage_GetWidth(image32Bit), FreeImage_GetHeight(image32Bit), 0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(image32Bit));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

void Texture::unload() {
	FreeImage_Unload(image32Bit);
	glBindTexture(GL_TEXTURE_2D, 0);
}