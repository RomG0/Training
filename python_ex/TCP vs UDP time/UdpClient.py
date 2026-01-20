import socket
import time

UDP_SERVER_IP = "127.0.0.1"
UDP_SERVER_PORT = 8822

def TimeUdpConnection():
    
    UdpClientSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    UdpServerAddr = (UDP_SERVER_IP, UDP_SERVER_PORT)
    sendData = "Hey there!"

    StartTime = time.perf_counter()

    UdpClientSocket.sendto(sendData.encode(encoding='utf-8'), UdpServerAddr)
    recvData = UdpClientSocket.recvfrom(1024)[0].decode(encoding='utf-8')

    EndTime = time.perf_counter()

    UdpClientSocket.close()

    print(recvData)
    TimePassed = EndTime - StartTime
    print(f"Time Passed is {TimePassed}")

def main():
    TimeUdpConnection()

if __name__ == "__main__":
    main()