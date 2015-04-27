##
## Makefile for sokoboule in ~/Desktop/Projects/Rush - Epikong/Example/Sokoban
## 
## Made by Thomas de Beauchene
## Login   <chauvo_t@epitech.net>
## 
## Started on  Sat Mar  8 10:15:00 2014 Thomas de Beauchene
## Last update Wed Mar 12 14:07:01 2014 Thomas de Beauchene
##

CC		:= gcc

RM		:= rm -f

SRCDIR		:= src

OBJDIR		:= build

HDRDIR		:= include

LIBDIR		:= lib

LIBSRCDIR	:= $(LIBDIR)/my

SRCS		:= 	\
			editeur.c \
			fichiers.c \
			jeu.c \
			main.c

OBJS		:= $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

SRCS		:= $(addprefix $(SRCDIR)/, $(SRCS))

#FLAGS		+= -Wextra -Wall
CFLAGS		+= -I./$(HDRDIR)
CFLAGS		+= -I/usr/include
#CFLAGS		+= -g -ggdb -g3

LDFLAGS		:= -lSDLmain -lSDL -lSDL_image
# -L/usr/lib64 -lm
# LDFLAGS	+= -g -ggdb -g3

TMPS		:= $(OBJS) $(SRCS:.c=.c~) Makefile~

NAME		:= sokoboule


all:		lib $(NAME)

$(OBJDIR)/%.o:	$(SRCDIR)/%.c
		$(COMPILE.c) $(OUTPUT_OPTION) $<

$(NAME):	$(OBJS)
		$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

$(OBJS):	| $(OBJDIR)

$(OBJDIR):
		mkdir $(OBJDIR)

# lib:
# 		make -C ./$(LIBSRCDIR)
# 		@make -C ./lib/mlx
clean:
		@$(RM) $(TMPS)
# @make clean -C ./$(LIBSRCDIR)
# make clean -C ./lib/mlx

fclean:		clean
		@$(RM) $(NAME)
# @make fclean -C ./$(LIBSRCDIR)

re:		fclean all

.PHONY:	all lib clean fclean re
