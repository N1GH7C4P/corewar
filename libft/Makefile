# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kpolojar <kpolojar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/02 11:15:37 by kpolojar          #+#    #+#              #
#    Updated: 2022/11/10 01:50:00 by kpolojar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
NAME = libft.a

CFLAGS = -Wall -Werror -Wextra #-fsanitize=address -g

FTS = strlen strdup strcpy strncpy strcat strncat strlcat strchr \
    strrchr strstr strnstr strcmp strncmp isdigit atoi isalpha isalnum \
    isascii isprint toupper tolower memset bzero memcpy memccpy memmove \
    memchr memcmp memalloc memdel strnew strdel strclr striter striteri \
    strmap strmapi strequ strnequ strsub strjoin strtrim strsplit itoa \
    putchar_fd putstr_fd putendl_fd putnbr_fd putchar putstr putendl \
    putnbr calloc lstnew foreach swap range count_if strlcpy lstdelone \
	lstdelone lstdel lstadd lstiter lstmap countdigits strndup realloc \
    get_next_line free_array sqrt lstrev strtoupper iswhitespace

PRINTFSRC = dstring formatting_a formatting_b ft_ftoa ft_itoabase handlers modifications_a modifications_b printf ft_ftoa_helpers modify_integers modify_floats modify_pointers modify_hexadecimals modify_octals modify_strings

FUNCS = $(patsubst %, ft_%, $(FTS))
OBJ = $(patsubst %, %.o, $(FUNCS))
SRC = $(patsubst %, %.c, $(FUNCS))

PRINTF_OBJ = $(patsubst %, %.o, $(PRINTFSRC))
PRINTF_SRC = $(patsubst %, ./printf/src/%.c, $(PRINTFSRC))

.PHONY: clean fclean re all
 
HEADERS = -I ./libft -I ./printf/include/

all: $(NAME)

$(NAME):
	$(CC) -c $(SRC) $(PRINTF_SRC) $(CFLAGS) $(HEADERS)
	ar -rc $(NAME) $(OBJ) $(PRINTF_OBJ)

clean:
	rm -f $(OBJ) $(PRINTF_OBJ)

fclean: clean 
	rm -f $(NAME)

re: fclean all
