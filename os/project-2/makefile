start: optional_threads.c statistical_funcs.c statistical_funcs.h util_funcs.h util_funcs.c ten_threads.c five_threads.c no_thread.c
	gcc optional_threads.c statistical_funcs.c statistical_funcs.h util_funcs.h util_funcs.c -o optional_threads.o -lm
	gcc ten_threads.c statistical_funcs.c statistical_funcs.h util_funcs.h util_funcs.c -o ten_threads.o -lm
	gcc five_threads.c statistical_funcs.c statistical_funcs.h util_funcs.h util_funcs.c -o five_threads.o -lm
	gcc no_thread.c statistical_funcs.c statistical_funcs.h util_funcs.h util_funcs.c -o no_thread.o -lm
	@echo ""
	@echo "you can execute no_thread.o for first part and five_threads.o and ten_threads.o for second part."
	@echo "alternatively you can execute optional_threads.o with any number of threads for the additional part."
	@echo "syntax for the optional_threads.o --> ./optional_threads.o <N> <number-of-threads>  "

clean:
	rm optional_threads.o ten_threads.o five_threads.o no_thread.o
