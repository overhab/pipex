# pipex
Pipex programm that simulates the launch of a command like: 
`< file1 cmd1 | cmd2 > file2`

For example:
`./pipex infile ``ls -l'' ``wc -l'' outfile`

should do the same as 
`< infile ls -l | wc -l > outfile`

## Usage

`make` to compile excecutable `pipex`

`./pipex file1 cmd1 cmd2 file2`

- `file1` and `file2` are file names
- `cmd1` and `cmd2` are shell commands with
their parameters.
