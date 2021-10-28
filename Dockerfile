FROM debian:bullseye

RUN apt-get update && apt-get install -y \
    build-essential \
    g++ \
    libsfml-dev

COPY src /usr/src/
WORKDIR /usr/src/

RUN g++ -c --static ./main.cpp
RUN g++ main.o -o Familiar -lsfml-graphics -lsfml-window -lsfml-system
RUN chmod +x ./Familiar

CMD [ "./Familiar" ]