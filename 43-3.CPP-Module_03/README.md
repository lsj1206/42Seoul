# CPP Module 03

## 개요

- CPP Module 03은 C++의 상속을 통해 공통 상태와 동작을 base class에 두고, derived class에서 필요한 차이를 확장하는 과제다.
- `ClapTrap`을 기준으로 `ScavTrap`, `FragTrap`을 만들며 접근 제어자, 생성/소멸 순서, member 재사용 범위를 구분해 학습한다.
- `ex00`~`ex02`를 통해 단일 base class를 공유하는 파생 class들의 상태값과 고유 동작을 정리한다.

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

## 개념 정리

### Inheritance

- _inheritance_, 상속은 _base class_(기본 클래스)의 member variable과 member function을 _derived class_(파생 클래스)가 이어받아 재사용하는 구조다.
- 공통 상태와 동작은 base class에 두고, derived class는 필요한 초기값이나 고유 동작만 추가할 수 있다.
- 이 과제에서는 `ClapTrap`이 base class가 되고, `ScavTrap`과 `FragTrap`이 derived class가 된다.

### Access Modifier

- `public` member는 class 외부에서도 접근할 수 있는 공개 interface다.
- `protected` member는 class 외부에서는 접근할 수 없지만, 상속받은 derived class 내부에서는 접근할 수 있다.
- `private` member는 자기 class 내부에서만 직접 접근할 수 있다.
- 상속 구조에서는 base class의 상태를 derived class가 직접 조정해야 하는지에 따라 `private`과 `protected`의 선택이 달라진다.

### Constructor와 Destructor 호출 순서

- derived object가 생성될 때는 base class constructor가 먼저 호출되고, 그 다음 derived class constructor가 호출된다.
- object가 소멸될 때는 반대로 derived class destructor가 먼저 호출되고, base class destructor가 나중에 호출된다.
- 이 순서는 derived class가 base class의 상태를 기반으로 만들어지기 때문에 필요하다.

### Up-casting과 Down-casting

- up-casting은 derived object를 base class pointer나 reference로 가리키는 것이다.
- up-casting된 상태에서는 base class interface 범위 안에서만 object를 다룰 수 있다.
- down-casting은 base class 쪽으로 바라보던 object를 다시 derived type으로 보는 것이며, 타입 관계를 더 조심해야 한다.

## 문제 해결의 핵심

### `ex00` 상태와 행동 가능 여부

- `ClapTrap`은 HP, EP, AD를 가지고 공격, 피해, 회복 동작을 수행한다.
- 공격과 회복은 EP를 소비하므로, 행동 전에 HP와 EP가 남아 있는지 확인해야 한다.
- 피해를 받을 때는 HP가 0 아래로 내려가지 않도록 상태 변경 범위를 제한해야 한다.

### `ex01` 상속을 위한 접근 범위 조정

- `ScavTrap`은 `ClapTrap`의 상태를 재사용하지만, HP/EP/AD 초기값은 `100/50/20`으로 달라야 한다.
- 이를 위해 `ex01`부터 `ClapTrap`의 상태 member는 derived class가 접근할 수 있는 `protected` 영역으로 이동한다.
- `ScavTrap`은 `ClapTrap`의 기본 동작 일부를 공유하면서, `attack` 출력과 `guardGate`처럼 자기 class만의 동작을 추가한다.

### `ex02` 같은 Base에서 다른 Derived 확장

- `FragTrap`도 `ClapTrap`을 상속하지만, 초기값은 `100/100/30`으로 `ScavTrap`과 다르다.
- `FragTrap`은 `attack`을 새로 정의하지 않고 `ClapTrap`의 공격 흐름을 그대로 사용하면서, 변경된 `Attack_damage` 값이 반영되게 한다.
- `highFivesGuys`는 `FragTrap` 전용 동작으로, 공통 base에 없는 기능을 derived class에서 확장하는 예시다.

### Virtual 선언

- `ex01` 이후 `ClapTrap`의 destructor와 `attack`은 `virtual`로 선언되어 있다.
- `virtual attack`은 derived class가 같은 이름의 동작을 다시 정의할 수 있게 하는 기반이 된다.
- `virtual destructor`는 base class 관점에서 derived object를 다룰 가능성을 고려해 소멸 흐름을 안전하게 열어 두는 선언이다.

## 내가 구현한 방식

### `ex00/ClapTrap`

- `ClapTrap`은 `Name`, `Hit_points`, `Energy_points`, `Attack_damage`를 member로 가진다.
- 기본 생성자는 `Default`, `10`, `10`, `0`으로 초기화하고, 이름을 받는 생성자는 전달받은 이름을 사용한다.
- `attack`은 HP와 EP를 확인한 뒤 EP를 1 줄이고, 현재 AD만큼 피해를 준다는 메시지를 출력한다.
- `takeDamage`는 받은 피해량만큼 HP를 줄이되, HP가 0이 되면 더 줄이지 않는다.
- `beRepaired`는 HP와 EP를 확인한 뒤 EP를 1 줄이고 HP를 회복한다.
- `checkHealth`와 `checkEnergy`는 행동 가능 여부를 확인하고, 부족한 상태일 때 메시지를 출력한다.

### `ex01/ScavTrap`

- `ScavTrap`은 `public ClapTrap`으로 선언되어 `ClapTrap`의 public interface를 이어받는다.
- `ClapTrap`의 상태 member는 `protected`로 변경되어, `ScavTrap` constructor에서 HP/EP/AD를 직접 재설정할 수 있다.
- `ScavTrap`의 기본값은 HP `100`, EP `50`, AD `20`이다.
- `Guardgate_mode`는 `ScavTrap` 고유 상태이며, 기본값은 `false`다.
- `attack`은 `ClapTrap`과 같은 상태 확인 및 EP 소모 흐름을 사용하지만, `ScavTrap` 전용 출력 메시지를 사용한다.
- `guardGate`는 HP와 EP를 확인한 뒤 `Guardgate_mode`를 `true`로 바꾸고 gate keeper mode 메시지를 출력한다.

### `ex02/FragTrap`

- `FragTrap`은 `public ClapTrap`으로 선언되어 `ClapTrap`의 상태와 기본 동작을 이어받는다.
- `FragTrap`의 기본값은 HP `100`, EP `100`, AD `30`이다.
- `FragTrap`은 별도의 `attack`을 정의하지 않으므로, `ClapTrap::attack`을 그대로 사용한다.
- `highFivesGuys`는 HP와 EP를 확인한 뒤 high five 요청 메시지를 출력한다.
- 복사 생성자는 `ClapTrap(copy)`를 통해 base 부분을 먼저 복사하고, 복사 대입 연산자는 이름과 상태값을 복사한다.

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
