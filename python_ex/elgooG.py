from dnslib import DNSRecord, DNSHeader, RR, A, QTYPE
import socket

LISTEN_IP = "0.0.0.0"
LISTEN_PORT = 53

REDIRECT_DOMAIN = "google.co.il."
REDIRECT_IP = "1.2.3.4"

