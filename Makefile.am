bin_PROGRAMS=bignum2

bignum2_SOURCES=\
		tools_config.h\
		src/colored_output.cc\
		src/colored_output.h\
		src/OutDebug.cc\
		src/OutDebug.h\
		src/DetectLocale.cc \
		src/DetectLocale.h \
		src/read_file.h \
		src/read_file.cc \
		src/main.cc
			  
AM_CPPFLAGS = -I$(top_srcdir)/tools \
	-I$(top_srcdir)/cpputils/cpputilsshared  \
	-I$(top_srcdir)/cpputils/cpputilsshared/cpputilsformat \
	-I$(top_srcdir)/src  \
	-I$(top_srcdir)/bignum \
	-DNOWAMAS \
	-std=c++11 \
	-fopenmp \
	-DLOCALEDIR=\"$(localedir)\"

noinst_LIBRARIES=tools/libtools.a \
	bignum/libbignum.a \
	cpputils/cpputilsshared/libcpputilsshared.a \
	cpputils/cpputilsshared/cpputilsformat/libcpputilsformat.a 

tools_libtools_a_SOURCES= \
	tools/arg.cpp \
	tools/arg.h \
	tools/database.cpp \
	tools/database.h \
	tools/db.cpp \
	tools/db.h \
	tools/dbi.cpp \
	tools/dbi.h \
	tools/debug.cpp \
	tools/debug.h \
	tools/mysql_db.cpp \
	tools/mysql_db.h \
	tools/odbc_db.cpp \
	tools/odbc_db.h \
	tools/oracle_db.cpp \
	tools/oracle_db.h \
	tools/pairs.cpp \
	tools/pairs.h \
	tools/theme.cpp \
	tools/theme.h \
	tools/thread.cpp \
	tools/thread.h


cpputils_cpputilsshared_libcpputilsshared_a_SOURCES= \
		cpputils/cpputilsshared/backtrace.cc \
		cpputils/cpputilsshared/backtrace.h \
		cpputils/cpputilsshared/cppdir.cc \
		cpputils/cpputilsshared/cppdir.h \
		cpputils/cpputilsshared/leoini.cc \
		cpputils/cpputilsshared/leoini.h \
		cpputils/cpputilsshared/logtool2.cc \
		cpputils/cpputilsshared/logtool2.h \
		cpputils/cpputilsshared/string_utils.cc \
		cpputils/cpputilsshared/string_utils.h \
		cpputils/cpputilsshared/vec_utils.cc \
		cpputils/cpputilsshared/vec_utils.h \
		cpputils/cpputilsshared/xml.cc \
		cpputils/cpputilsshared/xml.h \
		cpputils/cpputilsshared/cpp_util.h \
		cpputils/cpputilsshared/cpp_util_min_max.h \
		cpputils/cpputilsshared/cpp_utils.h \
		cpputils/cpputilsshared/cpputils.h \
		cpputils/cpputilsshared/ref.h \
		cpputils/cpputilsshared/jvector.h \
		cpputils/cpputilsshared/zvector.h \
		cpputils/cpputilsshared/range.h \
		cpputils/cpputilsshared/report_exception.h \
		cpputils/cpputilsshared/sql_exception.h \
		cpputils/cpputilsshared/utf8.h \
		cpputils/cpputilsshared/utf8/core.h \
		cpputils/cpputilsshared/utf8/checked.h \
		cpputils/cpputilsshared/utf8/unchecked.h \
		cpputils/cpputilsshared/utf8/cpp11.h \
		cpputils/cpputilsshared/utf8/cpp17.h \
		cpputils/cpputilsshared/utf8_util.h \
		cpputils/cpputilsshared/utf8_util.cc


cpputils_cpputilsshared_cpputilsformat_libcpputilsformat_a_SOURCES= \
	cpputils/cpputilsshared/cpputilsformat/format1.cc \
	cpputils/cpputilsshared/cpputilsformat/format2.cc \
	cpputils/cpputilsshared/cpputilsformat/format2.h \
	cpputils/cpputilsshared/cpputilsformat/format1.h \
	cpputils/cpputilsshared/cpputilsformat/format.h \
	cpputils/cpputilsshared/cpputilsformat/cformat.h \
	cpputils/cpputilsshared/cpputilsformat/wformat2.cc \
	cpputils/cpputilsshared/cpputilsformat/wformat2.h \
	cpputils/cpputilsshared/cpputilsformat/cwformat.h \
	cpputils/cpputilsshared/cpputilsformat/cwformat.cc

bignum_libbignum_a_SOURCES= \
	bignum/bignum2.cc \
	bignum/bignum2.h \
	bignum/BigInt.h \
	bignum/BigInt.cc \
	bignum/vchar.h \
	bignum/vchar.cc	

bignum2_LDADD = \
	bignum/libbignum.a \
	tools/libtools.a \
	cpputils/cpputilsshared/libcpputilsshared.a \
	cpputils/cpputilsshared/cpputilsformat/libcpputilsformat.a 

LIBS=
	
AM_LDFLAGS= -fopenmp	
	
if MINGW
AM_LDFLAGS +=
# with -std=c++11 WIN32 is disabled (_WIN32) would be the valid one, so we define it in mingw.
AM_CPPFLAGS += -DWIN32
else
AM_LDFLAGS +=
endif


#if USE_NLS
#PO_SUBDIR = po
#LIBS += $(LTLIBINTL)
#AM_CPPFLAGS += -DENABLE_NLS
#endif

SUBDIRS = $(PO_SUBDIR)

ACLOCAL_AMFLAGS = -I m4

EXTRA_DIST = \
	README \
	LICENSE 
	
	
	
	
