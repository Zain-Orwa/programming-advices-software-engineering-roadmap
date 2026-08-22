NAME	= libft.a
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
RM		= rm -f

# Detect OS and use appropriate archiver Cross-Platform Version (Works on macOS and Linux):
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
    AR = libtool -static -o
else
    AR = ar rcs
endif

SRCS	= ft_putchar.c ft_putstr.c ft_putnbr.c ft_strlen.c \
		  ft_strcpy.c ft_strncpy.c ft_strcmp.c ft_strncmp.c

OBJS	= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME) test_program

re: fclean all

test: $(NAME)
	$(CC) $(CFLAGS) main.c $(NAME) -o test_program
	./test_program

.PHONY: all clean fclean re test
