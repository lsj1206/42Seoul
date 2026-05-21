# born2beroot

## 개요

- 가상 머신 위에 리눅스 서버 환경을 구성하고, 보안 정책과 서비스 설정을 직접 확인하는 시스템 과제다.
- 코드 구현보다 OS 설치, 사용자/권한 관리, SSH, 방화벽, sudo, 모니터링 스크립트처럼 서버 운영의 기본 흐름을 익히는 과제다.
- 이 폴더에는 제출용 가상 머신 디스크 서명값인 `signature.txt`가 만 남아있다.

## 과제 요구사항 요약

- Debian 또는 Rocky 계열 가상 머신을 설치하고, 평가 기준에 맞는 호스트명과 사용자/그룹 구성을 설정한다.
- SSH는 지정 포트로만 접속하도록 제한하고, root 직접 접속은 막는 방향으로 구성한다.
- UFW 또는 firewalld, AppArmor 또는 SELinux 같은 보안 요소의 상태를 확인한다.
- sudo 정책은 인증 시도 제한, 경고 메시지, 로그 저장, TTY 요구 같은 규칙을 포함한다.
- 비밀번호 정책은 만료 주기, 최소 변경 기간, 복잡도 규칙 등을 설정한다.
- LVM 기반 파티션과 주기적으로 시스템 정보를 출력하는 `monitoring.sh`/cron 구성이 핵심 점검 대상이다.
- docs폴더에 born2beroot의 [Subject](./docs/Subject.md)와 [평가표](./docs/Evaluation.md)및 사용[명령어](./docs/Commands.md)가 자세히 정리되어 있다.

## 메모

- 정리된 내용이 많아 docs폴더에 [파일](./docs/Memo.md)로 정리했다.

## 참고 자료

- [born2beroot 아카이브](https://parkseunghan.notion.site/born2beroot-afdb78d74995456d9c91a4ae1be9874f)
- [Born2beroot 설치](https://github.com/ayoub0x1/born2beroot#Virtual-Machine)
- [Bonus 설치](https://nostressdev.tistory.com/12)
- [Bonus Sendmail](https://80000coding.oopy.io/705db1da-ea76-4875-a8b2-a971a18b9097#705db1da-ea76-4875-a8b2-a971a18b9097)
