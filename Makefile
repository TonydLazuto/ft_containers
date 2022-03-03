.PHONY		:	all clean fclean re

NAME		=	ft_containers

CC			=	c++

CFLAGS		=	-Wall -Wextra -Werror -pedantic -std=c++98

RM			=	/bin/rm -rf

OBJ_DIR		=	obj

SRCS		=	main.cpp

OBJS		=	$(patsubst %.cpp, $(OBJ_DIR)/%.o, $(SRCS))

all: 			$(NAME)

$(NAME): 		$(OBJ_DIR) $(OBJS)
				$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

$(OBJ_DIR):
				@mkdir -p $@

$(OBJS) : $(OBJ_DIR)/%.o: %.cpp
				$(CC) $(CFLAGS) -c $< -o $@

clean:			
				$(RM) $(OBJ_DIR)

fclean:			clean
				$(RM) $(NAME)

re:				fclean all
