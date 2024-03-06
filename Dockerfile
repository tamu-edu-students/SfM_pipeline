FROM hypertools_cubert:latest

RUN apt-get update 

RUN apt-get install -y \
    python3-pip \
    libceres-dev 
    

RUN apt update && apt-get update && apt-get install -y \
    libpcl-dev \
    libvtk7-dev

    # gdb \
    # gdbserver

