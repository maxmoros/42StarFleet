import socket

buff = ''
call_counter = 0

def get_next_line(conn, blocking=0):
    global buff
    global call_counter
#    print "GNL CALL"
    if blocking == 1 and not buff:
        conn.setblocking(blocking)
    else:
        conn.setblocking(0)
    while '\n' not in buff:
        try:
            buff += conn.recv(256)
        except:
            break
    if '\n' in buff:
        (line, buff) = buff.split('\n', 1)
    else:
        line = buff
        buff = ''
    if blocking == 1:
#        print "GNL : call %d, line\"%s\"\n" % (call_counter, line)
        call_counter += 1
#    print "GNL: \'" + line + "\'" + "\tBUFF : \'" + buff + "\'"
    return line

def clear_gnl():
    global buff
    buff = ''
