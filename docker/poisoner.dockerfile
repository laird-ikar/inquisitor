FROM 'debian'

RUN apt-get update && apt-get install -y	\
	make									\
	build-essential							\
	libpcap-dev								\
	wget									\
	vim										\
	watch									\
	net-tools

#install python
RUN apt-get install -y python3 python3-pip scapy

# Copy the poisoner source
COPY inquisitor_source /inquisitor_source

RUN make -C /inquisitor_source re

ENV PATH=$PATH:/inquisitor_source

# Run bash
CMD ["/bin/bash"]