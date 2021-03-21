#!/usr/bin/env python

import http.server

from http.server import BaseHTTPRequestHandler, HTTPServer
from os import curdir, sep

PORT = 9090
host = "192.168.0.14"
Handler = http.server.SimpleHTTPRequestHandler


class MyHandler(BaseHTTPRequestHandler):
    def do_HEAD(s):

        s.send_response(200)
        s.send_header("Content-type", "text/html")
        s.end_headers()

    def do_GET(self):
        if self.path == "/":
            self.path = "/index.html"
        try:
            sendReply = False
            if self.path.endswith(".html") or self.path.endswith(".txt"):
                mimetype = 'text/html'
                sendReply = True
            if self.path.endswith(".jpg"):
                mimetype = 'image/jpg'
                sendReply = True
            if self.path.endswith(".gif"):
                mimetype = 'image/gif'
                sendReply = True
            if self.path.endswith(".js"):
                mimetype = 'application/javascript'
                sendReply = True
            if self.path.endswith(".css"):
                mimetype = 'text/css'
                sendReply = True
            if self.path.endswith(".png"):
                mimetype = 'image/png'
            if self.path.endswith(".jpg"):
                mimetype = 'image/jpg'
                sendReply = True

            if sendReply == True:
                f = open(curdir + sep + self.path)
                self.send_response(200)
                self.send_header('Content-type', mimetype)
                self.end_headers()
                str1 = f.read()
                str2 = str.encode(str1)
                self.wfile.write(str2)
                f.close()
            return
        except IOError:
            self.send_error(404, 'File Not Found: %s' % self.path)

    def do_POST(self):
        global blink
        if self.path == "/actions":
            message = ""
            content_length = int(self.headers['Content-Length'])
            post_data = self.rfile.read(content_length).decode('utf-8')
            message += post_data
            length = len(message)
            f = open('basys.txt', 'w')
            f.write(message)
            f.truncate(length)
            f.close()

            # Redirect the browser on the main page
            self.send_response(302)
            self.send_header('Location', '/')
            self.end_headers()
            print(self.headers)
            print(self.path)
            print(self.command)

            return


import ssl
server = HTTPServer((host, PORT), MyHandler)
print("Serving at: "+ host)
server.socket = ssl.wrap_socket(server.socket, certfile='./server.pem',  server_side=True)
server.serve_forever()





