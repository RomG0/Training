import scapy.all as scapy

SERVER_IP = "127.0.0.1"

def SendSecretMessage(message):
    for i in range(len(message)):
        secretPortPacket = scapy.IP(dst=SERVER_IP) / scapy.UDP(dport=ord(message[i]))
        scapy.send(secretPortPacket)

def main():
    secretMessage = input("Enter the message you want to pass: ")
    SendSecretMessage(secretMessage)

if __name__ == "__main__":
    main()
