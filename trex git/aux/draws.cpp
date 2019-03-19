#include <SDL2/SDL.h>
void drawcircle(int x0, int y0, int rad, SDL_Texture* text, SDL_Renderer* renderer)
{
	SDL_SetRenderTarget(renderer, text); //on modifie la texture
	
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	int radius = 0;
	while(radius < rad)
	{
		int x = radius-1;
		int y = 0;
		int dx = 1;
		int dy = 1;
		int err = dx - (radius << 1);
		
		while (x >= y)
		{
			
			SDL_RenderDrawPoint(renderer,x0 + x, y0 + y);
			SDL_RenderDrawPoint(renderer,x0 + y, y0 + x);
			SDL_RenderDrawPoint(renderer,x0 - y, y0 + x);
			SDL_RenderDrawPoint(renderer,x0 - x, y0 + y);
			SDL_RenderDrawPoint(renderer,x0 - x, y0 - y);
			SDL_RenderDrawPoint(renderer,x0 - y, y0 - x);
			SDL_RenderDrawPoint(renderer,x0 + y, y0 - x);
			SDL_RenderDrawPoint(renderer,x0 + x, y0 - y);

			if (err <= 0)
			{
				y++;
				err += dy;
				dy += 2;
			}
			
			if (err > 0)
			{
				x--;
				dx += 2;
				err += dx - (radius << 1);
			}
		}
		radius ++;
	}
    SDL_SetRenderTarget(renderer, NULL);
}
void drawpad(int length, SDL_Texture* text, SDL_Renderer* renderer)
{
	SDL_SetRenderTarget(renderer, text); //on modifie la texture
	
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	for(int i = 0; i < length;i++)
	{
		SDL_RenderDrawPoint(renderer,0,i);
		SDL_RenderDrawPoint(renderer,1,i);
		SDL_RenderDrawPoint(renderer,2,i);
	}
    SDL_SetRenderTarget(renderer, NULL);
}
