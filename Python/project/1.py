from select import select, poll
import sys

timeout = 5
print "Enter something:"
rlist, _, _ = select([sys.stdin], [], [], timeout)

print "000"
print rlist
poll()
print "000"
if rlist:
    s = sys.stdin.readline()
    print s
else:
    print "No inprut. Moving on..."