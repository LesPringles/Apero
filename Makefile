NAME	= apero

SRCS	= ./sources/main.c		\
	  ./sources/layers.c		\
	  ./sources/sdl_init.c		\
	  ./sources/print_pixel.c	\
	  ./sources/print_square.c	\
	  ./sources/print_circle.c	\
	  ./sources/print_disc.c	\
	  ./sources/do_action.c

OBJS	= $(SRCS:.c=.o)

CFLAGS	+= -W -Wall -Wextra -g

OPTIONS	+= -lSDL -lSDL_mixer -lm

all: $(NAME)

$(NAME): $(OBJS)
	gcc $(OBJS) -o $(NAME) $(OPTIONS) 

clean:
	rm -f $(OBJS) $(NAME)

re: clean all
