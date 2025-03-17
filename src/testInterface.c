/* Are we on a Windows platform ? */
#if defined(_WIN32) || defined(_WIN64) || defined(__WINDOWS__) || defined(__TOS_WIN__)
void sysAgnosticFunction() {
   /* windows implementation */
}

/* Are we on a Linux platform ? */
#elif defined(__linux__) || defined(__linux) || defined(linux) || defined(__gnu_linux__)
void sysAgnosticFunction() {
    /* linux implementation */
}

/* Are we on a Unix platform ? */
#elif defined(__unix__) || defined(__unix) || defined(unix)         \
|| defined(__CYGWIN__) || ( defined(__APPLE__) && defined(__MACH) )
void sysAgnosticFunction() {
    /* unix implementation */
}

/* Are we on Unsupported platform? */
#else
void sysAgnosticFunction() {
    /* generic implementation */
}
#endif