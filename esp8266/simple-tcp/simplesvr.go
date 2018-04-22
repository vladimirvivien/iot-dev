package main

import (
	"flag"
	"fmt"
	"net"
	"os"
)

func main() {
	var addr string
	var network string
	flag.StringVar(&addr, "e", ":10101", "service endpoint [ip addr or socket path]")
	flag.StringVar(&network, "n", "tcp", "network protocol [tcp,unix]")
	flag.Parse()

	// validate network
	switch network {
	case "tcp", "tcp4", "tcp6", "unix":
	default:
		fmt.Println("unsupported network protocol")
		os.Exit(1)
	}

	l, err := net.Listen(network, addr)
	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}
	defer l.Close()
	fmt.Printf("listening at (%s) %s\n", network, addr)

	for {
		conn, err := l.Accept()
		if err != nil {
			fmt.Println("failed to accept conn:", err)
			conn.Close()
			continue
		}
		fmt.Println("connected to: ", conn.RemoteAddr())

		go handleConnection(conn)
	}
}

func handleConnection(conn net.Conn) {
	defer conn.Close() // clean up when done

	buf := make([]byte, 1024)

	n, err := conn.Read(buf)
	if err != nil {
		fmt.Println(err)
		return
	}

	// echo buffer
	w, err := conn.Write(buf[:n])
	if err != nil {
		fmt.Println("failed to write to client:", err)
		return
	}
	if w != n { // was all data sent
		fmt.Println("warning: not all data sent to client")
		return
	}
}
