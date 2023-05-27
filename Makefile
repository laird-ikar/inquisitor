# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bguyot <bguyot@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/21 10:13:25 by bguyot            #+#    #+#              #
#    Updated: 2023/05/26 18:16:19 by bguyot           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

up: build
	docker compose -f docker/docker-compose.yml up -d

attached: build
	docker compose -f docker/docker-compose.yml up --build

build: docker
	docker compose -f docker/docker-compose.yml build

down: docker
	docker compose -f docker/docker-compose.yml down

stop: docker
	docker compose -f docker/docker-compose.yml stop

re: down up

docker:
	until docker info > /dev/null 2>&1; do open -a Docker; done

clean:
	docker compose -f docker/docker-compose.yml down -v

.PHONY: up build down re clean docker