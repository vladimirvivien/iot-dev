package main

import (
	"flag"
	"fmt"
	"log"
	"net"
	"os"

	temp "./pb"
	"github.com/golang/protobuf/proto"
)

func main() {
	// setup flags
	var addr string
	network := "tcp"
	flag.StringVar(&addr, "e", ":10101", "service endpoint")
	flag.Parse()

	ln, err := net.Listen(network, addr)
	if err != nil {
		log.Println(err)
		os.Exit(1)
	}
	defer ln.Close()

	log.Printf("Temperator Service started: (%s) %s\n", network, addr)

	// connection loop
	for {
		conn, err := ln.Accept()
		if err != nil {
			log.Println(err)
			conn.Close()
			continue
		}
		log.Println("Connected to ", conn.RemoteAddr())
		go handleConnection(conn)
	}
}

func handleConnection(conn net.Conn) {
	defer func() {
		log.Println("INFO: closing connection")
		if err := conn.Close(); err != nil {
			log.Println("error closing connection:", err)
		}
	}()

	for {
		buf := make([]byte, 1024)

		n, err := conn.Read(buf)
		if err != nil {
			fmt.Println(err)
			return
		}
		if n <= 0 {
			fmt.Println("no data received")
			return
		}

		log.Println("INFO: got proto packet size:", n)

		var e temp.TempEvent
		if err := proto.Unmarshal(buf[:n], &e); err != nil {
			log.Println("failed to unmarshal:", err)
			continue
		}

		fmt.Println(e)
	}
}
