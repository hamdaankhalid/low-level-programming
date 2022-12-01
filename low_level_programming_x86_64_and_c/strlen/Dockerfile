FROM ubuntu:18.04

COPY . .

RUN apt-get update -y && \
  apt-get -y install -y nasm && \
  apt-get -y install binutils

RUN nasm -f elf64 strlen.asm -o strlen.o
RUN ld -s -o strlen strlen.o

CMD ["./strlen"]
