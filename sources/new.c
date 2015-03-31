#include <SDL/SDL.h>

#include "../includes/display.h"

int		new(SDL_Surface *surface)
{
  if (SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 255, 255, 255)) == -1)
    return -1;
  return 0;
}
