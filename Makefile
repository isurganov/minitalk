# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: spzona <spzona@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/29 14:11:55 by spzona            #+#    #+#              #
#    Updated: 2022/02/03 14:17:55 by spzona           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER = server 
CLIENT = client 
NAME = $(SERVER) $(CLIENT)

FLAGS = -Wall -Wextra -Werror -I

RM = rm -rf 

SERVER_SRC = ./src/server.c ./src/utils.c 
CLIENT_SRC = ./src/client.c ./src/utils.c 

SERVER_O = $(SERVER_SRC:%.c=%.o)
CLIENT_O = $(CLIENT_SRC:%.c=%.o)
DEPS_S = ${SERVER_SRC:.c=.d}
DEPS_C = ${CLIENT_SRC:.c=.d}
OBJS = $(SERVER_O) $(CLIENT_O)

HEADER = ./includes/minitalk.h

NAME: $(SERVER) $(CLIENT) $(HEADER)
all: $(NAME)
-include ${DEPS}

%.o: %.c
	@gcc $(FLAGS) $(HEADER) -o $@ -c $^ -MMD -MP

$(SERVER): $(SERVER_O) $(HEADER) Makefile
			@gcc $(SERVER_O) -o $(SERVER) -O2
			@echo "Server created"
$(CLIENT): $(CLIENT_O) $(HEADER) Makefile
			@gcc $(CLIENT_O) -o $(CLIENT) -O2
			@echo "Client created"

clean:
	@rm -f $(OBJS)
	@rm -f ${DEPS_S} ${DEPS_C}
	@echo "OBJ and DEPS deleted"

fclean: clean
	@rm -f $(SERVER) $(CLIENT)
	@echo "Output deleted"
	
re: fclean all

.PHONY: all clean fclean re