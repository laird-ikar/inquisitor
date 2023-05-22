FROM 'debian'

# Copy the poisoner source
COPY inquisitor_source /inquisitor_source

RUN apt-get update && apt-get install -y	\
	make									\
	build-essential							\
	libpcap-dev

RUN make -C /inquisitor_source

# Run bash
CMD ["/bin/bash"]