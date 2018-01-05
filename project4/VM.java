/*********************************************************************************
Copyright (c) 2014, Terence Parr
All rights reserved.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

https://github.com/parrt/simple-virtual-machine/
 *********************************************************************************/

import java.util.ArrayList;
import java.util.List;

/** A simple stack-based interpreter */
public class VM {

	Bytecode byteInstance = new Bytecode();

	// INSTRUCTION BYTECODES (byte is signed; use a short to keep 0..255)
	public static final short IADD = 1;     // int add
	public static final short ISUB = 2;
	public static final short IMUL = 3;
	public static final short ILT  = 4;     // int less than
	public static final short IEQ  = 5;     // int equal
	public static final short BR   = 6;     // branch
	public static final short BRT  = 7;     // branch if true
	public static final short BRF  = 8;     // branch if true
	public static final short ICONST = 9;   // push constant integer
	public static final short LOAD   = 10;  // load from local context
	public static final short GLOAD  = 11;  // load from global memory
	public static final short STORE  = 12;  // store in local context
	public static final short GSTORE = 13;  // store in global memory
	public static final short PRINT  = 14;  // print stack top
	public static final short POP  = 15;    // throw away top of stack
	public static final short CALL = 16;
	public static final short RET  = 17;    // return with/without value
	public static final short HALT = 18;
	public static final short MOD = 19;
	public static final short EXEC = 20;


	public static final int DEFAULT_STACK_SIZE = 1000;
	public static final int DEFAULT_CALL_STACK_SIZE = 1000;
	public static final int FALSE = 0;
	public static final int TRUE = 1;

	// registers
	int ip;             // instruction pointer register
	int sp = -1;  		  // stack pointer register

	// memory
	int[] code;         // word-addressable code memory but still bytecodes.
	int[] globals;      // global variable space
	int[] stack;		  // Operand stack, grows upwards
	Context ctx;		  // the active context

	/** Metadata about the functions allows us to refer to functions by
	 *  their index in this table. It makes code generation easier for
	 *  the bytecode compiler because it doesn't have to resolve
	 *  addresses for forward references. It can generate simply
	 *  "CALL i" where i is the index of the function. Later, the
	 *  compiler can store the function address in the metadata table
	 *  when the code is generated for that function.
	 */
	private FuncMetaData[] metadata;

	// Array of literals
	private String[] literalArrayVM;

	public boolean trace = false;

	public VM(int[] code, int nglobals, FuncMetaData[] metadata, String[] literalPool) {
		this.code = code;
		globals = new int[nglobals];
		stack = new int[DEFAULT_STACK_SIZE];
		this.metadata = metadata;
		this.literalArrayVM = literalPool;
	}

	public void exec(int startip) {
		ip = startip;
		ctx = new Context(null,0,metadata[0]); // simulate a call to main()
		cpu();
	}

	/** Simulate the fetch-decode execute cycle */
	protected void cpu() {
		int opcode = code[ip];
		int a,b,addr,regnum;
		// String to hold the return value from JavaRunCommand
		String getRetFromJavaRunCommand;
		while (opcode!= HALT && ip < code.length) {
			if ( trace ) System.err.printf("%-35s", disInstr());
			ip++; //jump to next instruction or to operand
			switch (opcode) {
				case IADD:
					b = stack[sp--];   			// 2nd opnd at top of stack
					a = stack[sp--]; 			// 1st opnd 1 below top
					stack[++sp] = a + b;      	// push result
					break;
				case ISUB:
					b = stack[sp--];
					a = stack[sp--];
					stack[++sp] = a - b;
					break;
				case IMUL:
					b = stack[sp--];
					a = stack[sp--];
					stack[++sp] = a * b;
					break;
				case ILT :
					b = stack[sp--];
					a = stack[sp--];
					stack[++sp] = (a < b) ? TRUE : FALSE;
					break;
				case IEQ :
					b = stack[sp--];
					a = stack[sp--];
					stack[++sp] = (a == b) ? TRUE : FALSE;
					break;
				case BR :
					ip = code[ip++];
					break;
				case BRT :
					addr = code[ip++];
					if ( stack[sp--]==TRUE ) ip = addr;
					break;
				case BRF :
					addr = code[ip++];
					if ( stack[sp--]==FALSE ) ip = addr;
					break;
				case ICONST:
					stack[++sp] = code[ip++]; // push operand
					break;
				case LOAD : // load local or arg; 1st local is fp+1, args are fp-3, fp-4, fp-5, ...
                    load();
					break;
				case GLOAD :// load from global memory
					addr = code[ip++];
					stack[++sp] = globals[addr];
					break;
				case STORE :
					regnum = code[ip++];
					ctx.locals[regnum] = stack[sp--];
					break;
				case GSTORE :
					addr = code[ip++];
					globals[addr] = stack[sp--];
					break;
				case PRINT :
					System.out.println(stack[sp--]);
					break;
				case POP:
					--sp;
					break;
				case CALL :
					// expects all args on stack
					int findex = code[ip++];			// index of target function
					int nargs = metadata[findex].nargs;	// how many args got pushed
					ctx = new Context(ctx,ip,metadata[findex]);
					// copy args into new context
					for (int i=0; i<nargs; i++) {
						ctx.locals[i] = stack[sp-i];
					}
					sp -= nargs;
					ip = metadata[findex].address;		// jump to function
					break;
				case RET:
					ip = ctx.returnip;
					ctx = ctx.invokingContext;			// pop
					break;
				case MOD:
					b = stack[sp--];   			// 2nd opnd at top of stack
					a = stack[sp--]; 			// 1st opnd 1 below top
					stack[++sp] = a % b;      	// push result
					break;
				case EXEC:
					// Code to execute an external program
					addr = code[ip++];

					// Instance of readFromFile class
					readFromFile aReadFromFile = new readFromFile();

					// we need the string literals in here - how do I get that in here?
					getRetFromJavaRunCommand = aReadFromFile.JavaRunCommand(literalArrayVM[addr]);

					stack[++sp] = Integer.parseInt(getRetFromJavaRunCommand);      	// push result
					break;
				default :
					throw new Error("invalid opcode: "+opcode+" at ip="+(ip-1));
			}
			if ( trace ) 
          		System.err.printf("%-22s %s\n", stackString(), callStackString());
			opcode = code[ip];
		}
		if ( trace ) System.err.printf("%-35s", disInstr());
		if ( trace ) System.err.println(stackString());
		if ( trace ) dumpDataMemory();
	}

    private void load() {
        int regnum;
        regnum = code[ip++];
        stack[++sp] = ctx.locals[regnum];
    }

	protected String stackString() {
		StringBuilder buf = new StringBuilder();
		buf.append("stack=[");
		for (int i = 0; i <= sp; i++) {
			int o = stack[i];
			buf.append(" ");
			buf.append(o);
		}
		buf.append(" ]");
		return buf.toString();
	}

	protected String callStackString() {
		List<String> stack = new ArrayList<String>();
		Context c = ctx;
		while ( c!=null ) {
			if ( c.metadata!=null ) {
				stack.add(0, c.metadata.name);
			}
			c = c.invokingContext;
		}
		return "calls="+stack.toString();
	}

	protected String disInstr() {
		int opcode = code[ip];

		String opName = Bytecode.instructions[opcode].name;
		StringBuilder buf = new StringBuilder();
		buf.append(String.format("%04d:\t%-11s", ip, opName));
		int nargs = Bytecode.instructions[opcode].n;
		if ( nargs>0 ) {
			List<String> operands = new ArrayList<String>();
			for (int i=ip+1; i<=ip+nargs; i++) {
				operands.add(String.valueOf(code[i]));
			}
			for (int i = 0; i<operands.size(); i++) {
				String s = operands.get(i);
				if ( i>0 ) buf.append(", ");
				buf.append(s);
			}
		}
		return buf.toString();
	}

	protected void dumpDataMemory() {
		System.err.println("Data memory:");
		int addr = 0;
		for (int o : globals) {
			System.err.printf("%04d: %s\n", addr, o);
			addr++;
		}
		System.err.println();
	}
}








