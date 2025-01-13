import socket
import hashlib
import time

def hash_string(string, algorithm='sha256'):
  
  hash_pass = hashlib.new(algorithm)
  hash_pass.update(string.encode('utf-8'))  # Encode string to bytes
  hex = hash_pass.hexdigest()
  return hex

FORMAT = 'UTF-8'



username = input("what is your username\n")
password = input("what is your password\n")

password = hash_string(password)

client = socket.socket()
client.connect(('127.0.0.1', 5430))

client.send(username.encode(FORMAT))
time.sleep(0.1)
client.send(password.encode(FORMAT))





m = client.recv(1024).decode(FORMAT)

print(m)

if m == "not a user":
  client.close()
  print("wrong username or password")