import socket
import sys
import time
import os
import random
import time
from gnl import get_next_line
from gnl import clear_gnl


team_name = "banana"
server_ip = "0.0.0.0"
comm_port = 5555
open_seats = 0
map_x = 0
map_y = 0
level = 1
ticks_to_hatch = -1;
inventory = [0, 0, 0, 0, 0, 0, 0]
bot_zero = True
conn = 0
tick_len = 0
home_start = False
resource_table =   [[1, 0, 0, 0, 0, 0],
                    [1, 1, 1, 0, 0, 0],
                    [2, 0, 1, 0, 2, 0],
                    [1, 1, 2, 0, 1, 0],
                    [1, 2, 1, 3, 0, 0],
                    [1, 2, 3, 0, 1, 0],
                    [2, 2, 2, 2, 2, 1]]
task_table = [True, True, True, True, True, True]

def print_bot():
    print("Bot:\n  team: {}".format(team_name))
    print("  open_seats: {}".format(open_seats))
    print("  map_x = {}".format(map_x))
    print("  map_y = {}".format(map_y))

def is_message(data):
    if data.split(' ', 1)[0] == "message":
        return True
    return False

def message_data(data):
    return data.split(',', 1)[1]

def expected_reply(msg):
    data = get_next_line(conn, 1)
    if data == msg:
        return True
    return False

def wipe_child():
    bot_zero = True
    open_seats = 0
    map_x = 0
    map_y = 0
    conn = 0

def stupid_ai():
    stupid_ai = random.randint(1, 8)
    if stupid_ai == 1:
        conn.send("right\n")
    elif stupid_ai == 2:
        conn.send("left\n")
    else:
        conn.send("advance\n")

def fork_bot():
    newpid = os.fork()
    if newpid == 0:
        clear_gnl()
        wipe_child()
        return (0)
    return (1)

def is_boss():
    global bot_zero
    global tick_len
    global home_start
    start = time.time()
    conn.send("broadcast bot_zero? %s\n" % team_name)
    while not expected_reply("ok"):
        pass
    end = time.time()
    tick_len = (end - start) / 7
    print "tick length = %f sec" % tick_len
    while (time.time() - end) < tick_len * 21:
        data = get_next_line(conn)
        if data:
            print "server: " + data
        if is_message(data):
            data = data.split(',', 1)[1]
            if data.split(',', 1)[0] == ("bot_zero " + team_name + " false"):
                if data.split(',', 1)[1] == "true":
                    home_start = True
                bot_zero = False
                print("NOT BOT ZERO")
                break
    if bot_zero:
        print("I AM BOT ZERO!")
        if open_seats > 1:
            home_start = False

def boss_feed():
    conn.send("take food\n")
    data = get_next_line(conn, 1)
    while data != "ko":
        if data == "ok":
            conn.send("take food\n")
        data = get_next_line(conn, 1)

def boss_incant():
    boss_feed()
    conn.send("incantation\n");
    data = get_next_line(conn, 1)
    while data.split(':', 1)[0] != "current level ":
        data = get_next_line(conn, 1)
    level = int(data.split(' ', 3)[3])
    print "\t\t\tTEAM %s IS NOW LVL %d!!!!!" % (team_name, level)
    while True:
        pass

def boss_reply(data):
    if bot_zero and data.split(' ', 1)[0] == "message":
        data = data.split(',', 1)[1]
        if data == ("bot_zero? " + team_name):
            print "\tNo, I'm the boss..."
            send = "broadcast bot_zero %s false," % team_name
            if home_start:
                send += "true\n"
            else:
                send += "false\n"
            conn.send(send)

def boss_callhome(data):
    global open_seats
    if is_message(data):
        if message_data(data) == "%s boss, I'm home!" % team_name:
            open_seats -= 1
            if open_seats == 1:
                home_start = True
                boss_incant()

def boss_ai():
    if not home_start:
        print "BOSS: come home! (%d)" % (open_seats - 1)
        conn.send("broadcast come home %s\n" % team_name)

def boss_loop():
    while True:
        data = ''
        boss_ai()
        while data != "ok":
            if data:
                print("server: " + data)
                boss_reply(data)
            if not home_start:
                boss_callhome(data)
            data = get_next_line(conn)

def worker_task():
    global resource_table
    global level
    global task_table
    for x in range(6):
        if resource_table[level][x] > 0:
            task_table[x] = True
        else:
            task_table[x] = False

def worker_drop_goods():
    pass

def worker_smarthome():
    conn.send("take food\n")
    data = get_next_line(conn, 1)
    while data != "ok" and data != "ko":
        if is_message(data):
            if message_data(data) == "%s got linemate\n" % team_name:
                task_table[0] = False
        data = get_next_line(conn, 1)
    if data == "ok":
        inventory[6] += 1
    if task_table[0]:
        conn.send("take linemate\n")
        data = get_next_line(conn, 1)
        while data != "ok" and data != "ko":
            if is_message(data):
                if message_data(data) == "%s got linemate\n" % team_name:
                    task_table[0] = False
            data = get_next_line(conn, 1)
        if data == "ok":
            conn.send("broadcast %s got linemate\n" % team_name)
            task_table[0] = False
            inventory[0] += 1
            data = get_next_line(conn)
            while data != "ok":
                data = get_next_line(conn)
    conn.send("advance\n")

def worker_get_home():
    global home_start
    global inventory
    while not home_start:
        data = get_next_line(conn, 1)
        if is_message(data):
            if data.split(',', 1)[1] == "come home %s" % team_name:
                home_dir = int(data.split(' ', 1)[1].split(',', 1)[0])
                if home_dir == 0:
                    home_start = True
                elif home_dir == 1 or home_dir == 2 or home_dir == 8:
                    worker_smarthome()
                elif home_dir == 3 or home_dir == 4 or home_dir == 5:
                    conn.send("left\n")
                elif home_dir == 6 or home_dir == 7:
                    conn.send("right\n")
                while home_start is False and data != "ok":
                    data = get_next_line(conn, 1)
    if inventory[0]:
        conn.send("put linemate\n")
        while not expected_reply("ok"):
            pass
        inventory[0] -= 1
    while inventory[6] > 2:
        conn.send("put food\n")
        while not expected_reply("ok"):
            pass
        inventory[6] -= 1
    if inventory[6] < 2:
        conn.send("take food\n")
        while not expected_reply("ok"):
            pass
    conn.send("broadcast %s boss, I'm home!\n" % team_name)
    while not expected_reply("current level : %d\n" % (level + 1)):
        pass

def worker_loop():
    global home_start
    if not home_start:
        worker_get_home()
    while True:
        data = ''
        stupid_ai()
        while data != "ok":
            if data:
                print("server: " + data)
            data = get_next_line(conn)

def assign_bot():
    thing_counter = 0
    is_boss()
    if open_seats > 1 and not fork_bot():
        init_comms()
    else:
        worker_task()
        if bot_zero:
            boss_loop()
        else:
            worker_loop()

def valid_ip_port(address):
    try:
        socket.inet_pton(socket.AF_INET6, address)
    except socket.error:
        return False
    return True

def init_comms():
    global team_name
    global open_seats
    global map_x
    global map_y
    global conn
    if len(sys.argv) > 1:
        team_name = sys.argv[1]
    conn = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    conn.connect((server_ip, comm_port))
    if not expected_reply("WELCOME"):
        print("Sorry, wrong number.\n")
        sys.exit()
    conn.send(team_name + "\n")
    open_seats = int(get_next_line(conn, 1))
    (map_x, map_y) = get_next_line(conn, 1).split(' ', 1)
    map_x = int(map_x)
    map_y = int(map_y)
    print_bot()
    assign_bot()
    
def init_bot():
    if (not server_ip and not comm_port):
        if len(sys.argv) == 4:
            (team_name, server_ip, comm_port) = sys.argv[1:3]
        else:
            print("Invalid bot arguments.\n")
            exit()

if __name__ == "__main__":
    init_comms()
