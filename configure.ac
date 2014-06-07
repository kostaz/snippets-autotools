AC_INIT([Snippets], [0.1])
AC_CONFIG_MACRO_DIR(src/boost/m4)

AX_BOOST_BASE
AX_BOOST_SYSTEM
AX_BOOST_FILESYSTEM
AX_BOOST_THREAD

LIBS="$BOOST_THREAD_LIB $BOOST_SYSTEM_LIB"

AM_INIT_AUTOMAKE([foreign])

AC_PROG_CC
AC_PROG_CXX

AC_OUTPUT(Makefile src/Makefile src/pure_virtual/Makefile \
	  src/helloworld/Makefile src/bitcoin_serialize/Makefile \
	  src/boost/Makefile src/boost/thread/Makefile \
	  src/boost/thread/bank_account_1/Makefile \
	  src/boost/thread/bank_account_2/Makefile)

