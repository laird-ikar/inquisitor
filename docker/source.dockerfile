FROM 'debian'

RUN apt-get update && apt-get install -y vsftpd net-tools

COPY vsftpd.conf /etc/vsftpd.conf

RUN mkdir -p /var/run/vsftpd/empty

#create user for ftp
RUN useradd -d /home/ftpuser -m ftpuser

#set password for ftp user
RUN echo "ftpuser:ftpuser" | chpasswd

#set permissions for ftp user
RUN chown ftpuser:ftpuser /home/ftpuser/ -R

#let ftpuser use ftp server
RUN echo "local_root=/home/ftpuser" >> /etc/vsftpd.conf

EXPOSE 21

CMD ["vsftpd"]