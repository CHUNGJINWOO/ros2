# 🚨 트러블슈팅 일지 (Troubleshooting Log)

본 문서는 캡스톤 로보틱스 프로젝트 진행 중 발생한 기술적 문제와 해결 과정을 기록합니다. 향후 동일한 문제가 발생했을 때 참고하기 위한 목적입니다.

---

## 1. Tailscale MagicDNS와 국내 보안 프로그램(AhnLab) 충돌 문제

* **발생 현상 (Problem)**:
  - 원격 개발 환경 구축을 위해 오라클 클라우드 서버와 로컬 노트북(Gram)을 Tailscale VPN으로 연결하는 과정에서 문제가 발생함.
  - 노트북에 설치된 '안랩 세이프 트랜잭션(AhnLab Safe Transaction)'이 `hosts` 파일 변조 위험을 감지하여 경고를 띄우고 네트워크 연결을 차단함.

* **원인 분석 (Root Cause)**:
  - Tailscale의 MagicDNS 기능이 기기 간 이름 기반 통신을 지원하기 위해 로컬 PC의 네트워크 설정(`/etc/hosts` 및 DNS 라우팅)을 동적으로 변경함.
  - 국내 금융/보안 소프트웨어는 이러한 백그라운드 DNS 변경 동작을 악성코드의 파밍(Phishing) 시도로 오인하여 시스템 보호 차원에서 강제로 차단함.

* **해결 방안 (Solution)**:
  - Tailscale 클라이언트 설정 메뉴로 진입함.
  - **'Use Tailscale DNS settings' (MagicDNS 사용)** 옵션을 찾아 수동으로 체크 해제(비활성화)함.
  - DNS 라우팅 설정을 우회하여 보안 프로그램과의 충돌을 물리적으로 방지하고 정상적인 연결을 복구함.

* **인사이트 및 배운 점 (Lesson Learned)**:
  - 클라우드 인프라를 구축할 때 도구 자체의 기능뿐만 아니라, 로컬 디바이스에 상주하는 보안 프로그램과의 호환성을 반드시 고려해야 함을 배움.
  - 네트워크 통신 문제가 발생했을 때, 단순 재설치보다 DNS 및 포트 라우팅 등 백그라운드에서 일어나는 충돌 원인을 먼저 분석하는 것이 중요함을 깨달음.

  ## 클라우드 백업 인프라 구축 중 트러블슈팅

### Gazebo Classic이 Oracle ARM 인스턴스에서 설치조차 안 됨
**증상**: `apt-cache policy ros-humble-gazebo-ros-pkgs` → `N: Unable to locate package`
**원인**: 저장소 설정 실수가 아니라, Gazebo Classic(gazebo11)이 arm64 아키텍처용
공식 패키지를 애초에 제공하지 않음 ([gazebo-classic 이슈 #3282](https://github.com/gazebosim/gazebo-classic/issues/3282)).
**해결**: 시뮬레이션은 로컬(x86_64)에서, 클라우드는 저장 전용으로 역할 재배치.

### SSH 키 등록 시 Permission denied (publickey)
**증상**: `ssh-copy-id`로 새 키를 등록하려 했지만 실패.
**원인**: 오라클 우분투 이미지는 기본적으로 비밀번호 SSH 로그인이 꺼져 있음.
**해결**: 인스턴스 생성 시 받은 원래 개인키로 먼저 접속 → 그 세션 안에서 새
공개키를 `~/.ssh/authorized_keys`에 수동으로 추가.

### PowerShell 스크립트의 한글 주석이 깨지며 변수가 비어버림
**증상**: `Register-ScheduledTask : 'TaskName' 매개 변수... 인수가 null이거나 비어 있습니다.`
**원인**: Windows PowerShell 5.1은 `.ps1`이 UTF-8(BOM 없음)이면 한글을 시스템
로캘(cp949 등)로 잘못 해석해 파싱이 깨질 수 있음.
**해결**: 스크립트 주석을 전부 영어로 작성해 인코딩 문제를 원천 차단.

### WSL 터미널과 PowerShell 터미널 혼동
**증상**: WSL에 `cd $HOME\Downloads` 같은 PowerShell 문법을 입력해 에러.
**해결**: `hostname`으로 현재 터미널이 어디인지 먼저 확인하는 습관화.

### 심볼릭 링크 생성 실패
**증상**: `ln -s ~/scripts/05_backup.sh ~/limo_ws/backup.sh` → `No such file or directory`
**원인**: `~/limo_ws` 폴더 자체가 아직 없음.
**해결**: `mkdir -p ~/limo_ws/results/important`로 대상 폴더 먼저 생성.

### Object Storage의 "Region"과 블록 볼륨의 "가용성 도메인(AD)" 혼동
**증상**: rclone 설정 중 Region란에 `utrK:AP-TOKYO-1-AD-1`(AD 값)을 넣으려 함.
**해결**: rclone에는 Region 식별자(`ap-tokyo-1`)만 입력. AD는 하위 개념으로 무관.