NAME	= ATM

CC		= g++
CFLAGS	= -Wall -Wextra -Werror

SRCS	= main.cpp \
		  utils.cpp \
		  deposit.cpp \
		  balance.cpp \
		  file_io.cpp \
		  withdraw.cpp \
		  user_inputs.cpp \
		  find_lookup.cpp \
		  show_screen.cpp \
		  main_menue_control.cpp

OBJS	= $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp atm.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re