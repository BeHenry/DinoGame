#ifndef DEF_ASSET
#define DEF_ASSET
#include <SDL2/SDL.h>
#include <vector>
class Asset
{
	public:
	Asset(std::vector<SDL_Rect> info, SDL_Texture* text, int type, int anime);
	Asset(SDL_Rect info, SDL_Texture* text, int type);
	~Asset();
	void addAnimationFrame(SDL_Rect info);
	int getType();
	SDL_Rect* getRect(int i);
	SDL_Texture* getTexture(); 
	void setAnimationOffset(int i);
	
	private:
	std::vector<SDL_Rect> pos;
	SDL_Texture* assets_base;
	int id;
	int animationOffset;
	

};

#endif
