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

/** To call, push one of these and pop to return */
public class Context {
	Context invokingContext;	// parent in the stack or "caller"
	FuncMetaData metadata;		// info about function we're executing
	int returnip;
	int[] locals; // args + locals, indexed from 0

	public Context(Context invokingContext, int returnip, FuncMetaData metadata) {
		this.invokingContext = invokingContext;
		this.returnip = returnip;
		this.metadata = metadata;
		locals = new int[metadata.nargs+metadata.nlocals];
	}
}


