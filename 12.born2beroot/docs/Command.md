# Command

## 기본 명령어

```shell
# 프로그램 목록 확인
sudo systemctl status
# <PROGRAM>에 대한 정보 확인 (작동 여부)
sudo service <PROGRAM> status
# <PROGRAM>에 대한 정보 확인
dpkg -l <PROGRAM>

# HOSTNAME
# HOSTNAME을 <HOSTNAME>으로 변경
sudo hostnamectl set-hostname <HOSTNAME>

# USER & GROUP
# 새로운 <USER> 생성 (-m Home 디렉토리도 생성)
sudo useradd -m <USER>
# <USER> 제거
sudo userdel <USER>
# 새로운 <GROUP> 생성
sudo addgroup <GROUP>
# <GROUP> 제거
sudo groupdel <GROUP>
# <GROUP>에 <USER> 추가 (-g 그룹1 변경)(-G 그룹2 변경)(-aG 그룹2에서부터 추가)
sudo usermod -aG <GROUP> <USER>

# PASSWORD
# PASSWORD 규칙 설정
sudo vi /etc/login.defs
sudo vi /etc/pam.d/common-password
# PASSWORD 규칙 확인
sudo chage -l <username>
# PASSWORD 변경 (root 변경시에는 <USER> 부분 공백)
sudo passwd <USER>

# SUDO
# sudo 설정
visudo
# 이전 명령을 수도로 실행
sudo !!
```

## UFW 명령어

```shell
# ufw 활성화
sudo ufw enable
# ufw 상태 확인
sudo ufw status
# <PORT NUMBER> 포트 허용
sudo ufw allow <PORT NUMBER>
# ufw 상태 확인 (번호 부여)
sudo ufw status numbered
# 번호에 따라서 <NUMBER>에 해당하는 포트 제거
sudo ufw delete <NUMBER>
```

## SSH 명령어

```shell
# <PORT>를 통해 접속
ssh <USERNAME>@<HOST IP> -p <PORT>
# ssh 설정
sudo vi /etc/ssh/sshd_config

# Key Pair 생성
ssh-keygen -t rsa
# 키 확인
cd ~/.ssh/
# 권한 수정
chmod 700 ~/.ssh
chmod 644 ~/.ssh/id_rsa.pub
chmod 644 ~/.ssh/known_hosts

# authorized_keys 파일 생성하고 id_rsa.pub 내용을 입력
vi ~/.ssh/authorized_keys
# 권한 수정
chmod 644 ~/.ssh/authorized_keys
```

## CRON 명령어

```shell
# 작업을 등록, 수정
crontab -e
# 설정된 내용들을 출력
crontab -l
# 설정된 내용 삭제
crontab -r

# cron 완전 종료
systemctl disable cron
# cron 시작
systemctl enable cron
```

## BONUS 명령어

```shell
# LIGHTTPD
# lighttpd 설정 보기
cat /etc/lighttpd/lighttpd.conf
# lighttpd fastcgi 설정 파일 보기
cat /etc/lighttpd/conf-available/15-fastcgi-php.conf

# PHP
# php-fpm 설정 파일 보기
cat /etc/php/7.4/fpm/php.ini


# MariaDB
# mariadb 진입
sudo mysql -u root -p
# DB 확인
SHOW DATABASES;

# WORDPRESS
# Wordpress와 DB 연동 (인증 키 : https://api.wordpress.org/secret-key/1.1/salt/)
vi /var/www/html/wordpress/wp-config.php

#SEND MAIL
# 메일 발송 시작
telnet localhost 25
# 메일 서버에 연결
helo localhost
# 발신자
mail from: seojulee@localhost
# 수신자
rcpt to: wmo@student.42seoul.kr
# 메일 시작
data
# 메일 제목
subject: hi
# ~ 메일 내용 작성
# 메일 본문 종료
.
# 메일 발송 및 종료
quit

# 메일 로그 확인
cat /var/log/mail.log
```
