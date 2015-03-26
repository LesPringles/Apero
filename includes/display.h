#ifndef DISPLAY_H_
# define DISPLAY_H_

# include <SDL/SDL.h>

# define WINX	1280
# define WINY	720

typedef enum	e_current_action
  {
    PRINT_PIXEL = 0,
    PRINT_SQUARE
  }		t_current_action;

typedef enum	e_button_state
  {
    PRESSED = 0,
    RELEASED,
    UNSET
  }		t_button_state;

typedef struct		s_layers_list
{
  SDL_Surface		*layer;
  SDL_Rect		*pos;
  struct s_layers_list	*next;
  struct s_layers_list	*prev;
}			t_layers_list;

typedef struct		s_display
{
  SDL_Surface		*screen;
  t_layers_list		*layers;
  t_current_action	action;
  t_button_state	button;
}			t_display;

typedef int		(*t_action_fptr)(t_display *, void *);

typedef struct		s_action
{
  t_current_action      current_action;
  t_action_fptr		action_fptr;
}			t_action;

int		refresh_display();
int		init_sdl();

int		display_layers(t_display *display);
int		add_layer(t_layers_list **list, SDL_Surface *layer, SDL_Rect *pos);
int		do_action(t_display *display, void *param);

#endif /* !DISPLAY_H_ */
