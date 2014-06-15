import serial
import bitstring
import glob
import time

fw = bitstring.ConstBitStream(bytes=open("./helium.bin").read())

ser = serial.Serial(glob.glob("/dev/ttyACM*")[0], 115200)

ser.setTimeout(.1)

def confirm():
	i = 0
	while ser.read() != ">":
		i+= 1
		if i > 100:
			return False
	return True

regBase = 0x400e0800
flashBase = 0x80000
offset = 0

# erase flash
ser.write("W400E0804,5A000005#")
confirm()

for pos in xrange(0,fw.length/8,4):
	fw.bytepos = pos
	addr = hex(flashBase+pos).lstrip("0x").rstrip("L").zfill(8)
	data = hex(fw.peek("<L")).lstrip("0x").zfill(8)
	cmd = ("W"+addr+","+data+"#").upper()
	ser.write(cmd)
	if not confirm():
		print "failed at:", cmd
		exit()

# disable SAM-BA: 0x5a000000 | (1 << 8) | 0x0b) < 0)
ser.write("W400E0804,5A00010B#")
ser.confirm()
# last thing - switch to app memory
#ser.write("G00000000#")
#ser.confirm()
#ser.read()
