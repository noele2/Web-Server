# Web_Server

This project revolves around developing a single and multi-threaded HTTP Web Server in both C and Rust.  

## Rust Web Server

The Rust implementation of the HTTP Web Server includes both a single-threaded and multi-threaded approach for implementing a Web Server. 

### Single Threaded

The program is broken up into two different methods: one method to handle the TCP connection and the other method to handle the implemented http requests. 

![TCP](https://www.ionos.com/digitalguide/fileadmin/DigitalGuide/Schaubilder/EN-tcp-verbindungsabbau.png)

Within the TCP protocol method, each TCP listening instance is iterated through to get a single stream between the client and the server. 

The resulting TCP connection request may look like:

    $ cargo run
    Compiling Single-Threaded v0.1.0 (file:///projects/Single-Threaded )
        Finished dev [unoptimized + debuginfo] target(s) in 0.42s
        Running `target/debug/Single-Threaded `
    Request: [
        "GET / HTTP/1.1",
        "Host: 127.0.0.1:7878",
        "User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:99.0) Gecko/20100101 Firefox/99.0",
        "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8",
        "Accept-Language: en-US,en;q=0.5",
        "Accept-Encoding: gzip, deflate, br",
        "DNT: 1",
        "Connection: keep-alive",
        "Upgrade-Insecure-Requests: 1",
        "Sec-Fetch-Dest: document",
        "Sec-Fetch-Mode: navigate",
        "Sec-Fetch-Site: none",
        "Sec-Fetch-User: ?1",
        "Cache-Control: max-age=0",
    ]

The *handle_connections* method is capable of returning the http requests including GET, POST, etc by hardcoding the corresponding html documents or messages in the client buffer. 

The single-threaded Rust HTTP Web Server can be accessed by first cloning the repository and then navigating to */Rust_Webserver/Single-Threaded* directory. This implementation utilizes Rusts's cargo structures which implement the files below:

[Cargo.toml](noele2/Web-Server/Rust_Webserver/Single-Threaded/Cargo.toml)
[Cargo.lock](noele2/Web-Server/Rust_Webserver/Single-Threaded/Cargo.lock)

As such the server code can be run using the following simple command

    cargo run

The TCP connection listens to port 8080 and the HTTP Web Server can be easily accessed at localhost:8080 or *'127.0.0.1:8080'*. The resulting html output can be customized in the index.html page. 

### Multi-Threaded

The multi-threaded HTTP Web Server utilizes *thread pools* in order to utilize a group of spawned tasks to run processes concurrently. As Rust provides a standard thread library (*thread::spawn *), this was not too bad as opposed to the C implementation of threads. 

In essence, we utilize a sequence of Worker structs to fetch the tasks held in a queue and assign them to their corresponding thread in the thread pool. Specifically, every thread pool will create a channel saving the sending and receiving sides in a Mutex to lock the data. 

Finally, the Drop train within Rust was implemented on each of the threads to improve the efficiency of each request by shutting down the thread after the client's disconnection. This thread can then be put back into the thread pool for future use. 

Similarly, the server can be run using the following command

    cargo run

The resulting connections can look something like this:

    $ cargo run
    Compiling Multi-Threaded v0.1.0 (file:///projects/Multi-Threaded)
        Finished dev [unoptimized + debuginfo] target(s) in 1.0s
        Running `target/debug/hello`
    Worker 0 got a job; executing.
    Shutting down.
    Shutting down worker 0
    Worker 3 got a job; executing.
    Worker 1 disconnected; shutting down.
    Worker 2 disconnected; shutting down.
    Worker 3 disconnected; shutting down.
    Worker 0 disconnected; shutting down.
    Shutting down worker 1
    Shutting down worker 2
    Shutting down worker 3

Workers 0 and 3 got the first two requests and are shutdown after the client disconnects while worker 1 and 2 remain active concurrently. 

The server can be accessed by localhost:8080 or *'127.0.0.1:8080'* and is now able to respond to multiple client at once due to its improved and efficient multi-threading capabilities. 

## C Web Server

The C implementation of the HTTP Web Server includes both a single-threaded and multi-threaded approach for implementing a HTTP Web Server as well. 

### Single Threaded

The 