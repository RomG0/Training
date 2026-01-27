import socket
import struct

def CalcChecksum(data):
    if len(data) % 2:
        data += b'\x00'
    checksum = 0
    for i in range(0, len(data), 2):
        word = (data[i] << 8) + data[i + 1]
        checksum += word
    checksum = (checksum >> 16) + (checksum & 0xFFFF)
    checksum += (checksum >> 16)
    return ~checksum & 0xFFFF

def send_ping(host):
    message = "Hello, this is a ping message!"

    sock = socket.socket(socket.AF_INET, socket.SOCK_RAW, socket.IPPROTO_ICMP)
    

    icmp_type = 8 
    icmp_code = 0
    checksum = 0
    identifier = 12345
    sequence_number = 1
    payload = message.encode('utf-8')
    
    header = struct.pack('!BBHHH', icmp_type, icmp_code, checksum, identifier, sequence_number)
    
    packed_packet = header + payload

    checksum = CalcChecksum(packed_packet)
    
    header = struct.pack('!BBHHH', icmp_type, icmp_code, checksum, identifier, sequence_number)
    
    packet = header + payload

    sock.sendto(packet, (host, 1))
    print(f'Sent ICMP Echo Request to {host}')

