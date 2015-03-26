#include "../includes/display.h"
#include "../includes/shapes.h"

static const t_action	actions[] =
  {
    {PRINT_PIXEL, &print_pixel},
    {PRINT_SQUARE, &print_square}
  };

int		do_action(t_display *display, void *param)
{
  unsigned int	i;

  for (i = 0; i < (sizeof(actions) / sizeof(actions[0])); i++)
    if (display->action == actions[i].current_action)
      return actions[i].action_fptr(display, param);
  return (-1);
}
