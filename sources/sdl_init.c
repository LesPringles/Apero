#include <stdio.h>
#include <SDL/SDL.h>

#include "../includes/display.h"
#include "../includes/shapes.h"
#include "../includes/couleurs.h"

static int	manage_mouse_event(SDL_Event *event, t_display *display)
{
  (void)display;
  switch (event->type)
    {
    case SDL_MOUSEMOTION:
      return do_action(display, &event->button);
      break;
    case SDL_MOUSEBUTTONDOWN:
      display->button = PRESSED;
      return do_action(display, &event->button);
      break;
    case SDL_MOUSEBUTTONUP:
      display->button = RELEASED;
      break;
    default:
      break;
    }
  return 0;
}

static void	change_color(t_display *display)
{
  display->color_index++;
  if (display->color_index > NB_COLORS)
    display->color_index = 0;
}

static void change_actions(t_display *display)
{
	display->action++;
	if (display->action > PRINT_DISC)
		display->action =0;
}


static int	manage_key_event(SDL_Event *event, t_display *display)
{
  (void)display;
  //unsigned int i = 0;

  switch ((int)event->key.keysym.sym)
    {
    case SDLK_ESCAPE:
      return 1;
      break;
    case SDLK_SPACE:
      display->button = RELEASED;
      do_action(display, &event->button);
	  change_actions(display);
      break;
    case SDLK_n:
      if (new(display->screen) == -1)
	return -1;
      break;
    case SDLK_o:
	// MArche oas
      if (open(display, display->screen) == -1)
	return -1;
      break;
    case SDLK_BACKSPACE:
      if (undo(display) == -1)
	return -1;
      break;
    case SDLK_RSHIFT:
      if (redo(display) == -1)
	return -1;
      break;
    case SDLK_s:
      if (save(display->screen, "ressources/out.bmp") == -1)
	return -1;
      break ;
    case SDLK_c:
      change_color(display);
      break;
    case SDLK_t:
      //TODO Changerla taille du pinceau
      break;

    default:
      break;
    }
  return 0;
}

static int	manage_event(SDL_Event *event, t_display *display)
{
  if (event->type == SDL_QUIT)
    return 1;
  if (event->type == SDL_KEYDOWN)
    return manage_key_event(event, display);
  return manage_mouse_event(event, display);
}

static int	sdl_loop(t_display *display)
{
  SDL_Event	event;
  int		ret;

  while (SDL_WaitEvent(&event))
    {
      if ((ret = manage_event(&event, display)) == -1)
	return -1;
      else if (ret)
	return 0;
    }
  return 0;
}

int		init_sdl()
{
  SDL_Rect	pos;
  t_display	display;

  display.layers = NULL;
  display.action = PRINT_PIXEL;
  display.button = RELEASED;
  if (SDL_Init(SDL_INIT_VIDEO) == -1)
    return -1;
  if ((display.screen = SDL_SetVideoMode(WINX, WINY, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL)
    return -1;
  if (new(display.screen) == -1)
	return -1;
  SDL_WM_SetCaption("Apero", NULL);
  if (new(display.screen) == -1)
    return -1;
  pos.x = 0;
  pos.y = 0;
  if (add_layer(&display.layers, display.screen, &pos) == -1)
    return -1;
  display.color_index = 0;
  sdl_loop(&display);
  SDL_Quit();
  return 0;
}
