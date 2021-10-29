FROM ubuntu:latest

RUN apt-get update && apt-get install -y \
    build-essential \
    wget \
    unzip \
    g++ \
    mingw-w64 \
    libsfml-dev

COPY src /usr/application/src/
WORKDIR /usr/application/src/

RUN g++ -o Familiar main.cpp -DSFML_STATIC -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -static-libstdc++

RUN wget https://github.com/SFML/SFML/releases/download/2.5.1/SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit.zip -P /tmp -nc
RUN unzip /tmp/SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit -d /usr/application

# TODO: Unresolved externals
RUN x86_64-w64-mingw32-g++ main.cpp -o Familiar.exe -static -L/usr/application/SFML-2.5.1/lib -I/usr/application/SFML-2.5.1/include -DSFML_STATIC -lsfml-graphics-s -lsfml-system-s -lsfml-audio-s