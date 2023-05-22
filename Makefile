# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bguyot <bguyot@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/21 10:13:25 by bguyot            #+#    #+#              #
#    Updated: 2023/05/22 10:34:25 by bguyot           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

up: build
	docker compose -f docker/docker-compose.yml up -d

attached: build
	docker compose -f docker/docker-compose.yml up --build

build:
	docker compose -f docker/docker-compose.yml build

down:
	docker compose -f docker/docker-compose.yml down

re: down up
	

clean:
	docker compose -f docker/docker-compose.yml down -v

.PHONY: up build down re clean docker