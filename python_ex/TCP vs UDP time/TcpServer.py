import socket

TCP_SERVER_IP = "0.0.0.0"
TCP_SERVER_PORT = 8821

def StartTcpServer():
    TcpServerSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    TcpServerSocket.bind((TCP_SERVER_IP, TCP_SERVER_PORT))
    TcpServerSocket.listen()

    print(f"Server listening on port {TCP_SERVER_PORT}")

    while True:
        TcpStream, ClientAddr = TcpServerSocket.accept()
        recvData = TcpStream.recv(1024).decode(encoding='utf-8')
        sendData = f"Recieved {recvData} from {ClientAddr}"
        TcpStream.send(sendData.encode(encoding='utf-8'))
        TcpStream.close

def main():
    StartTcpServer()

if __name__ == "__main__":
    main()
