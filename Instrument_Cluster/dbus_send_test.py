import socket
import random
import time

# 송신할 서버 주소와 포트 설정 (localhost:12345)
UDP_IP = "127.0.0.1"
UDP_PORT = 12345
count = 0
# 소켓 생성
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

while True:
    random_value = count % 260
    # 값을 문자열로 변환 후 전송
    message = str(random_value).encode('utf-8')
    sock.sendto(message, (UDP_IP, UDP_PORT))
    
    print(f"Sent: {random_value}")
    count += 1
    # 1초 대기
    time.sleep(0.1)
