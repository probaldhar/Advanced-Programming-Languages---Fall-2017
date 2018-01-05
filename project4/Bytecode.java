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



public class Bytecode {

	public static class Instruction {

		String name; // E.g., "iadd", "call"
		int n = 0;

		public Instruction(String name) {
        	this(name,0);
      	}
		
      	public Instruction(String name, int nargs) {
			this.name = name;
			this.n = nargs;
		}
	}


	/**
	 *
	 */
	public static Instruction[] instructions = new Instruction[] {
		null, // <INVALID>
		new Instruction("iadd"), // index is the opcode
		new Instruction("isub"),
		new Instruction("imul"),
		new Instruction("ilt"),
		new Instruction("ieq"),
		new Instruction("br", 1),
		new Instruction("brt", 1),
		new Instruction("brf", 1),
		new Instruction("iconst", 1),
		new Instruction("load", 1),
		new Instruction("gload", 1),
		new Instruction("store", 1),
		new Instruction("gstore", 1),
		new Instruction("print"),
		new Instruction("pop"),
		new Instruction("call", 1), // call index of function in meta-info table
		new Instruction("ret"),
		new Instruction("halt"),
		new Instruction("mod"),
		new Instruction("exec", 1)
	};
}


