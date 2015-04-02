#include "../includes/display.h"
#include "../includes/couleurs.h"

static int		set_start_pos(SDL_Rect **p, Uint16 x, Uint16 y)
{
  if ((*p = malloc(sizeof(SDL_Rect))) == NULL)
    return -1;
  (*p)->x = x;
  (*p)->y = y;
  return 0;
}

static int		display_rectempty(t_display *display, SDL_Rect *pos, int w, int h)
{
  SDL_Surface		*square;
  SDL_Surface 		*square2;

  if ((square = SDL_CreateRGBSurface(0, w + 6, h + 6, 32, 0, 0, 0, 0)) == NULL)
    return -1;
  if ((square2 = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0)) == NULL)
	return -1;


  /*
  SDL_Rect ligneHaut;
	ligneHaut.x = pos->x-1;
	ligneHaut.y = pos->y-1;
	ligneHaut.w = h;
	ligneHaut.h = 1;
 
	SDL_FillRect(square, &ligneHaut, colors[display->color_index]);
 
	SDL_Rect ligneDroite;
	ligneDroite.x = pos->x+h-1;
	ligneDroite.y = pos->y-1;
	ligneDroite.w = 1;
	ligneDroite.h = w;
 
	SDL_FillRect(square, &ligneDroite, colors[display->color_index]);
 
	SDL_Rect ligneGauche;
	ligneGauche.x = pos->x-1;
	ligneGauche.y = pos->y-1;
	ligneGauche.w = 1;
	ligneGauche.h = w;
 
	SDL_FillRect(square, &ligneGauche, colors[display->color_index]);
 
	SDL_Rect ligneBas;
	ligneBas.x = pos->x-1;
	ligneBas.y = pos->y+w-1;
	ligneBas.w = h;
	ligneBas.h = 1;
 
	SDL_FillRect(square, &ligneBas, colors[display->color_index]);
  */




  if (SDL_FillRect(square, NULL, colors[display->color_index]) == -1)
    return -1;
  if (SDL_FillRect(square2, NULL, colors[WHITE]) == -1)
	return -1;
  if (SDL_BlitSurface(square, NULL, display->screen, pos) == -1)
    return -1;
  if (SDL_BlitSurface(square2, NULL, display->screen, pos) == -1)
    return -1;

  return SDL_Flip(display->screen);
  return 0;
}

static int		get_w(SDL_Rect *start, SDL_Rect *end)
{
  return abs(end->x - start->x);
}

static int		get_h(SDL_Rect *start, SDL_Rect *end)
{
  return abs(end->y - start->y);
}

int			print_rectempty(t_display *display, void *param)
{
  static t_button_state	last_state = UNSET;
  static SDL_Rect	*start_pos = NULL;
  static SDL_Surface	*original_screen = NULL; // SAVE FOR APERCU
  SDL_MouseButtonEvent	*mouse;
  SDL_Rect		pos;
  SDL_Rect		pos_0;
  SDL_Rect		origin;

  pos_0.x = 0;
  pos_0.y = 0;
  mouse = (SDL_MouseButtonEvent *)param;
  pos.x = mouse->x;
  pos.y = mouse->y;
  if (last_state == UNSET && display->button == RELEASED)
    return (0);
  // BEGIN APERCU
  if ((start_pos == NULL)
      && ((last_state == UNSET) || (last_state == RELEASED))
      && (display->button == PRESSED))
    {
      last_state = PRESSED;
      if ((original_screen = SDL_CreateRGBSurface(0, WINX, WINY, 32, 0, 0, 0, 0)) == NULL)
	return -1;
      if (SDL_BlitSurface(display->screen, NULL, original_screen, &pos_0) == -1)
	return -1;
      if (set_start_pos(&start_pos, mouse->x, mouse->y) == -1)
	return -1;
    }
  // END APERCU
if (display->button == RELEASED)
    {
      // SAVE LAYER
      if (last_state == PRESSED)
		if (add_layer(&display->layers, display->screen, &pos_0) == -1)
	  		return -1;
      last_state = RELEASED;
      original_screen = NULL;
      start_pos = NULL;
      return 0;
    }
  // BEGIN APERCU

  if (SDL_BlitSurface(original_screen, NULL, display->screen, &pos_0) == -1)
    return -1;
  // END APERCU

    if(pos.x > start_pos->x)
    {
		if(pos.y > start_pos->y)
			return display_rectempty(display, start_pos, get_w(start_pos, &pos), get_h(start_pos, &pos));

		else
		{
			origin.x = start_pos->x;
			origin.y = pos.y;
			return display_rectempty(display, &origin, get_w(start_pos, &pos), get_h(start_pos, &pos));
		}

    }
  else
  {
		if(pos.y > start_pos->y)
		{
			origin.x = pos.x;
			origin.y = start_pos->y;
			return display_rectempty(display, &origin, get_w(start_pos, &pos), get_h(start_pos, &pos));
		}
		else
			return display_rectempty(display, &pos, get_w(start_pos, &pos), get_h(start_pos, &pos));
  }

}
