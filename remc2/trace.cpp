#include <stdio.h>
#include <time.h>

static FILE *fp_trace;

extern "C"
{
    void __cyg_profile_func_enter(void *this_fn, void *call_site)
        __attribute__((no_instrument_function));
    void __cyg_profile_func_exit(void *this_fn, void *call_site)
        __attribute__((no_instrument_function));
}

void __attribute__((constructor)) trace_begin(void)
{
    fp_trace = fopen("trace.out", "w");
}

void __attribute__((destructor)) trace_end(void)
{
    if (fp_trace != NULL) {
        fclose(fp_trace);
    }
}

//__attribute__((no_instrument_function))
void __cyg_profile_func_enter(void *func, void *caller)
{
    if (fp_trace != NULL) {
        fprintf(fp_trace, "e %p %p\n", func, caller);
    }
}

//__attribute__((no_instrument_function))
void __cyg_profile_func_exit(void *func, void *caller)
{
    if (fp_trace != NULL) {
        fprintf(fp_trace, "x %p %p\n", func, caller);
    }
}
