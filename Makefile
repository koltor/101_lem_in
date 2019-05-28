# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: matheme <matheme@student.le-101.fr>        +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2019/03/14 16:56:52 by matheme      #+#   ##    ##    #+#        #
#    Updated: 2019/05/28 15:55:02 by matheme     ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

# nom de l'executable
NAME = lem-in

# les routes

#source
PARSING_SRC_PATH	= parsing_src
SRC_PATH			= src
#object
OBJ_PATH			= obj
PARSING_OBJ_PATH	= parsing_obj

INC_PATH			= include
LIB_PATH			= .

# nom des fichier code source (*.c)
NAME_SRC			=	debug.c lib_plus.c main.c option.c error.c

NAME_SRC_PARSING	=	scan_create_struct.c scan_file.c scan_get_anthill.c \
						scan_get_room.c scan_get_tube.c scan_is_order.c \
						scan_is_room.c scan_is_tube.c scan_other.c \
						scan_room.c scan_skip.c scan_tube.c

#nom des ficher objects (*.o)
NAME_OBJ			= $(NAME_SRC:.c=.o)
PARSING_NAME_OBJ 	= $(NAME_SRC_PARSING:.c=.o)

#les sources
SRC		 =  $(addprefix $(SRC_PATH)/,$(NAME_SRC))
SRC		+=  $(addprefix $(PARSING_SRC_PATH)/,$(NAME_SRC_PARSING))
HEADER	=  $(INC_PATH)/lem_in.h

# les objects
OBJ			= $(addprefix $(OBJ_PATH)/,$(NAME_OBJ))
PARSING_OBJ	= $(addprefix $(PARSING_OBJ_PATH)/,$(PARSING_NAME_OBJ))

#compilateur + flags + framework
CC			= gcc#-g3 -fsanitize=address
CFLAGS		= -Wall -Wextra -Werror

#librairies
LIBFT				= $(LIB_PATH)/libft
LIBFT_INC			= $(LIB_PATH)/libft
LIBFT.A				= $(LIBFT)/libft.a

all : lib $(NAME)
	@echo "\033[48;5;22m\033[38;5;15m lem-in \033[0m"

$(NAME) : $(OBJ) $(PARSING_OBJ) $(LIBFT.A)
	@$(CC) -I $(LIBFT_INC) -L $(LIBFT) $^ -o $@ $

$(OBJ_PATH)/%.o : $(SRC_PATH)/%.c $(HEADER)
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@$(CC) -I $(LIBFT) -I $(INC_PATH) -c $< -o $@
	@printf "\033[48;5;28m \033[0m"

$(PARSING_OBJ_PATH)/%.o : $(PARSING_SRC_PATH)/%.c $(HEADER)
	@mkdir $(PARSING_OBJ_PATH) 2> /dev/null || true
	@$(CC) -I $(LIBFT) -I $(INC_PATH) -c $< -o $@
	@printf "\033[48;5;28m \033[0m"

lib:
	@make -C $(LIBFT)

clean:
	@rm -f $(OBJ)
	@rm -f $(PARSING_OBJ)
	@make -C $(LIBFT) clean
	@rmdir $(OBJ_PATH) 2> /dev/null || true
	@rmdir $(PARSING_OBJ_PATH) 2> /dev/null || true
	@echo "\033[48;5;1m\033[38;5;15m   binaire supprimer  \033[0m"

fclean: clean
	@make -C $(LIBFT) fclean
	@rm -f $(NAME)
	@echo "\033[48;5;208m\033[38;5;15m tout a été supprimer \033[0m"

re: fclean all

nonor :
	@norminette $(SRC_PATH)/*.c $(PARSING_SRC_PATH)/*.c $(INC_PATH)/*.h
