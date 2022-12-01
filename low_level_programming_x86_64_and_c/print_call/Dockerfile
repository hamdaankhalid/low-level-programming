FROM ubuntu:18.04

COPY . .

RUN apt-get update -y && \
  apt-get -y install -y nasm && \
  apt-get -y install binutils

RUN nasm -f elf64 print_call.asm -o print_call.o
RUN ld -s -o print_call print_call.o

CMD ["./print_call"]
