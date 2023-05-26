FROM 'debian'

#install ftp and ping
RUN apt-get update && apt-get install -y ftp iputils-ping net-tools

CMD ["bash"]