FROM ubuntu:18.04 as environ


RUN apt-get update -y && \
  apt-get -y install -y nasm && \
  apt-get -y install binutils && \
  apt-get -y install gcc

FROM environ

COPY . .
# create object file from asm
RUN nasm -f elf64 mylib.asm -o mylib.o
# create object file c code
RUN gcc -c sort.c

# link asm and c object files
RUN gcc mylib.o sort.o -o sort

CMD ["./sort"]
