# syntax=docker/dockerfile:1

FROM raspbian
WORKDIR /app
COPY ./config/* /etc/TypewriterTTY/
COPY . .

RUN /bin/bash ./inst.sh
RUN make all

RUN useradd app
USER app

CMD [ "./typewritertty" ]
