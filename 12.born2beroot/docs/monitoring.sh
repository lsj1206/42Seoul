#!/bin/bash

# ===== 정보 수집 =====

# Architecture: uname -a로 운영체제, 커널 버전, 아키텍처 정보 수집
arc=$(uname -a)

# CPU physical: /proc/cpuinfo의 physical id 개수로 물리 프로세서 수 계산
py_cpu=$(grep "physical id" /proc/cpuinfo | wc -l)

# vCPU: /proc/cpuinfo의 processor 항목 수로 가상 프로세서 수 계산
vr_cpu=$(cat /proc/cpuinfo | grep -c processor)

# Memory Usage: free -m으로 RAM 사용량, 전체량, 사용률 계산
mem_use=$(free -m | grep Mem | awk '{printf "%d/%dMB (%.2f%%)\n", $3, $2, $3/$2 * 100}')

# Disk Usage: df -BM -a 결과 중 /dev/mapper 항목을 합산해 디스크 사용량과 사용률 계산
a_disk=$(df -BM -a | grep /dev/mapper | awk '{sum_used+=$3}{sum_size+=$2}END{sum_size=sum_size/1024}END{printf "%d/%.0fGb\n", sum_used, sum_size}')
per_disk=$(df -BM -a | grep /dev/mapper | awk '{sum_size+=$2}{sum_used+=$3}END{sum_used=sum_used*100}END{disk_per=sum_used/sum_size}END{print disk_per}')

# CPU load: mpstat의 idle 비율을 100에서 빼서 현재 CPU 사용률 계산
per_cpu=$(mpstat | grep all | awk '{printf "%.1f%%\n", 100-$13}')

# Last boot: who -b로 마지막 부팅 날짜와 시간 수집
boot_time=$(who -b | awk '{print $3, $4}')

# LVM use: lsblk 결과에 lvm 타입 장치가 있으면 yes, 없으면 no로 변환
lvm_cnt=$(lsblk | grep lvm | wc -l)
lvm_use=$(if [ $lvm_cnt -gt 0 ] ; then printf "yes\n" ; else printf "no\n" ; fi)

# Connections TCP: ss 결과에서 tcp 연결 수 계산
link_tcp=$(ss | grep tcp | wc -l)

# User log: who 결과로 현재 로그인한 사용자 수 계산
user_cnt=$(who | wc -l)

# Network: hostname -I로 IPv4 주소, ip link show로 MAC 주소 수집
net_ip=$(hostname -I)
net_mac=$(ip link show | grep "link/ether" | awk '{print $2}')

# Sudo: journalctl _COMM=sudo 로그에서 sudo 실행 횟수 계산
sudo_cnt=$(journalctl _COMM=sudo | grep COMMAND | wc -l)

# ===== 정보 출력 =====
printf "	#Architecture : $arc \n"
printf "	#CPU physical : $py_cpu\n"
printf "	#vCPU : $vr_cpu\n"
printf "	#Memory Usage : %s\n" "$mem_use"
printf "	#Disk Usage : %s (%.0f%%)\n" "$a_disk" "$per_disk"
printf "	#CPU load : %s\n" "$per_cpu"
printf "	#Last boot : $boot_time\n"
printf "	#LVM use : $lvm_use\n"
printf "	#Connections TCP : $link_tcp ESTABLISHED\n"
printf "	#User log : $user_cnt\n"
printf "	#Network : IP $net_ip($net_mac)\n"
printf "	#Sudo : $sudo_cnt cmd\n"
