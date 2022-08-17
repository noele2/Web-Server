# Web_Server

This project revolves around developing a single and multi-threaded HTTP Webserver in both C and Rust.  

## Rust Webserver

The Rust implementation of the HTTP webserver includes both a single-threaded and multi-threaded approach for implementing a webserver. 

The program is broken up into two different methods: one method to handle the TCP connection and the other method to handle the implemented http requests. 

![TCP](https://www.ionos.com/digitalguide/fileadmin/DigitalGuide/Schaubilder/EN-tcp-verbindungsabbau.png)


    cargo run

As always the TCP connection was implemented on port 8080 of the localhost. 

