# minitalk

## 개요

- `minitalk`는 UNIX signal을 이용해 클라이언트 프로세스가 서버 프로세스에 문자열을 전달하는 통신 과제다.
- 네트워크 소켓이나 파일 공유 없이 `SIGUSR1`, `SIGUSR2` 두 신호만으로 문자를 bit 단위로 직렬화해 보낸다.
- PID, `kill`, `sigaction`, bit 연산, ACK 흐름, 비동기 signal handler의 제약을 함께 다룬다.

## 과제 요구사항

### Mandatory

- `server`와 `client` 실행 파일을 생성한다.
- 서버는 실행되면 자신의 PID를 출력하고, 클라이언트가 보낸 문자열을 수신해 출력한다.
- 클라이언트는 서버 PID와 전송할 문자열을 인자로 받는다.
- 통신에는 `SIGUSR1`, `SIGUSR2` 두 signal만 사용한다.
- 문자열은 문자 하나를 8bit로 나누고, 각 bit를 signal 하나로 표현해 전송한다.
- 서버는 재시작 없이 여러 번의 클라이언트 요청을 이어서 처리할 수 있어야 한다.
- 서버는 수신한 문자열을 가능한 빠르게 출력해야 한다.

### Bonus

- 서버가 signal을 정상적으로 수신했음을 클라이언트에게 다시 알려주는 ACK 흐름을 구현할 수 있다.
- Unicode 문자를 지원할 수 있다.
- 현재 코드에서는 mandatory 파일과 bonus 파일이 거의 같은 ACK 흐름을 사용한다. `make bonus`는 별도 bonus source set을 사용하지만, 기본 구현에도 bit 단위 ACK 대기 구조가 포함되어 있다.

## 메모

### Signal 기반 통신

- 클라이언트는 `kill(server_pid, signal)`로 서버에 signal을 보낸다.
- 현재 코드에서는 `SIGUSR1`을 bit `1`, `SIGUSR2`를 bit `0`에 대응시키기 위해 `ONE`, `ZERO` 매크로를 사용한다.
- signal 자체에는 문자 데이터가 실리지 않으므로, 클라이언트가 각 문자를 8bit로 나눠 순서대로 보내고 서버가 이를 다시 `unsigned char` 버퍼에 누적한다.
- 문자열의 끝은 `\0` 문자까지 전송하는 방식으로 구분한다. 서버는 null byte를 받으면 메시지 하나가 끝났다고 판단한다.

### sigaction과 SA_SIGINFO

- `sigaction`은 signal이 들어왔을 때 실행할 handler를 등록하는 함수다.
- 단순 handler는 signal 번호만 받을 수 있지만, `SA_SIGINFO`를 사용하면 `sa_sigaction` 형태의 handler에서 `siginfo_t`를 함께 받을 수 있다.
- 현재 서버는 `info->si_pid`로 signal을 보낸 클라이언트 PID를 확인하고, 같은 PID로 ACK signal을 돌려보낸다.
- 서버는 메시지 수신 중 첫 클라이언트 PID를 저장하고, 해당 메시지가 끝날 때까지 다른 PID에서 온 signal은 무시한다.

### ACK와 전송 흐름

- 일반 UNIX signal은 같은 종류의 pending signal을 개별 이벤트로 모두 queue하지 않을 수 있어, 전송이 너무 빠르면 bit가 누락되고 8bit 단위의 문자 조립이 어긋날 수 있다.
- 이를 줄이기 위해 현재 구현은 `pause()`를 이용한 ACK 기반 stop-and-wait 방식을 사용한다.
- 클라이언트는 bit 하나를 `kill()`로 보낸 뒤 `pause()`로 서버의 ACK를 기다리고, ACK를 받기 전에는 다음 bit를 보내지 않는다.
- 서버는 bit를 처리한 뒤 메시지가 진행 중이면 `SIGUSR1`을 ACK로 보내고, null byte를 받아 메시지가 끝나면 `SIGUSR2`를 보내 종료를 알린다.
- 이 방식은 signal 자체를 완전한 데이터 queue로 바꾸지는 못하지만, `전송 -> 대기 -> 처리 확인 -> 다음 전송` 순서를 강제해 문자열이 깨질 가능성을 줄인다.

### UTF-8 전송

- UTF-8은 한 문자가 1byte일 수도 있고 여러 byte일 수도 있다.
- 현재 구현은 문자를 Unicode code point 단위로 해석하지 않고, 문자열 메모리에 들어 있는 byte를 순서대로 전송한다.
- 그래서 한글처럼 여러 byte로 이루어진 문자도 byte 순서가 유지되면, UTF-8을 사용하는 터미널에서 원래 문자처럼 출력될 수 있다.
- 즉 Unicode 지원은 별도의 문자 파싱을 추가한 결과라기보다, UTF-8 byte stream을 그대로 보존해 전송한 결과에 가깝다.

### PID와 입력 검증

- macOS의 PID 범위는 `100`부터 `99998`까지다.
- 클라이언트는 인자가 정확히 2개인지, 메시지가 비어 있지 않은지, 서버 PID 인자가 숫자로만 구성되어 있는지 확인한다.
- `ft_atoi`는 변환 중 overflow가 발생하면 종료하도록 작성되어 있다.
- 입력 검증을 먼저 끝내면 signal 전송 로직은 "유효한 PID에 유효한 문자열을 보낸다"는 전제만 다루면 된다.

## minitalk 과제의 가치

`minitalk`의 핵심은 signal을 데이터 전송 수단처럼 사용하는 데 있다. signal은 원래 문자열이나 구조체 같은 payload를 직접 담아 보내는 통신 채널이 아니라, 특정 이벤트가 발생했음을 프로세스에 알리는 비동기 알림에 가깝다.

따라서 이 과제에서는 `SIGUSR1`, `SIGUSR2` 두 가지 상태만으로 데이터를 표현하기 위해 문자를 bit 단위로 쪼개고, 서버와 클라이언트가 같은 순서와 속도로 해석할 수 있는 작은 protocol을 직접 설계해야 한다. 단순히 문자열을 출력하는 문제가 아니라, 제한된 통신 수단 위에서 직렬화, 동기화, ACK, PID 기반 응답 흐름을 구성하는 경험에 가깝다.

## 폴더 구조

```text
.
├── client.c
├── client_bonus.c
├── server.c
├── server_bonus.c
├── utils.c
├── utils_bonus.c
├── minitalk.h
├── minitalk_bonus.h
├── ft_printf/
└── Makefile
```

- `server.c`, `client.c`: 기본 서버/클라이언트 구현
- `server_bonus.c`, `client_bonus.c`: bonus 빌드에 사용되는 서버/클라이언트 구현
- `utils.c`, `utils_bonus.c`: 입력 검증과 문자열/숫자 변환 보조 함수
- `minitalk.h`, `minitalk_bonus.h`: signal 매크로, 공유 구조체, 함수 원형
- `ft_printf/`: 출력에 사용하는 `ft_printf` 구현
- `Makefile`: 기본 빌드와 bonus 빌드 규칙

## 빌드 및 실행

### 빌드

```bash
make
make bonus
```

- `make`는 기본 소스로 `server`, `client` 실행 파일을 생성한다.
- `make bonus`는 bonus 소스로 같은 이름의 `server`, `client` 실행 파일을 생성한다.

### 실행

```bash
./server
./client <server_pid> "message"
```

- 먼저 서버를 실행해 출력된 PID를 확인한다.
- 다른 터미널에서 클라이언트를 실행하고, 서버 PID와 보낼 문자열을 인자로 전달한다.
- UTF-8 터미널 환경에서는 다음처럼 여러 byte 문자도 전송 결과를 확인할 수 있다.

```bash
./client <server_pid> "한글"
```

## 참고 자료

- [Signal](https://www.joinc.co.kr/w/Site/system_programing/Book_LSP/ch06_Signal)
- [Minitalk](https://velog.io/@jay13jeong/Minitalk-UNIX-signals)
