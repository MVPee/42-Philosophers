# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvan-pee <mvan-pee@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/20 14:43:43 by mvan-pee          #+#    #+#              #
#    Updated: 2023/12/20 15:01:51 by mvan-pee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = 	srcs/main.c
OBJS = $(SRCS:.c=.o)
CFLAGS = -Wall -Werror -Wextra

RED=\033[0;31m
GREEN=\033[0;32m
NC=\033[0m

all: $(NAME)

$(NAME): $(OBJS)
	@gcc $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	@gcc $(CFLAGS) -c $< -o $@
	@echo "\n${RED}██████╗ ██╗  ██╗██╗██╗      ██████╗ ${NC}"
	@echo "${RED}██╔══██╗██║  ██║██║██║     ██╔═══██╗${NC}"
	@echo "${RED}██████╔╝███████║██║██║     ██║   ██║${NC}"
	@echo "${RED}██╔═══╝ ██╔══██║██║██║     ██║   ██║${NC}"
	@echo "${RED}██║     ██║  ██║██║███████╗╚██████╔╝${NC}"
	@echo "${RED}╚═╝     ╚═╝  ╚═╝╚═╝╚══════╝ ╚═════╝ ${NC}\n\n"
	@echo "${GREEN}Try ./philo time_die time_eat time_sleep how_much_eat${NC}\n"
	
clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re