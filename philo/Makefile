# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/20 14:43:43 by mvan-pee          #+#    #+#              #
#    Updated: 2024/01/18 10:24:24 by mvpee            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = 	main.c \
		ft_utils.c \
		routine.c \
		actions.c

OBJS = $(SRCS:%.c=%.o)
CFLAGS = -Wall -Werror -Wextra #-g -fsanitize=thread

RED=\033[0;31m
GREEN=\033[0;32m
NC=\033[0m

all: $(NAME)

$(NAME): $(OBJS)
	@gcc $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "\n${RED}██████╗ ██╗  ██╗██╗██╗      ██████╗ ${NC}"
	@echo   "${RED}██╔══██╗██║  ██║██║██║     ██╔═══██╗${NC}"
	@echo   "${RED}██████╔╝███████║██║██║     ██║   ██║${NC}"
	@echo   "${RED}██╔═══╝ ██╔══██║██║██║     ██║   ██║${NC}"
	@echo   "${RED}██║     ██║  ██║██║███████╗╚██████╔╝${NC}"
	@echo   "${RED}╚═╝     ╚═╝  ╚═╝╚═╝╚══════╝ ╚═════╝ MVPee${NC}\n\n"
	@echo   "${GREEN}Try ./philo nbr_of_philo time_die time_eat time_sleep [how_much_eat]${NC}\n"
	
%.o: %.c
	@gcc $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re