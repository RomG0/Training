import socket
import time

TCP_SERVER_IP = "127.0.0.1"
TCP_SERVER_PORT = 8821

def TimeTcpConnection():
    
    TcpClientSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sendData = "Hey there!"
    
    StartTime = time.perf_counter()

    TcpClientSocket.connect((TCP_SERVER_IP, TCP_SERVER_PORT))
    TcpClientSocket.send(sendData.encode(encoding='utf-8'))
    recvData = TcpClientSocket.recv(1024).decode(encoding='utf-8')

    EndTime = time.perf_counter()

    TcpClientSocket.close()

    print(recvData)
    TimePassed = EndTime - StartTime
    print(f"Time Passed is {TimePassed}")

def main():
    TimeTcpConnection()

if __name__ == "__main__":
    main()