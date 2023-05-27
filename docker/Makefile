# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bguyot <bguyot@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/21 09:56:44 by bguyot            #+#    #+#              #
#    Updated: 2023/05/21 16:55:52 by bguyot           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	inquisitor

SRCS_FILE	=	inquisitor
SRCS_FOLD	= 	srcs/
SRCS		=	$(addsuffix .cpp, $(addprefix $(SRCS_FOLD), $(SRCS_FILE)))

INCS_FILE	=	inquisitor
INCS_FOLD	=	incs/
INCS		=	$(addsuffix .hpp, $(addprefix $(INCS_FOLD), $(INCS_FILE)))

OBJS		=	$(SRCS:.cpp=.o)

CC			=	c++
CFLAGS		=	-lpcap
RM			=	rm -f

all:			$(NAME)

$(NAME):		$(OBJS) $(CLASS_OBJS) $(INCS)
				$(CC) $(OBJS) -o $(NAME) $(CFLAGS)

.cpp.o:
				$(CC) -c $< -o $@ $(CFLAGS)

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re .cpp.o