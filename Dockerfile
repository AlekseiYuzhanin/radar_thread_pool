FROM alpine:3.14.9

RUN apk add --update gcc g++ make

COPY . .

RUN make

CMD [ "./app" ]