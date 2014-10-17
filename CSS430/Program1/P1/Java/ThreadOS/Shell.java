/*
CSS430B Spring 2014
Professor Stephen Dame
Programming Assignment 1 Part 2

Specification
Shell Command Interpreter
User types in command followed by a & or ;
& following a command will execute next command concurrently
; following a command will wait until command has completed 
	before executing next command

Test using the following commands
PingPong abc 10000000 & PingPong xyz 10000000 & PingPong 123 10000000 &
PingPong abc 10000000 ; PingPong xyz 10000000 ; PingPong 123 10000000 ;

Custom test (mixing & and ;)
PingPong abc 10000000 & PingPong xyz 10000000 ; PingPong 123 10000000 ;

Current Implementation
For loop to increment the prompt number
While loop to process and execute commands

Ideal Implementation
I don't know, recursive solution was getting too complex
*/
public class Shell extends Thread{

    public Shell() {
    }

    public void run() {
		//count how many times starting at 1 that a command was executed
        for(int i = 1;;i++) {
			//show prompt in style of Shell[i]%
			//I looked into Loader.java for how it showed the --> prompt and mimicked
            String command = "";
            do {
                StringBuffer s = new StringBuffer();
				//Prompt Format
                SysLib.cout("shell[" + i + "]% ");
				//User Input
                SysLib.cin(s);
                command = s.toString();
            } while (command.length() == 0); //If command length is 0, keep prompting user
			
			//Convert string to array of strings (HINT)
            String[] strArgs = SysLib.stringToArgs(command);
			
			//Parse commands from left to right to cmdStart is at 0
            int cmdStart = 0;
			//Keep looping until no more commands possible to parse
            while (cmdStart < strArgs.length) {
                for (int cmdEnd = cmdStart; cmdEnd < strArgs.length; cmdEnd++) {
					//when cmdEnd hits a &, ;, or end of the string array, that will mean there is a command
                    if (strArgs[cmdEnd].equals(";") || strArgs[cmdEnd].equals("&") || (cmdEnd == strArgs.length - 1)) {
						//get the number of elements the command takes in the array
                        int size = cmdEnd - cmdStart;
						//check for single command with no & or ; or end command and increment size
						//PingPong abc 1000 would result in size 2 so must add 1
                        if(!strArgs[cmdEnd].equals(";") && !strArgs[cmdEnd].equals("&") && cmdEnd == strArgs.length - 1) {
                            size++;
                        }
						//Build a string array as the SysLib.exec takes String array
						//Just in case size is 0, create size of 1 because to get here, the command had to be
						//more than 0 length
                        String[] newCmd = new String[size > 0 ? size : 1];
						//Get a subset of the string to build command using cmdStart and size
                        for (int j = 0; j < newCmd.length; j++) {
                            newCmd[j] = strArgs[cmdStart + j];
                        }
						//if user types in only exit, then exit and return
						//check if user typed in exit followed by more input
                        if (strArgs.length == 1 && newCmd[0].equalsIgnoreCase("exit")) {
                            SysLib.exit();
                            return;
                        }
						//execute command
                        int child = SysLib.exec(newCmd);
						//if the end of the command detected was not a &
						//wait for the process to complete before continuing
                        if (!strArgs[cmdEnd].equals("&")) {
                            while ((child != -1) && (SysLib.join() != child)) {
                            }
                        }
						//cmdStart for the next command is after the end of the current command
                        cmdStart = cmdEnd + 1;
                    }
                }
            }
        }
    }
}
