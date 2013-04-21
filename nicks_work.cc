//
// builtin_cmd - If the user has typed a built-in command then execute
// it immediately. The command name would be in argv[0] and
// is a C string. We've cast this to a C++ string type to simplify
// string comparisons; however, the do_bgfg routine will need 
// to use the argv array as well to look for a job number.
//
int builtin_cmd(char **argv) 
{
  string cmd(argv[0]);
  
  /* check for quitting or exitting first */
  if(cmd == "quit") exit(0);
  
  /* If a forground or background task    */
  else if(cmd == "fg" || cmd == "bg"){
	do_bgfg(argv);
	return 1;
  }
  else if(cmd == "jobs"){
	listjobs(jobs);
	return 1;
  }
  else
	printf("%s : Command does not exist\n", argv[0]);

  return 0;
}

/////////////////////////////////////////////////////////////////////////////
//
// do_bgfg - Execute the builtin bg and fg commands
//
void do_bgfg(char **argv) 
{
  struct job_t *jobp=NULL;
    
  /* Ignore command if no argument */
  if (argv[1] == NULL) {
    printf("%s command requires PID or %%jobid argument\n", argv[0]);
    return;
  }
    
  /* Parse the required PID or %JID arg */
  if (isdigit(argv[1][0])) {
    pid_t pid = atoi(argv[1]);
    if (!(jobp = getjobpid(jobs, pid))) {
      printf("(%d): No such process\n", pid);
      return;
    }
  }
  else if (argv[1][0] == '%') {
    int jid = atoi(&argv[1][1]);
    if (!(jobp = getjobjid(jobs, jid))) {
      printf("%s: No such job\n", argv[1]);
      return;
    }
  }	    
  else {
    printf("%s: argument must be a PID or %%jobid\n", argv[0]);
    return;
  }

  //
  // You need to complete rest. At this point,
  // the variable 'jobp' is the job pointer
  // for the job ID specified as an argument.
  //
  // Your actions will depend on the specified command
  // so we've converted argv[0] to a string (cmd) for
  // your benefit.
  //
  string cmd(argv[0]);

	if(cmd == "fg"){
		if(jobp->state==ST){
			kill(-jobp -> pid, SIGCONT);
		}
		jobp -> state = FG;//set state to foreground job
		waitfg(jobp -> pid)	
		
	}else if(cmd == "bg"){
		//continue it
		kill(-jobp -> pid, SIGCONT);
		//change the state to BG
		jobp -> state = BG;
	}
	
	return;
} ./sdriver.pl -t trace01.txt -s ./tsh -a "-p"