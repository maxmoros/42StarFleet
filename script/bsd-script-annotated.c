#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/time.h>

#include <errno.h>
#include <fcntl.h>
#include <paths.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <tzfile.h>
#include <unistd.h>

#include <util.h>

FILE	*fscript;
int	master, slave;
int	child, subchild;
int	outcc;
char	*fname;

struct	termios tt;

__dead	void done __P((void));
	void dooutput __P((void));
	void doshell __P((void));
	void err __P((const char *, ...));
	void fail __P((void));
	void finish __P((int));
	void scriptflush __P((int));

int main(int argc, char *argv[])
{
	register int cc;
	struct termios rtt;
	struct winsize win;
	char ibuf[BUFSIZ];

	fname = "typescript";
	fscript = fopen(fname, "w");
	/* JOSH: equiv _ioctl(0, TIOCGETA, &tt). TIOCGET = "get termios struct" */
	(void)tcgetattr(STDIN_FILENO, &tt);
	(void)ioctl(STDIN_FILENO, TIOCGWINSZ, &win);
	/* JOSH: man page for openpty:
	* int openpty(int *amaster, int *aslave, char *name,
	* struct termios *termp, struct winsize *winp)
	*
	* The openpty() function allocates a pseudo-tty and returns
	* file descriptors for the master and slave in amaster and aslave.
	* If name is non-null, the filename of the slave is returned in name.
	* If termp is non-null, the terminal parameters of the slave will
	* be set to the values in termp.
	* If winp is non-null, the window size of the slave will be
	* set to the values in winp. */
	if (openpty(&master, &slave, NULL, &tt, &win) == -1)
		err("openpty: %s", strerror(errno));
	(void)printf("Script started, output file is %s\n", fname);
	rtt = tt;
	cfmakeraw(&rtt);
	rtt.c_lflag &= ~ECHO;
	/* JOSH: equiv to _ioctl(0, TIOCSETAF, &rtt) */
	(void)tcsetattr(STDIN_FILENO, TCSAFLUSH, &rtt);
	(void)signal(SIGCHLD, finish);
	/* JOSH: Fork once so that future input is executed in a subshell. When user
	 * types 'exit' they should exit our subshell, not their original session.
	 * Within the subshell, fork again. The parent will remain as the interactive
	 * shell and the child will write the output to fname. */
	child = fork();
	if (child == 0) {
		subchild = child = fork();
		if (child)
			dooutput();
		else
			doshell();
	}
	(void)fclose(fscript);
	/* JOSH: We have only been writing once every thirty seconds, so
	 * there's likely unflushed */
	while ((cc = read(STDIN_FILENO, ibuf, BUFSIZ)) > 0)
		(void)write(master, ibuf, cc);
	done();
}

/* JOSH: This is the fg/bg handler */
void finish(int signo)
{
	register int die, pid;
	union wait status;

	die = 0;
	while ((pid = wait3((int *)&status, WNOHANG, 0)) > 0)
		if (pid == child)
			die = 1;

	if (die)
		done();
}

void dooutput()
{
	/* JOSH: every it_interval.tv_sec seconds, send this process a SIGALRM.
	 * Our SIGALRM handler is scriptflush, which calls fflush, which I can't find
	 * but which presumably does what you would expect.
	 * Everything in here is a syscall. */
	struct itimerval value;
	register int cc;
	time_t tvec;
	char obuf[BUFSIZ];

	(void)close(STDIN_FILENO);
	tvec = time(NULL);
	(void)fprintf(fscript, "Script started on %s", ctime(&tvec));

	(void)signal(SIGALRM, scriptflush);
	value.it_interval.tv_sec = SECSPERMIN / 2;
	value.it_interval.tv_usec = 0;
	value.it_value = value.it_interval;
	(void)setitimer(ITIMER_REAL, &value, NULL);
	for (;;) {
		cc = read(master, obuf, sizeof (obuf));
		if (cc <= 0)
			break;
		(void)write(1, obuf, cc);
		(void)fwrite(obuf, 1, cc, fscript);
		outcc += cc;
	}
	done();
}

void scriptflush(int signo)
{
	if (outcc) {
		(void)fflush(fscript);
		outcc = 0;
	}
}

void doshell()
{
	char *shell;

	shell = getenv("SHELL");
	if (shell == NULL)
		shell = _PATH_BSHELL;
	/* JOSH: not using either of these because we're the (sub)parent from the 2nd fork */
	(void)close(master);
	(void)fclose(fscript);
	/* JOSH: equivalent to
	 * tcsetsid(slave); // create new session unless already current leader
	 * __ioctl(slave, TIOCSTTY, NULL) // "become controlling tty"
	 * execve(shell, { shell, NULL }, environ);
	 */
	login_tty(slave);
	execl(shell, "sh", "-i", NULL);
	perror(shell);
	fail();
}

void fail()
{
	(void)kill(0, SIGTERM);
	done();
}

void done()
{
	/* JOSH: Subshell reports the result on stdout; forked 'writer' process
	 * closes the file to which it was writing. */
	time_t tvec;

	if (subchild) {
		tvec = time(NULL);
		(void)fprintf(fscript,"\nScript done on %s", ctime(&tvec));
		(void)fclose(fscript);
		(void)close(master);
	} else {
		(void)tcsetattr(STDIN_FILENO, TCSAFLUSH, &tt);
		(void)printf("Script done, output file is %s\n", fname);
	}
	exit(0);
}

/* JOSH: fancy err(...) define we commented out above and aren't calling */
/* #if __STDC__ */
/* #include <stdarg.h> */
/* #else */
/* #include <varargs.h> */
/* #endif */

/* void */
/* #if __STDC__ */
/* err(const char *fmt, ...) */
/* #else */
/* err(fmt, va_alist) */
/* 	char *fmt; */
/* 	va_dcl */
/* #endif */
/* { */
/* 	va_list ap; */
/* #if __STDC__ */
/* 	va_start(ap, fmt); */
/* #else */
/* 	va_start(ap); */
/* #endif */
/* 	(void)fprintf(stderr, "script: "); */
/* 	(void)vfprintf(stderr, fmt, ap); */
/* 	va_end(ap); */
/* 	(void)fprintf(stderr, "\n"); */
/* 	exit(1); */
/* 	/1* NOTREACHED *1/ */
/* } */
