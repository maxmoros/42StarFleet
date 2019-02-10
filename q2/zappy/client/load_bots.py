import socket
import os
from bossbot import BossBot
from workbot import WorkBot
import argparse

usage = '''Usage: ./client -n <team> -p <port> [-h <hostname>]
-n team_name
-p port
-h name of the host, by default it'll be localhost'''
parser = argparse.ArgumentParser(add_help=False, usage=usage)
parser.add_argument("-n", help="team to join on connect", required=True, dest='team')
parser.add_argument("-h", default='localhost', help="zappy server hostname", dest='host')
parser.add_argument("-p", "--port", type=int, help="zappy server port number", required=True)
args = parser.parse_args()

server_ip = args.host
comm_port = args.port
worker = False

print "Hello"
boss = BossBot(server_ip, comm_port, "a")
for i in range(5):
    pid = os.fork()
    if pid == 0:
        boss = None
        work = WorkBot(server_ip, comm_port, "a")
        worker = True
    else:
        break
if worker:
    print(WorkBot.team_inventory)
    work.work_loop()
else:
    boss.boss_loop()

while True:
    pass
