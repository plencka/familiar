FROM debian:bullseye

ARG APP_NAME=Familiar

RUN apt-get update && apt-get install -y \
    build-essential \
    unzip \
    g++ \
    g++-mingw-w64-x86-64 \
    libsfml-dev

ADD https://github.com/SFML/SFML/releases/download/2.5.1/SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit.zip /tmp
RUN unzip /tmp/SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit -d /externals

COPY src /application/src/
WORKDIR /application/src/

RUN rm -rf ../builds \
    && mkdir -p ../builds/Linux \
    && g++ -o ../builds/Linux/${APP_NAME} main.cpp \
    -lsfml-graphics \
    -lsfml-window \
    -lsfml-system \
    -lsfml-audio \
    && mkdir -p ../builds/Win_x86_64 \
    && x86_64-w64-mingw32-g++ main.cpp -o ../builds/Win_x86_64/${APP_NAME}.exe \
    -L/externals/SFML-2.5.1/lib -I/externals/SFML-2.5.1/include \
    -static-libstdc++ -static-libgcc \
    -DSFML_STATIC \
    -lsfml-graphics-s \
    -lsfml-window-s \
    -lsfml-system-s \
    -lsfml-audio-s \
    -lfreetype \
    -lopengl32 -lwinmm -lgdi32
