import socket
import sql_connection as sq
import hashlib

def hash_string(string, algorithm='sha256'):
  
  hash_pass = hashlib.new(algorithm)
  hash_pass.update(string.encode('utf-8'))  # Encode string to bytes
  hex = hash_pass.hexdigest()
  return hex

try:
    sq.create_table("PERMISSIONS", "userName", "passwordHash", "level")
    sq.add_user("bob", hash_string("pizza"), 3)
    sq.add_user("bar", hash_string("barbur"), 0)
    sq.add_user("nir", hash_string("jaron"), 2)
except Exception as e:
    print(e)

FORMAT = 'UTF-8'

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind(('0.0.0.0', 5430))
server.listen()
client, address = server.accept()

print("connected")

username = client.recv(1024).decode(FORMAT)
password = client.recv(1024).decode(FORMAT)
print(f"Received username: {username}")
print(f"Received password: {password}")

if not sq.IsAuthorized(username, password):
    client.send("not a user".encode(FORMAT))
    print("connection closed")
    client.close()
else:
    client.send("u in".encode(FORMAT))
    print("client is in")

