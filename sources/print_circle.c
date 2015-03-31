#include "../includes/display.h"
#include <math.h>

/*void setPixel(t_display *display, int x, int y, Uint32 coul)
  {
  *((Uint32*)(display->screen->pixels) + x + y * WINX) = coul;
  }


void setPixelVerif(t_display *display, int x, int y, Uint32 coul)
{
  if (x >= 0 && x < WINX &&
      y >= 0 && y < WINY)
    setPixel(display, x, y, coul);
}*/

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

/*enum {
  C_NOIR, C_BLEU_FONCE, C_VERT_FONCE, C_CYAN_FONCE, C_ROUGE_FONCE,
  C_MAGENTA_FONCE, C_OCRE, C_GRIS_CLAIR, C_GRIS, C_BLEU, C_VERT,
  C_CYAN, C_ROUGE, C_MAGENTA, C_JAUNE, C_BLANC,

  NB_COULEURS
};

Uint32 couleurs[NB_COULEURS];

void initCouleurs(void)
{
	SDL_Surface *square;

  couleurs[C_NOIR]          = SDL_MapRGB(square->format, 0x00, 0x00, 0x00);
  couleurs[C_BLEU_FONCE]    = SDL_MapRGB(square->format, 0x00, 0x00, 0x80);
  couleurs[C_VERT_FONCE]    = SDL_MapRGB(square->format, 0x00, 0x80, 0x00);
  couleurs[C_CYAN_FONCE]    = SDL_MapRGB(square->format, 0x00, 0x80, 0x80);
  couleurs[C_ROUGE_FONCE]   = SDL_MapRGB(square->format, 0x80, 0x00, 0x00);
  couleurs[C_MAGENTA_FONCE] = SDL_MapRGB(square->format, 0x80, 0x00, 0x80);
  couleurs[C_OCRE]          = SDL_MapRGB(square->format, 0x80, 0x80, 0x00);
  couleurs[C_GRIS_CLAIR]    = SDL_MapRGB(square->format, 0xC0, 0xC0, 0xC0);
  couleurs[C_GRIS]          = SDL_MapRGB(square->format, 0x80, 0x80, 0x80);
  couleurs[C_BLEU]          = SDL_MapRGB(square->format, 0x00, 0x00, 0xFF);
  couleurs[C_VERT]          = SDL_MapRGB(square->format, 0x00, 0xFF, 0x00);
  couleurs[C_CYAN]          = SDL_MapRGB(square->format, 0x00, 0xFF, 0xFF);
  couleurs[C_ROUGE]         = SDL_MapRGB(square->format, 0xFF, 0x00, 0x00);
  couleurs[C_MAGENTA]       = SDL_MapRGB(square->format, 0xFF, 0x00, 0xFF);
  couleurs[C_JAUNE]         = SDL_MapRGB(square->format, 0xFF, 0xFF, 0x00);
  couleurs[C_BLANC]         = SDL_MapRGB(square->format, 255, 255, 255);
}*/


  if ((square = SDL_CreateRGBSurface(0, 0, 0, 32, 0, 0, 0, 0)) == NULL)
    return -1;

  cercle(display, cx, cy, r, SDL_MapRGB(square->format, 255, 0, 255));

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
			mouse->x,
			mouse->y,
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
