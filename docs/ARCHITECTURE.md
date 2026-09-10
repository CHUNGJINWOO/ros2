# 🏛️ 시스템 아키텍처 및 기술 스택 선정 이유 (Architecture & Rationale)

본 문서는 캡스톤 로보틱스 프로젝트에서 구축한 클라우드 분산 개발 환경의 아키텍처 설계와 기술 스택 선택 배경을 기록합니다.

---

## 1. 전체 시스템 구성도 (System Architecture)
- **Cloud Server (OCI)**: Oracle Cloud Infrastructure (Ubuntu 22.04 LTS) 기반의 원격 서버로, 무거운 ROS2 빌드 및 시뮬레이션 연산을 담당합니다.
- **Local Client (LG Gram)**: 사용자 개발용 로컬 노트북으로, 웹 브라우저(`code-server`)를 통해 원격 개발 환경에 접속하고 가벼운 시각화 및 제어 명령을 내립니다.
- **Secure Network (Tailscale)**: 공인 IP 노출 없이 WireGuard 기반 암호화 통신을 제공하여 사설망 환경을 구축합니다.

## 2. 기술 스택별 선택 이유 (Rationale)

### 📌 Oracle Cloud Infrastructure (OCI)
- **선택 이유**: 고성능 리눅스 서버 환경을 비용 부담 없이 구축할 수 있으며, 24시간 언제 어디서나 접근 가능한 독립된 개발 공간을 확보하기 위함입니다.
- **장점**: 실제 로봇 배포 환경과 동일한 우분투 운영체제를 보장하며, 로컬 하드웨어의 성능 한계를 극복합니다.

### 📌 Tailscale VPN & Funnel
- **선택 이유**: 공유기 포트 포워딩 설정 없이 방화벽 외부에서 안전하게 사설망 기반 SSH 접속 및 ROS2 노드 간 통신을 수행하기 위함입니다.
- **장점**: HTTPS 자동 암호화와 자체 비밀번호 인증을 통해 외부 패킷 스니핑을 차단합니다.

### 📌 ROS2 Humble & code-server
- **선택 이유**: Ubuntu 22.04 LTS와 가장 안정적으로 연동되는 ROS2 장기 지원 버전이며, 별도의 무거운 프로그램 설치 없이 웹 브라우저로 즉시 개발 가능한 환경을 구축했습니다.