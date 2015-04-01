#include "../includes/display.h"
#include <math.h>

void echangerEntiers(int* x, int* y)
{
  int t = *x;
  *x = *y;
  *y = t;
}

void ligne(t_display *display, int x1, int y1, int x2, int y2, Uint32 coul)
{
  int d, dx, dy, aincr, bincr, xincr, yincr, x, y;

  if (abs(x2 - x1) < abs(y2 - y1)) {
    /* parcours par l'axe vertical */

    if (y1 > y2) {
      echangerEntiers(&x1, &x2);
      echangerEntiers(&y1, &y2);
    }

    xincr = x2 > x1 ? 1 : -1;
    dy = y2 - y1;
    dx = abs(x2 - x1);
    d = 2 * dx - dy;
    aincr = 2 * (dx - dy);
    bincr = 2 * dx;
    x = x1;
    y = y1;

    setPixelVerif(display, x, y, coul);

    for (y = y1+1; y <= y2; ++y) {
      if (d >= 0) {
	x += xincr;
	d += aincr;
      } else
	d += bincr;

      setPixelVerif(display, x, y, coul);
    }

  } else {
    /* parcours par l'axe horizontal */

    if (x1 > x2) {
      echangerEntiers(&x1, &x2);
      echangerEntiers(&y1, &y2);
    }

    yincr = y2 > y1 ? 1 : -1;
    dx = x2 - x1;
    dy = abs(y2 - y1);
    d = 2 * dy - dx;
    aincr = 2 * (dy - dx);
    bincr = 2 * dy;
    x = x1;
    y = y1;

    setPixelVerif(display, x, y, coul);

    for (x = x1+1; x <= x2; ++x) {
      if (d >= 0) {
	y += yincr;
	d += aincr;
      } else
	d += bincr;

      setPixelVerif(display, x, y, coul);
    }
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

static int		display_ligne(t_display *display, SDL_Rect *pos, int x1, int y1, int x2, int y2)
{
  SDL_Surface		*square;

  if ((square = SDL_CreateRGBSurface(0, 0, 0, 32, 0, 0, 0, 0)) == NULL)
    return -1;

  ligne(display, x1, y1, x2, y2, SDL_MapRGB(square->format, 0xFF, 0xFF, 0xFF));

  if (SDL_BlitSurface(square, NULL, display->screen, pos) == -1)
    return -1;
  return SDL_Flip(display->screen);
  return 0;
}

/*static long 			get_r(SDL_Rect *start, SDL_Rect *end)
{
	return sqrtl((end->x - start->x) * (end->x - start->x) + (end->y - start->y) * (end->y - start->y));
}*/

int			print_ligne(t_display *display, void *param)
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
		return display_ligne(display,
			((pos.x > start_pos->x) ? &pos : start_pos),
			mouse->x,
			mouse->y,
			start_pos->x,
			start_pos->y);
	}



  if (display->button == RELEASED)
    {
      last_state = RELEASED;
      start_pos = NULL;
      return 0;
    }


  return 0;
}
