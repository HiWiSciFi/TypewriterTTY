# syntax=docker/dockerfile:1

FROM debian
WORKDIR /app
COPY ./config/* /etc/TypewriterTTY/
COPY . .

RUN bash ./inst.sh

RUN useradd app
USER app

CMD [ "./typewritertty" ]
