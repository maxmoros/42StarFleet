import socket
from random import randint
class WorkBot:
    """Work Work..."""
    team_name = "banana"
    tick_len = 0.0
    conn = 0
    buff = ''
    line = ''
    map_x = 0
    map_y = 0
    north = -1
    bot_number = -1
    food_min = 2
    level = 1
    msg_dir = -1
    bots_active = 0
    bots_away = 0
    can_move = True
    bots_unique = False
    come_home = False
    bots_home = False
    forager = False
    scavenger = False
    inventory = [0,0,0,0,0,0,0]
    tile_inventory = [0 ,0 ,0 ,0 ,0 ,0 ,0]
    team_inventory = [0 ,0 ,0 ,0 ,0 ,0 ,0]
    target = [0, 0, 0, 0, 0, 0, 0]
    nums = [0, 0, 0, 0, 0]
#    requirements_met = False
    requirements =     [[1, 0, 0, 0, 0, 0, 16],
                        [1, 1, 1, 0, 0, 0, 20],
                        [2, 0, 1, 0, 2, 0, 20],
                        [1, 1, 2, 0, 1, 0, 20],
                        [1, 2, 1, 3, 0, 0, 20],
                        [1, 2, 3, 0, 1, 0, 20],
                        [2, 2, 2, 2, 2, 1, 20]]
    tasks = [True, True, True, True, True, True, True]
    resources = ["linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame", "food"]

    def __init__(self, server_ip="localhost", comm_port=5555, team="banana"):
        self.team_name = team
        self.init_comm(server_ip, comm_port)
        self.print_bot()

    def work_loop(self):
        print "WORK: working"
        self.bots_home = False
        self.get_home()
        self.wait_on_bots()
        self.can_move = True
        while True:
            if self.can_move:
                if self.come_home:
                    self.come_home = False
                    self.get_home()
                    self.wait_on_bots()
                if self.forager:
                    self.forager = False
                    self.bots_home = False
                    self.go_forage()
                if self.scavenger:
                    self.scavenger = False
                    self.bots_home = False
                    self.go_scavenge()
            else:
                pass
            self.get_next_line()
            self.decode_msg(self.line)
            # IS THERE AN ELSE?

    def print_bot(self):
        print("WorkBot:\n  team: %s" % self.team_name)
        print("  open_seats: %s" % self.bots_active)
        print("  map_x: %s" % self.map_x)
        print("  map_y: %s" % self.map_y)

    def init_comm(self, server_ip, comm_port):
        self.conn = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.conn.connect((server_ip, comm_port))
        self.get_next_line()
        if self.line != "WELCOME":
            print("ERROR: Sorry, wrong number...\n")
            while True:
                pass
        self.conn.send("%s\n" % self.team_name)
        self.bots_active = int(self.get_next_line())
        (self.map_x, self.map_y) = self.get_next_line().split(' ', 1)
        self.map_x = int(self.map_x)
        self.map_y = int(self.map_y)

    def get_next_line(self, blocking=1):
        if blocking == 1 and not self.buff:
            self.conn.setblocking(blocking)
        else:
            self.conn.setblocking(0)
        while '\n' not in self.buff:
            try:
                self.buff += self.conn.recv(256)
            except:
                breas
        if '\n' in self.buff:
            (self.line, self.buff) = self.buff.split('\n', 1)
        else:
            self.line = self.buff
            self.buff = ''
 #       print("\twrksrv: \'%s\'" % self.line)
        return (self.line)

    def broadcast(self, msg):
        self.conn.send("broadcast %s,%s\n" % (self.team_name, msg))
        self.confirm_command("ok")

    def get_broadcast(self, msg):
        return msg.split(',', 1)[1]

    def get_message(self, msg):
        return msg.split(',', 2)[2]

    def same_team(self, msg):
        if self.get_broadcast(msg).startswith(self.team_name):
            return (True)
        return (False)

    def remove_task(self, msg):
        msg = msg.split(',', 1)[1]
        for i in range(len(self.resources)):
            if self.resources[i] in msg:
                self.tasks[i] = False
                break

    def decode_msg(self, msg):
        if msg.startswith("message") and self.same_team(msg):
            self.msg_dir = int(msg[8])
            msg = self.get_message(msg)
            if msg.startswith("come home"):
                self.bots_away = int(msg.split(',', 1)[1])
                if self.msg_dir != 0: 
                    self.come_home = True
            elif msg.startswith("collect food"):
                self.farager = True
            elif msg.startswith("collect resources"):
                self.scavenger = True
            elif msg.startswith("requirement met"):
                self.remove_task(msg)
            elif msg.startswith("bot is home"):
                self.bots_away -= 1
            elif msg.startswith("all bots home"):
                self.bots_home = True
            elif msg.startswith("i'm bot"):
                self.nums[int(msg.split(' ', 2)[2])] += 1
            elif msg.startswith("got"):
                pass
            elif msg.startswith("level up"):
                self.level += 1
                if self.level == 2:
                    self.food_min = 4 
            elif msg.startswith("new north"):
                self.north = self.msg_dir
                self.can_move = True
            elif msg.startswith("halt"):
                print("\tWORKER: halted")
                while True:
                    pass
            else:
                print("\033[31mERROR: recieved unknown message : %s\033[0m" % msg)
                while True:
                    pass
        elif msg.startswith("ko"):
            return (False)
        else:
            print("\033[31mError: unknown server response : %s\033[0m" % msg)
            while True:
                pass
        return (True)

    def set_requirements(self):
        self.target = self.requirements[self.level - 1]
        for i in range(len(self.target)):
            if self.requirements[self.level - 1][i] > self.team_inventory[i]:
                self.tasks[i] = True
            else:
                self.tasks[i] = False
        if self.team_inventory[5] < 1:
            self.tasks[5] = True
        print("\033[33mBot # %d @lvl %d:\ntasks:" % (self.bot_number, self.level))
        print self.tasks
        print("target")
        print self.target
        print("team_inventory:")
        print self.team_inventory
        print("\033[0m")

    def confirm_command(self, msg):
        self.get_next_line()
        while not self.line.startswith(msg) or not (msg in self.line):
            if not self.decode_msg(self.line):
                return (False)
            self.get_next_line()
        return (True)

    def confirm_direction(self):
        self.get_next_line()
        while not (self.line.startswith("message") and
                self.same_team(self.line) and
                self.line.count("come home") == 1):
            self.decode_msg(self.line)
            self.get_next_line()
        self.msg_dir = int(self.line[8])
        self.bots_away = int(self.line.split(',', 3)[3])

# Serious Logical flaw here!! bot_number will be incorrectly set if two bots arrive home at the same time... Unique bot numbers required for get_on_path().
# OPPORTUNITY for smart turning updating msg_dir without new message!!
    def get_home(self):
 #       self.confirm_direction()
        while self.msg_dir != 0:
            self.confirm_direction()
            if self.msg_dir == 0:
                break
            elif self.msg_dir == 1 or self.msg_dir == 2 or self.msg_dir == 8:
                self.advance()
            elif self.msg_dir == 3 or self.msg_dir == 4 or self.msg_dir == 5:
                self.turn_left()
            elif self.msg_dir == 6 or self.msg_dir == 7:
                self.turn_right()
        self.can_move = False
        self.come_home = False
        self.drop_resources()
        self.broadcast("bot is home")
        print("\tWORKER: bot is home")
        if self.bot_number < 0:
            self.bot_number = self.bots_away #will be a bug at some point

    def movement(self, command):
        self.conn.send(command)
        self.confirm_command("ok")

    def advance(self, count=1):
        while count > 0:
            self.movement("advance\n")
            count -= 1

    def turn_right(self):
        self.movement("right\n")

    def turn_left(self):
        self.movement("left\n")

    def put(self, item):
        self.conn.send("put %s\n" % item)
        self.confirm_command("ok")

    def take(self, item):
        self.conn.send("take %s\n" % item)
        return (self.confirm_command("ok"))

    def see(self):
        self.conn.send("see\n")
        self.confirm_command("{")

    def count_resources(self):
        self.see()
        self.line = self.line.split(',', 1)[0]
        for i in range(len(self.tile_inventory)):
            self.tile_inventory[i] = self.line.count(self.resources[i])

    def set_team_inventory(self):
        self.count_resources()
        self.team_inventory = self.tile_inventory

    def drop_resources(self):
        for i in range(len(self.inventory) - 1):
            while self.inventory[i] > 0:
                self.put(self.resources[i])
                self.inventory[i] -= 1
        while self.inventory[6] > self.food_min:
            self.put("food")
            self.inventory[6] -= 1

    def grab_food(self):
        while self.inventory[6] < self.food_min:
            if not self.take("food"):
                break
            self.inventory[6] += 1
        self.inventory[6] = 0

    def confirm_unique_bot_num(self):
        while self.nums != [1, 1, 1, 1, 1]:
            self.nums = [0, 0, 0, 0, 0]
            self.broadcast("i'm bot %d" % self.bot_number)
            while sum(self.nums) < 5:
                self.get_next_line()
                self.decode_msg(self.line)
            if self.nums[self.bot_number] > 1:
                rand = randint(0, 2)
                if rand == 0:
                    for i in range(5):
                        if self.nums[i] == 0:
                            self.bot_number = i
                            break
        self.bots_unique = True

    def wait_on_bots(self):
        while not self.bots_home:
            self.get_next_line()
            self.decode_msg(self.line)
        self.grab_food()
        if self.level == 1 and not self.bots_unique:
            rand = randint(0, 6)
  #          self.confirm_unique_bot_num()

    def go_forage(self):
        print("\tWORKER: faraging")
        self.set_team_inventory()
        self.tasks = [False, False, False, False, False, False, True]
        if self.team_inventory[4] < 6:
            self.tasks[4] = True
        if self.team_inventory[5] < 1:
            self.tasks[5] = True
        self.get_on_path()
        self.farm_task()
       
    def go_scavenge(self):
        print("\tWORKER: scavenging")
        self.conn.send("inventory\n")
        self.confirm_command('{')
        self.set_requirements()
        self.get_on_path()
        self.farm_task()

# make efficient
    def get_on_path(self):
        if self.bot_number < 3:
            self.face_north()
        else:
            self.face_east()
        if self.bot_number < 3:
            self.advance(self.bot_number)
        else:
            self.advance(self.bot_number - 2)
        self.turn_left()
        if self.bot_number == 0:
            self.advance()

    def face_north(self):
        if self.north == 3:
            self.turn_left()
        elif self.north == 5:
            self.turn_right()
            self.turn_right()
        elif self.north == 7:
            self.turn_right()

    def face_east(self):
        if self.north == 1:
            self.turn_right()
        elif self.north == 5:
            self.turn_left()
        elif self.north == 7:
            self.turn_right()
            self.turn_right()

    def farm_task(self):
        while not self.come_home:
            sight = self.level + 1
            self.see()
            total_sight = self.line[1:-1].split(',')
            line_sight = []
            for i in range(self.level + 1):
                index = 0
                for j in range(i + 1):
                    index += j * 2
                line_sight.append(total_sight[index])
            for i in range(self.level + 1):
                if not self.come_home:
                    self.farm_square(line_sight[i])
                    if not self.come_home:
                        self.advance()

    def farm_square(self, square):
        for i in range(len(self.resources)):
            self.tile_inventory[i] = square.count(self.resources[i])
        for i in range(len(self.tasks)):
            while not self.come_home and self.tasks[i] and self.tile_inventory[i] > 0:
                if self.take(self.resources[i]):
                    self.inventory[i] += 1
                    self.broadcast("got %s" % self.resources[i])
                self.tile_inventory[i] -= 1
