FROM debian:bullseye

RUN apt-get update && apt-get install -y \
    build-essential \
    g++ \
    gcc-multilib \
    mingw-w64 \
    libsfml-dev

COPY src /usr/application/src/
WORKDIR /usr/application/src/

# RUN g++ -c main.cpp
# RUN g++ main.o -o Familiar -lsfml-graphics -lsfml-window -lsfml-system

# RUN x86_64-w64-mingw32-g++ main.cpp -o Familiar.exe -lsfml-system -lsfml-graphics -lsfml-window -I /usr/include
RUN g++ -o Familiar main.cpp -DSFML_STATIC -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -static-libstdc++
