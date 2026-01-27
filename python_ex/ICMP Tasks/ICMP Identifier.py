import scapy.all as scapy

DESTINATION_HOST = "www.kan.org.il"

def main():
    icmp_packet = scapy.IP(dst=DESTINATION_HOST)/scapy.ICMP(id=1234)
    icmp_answer = scapy.sr1(icmp_packet)
    print(f"ICMP packet identifier is: {icmp_answer[scapy.ICMP].id}")

if __name__ == "__main__":
    main()