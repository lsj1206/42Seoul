# Philosophers

## 개요

- 식사하는 철학자 문제를 통해 공유 자원 동기화와 스레드 안전성을 다루는 동시성 과제로, 각 철학자가 `time_to_die` 안에 계속 식사할 수 있도록 thread 실행 순서와 공유 fork 접근을 동기화해, 가능한 한 철학자가 죽지 않게 만드는 것이다.
- 이 과정에서 공유 fork를 동시에 잡으려다 발생하는 `deadlock`, 특정 철학자가 계속 식사 기회를 얻지 못하는 `starvation`, thread 실행 타이밍에 따라 죽음 판정이나 식사 기회가 달라지는 `race condition`을 제어하는 것이 핵심이다.

## 과제 요구사항

### Mandatory

- 프로그램은 4개의 필수인자와 1개의 선택인자를 받는다.
  - `number_of_philosophers`: 철학자 수이자 fork 수와 같다.
  - `time_to_die` : 철학자가 마지막 식사 후 이 시간 이상 식사하지 못하면 죽는다.
  - `time_to_eat` : 철학자가 식사하는 데 걸리는 시간
  - `time_to_sleep` : 철학자가 자는 데 걸리는 시간
  - `number_of_times_each_philosopher_must_eat` : 선택 인자이며, 모든 철학자가 이 횟수만큼 식사하면 시뮬레이션을 종료한다.
- 각 철학자는 독립적인 thread로 실행되며, 식사하려면 양쪽 fork를 모두 잡아야 한다.
- fork는 인접한 철학자들이 공유하는 자원이므로, 동시에 두 철학자가 같은 fork를 잡을 수 없어야 한다.
- thread 실행 순서와 fork 접근을 조정해 철학자가 `time_to_die` 안에 다시 식사할 수 있도록 만들어야 한다.
- 철학자가 `time_to_die` 동안 식사하지 못하면 실제 사망 시점 이후 _10ms_ 이내에 death message를 출력하고 시뮬레이션을 종료한다.
- 철학자의 상태 변화는 `timestamp_in_ms X action` 형식으로 출력하며, 여러 thread의 출력 메시지가 서로 섞이면 안 된다.
- 선택 인자가 있으면 모든 철학자가 지정된 횟수만큼 식사했을 때 시뮬레이션을 종료한다.
- 공유 데이터 접근은 data race가 발생하지 않도록 동기화해야 한다.

## 개념 정리

### 공유 자원

- 공유 자원은 여러 thread가 동시에 접근할 수 있는 데이터나 외부 자원이다.
- 이 과제에서 대표적인 공유 자원은 fork, 출력 스트림, 종료 플래그, 마지막 식사 시간, 전체 식사 완료 횟수다.
- thread는 process의 code/data/heap 영역을 공유하지만, 각자의 stack을 가진다. 그래서 같은 구조체나 전역 상태를 여러 thread가 읽고 쓰면 동기화가 필요하다.

### Race Condition과 Data Race

- `race condition`은 실행 순서나 타이밍에 따라 결과가 달라지는 상황이다.
  - thread 스케줄링에 따라 fork 획득 순서, 죽음 판정 시점, 식사 기회가 달라질 수 있다는 점이 여기에 해당한다.

- `data race`는 여러 thread가 같은 공유 데이터에 동시 접근하고, 그중 하나 이상이 write를 수행하는데 적절한 동기화가 없는 경우를 말한다.
  - 금지하는 것은 이 data race이며, 마지막 식사 시간, 종료 플래그, 출력 상태처럼 공유되는 값은 mutex로 보호해야 한다.

- 즉, `data race`는 발생이 곧 문제인 반면, `race condition`은 실행 순서나 타이밍에 따라 결과가 달라질 수 있는 구조를 말한다.

### Deadlock과 Starvation

- `deadlock`은 교착 상태로, 여러 thread가 서로 상대방이 가진 자원이 풀리기만 기다려 아무도 진행하지 못하는 상태로, 아래 같은 조건으로 발생한다.
  - `mutual exclusion`: 상호 배제, 하나의 자원에 동시에 하나의 thread 또는 process만 접근할 수 있는 조건이다.
  - `hold and wait`: 점유 대기, 이미 획득한 자원을 가진 상태에서 다른 자원이 풀리기를 기다리는 조건이다.
  - `no preemption`: 비선점, 다른 thread나 process가 가진 자원을 강제로 빼앗을 수 없고, 소유자가 직접 해제할 때까지 기다려야 하는 조건이다.
  - `circular wait`: 순환 대기, 여러 thread나 process가 서로가 가진 자원을 순환 형태로 기다리는 조건이다.

- `starvation`은 기아 상태로, 스케줄링이나 자원 분배가 불공정해 특정 thread가 무기한 대기하는 상태다.

### Critical Section

- `critical section`은 동시에 실행되면 안 되는 코드 구간이다.
- fork를 집는 구간, 마지막 식사 시간 갱신, 죽음 여부 확인, 출력 한 줄을 찍는 구간이 여기에 해당한다.
- mutex나 semaphore는 critical section에 들어갈 수 있는 thread 수를 제한해 공유 상태가 깨지지 않도록 돕는다.

### Context Switching

- `context switching`은 CPU가 실행 중인 thread를 바꾸면서 현재 실행 상태를 저장하고 다른 thread의 상태를 복원하는 과정이다.
- thread 교체가 자주 발생하면 `context switching` 오버헤드가 커져, 실제 작업보다 실행 상태 저장/복원과 대기 시간에 더 많은 비용이 들어갈 수 있다.

## 문제 해결의 핵심

### Critical Section 경계 설정

- lock이 부족하면 `data race`로 인해 마지막 식사 시간 오판, 종료 상태 누락 같은 문제가 발생해 철학자가 죽게 되고, 출력 보호가 부족하면 메시지가 서로 섞일 수 있다. 반대로 lock이 너무 많으면 thread 대기와 `context switching`이 delay를 만들어 철학자가 `time_to_die` 안에 다시 식사하지 못할 수 있다.

- 따라서 fork 획득, 마지막 식사 시간 갱신, 죽음 여부 확인, 출력처럼 결과의 일관성을 깨뜨릴 수 있는 구간만 `critical section`으로 분리해야 한다.

### Deadlock과 Starvation 완화

- 모든 철학자가 같은 시점에 같은 방식으로 fork를 잡으려 하면 `circular wait`이 생길 수 있다.
- deadlock을 피하더라도 특정 철학자가 계속 fork를 얻지 못하면 `starvation`이 발생할 수 있다.
- 그래서 단순히 lock을 거는 것만으로는 부족하고, thread 시작 시점, fork 접근 타이밍, monitor의 관찰 주기를 함께 조정해야 한다.

### 시간 제약과 관찰

- `time_to_die`는 단순한 타이머가 아니라 동시성 설계가 실패했는지 드러내는 기준이다.
- monitor는 각 철학자의 마지막 식사 시간을 반복해서 확인해야 하며, death message는 실제 사망 시점 이후 _10ms_ 이내에 출력되어야 한다.
- sleep을 길게 한 번 호출하면 종료 상태 반영이 늦어질 수 있으므로, 짧게 나누어 쉬면서 종료 조건을 확인하는 방식이 필요하다.

## 내가 구현한 방식

### 구조체 역할

- `t_arg`: 철학자 수, 죽기까지의 시간, 먹는 시간, 자는 시간, 필수 식사 횟수를 저장한다.
- `t_shr`: fork 배열, 출력 mutex, 공유 상태 mutex, 시작 시간, 종료 플래그, 식사 완료 수를 저장한다.
- `t_philo`: thread id, 철학자 번호, 왼쪽/오른쪽 fork index, 마지막 식사 시간, 식사 횟수, 현재 식사 중 여부를 저장한다.

### 초기화 흐름

- `init_arg`는 인자 개수와 양수 조건을 검증하고, 시간 값과 선택 인자 `must_eat`을 저장한다.
- `init_shared`는 공유 mutex인 `mtx`, 출력 mutex인 `print`, fork mutex 배열인 `forks`를 초기화한다.
- `init_philo`는 철학자별 id, 왼쪽 fork index, 오른쪽 fork index, 식사 횟수와 마지막 식사 시간을 초기화한다.

### Fork와 출력 보호

- `forks`는 `pthread_mutex_t` 배열이며, 각 원소가 fork 하나를 의미한다.
- 철학자는 식사 전에 왼쪽 fork mutex를 lock하고, 이어서 오른쪽 fork mutex를 lock한다.
- 식사가 끝나면 오른쪽 fork, 왼쪽 fork 순서로 unlock한다.
- `print` mutex는 여러 thread의 출력이 한 줄 안에서 섞이지 않도록 보호한다.
- 죽음 이후에는 일반 상태 메시지를 출력하지 않도록 `printer`에서 종료 상태를 확인한다.

### 공유 상태 보호

- `mtx`는 마지막 식사 시간(`ate_time`), 현재 식사 중 여부(`eating`), 전체 식사 완료 수(`ate_all`) 같은 공유 상태를 보호하는 데 사용된다.
- `monitor`는 모든 철학자를 순회하면서 마지막 식사 시간과 `time_to_die`를 비교하고, 모든 철학자의 식사 완료 여부도 확인한다.
- `is_dead`는 종료 판단과 출력 억제에 모두 쓰이는 공유 플래그다. 현재 코드에서는 `dead_handler`가 `mtx`를 잡은 monitor 흐름에서 호출되고, 동시에 `print` mutex 안에서 값을 변경한다.
- `finish_checker`는 `mtx`로 종료 상태를 확인하고, `printer`는 `print` mutex로 죽음 이후의 일반 메시지 출력을 억제한다. 따라서 `is_dead`는 종료 제어와 출력 제어가 만나는 공유 상태로 볼 수 있다.

### Deadlock 회피 방식

- 현재 코드는 모든 철학자가 왼쪽 fork를 먼저 잡고 오른쪽 fork를 잡는 구조다.
- fork 획득 순서를 철학자별로 반대로 바꾸는 방식은 사용하지 않는다.
- 대신 thread 생성 사이에 짧은 `usleep(10)`을 두고, 홀수 id 철학자는 루틴 시작 시점에 지연을 둬 동시에 모든 철학자가 fork를 잡으려는 상황을 완화한다.
- 이 방식은 실행 타이밍을 분산해 deadlock 가능성을 줄이는 접근이지만, fork 순서 자체를 바꾸는 구조와는 구분해서 이해해야 한다.

### 시간과 종료 조건

- 시간 측정은 `gettimeofday`를 이용해 millisecond 단위로 계산한다.
- `start_time`은 thread 생성 직전에 기록하고, 출력 timestamp는 현재 시간에서 `start_time`을 뺀 값이다.
- `timer`는 긴 시간 동안 한 번에 sleep하지 않고, 짧은 `usleep`을 반복하면서 종료 상태를 확인한다.
- `monitor`는 주기적으로 철학자들의 마지막 식사 시간을 확인해 `time_to_die` 이상 식사하지 못한 철학자가 있으면 죽음 메시지를 출력하고 종료 플래그를 세운다.
- 선택 인자 `must_eat`이 있으면 각 철학자가 목표 식사 횟수를 채웠을 때 `ate_all`을 증가시키고, 모든 철학자가 완료되면 시뮬레이션을 종료한다.
- 철학자가 한 명이면 잡을 수 있는 fork가 하나뿐이라 두 번째 fork를 얻을 수 없다. 현재 코드는 fork 하나를 잡은 뒤 `time_to_die`만큼 기다리는 예외 루틴으로 처리한다.

### 구현 흐름

```text
init_arg
  -> init_shared
  -> init_philo
  -> start_philo
  -> routine / monitor
  -> destroy_thread / destroy_mutex
```

- `start_philo`는 thread를 만들고 monitor loop를 실행한다.
- `routine`은 fork 잡기, 먹기, 자기, 생각하기를 반복한다.
- 종료 후에는 thread join, mutex destroy, 할당 해제를 수행한다.

## 폴더 구조

```text
.
└── philo/
    ├── main.c
    ├── philo.c
    ├── routine.c
    ├── destroy.c
    ├── utils.c
    ├── philo.h
    └── Makefile
```

- `philo/main.c`: 인자 검증, 공유 자원 초기화, 철학자 구조체 초기화
- `philo/philo.c`: 출력, monitor, thread 시작 흐름
- `philo/routine.c`: 철학자의 반복 행동과 fork 획득/해제
- `philo/utils.c`: 시간 측정, sleep loop, 숫자 변환
- `philo/destroy.c`: thread join, mutex destroy, 메모리 해제
- `philo/philo.h`: 구조체, 메시지 상수, 함수 원형
- `philo/Makefile`: `-pthread` 기반 빌드 규칙

## 빌드 및 실행

### 빌드

```bash
cd philo
make
```

- 결과물은 `philo` 실행 파일이다.
- Makefile은 `-pthread` 옵션을 사용해 pthread 기반 thread/mutex 코드를 빌드한다.

### 실행

```bash

./philo 5 800 200 200
./philo 5 800 200 200 7
./philo 1 800 200 200
./philo 4 310 200 100
```

- 첫 번째 예시는 기본 시뮬레이션이다.
- 두 번째 예시는 모든 철학자가 7번 식사하면 종료되는 케이스다.
- 세 번째 예시는 철학자가 한 명뿐인 예외 케이스다.
- 네 번째 예시는 시간 조건에 따라 죽음이 발생할 수 있는 케이스다.

## 참고 자료

- [철학자에게 밥을 먹이자](https://techdebt.tistory.com/32)
