# Minishell

## 개요

- `minishell`은 사용자의 입력을 해석해 built-in 명령어 또는 외부 프로그램을 실행하는 작은 셸을 구현하는 2인 팀 프로젝트다.
- 핵심은 입력 문자열을 토큰화, 확장, 파싱, 실행 단계로 나누고, pipe, redirection, 환경 변수, signal처럼 실제 셸에서 맞물려 동작하는 기능을 일관된 실행 흐름으로 처리하는 것이다.

## 팀 프로젝트와 담당 범위

- 이 과제는 2인 팀 프로젝트로 진행했다.
- 전체 프로그램은 `readline -> lexer -> expand -> parser -> execute` 흐름으로 구성되어 있다.
- 내가 맡은 파트는 built-in 명령어 구현이다.
- built-in 명령어는 외부 실행 파일과 달리 현재 셸의 상태를 직접 바꿀 수 있으므로, 환경 변수 저장 구조와 부모/자식 프로세스 실행 위치를 함께 고려해야 했다.

## 과제 요구사항

### Mandatory

- GNU Readline을 사용해 프롬프트를 띄우고 command history를 관리한다.
- quote가 닫히지 않은 입력이나 지원 범위 밖의 특수문자(`\`, `;`)는 해석하지 않는다.
- single quote는 내부 meta character 해석을 막고, double quote는 `$` 확장만 허용하는 방식으로 처리한다.
- `<`, `>`, `<<`, `>>` redirection을 구현한다.
- `<<` heredoc은 delimiter가 나올 때까지 입력을 읽으며, history 갱신은 요구되지 않는다.
- `|` pipe를 구현해 앞 명령의 표준 출력을 다음 명령의 표준 입력으로 연결한다.
- `$VAR` 환경 변수와 `$?` 최근 foreground pipeline의 종료 상태를 확장한다.
- `Ctrl+C`, `Ctrl+D`, `Ctrl+\`가 interactive bash와 비슷하게 동작하도록 처리한다.
- `echo -n`, `cd`, `pwd`, `export`, `unset`, `env`, `exit` built-in을 구현한다.

## 개념 정리

### Shell과 실행 흐름

- shell은 사용자 입력을 읽고 해석한 뒤, 내부 명령을 직접 처리하거나 외부 프로그램을 실행하는 프로그램이다.
- 입력 문자열은 그대로 실행할 수 없기 때문에 token, syntax tree, process 실행 단위로 단계적으로 변환해야 한다.
- 이 과제에서는 입력 처리, 확장, 파싱, 실행, 종료 상태 관리가 하나의 흐름으로 연결된다.

### Built-in과 외부 명령어

- built-in은 shell 내부에서 직접 처리하는 명령어이고, 외부 명령어는 `PATH` 검색 또는 직접 경로를 통해 `execve`로 실행하는 프로그램이다.
- `echo`, `pwd`, `env`처럼 출력 중심인 built-in도 있지만, `cd`, `export`, `unset`, `exit`처럼 현재 shell 상태를 바꾸는 built-in도 있다.
- 현재 shell 상태를 바꾸는 명령어는 실행 위치가 중요하다. 부모 프로세스에서 실행해야 변경 사항이 shell에 남고, 자식 프로세스에서 실행하면 변경 사항은 자식 프로세스 안에서만 끝난다.

### 환경 변수와 확장

- 환경 변수는 `key=value` 형태의 문자열 집합이며, shell은 이를 명령 실행 환경과 문자열 확장에 사용한다.
- `$VAR`는 변수 값으로 치환되고, `$?`는 최근 foreground pipeline의 종료 상태로 치환된다.
- quote 규칙에 따라 확장 여부가 달라진다. single quote 안에서는 meta character 해석을 막고, double quote 안에서는 `$` 확장을 허용한다.

### Signal과 Terminal 입력

- signal은 프로세스에 비동기 이벤트를 전달하는 방식이며, interactive shell에서는 입력 대기 중인지, 자식 프로세스 실행 중인지, heredoc 입력 중인지에 따라 처리 방식이 달라진다.
- `Ctrl+C`는 `SIGINT`, `Ctrl+\`는 `SIGQUIT`에 대응하지만, `Ctrl+D`는 signal이 아니라 terminal canonical mode에서 EOF 입력으로 처리된다.
- terminal의 `ECHOCTL` flag를 조정하면 `^C` 같은 제어 문자 표시 방식을 제어할 수 있다.

## 문제 해결의 핵심

### 부모/자식 프로세스 실행 경계

- 외부 명령어는 `fork` 이후 자식 프로세스에서 `execve`로 실행한다.
- pipe가 있는 명령도 각 command가 독립적인 process 흐름을 가지므로 자식 프로세스에서 실행된다.
- 반면 pipe가 없는 built-in은 부모 프로세스에서 실행해야 `cd`, `export`, `unset`, `exit`처럼 shell 상태를 바꾸는 결과가 유지된다.

### 환경 상태 관리

- shell은 실행 중 환경 변수 목록을 계속 갱신해야 한다.
- `export`, `unset`, `cd`는 환경 변수 저장소를 직접 바꾸고, 외부 명령어 실행 시에는 현재 저장소를 `execve`에 넘길 `envp` 배열로 변환해야 한다.
- key 유효성 검사, value 유무, 정렬 출력처럼 built-in마다 요구하는 환경 변수 처리 규칙도 분리해야 한다.

### Signal과 종료 상태

- interactive shell은 signal을 받았을 때 프롬프트를 복구해야 하고, 자식 프로세스 실행 중에는 자식의 종료 상태를 shell의 상태로 반영해야 한다.
- heredoc 입력 중에는 일반 프롬프트 대기 상태와 다른 signal 처리가 필요하다.
- signal 종료는 `128 + signal number` 형태로 종료 상태에 반영한다.

## 내가 구현한 방식

### 구조체 역할

- `t_shell`: terminal 설정, 환경 변수 hashtable, 자식 process pid queue를 저장한다.
- `t_process`: command 실행에 필요한 `argv`, redirection fd, pipe fd, pipe 개수, 실행 flag를 저장한다.
- `t_tree`: parser가 만든 실행 tree node이며, pipe, redirection, command 정보를 표현한다.
- `t_token`: lexer가 만든 token이며, 문자열, redirection, pipe, EOF 같은 입력 단위를 표현한다.
- `t_hashtable`: 환경 변수를 key 기준으로 저장하고 검색, 삽입, 삭제, 병합에 사용한다.

### Shell 실행 흐름

```text
readline
  -> lexer
  -> expand
  -> parser
  -> execute
  -> builtins 또는 execve
```

- `run_shell`은 `readline("$ ")`으로 입력을 받고 history에 저장한다.
- `lexer`는 입력 문자열을 quote, blank, redirection, pipe, string token으로 나눈다.
- `expand`는 token 문자열에 대해 quote 규칙과 `$VAR`, `$?` 확장을 처리한다.
- `parse`는 token list를 pipe, redirection, command node로 구성된 tree로 변환한다.
- `execute`는 tree를 순회하며 pipe, redirection, heredoc, process 실행을 준비한다.

### Built-in 분기

- `is_builtin`은 현재 command가 `cd`, `echo`, `env`, `exit`, `export`, `pwd`, `unset` 중 하나인지 판별한다.
- `builtins_check`는 command 이름에 따라 실제 built-in 함수를 호출하는 dispatcher 역할을 한다.
- pipe가 없는 built-in은 `execute_builtin`에서 부모 프로세스가 직접 실행한다.
- pipe가 있거나 외부 명령어인 경우에는 `execute_process`가 `fork`로 자식 프로세스를 만들고, 자식에서 built-in 또는 외부 명령어를 실행한다.

### Built-in 구현

- `pwd`는 `getcwd(NULL, 0)`로 현재 작업 디렉터리를 얻어 출력한다.
- `cd`는 인자가 없거나 `~`인 경우 `HOME`, `-` 또는 `--`인 경우 `OLDPWD`, 그 외에는 전달된 경로로 이동한다.
- `cd` 성공 후에는 기존 경로를 `OLDPWD`, 이동 후 경로를 `PWD`로 갱신한다.
- `echo`는 인자를 공백으로 구분해 출력하고, `-n`, `-nnn`처럼 `n`이 반복되는 option은 newline 생략 옵션으로 처리한다.
- `export`는 인자가 없으면 `declare -x` 형식으로 정렬된 환경 변수를 출력하고, 인자가 있으면 key 유효성을 검사한 뒤 hashtable에 삽입하거나 갱신한다.
- `unset`은 key 유효성을 검사한 뒤 해당 환경 변수를 삭제한다.
- `env`는 value가 존재하는 환경 변수만 `key=value` 형식으로 출력하며, 현재 구현에서는 추가 인자를 에러로 처리한다.
- `exit`는 인자가 없으면 직전 종료 상태를 사용하고, 숫자 인자가 있으면 `0~255` 범위로 맞춰 종료한다.

### 환경 변수 저장 방식

- 환경 변수는 `t_hashtable` 배열에 저장한다.
- `init_env`는 `envp`를 `key=value`로 나누어 hashtable에 넣고, `OLDPWD`를 제거한 뒤 `SHLVL`을 갱신한다.
- `export`, `unset`, `cd`는 hashtable을 직접 수정한다.
- 외부 명령어를 실행할 때는 `hashtable_merge`로 현재 환경을 `execve`에 전달할 배열 형태로 변환한다.

### Pipe와 Redirection 실행

- `execute_pipe`는 pipe node를 기준으로 fd 쌍을 만들고, 왼쪽 command의 출력과 오른쪽 command의 입력을 연결한다.
- `execute_redir`는 `<`, `>`, `<<`, `>>` node를 순회하며 process의 입력/출력 fd를 갱신한다.
- `execute_heredoc`은 별도 child process에서 delimiter가 나올 때까지 입력을 읽고, 그 결과를 pipe fd로 연결한다.
- `dup_process_fd`는 준비된 redirection fd 또는 pipe fd를 표준 입력/출력에 연결한다.
- `close_other_pipes`와 `close_pipeline`은 사용하지 않는 fd를 정리해 pipe 대기 문제가 생기지 않도록 한다.

### Signal과 Terminal 처리

- `signal_init`은 프롬프트 대기, 자식 프로세스 실행, heredoc 입력, 부모 대기 상태에 따라 `SIGINT` 처리 방식을 다르게 설정한다.
- 프롬프트 대기 중 `Ctrl+C`가 들어오면 현재 입력 줄을 비우고 프롬프트를 다시 표시한다.
- 자식 프로세스 실행 중 `SIGINT`가 들어오면 종료 상태를 `128 + signal number` 흐름으로 반영한다.
- `Ctrl+\`와 `SIGTERM`은 현재 shell에서 무시하도록 설정한다.
- `Ctrl+D`는 `readline`이 `NULL`을 반환하는 EOF 입력으로 처리하고, `exit`를 출력한 뒤 shell을 종료한다.
- 실행 전후로 terminal의 `ECHOCTL` flag를 조정해 제어 문자 표시 방식을 바꾼다.

## 폴더 구조

```text
.
├── includes/
├── libft/
├── srcs/
│   ├── builtins/
│   ├── debug/
│   ├── execute/
│   ├── expand/
│   ├── hashtable/
│   ├── lexer/
│   ├── parser/
│   ├── shell/
│   └── tree/
└── Makefile
```

- `includes`: module별 header와 공용 구조체 정의
- `libft`: 과제에서 재사용하는 기본 C 함수 구현
- `srcs/builtins`: built-in 명령어와 환경 변수 key 검증, 정렬 유틸리티
- `srcs/execute`: pipe, redirection, heredoc, process 실행과 fd 정리
- `srcs/expand`: quote와 환경 변수 확장
- `srcs/lexer`: 입력 문자열 token화
- `srcs/parser`: token list를 실행 tree로 변환
- `srcs/hashtable`: 환경 변수 저장소
- `srcs/shell`: readline loop, signal, terminal 설정
- `srcs/tree`: parser tree 생성과 해제

## 빌드 및 실행

### 빌드

```bash
make
```

- 결과물은 `minishell` 실행 파일이다.
- Makefile은 Homebrew 경로의 readline header/library를 참조한다.

### 실행

```bash
./minishell
```

- 실행 후 `$ ` 프롬프트에서 명령어를 입력한다.

### 확인 예시

```bash
echo -n hello
pwd
cd ..
export A=1
env
unset A
echo $?
echo hi | cat
cat << EOF
hello
EOF
```

## 참고 자료

- [특정 시그널을 계속 무시하게 하는 방법](http://itqomcom.blogspot.com/2018/11/linuxunix-signal.html)
- [Ctrl+D 조작을 위한 terminal 설정 변경](https://80000coding.oopy.io/13bd7bb7-3a7f-4b51-b84a-905c47368277)
