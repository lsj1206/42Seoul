# CPP Module 00

## 개요

- CPP Module 00은 C++ 문법과 객체 지향 프로그래밍의 출발점을 다루는 첫 번째 C++ 과제다.
- C에서 익숙한 절차 중심 작성 방식에서, C++의 object 중심 구조로 전환하는 학습을 한다.
- `megaphone`으로 기본 입출력과 문자열 처리를 연습하고, `PhoneBook`/`Contact`로 object가 상태와 동작을 함께 갖는 구조를 정리한다.

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

- `ex00`은 인자로 받은 문자열을 모두 대문자로 변환해 출력하는 `megaphone` 프로그램을 만든다.
- `ex00`은 인자가 없을 때 정해진 feedback noise 문구를 출력한다.
- `ex01`은 최대 8개의 연락처를 저장하는 `PhoneBook`과 연락처 정보를 담는 `Contact` class를 구현한다.
- `ex01`은 `ADD`, `SEARCH`, `EXIT` 명령을 처리하고, 검색 결과를 정해진 폭과 형식으로 출력한다.

## 핵심 메모

### Constructor와 Destructor

- **Constructor**: object가 되기 위해 반드시 하나의 constructor가 호출되어야 한다.
- Constructor는 object 생성 시 한 번 호출된다.
- Constructor는 class 이름과 같은 이름을 가지며, 반환형과 반환값이 없다.
- Constructor는 overloading과 default argument 설정이 가능하다.
- **Destructor**: object 소멸 시 반드시 호출된다.
- Destructor는 `~`가 붙은 형태의 이름을 가진다.
- Destructor는 매개변수를 받을 수 없고 overloading할 수 없다.
- `PhoneBook`은 constructor에서 `idx`를 0으로 초기화하고, 동적 자원을 사용하지 않으므로 destructor에서 별도 해제 작업을 하지 않는다.

### this Pointer

- **this pointer**는 object 자신에 대한 pointer다.
- `this`는 class의 member function 내부에서만 사용할 수 있다.
- Constructor나 member function에서 매개변수 이름과 member 이름을 구분할 때 사용할 수 있다.
- `PhoneBook`과 `Contact`의 member function은 현재 object의 field에 값을 저장하거나 읽는 흐름을 가진다.

### static_cast

- `static_cast<바꾸려는 타입>(대상)` 형태로 사용하는 C++의 명시적 형 변환 문법이다.
- 기본 자료형 사이의 변환처럼 compile time에 판단 가능한 변환에 사용할 수 있다.
- C style cast는 여러 종류의 변환을 넓게 허용할 수 있으므로, 변환 의도를 분명하게 드러내기 위해 `static_cast`를 사용한다.
- `megaphone`은 `std::toupper`의 반환값을 문자로 출력하기 위해 `static_cast<char>`를 사용한다.

### Member Initializer

- **member initializer**는 constructor를 통해 member variable을 초기화하는 문법이다.
- const member, reference member, object member, 부모 class member를 초기화할 때 사용할 수 있다.
- reference member처럼 반드시 생성 시점에 초기화되어야 하는 member에는 member initializer가 필요하다.
- `PhoneBook::PhoneBook() : idx(0) {}`는 constructor body에 들어가기 전에 `idx`를 0으로 초기화한다.

### Class와 Encapsulation

- **class**는 data와 그 data를 다루는 member function을 함께 묶는 단위다.
- **encapsulation(캡슐화)**은 object의 내부 상태를 직접 노출하지 않고, public interface를 통해 다루게 하는 방식이다.
- `Contact`는 `first_name`, `last_name`, `nickname`, `phone`, `secret`을 `private` member로 숨긴다.
- `PhoneBook`은 `Contact contacts[8]`과 현재 저장 위치 `idx`를 가지고, `ADD`, `SEARCH`, `EXIT` 흐름을 public member function으로 처리한다.
- 8개를 초과해 `ADD`가 들어오면 `idx`를 0으로 되돌려 가장 오래된 연락처부터 덮어쓴다.

### 입출력과 문자열 표시

- `std::cout`은 표준 출력 stream이며, `std::cin`은 표준 입력 stream이다.
- `megaphone`은 `main`의 `char **av`로 들어온 C style string을 순회하지만, 출력은 `std::cout`으로 처리한다.
- `PhoneBook`의 `print_phonebook`은 `std::setw(10)`을 사용해 표의 폭을 맞춘다.
- `length_handler`는 문자열 길이가 10자를 초과하면 앞 9자만 남기고 마지막에 `.`을 붙여 출력 형식을 맞춘다.

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
