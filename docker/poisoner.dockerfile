FROM 'debian:buster'

ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y	\
	make									\
	build-essential							\
	libpcap-dev								\
	wget									\
	vim										\
	watch									\
	net-tools								\
	python3 python3-pip scapy tshark

#install python
RUN apt-get update && apt-get install -y tcpdump

RUN apt-get update && apt-get install -y arping

RUN rm -f /arpspoof_capture.pcap && touch /arpspoof_capture.pcap

# Copy the poisoner source
COPY ./inquisitor /usr/bin/

# RUN make -C /inquisitor_source re

RUN chmod +x /usr/bin/inquisitor

# ENV PATH=$PATH:/inquisitor_source

# Run bash
CMD ["/bin/bash"]