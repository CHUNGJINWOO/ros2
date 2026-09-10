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

ROS2 원격 분산 통신 환경 구축 (Oracle Cloud - 로컬 WSL2)
1. 목적 (Objective)
원격지에 위치한 오라클 클라우드(Oracle Cloud) 서버와 로컬 환경의 Windows WSL2(Ubuntu) 간에 안정적인 ROS2 양방향 통신망을 구축하는 것입니다. 물리적으로 다른 네트워크에 있는 두 시스템이 마치 같은 공유기에 연결된 것처럼 서로의 ROS2 노드(Node)를 인식하고 데이터를 주고받도록 만드는 것을 목표로 합니다.

2. 해당 방식을 선택한 이유 (Reasoning)
ROS2 원격 통신을 구현하는 방법은 여러 가지가 있으나, 다음의 이유로 WSL2 내부 Tailscale 설치 및 Fast DDS 유니캐스트(Unicast) 프로파일 지정 방식을 채택했습니다.

Tailscale(VPN) 사용: 포트 포워딩이나 복잡한 공유기 방화벽 설정 없이, 안전한 P2P(Peer-to-Peer) 가상 사설망을 쉽게 구성할 수 있습니다.

WSL2 내부에 독립적 VPN 구축: Windows 호스트에만 Tailscale을 설치할 경우, Windows의 가상 라우터(NAT)가 외부에서 들어오는 UDP 데이터 패킷을 WSL2 내부로 전달하지 못하고 차단합니다. 이를 우회하기 위해 WSL2 우분투 환경 내부에 직접 Tailscale을 설치하여 서버와 1:1 직통 통신 터널을 뚫었습니다.

Fast DDS Peer 직접 지정: 일반적인 ROS2의 노드 탐색 방식인 '멀티캐스트(Multicast)'는 가상 사설망(VPN) 환경에서 차단되는 경우가 많습니다. 따라서 통신 미들웨어를 Fast DDS로 설정하고, 상대방의 IP를 명시적으로 가리키는 fastdds.xml 프로파일을 작성하여 멀티캐스트 없이도 서로를 찾을 수 있도록 설정했습니다.

3. 이를 통해 얻은 이득 (Benefits)
분산 제어 시스템 기반 마련: 로컬 컴퓨터의 연산 한계를 벗어나 클라우드 서버의 강력한 컴퓨팅 자원을 활용할 수 있습니다. 향후 무거운 연산(AI, SLAM, 네비게이션 등)은 클라우드에서 처리하고, 실제 모터 구동 및 센서 제어는 현장의 로컬 기기에서 수행하는 고도화된 로봇 시스템을 설계할 수 있습니다.

유연한 원격 제어: 물리적인 거리 제약이나 복잡한 네트워크 환경(공공 와이파이, 방화벽 등)의 방해를 받지 않고, 인터넷이 연결된 곳이라면 어디서든 로봇 시스템을 제어하고 모니터링할 수 있는 인프라를 확보했습니다.

4. 발생한 문제점 및 해결 방안 (Troubleshooting)
이슈 1: Windows NAT에 의한 수신 패킷 차단
증상: Ping 테스트는 성공하여 물리적 연결은 확인되었으나, ROS2 데이터는 수신되지 않았습니다.

원인: Windows에 설치된 Tailscale이 받은 데이터를 WSL2 내부로 넘겨주지 못했습니다.

해결 방안: WSL2 터미널에서 리눅스용 Tailscale을 직접 다운로드하고 설치하여 독립적인 네트워크 인터페이스(tailscale0)를 생성했습니다.

이슈 2: 미들웨어(Middleware) 설정 충돌
증상: VPN 환경이 정상 작동함에도 불구하고 노드 간 통신이 이루어지지 않았습니다.

원인: .bashrc 파일에 타 미들웨어인 Cyclone DDS가 강제 할당(export RMW_IMPLEMENTATION=rmw_cyclonedds_cpp)되어 있어, 기껏 작성한 Fast DDS 설정이 완전히 무시되고 있었습니다.

해결 방안: 양쪽 기기의 .bashrc에서 해당 구문을 삭제하고, 환경 변수를 초기화하여 기본 통신 방식인 Fast DDS가 정상 작동하도록 복구했습니다.

이슈 3: XML 설정 파일 파싱(Parsing) 에러
증상: 수신 노드(listener) 실행 시 [XMLPARSER Error]가 발생하며 프로그램이 종료되었습니다.

원인: fastdds.xml 파일 내의 프로파일 기본값 설정 속성명이 잘못 기재되었습니다. (is_default_true로 오기입)

해결 방안: 속성명을 공식 문법인 is_default_profile="true"로 수정하여 문법 오류를 해결했습니다.

5. 사용된 핵심 코드 및 설정 (Codes)
1) WSL2 내부 Tailscale 설치 및 실행
Bash
# 패키지 다운로드 및 설치
curl -fsSL https://tailscale.com/install.sh | sh

# Tailscale 실행 및 계정 연동
sudo tailscale up

# 부여된 Tailscale IP 확인
tailscale ip -4
2) 미들웨어 강제 설정 해제
Bash
# 환경 변수 강제 할당 해제
unset RMW_IMPLEMENTATION

# .bashrc 설정 갱신
source ~/.bashrc
3) Fast DDS 유니캐스트 프로파일 생성 (fastdds.xml)
로컬 환경에서 원격 클라우드 서버의 VPN IP(예: 100.127.79.18)를 직접 바라보도록 설정합니다.

XML
<?xml version="1.0" encoding="UTF-8" ?>
<profiles xmlns="http://www.eprosima.com/XMLSchemas/fastRTPS_Profiles">
    <participant profile_name="connect_profile" is_default_profile="true">
        <rtps>
            <builtin>
                <initialPeersList>
                    <locator>
                        <udpv4>
                            <address>100.127.79.18</address>
                        </udpv4>
                    </locator>
                </initialPeersList>
            </builtin>
        </rtps>
    </participant>
</profiles>
4) 설정 적용 및 테스트 실행
Bash
# 작성한 XML 파일을 시스템 환경 변수에 등록 (.bashrc에 추가)
echo "export FASTRTPS_DEFAULT_PROFILES_FILE=/home/$(whoami)/fastdds.xml" >> ~/.bashrc
source ~/.bashrc

# 클라우드 서버 터미널 (데이터 송신)
ros2 run demo_nodes_cpp talker

# 로컬 WSL2 터미널 (데이터 수신)
ros2 run demo_nodes_py listener