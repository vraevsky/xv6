FROM ubuntu:18.04
RUN 	apt-get update && apt-get install -y qemu-kvm qemu && \
	apt-get install -y build-essential &&\
	apt-get install -y git
RUN git clone https://github.com/noam1023/xv6-public.git
CMD ["/bin/bash"]

