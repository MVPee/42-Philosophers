# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvan-pee <mvan-pee@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/20 14:43:43 by mvan-pee          #+#    #+#              #
#    Updated: 2023/12/20 14:43:57 by mvan-pee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

LIBFT = srcs/libft

SRCS = 	srcs/philo/main.c

OBJS = $(SRCS:.c=.o)

CFLAGS = -I$(LIBFT) -Wall -Werror -Wextra
LDFLAGS = -L$(LIBFT) -lft

all: $(NAME)

$(LIBFT)/libft.a:
	$(MAKE) -C $(LIBFT)

$(NAME): $(OBJS) $(LIBFT)/libft.a
	gcc $(OBJS) $(LDFLAGS) -o $(NAME)

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT) clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT) fclean
	rm -f $(NAME)

re: fclean all

sort: all
	./push_swap 1 4 56 1009 12938

nsort: all
	./push_swap 1 2 56 12938 1009 

.PHONY: all clean fclean re