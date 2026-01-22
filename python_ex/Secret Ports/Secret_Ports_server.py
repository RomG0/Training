import scapy.all as scapy

SNIFF_INTERFACE = "Software Loopback Interface 1"
SNIFF_FILTER = "dst host 127.0.0.1 and dst portrange 0-127"

def analizePorts(packet):
    if scapy.UDP in packet:
        port = packet[scapy.UDP].dport
        print(chr(port), end="")

def main():

    print("Sniffing for secret message on ports 0-127...")
    scapy.sniff(iface = SNIFF_INTERFACE, filter = SNIFF_FILTER, prn = analizePorts)

if __name__ == "__main__":
    main()
