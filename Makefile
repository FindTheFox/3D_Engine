# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <user42@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/04 18:53:52 by saneveu           #+#    #+#              #
#    Updated: 2020/04/28 23:28:50 by user42           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include includes/def/sources.mk 
include	includes/def/includes.mk

BLACK	=	\033[30m
RED		=	\033[31m
GREEN	=	\033[32m
YELLOW	=	\033[33m
BLUE	=	\033[34m
PURPLE	=	\033[35m
TUR		=	\033[36m
WHITE	=	\033[37m
END		=	\033[0m

UP 		=	\033[A
CUT 	=	\033[K

# project
NAME	=	DooM
OS		=	$(shell uname)

SRCDIR	=	srcs/
SRC     =	$(addprefix $(SRCDIR), $(SRCS_FILE))

OBJDIR	=	./obj
OBJ		=	$(addprefix $(OBJDIR)/, $(SRCS_FILE:.c=.o))

INCDIR	=	./includes
HEADER	=	$(addprefix $(INCDIR)/,$(INC_FILE))

# compiler
CC		=	gcc #-g -fsanitize=address
CFLAGS	=	-Ofast -march=native #-Wall -Wextra -Werror

ifeq ($(OS), Linux)
	SDL		=	`sdl2-config --cflags --libs` -lSDL2_ttf -lSDL2_image
	DIRSDL	=	
else
	SDL		=	-F ~/Library/Frameworks -framework SDL2 -framework SDL2_ttf -framework SDL2_image
	DIRSDL	=	-I ./SDL
endif 

# ft library
FT		=	./libft/
FT_LIB	=	$(addprefix $(FT),libft.a)

all: 		obj $(FT_LIB) $(NAME)

obj:
			mkdir -p $(OBJDIR)
			mkdir -p $(OBJDIR)/engine $(OBJDIR)/exit $(OBJDIR)/events $(OBJDIR)/vectors $(OBJDIR)/obj_parser $(OBJDIR)/matrices $(OBJDIR)/init $(OBJDIR)/platform


$(FT_LIB):
			@$(MAKE) -j8 -C $(FT)
			@echo "${GREEN}{LIBRARY COMPILED}${END}"

$(NAME):	$(OBJ) $(FT_LIB)
			@$(CC) $(CFLAGS) -I$(INCDIR) -o $(NAME) $(OBJ) $(FT_LIB) $(SDL)  -lm -lpthread -o $@
			@echo "${GREEN}{$@ COMPILED}${END}"

$(OBJDIR)/%.o:$(SRCDIR)/%.c $(HEADER)
			@echo "${TUR}compiling [$@] ...${END}"
			@$(CC) $(CFLAGS) -I$(INCDIR) -c -o $@ $< $(DIRSDL)
			@printf "$(UP)$(CUT)"

clean:
			@/bin/rm -rf $(OBJDIR)
			@$(MAKE) -C $(FT) clean
			@echo "${PURPLE}{.o deleted}${END}"

fclean:		clean
			@/bin/rm -rf $(NAME)
			@$(MAKE) -C $(FT) fclean
			@echo "${RED}{$(NAME) deleted}${END}"
			@echo "${RED}{$(LIB) deleted}${END}"

re:			fclean all

SDL2:
			brew install sdl2
			brew link sdl2
			brew install sdl2_ttf
			brew link sdl2_ttf
			brew install sdl2_mixer
			brew link sdl2_mixer
			cp -rf SDL/framework/SDL2_mixer.framework ~/Library/Frameworks
			cp -rf SDL/framework/SDL2_ttf.framework ~/Library/Frameworks
			cp -rf SDL/framework/SDL2.framework ~/Library/Frameworks

.PHONY:		all clean fclean re
