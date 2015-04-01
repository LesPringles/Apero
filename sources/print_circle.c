#include <math.h>

#include "../includes/display.h"
#include "../includes/couleurs.h"

void cercle(t_display *display, int cx, int cy, long rayon, Uint32 coul)
{
  int d, y, x;

  d = 3 - (2 * rayon);
  x = 0;
  y = rayon;

  while (y >= x) {
    setPixelVerif(display, cx + x, cy + y, coul);
    setPixelVerif(display, cx + y, cy + x, coul);
    setPixelVerif(display, cx - x, cy + y, coul);
    setPixelVerif(display, cx - y, cy + x, coul);
    setPixelVerif(display, cx + x, cy - y, coul);
    setPixelVerif(display, cx + y, cy - x, coul);
    setPixelVerif(display, cx - x, cy - y, coul);
    setPixelVerif(display, cx - y, cy - x, coul);

    if (d < 0)
      d = d + (4 * x) + 6;
    else {
      d = d + 4 * (x - y) + 10;
      y--;
    }

    x++;
  }
}

static int		set_start_pos(SDL_Rect **p, Uint16 x, Uint16 y)
{
  if ((*p = malloc(sizeof(SDL_Rect))) == NULL)
    return -1;
  (*p)->x = x;
  (*p)->y = y;
  return 0;
}

static int		display_circle(t_display *display, SDL_Rect *pos, int cx, int cy, long r)
{
  SDL_Surface		*square;

  if ((square = SDL_CreateRGBSurface(0, 0, 0, 32, 0, 0, 0, 0)) == NULL)
    return -1;

  cercle(display, cx, cy, r, colors[display->color_index]);

  if (SDL_BlitSurface(square, NULL, display->screen, pos) == -1)
    return -1;
  return SDL_Flip(display->screen);

  return 0;
}

static long 			get_r(SDL_Rect *start, SDL_Rect *end)
{
  return sqrtl((end->x - start->x) * (end->x - start->x) + (end->y - start->y) * (end->y - start->y));
}

int			print_circle(t_display *display, void *param)
{
  static t_button_state	last_state = UNSET;
  static SDL_Rect	*start_pos = NULL;
  SDL_MouseButtonEvent	*mouse;
  SDL_Rect		pos;

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

  if (last_state == PRESSED && display->button == RELEASED)
    {
      last_state = RELEASED;
      return display_circle(display,
			    ((pos.x > start_pos->x) ? &pos : start_pos),
			    mouse->x - (get_r(start_pos, &pos) / 2),
			    mouse->y - (get_r(start_pos, &pos) / 2),
			    get_r(start_pos, &pos));
    }

  if (display->button == RELEASED)
    {
      last_state = RELEASED;
      start_pos = NULL;
      return 0;
    }
  return 0;
}
