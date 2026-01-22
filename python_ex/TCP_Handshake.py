import scapy.all as scapy

syn_segment = scapy.TCP(dport=80, seq=123, flags='S')
syn_packet = scapy.IP(dst='www.google.com')/syn_segment
syn_ack_packet = scapy.sr1(syn_packet)
ack_segment = scapy.TCP(dport= 80, seq= 124, ack= syn_ack_packet[scapy.TCP].seq + 1, flags='A')
ack_packet = scapy.IP(dst='www.google.com')/ack_segment
scapy.send(ack_packet)
