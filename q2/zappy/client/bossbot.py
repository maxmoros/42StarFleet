import socket

class BossBot:
    """Destroyer of worlds! :D"""
    team_name = "banana"
    tick_len = 0.0
    conn = 0
    buff = ''
    line = ''
    map_x = 0
    map_y = 0
    food_min = 6
    level = 1
    msg_dir = -1
    bots_active = 0
    eggs = 0
    bots_away = 0
    can_move = True
    inventory = [0,0,0,0,0,0,0]
    team_inventory = [0,0,0,0,0,0,0]
    target = [0, 0, 0, 0, 0, 0, 0]
#    requirements_met = False
    requirements =     [[1, 0, 0, 0, 0, 0, 16],
                        [2, 2, 2, 0, 0, 0, 20],
                        [2, 0, 1, 0, 2, 0, 20],
                        [1, 1, 2, 0, 1, 0, 20],
                        [1, 2, 1, 3, 0, 0, 20],
                        [1, 2, 3, 0, 1, 0, 20],
                        [2, 2, 2, 2, 2, 1, 20]]
    tasks = [True, True, True, True, True, True, False]
    resources = ["linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame", "food"]
    
    def __init__(self, server_ip="localhost", comm_port=5555, team = "banana"):
        self.team_name = team
        self.init_comm(server_ip, comm_port)
        self.print_bot()

    def boss_loop(self):
        print("BOSS: Bossing")
        if self.bots_away > 0:
            self.call_home_workers()
        while self.level < 8:
            print("\033[32mBOSS: set north\033[0m")
            self.set_north()
            print("\033[32mBOSS: set requirements\033[0m")
            self.set_requirements()
            print("\033[32mBOSS: sending scavengers\033[0m")
            self.send_scavengers()
            print("\033[32mBOSS: monitoring collection\033[0m")
            print("\033[32mBOSS: TEAM INV\033[0m")
            print self.team_inventory
            self.monitor_collection()
            print("\033[32mBOSS: calling home\033[0m")
            self.call_home_workers()
            print("\033[32mBOSS: incanting\033[0m")
            self.incantation()

    def print_bot(self):
        print("BossBot:\n  team: %s" % self.team_name)
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
        self.bots_away = self.bots_active - 1
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
                break
        if '\n' in self.buff:
            (self.line, self.buff) = self.buff.split('\n', 1)
        else:
            self.line = self.buff
            self.buff = ''
        print("Sever: \"%s\"" % self.line)
        return self.line

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

    def msg_is_resource(self, msg):
        if msg.startswith("got"):
            msg = msg.split(' ', 1)[1]
            for i in range(len(self.team_inventory)):
                if self.resources[i] in msg:
                    self.team_inventory[i] += 1
                    if self.team_inventory[i] >= self.target[i]:
                        self.broadcast("requirement met,%s" % self.resources[i])
                    break
            return (True)
        return (False)

    def worker_communication(self, msg):
        if msg.startswith("come home"):
            return (True)
        elif msg.startswith("collect food"):
            return (True)
        elif msg.startswith("collect resources"):
            return (True)
        elif msg.startswith("requirement met"):
            return (True)
        elif msg.startswith("bot is home"):
            return (True)
        elif msg.startswith("all bots home"):
            return (True)
        elif msg.startswith("new north"):
            return (True)
        elif msg.startswith("level up"):
            return (True)
        elif msg.startswith("i'm bot"):
            return (True)
        return (False)

    def decode_message(self, msg):
        if msg.startswith("message") and self.same_team(msg):
            self.msg_dir = int(msg[8])
            msg = self.get_message(msg)
            if self.msg_is_resource(msg):
                print("\033[32mBOSS: %s\033[0m" % msg)
            elif "bot is home" in msg:
                self.bots_away -= 1
            elif self.worker_communication(msg):
                pass
            else:
                self.broadcast("halt")
                print("\033[31mError: unknown message : \'%s\'\033[0m" % msg)
                while True:
                    pass
        elif msg.startswith("current level"):
            pass
        elif msg.startswith("ko"):
            return (False)
        else:
            print("\033[31mError: unknown server response : \'%s\'\033[0m" % msg)
        return (True)

    def monitor_collection(self):
        while not self.requirements_met():
            self.get_next_line()
            self.decode_message(self.line)

    def requirements_met(self):
        for i in range(len(self.target)):
            if self.team_inventory[i] < self.target[i]:
                return (False)
        return (True)

    def set_requirements(self):
        self.target = self.requirements[self.level - 1]

    def confirm_command(self, msg):
        self.get_next_line()
        while not self.line.startswith(msg):
            if not self.decode_message(self.line):
                return (False)
            self.get_next_line()
        return (True)

    def call_home_workers(self):
        print "BOSS: calling home \'%d\' workers" % self.bots_away
        while self.bots_away > 0:
            self.broadcast("come home,%d" % self.bots_away)
        self.broadcast("all bots home")
        self.grab_food()

    def grab_food(self):
        while self.inventory[6] < self.food_min:
            if not self.take("food"):
                break
            self.inventory[6] += 1
        print("BOSS: got %d food" % self.inventory[6])
        self.inventory[6] = 0

    def movement(self, command):
        self.conn.send(command)
        self.confirm_command("ok")

    def advance(self):
        self.movement("advance\n")

    def turn_right(self):
        self.movement("right\n")

    def turn_left(self):
        self.movement("left\n")

    def take(self, item):
        self.conn.send("take %s\n" % item)
        return (self.confirm_command("ok"))
    
    def bot_inventory(self):
        self.conn.send("inventory\n")
        self.confirm_command("{")
        inv_list = self.line.split(',', 6)
        for i in range(inv_list):
            self.inventory[i] = int(inv_list[i].split(' ', 1)[1])
    
    def see(self):
        self.conn.send("see\n")

    def set_team_inventory(self):
        self.see()
        self.confirm_command("{")
        self.line = self.line.split(',', 1)[0]
        for i in range(len(self.team_inventory)):
            self.team_inventory[i] = self.line.count(self.resources[i])

    def incant(self):
        self.conn.send("incantation\n")

    def commit_incant_resources(self):
        for i in range(len(self.requirements[self.level - 1])):
            self.team_inventory[i] -= self.requirements[self.level - 1][i]

#FIX THE SERVER LVL UP MSG TO INCLUDE ':'
    def incantation(self):
        print("\033[32m")
        print self.team_inventory
        print self.target
        print("\033[0m")
        if not self.requirements_met():
            print("\033[31mError: insufficient resources to incant.\033[0m")
            broadcast("halt")
            while True:
                pass
        print("BOSS: Starting incantation")
        self.commit_incant_resources()
        self.incant()
        self.confirm_command("elevation in progress")
        self.confirm_command("current level ")
        self.line = self.line.split(' ', 2)[2]
        if int(self.line) > self.level:
            self.level = int(self.line)
            self.broadcast("level up")
        else:
            print("\033[31mERROR: Incantation failed\033[0m")
            self.broadcast("halt")
            while True:
                pass
        self.set_team_inventory()

    def set_north(self):
        self.advance()
        self.broadcast("new north")
        self.turn_right()
        self.turn_right()
        self.advance()

    def send_foragers(self):
        self.broadcast("collect food")
        self.bots_away = 5

    def send_scavengers(self):
        self.broadcast("collect resources")
        self.bots_away = 5
