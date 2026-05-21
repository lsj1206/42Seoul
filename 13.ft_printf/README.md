# ft_printf

## 개요

- C 표준 함수 `printf`의 일부 서식 기능을 직접 구현해 `libftprintf.a` 정적 라이브러리로 만드는 과제다.
- 가변 인자 처리, 서식 문자열 파싱, 타입별 출력, 반환값 누적을 직접 구현하며 출력 함수의 내부 구조를 익히는 것이 목적이다.

## 과제 요구사항

### Mandatory

- `libftprintf.a` 정적 라이브러리를 생성한다.
- `int ft_printf(const char *, ...)` 형태의 가변 인자 함수를 구현한다.
- `va_list`, `va_start`, `va_arg`, `va_end`를 사용해 고정 인자 뒤의 가변 인자를 순서대로 읽는다.
- `%c`, `%s`, `%p`, `%d`, `%i`, `%u`, `%x`, `%X`, `%%` 지정자를 처리한다.
- 출력은 `write` 기반으로 수행하고, 함수는 실제 출력한 문자 수를 반환해야 한다.
- 정수 출력은 부호 있는 10진수, 부호 없는 10진수, 16진수, 포인터 주소처럼 타입별 변환 규칙을 나누어 처리한다.
- 표준 `printf`와 비교했을 때 기본 지정자에 대해 같은 출력 결과를 내야 한다.

### Bonus

- `-`, `0`, `.precision`, `#`, space, `+` 같은 플래그, 폭, 정밀도 개념을 추가로 구현한다.
- `-`는 출력 폭보다 실제 출력이 짧을 때 왼쪽 정렬에 사용된다.
- `0`은 오른쪽 정렬 상황에서 공백 대신 `0`으로 채우는 플래그이며, 정수 서식에서 precision이나 `-` 플래그가 있으면 무시된다.
- `.precision`은 출력할 최소 자릿수나 문자열 출력 길이에 영향을 준다.
- `#`은 16진수 같은 진법 출력에서 접두사를 붙이는 플래그로 이해했다.
- space와 `+`는 양수/음수의 부호 표현 방식에 영향을 주며, `+`가 있으면 space는 무시된다.

## 메모

### 가변 인자

- 가변 인자는 `<stdarg.h>`의 `va_list`, `va_start`, `va_arg`, `va_end`로 접근하며, 고정 인자 뒤의 메모리 위치를 순서대로 읽는 방식으로 이해했다.
- `char`, `short`, `float` 계열은 default argument promotion 때문에 `int` 또는 `double`로 승격될 수 있어 `va_arg` 타입을 서식 지정자와 정확히 맞춰야 한다.

> default argument promotion: 가변 인자처럼 인자 타입 정보가 함수 원형에 명확히 남지 않는 호출에서는 작은 정수 타입(`char`, `short`)은 `int`로, `float`은 `double`로 승격되어 전달된다. 따라서 `%c`도 `va_arg(ap, int)`로 읽고, 서식 지정자에 맞는 승격 후 타입을 사용해야 한다.

### 서식 지정자

- `%c`, `%s`, `%d`, `%i`, `%u`, `%x`, `%X`, `%p`, `%%`는 출력 대상 타입과 변환 규칙이 다르므로, `specifier_check` 분기 함수로 처리했다.
- `%p`는 주소값을 16진수 문자열로 표현하는 흐름이라, `unsigned long` 계열로 변환해 다루는 것이 안전하다.
- `%s`에서 width는 전체 출력 칸을 맞추는 역할을 하고, precision은 출력할 문자열 길이를 제한하는 역할을 한다.
- 음수 정수, `INT_MIN`, 0, 빈 문자열, `NULL` 문자열 같은 경계값은 출력 내용에 반환 카운트까지 재현해야 한다.

## 폴더 구조

```text
.
├── ft_printf
│   ├── ft_printf.c
│   ├── ft_printf_specifier.c
│   ├── ft_printf_utils.c
│   ├── ft_printf.h
│   └── Makefile
├── ftbonus
│   ├── ft_printf_bonus.c
│   ├── ft_printf_option_bonus.c
│   ├── ft_printf_specifier_1_bonus.c
│   ├── ft_printf_specifier_2_bonus.c
│   ├── ft_printf_utils_1_bonus.c
│   ├── ft_printf_utils_2_bonus.c
│   ├── ft_printf_bonus.h
│   └── Makefile
├── README.md
└── test.c
```

- `ft_printf/`: mandatory 구현 파일과 Makefile
- `ftbonus/`: bonus 구현 파일과 Makefile
- `test.c`: `printf` 비교 테스트 파일

## 빌드 및 실행

### mandatory 빌드

```bash
make -C ft_printf
```

- 결과물은 `ft_printf/libftprintf.a`다.

### bonus 빌드

```bash
make -C ftbonus
```

- 결과물은 `ftbonus/libftprintf.a`다.

### mandatory 테스트 실행

```bash
cc test.c -Ift_printf -Lft_printf -lftprintf
./a.out
```

### bonus 테스트 실행

```bash
cc test.c -Iftbonus -Lftbonus -lftprintf
./a.out
```

- 직접 실행 파일을 만드는 과제가 아니라 라이브러리를 만든다.
- 별도 테스트 파일에서 `ft_printf`를 호출해 표준 `printf`와 출력 결과를 비교한다.

## 참고 자료

- [ft_printf 규칙표](https://80000coding.oopy.io/3e12395e-150d-4a58-9288-6a4e417a60c1#3e12395e-150d-4a58-9288-6a4e417a60c1)
- [printf와 scanf](https://eatchangmyeong.github.io/2022/07/08/all-about-printf-and-scanf.html)
- [서식지정자란?](https://love-every-moment.tistory.com/49)
