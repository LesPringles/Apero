#include "../includes/display.h"




static int		set_start_pos(SDL_Rect **p, Uint16 x, Uint16 y)
{
  if ((*p = malloc(sizeof(SDL_Rect))) == NULL)
    return -1;
  (*p)->x = x;
  (*p)->y = y;
  return 0;
}

static int		display_square(t_display *display, SDL_Rect *pos, int w, int h)
{
  SDL_Surface		*square;

  if ((square = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0)) == NULL)
    return -1;
  if (SDL_FillRect(square, NULL, SDL_MapRGB(square->format, 255, 255, 255)) == -1)
    return -1;
  if (SDL_BlitSurface(square, NULL, display->screen, pos) == -1)
    return -1;
  return SDL_Flip(display->screen);
  return 0;
}

static int		get_w(SDL_Rect *start, SDL_Rect *end)
{
  return abs(end->x - start->x);
}

int			print_square(t_display *display, void *param)
{
  static t_button_state	last_state = UNSET;
  static SDL_Rect	*start_pos = NULL;
  SDL_MouseButtonEvent	*mouse;
  SDL_Rect		pos, origin;

  mouse = (SDL_MouseButtonEvent *)param;
  pos.x = mouse->x;
  pos.y = mouse->y;
  if (last_state == UNSET && display->button == RELEASED)
    return (0);
  if ((start_pos == NULL)
      && ((last_state == UNSET) || (last_state == RELEASED))
      && (display->button == PRESSED))
    {
      last_state = PRESSED;
      if (set_start_pos(&start_pos, mouse->x, mouse->y) == -1)
	return -1;
    }
  if (display->button == RELEASED)
    {
      last_state = RELEASED;
      start_pos = NULL;
      return 0;
    }

  if(pos.x > start_pos->x) 
  { 
		if(pos.y > start_pos->y) 
			return display_square(display, start_pos, get_w(start_pos, &pos), get_w(start_pos, &pos)); 

		else 
		{ 
			origin.x = start_pos->x; 
			origin.y = pos.y; 
			return display_square(display, &origin, get_w(start_pos, &pos), get_w(start_pos, &pos)); 
		} 

  } 
  else 
  { 
		if(pos.y > start_pos->y) 
		{ 
			origin.x = pos.x; 
			origin.y = start_pos->y; 
			return display_square(display, &origin, get_w(start_pos, &pos), get_w(start_pos, &pos)); 
		}
		else 
			return display_square(display, &pos, get_w(start_pos, &pos), get_w(start_pos, &pos)); 
  }
  
}
