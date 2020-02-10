FROM debian:10

RUN apt-get update
RUN apt-get install -y gcc make libsdl2-dev

COPY ./ /app
WORKDIR /app
