# NetPractice

## 개요

- NetPractice는 작은 가상 네트워크에서 IP 주소, subnet mask, routing table을 채워 통신이 가능하게 만드는 네트워크 문제 풀이 과제로, 제한 시간 안에 네트워크 설정 문제를 풀고 풀이 근거를 설명하는 구조다.

## 과제 요구사항

- 브라우저 기반 training interface에서 총 10개의 레벨을 완료한다.
- 각 레벨의 비정상 네트워크 다이어그램에서 수정 가능한 IP, mask, route, gateway 값을 올바르게 채운다.
- `Check again`으로 목표 통신이 성공하는지 확인하고, 완료한 레벨은 `Get my config`로 설정 파일을 export한다.
- 레벨별 설정 파일을 제출 대상으로 관리한다.
- 평가 중에는 제한 시간 안에 랜덤 레벨을 풀어야 하며, 외부 도구 사용은 제한되고 단순 계산기 정도만 허용된다.

## 평가 방식과 제출물

- 일반 학습 모드에서는 intranet login을 입력하고 1~10 레벨을 순서대로 진행한다.
- 평가 모드에서는 login을 비워 둔 상태로 시작하며, 6~10 레벨 중 3개가 랜덤으로 출제되고 15분 안에 해결해야 한다.
- 평가는 결과만 맞히는 것이 아니라, 왜 같은 네트워크인지, 왜 해당 gateway를 사용해야 하는지, route의 목적지 범위를 어떻게 계산했는지 설명할 수 있어야 한다.
- 제출 파일은 `Get my config`로 export한 레벨별 JSON 설정 파일이며, 현재 폴더에서는 `json/level1.json`부터 `json/level10.json`까지 보관되어 있다.

## 개념 정리

### Network, Internet, Packet

- Network는 두 대 이상의 장치가 연결되어 데이터를 주고받을 수 있는 통신 구조다.
- Internet은 TCP/IP를 기반으로 여러 네트워크가 연결된 더 큰 네트워크이며, NetPractice에서는 외부망 역할을 하는 노드로 등장한다.
- Packet은 데이터를 네트워크로 전송하기 위해 나눈 단위이고, 문제 풀이에서는 이 packet이 목표 장치까지 도달할 수 있는 경로를 구성해야 한다.

### TCP/IP와 계층 모델

- TCP/IP는 인터넷 통신의 기반이 되는 프로토콜 묶음이며, IP는 주소 기반 전달을 담당하고 TCP는 연결과 신뢰성 있는 전송을 담당한다.
- NetPractice의 중심은 TCP 연결 과정이 아니라 IP 주소와 routing 판단이므로, 주로 네트워크 계층 관점에서 문제를 풀게 된다.
- OSI 7 Layer와 TCP/IP 4 Layer는 통신 과정을 계층으로 나누어 이해하기 위한 모델이며, 이 과제에서는 IP, router, gateway가 어느 계층의 문제인지 구분하는 데 도움이 된다.

### IPv4, Subnet Mask, CIDR

- IPv4 주소는 32bit 주소를 8bit씩 나누어 10진수 네 개로 표현한 값이다.
- Subnet mask는 IP 주소에서 network 영역과 host 영역을 나누는 기준이다.
- CIDR prefix는 `/24`, `/30`처럼 왼쪽에서부터 몇 bit를 network 영역으로 사용할지 나타내는 표기다.
- 두 IP가 같은 네트워크에 속하는지는 각 IP에 같은 mask를 적용했을 때 network 주소가 같은지로 판단한다.

### Network Address, Broadcast Address, Host Range

- Network address는 host bit가 모두 0인 주소로, 해당 네트워크 자체를 가리킨다.
- Broadcast address는 host bit가 모두 1인 주소로, 해당 네트워크의 모든 host를 대상으로 하는 주소다.
- 일반 host나 router interface에는 network address와 broadcast address를 사용할 수 없으므로, 실제 입력 가능한 값은 그 사이의 host range에서 골라야 한다.
- 같은 네트워크 안에서는 각 interface의 host 주소가 서로 달라야 한다.

### Public IP와 Private IP

- Public IP는 외부 인터넷에서 식별 가능한 주소이고, private IP는 내부망에서 사용하기 위해 예약된 주소 대역이다.
- 대표적인 private IP 대역은 `10.0.0.0/8`, `172.16.0.0/12`, `192.168.0.0/16`이다.
- NetPractice의 internet 노드는 private subnet으로 향하는 경로를 허용하지 않으므로, internet을 거치는 문제에서는 public/private 범위를 함께 확인해야 한다.

### Routing Table, Default Route, Gateway

- Routing table은 목적지 네트워크와 다음 hop을 기준으로 packet을 어디로 보낼지 결정하는 표다.
- Route의 destination은 최종 목적지가 속한 네트워크 범위이고, gateway는 그 목적지로 가기 위해 먼저 전달할 다음 장치의 IP다.
- `default` 또는 `0.0.0.0/0`은 더 구체적인 route가 없을 때 사용하는 기본 경로다.
- Gateway로 지정한 IP는 현재 장치가 직접 도달 가능한 네트워크 안에 있어야 한다.

### Switch, Router, Gateway, Internet

- Switch는 같은 네트워크 안의 장치들을 연결하는 역할을 하며, routing table을 기준으로 다른 네트워크를 선택하지 않는다.
- Router는 서로 다른 네트워크를 연결하고, 각 interface는 연결된 네트워크에 맞는 IP와 mask를 가져야 한다.
- Gateway는 현재 네트워크를 벗어나 다른 네트워크로 packet을 보내기 위해 사용하는 다음 hop이다.
- Internet 노드는 외부망처럼 동작하므로, 사설 IP 대역과 연결될 때는 경로가 거부될 수 있다는 점을 고려해야 한다.

## 문제 풀이 접근

### 1. 목표 통신 방향 확인

- 먼저 레벨 상단의 목표가 어떤 장치에서 어떤 장치로 통신해야 하는지 확인한다.
- 양방향 통신이 필요한 경우, 출발지에서 목적지로 가는 경로와 목적지에서 다시 돌아오는 경로를 모두 고려한다.

### 2. 고정 필드와 수정 가능한 필드 구분

- 비활성화된 값은 문제에서 주어진 조건이므로 바꾸려고 하지 않는다.
- 수정 가능한 IP, mask, route, gateway만 후보로 두고, 고정값이 속한 네트워크 범위를 먼저 계산한다.

### 3. 같은 링크의 네트워크 범위 확정

- 같은 선이나 switch로 연결된 interface들은 같은 네트워크에 속해야 한다.
- 이미 고정된 IP와 mask가 있다면 그 값을 기준으로 network address, broadcast address, host range를 계산한다.
- 빈 IP를 채울 때는 같은 host range 안에서 중복되지 않는 주소를 선택한다.

### 4. Gateway 도달 가능성 확인

- Gateway는 최종 목적지가 아니라 다음으로 packet을 넘겨줄 장치의 IP다.
- Gateway IP는 현재 장치의 interface 중 하나와 같은 네트워크 안에 있어야 한다.
- Gateway가 같은 네트워크 안에 없으면 route가 맞아도 packet을 다음 hop으로 보낼 수 없다.

### 5. Route Destination과 Next Hop 분리

- Route destination은 "어디로 가는 packet인가"를 나타내고, gateway는 "그 packet을 누구에게 먼저 보낼 것인가"를 나타낸다.
- 특정 네트워크로 가는 route와 모든 목적지를 처리하는 default route를 구분한다.
- 다중 router 문제가 나오면 각 router가 목적지 방향과 되돌아오는 방향의 route를 모두 알고 있는지 확인한다.

### 6. 로그로 실패 지점 역추적

- `Check again`의 로그는 packet이 어느 장치에서 멈췄는지 보여준다.
- `invalid IP`, `invalid netmask`, `destination does not match any route`, `route match but no interface for gateway` 같은 메시지를 기준으로 IP 범위 문제인지, mask 문제인지, gateway 문제인지 분리한다.
- 실패한 장치만 고치기보다, 그 장치가 속한 링크와 다음 hop까지 함께 다시 계산한다.

## 폴더 구조

```text
.
├── index.html
├── level1.html ~ level10.html
├── end.html
├── css/
├── js/
│   ├── intro.js
│   ├── show.js
│   ├── sim.js
│   └── level1.js ~ level10.js
├── json/
│   └── level1.json ~ level10.json
└── img/
```

- `index.html`: login 입력과 학습/평가 모드 진입 화면
- `level*.html`: 레벨별 실습 화면
- `js/level*.js`: 각 레벨의 장치, link, interface, route, 목표 조건 데이터
- `js/sim.js`: IP, mask, route, gateway를 검증하고 packet 경로를 시뮬레이션하는 로직
- `json/level*.json`: `Get my config`로 export한 레벨별 설정 파일
- `css`, `img`: 실습 인터페이스의 화면 리소스

## 실습 인터페이스 실행

NetPractice는 별도 컴파일 과정 없이 정적 HTML 파일을 브라우저에서 열어 진행한다.

```powershell
cd 42.NetPractice
Start-Process .\index.html
```

- 학습 모드에서는 login을 입력하고 `Start`를 눌러 1레벨부터 진행한다.
- 평가 모드를 확인하려면 login을 비워 둔 상태로 시작한다.
- 레벨을 통과하면 다음 레벨로 이동하기 전에 `Get my config`로 설정 파일을 export한다.

## 참고 자료

- [NetPractice level 1~10](https://woongtech.tistory.com/entry/42SEOUL-Netpractice)
