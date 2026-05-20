# 01 - libft

## 개요

- C 표준 라이브러리의 일부 함수와 연결 리스트 유틸리티를 직접 구현해 `libft.a` 정적 라이브러리로 묶는 과제였다.
- 문자열, 메모리, 문자 판별, 동적 할당, 파일 디스크립터 출력처럼 이후 C 과제에서 계속 재사용할 기본 도구를 만드는 목적이다.
- 기존 함수의 동작을 흉내 내는 데서 끝나지 않고, 실패 처리와 메모리 소유권을 직접 정리하는것이 중요한 포인트였다.

## 과제 요구사항 요약

- `ft_isalpha`, `ft_isdigit`, `ft_strlen`, `ft_memset`, `ft_memcpy`, `ft_memmove`, `ft_strncmp`처럼 libc 계열 함수를 재구현한다.
- `ft_substr`, `ft_strjoin`, `ft_strtrim`, `ft_split`, `ft_itoa`, `ft_strmapi`처럼 새 문자열을 할당해 반환하는 보조 함수를 구현한다.
- `ft_putchar_fd`, `ft_putstr_fd`, `ft_putendl_fd`, `ft_putnbr_fd`는 지정된 파일 디스크립터로 출력한다.
- 보너스 파트에서는 `t_list` 단일 연결 리스트의 생성, 추가, 삭제, 순회, 매핑 함수를 구현한다.
- `Makefile`은 `all`, `bonus`, `clean`, `fclean`, `re` 타겟을 제공하고 결과물은 `libft.a`다.

## 메모

### size_t

- `sizeof`의 결과를 표현하는 부호 없는 정수 타입
- 메모리 크기나 배열 길이처럼 음수가 될 수 없는 값을 나타낼 때 사용
- 실제 기반 타입은 플랫폼/컴파일러에 따라 다름
  - 32비트 환경에서는 보통 `unsigned int`
  - 64비트 Linux/macOS 계열에서는 보통 `unsigned long`
  - 64비트 Windows 계열에서는 `unsigned __int64` 또는 `unsigned long long` 계열

### int c

- 문자 처리 함수가 `int c`를 받는 이유는 `unsigned char`로 표현 가능한 문자 값 전체와 `EOF`를 함께 표현하기 위함이다.
- `char`는 signed 여부가 환경마다 달라 음수로 해석될 수 있으므로, 표준 라이브러리는 문자 값을 `int`로 받아 `unsigned char` 범위의 값과 `EOF`를 구분할 수 있게 한다.

### mem 계열과 unsigned char

- mem 계열 함수는 타입 정보를 몰라 `void *`와 길이 `n`만 받기 때문에,
  `int *`(4byte), `long *`(4~8byte)처럼 특정 타입 크기 단위로 움직일 수 없고, 최소 주소 지정 단위인 byte 단위로 접근해야 함.

- C에서 `char` 계열은 1byte가 보장된다.
  - 일반적인 Linux/macOS/Windows에서는 `CHAR_BIT==8`이므로.

- 메모리는 부호가 없기 때문에 `unsigned char`는 각 byte 값을 `0~255` 범위로 안정적으로 해석하기 때문에 가장 적합하다.

### memcpy와 memmove

- `memcpy`와 `memmove`의 차이는 원본과 대상 영역이 겹칠 때 드러난다.
- `memcpy`는 겹치지 않는 메모리 영역을 빠르게 복사하는 함수이고, `dst`와 `src` 범위가 겹치면 동작이 정의되지 않는다.
- `memmove`는 같은 배열이나 버퍼 안에서 복사 범위가 겹치는 경우까지 고려해 안전하게 복사한다.

### Makefile 컴파일 옵션

- `cc -c`는 소스 파일을 컴파일해 오브젝트 파일(`.o`)까지만 만들고 링크 단계는 수행하지 않는 옵션이다.
- `ar -r`은 오브젝트 파일을 아카이브에 추가하거나 같은 이름의 기존 멤버를 교체한다.
- `ar -c`는 아카이브가 없을 때 새로 만들며, 생성 경고를 억제한다.
- `ar -s`는 아카이브 안의 오브젝트 심볼 인덱스를 만들어 정적 라이브러리 링크에 사용할 수 있게 한다.
- Makefile에서는 `cc -c`로 오브젝트를 만들고 `ar -rcs`로 `libft.a`를 생성하면서, 정적 라이브러리와 심볼 인덱스의 역할을 정리했다.

### Dangling Pointer

- 이미 해제된 메모리 주소를 포인터가 계속 들고 있는 상태
- 잘못된 값 참조나 프로그램 오류를 일으킬 수 있음
- 해제한 포인터를 다시 접근하지 않도록 흐름을 끊고, `NULL`로 갱신하는 방식으로 방지할 수 있다.

```c
free(ptr);
ptr = NULL;
```

## 폴더 구조

```text
.
├── ft_*.c
├── libft.h
└── Makefile
```

- `ft_*.c`: 함수별 구현 파일
- `libft.h`: 함수 원형, `t_list` 구조체, 필요한 헤더 선언
- `Makefile`: 정적 라이브러리 생성과 정리 타겟

## 빌드 및 실행

### 빌드

```bash
make
make bonus
```

- `make`는 필수 함수 기반의 `libft.a`를 생성한다.
- `make bonus`는 리스트 함수까지 포함해 라이브러리를 생성한다.

### 실행

```bash
cc main.c -L. -lft
./a.out
```

- 직접 실행 파일을 제출하는 과제가 아니라 라이브러리를 생성하는 과제다.
- 별도 테스트 `main.c`에서 `libft.a`를 링크해 함수 동작을 확인한다.
