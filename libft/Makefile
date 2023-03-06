NAME = libft.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror

HEADER = libft.h

SRC = ft_memset.c       \
	ft_bzero.c          \
	ft_memcpy.c         \
	ft_memmove.c        \
	ft_memchr.c         \
	ft_memcmp.c         \
	ft_strlen.c         \
	ft_isalpha.c        \
	ft_isdigit.c        \
	ft_isalnum.c        \
	ft_isascii.c        \
	ft_isprint.c        \
	ft_toupper.c        \
	ft_tolower.c        \
	ft_strchr.c         \
	ft_strrchr.c        \
	ft_strlcpy.c        \
	ft_strlcat.c        \
	ft_strnstr.c        \
	ft_atoi.c           \
	ft_calloc.c         \
	ft_strncmp.c        \
	ft_strjoin.c	    \
	ft_strdup.c		    \
	ft_substr.c		    \
	ft_strtrim.c        \
	ft_putchar_fd.c     \
	ft_putendl_fd.c     \
	ft_putnbr_fd.c      \
	ft_putstr_fd.c      \
	ft_strmapi.c        \
	ft_striteri.c       \
	ft_itoa.c           \
	ft_split.c			\
	utils.c				\

BONUS = ft_lstnew.c     \
	ft_lstadd_front.c   \
	ft_lstsize.c        \
	ft_lstlast.c        \
	ft_lstadd_back.c    \
	ft_lstdelone.c      \
	ft_lstclear.c       \
	ft_lstiter.c        \
	ft_lstmap.c

OBJS = ${SRC:.c=.o}

OBJB = ${BONUS:.c=.o}

all: ${NAME}

${NAME}: ${OBJS} ${HEADER}
	ar -rcs $@ ${OBJS}

%.o: %.c
	${CC} ${CFLAGS} -o $@ -c $<

bonus: all ${OBJB} ${HEADER}
	ar -rcs ${NAME} ${OBJB}

clean:
	rm -rf ${OBJS} ${OBJB}

fclean: clean
	rm -rf ${NAME}

re: fclean all


