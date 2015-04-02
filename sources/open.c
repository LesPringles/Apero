#include <SDL/SDL.h>


#include "../includes/display.h"


int		open(t_display *display, SDL_Surface *surface)
{
  if ((surface == SDL_LoadBMP("ressources/out.bmp")) == -1)
    return -1;
  if (SDL_BlitSurface(surface, NULL, display->screen, NULL) == -1)
	return -1;
  if (SDL_Flip(display->screen) == -1)
	return -1;
  return 0;
}
