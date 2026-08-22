# =========================
# my_lib Makefile
# =========================

NAME    = libmy_lib.a
CC      = cc
CFLAGS  = -Wall -Wextra -Werror
RM      = rm -f

# Detect OS and use appropriate archiver
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
    AR = libtool -static -o
else
    AR = ar rcs
endif

INCDIR  = include
SRCDIR  = src
TESTDIR = tests

# ---- Sources (add new .c files here as you create them) ----
SRCS = \
    $(SRCDIR)/io/my_putchar.c \
    $(SRCDIR)/io/my_putstr.c \
    $(SRCDIR)/io/my_putnbr.c \
		$(SRCDIR)/io/my_putnbr_base.c \
    $(SRCDIR)/string/my_strlen.c \
    $(SRCDIR)/string/my_strcpy.c \
    $(SRCDIR)/string/my_strncpy.c \
		$(SRCDIR)/string/my_strlcpy.c \
    $(SRCDIR)/string/my_strcmp.c \
    $(SRCDIR)/string/my_strncmp.c \
    $(SRCDIR)/string/my_strstr.c \
		$(SRCDIR)/string/my_strcat.c \
		$(SRCDIR)/string/my_strncat.c \
		$(SRCDIR)/string/my_atoi.c \
		$(SRCDIR)/string/my_atoi_base.c \
		$(SRCDIR)/string/my_strlcat.c \
		$(SRCDIR)/utils/my_isalpha.c \
		$(SRCDIR)/utils/my_isdigit.c \
		$(SRCDIR)/utils/my_isalnum.c \
		$(SRCDIR)/utils/my_isascii.c \
		$(SRCDIR)/utils/my_isprint.c \
		$(SRCDIR)/string/my_str_is_alpha.c \
		$(SRCDIR)/string/my_str_is_numeric.c \
		$(SRCDIR)/string/my_str_is_lowercase.c \
		$(SRCDIR)/string/my_str_is_uppercase.c \
		$(SRCDIR)/string/my_str_is_printable.c \
		$(SRCDIR)/string/my_str_to_uppercase.c \
		$(SRCDIR)/string/my_str_to_lowercase.c \
		$(SRCDIR)/string/my_str_capitalize.c 


OBJS = $(SRCS:.c=.o)

TEST_NAME = test_my_lib
TEST_SRC  = $(TESTDIR)/main.c
TEST_OBJ  = $(TEST_SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -I $(INCDIR) -c $< -o $@

clean:
	$(RM) $(OBJS) $(TEST_OBJ)

fclean: clean
	$(RM) $(NAME) $(TEST_NAME)

re: fclean all

test: $(NAME) $(TEST_OBJ)
	$(CC) $(CFLAGS) -I $(INCDIR) $(TEST_OBJ) -L. -lmy_lib -o $(TEST_NAME)
	./$(TEST_NAME)

.PHONY: all clean fclean re test

