import socket

UDP_SERVER_IP = "0.0.0.0"
UDP_SERVER_PORT = 8822

def StartUdpServer():
    UdpServerSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    UdpServerSocket.bind((UDP_SERVER_IP, UDP_SERVER_PORT))

    print(f"Server listening on port {UDP_SERVER_PORT}")

    while True:
        data, ClientAddr = UdpServerSocket.recvfrom(1024)
        recvData = data.decode(encoding='utf-8')
        sendData = f"Recieved {recvData} from {ClientAddr}"
        UdpServerSocket.sendto((sendData.encode(encoding='utf-8')), ClientAddr)

def main():
    StartUdpServer()

if __name__ == "__main__":
    main()
