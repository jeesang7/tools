## Simple Server
- 간단한 리눅스 소켓 프로그래밍을 위한 서버 프로그램
  
### Build & Usage
```
(server)
$ cc -o simple_server simple_server.c
$ ./simple_server

(client)
$ nc localhost 8080
```

### Future Work
- configurable for IP, PORT
- test to send file