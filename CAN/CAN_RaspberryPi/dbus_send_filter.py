import socket
import time
import can

# Set the server address and port for sending (localhost:12345)
UDP_IP = "127.0.0.1"
UDP_PORT = 12345

# Create a socket (UDP)
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Set the CAN interface
can_interface = 'can0'

# Initialize the CAN Bus
bus = can.interface.Bus(channel=can_interface, interface='socketcan')

# 칼만 필터 초기값 설정
Q = 1.0  # 프로세스 노이즈 공분산
R = 1.0  # 측정 노이즈 공분산
P = 1.0  # 오차 공분산
x_est_last = 0  # 이전 상태 추정치

# 칼만 필터 함수
def kalman_filter(measurement, x_est_last, P):
    # Prediction
    x_pred = x_est_last  # 예측된 상태 (이전 상태 그대로 유지)
    P_pred = P + Q       # 오차 공분산 예측

    # Update
    K = P_pred / (P_pred + R)  # 칼만 이득 계산
    x_est = x_pred + K * (measurement - x_pred)  # 새로운 상태 추정치
    P = (1 - K) * P_pred  # 오차 공분산 업데이트

    return x_est, P

while True:
    # Receive a CAN message
    message = bus.recv()
    
    # Process the message if the data length is 8 bytes
    if message is not None and len(message.data) == 8:
        
        # Get RPM data from CAN message
        rpm_m = int(message.data[0])
        rpm_s = float(message.data[1]) * 0.01
        rpm = int((rpm_m + rpm_s) * 50) // 5
        
    # 칼만 필터 적용
    filtered_rpm, P = kalman_filter(rpm, x_est_last, P)
    x_est_last = filtered_rpm  # 현재 추정값을 다음 루프에서 사용
    
    # 필터링된 값을 100ms마다 전송
    udp_message = str(int(filtered_rpm)).encode('utf-8')  # Convert the RPM data to a string
    sock.sendto(udp_message, (UDP_IP, UDP_PORT))
    
    print(f"Sent (filtered RPM): {int(filtered_rpm)} | Raw RPM: {rpm}")
    
    # 100ms 대기
    time.sleep(0.1)

