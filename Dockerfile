FROM ubuntu:noble-20241118.1 AS builder

WORKDIR /home
RUN apt-get update && apt-get install -y --no-install-recommends \
    g++ \
    build-essential \
    make \
    libsdl2-dev \
    libsdl2-image-dev \
    libsdl2-mixer-dev \
    libsdl2-ttf-dev && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

COPY . .
RUN make

FROM builder AS devel 

ENV SANITIZE=1
ENV XDG_RUNTIME_DIR=/tmp/runtime

RUN mkdir -p /tmp/runtime

RUN apt-get update && apt-get install -y --no-install-recommends \
    g++ \
    build-essential \
    make \
    libasan8 \
    x11-apps \
    valgrind \
    gdb \
    nano && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

RUN echo "export PS1='🐳  \[\033[1;36m\][gamedev] \[\033[1;34m\]\W\[\033[0;35m\] \[\033[1;36m\]# \[\033[0m\]'" >> ~/.bashrc
CMD ["bash"]

FROM ubuntu:noble-20241118.1 AS final 
WORKDIR /home

RUN apt-get update && apt-get upgrade -y && apt-get install -y --no-install-recommends \
    x11-apps \
    libsdl2-2.0-0 \
    libsdl2-image-2.0-0 \
    libsdl2-mixer-2.0-0 \
    libsdl2-ttf-2.0-0 && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

COPY --from=builder /home/build/bin/Game .
COPY --from=builder /home/assets .

CMD ["./Game"]
