play:
	connect

compile:
	cl Stack.c Hashmap.c AI.c connect.c /link /out:connect.exe
	
clean:
	del *.obj
	del *.o
	del *.exe