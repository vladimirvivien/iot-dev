FROM golang:latest

COPY  .    /temp-server
COPY  ./pb /temp-server/pb
WORKDIR    /temp-server/  

RUN go get -d -v ./...
RUN CGO_ENABLED=0 go build -a -o temp-server .

FROM alpine:latest
COPY --from=0 /temp-server/temp-server .
CMD ["./temp-server"]