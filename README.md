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

## ☁️ Cloud-Based 원격 개발 환경 아키텍처

본 캡스톤 프로젝트는 로컬 하드웨어(LG Gram)의 성능 한계를 극복하고, 장소에 구애받지 않는 유연한 개발 환경을 위해 **Oracle Cloud Infrastructure(OCI) 기반의 무설치 원격 IDE 환경**을 구축했습니다.

### 🔹 Architecture 요약
- **Compute Server**: Oracle Cloud Ubuntu 22.04 LTS (ROS2 / LIMO 시뮬레이션 연산 전담)
- **Web IDE**: `code-server`를 활용한 VS Code 브라우저 렌더링
- **Network Security**: `Tailscale Funnel`을 이용한 Ingress 통제 및 HTTPS 자동 암호화

### 🔹 도입 배경 및 기술적 이점
1. **Zero-Install 접속**: 로컬 PC에 특정 프로그램(VS Code, VPN 등)을 설치할 필요 없이 웹 브라우저(Chrome, Edge 등)만으로 즉각적인 개발 환경 접근이 가능합니다.
2. **보안성 강화 (HTTPS & Auth)**: Tailscale Funnel을 통해 포트 개방 없이 안전한 터널링을 구현하였으며, HTTPS 기반의 통신 암호화와 자체 비밀번호 인증을 통해 공용 네트워크에서의 패킷 스니핑 및 무단 접근을 차단했습니다.
3. **분산 처리**: 무거운 Gazebo 시뮬레이션 물리 연산과 ROS2 빌드는 클라우드 서버 자원을 활용하고, 로컬 디바이스는 가벼운 시각화 렌더링만 담당하여 하드웨어 병목 현상을 방지했습니다.