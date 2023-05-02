#pragma once

namespace Lone {
	class Texture
	{
	public:
		Texture(const char* filePath);
		~Texture();
		void Bind(uint32_t slot = 0);
	public:
		uint32_t id;
	private:
		int width;
		int height;
		int nrChannels;
	};
}