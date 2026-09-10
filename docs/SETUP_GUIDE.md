# 🛠️ 원격 개발 환경 구축 가이드 (Setup Guide)

본 문서는 Oracle Cloud, Tailscale, 그리고 code-server를 활용한 로보틱스 원격 개발 환경의 단계별 구축 명령어와 설정 방법을 기록합니다.

---

## 1. Oracle Cloud Infrastructure (OCI) 서버 프로비저닝
- **OS**: Ubuntu 22.04 LTS
- **네트워크 보안**: VCN(가상 클라우드 네트워크) 설정 시 SSH(22) 포트만 최소한으로 개방하여 초기 보안을 확보했습니다.
- **초기 접속 명령어**: OCI 콘솔에서 발급받은 프라이빗 키(`.key`)를 사용하여 로컬 환경에서 서버로 최초 접속을 수행했습니다.
  ```bash
  ssh -i <private_key.key> ubuntu@<OCI_공인_IP>

# 보안 통신망 (Tailscale VPN) 구축

# 1. Tailscale 자동 설치 스크립트 실행
curl -fsSL [https://tailscale.com/install.sh](https://tailscale.com/install.sh) | sh

# 2. 기기 등록 및 VPN 네트워크 실행
sudo tailscale up

# 로컬 PC (VS Code Remote-SSH) 연결 설정

Host ros2-server_oracle
    HostName <Tailscale_할당_IP>
    User ubuntu
    IdentityFile ~/.ssh/oci_private_key.key

# 무설치 웹 IDE (code-server) 및 HTTPS 접근 구축

# 1. code-server 설치
curl -fsSL [https://code-server.dev/install.sh](https://code-server.dev/install.sh) | sh

# 2. 백그라운드 서비스 활성화 및 서버 시작
sudo systemctl enable --now code-server@$USER

# code-server 보안 설정
bind-addr: 127.0.0.1:8080
auth: password
password: <본인만의_안전한_비밀번호>
cert: false

# Tailscale Funnel을 이용한 외부 웹 접속 개방
sudo tailscale funnel 8080

<Steps>
  <Step subtitle="깃허브 전송" title="3단계: 깃허브(GitHub)에 전체 파일 업로드(커밋 및 푸시)">
    - 문서 저장을 마친 후, 왼쪽의 **가지 모양 아이콘(소스 제어)**을 누릅니다.
    - 새로 만든 `docs/SETUP_GUIDE.md`를 포함하여 변경된 모든 파일 옆의 **`+` 기호(변경 내용 스테이징)**를 눌러 위로 올립니다. (단, `build`, `install` 폴더 안의 임시 파일은 제외합니다.)
    - 메시지 입력 칸에 `docs: 원격 개발 환경 구축 세부 가이드 및 소스 코드 주석 추가`라고 적습니다.
    - **[커밋 및 동기화]** (또는 푸시) 버튼을 눌러 깃허브에 최종 반영합니다.
  </Step>
</Steps>

<Elicitations message="구축 가이드 문서 작성 및 깃허브 업로드를 성공적으로 완료하셨습니까?">
  <Elicitation label="빌드 임시 파일 숨기기 (.gitignore)" query="깃허브에 업로드할 때 계속 거슬리는 19개의 build, install 임시 파일들을 안 보이게 숨기는 방법(.gitignore)을 알려줘."/>
  <Elicitation label="ROS2 분산 통신 (Domain ID) 설정" query="문서화 작업과 깃허브 업로드는 완벽하게 끝났어. 이제 본격적으로 클라우드 서버와 노트북 간의 ROS2 분산 통신 설정을 진행해 줘."/>
</Elicitations>
