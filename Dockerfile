FROM debian:bullseye

RUN apt-get update && apt-get install -y \
    build-essential \
    g++ \
    libsfml-dev

COPY src /usr/application/src/
WORKDIR /usr/application/src/

RUN g++ -o Familiar main.cpp -DSFML_STATIC -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -static-libstdc++
