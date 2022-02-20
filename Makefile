.PHONY		:	all clean fclean re

NAME		=	ft_containers

CC			=	c++

CFLAGS		=	-std=c++98 -Wall -Wextra -Werror -pedantic -I. -fsanitize=address

RM			=	/bin/rm -f

OBJ_DIR		=	obj

SRCS		=	main.cpp

OBJS		=	$(addprefix $(OBJ_DIR)/,$(SRCS:.cpp=.o))

all: 			$(NAME)

$(NAME): 		$(OBJS)
				$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

$(OBJ_DIR)/%.o:	%.cpp
				@mkdir -p $(OBJ_DIR)
				$(CC) $(CFLAGS) -c $< -o $@

clean:			
				rm -rf $(OBJ_DIR)

fclean:			clean
				$(RM) $(NAME)

re:				fclean all
