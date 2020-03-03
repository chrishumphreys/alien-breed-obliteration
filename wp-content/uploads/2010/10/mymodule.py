log_filename = "c:\\tmp\\olly.log"
debug = 1
readmem = 1

def logf( str ):
	f = open(log_filename, "ab")
	f.write( str )
	f.write( "\n" )
	f.close()

def print_debug( str ):
	if debug:
		print str
	logf(str)

def CreateFileA_handler(hookcall):
	myproxy = hookcall.proxy
	print_debug("CreateFileA_handler running...")
	filename = myproxy.readasciiz( hookcall.params[0] )
	print_debug(filename)
	hookcall.sendack()
	return

def ReadFile_handler_after(hookcall):
	myproxy = hookcall.proxy
	print_debug("ReadFileA_handler_after running...")
	
	_HANDLE = hookcall.params[0]
	_BUF = hookcall.params[1]
	_TOREAD = hookcall.params[2]
	_READ = hookcall.params[3]
	_OVRLAP = hookcall.params[4]
	
	read = myproxy.readdword(_READ)
	filename= myproxy.readasciiz(0x47cdc0)
	print_debug(filename) 
	print_debug("Buffer: %xh (%d)" % (_BUF, _BUF))
	print_debug("To Read %xh (%d)" % (_TOREAD, _TOREAD))
	print_debug("Read %xh (%d)" % (read, read))
	
	if readmem:
		if _BUF != 0 and read > 1:
			if read <= 26000:
				print_debug("About to read memory...")
				data = myproxy.readmemory(_BUF, _TOREAD);	
				print_debug("Read")
			else:
				print_debug("Data too large (%d)" % (read))
				hookcall.sendack()
				return
		else:
			print_debug("BUF IS NULL or too small, we don't care!")
			hookcall.sendack()
			return
			
		print_debug("About to write file: " + filename)
		f = open('c:\\tmp\\' + filename, 'wb')
		f.write(data)
		f.close()
		print_debug("Written")

		##print "About to free memory"
		##myproxy.freememory( data)
		##print "Freed"
	
	hookcall.sendack()
	return
	
	
def FileDecodedBreakPoint(hookcall):
	myproxy = hookcall.proxy
	print_debug("FileDecodedBreakPoint running...")
	
	##At this breakbpoint the data buffer and the length are
	##always at the same position on the stack +14 and +18
	
	_ESP = hookcall.regs['esp']
	print_debug("esp = %X" % _ESP)
	
	_BUF = myproxy.readdword(_ESP+0x14)
	print_debug("buffer = %X" % _BUF)
	
	_LENGTH = myproxy.readdword(_ESP+0x18)
	print_debug("length = %X (%d)" % (_LENGTH, _LENGTH))
	
	##The file name is always at 0x47cdc0
	
	filename= myproxy.readasciiz(0x47cdc0)
	print_debug(filename) 
	
	print_debug("About to write file: " + filename)
	f = open('c:\\tmp\\' + filename, 'wb')
	
	copied = 0
	CHUNK = 20000    ## max we will read per loop
	
	while copied < _LENGTH:
	
		if copied + CHUNK > _LENGTH:
			CHUNK = _LENGTH - copied
			
		data = myproxy.readmemory((_BUF + copied), CHUNK)
		print_debug("Read %x bytes" % (len(data)))
		f.write(data)	
		copied += len(data)
	
	f.close()
	
	
	hookcall.sendack()
	##hookcall.sendacknocont()
	return
	
	
def FileSeekBreakPoint(hookcall):
	myproxy = hookcall.proxy
	#print_debug("FileSeekPoint running...")
	
	_ESP = hookcall.regs['esp']
	#print_debug("esp = %X" % _ESP)
	
	_OFFSET = myproxy.readdword(_ESP+0x04)
	print_debug("offset:%X" % _OFFSET)
	
	#filename= myproxy.readasciiz(_ESP+0x1c)
	#print_debug(filename) 
	
	hookcall.sendack()
	##hookcall.sendacknocont()
	return
	
def FileLoadBreakPoint(hookcall):
	myproxy = hookcall.proxy
	#print_debug("FileLoadBreakPoint running...")
	
	_ESP = hookcall.regs['esp']
	#print_debug("esp = %X" % _ESP)
	
	_BUF = myproxy.readdword(_ESP)
	
	filename= myproxy.readasciiz(_BUF)
	print_debug("file:%s" % filename) 
	
	hookcall.sendack()
	##hookcall.sendacknocont()
	return
	
def FileReadBreakPoint(hookcall):
	myproxy = hookcall.proxy
	#print_debug("FileReadBreakPoint running...")
	
	_ESP = hookcall.regs['esp']
	#print_debug("esp = %X" % _ESP)
	
	_LEN = myproxy.readdword(_ESP+0x08)
	print_debug("len:%X" % _LEN)
	
	hookcall.sendack()
	##hookcall.sendacknocont()
	return
	