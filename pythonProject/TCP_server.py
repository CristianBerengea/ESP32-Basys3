import socket
import sys
import requests


host = "192.168.0.14"

server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind((host,9092))
server_socket.listen(5)
print("Server :"+host+":9092")

try:
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
except socket.error as err:
    print("Failed to create a soket")
    print("Reason"+ str(err))
    sys.exit()

while True:
    print("Server waiting for connection")
    client_socket,addr=server_socket.accept()
    print("client connected from", addr)
    while True:
        data = client_socket.recv(16)
        string = data.decode('utf-8')
        print("Recived from client : %s"% string)
        try:
            if(string=="cmd"):
                x = requests.get('https://192.168.0.14:9090/basys.txt', verify=False)
                print(x.text)
                str = x.text
                client_socket.send(bytes(str,'utf-8'))
            else:
                length = len(string)
                f = open('recive.txt', 'w')
                f.write(string)
                f.truncate(length)
                f.close()
        except:
            print('Exited by the user')
    client_socket.close()
server_socket.close()