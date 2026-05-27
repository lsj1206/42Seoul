# CPP Module 01

## 개요

- CPP Module 01은 C++에서 object의 생성 위치, lifetime, 참조 방식, file stream, member function pointer를 다루는 과제다.
- C에서 익숙한 `malloc/free` 흐름을 C++의 `new/delete`, stack/heap object, pointer/reference 관계로 재학습한다.
- `Zombie`, `Weapon`, `FileManager`, `Harl` 구현을 통해 object가 언제 생성되고 언제 해제되어야 하는지 정리한다.

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

- `ex00`은 `Zombie` class를 만들고, `newZombie`와 `randomChump`를 통해 heap object와 stack object의 차이를 확인한다.
- `ex01`은 `zombieHorde` 함수에서 `Zombie` 배열을 한 번의 할당으로 생성하고, 사용 후 배열 전체를 해제한다.
- `ex02`는 같은 문자열을 pointer와 reference가 어떻게 가리키는지 주소와 값을 출력해 비교한다.
- `ex03`은 `Weapon`, `HumanA`, `HumanB`를 통해 reference member와 pointer member의 차이를 확인한다.
- `ex04`는 파일을 읽고 문자열을 치환한 뒤 원본을 직접 수정하지 않고 `<filename>.replace` 파일을 생성한다.
- `ex05`는 `Harl` class에서 level 문자열에 따라 알맞은 member function을 호출한다.

## 핵심 메모

### New & Delete

- **dynamic memory allocation**: runtime에 사용할 memory 공간을 할당하는 것.
  - 상황에 따라 원하는 크기만큼의 memory를 heap에 할당한다.
  - Heap은 사용자가 직접 관리해야 하는 memory 영역이다.
    - Stack은 compiler에 의해 어느 정도 안정성이 보장된다.
- `new`는 C++에서 지원하는 dynamic allocation 방식이며, `malloc`에 대응된다.
- `delete`는 `free`에 대응되며, 할당된 memory를 해제할 때 사용한다.
- `new`가 실패하면 기본적으로 `std::bad_alloc` 예외가 throw된다.
  - C에서 사용하는 NULL체크로 예외처리가 불가능하다.
- try-catch문을 통해서 예외처리할 수 있으며, `new(std::nothrow)`로 선언하면 C와 같은 방식으로(NULL 체크)로 예외처리가 가능하다.
- `newZombie`는 `new Zombie(name)`으로 heap object를 만들고, 호출한 쪽에서 `delete`로 lifetime을 끝낸다.
- `randomChump`는 함수 내부 stack object를 만든 뒤 바로 `announce`를 호출한다.
- `zombieHorde`는 `new(std::nothrow) Zombie[N]`로 배열을 만들고, 호출한 쪽에서 `delete[]`로 해제한다.

### Pointer와 Reference

- **pointer**는 다른 변수의 memory address를 가지고 있는 변수다.
- Pointer가 가리키는 값에 접근하려면 `*` operator를 사용해 dereference해야 한다.
- **reference**는 이미 존재하는 변수의 alias다.
- Reference는 선언과 동시에 초기화되어야 하며, null 참조가 불가능하고 다른 대상을 다시 가리키도록 재할당할 수 없다.
- `ex02`는 같은 문자열에 대해 원본 변수, pointer, reference의 주소와 값을 각각 출력한다.
- `HumanA`는 생성 시점에 항상 `Weapon`을 받아야 하므로 `Weapon&` reference member를 사용하고, `HumanB`는 weapon이 없을 수 있으므로 `Weapon*` pointer member를 사용한다.

### File Stream과 문자열 치환

- **file stream**은 파일을 입력 또는 출력 대상으로 다루는 stream이다.
- `std::ifstream`은 file input, `std::ofstream`은 file output에 사용한다.
- `FileManager`는 원본 파일을 열고, 출력 파일을 `<filename>.replace` 이름으로 만든다.
- `stringReplace`는 각 줄에서 `s1`을 찾아 지우고 `s2`를 삽입하는 방식으로 치환한 뒤 출력 파일에 기록한다.
- 원본 파일 이름, 찾을 문자열, 바꿀 문자열이 비어 있으면 잘못된 인자로 처리한다.

### Member Function Pointer

- **member function pointer**는 class의 member function을 가리키는 pointer다.
- 일반 function pointer와 달리 object와 함께 호출해야 하므로 `(this->*f[i])()` 형태를 사용한다.
- `Harl`은 `debug`, `info`, `warning`, `error`를 private member function으로 가진다.
- `complain`은 level 문자열 배열과 member function pointer 배열을 같은 순서로 두고, 입력 문자열과 일치하는 함수를 호출한다.

## 폴더 구조

```text
.
├── ex00/
│   ├── Makefile
│   ├── main.cpp
│   ├── Zombie.hpp
│   ├── Zombie.cpp
│   ├── newZombie.cpp
│   └── randomChump.cpp
├── ex01/
│   ├── Makefile
│   ├── main.cpp
│   ├── Zombie.hpp
│   ├── Zombie.cpp
│   └── zombieHorde.cpp
├── ex02/
│   ├── Makefile
│   └── main.cpp
├── ex03/
│   ├── Makefile
│   ├── main.cpp
│   ├── Weapon.hpp
│   ├── Weapon.cpp
│   ├── HumanA.hpp
│   ├── HumanA.cpp
│   ├── HumanB.hpp
│   └── HumanB.cpp
├── ex04/
│   ├── Makefile
│   ├── main.cpp
│   ├── FileManager.hpp
│   └── FileManager.cpp
└── ex05/
    ├── Makefile
    ├── main.cpp
    ├── Harl.hpp
    └── Harl.cpp
```

- `ex00`, `ex01`: `Zombie` object의 stack/heap 생성과 배열 할당
- `ex02`: pointer와 reference 비교
- `ex03`: `Weapon`, `HumanA`, `HumanB` 관계 구현
- `ex04`: file stream 기반 문자열 치환
- `ex05`: `Harl` class와 member function pointer 분기

## 빌드 및 실행

### 빌드

```bash
cd ex00 && make
cd ../ex01 && make
cd ../ex02 && make
cd ../ex03 && make
cd ../ex04 && make
cd ../ex05 && make
```

- 각 exercise 폴더에서 개별 Makefile을 실행한다.
- 실행 파일명은 각 폴더의 Makefile `NAME` 값인 `ex00`부터 `ex05`까지다.

### 실행

```bash
./ex00
./ex01
./ex02
./ex03
./ex04 <filename> <s1> <s2>
./ex05
```

- `ex04`는 입력 파일에서 `s1`을 찾아 `s2`로 치환한 내용을 `<filename>.replace` 파일로 출력한다.
- 나머지 exercise는 각 `main.cpp`에 작성된 테스트 흐름을 실행한다.

## 참고 자료

- [cplusplus.com - new operator](https://cplusplus.com/reference/new/operator%20new/)
- [cplusplus.com - string](https://cplusplus.com/reference/string/string/)
- [cplusplus.com - fstream](https://cplusplus.com/reference/fstream/)
