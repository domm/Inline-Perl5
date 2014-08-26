#include <EXTERN.h>
#include <perl.h>

static PerlInterpreter *my_perl;

static void xs_init (pTHX);
EXTERN_C void boot_DynaLoader (pTHX_ CV* cv);
EXTERN_C void boot_Socket (pTHX_ CV* cv);

EXTERN_C void xs_init(pTHX) {
    char *file = __FILE__;
    /* DynaLoader is a special case */
    newXS("DynaLoader::boot_DynaLoader", boot_DynaLoader, file);
}

PerlInterpreter *p5_init_perl() {
    char *embedding[] = { "", "-e", "0" };
    PERL_SYS_INIT3(0, NULL, NULL);
    my_perl = perl_alloc();
    perl_construct( my_perl );
    perl_parse(my_perl, xs_init, 3, embedding, NULL);
    PL_exit_flags |= PERL_EXIT_DESTRUCT_END;
    perl_run(my_perl);
    return my_perl;
}

void p5_destruct_perl(PerlInterpreter *my_perl) {
    perl_destruct(my_perl);
    perl_free(my_perl);
    PERL_SYS_TERM();
}

int p5_SvIOK(PerlInterpreter *my_perl, SV* sv) {
    return SvIOK(sv);
}

int p5_SvPOK(PerlInterpreter *my_perl, SV* sv) {
    return SvPOK(sv);
}


char *p5_sv_to_char_star(PerlInterpreter *my_perl, SV *sv) {
    STRLEN len;
    char *ptr;
    ptr = SvPV(sv, len);
    return ptr;
}
