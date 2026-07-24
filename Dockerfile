FROM ubuntu:24.04

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    gdb

WORKDIR /workspace

COPY . .

RUN cmake -S . -B build && cmake --build build

CMD ["./build/server"]