import socket
from threading import Thread

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind(('0.0.0.0', 8089))
s.listen(20)

state = 0
conns = []
exiting = False

def accept_conns():
  while 1:
    try:
      conn, addr = s.accept()
    except socket.error:
      break
    print(f"Received connection from {addr}")
    conns.append(conn)

t = Thread(target=accept_conns)
t.start()

try:
  while not exiting:
    input()
    state ^= 1
    print(f"state: {state}", end="")
    data = str(state).encode('ascii')
    alive = []
    for conn in conns:
        try:
          conn.sendall(data)
          alive.append(conn)
        except BrokenPipeError:
          pass
    conns = alive
except KeyboardInterrupt:
  s.close()
