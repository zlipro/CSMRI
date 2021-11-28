
#include <stdbool.h>


#include "misc/cppwrap.h"
#include "misc/types.h"
#include "misc/misc.h"

typedef bool opt_conv_f(void* ptr, char c, const char* optarg);

struct opt_s {

	char c;
	const char* s;
	bool arg;
	opt_conv_f* conv;
	void* ptr;
	const char* descr;
};

extern opt_conv_f opt_set;
extern opt_conv_f opt_clear;
extern opt_conv_f opt_int;
extern opt_conv_f opt_uint;
extern opt_conv_f opt_long;
extern opt_conv_f opt_float;
extern opt_conv_f opt_string;
extern opt_conv_f opt_vec2;
extern opt_conv_f opt_float_vec2;
extern opt_conv_f opt_vec3;
extern opt_conv_f opt_float_vec3;
extern opt_conv_f opt_select;
extern opt_conv_f opt_subopt;

struct opt_select_s {

	void* ptr;
	const void* value;
	const void* default_value;
	size_t size;
};

struct opt_subopt_s {

	int n;
	struct opt_s* opts;
};

typedef long opt_vec2_t[2];
typedef float opt_fvec2_t[2];
typedef long opt_vec3_t[3];
typedef float opt_fvec3_t[3];

#define OPT_SEL(T, x, v)	&(struct opt_select_s){ (x), &(T){ (v) }, &(T){ *(x) }, sizeof(T) }
#define OPT_SUB(n, opts)	&(struct opt_subopt_s){ (n), (opts) }

#define OPT_SET(c, ptr, descr)			{ (c), NULL, false, opt_set, TYPE_CHECK(bool*, (ptr)), "\t" descr }
#define OPT_CLEAR(c, ptr, descr)		{ (c), NULL, false, opt_clear, TYPE_CHECK(bool*, (ptr)), "\t" descr }
#define OPT_ARG(c, _fun, T, ptr, argname, descr) { (c), NULL, true, _fun, TYPE_CHECK(T*, (ptr)), " " argname "      \t" descr }
#define OPT_STRING(c, ptr, argname, descr)	OPT_ARG(c, opt_string, const char*, ptr, argname, descr)
#define OPT_UINT(c, ptr, argname, descr)	OPT_ARG(c, opt_uint, unsigned int, ptr, argname, descr)
#define OPT_INT(c, ptr, argname, descr)		OPT_ARG(c, opt_int, int, ptr, argname, descr)
#define OPT_LONG(c, ptr, argname, descr)	OPT_ARG(c, opt_long, long, ptr, argname, descr)
#define OPT_FLOAT(c, ptr, argname, descr)	OPT_ARG(c, opt_float, float, ptr, argname, descr)
#define OPT_VEC2(c, ptr, argname, descr)	OPT_ARG(c, opt_vec2, opt_vec2_t, ptr, argname, descr)
#define OPT_FLVEC2(c, ptr, argname, descr)	OPT_ARG(c, opt_float_vec2, opt_fvec2_t, ptr, argname, descr)
#define OPT_VEC3(c, ptr, argname, descr)	OPT_ARG(c, opt_vec3, opt_vec3_t, ptr, argname, descr)
#define OPT_FLVEC3(c, ptr, argname, descr)	OPT_ARG(c, opt_float_vec3, opt_fvec3_t, ptr, argname, descr)
#define OPT_SELECT(c, T, ptr, value, descr)	{ (c), NULL, false, opt_select, OPT_SEL(T, TYPE_CHECK(T*, ptr), value), "\t" descr }
#define OPT_SUBOPT(c, argname, descr, NR, opts)	OPT_ARG(c, opt_subopt, struct opt_subopt_s, OPT_SUB(NR, opts), argname, descr)

// If the character in these macros is 0 (please note: NOT '0'), then it is only a long opt
// Otherwise, it is both
#define OPTL_SET(c, s, ptr, descr)			{ (c), (s), false, opt_set, TYPE_CHECK(bool*, (ptr)), "\t" descr }
#define OPTL_CLEAR(c, s, ptr, descr)			{ (c), (s), false, opt_clear, TYPE_CHECK(bool*, (ptr)), "\t" descr }
#define OPTL_ARG(c, s, _fun, T, ptr, argname, descr) { (c), (s), true, _fun, TYPE_CHECK(T*, (ptr)), " " argname "      \t" descr }
#define OPTL_STRING(c, s, ptr, argname, descr)	OPTL_ARG(c, s, opt_string, const char*, ptr, argname, descr)
#define OPTL_UINT(c, s, ptr, argname, descr)	OPTL_ARG(c, s, opt_uint, unsigned int, ptr, argname, descr)
#define OPTL_INT(c, s, ptr, argname, descr)	OPTL_ARG(c, s, opt_int, int, ptr, argname, descr)
#define OPTL_LONG(c, s, ptr, argname, descr)	OPTL_ARG(c, s, opt_long, long, ptr, argname, descr)
#define OPTL_FLOAT(c, s, ptr, argname, descr)	OPTL_ARG(c, s, opt_float, float, ptr, argname, descr)
#define OPTL_CFLOAT(c, s, ptr, argname, descr)	OPTL_ARG(c, s, opt_cfloat, complex float, ptr, argname, descr)
#define OPTL_VEC2(c, s, ptr, argname, descr)	OPTL_ARG(c, s, opt_vec2, opt_vec2_t, ptr, argname, descr)
#define OPTL_FLVEC2(c, s, ptr, argname, descr)	OPTL_ARG(c, s, opt_float_vec2, opt_fvec2_t, ptr, argname, descr)
#define OPTL_VEC3(c, s, ptr, argname, descr)	OPTL_ARG(c, s, opt_vec3, opt_vec3_t, ptr, argname, descr)
#define OPTL_FLVEC3(c, s, ptr, argname, descr)	OPTL_ARG(c, s, opt_float_vec3, opt_fvec3_t, ptr, argname, descr)
#define OPTL_SELECT(c, s, T, ptr, value, descr)	{ (c), (s), false, opt_select, OPT_SEL(T, TYPE_CHECK(T*, ptr), value), "\t" descr }
#define OPTL_SUBOPT(c, s, argname, descr, NR, opts)	OPTL_ARG(c, s, opt_subopt, struct opt_subopt_s, OPT_SUB(NR, opts), argname, descr)

extern void cmdline(int* argc, char* argv[], int min_args, int max_args, const char* usage_str, const char* help_str, int n, const struct opt_s opts[n]);

#include "misc/cppwrap.h"

