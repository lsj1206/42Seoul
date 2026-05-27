# CPP Module 03

## 개요

- CPP Module 03은 C++의 inheritance를 통해 공통 상태와 동작을 base class에 두고, derived class에서 필요한 차이를 확장하는 과제다.
- `ClapTrap`을 기준으로 `ScavTrap`, `FragTrap`을 만들며 access modifier, constructor/destructor 호출 순서, member 재사용 범위를 구분해 학습한다.
- `ex00`~`ex02`를 통해 단일 base class를 공유하는 derived class들이 서로 다른 상태값과 고유 동작을 가질 수 있음을 확인한다.

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

- `ex00`은 `Name`, `Hit_points`, `Energy_points`, `Attack_damage`를 가진 `ClapTrap` class를 구현한다.
- `ClapTrap`은 `attack`, `takeDamage`, `beRepaired`를 제공하고, HP 또는 EP가 부족한 경우 행동하지 않아야 한다.
- `ex01`은 `ScavTrap`을 `ClapTrap`에서 public 상속하고, 다른 초기값과 다른 `attack` 출력, `guardGate` 동작을 추가한다.
- `ex01`은 `ScavTrap` 생성 시 `ClapTrap`이 먼저 생성되고, 소멸 시 반대 순서로 호출되는 흐름을 보여야 한다.
- `ex02`는 `FragTrap`을 `ClapTrap`에서 public 상속하고, 다른 초기값과 `highFivesGuys` 동작을 추가한다.
- `ex02` 역시 base class와 derived class의 생성/소멸 호출 순서를 확인할 수 있어야 한다.

## 핵심 메모

### Inheritance

- **base class(부모 클래스)**의 member variable과 method를 **derived class(자식/파생 클래스)**가 재사용하는 개념이다.
- derived class는 base class의 member를 물려받는다.
- `ClapTrap`을 base class로 두고 `ScavTrap`과 `FragTrap`이 이를 상속하는 구조가 이 개념에 해당한다.

### Access modifier

- `public`: member variable 및 method에 어떤 class에서나 접근 가능하다.
- `protected`: member variable 및 method에 자신을 상속하는 class까지만 접근 가능하다.
- `private`: member variable 및 method에 오직 본인 class 안에서만 접근 가능하다.
- `ex00`의 `ClapTrap` member는 `private`이지만, `ex01`부터는 `ScavTrap`과 `FragTrap`이 HP/EP/AD 값을 재설정할 수 있도록 `protected`로 변경된다.

### Up-casting과 Down-casting

- **Up-casting**: *base class pointer*로 derived class object를 가리키는 것.
- Up-casting은 명시적 type 변환이 필요 없다.
- Up-casting된 base class pointer로는 base class의 member에만 접근 가능하다.
- **Down-casting**: derived class pointer로 base class pointer가 가리키는 object를 가리키는 것.
- 현재 코드에서 base class pointer를 직접 만들지는 않지만, `ScavTrap : public ClapTrap`과 `FragTrap : public ClapTrap` 선언이 up-casting 가능한 상속 관계를 만든다.

> _base class pointer_: base class type으로 선언된 pointer이며, derived class object의 주소를 가리킬 수 있다.
> pointer type은 base class이므로 base class에 정의된 member를 기준으로 접근한다.

### ClapTrap의 상태와 Derived class 확장

- `ClapTrap`은 `Name`, `Hit_points`, `Energy_points`, `Attack_damage`를 가지고 `attack`, `takeDamage`, `beRepaired`를 수행한다.
- `attack`과 `beRepaired`는 EP를 소비하므로, 현재 코드는 `checkHealth`와 `checkEnergy`로 행동 가능 여부를 먼저 확인한다.
- `ScavTrap`은 `ClapTrap`의 상태를 재사용하면서 HP `100`, EP `50`, AD `20`으로 값을 바꾸고, `guardGate`를 추가한다.
- `FragTrap`은 HP `100`, EP `100`, AD `30`으로 값을 바꾸고, `highFivesGuys`를 추가한다.
- `ex01` 이후 `ClapTrap`의 destructor와 `attack`은 `virtual`로 선언되어 있고, `ScavTrap`은 `attack`을 다시 정의한다.

## 폴더 구조

```text
.
├── ex00/
│   ├── Makefile
│   ├── main.cpp
│   ├── ClapTrap.hpp
│   └── ClapTrap.cpp
├── ex01/
│   ├── Makefile
│   ├── main.cpp
│   ├── ClapTrap.hpp
│   ├── ClapTrap.cpp
│   ├── ScavTrap.hpp
│   └── ScavTrap.cpp
└── ex02/
    ├── Makefile
    ├── main.cpp
    ├── ClapTrap.hpp
    ├── ClapTrap.cpp
    ├── ScavTrap.hpp
    ├── ScavTrap.cpp
    ├── FragTrap.hpp
    └── FragTrap.cpp
```

- `ex00`: 기본 `ClapTrap` class와 HP/EP 기반 동작
- `ex01`: `ScavTrap` 상속, 다른 초기값, `guardGate`
- `ex02`: `FragTrap` 상속, 다른 초기값, `highFivesGuys`

## 빌드 및 실행

### 빌드

```bash
cd ex00 && make
cd ../ex01 && make
cd ../ex02 && make
```

- 각 exercise 폴더에서 개별 Makefile을 실행한다.
- 실행 파일명은 각 폴더의 Makefile `NAME` 값인 `ex00`, `ex01`, `ex02`다.

### 실행

```bash
./ex00
./ex01
./ex02
```

- 각 exercise 폴더에서 빌드한 뒤 해당 실행 파일을 실행한다.
- 실행 결과는 각 `main.cpp`에 작성된 예제 흐름을 출력한다.
