#include <stdlib.h>
#include <SDL/SDL.h>

#include "../includes/display.h"

int		display_layers(t_display *display)
{
  if (SDL_FillRect(display->screen, NULL, SDL_MapRGB(display->screen->format, 0, 0, 0)) == -1)
    return -1;
  while (display->layers != NULL)
    {
      printf("Layer adress : %p\n", display->layers);
      if (SDL_BlitSurface(display->layers->layer, NULL, display->screen, display->layers->pos) == -1)
	return -1;
      display->layers = display->layers->next;
    }
  return SDL_Flip(display->screen);
}

int		add_layer(t_layers_list **list, SDL_Surface *layer, SDL_Rect *pos)
{
  t_layers_list	*new_layer;

  if ((new_layer = malloc(sizeof(t_layers_list))) == NULL)
    return (-1);
  new_layer->layer = layer;
  new_layer->pos = pos;
  new_layer->next = *list;
  new_layer->prev = NULL;
  *list = new_layer;
  return (0);
}
