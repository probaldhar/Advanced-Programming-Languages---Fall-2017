import javax.swing.*;
import javax.swing.filechooser.FileSystemView;
import java.io.File;
import java.util.Arrays;
import java.util.List;

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

public class Test {

	public static void main(String[] args) {

		// Array of FuncMetaData
		FuncMetaData[] test_metadata = new FuncMetaData[10];

		// Array of literals
		String[] literalArray = new String[100];

		// Object of readFromFile class
		readFromFile aReadFromFile = new readFromFile();

		// ArrayList to store the array of operands and operator
		List<Integer> buildArray;

		// File Chooser
		JFileChooser jfc = new JFileChooser(FileSystemView.getFileSystemView().getHomeDirectory());

   	jfc.setCurrentDirectory(new File("."));
// 		jfc.setCurrentDirectory(new File(System.getProperty("user.dir"))); 

		int returnValue = jfc.showOpenDialog(null);

		if (returnValue == JFileChooser.APPROVE_OPTION) {
      
         // getting the selected file
			File selectedFile = jfc.getSelectedFile();

			// get the arrayList for the operands and operators
			buildArray = aReadFromFile.readFromFileFunc(selectedFile.getAbsolutePath(), test_metadata, literalArray);

			// Converting ArrayList to an array - first argument of VM
			Integer[] newArray = new Integer[buildArray.size()];
			newArray = buildArray.toArray(newArray);

			// Need Java 8 for this
			// Converting Integer[] to int[]
			int[] intArray = Arrays.stream(newArray).mapToInt(Integer::intValue).toArray();

			// Testing
			VM vm = new VM(intArray, 2, test_metadata, literalArray);
			vm.trace = false;
			vm.exec(test_metadata[0].address);
			System.out.println("after GCDFunc/GCDEXEC");

		}
      
    }
}


