# Example of simple echo server
# www.solusipse.net

import socket
import time

def listen():
    connection = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    connection.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    connection.bind(('0.0.0.0', 5555))
    connection.listen(10)
    while True:
        current_connection, address = connection.accept()
        current_connection.send("WELCOME\n")
        team = current_connection.recv(256)
        print(team)
        print("sending game info")
        current_connection.send("2\n")
        current_connection.send("4 7\n")
        current_connection.setblocking(0)
        while True:
            try:
                data = current_connection.recv(2048)
            except:
                data = 0
            if data == 'quit\r\n':
                current_connection.shutdown(1)
                current_connection.close()
                break

            elif data == 'stop\r\n':
                current_connection.shutdown(1)
                current_connection.close()
                exit()

            elif data:
                print data

if __name__ == "__main__":
    try:
        listen()
    except KeyboardInterrupt:
        pass
