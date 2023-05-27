# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bguyot <bguyot@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/27 11:10:28 by bguyot            #+#    #+#              #
#    Updated: 2023/05/27 16:09:55 by bguyot           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = inquisitor

SRCS_FILE = arping main capture_and_forward
SRCS = $(addprefix srcs/, $(addsuffix .cpp, $(SRCS_FILE)))

INCS_FILE = arping main capture_and_forward
INCS = $(addprefix incs/, $(addsuffix .hpp, $(INCS_FILE)))

OBJS = $(SRCS:.cpp=.o)

CC = c++
CFLAGS = -pthread -lpcap

all: $(NAME)

$(NAME): $(OBJS) $(INCS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY : all clean fclean re