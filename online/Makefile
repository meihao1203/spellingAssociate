OBJS:=*.cpp
ELF:=server
$(ELF):$(OBJS)
	g++ $(OBJS) -o $(ELF) -std=c++11 -lpthread
.PHONY:rebuild clean
clean:
	rm -rf $(ELF)
rebuild:
	make clean server
