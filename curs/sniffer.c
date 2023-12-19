#include <stdio.h>
#include <stdlib.h>
#include <pcap.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>

void packet_handler(u_char *user_data, const struct pcap_pkthdr *pkthdr, const u_char *packet) {
    struct ip *ip_header = (struct ip *)(packet + 14); 
    struct tcphdr *tcp_header;
    struct udphdr *udp_header;
    struct icmphdr *icmp_header;
    char source_ip[INET_ADDRSTRLEN];
    char dest_ip[INET_ADDRSTRLEN];
    
    inet_ntop(AF_INET, &(ip_header->ip_src), source_ip, INET_ADDRSTRLEN);
    inet_ntop(AF_INET, &(ip_header->ip_dst), dest_ip, INET_ADDRSTRLEN);
    
    printf("Источник: %s\n", source_ip);
    printf("Назначение: %s\n", dest_ip);
    
    switch (ip_header->ip_p) {
        case IPPROTO_TCP:
            tcp_header = (struct tcphdr *)(packet + 14 + ip_header->ip_hl * 4);
            printf("Протокол: TCP\n");
            printf("Исходный порт: %d\n", ntohs(tcp_header->th_sport));
            printf("Целевой порт: %d\n", ntohs(tcp_header->th_dport));
            break;
        case IPPROTO_UDP:
            udp_header = (struct udphdr *)(packet + 14 + ip_header->ip_hl * 4);
            printf("Протокол: UDP\n");
            printf("Исходный порт: %d\n", ntohs(udp_header->uh_sport));
            printf("Целевой порт: %d\n", ntohs(udp_header->uh_dport));
            break;
        case IPPROTO_ICMP:
            icmp_header = (struct icmphdr *)(packet + 14 + ip_header->ip_hl * 4);
            printf("Протокол: ICMP\n");
            printf("Тип: %d\n", icmp_header->type);
            printf("Код: %d\n", icmp_header->code);
            break;
        default:
            printf("Протокол: Неизвестный\n");
            break;
    }
    
    printf("------------------------------------------------------\n");
}

int main() {
    char error_buffer[PCAP_ERRBUF_SIZE];
    pcap_if_t *devices;
    pcap_t *handle;
    struct pcap_pkthdr header;
    const u_char *packet;
    char *device;
    
    if (pcap_findalldevs(&devices, error_buffer) == -1) {
        printf("Ошибка при получении списка сетевых устройств: %s\n", error_buffer);
        return 1;
    }
    
    device = devices->name;
    
    handle = pcap_open_live(device, BUFSIZ, 1, 1000, error_buffer);
    if (handle == NULL) {
        printf("Ошибка при открытии сетевого устройства: %s\n", error_buffer);
        return 1;
    }
    
    pcap_loop(handle, -1, packet_handler, NULL);
    pcap_close(handle);
    
    return 0;
}