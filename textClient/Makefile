OBJS:=*.cpp
ELF:=client
$(ELF):$(OBJS)
	g++ $(OBJS) -o $(ELF) -std=c++11
.PHONY:clean rebuild
clean:
	rm -rf $(ELF)
rebuild:
	make clean $(ELF)
