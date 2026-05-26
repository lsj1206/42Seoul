# CPP Module 02

## 개요

- CPP Module 02는 `Fixed` class를 통해 Orthodox Canonical Form, 고정소수점 표현, 연산자 오버로딩을 단계적으로 구현하는 과제다.
- 실수처럼 보이는 값을 내부에서는 정수 raw value로 저장하고, 외부에서는 생성자, 변환 함수, 연산자를 통해 자연스럽게 학습한다.
- 같은 `Fixed` class를 확장해가며 객체 복사, 값 변환, 비교/산술/증감 연산의 형태를 정리한다.

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

- `ex00`은 Orthodox Canonical Form을 따르는 `Fixed` class를 구현한다.
- `Fixed` class는 내부 정수 raw value와 8bit fractional bits를 private member로 관리한다.
- `ex00`은 기본 생성자, 복사 생성자, 복사 대입 연산자, 소멸자, `getRawBits`, `setRawBits`를 제공한다.
- `ex01`은 `int`와 `float` 값을 받는 생성자, `toInt`, `toFloat`, `operator<<`를 추가한다.
- `ex02`는 비교 연산자, 산술 연산자, 전위/후위 증감 연산자, `min`/`max`의 const/non-const overload를 추가한다.

## 개념 정리

### Orthodox Canonical Form

- *Orthodox Canonical Form*은 C++ class가 기본 생성자, 복사 생성자, 복사 대입 연산자, 소멸자를 갖추는 기본 형태다.
- object의 생성, 복사, 대입, 소멸 흐름을 class 안에서 명확하게 표현하기 위한 관례라고 볼 수 있다.

### `static_cast`

- `static_cast<바꾸려는 타입>(대상)` 형태로 사용하는 C++의 명시적 형 변환 문법이다.
- 기본 자료형 사이의 변환처럼 compile time에 판단 가능한 변환에 사용할 수 있다.
- C style cast는 여러 종류의 변환을 넓게 허용할 수 있으므로, 변환 의도를 분명하게 드러내기 위해 `static_cast`를 사용한다.
- 고정소수점 값을 출력 가능한 실수 형태로 바꿀 때처럼, 타입 변환이 계산 결과에 직접 영향을 주는 경우 변환하려는 타입을 명확히 의식해야 한다.

### Fixed Point

- 컴퓨터는 값을 2진수로 다루기 때문에, 10진 소수 중 일부는 정확히 표현되지 않고 근사값으로 저장된다.
- 고정소수점은 소수점 위치를 고정해 두고, 하나의 정수 raw value를 정해진 배율로 해석해 소수처럼 다루는 표현 방식이다.
- 이 과제에서는 *fractional bits*를 8bit로 고정하기 때문에, raw value와 실제 값 사이의 배율이 `2^8`, 즉 `256`으로 정해진다.
- 값을 저장할 때는 실제 값에 `256`을 곱해 raw value로 만들고, 값을 꺼낼 때는 raw value를 `256`으로 나누어 실제 값에 가깝게 복원한다.
- 정수 입력은 `num << 8`처럼 왼쪽 shift를 사용해 내부 raw value로 변환할 수 있다.
- 실수 입력은 shift를 직접 적용할 수 없으므로 `num * 256` 뒤 `roundf`로 반올림해 내부 정수값으로 저장한다.

> *fractional bits*는 raw value에서 소수부를 표현하기 위해 확보해 둔 비트 수이자, 소수점 위치를 정하는 기준으로, `bits = 8`이면 raw value의 오른쪽에서 8bit 앞에 소수점이 있다고 해석한다.

## 문제 해결의 핵심

### `ex00` Orthodox Canonical Form

- `Fixed` object는 생성, 복사, 대입, 소멸 시점이 모두 명확해야 한다.
- 기본 생성자는 raw value의 초기 상태를 만들고, 복사 생성자와 복사 대입 연산자는 다른 object의 raw value를 현재 object로 옮긴다.
- raw value는 private member로 숨기고, 외부 접근은 `getRawBits`와 `setRawBits`를 통해 제한한다.

### `ex01` 고정소수점 변환

- 외부에서 받은 `int` 또는 `float` 값은 내부 raw value로 변환되어 저장되어야 한다.
- `int` 값은 fractional bits만큼 shift하고, `float` 값은 배율을 곱한 뒤 반올림해 소수부 손실을 줄인다.
- 출력과 변환 함수는 raw value를 직접 노출하지 않고, `toInt`, `toFloat`, `operator<<`를 통해 사용할 수 있는 값으로 복원한다.

### `ex02` 숫자처럼 다루는 인터페이스

- 비교 연산은 같은 배율로 저장된 raw value를 비교하면 되므로 내부 정수값 기준으로 판단할 수 있다.
- 산술 연산은 두 `Fixed` 값을 계산한 뒤 다시 `Fixed` object로 반환해야 연산 결과를 같은 class interface 안에서 계속 다룰 수 있다.
- 전위 증감은 값을 먼저 바꾼 뒤 반환하고, 후위 증감은 바뀌기 전 값을 반환한 뒤 현재 object를 변경해야 한다.
- `min`/`max`는 const object와 non-const object를 모두 받을 수 있어야 하므로 overload를 나누어 constness를 유지한다.

## 내가 구현한 방식

### `ex00/Fixed`

- `Fixed.hpp`는 `static const int bits = 8`과 `int RawBit`을 private member로 가진다.
- 기본 생성자는 `RawBit`을 0으로 초기화하고, 생성/복사/대입/소멸 흐름을 확인할 수 있도록 메시지를 출력한다.
- 복사 생성자는 `copy.getRawBits()`로 읽은 값을 `setRawBits`로 저장한다.
- 복사 대입 연산자는 자기 자신을 대입하는 경우를 확인한 뒤 raw value를 복사하고, 현재 object를 반환한다.
- `getRawBits`는 raw value를 반환하고, `setRawBits`는 전달받은 정수를 raw value에 저장한다.

### `ex01/Fixed`

- `Fixed(const int n)`은 `n << bits`로 정수 입력을 내부 raw value로 변환한다.
- `Fixed(const float n)`은 `roundf(n * 256)`으로 실수 입력을 8bit fractional scale에 맞춘 raw value로 변환한다.
- `toInt`는 `RawBit >> bits`로 정수 부분을 반환한다.
- `toFloat`는 `(float)RawBit / 256`으로 raw value를 실수 형태로 복원한다.
- `operator<<`는 `toFloat()` 결과를 stream에 전달해 `Fixed` object를 바로 출력할 수 있게 한다.

### `ex02/Fixed`

- 기본 생성자는 member initializer를 사용해 `RawBit(0)`으로 초기화한다.
- 비교 연산자는 `RawBit`과 비교 대상의 raw value를 비교하고, 결과를 `int`로 반환한다.
- 산술 연산자는 양쪽 값을 `toFloat()`로 변환해 계산한 뒤, 계산 결과로 새로운 `Fixed` object를 만든다.
- 전위 `++`/`--`는 현재 object의 `RawBit`을 먼저 변경한 뒤 변경된 값을 반환한다.
- 후위 `++`/`--`는 변경 전 raw value를 임시 object에 저장하고, 현재 object를 변경한 뒤 임시 object를 반환한다.
- 증감 연산은 `RawBit`을 1씩 바꾸므로 실제 값 기준으로는 `1 / 256`씩 증가하거나 감소한다.
- `min`/`max`는 비교 연산자를 사용해 더 작은 값 또는 더 큰 값을 고르고, 원본 object에 대한 reference를 반환한다.

## 폴더 구조

```text
.
├── ex00/
│   ├── Makefile
│   ├── main.cpp
│   ├── Fixed.hpp
│   └── Fixed.cpp
├── ex01/
│   ├── Makefile
│   ├── main.cpp
│   ├── Fixed.hpp
│   └── Fixed.cpp
└── ex02/
    ├── Makefile
    ├── main.cpp
    ├── Fixed.hpp
    └── Fixed.cpp
```

- `ex00`: Orthodox Canonical Form을 따르는 기본 `Fixed` class
- `ex01`: 정수/실수 변환과 stream 출력 interface
- `ex02`: 비교, 산술, 증감, `min`/`max` 연산자 오버로딩

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

## 참고 자료

[컴퓨터의 소수표현 방식 이해해보기](https://80000coding.oopy.io/5e8bf087-80c8-425a-9d78-9a6a67156073)
