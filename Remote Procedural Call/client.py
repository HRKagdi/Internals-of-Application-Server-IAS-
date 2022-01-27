import socket,ast
HOST = '127.0.0.1'
PORT = 9999
print()
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM) 
s.connect((HOST,PORT))
fname = 'foo'
dict={}
argsList=[4]
dict[fname]=argsList
s.sendall((str(dict)).encode())
res = s.recv(1024).decode()
print(res)
	