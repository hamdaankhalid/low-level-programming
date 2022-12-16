FROM ubuntu:18.04

COPY . .

RUN apt-get update -y && \
  apt-get -y install -y nasm && \
  apt-get -y install binutils && \
  apt-get -y install python

CMD ["python", "test.py"]
