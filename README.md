# Steps to use (in Linux)

If you have Sublime Text installed, you can use these commands (which are based on the `subl` command line tool that Sublime Text uses). There is a default `template.cpp` file that can be used as a template. To make a new file named `<filename>.cpp` out of this template, simply run the following command.
```
  bash make-cp <filename>
```
This will create a new file for you, and open it in Sublime Text for you to modify. To run the file, either follow standard C++ building steps, or you can also do 
```
  bash run-cp <filename>
```
`template.cpp` uses the files `input.txt`, `error.txt` and `output.txt` for input, error and output redirection, if the flag `ONLINE_JUDGE` is not set (most online judges set this flag to true). So, after running the above command, you should be able to see the output in the `output.txt` file.
