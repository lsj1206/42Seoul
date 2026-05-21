# LaPiscine

## 개요

- LaPiscine은 42Seoul 본 과정을 진행하기 이전에 하는 한 달간의 테스트 과정으로, 42의 교육 방식과 C 언어, UNIX 환경에 익숙해지는 것을 목표로 한다.
- UNIX 명령어 사용, 파일 권한, 표준 출력, 포인터, 문자열, 배열, 재귀, 동적 할당처럼 이후 과제의 바탕이 되는 내용이다.

## 과제 요구사항 요약

| 구간        | 주요 내용                                                                |
| ----------- | ------------------------------------------------------------------------ |
| Shell 00~01 | 파일 생성/수정, 권한, `find`, `grep`, 파이프라인, 압축, Git 제출 흐름    |
| C 00~04     | 출력 함수, 반복문, 포인터 전달, 문자열 순회, 정수 출력, 기초 배열 처리   |
| C 05~07     | 재귀, 수학 함수, 문자열 복사/비교/검색, 동적 할당과 배열 생성            |
| C 08~13     | 헤더, 매크로, 구조체, 리스트, 함수 포인터, 고급 문자열 처리              |
| Rush        | 제한된 시간 안에 팀 단위로 문제를 나누고 인터페이스를 맞추는 소규모 구현 |

## 과제별 요구/제약사항 및 내용

현재 저장소의 실제 파일 기준으로 정리했다. C 과제는 Norminette와 `gcc -Wall -Wextra -Werror` 기준을 통과해야 하며, Shell 과제는 `/bin/sh`로 실행 가능한 형태와 정확한 출력 형식을 맞춰야 한다.

`_Real_Subject`에는 있으나 현재 코드 파일로는 없는 항목은 `Shell01 ex00 Exam`, `Shell01 ex05 Can you create it ?`, `C02 ex12 ft_print_memory`다.

### Shell00

- ex00 `z`: `Z`만 담긴 파일을 만든다.
- ex01 `testShell00.tar`: 지정된 권한, 크기, 타임스탬프를 가진 파일을 tar로 제출한다.
- ex02 `exo2.tar`: 파일, 디렉터리, 심볼릭 링크의 권한과 시간을 subject 예시와 맞춘다.
- ex03 `klist.txt`: Kerberos 티켓 목록을 요구된 형식으로 저장한다.
- ex04 `midLS`: 숨김 파일을 제외하고 생성일 기준 목록을 쉼표와 디렉터리 표시(`/`)까지 맞춰 출력하는 명령을 적는다.
- ex05 `git_commit.sh`: 현재 Git 저장소의 최근 5개 commit hash를 출력한다.
- ex06 `git_ignore.sh`: Git이 무시하는 파일 목록을 출력한다.
- ex07 `b`: 주어진 `a`와 비교했을 때 subject의 patch 결과가 나오도록 파일 `b`를 만든다.
- ex08 `clean`: `~`로 끝나거나 `#...#` 형태인 파일을 찾아 표시하고 삭제하는 단일 명령을 작성한다.
- ex09 `ft_magic`: 42번째 바이트에 `42`가 있는 파일을 탐지하는 magic file을 만든다.

### Shell01

- ex01 `print_groups.sh`: `FT_USER`가 속한 그룹들을 공백 없이 쉼표로 구분해 출력한다.
- ex02 `find_sh.sh`: 현재 디렉터리 아래의 `.sh` 파일을 찾고 확장자를 제외한 이름만 출력한다.
- ex03 `count_files.sh`: 현재 디렉터리와 하위 항목의 일반 파일 및 디렉터리 개수를 센다.
- ex04 `MAC.sh`: 시스템의 MAC 주소를 한 줄에 하나씩 출력한다.
- ex06 `skip.sh`: `ls -l` 출력에서 첫 줄부터 한 줄씩 건너뛰어 보여준다.
- ex07 `r_dwssap.sh`: `/etc/passwd`에서 주석 제거, 행 필터링, login 뒤집기, 역정렬, 범위 추출, 쉼표/마침표 출력을 조합한다.
- ex08 `add_chelou.sh`: 서로 다른 기수 체계의 두 환경 변수 값을 더해 지정된 기수 문자 집합으로 출력한다.

### C00

- ex00 `ft_putchar`: 문자 하나를 `write`로 출력한다.
- ex01 `ft_print_alphabet`: `a`부터 `z`까지 한 줄로 출력한다.
- ex02 `ft_print_reverse_alphabet`: `z`부터 `a`까지 역순으로 출력한다.
- ex03 `ft_print_numbers`: `0`부터 `9`까지 출력한다.
- ex04 `ft_is_negative`: 음수는 `N`, 0 이상은 `P`를 출력한다.
- ex05 `ft_print_comb`: 서로 다른 세 숫자의 오름차순 조합을 형식에 맞춰 출력한다.
- ex06 `ft_print_comb2`: `00`부터 `99` 사이 두 수의 오름차순 조합을 출력한다.
- ex07 `ft_putnbr`: `int` 범위의 정수를 문자열로 변환해 출력한다.
- ex08 `ft_print_combn`: `0 < n < 10` 범위에서 n자리 숫자 조합을 오름차순으로 출력한다.

### C01

- ex00 `ft_ft`: 포인터가 가리키는 `int` 값을 42로 바꾼다.
- ex01 `ft_ultimate_ft`: 여러 단계 포인터를 따라가 최종 `int` 값을 42로 바꾼다.
- ex02 `ft_swap`: 두 정수 값을 포인터로 교환한다.
- ex03 `ft_div_mod`: 나눗셈의 몫과 나머지를 포인터에 저장한다.
- ex04 `ft_ultimate_div_mod`: 두 포인터 값 자체를 몫과 나머지로 갱신한다.
- ex05 `ft_putstr`: 널 종료 문자열을 `write`로 출력한다.
- ex06 `ft_strlen`: 문자열 길이를 계산해 반환한다.
- ex07 `ft_rev_int_tab`: 정수 배열을 제자리에서 뒤집는다.
- ex08 `ft_sort_int_tab`: 정수 배열을 오름차순으로 정렬한다.

### C02

- ex00 `ft_strcpy`: 원본 문자열을 목적지 버퍼에 복사한다.
- ex01 `ft_strncpy`: 최대 `n`글자까지 복사하고 남는 영역을 널로 채운다.
- ex02 `ft_str_is_alpha`: 문자열이 알파벳만 포함하는지 검사한다.
- ex03 `ft_str_is_numeric`: 문자열이 숫자만 포함하는지 검사한다.
- ex04 `ft_str_is_lowercase`: 문자열이 소문자만 포함하는지 검사한다.
- ex05 `ft_str_is_uppercase`: 문자열이 대문자만 포함하는지 검사한다.
- ex06 `ft_str_is_printable`: 문자열이 출력 가능한 문자만 포함하는지 검사한다.
- ex07 `ft_strupcase`: 문자열 안의 소문자를 대문자로 바꾼다.
- ex08 `ft_strlowcase`: 문자열 안의 대문자를 소문자로 바꾼다.
- ex09 `ft_strcapitalize`: 단어의 첫 글자만 대문자, 나머지는 소문자로 정규화한다.
- ex10 `ft_strlcpy`: `strlcpy` 동작처럼 크기를 제한해 복사하고 원본 길이를 반환한다.
- ex11 `ft_putstr_non_printable`: 출력 불가능한 문자를 `\xx` 16진수 형태로 출력한다.

### C03

- ex00 `ft_strcmp`: 두 문자열을 사전순으로 비교한다.
- ex01 `ft_strncmp`: 최대 `n`글자까지만 비교한다.
- ex02 `ft_strcat`: 문자열을 목적지 문자열 뒤에 이어 붙인다.
- ex03 `ft_strncat`: 최대 `nb`글자까지만 이어 붙인다.
- ex04 `ft_strstr`: 문자열 안에서 부분 문자열의 첫 위치를 찾는다.
- ex05 `ft_strlcat`: 버퍼 크기를 고려해 이어 붙이고 만들어지려던 전체 길이를 반환한다.

### C04

- ex00 `ft_strlen`: 문자열 길이를 반환한다.
- ex01 `ft_putstr`: 문자열을 표준 출력에 쓴다.
- ex02 `ft_putnbr`: 정수를 출력하며 `INT_MIN` 같은 경계값을 고려한다.
- ex03 `ft_atoi`: 공백, 부호, 숫자 구간을 해석해 정수로 변환한다.
- ex04 `ft_putnbr_base`: 유효한 base 문자 집합으로 정수를 출력한다.
- ex05 `ft_atoi_base`: 유효한 base 문자 집합을 기준으로 문자열을 정수로 변환한다.

### C05

- ex00 `ft_iterative_factorial`: 반복문으로 팩토리얼을 계산한다.
- ex01 `ft_recursive_factorial`: 재귀로 팩토리얼을 계산한다.
- ex02 `ft_iterative_power`: 반복문으로 거듭제곱을 계산한다.
- ex03 `ft_recursive_power`: 재귀로 거듭제곱을 계산한다.
- ex04 `ft_fibonacci`: n번째 피보나치 값을 재귀로 구한다.
- ex05 `ft_sqrt`: 정수 제곱근이 존재할 때만 그 값을 반환한다.
- ex06 `ft_is_prime`: 주어진 수가 소수인지 판별한다.
- ex07 `ft_find_next_prime`: 주어진 수 이상에서 가장 가까운 소수를 찾는다.
- ex08 `ft_ten_queens_puzzle`: 10-queen 해를 모두 출력하고 해의 개수를 반환한다.

### C06

- ex00 `ft_print_program_name`: 프로그램 이름을 출력한다.
- ex01 `ft_print_params`: 명령행 인자를 입력 순서대로 한 줄씩 출력한다.
- ex02 `ft_rev_params`: 명령행 인자를 역순으로 출력한다.
- ex03 `ft_sort_params`: 명령행 인자를 ASCII 오름차순으로 정렬해 출력한다.

### C07

- ex00 `ft_strdup`: 문자열을 새로 할당해 복제한다.
- ex01 `ft_range`: `min` 이상 `max` 미만의 정수 배열을 동적 할당한다.
- ex02 `ft_ultimate_range`: 배열 주소를 이중 포인터로 돌려주고 길이를 반환한다.
- ex03 `ft_strjoin`: 문자열 배열을 구분자와 함께 하나의 새 문자열로 합친다.
- ex04 `ft_convert_base`: 문자열 숫자를 한 base에서 다른 base로 변환한다.
- ex05 `ft_split`: 구분자 문자 집합을 기준으로 문자열을 단어 배열로 나눈다.

### C08

- ex00 `ft.h`: 기본 함수 프로토타입을 모은 헤더를 작성한다.
- ex01 `ft_boolean.h`: boolean 타입, 매크로, 출력 문자열을 정의한다.
- ex02 `ft_abs.h`: 절댓값 매크로 `ABS`를 정의한다.
- ex03 `ft_point.h`: 좌표 구조체 `t_point`를 정의한다.
- ex04 `ft_strs_to_tab`: 문자열 배열을 `t_stock_str` 구조체 배열로 변환한다.
- ex05 `ft_show_tab`: `t_stock_str` 배열의 문자열, 길이, 복사본을 출력한다.

### C09

- ex00 `libft`: `libft_creator.sh`로 `ft_putchar`, `ft_swap`, `ft_putstr`, `ft_strlen`, `ft_strcmp`를 포함한 `libft.a`를 만든다.
- ex01 `Makefile`: `srcs`, `includes` 구조에서 `libft.a`를 빌드하고 `all`, `clean`, `fclean`, `re` 규칙을 제공한다. 현재 저장소에는 이 Makefile만 보관되어 있다.
- ex02 `ft_split`: `charset`의 각 문자를 구분자로 사용해 빈 문자열 없이 문자열 배열을 만든다.

### C11

- ex00 `ft_foreach`: 정수 배열의 각 원소에 함수 포인터를 적용한다.
- ex01 `ft_map`: 정수 배열에 함수를 적용한 결과를 새 배열로 반환한다.
- ex02 `ft_any`: 문자열 배열 중 하나라도 검사 함수를 통과하면 참을 반환한다.
- ex03 `ft_count_if`: 문자열 배열에서 조건을 만족하는 항목 수를 센다.
- ex04 `ft_is_sort`: 비교 함수 기준으로 배열이 정렬되어 있는지 판별한다.
- ex05 `do-op`: 두 정수와 연산자를 받아 계산 결과 또는 오류 메시지를 출력하는 프로그램을 만든다.
- ex06 `ft_sort_string_tab`: 문자열 배열을 ASCII 오름차순으로 정렬한다.
- ex07 `ft_advanced_sort_string_tab`: 전달받은 비교 함수 기준으로 문자열 배열을 정렬한다.

### Rush00

- ex00 `Rush00~Rush04`: `rush(x, y)` 함수로 너비와 높이에 맞는 사각형 패턴을 출력한다. 현재 저장소에는 `main.c`, `ft_putchar.c`, `rush00.c`부터 `rush04.c`까지 각 패턴 구현이 함께 보관되어 있다.

### Rush01

- ex00 `Rush-01`: 4x4 스카이스크래퍼 퍼즐을 풀어 첫 번째 해를 출력한다. 입력은 16개의 `1`~`4` 값 문자열만 허용하며, 잘못된 입력이나 해 없음은 `Error\n`로 처리한다.

## 폴더 구조

```text
.
├── Shell00/
├── Shell01/
├── C00/ ... C09/
├── C11/
├── Rush00/
└── Rush01/
```
