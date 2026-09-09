# ☁️ Cloud-based ROS2 Distributed Development Environment

## 1. 프로젝트 개요 (Overview)
- **목적**: 로컬 Windows PC와 클라우드(Oracle Cloud Infrastructure) 간의 원격 로보틱스 개발 환경 구축
- **핵심 기술**: ROS2 Humble, Ubuntu 22.04 LTS, Tailscale VPN, VS Code Remote-SSH, Git/GitHub

## 2. 아키텍처 및 기술 스택 선택 이유 (Architecture & Rationale)

### 📌 클라우드 서버 (Oracle Cloud Infrastructure, Ubuntu 22.04)
- **선택 이유**: 로컬 PC 하드웨어 제약을 극복하고, 24시간 언제 어디서나 접근 가능한 독립된 Linux 서버 환경 확보
- **장점**: 고성능 연산 자원 활용 가능, 실제 로봇 배포 환경과 동일한 우분투 운영체제 보장
- **단점**: 네트워크 지연 발생 가능 및 초기 세팅 시간 소요

### 📌 보안 통신망 (Tailscale VPN)
- **선택 이유**: 공인 IP를 직접 노출하지 않고 방화벽 외부에서 안전하게 사설망 기반 SSH 접속 및 ROS2 통신 수행
- **장점**: 포트 포워딩 없이 WireGuard 기반 암호화 통신 보장, 백신 충돌 시 우회 가능
- **단점**: 백그라운드에서 VPN 앱이 구동되어 있어야 함

### 📌 원격 개발 환경 (VS Code Remote-SSH)
- **선택 이유**: 원격 서버의 CLI 환경과 로컬 PC의 GUI 편집 편의성 결합