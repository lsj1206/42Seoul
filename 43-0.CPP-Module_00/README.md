# CPP Module 00

## 개요

- CPP Module 00은 C++ 문법과 객체 지향 프로그래밍의 출발점을 다루는 첫 번째 C++ 과제다.
- - C에서 익숙한 절차 중심 작성 방식에서, C++의 객체 중심 구조로 전환하는 학습을 한다.
- `megaphone`으로 기본 입출력과 문자열 처리를 연습하고, `PhoneBook`/`Contact`로 객체가 상태와 동작을 함께 갖는 구조를 정리한다.

## 과제 요구사항

### C++98과 CPP Module 공통 규칙

- C++98 기준으로 컴파일되어야 하며, `-Wall -Wextra -Werror` 옵션을 통과해야 한다.
- 모든 출력은 표준 출력으로 보내며, 별도 지시가 없으면 개행으로 끝낸다.
- header는 include guard로 보호하고, template을 제외하면 header 안에 함수 구현을 두지 않는다.
- class 이름은 _UpperCamelCase_ 형식으로 작성한다.
- `alloc`, `free`, `printf` 함수를 사용할 수 없다.
- STL container와 `<algorithm>` header를 사용할 수 없다.
- `nullptr`는 C++11부터 도입된 키워드이므로 C++98 기준에서는 사용할 수 없다.
- `using namespace`는 사용할 수 없다.
  - 필요한 이름 앞에 namespace를 명시해야 한다.
  - `namespace`는 함수, 구조체, 변수 이름이 어느 소속에 속하는지 정해 주는 단위다.
- `friend` 키워드는 사용할 수 없다.
  - class 간 친구 관계를 만들어 다른 class의 private member에 접근할 수 있게 하는 키워드다.

### Mandatory

- C++98 기준으로 컴파일되어야 하며, `-Wall -Wextra -Werror` 옵션을 통과해야 한다.
- `ex00`은 인자로 받은 문자열을 모두 대문자로 변환해 출력하는 `megaphone` 프로그램을 만든다.
- `ex00`은 인자가 없을 때 정해진 feedback noise 문구를 출력한다.
- `ex01`은 최대 8개의 연락처를 저장하는 `PhoneBook`과 연락처 정보를 담는 `Contact` class를 구현한다.
- `ex01`은 `ADD`, `SEARCH`, `EXIT` 명령을 처리하고, 검색 결과를 정해진 폭과 형식으로 출력한다.

## 개념 정리

### Constructor와 Destructor

- constructor는 object가 되기 위해 반드시 한 번 호출되는 함수이며, object 생성 시 한 번 호출된다.
- constructor는 class 이름과 같은 이름을 가지고, 반환형과 반환값이 없다.
- constructor는 overloading과 default argument 설정이 가능하다.
- default constructor는 인자를 받지 않으며, 생성자를 따로 정의하지 않으면 compiler가 생성할 수 있다.
- destructor는 object 소멸 시 호출되며, `~`가 붙은 class 이름 형태를 가진다.
- destructor는 반환형이 없고 매개변수를 받을 수 없으며, overloading과 default argument 설정이 불가능하다.
- 생성자에서 동적 할당한 메모리 공간은 destructor에서 해제해야 한다.
- default destructor가 존재한다.

### `this` Pointer

- `this`는 object 자신에 대한 pointer다.
- `this`는 class의 member function 내부에서만 사용할 수 있다.
- object 자신의 주소를 return할 필요가 있을 때 사용할 수 있다.
- constructor나 member function에서 매개변수 이름과 member 이름을 구분할 때 사용할 수 있다.

### `static_cast`

- `static_cast<바꾸려는 타입>(대상)` 형태로 사용한다.
- 기본 자료형 간 형 변환이나 상속 관계의 class 계층 간 변환에 사용할 수 있다.
- 형 변환 시점이 compile time이기 때문에 static이라는 이름이 붙는다.
- C style cast는 일반적이지 않은 형 변환도 허용할 수 있으므로, 의도를 더 명확히 하기 위해 `static_cast`를 사용한다.

### Member Initializer

- member initializer는 constructor를 통해 구현하며, member variable을 초기화하는 문법이다.
- const member, reference member, object member, 부모 class member를 초기화할 때 사용할 수 있다.
- field 선언과 member initializer가 모두 존재하면 member initializer의 초기화가 적용된다.

## 문제 해결의 핵심

### C 문자열 입력을 C++ 출력 흐름으로 처리

- `megaphone`은 `main`의 `char **av`로 들어온 C 스타일 문자열을 순회하지만, 출력은 `std::cout`으로 처리한다.
- `std::toupper`는 변환 결과를 `int`로 반환하므로, 문자로 출력하기 위해 `static_cast<char>`를 사용한다.
- 인자가 없는 경우와 있는 경우를 분리해, 과제에서 요구한 기본 문구와 변환 출력을 각각 처리한다.

### 고정 크기 저장소로 연락처 관리

- `PhoneBook`은 동적 할당이나 컨테이너 없이 `Contact contacts[8]` 배열로 연락처를 저장한다.
- 8개를 초과해 `ADD`가 들어오면 `idx`를 0으로 되돌려 가장 오래된 연락처부터 덮어쓴다.
- 이 방식은 저장 가능한 개수가 고정된 과제 조건을 단순한 순환 저장 구조로 처리한다.

### 입력 검증과 출력 형식 분리

- `ADD`에서는 각 field가 비어 있으면 다시 입력받아 빈 연락처가 저장되지 않도록 한다.
- `SEARCH`에서는 전체 목록을 먼저 표 형태로 출력하고, 사용자가 선택한 index가 유효할 때만 상세 정보를 보여준다.
- 목록 출력에서는 10칸 폭을 맞추고, 10자를 넘는 문자열은 앞 9자와 `.`로 줄여 과제의 출력 형식을 맞춘다.

### 상태 접근 통제

- `Contact`의 실제 field는 `private`으로 숨기고, 입력 함수와 출력 함수만 `public`으로 제공한다.
- `PhoneBook`은 `Contact`의 내부 field에 직접 접근하지 않고, public member function을 통해 값을 저장하거나 읽는다.
- 이 구조를 통해 C의 구조체처럼 데이터를 직접 만지는 방식에서 class interface를 통해 object를 다루는 방식으로 넘어간다.

## 내가 구현한 방식

### `ex00/megaphone.cpp`

- 인자가 없으면 `* LOUD AND UNBEARABLE FEEDBACK NOISE *`를 출력한다.
- 인자가 있으면 첫 번째 인자부터 마지막 인자까지 각 문자를 순회하며 `std::toupper`로 대문자 변환 후 출력한다.
- 모든 인자 처리가 끝난 뒤 한 번만 개행을 출력한다.

### `ex01/Contact`

- `Contact`는 `first_name`, `last_name`, `nickname`, `phone`, `secret`을 `private` member로 가진다.
- `input_*` 함수는 각 field에 문자열을 저장하고, `output_*` 함수는 저장된 값을 반환한다.
- 입력과 출력 함수를 분리해 `PhoneBook`이 연락처 정보를 필요한 방식으로 저장하고 표시할 수 있게 한다.

### `ex01/PhoneBook`

- `PhoneBook`은 `Contact contacts[8]`과 현재 저장 위치를 나타내는 `idx`를 가진다.
- constructor는 `idx`를 0으로 초기화하고, destructor는 별도 동적 자원이 없으므로 추가 정리 작업을 하지 않는다.
- `ADD`는 다섯 개 field를 순서대로 입력받아 현재 `idx` 위치의 `Contact`에 저장한 뒤 `idx`를 증가시킨다.
- `SEARCH`는 저장된 연락처 목록을 출력하고, 입력받은 index가 1~8 범위이며 실제 데이터가 있을 때 상세 정보를 출력한다.
- `EXIT`는 프로그램을 종료한다.

### 입력과 표시 보조 함수

- `str_vaild`는 빈 문자열이 들어오면 다시 입력을 요구해 필수 field가 비어 있지 않도록 한다.
- `length_handler`는 문자열 길이가 10자를 초과하면 앞 9자만 남기고 마지막에 `.`을 붙인다.
- `print_phonebook`은 `std::setw(10)`을 사용해 `Index`, `First Name`, `Last Name`, `Nickname` 열을 같은 폭으로 출력한다.

## 폴더 구조

```text
.
├── ex00/
│   ├── Makefile
│   └── megaphone.cpp
└── ex01/
    ├── Makefile
    ├── main.cpp
    ├── Contact.hpp
    ├── Contact.cpp
    ├── PhoneBook.hpp
    └── PhoneBook.cpp
```

- `ex00`: 문자열을 대문자로 출력하는 `megaphone` 프로그램
- `ex01`: `PhoneBook`과 `Contact` class를 사용하는 간단한 전화번호부 프로그램

## 빌드 및 실행

### 빌드

```bash
cd ex00
make

cd ../ex01
make
```

- 각 exercise 폴더에서 개별 Makefile을 실행한다.
- `ex00`의 실행 파일명은 `megaphone`, `ex01`의 실행 파일명은 `ex01`이다.

### 실행

```bash
./megaphone "hello" "cpp"

./ex01
```

- `megaphone`은 인자를 대문자로 변환해 출력한다.
- `ex01`은 실행 후 `ADD`, `SEARCH`, `EXIT` 명령을 입력해 동작을 확인한다.

## 참고 자료

- [cplusplus.com - std::string](https://cplusplus.com/reference/string/string/)
- [cplusplus.com - iomanip](https://cplusplus.com/reference/iomanip/)
