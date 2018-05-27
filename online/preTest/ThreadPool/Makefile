OBJS:=*.cpp
ELF:=Threadpool
$(ELF):$(OBJS)
	g++ $(OBJS) -o $(ELF) -std=c++11 -lpthread
.PHONY:rebuild clean
rebuild:
	make clean $(ELF)
clean:
	rm -rf $(ELF)

