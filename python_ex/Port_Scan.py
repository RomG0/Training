import scapy.all as scapy

IP_ADDRESS = '192.168.20.5'

def ScanPorts():
    port_list = []
    for i in range(20, 1025):
        syn_segment = scapy.TCP(dport=i, seq=123, flags='S')
        syn_packet = scapy.IP(dst=IP_ADDRESS)/syn_segment
        returned_packet = scapy.sr1(syn_packet)
        if (returned_packet[scapy.TCP].flags == 'SA'):
            port_list.append(i)
    for port in port_list:
        print(port)

def main():
    ScanPorts()

if __name__ == "__main__":
    main()