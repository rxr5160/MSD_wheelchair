import zmq
import time
import json

ctx = zmq.Context.instance()
socket = ctx.socket(zmq.PAIR)
socket.connect("tcp://*:4321")
print("connected")

def get_json_bytes(message: dict) -> bytes:
    json_stringified = json.dumps(message)
    print(json_stringified.encode('UTF-8'));
    return json_stringified.encode('UTF-8')

msg = {
    "State": "CONNECTED",
    "Reason": "System start"
}
socket.send(get_json_bytes(msg))
print(f"Sent {msg}")
time.sleep(5)

##json_str = socket.recv_json()
##print(f"Received {json_str}");

msg = {
    "MoveTo": 7
}
socket.send(get_json_bytes(msg))
print(f"Sent {msg}")

ret = socket.recv()
print(ret)

socket.close()
