# Makefile

# compile main.cpp into 'shell' executable
shell: main.cpp
	g++ main.cpp -o shell

# run shell with process/thread limit
run: shell
	bash -c "ulimit -u 100; ./shell"

# clean up compiled files
clean:
	rm -f shell