package main

import (
	"flag"
	"fmt"
	"log"
	"net"
	"os"

	dice "./pb"
	"github.com/golang/protobuf/proto"
)

var messages = []string{
	"the path to happiness is toward the bathroom",
	"may you become carbon neutral someday",
	"you are not illeterate",
	"be kind to pigeons, a status will be made of you someday",
	"your head is the wrong size for your body",
	"every exist is a new entrance",
	"you will be hungry again in one hour exactly",
	"they already know your secrets",
	"Hard work pays off in the future, laziness now",
	"a cynic is a frustrated optimist",
	"aliens will come to you after you read this",
	"the road to riches is paved with homework",
}

func main() {
	// setup flags
	var addr string
	var network string
	flag.StringVar(&addr, "e", ":10101", "service endpoint [ip addr or socket path]")
	flag.StringVar(&network, "n", "tcp", "network protocol [tcp,unix]")
	flag.Parse()

	ln, err := net.Listen(network, addr)
	if err != nil {
		log.Println(err)
		os.Exit(1)
	}
	defer ln.Close()

	log.Printf("DiceRoll servic started: (%s) %s\n", network, addr)

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

	var dr dice.DiceRoll
	if err := proto.Unmarshal(buf[:n], &dr); err != nil {
		log.Println("failed to unmarshal:", err)
		return
	}

	// echo buffer
	fmt.Printf("Rolled lucky number %d,  message: %s\n", dr.GetRoll(), messages[int(dr.GetRoll())])
}
