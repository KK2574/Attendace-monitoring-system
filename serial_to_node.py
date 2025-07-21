import serial
import requests
import json

ser = serial.Serial('COM6', 9600)  # update COM port as needed

while True:
    if ser.in_waiting > 0:
        line = ser.readline().decode('utf-8').strip()
        print(f"Received: {line}")
        
        if "ID" in line:
            try:
                id_num = int(line.split("ID")[1].strip())
                payload = {'fingerprintId': id_num}
                res = requests.post('http://localhost:3000/api/attendance', json=payload)
                print("Response:", res.text)
            except Exception as e:
                print("Error:", e)
