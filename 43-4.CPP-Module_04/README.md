# CPP Module 04

## 개요

- CPP Module 04는 상속 계층에서 base class pointer로 derived object를 다룰 때 발생하는 polymorphism, virtual function, dynamic binding을 확인하는 과제다.
- 같은 interface 호출이 실제 object type에 따라 다른 동작으로 연결되는 흐름을 작은 class 예제로 정리한다.
- `Brain`을 소유하는 `Dog`/`Cat`과 pure virtual function을 가진 `AAnimal`을 통해 동적 자원 관리, deep copy, abstract class까지 함께 다룬다.

## 과제 요구사항

### C++98과 CPP Module 공통 규칙

- C++98 기준으로 컴파일되어야 하며, `-Wall -Wextra -Werror` 옵션을 통과해야 한다.
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

### Mandatory

- `ex00`은 `Animal`, `Dog`, `Cat` class를 만들고, base pointer로 호출한 `makeSound`가 실제 object type에 맞게 동작하도록 구현한다.
- `ex00`은 `WrongAnimal`, `WrongCat`을 통해 `makeSound`가 `virtual`이 아닐 때의 차이를 비교한다.
- `Animal`의 destructor는 `virtual`로 선언해 base pointer로 derived object를 삭제해도 소멸 흐름이 이어지게 한다.
- `ex01`은 `Dog`와 `Cat`이 `Brain`을 동적 자원으로 가지도록 확장한다.
- `ex01`은 `Dog`와 `Cat`의 copy constructor, copy assignment operator, destructor에서 `Brain`의 deep copy와 해제를 처리한다.
- `ex02`는 `Animal`을 직접 인스턴스화할 수 없는 abstract class 형태로 바꾸고, derived class가 `makeSound`를 구현하도록 한다.

## 핵심 메모

### Deep Copy

- **deep copy(깊은 복사)**는 pointer member가 가리키는 resource를 공유하지 않고, object별로 독립된 resource를 가지도록 복사하는 방식이다.
- 얕은 복사는 pointer 값만 복사하므로 여러 object가 같은 resource를 가리킬 수 있다.
- `Dog`와 `Cat`은 `Brain*`을 member로 가지고, constructor에서 각자 `Brain`을 만든다.
- Copy constructor는 먼저 새 `Brain`을 만든 뒤 대입 연산자를 통해 내용을 복사한다.
- Copy assignment operator는 `*this->brain = *copy.brain`으로 `Brain` 내부의 `ideas[100]` 값을 복사한다.

### Virtual inheritance

```c++
Base* p = new Derived();
delete p;
// compiler는 `p`를 base class pointer로 인식한다.
// 이때 derived class destructor가 호출되지 않으면 memory leak이 발생할 수 있다.
```

- **Virtual inheritance(가상 상속)**는 derived class object가 생성될 때 base class member 공간을 한 번만 할당하고, 이미 할당되어 있다면 그 공간을 공유하도록 compiler에게 지시하는 상속이다.
- `virtual` keyword가 붙은 function은 어떤 function이 실행될지 compile time에 정해지지 않고 runtime에 정해질 수 있다.
- 이 과제에서는 `virtual`이 있는 `Animal::makeSound`와 `virtual`이 없는 `WrongAnimal::makeSound`의 호출 차이를 비교한다.

> _dynamic binding(동적 바인딩)_: 어떤 function이 실행될지 compile 단계에서 정해지지 않고 runtime 단계에서 정해지는 것.

### Abstract class와 Pure virtual function

- **abstract class(추상 클래스)**: pure virtual function이 한 개 이상 존재하는 class로, object 생성이 불가능하다.

- **pure virtual function(순수 가상 함수)**: 무엇을 하는지 정의되어 있지 않아 반드시 _overriding_ 되어야만 하는 function.

  ```c++
  // pure virtual function 선언 형태
  virtual void speak() = 0;
  ```

- `AAnimal`은 `virtual void makeSound() const = 0`을 선언한 abstract class이고, `Dog`와 `Cat`은 이를 overriding한다.

> _overriding_: derived class가 base class의 virtual function과 같은 signature로 function을 다시 정의하는 것. <br> base class pointer로 호출하더라도 runtime의 실제 object type에 맞는 derived class 구현이 실행될 수 있게 한다.

> **Polymorphism(다형성)** 구현: abstract class를 상속한 여러 하위 class들은 abstract class의 method를 각각 다르게 구현해서, 동일한 method 호출이 서로 다른 구현을 실행할 수 있게 한다.

## 폴더 구조

```text
.
├── ex00/
│   ├── Makefile
│   ├── main.cpp
│   ├── Animal.hpp
│   ├── Animal.cpp
│   ├── Dog.hpp
│   ├── Dog.cpp
│   ├── Cat.hpp
│   ├── Cat.cpp
│   ├── WrongAnimal.hpp
│   ├── WrongAnimal.cpp
│   ├── WrongCat.hpp
│   └── WrongCat.cpp
├── ex01/
│   ├── Makefile
│   ├── main.cpp
│   ├── Animal.hpp
│   ├── Animal.cpp
│   ├── Dog.hpp
│   ├── Dog.cpp
│   ├── Cat.hpp
│   ├── Cat.cpp
│   ├── Brain.hpp
│   ├── Brain.cpp
│   ├── WrongAnimal.hpp
│   ├── WrongAnimal.cpp
│   ├── WrongCat.hpp
│   └── WrongCat.cpp
└── ex02/
    ├── Makefile
    ├── main.cpp
    ├── AAnimal.hpp
    ├── AAnimal.cpp
    ├── Dog.hpp
    ├── Dog.cpp
    ├── Cat.hpp
    ├── Cat.cpp
    ├── Brain.hpp
    ├── Brain.cpp
    ├── WrongAnimal.hpp
    ├── WrongAnimal.cpp
    ├── WrongCat.hpp
    └── WrongCat.cpp
```

- `ex00`: virtual `makeSound`와 non-virtual `makeSound` 비교
- `ex01`: `Brain`을 소유하는 `Dog`/`Cat`의 deep copy
- `ex02`: pure virtual function을 가진 abstract class

## 빌드 및 실행

### 빌드

```bash
cd ex00 && make
cd ../ex01 && make
cd ../ex02 && make
```

- 각 exercise 폴더에서 개별 Makefile을 실행한다.
- 실행 파일명은 각 폴더의 Makefile `NAME` 값인 `ex00`, `ex01`, `ex02`다.
- `ex02` Makefile에는 `-g -fsanitize=address` 옵션이 포함되어 있다.

### 실행

```bash
./ex00
./ex01
./ex02
```

- 각 exercise 폴더에서 빌드한 뒤 해당 실행 파일을 실행한다.
- 실행 결과는 각 `main.cpp`에 작성된 예제 흐름을 출력한다.
