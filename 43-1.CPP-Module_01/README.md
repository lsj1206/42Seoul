# 12 - CPP Module 01

## 개요

- CPP Module 01은 C++에서 객체의 생성 위치, 생명주기, 참조 방식, 파일 stream, member function pointer를 다루는 과제다.
- 핵심은 C에서 익숙한 `malloc/free` 흐름을 C++의 `new/delete`, stack/heap object, pointer/reference 관계로 다시 구분하는 것이다.
- 현재 폴더에서는 `Zombie`, `Weapon`, `FileManager`, `Harl` 구현을 통해 객체가 언제 생성되고 언제 해제되어야 하는지 정리한다.

## 과제 요구사항

### Mandatory

- C++98 기준으로 컴파일되어야 하며, `-Wall -Wextra -Werror` 옵션을 통과해야 한다.
- `ex00`은 `Zombie` class를 만들고, `newZombie`와 `randomChump`를 통해 heap object와 stack object의 차이를 확인한다.
- `ex01`은 `zombieHorde` 함수에서 `Zombie` 배열을 한 번의 할당으로 생성하고, 사용 후 배열 전체를 해제한다.
- `ex02`는 같은 문자열을 pointer와 reference가 어떻게 가리키는지 주소와 값을 출력해 비교한다.
- `ex03`은 `Weapon`, `HumanA`, `HumanB`를 통해 reference member와 pointer member의 차이를 확인한다.
- `ex04`는 파일을 읽고 문자열을 치환한 뒤 원본을 직접 수정하지 않고 `<filename>.replace` 파일을 생성한다.
- `ex05`는 `Harl` class에서 level 문자열에 따라 알맞은 member function을 호출한다.

### C++98과 CPP Module 공통 규칙

- class 이름은 _UpperCamelCase_ 형식으로 작성한다.
- header는 include guard로 보호하고, template을 제외하면 header 안에 함수 구현을 두지 않는다.
- 모든 출력은 표준 출력으로 보내며, 별도 지시가 없으면 개행으로 끝낸다.
- `alloc`, `free`, `printf` 함수를 사용할 수 없다.
- STL container와 `<algorithm>` header를 사용할 수 없다.
- `nullptr`는 C++11부터 도입된 키워드이므로 C++98 기준에서는 사용할 수 없다.
- `using namespace`는 사용할 수 없다.
  - 필요한 이름 앞에 namespace를 명시해야 한다.
  - `namespace`는 함수, 구조체, 변수 이름이 어느 소속에 속하는지 정해 주는 단위다.
- `friend` 키워드는 사용할 수 없다.
  - class 간 친구 관계를 만들어 다른 class의 private member에 접근할 수 있게 하는 키워드다.

## 개념 정리

### New & Delete

- `new`는 C++에서 동적 메모리를 할당하고 object의 constructor를 호출한다.
- `delete`는 object의 destructor를 호출하고 할당된 메모리를 해제한다.
- C에서는 heap 할당에 `malloc/free`를 사용하지만, C++에서는 `new/delete`가 이에 대응된다.
- 배열을 동적으로 생성할 때는 `new[]`를 사용하고, 해제할 때는 `delete[]`를 사용한다.
- 기본 `new`가 실패하면 `std::bad_alloc` 예외가 발생한다.
- C처럼 null check 방식으로 실패를 다루려면 `new(std::nothrow)` 형태를 사용할 수 있다.

### Heap과 Stack

- heap은 실행 중 원하는 크기의 메모리를 할당할 수 있는 영역이며, 사용자가 직접 할당과 해제를 관리해야 한다.
- heap에 할당한 object는 필요한 동안 유지할 수 있지만, 해제하지 않으면 memory leak이 발생할 수 있다.
- stack은 함수 호출과 함께 할당되고, 함수 호출이 끝나면 자동으로 소멸하는 영역이다.
- stack object는 명시적인 해제가 필요 없지만, 함수 scope를 벗어나면 더 이상 사용할 수 없다.

### Pointer와 Reference

- pointer는 다른 변수의 메모리 주소를 가지고 있는 변수다.
- pointer가 가리키는 값에 접근하려면 `*` operator를 사용해 dereference해야 한다.
- reference는 이미 존재하는 변수의 alias다.
- reference는 선언과 동시에 초기화되어야 하며, null 참조가 불가능하고 다른 대상을 다시 가리키도록 재할당할 수 없다.
- reference는 내부적으로 pointer처럼 object의 주소를 저장하도록 구현될 수 있지만, 사용하는 쪽에서는 이름만으로 접근한다.

### Member Initializer

- member initializer는 constructor를 통해 구현하며, member variable을 초기화하는 문법이다.
- const member, reference member, object member, 부모 class member를 초기화할 때 사용할 수 있다.
- reference member처럼 반드시 생성 시점에 초기화되어야 하는 member에는 member initializer가 필요하다.

## 문제 해결의 핵심

### `ex00` Stack Object와 Heap Object

- `newZombie`는 heap에 `Zombie` object를 만들고 pointer를 반환하므로, 함수 밖에서도 object를 사용할 수 있다.
- heap object는 더 이상 필요하지 않을 때 호출한 쪽에서 `delete`해야 한다.
- `randomChump`는 함수 내부 stack에 `Zombie` object를 만들고 바로 `announce`를 호출하므로, 함수가 끝나면 object가 자동으로 소멸한다.

### `ex01` 배열 생명주기

- 여러 `Zombie`를 한 번에 만들려면 `new[]`를 사용해 배열을 할당해야 한다.
- 배열로 할당한 object는 `delete[]`로 해제해야 각 요소의 destructor 호출과 배열 메모리 해제가 함께 맞는다.
- `zombieHorde`는 `N`이 유효하지 않거나 할당에 실패한 경우 null pointer를 반환하도록 처리한다.

### `ex02` Pointer와 Reference 비교

- 같은 문자열에 대해 원본 변수, pointer, reference의 주소와 값을 각각 출력한다.
- pointer는 주소를 저장하고 `*`로 값을 읽지만, reference는 별칭처럼 원본 이름과 같은 방식으로 값을 읽는다.
- 이 exercise는 pointer와 reference가 같은 object를 가리킬 수 있지만, 선언과 사용 방식이 다르다는 점을 확인하는 용도다.

### `ex03` Reference Member와 Pointer Member

- `HumanA`는 생성 시점에 항상 `Weapon`을 받아야 하므로 `Weapon&` reference member를 사용한다.
- reference member는 생성과 동시에 초기화되어야 하므로 constructor의 member initializer에서 설정한다.
- `HumanB`는 weapon이 없을 수 있고 나중에 `setWeapon`으로 받을 수 있으므로 `Weapon*` pointer member를 사용한다.
- `Weapon::getType`은 `const std::string&`를 반환해 weapon type 문자열을 직접 복사하지 않고 참조한다.

### `ex04` 파일 치환

- 원본 파일을 직접 수정하지 않고, 입력 파일 이름에 `.replace`를 붙인 새 파일을 만든다.
- 입력 파일과 출력 파일은 file stream으로 열고, 한 줄씩 읽어 `s1`을 찾아 `s2`로 치환한다.
- 파일 이름, 찾을 문자열, 바꿀 문자열이 비어 있으면 잘못된 인자로 처리한다.

### `ex05` Member Function Pointer

- `Harl`은 `DEBUG`, `INFO`, `WARNING`, `ERROR` level에 대응하는 private member function을 가진다.
- `complain`은 문자열과 member function pointer 배열을 비교해 일치하는 level의 함수를 호출한다.
- 일치하는 level이 없으면 invalid level 메시지를 출력한다.

## 내가 구현한 방식

### `Zombie`, `newZombie`, `randomChump`

- `Zombie`는 `name`을 private member로 가지고, `announce`에서 `<name>: BraiiiiiiinnnzzzZ...` 형식으로 출력한다.
- destructor는 object가 소멸될 때 `<name> is dead`를 출력해 소멸 시점을 확인할 수 있게 한다.
- `newZombie`는 `new Zombie(name)`으로 heap object를 만들고 pointer를 반환한다.
- `randomChump`는 local `Zombie` object를 만들고 `announce`를 호출한다.

### `zombieHorde`

- `zombieHorde(int N, std::string name)`은 `N <= 0`이면 null pointer를 반환한다.
- `new(std::nothrow) Zombie[N]`로 배열을 할당하고, 실패하면 null pointer를 반환한다.
- 각 요소에 `SetName`으로 같은 이름을 설정한 뒤 `announce`를 호출한다.
- 호출자는 반환된 배열을 사용한 뒤 `delete[]`로 해제한다.

### `Pointer`와 `Reference` 출력

- `ex02`는 `std::string A`, `std::string* stringPTR`, `std::string& stringREF`를 만든다.
- 원본 문자열, pointer, reference의 주소를 출력하고, 이어서 각각의 값을 출력한다.
- reference의 주소는 원본 문자열의 주소와 같은 값으로 출력된다.

### `Weapon`, `HumanA`, `HumanB`

- `Weapon`은 `type`을 저장하고, `getType`과 `setType`으로 값을 읽고 변경한다.
- `HumanA`는 `Weapon& weapon`을 member로 가지고, constructor member initializer로 weapon을 초기화한다.
- `HumanB`는 `Weapon* weapon`을 member로 가지고, constructor에서 null pointer로 초기화한 뒤 `setWeapon`으로 weapon 주소를 저장한다.
- `attack`은 weapon이 있으면 현재 weapon type을 출력하고, `HumanB`는 weapon이 없을 때 별도 메시지를 출력한다.

### `FileManager`

- `FileManager`는 파일 이름, 찾을 문자열, 바꿀 문자열과 입출력 file stream을 member로 가진다.
- `checkArg`는 파일 이름과 치환 문자열이 비어 있는지 확인한다.
- `getFile`은 원본 파일을 열고, 출력 파일을 `<filename>.replace` 이름으로 연다.
- `stringReplace`는 각 줄에서 `s1`을 찾아 지우고 `s2`를 삽입하는 방식으로 치환한 뒤 출력 파일에 기록한다.
- destructor는 입출력 file stream을 닫는다.

### `Harl`

- `Harl`은 `debug`, `info`, `warning`, `error`를 private member function으로 가진다.
- `complain`은 member function pointer 배열과 level 문자열 배열을 같은 순서로 두고, 입력 문자열과 일치하는 함수를 호출한다.
- `main`은 네 가지 정상 level과 하나의 잘못된 level을 호출해 분기 흐름을 확인한다.

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
